/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/// \addtogroup u2w
/// @{
/// \file

#ifndef _OPCODES_H
#define _OPCODES_H

#include "Common.h"

// Note: this include need for be sure have full definition of class WorldSession
//       if this class definition not complite then VS for x64 release use different size for
//       struct OpcodeHandler in this header and Opcode.cpp and get totally wrong data from
//       table opcodeTable in source when Opcode.h included but WorldSession.h not included
#include "WorldSession.h"

/// List of Opcodes
enum Opcodes
{
#error You need to add opcode ids.
};

/// Player state
enum SessionStatus
{
    STATUS_AUTHED = 0,                                      ///< Player authenticated (_player==NULL, m_playerRecentlyLogout = false or will be reset before handler call, m_GUID have garbage)
    STATUS_LOGGEDIN,                                        ///< Player in game (_player!=NULL, m_GUID == _player->GetGUID(), inWorld())
    STATUS_TRANSFER,                                        ///< Player transferring to another map (_player!=NULL, m_GUID == _player->GetGUID(), !inWorld())
    STATUS_LOGGEDIN_OR_RECENTLY_LOGGEDOUT,                  ///< _player!= NULL or _player==NULL && m_playerRecentlyLogout, m_GUID store last _player guid)
    STATUS_NEVER,                                           ///< Opcode not accepted from client (deprecated or server side only)
    STATUS_UNHANDLED                                        ///< We don' handle this opcode yet
};

enum PacketProcessing
{
    PROCESS_INPLACE = 0,                                    //process packet whenever we receive it - mostly for non-handled or non-implemented packets
    PROCESS_THREADUNSAFE,                                   //packet is not thread-safe - process it in World::UpdateSessions()
    PROCESS_THREADSAFE                                      //packet is thread-safe - process it in Map::Update()
};

class WorldPacket;

struct OpcodeHandler
{
    char const* name;
    SessionStatus status;
    PacketProcessing packetProcessing;
    void (WorldSession::*handler)(WorldPacket& recvPacket);
};

#define MAX_OPCODE_HANDLER_INDEX    2048

#define CONDENSE_OPCODE(a1) (a1 & 3 | ((a1 & 8 | ((a1 & 0x20 | ((a1 & 0x300 | (a1 >> 1) & 0x7C00) >> 2)) >> 1)) >> 1))

#define DEFINE_OPCODE_HANDLER(opcode, status, processing, handler)                              \
    if (opcode != UNKNOWN_OPCODE) {                                                             \
        uint32 condensed = CONDENSE_OPCODE(opcode);                                             \
        if (condensed >= MAX_OPCODE_HANDLER_INDEX)                                              \
        {                                                                                       \
            sLog.outError("Condensed opcode out of range " #opcode " %u -> %u",                 \
                opcode, condensed);                                                             \
        }                                                                                       \
        else opcodeTable[CONDENSE_OPCODE(opcode)] = new OpcodeHandler(#opcode, status, processing, handler);\
    }

extern OpcodeHandler* opcodeTable[MAX_OPCODE_HANDLER_INDEX];
void InitializeOpcodes();

/// Lookup opcode name for human understandable logging
inline const char* LookupOpcodeName(uint16 id)
{
    return "Unknown opcode";
}
#endif
/// @}
