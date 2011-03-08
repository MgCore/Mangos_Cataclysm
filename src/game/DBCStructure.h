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

#ifndef MANGOS_DBCSTRUCTURE_H
#define MANGOS_DBCSTRUCTURE_H

#include "Common.h"
#include "DBCEnums.h"
#include "Path.h"
#include "Platform/Define.h"

#include <map>
#include <set>
#include <vector>

// Structures using to access raw DBC data and required packing to portability

// GCC have alternative #pragma pack(N) syntax and old gcc version not support pack(push,N), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

typedef char const* const* DBCString;                       //char* DBCStrings[MAX_LOCALE];

struct AchievementEntry
{
    uint32    ID;                                           // 0
    uint32    factionFlag;                                  // 1 -1=all, 0=horde, 1=alliance
    uint32    mapID;                                        // 2 -1=none
    //uint32 parentAchievement;                             // 3 its Achievement parent (can`t start while parent uncomplete, use its Criteria if don`t have own, use its progress on begin)
    DBCString name;                                         // 4
    //char *description;                                    // 5
    uint32    categoryId;                                   // 6
    uint32    points;                                       // 7 reward points
    //uint32 OrderInCategory;                               // 8
    uint32    flags;                                        // 9
    //uint32    icon;                                       // 10 icon (from SpellIcon.dbc)
    //char *reward;                                         // 11
    uint32 count;                                           // 12 - need this count of completed criterias (own or referenced achievement criterias)
    uint32 refAchievement;                                  // 13 - referenced achievement (counting of all completed criterias)
};

struct AchievementCategoryEntry
{
    uint32    ID;                                           // 0
    uint32    parentCategory;                               // 1 -1 for main category
    //char *name;                                           // 2
    //uint32    sortOrder;                                  // 3
};

struct AchievementCriteriaEntry
{
    uint32  ID;                                             // 0
    uint32  referredAchievement;                            // 1
    uint32  requiredType;                                   // 2
    union
    {
        // ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE          = 0
        // TODO: also used for player deaths..
        struct
        {
            uint32  creatureID;                             // 3
            uint32  creatureCount;                          // 4
        } kill_creature;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_BG                 = 1
        struct
        {
            uint32  bgMapID;                                // 3
            uint32  winCount;                               // 4
            uint32  additionalRequirement1_type;            // 5 additional requirement 1 type
            uint32  additionalRequirement1_value;           // 6 additional requirement 1 value
            uint32  additionalRequirement2_type;            // 7 additional requirement 2 type
            uint32  additionalRequirement2_value;           // 8 additional requirement 1 value
        } win_bg;

        // ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL            = 5
        struct
        {
            uint32  unused;                                 // 3
            uint32  level;                                  // 4
        } reach_level;

        // ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL      = 7
        struct
        {
            uint32  skillID;                                // 3
            uint32  skillLevel;                             // 4
        } reach_skill_level;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT   = 8
        struct
        {
            uint32  linkedAchievement;                      // 3
        } complete_achievement;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT   = 9
        struct
        {
            uint32  unused;                                 // 3
            uint32  totalQuestCount;                        // 4
        } complete_quest_count;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY = 10
        struct
        {
            uint32  unused;                                 // 3
            uint32  numberOfDays;                           // 4
        } complete_daily_quest_daily;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE = 11
        struct
        {
            uint32  zoneID;                                 // 3
            uint32  questCount;                             // 4
        } complete_quests_in_zone;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST   = 14
        struct
        {
            uint32  unused;                                 // 3
            uint32  questCount;                             // 4
        } complete_daily_quest;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND  = 15
        struct
        {
            uint32  mapID;                                  // 3
        } complete_battleground;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP           = 16
        struct
        {
            uint32  mapID;                                  // 3
        } death_at_map;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON       = 18
        struct
        {
            uint32  manLimit;                               // 3
        } death_in_dungeon;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID          = 19
        struct
        {
            uint32  groupSize;                              // 3 can be 5, 10 or 25
        } complete_raid;

        // ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE     = 20
        struct
        {
            uint32  creatureEntry;                          // 3
        } killed_by_creature;

        // ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING     = 24
        struct
        {
            uint32  unused;                                 // 3
            uint32  fallHeight;                             // 4
        } fall_without_dying;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM            = 26
        struct
        {
            uint32 type;                                    // 3, see enum EnviromentalDamage
        } death_from;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST         = 27
        struct
        {
            uint32  questID;                                // 3
            uint32  questCount;                             // 4
        } complete_quest;

        // ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET        = 28
        // ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2       = 69
        struct
        {
            uint32  spellID;                                // 3
            uint32  spellCount;                             // 4
        } be_spell_target;

        // ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL             = 29
        // ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2            = 110
        struct
        {
            uint32  spellID;                                // 3
            uint32  castCount;                              // 4
        } cast_spell;

        // ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA = 31
        struct
        {
            uint32  areaID;                                 // 3 Reference to AreaTable.dbc
            uint32  killCount;                              // 4
        } honorable_kill_at_area;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA              = 32
        struct
        {
            uint32  mapID;                                  // 3 Reference to Map.dbc
        } win_arena;

        // ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA             = 33
        struct
        {
            uint32  mapID;                                  // 3 Reference to Map.dbc
        } play_arena;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL            = 34
        struct
        {
            uint32  spellID;                                // 3 Reference to Map.dbc
        } learn_spell;

        // ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM               = 36
        struct
        {
            uint32  itemID;                                 // 3
            uint32  itemCount;                              // 4
        } own_item;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA        = 37
        struct
        {
            uint32  unused;                                 // 3
            uint32  count;                                  // 4
            uint32  flag;                                   // 5 4=in a row
        } win_rated_arena;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING    = 38
        struct
        {
            uint32  teamtype;                               // 3 {2,3,5}
        } highest_team_rating;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_PERSONAL_RATING= 39
        struct
        {
            uint32  teamtype;                               // 3 {2,3,5}
            uint32  teamrating;                             // 4
        } highest_personal_rating;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL      = 40
        struct
        {
            uint32  skillID;                                // 3
            uint32  skillLevel;                             // 4 apprentice=1, journeyman=2, expert=3, artisan=4, master=5, grand master=6
        } learn_skill_level;

        // ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM               = 41
        struct
        {
            uint32  itemID;                                 // 3
            uint32  itemCount;                              // 4
        } use_item;

        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM              = 42
        struct
        {
            uint32  itemID;                                 // 3
            uint32  itemCount;                              // 4
        } loot_item;

        // ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA           = 43
        struct
        {
            // TODO: This rank is _NOT_ the index from AreaTable.dbc
            uint32  areaReference;                          // 3
        } explore_area;

        // ACHIEVEMENT_CRITERIA_TYPE_OWN_RANK               = 44
        struct
        {
            // TODO: This rank is _NOT_ the index from CharTitles.dbc
            uint32  rank;                                   // 3
        } own_rank;

        // ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT          = 45
        struct
        {
            uint32  unused;                                 // 3
            uint32  numberOfSlots;                          // 4
        } buy_bank_slot;

        // ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION        = 46
        struct
        {
            uint32  factionID;                              // 3
            uint32  reputationAmount;                       // 4 Total reputation amount, so 42000 = exalted
        } gain_reputation;

        // ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION= 47
        struct
        {
            uint32  unused;                                 // 3
            uint32  numberOfExaltedFactions;                // 4
        } gain_exalted_reputation;

        // ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP      = 48
        struct
        {
            uint32 unused;                                  // 3
            uint32 numberOfVisits;                          // 4
        } visit_barber;

        // ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM        = 49
        // TODO: where is the required itemlevel stored?
        struct
        {
            uint32  itemSlot;                               // 3
            uint32  count;                                  // 4
        } equip_epic_item;

        // ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT      = 50
        struct
        {
            uint32  rollValue;                              // 3
            uint32  count;                                  // 4
        } roll_need_on_loot;
        // ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT      = 51
        struct
        {
            uint32  rollValue;                              // 3
            uint32  count;                                  // 4
        } roll_greed_on_loot;

        // ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS               = 52
        struct
        {
            uint32  classID;                                // 3
            uint32  count;                                  // 4
        } hk_class;

        // ACHIEVEMENT_CRITERIA_TYPE_HK_RACE                = 53
        struct
        {
            uint32  raceID;                                 // 3
            uint32  count;                                  // 4
        } hk_race;

        // ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE               = 54
        // TODO: where is the information about the target stored?
        struct
        {
            uint32  emoteID;                                // 3 enum TextEmotes
            uint32  count;                                  // 4 count of emotes, always required special target or requirements
        } do_emote;
        // ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE            = 13
        // ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE           = 55
        // ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS      = 56
        struct
        {
            uint32  unused;                                 // 3
            uint32  count;                                  // 4
            uint32  flag;                                   // 5 =3 for battleground healing
            uint32  mapid;                                  // 6
        } healing_done;

        // ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM             = 57
        struct
        {
            uint32  itemID;                                 // 3
            uint32  count;                                  // 4
        } equip_item;

        // ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD= 62
        struct
        {
            uint32  unused;                                 // 3
            uint32  goldInCopper;                           // 4
        } quest_reward_money;


        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY             = 67
        struct
        {
            uint32  unused;                                 // 3
            uint32  goldInCopper;                           // 4
        } loot_money;

        // ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT         = 68
        struct
        {
            uint32  goEntry;                                // 3
            uint32  useCount;                               // 4
        } use_gameobject;

        // ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL       = 70
        // TODO: are those special criteria stored in the dbc or do we have to add another sql table?
        struct
        {
            uint32  unused;                                 // 3
            uint32  killCount;                              // 4
        } special_pvp_kill;

        // ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT     = 72
        struct
        {
            uint32  goEntry;                                // 3
            uint32  lootCount;                              // 4
        } fish_in_gameobject;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS = 75
        struct
        {
            uint32  skillLine;                              // 3
            uint32  spellCount;                             // 4
        } learn_skillline_spell;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL               = 76
        struct
        {
            uint32  unused;                                 // 3
            uint32  duelCount;                              // 4
        } win_duel;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER          = 96
        struct
        {
            uint32  powerType;                              // 3 mana=0, 1=rage, 3=energy, 6=runic power
        } highest_power;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT           = 97
        struct
        {
            uint32  statType;                               // 3 4=spirit, 3=int, 2=stamina, 1=agi, 0=strength
        } highest_stat;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER     = 98
        struct
        {
            uint32  spellSchool;                            // 3
        } highest_spellpower;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_RATING         = 100
        struct
        {
            uint32  ratingType;                             // 3
        } highest_rating;

        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE              = 109
        struct
        {
            uint32  lootType;                               // 3 3=fishing, 2=pickpocket, 4=disentchant
            uint32  lootTypeCount;                          // 4
        } loot_type;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE       = 112
        struct
        {
            uint32  skillLine;                              // 3
            uint32  spellCount;                             // 4
        } learn_skill_line;

        // ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL    = 113
        struct
        {
            uint32  unused;                                 // 3
            uint32  killCount;                              // 4
        } honorable_kill;

        struct
        {
            uint32  value;                                  // 3 main requirement
            uint32  count;                                  // 4 main requirement count
            uint32  additionalRequirement1_type;            // 5 additional requirement 1 type
            uint32  additionalRequirement1_value;           // 6 additional requirement 1 value
            uint32  additionalRequirement2_type;            // 7 additional requirement 2 type
            uint32  additionalRequirement2_value;           // 8 additional requirement 1 value
        } raw;
    };
    char*  name;                                            // 9
    uint32  completionFlag;                                 // 10
    //uint32  timedCriteriaStartType;                       // 11 Only appears with timed achievements, seems to be the type of starting a timed Achievement, only type 1 and some of type 6 need manual starting
                                                            // 1: ByEventId(?) (serverside IDs),    2: ByQuestId,   5: ByCastSpellId(?)
                                                            // 6: BySpellIdTarget(some of these are unknown spells, some not, some maybe spells)
                                                            // 7: ByKillNpcId,  9: ByUseItemId
    uint32  timedCriteriaMiscId;                            // 28 Alway appears with timed events, used internally to start the achievement, store
    uint32  timeLimit;                                      // 29 time limit in seconds
    uint32  showOrder;                                      // 30 show order, also used in achievement shift-links as index in state bitmask
    //uint32 unk1;                                          // 15 only one value, still unknown
    //uint32 unk2;                                          // 16 all zeros
    //uint32 moreRequirement[3];                            // 17-19
    //uint32 moreRequirementValue[3];                       // 20-22

    // helpers
    bool IsExplicitlyStartedTimedCriteria() const
    {
        if (!timeLimit)
            return false;

        // in case raw.value == timedCriteriaMiscId in timedCriteriaMiscId stored spellid/itemids for cast/use, so repeating aura start at first cast/use until fails
        return requiredType == ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST || raw.value != timedCriteriaMiscId;
    }
};

struct AreaTableEntry
{
    uint32  ID;                                             // 0
    uint32  mapid;                                          // 1
    uint32  zone;                                           // 2 if 0 then it's zone, else it's zone id of this area
    uint32  exploreFlag;                                    // 3, main index
    uint32  flags;                                          // 4, unknown value but 312 for all cities
                                                            // 5-9 unused
    int32   area_level;                                     // 10
    DBCString area_name;                                    // 11
    uint32  team;                                           // 12
                                                            // 13-19 unknown
    //uint32 unk20;                                         // 20 4.0.0
    //uint32 unk21;                                         // 21 4.0.0
    //uint32 unk22;                                         // 22 4.0.0
    //uint32 unk23;                                         // 23 4.0.0
    //uint32 unk24;                                         // 24 4.0.1, may be worldStateId
};

struct AreaGroupEntry
{
    uint32  AreaGroupId;                                    // 0
    uint32  AreaId[6];                                      // 1-6
    uint32  nextGroup;                                      // 7 index of next group
};

struct AreaTriggerEntry
{
    uint32  id;                                             // 0        m_ID
    uint32  mapid;                                          // 1        m_ContinentID
    float   x;                                              // 2        m_x
    float   y;                                              // 3        m_y
    float   z;                                              // 4        m_z
    //uint32                                                // 5
    //uint32                                                // 6
    //uint32                                                // 7
    float   radius;                                         // 8        m_radius
    float   box_x;                                          // 9        m_box_length
    float   box_y;                                          // 10       m_box_width
    float   box_z;                                          // 11       m_box_heigh
    float   box_orientation;                                // 12       m_box_yaw
};

struct ArmorLocationEntry
{
  uint32    InventoryType;                                  // 0
  float     Value[5];                                       // 1-5 multiplier for armor types (cloth...plate, no armor?)
};

struct AuctionHouseEntry
{
    uint32    houseId;                                      // 0 index
    uint32    faction;                                      // 1 id of faction.dbc for player factions associated with city
    uint32    depositPercent;                               // 2 1/3 from real
    uint32    cutPercent;                                   // 3
    //char*     name;                                       // 4
};

struct BankBagSlotPricesEntry
{
    uint32  ID;
    uint32  price;
};

struct BarberShopStyleEntry
{
    uint32  Id;                                             // 0
    uint32  type;                                           // 1 value 0 -> hair, value 2 -> facialhair
    //char*   name;                                         // 2 name of hair style
    //uint32  unk_name;                                     // 3, all empty
    //float   CostMultiplier;                               // 4 values 1 and 0.75
    uint32  race;                                           // 5 race
    uint32  gender;                                         // 6 0 -> male, 1 -> female
    uint32  hair_id;                                        // 7 real ID to hair/facial hair
};

struct BattlemasterListEntry
{
    uint32  id;                                             // 0
    int32   mapid[8];                                       // 1-8 mapid
    uint32  type;                                           // 9 (3 - BG, 4 - arena)
    //uint32 canJoinAsGroup;                                // 10 (0 or 1)
    DBCString name;                                         // 11
    uint32 maxGroupSize;                                    // 12 maxGroupSize, used for checking if queue as group
    uint32 HolidayWorldStateId;                             // 13 new 3.1
    uint32 minLevel;                                        // 14, min level (sync with PvPDifficulty.dbc content)
    uint32 maxLevel;                                        // 15, max level (sync with PvPDifficulty.dbc content)
    uint32 maxGroupSizeRated;                               // 16 4.0.1
    uint32 maxPlayers;                                      // 17 4.0.1
    uint32 minPlayers;                                      // 18 4.0.6
    uint32 rated;                                           // 19 4.0.3 value 2 for Rated Battlegrounds
};

/*struct Cfg_CategoriesEntry
{
    uint32 Index;                                           // categoryId, sent in RealmList packet
    uint32 Unk1;
    uint32 Unk2;
    uint32 IsTournamentRealm;
    char *categoryName;
}*/

/*struct Cfg_ConfigsEntry
{
    uint32 Id;
    uint32 Type;                                            // sent in RealmList packet
    uint32 IsPvp;
    uint32 IsRp;
};*/

#define MAX_OUTFIT_ITEMS 24

struct CharStartOutfitEntry
{
    //uint32 Id;                                            // 0
    uint32 RaceClassGender;                                 // 1 (UNIT_FIELD_BYTES_0 & 0x00FFFFFF) comparable (0 byte = race, 1 byte = class, 2 byte = gender)
    int32 ItemId[MAX_OUTFIT_ITEMS];                         // 2-25
    //int32 ItemDisplayId[MAX_OUTFIT_ITEMS];                // 26-29 not required at server side
    //int32 ItemInventorySlot[MAX_OUTFIT_ITEMS];            // 50-73 not required at server side
    //uint32 Unknown1;                                      // 74, unique values (index-like with gaps ordered in other way as ids)
    //uint32 Unknown2;                                      // 75
    //uint32 Unknown3;                                      // 76
    //uint32 Unknown4;                                      // 77
    //uint32 Unknown5;                                      // 78
};

struct CharTitlesEntry
{
    uint32  ID;                                             // 0, title ids, for example in Quest::GetCharTitleId()
    //uint32      unk1;                                     // 1 flags?
    DBCString name;                                         // 2
    //char*       name2;                                    // 3, unused
    uint32  bit_index;                                      // 4 used in PLAYER_CHOSEN_TITLE and 1<<index in PLAYER__FIELD_KNOWN_TITLES
    //uint32                                                // 5
};

struct ChatChannelsEntry
{
    uint32  ChannelID;                                      // 0
    uint32  flags;                                          // 1
    //uint32                                                // 2
    DBCString pattern;                                      // 3
    //char*       name;                                     // 4
};

struct ChrClassesEntry
{
    uint32  ClassID;                                        // 0
    uint32  powerType;                                      // 1
                                                            // 2, unused
    DBCString name;                                         // 3 unused
    //char*       nameFemale;                               // 4 unused, if different from base (male) case
    //char*       nameNeutralGender;                        // 5 unused, if different from base (male) case
    //char*       capitalizedName                           // 6, unused capitalized name
    uint32  spellfamily;                                    // 7
    //uint32 flags2;                                        // 8, unused 0x08 HasRelicSlot
    uint32  CinematicSequence;                              // 9 id from CinematicSequences.dbc
    uint32  expansion;                                      // 10 (0 - original race, 1 - tbc addon, ...)
    //uint32                                                // 11
    //uint32                                                // 12
    //uint32                                                // 13
};

struct ChrRacesEntry
{
    uint32      RaceID;                                     // 0
                                                            // 1 unused
    uint32      FactionID;                                  // 2 faction template id
                                                            // 3 unused
    uint32      model_m;                                    // 4
    uint32      model_f;                                    // 5
                                                            // 6 unused
    uint32      TeamID;                                     // 7 (7-Alliance 1-Horde)
                                                            // 8-11 unused
    uint32      CinematicSequence;                          // 12 id from CinematicSequences.dbc
    //uint32    unk_322;                                    // 13 faction (0 alliance, 1 horde, 2 not available?)
    DBCString name;                                         // 14 used for DBC language detection/selection
    //char*       nameFemale;                               // 15, if different from base (male) case
    //char*       nameNeutralGender;                        // 16, if different from base (male) case
                                                            // 17-19 unused
    uint32      expansion;                                  // 20 (0 - original race, 1 - tbc addon, ...)
    //uint32                                                // 21 (23 for worgens)
    //uint32                                                // 22 4.0.0
    //uint32                                                // 23 4.0.0
};

/* not used
struct CinematicCameraEntry
{
    uint32      id;                                         // 0 index
    char*       filename;                                   // 1
    uint32      soundid;                                    // 2 in SoundEntries.dbc or 0
    float       start_x;                                    // 3
    float       start_y;                                    // 4
    float       start_z;                                    // 5
    float       unk6;                                       // 6 speed?
};
*/

struct CinematicSequencesEntry
{
    uint32      Id;                                         // 0 index
    //uint32      unk1;                                     // 1 always 0
    //uint32      cinematicCamera;                          // 2 id in CinematicCamera.dbc
                                                            // 3-9 always 0
};

struct CreatureDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
                                                            // 1        m_modelID
                                                            // 2        m_soundID
    uint32      ExtendedDisplayInfoID;                      // 3        m_extendedDisplayInfoID -> CreatureDisplayInfoExtraEntry::DisplayExtraId
    float       scale;                                      // 4        m_creatureModelScale
                                                            // 5        m_creatureModelAlpha
                                                            // 6-8      m_textureVariation[3]
                                                            // 9        m_portraitTextureName
                                                            // 10       m_sizeClass
                                                            // 11       m_bloodID
                                                            // 12       m_NPCSoundID
                                                            // 13       m_particleColorID
                                                            // 14       m_creatureGeosetData
                                                            // 15       m_objectEffectPackageID
                                                            // 16
};

struct CreatureDisplayInfoExtraEntry
{
    uint32      DisplayExtraId;                             // 0        CreatureDisplayInfoEntry::m_extendedDisplayInfoID
    uint32      Race;                                       // 1
    //uint32    Gender;                                     // 2        Model gender, exist not small amount cases when query creature data return different gender from used model, so can't be replacement for model gender field.
    //uint32    SkinColor;                                  // 3
    //uint32    FaceType;                                   // 4
    //uint32    HairType;                                   // 5        CharHairGeosets.dbc
    //uint32    HairStyle;                                  // 6        CharSections.dbc, where GeneralType=3
    //uint32    BeardStyle;                                 // 7
    //uint32    Equipment[11];                              // 8-18     equipped static items EQUIPMENT_SLOT_HEAD..EQUIPMENT_SLOT_HANDS, client show its by self
    //uint32    CanEquip;                                   // 19       0..1 Can equip additional things when used for players
    //char*                                                 // 20       CreatureDisplayExtra-*.blp
};

struct CreatureFamilyEntry
{
    uint32  ID;                                             // 0        m_ID
    float   minScale;                                       // 1        m_minScale
    uint32  minScaleLevel;                                  // 2        m_minScaleLevel
    float   maxScale;                                       // 3        m_maxScale
    uint32  maxScaleLevel;                                  // 4        m_maxScaleLevel
    uint32  skillLine[2];                                   // 5-6      m_skillLine
    uint32  petFoodMask;                                    // 7        m_petFoodMask
    int32   petTalentType;                                  // 8        m_petTalentType
                                                            // 9        m_categoryEnumID
    DBCString Name;                                         // 10       m_name_lang
                                                            // 11       m_iconFile
};

#define MAX_CREATURE_SPELL_DATA_SLOT 4

struct CreatureSpellDataEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    spellId[MAX_CREATURE_SPELL_DATA_SLOT];        // 1-4      m_spells[4]
    //uint32    availability[MAX_CREATURE_SPELL_DATA_SLOT]; // 4-7      m_availability[4]
};

struct CreatureTypeEntry
{
    uint32    ID;                                           // 0        m_ID
    //char*   Name;                                         // 1        name
    //uint32    no_expirience;                              // 2 no exp? critters, non-combat pets, gas cloud.
};

/*struct CurrencyCategoryEntry
{
    uint32    ID;                                           // 0
    uint32    Unk1;                                         // 1        0 for known categories and 3 for unknown one (3.0.9)
    char*   Name;                                           // 2        name
};*/

struct CurrencyTypesEntry
{
    uint32    ID;                                           // 0        id
    //uint32    Category;                                   // 1        may be category
    //char *name;                                           // 2
    //char *iconName;                                       // 3
    //uint32 unk4;                                          // 4        all 0
    //uint32 unk5;                                          // 5        archaeology-related (?)
    //uint32 unk6;                                          // 6        archaeology-related (?)
    uint32 TotalCap;                                        // 7
    uint32 WeekCap;                                         // 8
    //int32 unk9;                                           // 9
    //char* description;                                    // 10
};

struct DurabilityCostsEntry
{
    uint32    Itemlvl;                                      // 0
    uint32    multiplier[29];                               // 1-29
};

struct DurabilityQualityEntry
{
    uint32    Id;                                           // 0
    float     quality_mod;                                  // 1
};

struct EmotesEntry
{
    uint32  Id;                                             // 0
    //char*   Name;                                         // 1, internal name
    //uint32  AnimationId;                                  // 2, ref to animationData
    uint32  Flags;                                          // 3, bitmask, may be unit_flags
    uint32  EmoteType;                                      // 4, Can be 0, 1 or 2 (determine how emote are shown)
    uint32  UnitStandState;                                 // 5, unconfirmed, may be enum UnitStandStateType
    //uint32  SoundId;                                      // 6, ref to soundEntries
};

struct EmotesTextEntry
{
    uint32  Id;
    uint32  textid;
};

struct FactionEntry
{
    uint32      ID;                                         // 0        m_ID
    int32       reputationListID;                           // 1        m_reputationIndex
    uint32      BaseRepRaceMask[4];                         // 2-5      m_reputationRaceMask
    uint32      BaseRepClassMask[4];                        // 6-9      m_reputationClassMask
    int32       BaseRepValue[4];                            // 10-13    m_reputationBase
    uint32      ReputationFlags[4];                         // 14-17    m_reputationFlags
    uint32      team;                                       // 18       m_parentFactionID
    float       spilloverRateIn;                            // 19       Faction gains incoming rep * spilloverRateIn
    float       spilloverRateOut;                           // 20       Faction outputs rep * spilloverRateOut as spillover reputation
    uint32      spilloverMaxRankIn;                         // 21       The highest rank the faction will profit from incoming spillover
    //uint32    spilloverRank_unk;                          // 22       It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    DBCString name;                                         // 23       m_name_lang
    //char*     description;                                // 24       m_description_lang
    //uint32                                                // 25

    // helpers

    int GetIndexFitTo(uint32 raceMask, uint32 classMask) const
    {
        for (int i = 0; i < 4; ++i)
        {
            if ((BaseRepRaceMask[i] == 0 || (BaseRepRaceMask[i] & raceMask)) &&
                (BaseRepClassMask[i] == 0 || (BaseRepClassMask[i] & classMask)))
                return i;
        }

        return -1;
    }
};

struct FactionTemplateEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      faction;                                    // 1        m_faction
    uint32      factionFlags;                               // 2        m_flags
    uint32      ourMask;                                    // 3        m_factionGroup
    uint32      friendlyMask;                               // 4        m_friendGroup
    uint32      hostileMask;                                // 5        m_enemyGroup
    uint32      enemyFaction[4];                            // 6        m_enemies[4]
    uint32      friendFaction[4];                           // 10       m_friend[4]
    //-------------------------------------------------------  end structure

    // helpers
    bool IsFriendlyTo(FactionTemplateEntry const& entry) const
    {
        if(entry.faction)
        {
            for(int i = 0; i < 4; ++i)
                if (enemyFaction[i]  == entry.faction)
                    return false;
            for(int i = 0; i < 4; ++i)
                if (friendFaction[i] == entry.faction)
                    return true;
        }
        return (friendlyMask & entry.ourMask) || (ourMask & entry.friendlyMask);
    }
    bool IsHostileTo(FactionTemplateEntry const& entry) const
    {
        if(entry.faction)
        {
            for(int i = 0; i < 4; ++i)
                if (enemyFaction[i]  == entry.faction)
                    return true;
            for(int i = 0; i < 4; ++i)
                if (friendFaction[i] == entry.faction)
                    return false;
        }
        return (hostileMask & entry.ourMask) != 0;
    }
    bool IsHostileToPlayers() const { return (hostileMask & FACTION_MASK_PLAYER) !=0; }
    bool IsNeutralToAll() const
    {
        for(int i = 0; i < 4; ++i)
            if (enemyFaction[i] != 0)
                return false;
        return hostileMask == 0 && friendlyMask == 0;
    }
    bool IsContestedGuardFaction() const { return (factionFlags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD)!=0; }
};

struct GameObjectDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
    // char* filename;                                      // 1
    // uint32 unknown2[10];                                 // 2-11     unknown data
    float  unknown12;                                       // 12-17    unknown size data, use first value as interact dist, mostly in hacks way
    // float  unknown13[5];                                 // 12-17    unknown size data
    // uint32 unknown18;                                    // 18       unknown data
};

struct GemPropertiesEntry
{
    uint32      ID;                                         // 0
    uint32      spellitemenchantement;                      // 1
    //uint32                                                // 2
    //uint32                                                // 3
    uint32      color;                                      // 4
    //uint32                                                // 5
};

struct GlyphPropertiesEntry
{
    uint32  Id;
    uint32  SpellId;
    uint32  TypeFlags;
    uint32  Unk1;                                           // GlyphIconId (SpellIcon.dbc)
};

struct GlyphSlotEntry
{
    uint32  Id;
    uint32  TypeFlags;
    uint32  Order;
};

// All Gt* DBC store data for 100 levels, some by 100 per class/race
#define GT_MAX_LEVEL    100
// gtOCTClassCombatRatingScalar.dbc stores data for 32 ratings, look at MAX_COMBAT_RATING for real used amount
#define GT_MAX_RATING   32

struct GtBarberShopCostBaseEntry
{
    //uint32 level;
    float   cost;
};

struct GtCombatRatingsEntry
{
    //uint32 level;
    float    ratio;
};

struct GtChanceToMeleeCritBaseEntry
{
    //uint32 level;
    float    base;
};

struct GtChanceToMeleeCritEntry
{
    //uint32 level;
    float    ratio;
};

struct GtChanceToSpellCritBaseEntry
{
    //uint32 level;
    float    base;
};

struct GtChanceToSpellCritEntry
{
    //uint32 level;
    float    ratio;
};

struct GtOCTClassCombatRatingScalarEntry
{
    float    ratio;
};

/*struct GtOCTRegenHPEntry
{
    //uint32 level;
    float    ratio;
};*/

//struct GtOCTRegenMPEntry
//{
//    float    ratio;
//};

/*struct GtRegenHPPerSptEntry
{
    //uint32 level;
    float    ratio;
};*/

struct GtRegenMPPerSptEntry
{
    //uint32 level;
    float    ratio;
};

struct gtSpellScaling
{
    uint32 level;
    float coef;
};

/*struct HolidayDescriptionsEntry
{
    uint32 ID;                                              // 0, this is NOT holiday id
    //char*     name;                                       // 1    m_name_lang
};*/

/*struct HolidayNamesEntry
{
    uint32 ID;                                              // 0, this is NOT holiday id
    //char*     name;                                       // 1    m_name_lang
};*/

struct HolidaysEntry
{
    uint32 ID;                                              // 0, holiday id
    //uint32 unk1;                                          // 1
    //uint32 unk2;                                          // 2
    //uint32 unk3[8]                                        // 3-10, empty fields
    //uint32 unk11[13]                                      // 11-23, some unknown data (bit strings?)
    //uint32 unk11[13]                                      // 24-36, some empty fields (continue prev?)
    //uint32 unk11[12]                                      // 37-48, counters?
    //uint32 holidayNameId;                                 // 49, id for HolidayNames.dbc
    //uint32 holidayDescriptionId;                          // 50, id for HolidayDescriptions.dbc
    //uint32 unk51;                                         // 51
    //uint32 unk52;                                         // 52
    //uint32 unk53;                                         // 53
    //uint32 unk54;                                         // 54
};

struct ItemArmorQualityEntry
{
  uint32    Id;                                             // 0 item level
  float     Value[7];                                       // 1-7 multiplier for item quality
  uint32    Id2;                                            // 8 item level
};

struct ItemArmorShieldEntry
{
  uint32    Id;                                             // 0 item level
  uint32    Id2;                                            // 1 item level
  float     Value[7];                                       // 2-8 multiplier for item quality
};

struct ItemArmorTotalEntry
{
  uint32    Id;                                             // 0 item level
  uint32    Id2;                                            // 1 item level
  float     Value[4];                                       // 2-5 multiplier for armor types (cloth...plate)
};

struct ItemBagFamilyEntry
{
    uint32   ID;                                            // 0
    //char*     name;                                       // 1     m_name_lang
};

struct ItemClassEntry
{
    //uint32 id;                                            // 0
    uint32 Class;                                           // 1 equal to id
    //uint32 unk2;                                          // 2 looks like second class
    //uint32 unk3;                                          // 3 1 for weapons
    //DBCString name;                                       // 4
};

struct ItemDisplayInfoEntry
{
    uint32      ID;                                         // 0        m_ID
                                                            // 1        m_modelName[2]
                                                            // 2        m_modelTexture[2]
                                                            // 3        m_inventoryIcon
                                                            // 4        m_geosetGroup[3]
                                                            // 5        m_flags
                                                            // 6        m_spellVisualID
                                                            // 7        m_groupSoundIndex
                                                            // 8        m_helmetGeosetVis[2]
                                                            // 9        m_texture[2]
                                                            // 10       m_itemVisual[8]
                                                            // 11       m_particleColorID
};

//struct ItemCondExtCostsEntry
//{
//    uint32      ID;
//    uint32      condExtendedCost;                         // ItemPrototype::CondExtendedCost
//    uint32      itemextendedcostentry;                    // ItemPrototype::ExtendedCost
//    uint32      arenaseason;                              // arena season number(1-4)
//};

// common struct for:
// ItemDamageAmmo.dbc
// ItemDamageOneHand.dbc
// ItemDamageOneHandCaster.dbc
// ItemDamageRanged.dbc
// ItemDamageThrown.dbc
// ItemDamageTwoHand.dbc
// ItemDamageTwoHandCaster.dbc
// ItemDamageWand.dbc
struct ItemDamageEntry
{
  uint32    Id;                                             // 0 item level
  float     Value[7];                                       // 1-7 multiplier for item quality
  uint32    Id2;                                            // 8 item level
};

#define MAX_EXTENDED_COST_ITEMS         5
#define MAX_EXTENDED_COST_CURRENCIES    5

struct ItemExtendedCostEntry
{
    uint32      ID;                                         // 0 extended-cost entry id
    //uint32    reqhonorpoints;                             // 1 required honor points
    //uint32    reqarenapoints;                             // 2 required arena points
    uint32      RequiredArenaSlot;                          // 4 arena slot restrictions (min slot value)
    uint32      RequiredItem[MAX_EXTENDED_COST_ITEMS];      // 5-8 required item id
    uint32      RequiredItemCount[MAX_EXTENDED_COST_ITEMS]; // 9-13 required count of 1st item
    uint32      RequiredPersonalArenaRating;                // 14 required personal arena rating
    //uint32                                                // 15
    uint32      RequiredCurrency[MAX_EXTENDED_COST_CURRENCIES];      // 16-20
    uint32      RequiredCurrencyCount[MAX_EXTENDED_COST_CURRENCIES]; // 21-25
    //uint32    something[5];                               // 26-30
};

struct ItemLimitCategoryEntry
{
    uint32      ID;                                         // 0 Id
    //char*     name;                                       // 1        m_name_lang
    uint32      maxCount;                                   // 2, max allowed equipped as item or in gem slot
    uint32      mode;                                       // 3, 0 = have, 1 = equip (enum ItemLimitCategoryMode)
};

struct ItemRandomPropertiesEntry
{
    uint32    ID;                                           // 0        m_ID
    //char*     internalName                                // 1        m_Name
    uint32    enchant_id[5];                                // 2-6      m_Enchantment
    DBCString nameSuffix;                                   // 7        m_name_lang
};

struct ItemRandomSuffixEntry
{
    uint32    ID;                                           // 0        m_ID
    DBCString nameSuffix;                                   // 1        m_name_lang
                                                            // 2        m_internalName
    uint32    enchant_id[5];                                // 3-7      m_enchantment
    uint32    prefix[5];                                    // 8-12     m_allocationPct
};

struct ItemSetEntry
{
    //uint32    id                                          // 0        m_ID
    DBCString name;                                         // 1        m_name_lang
    //uint32    itemId[17];                                 // 2-18     m_itemID
    uint32    spells[8];                                    // 19-26    m_setSpellID
    uint32    items_to_triggerspell[8];                     // 27-34    m_setThreshold
    uint32    required_skill_id;                            // 35       m_requiredSkill
    uint32    required_skill_value;                         // 36       m_requiredSkillRank
};

struct ItemSubClassEntry
{
    //uint32 id;
    uint32 Class;
    uint32 SubClass;
    //int32 unk3;
    //int32 unk4;
    //uint32 unk5;
    //uint32 unk6;
    //uint32 unk7;
    //uint32 unk8;
    //uint32 unk9;
    //uint32 unk10;
    //DBCString name1;
    //DBCString name2;
};

#define MAX_LOCK_CASE 8

struct LockEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      Type[MAX_LOCK_CASE];                        // 1-8      m_Type
    uint32      Index[MAX_LOCK_CASE];                       // 9-16     m_Index
    uint32      Skill[MAX_LOCK_CASE];                       // 17-24    m_Skill
    //uint32      Action[MAX_LOCK_CASE];                    // 25-32    m_Action
};

struct MailTemplateEntry
{
    uint32      ID;                                         // 0
    //char*       subject;                                  // 1
    DBCString content;                                      // 2
};

struct MapEntry
{
    uint32  MapID;                                          // 0
    //char*       internalname;                             // 1 unused
    uint32  map_type;                                       // 2
    //uint32 mapFlags;                                      // 3 some kind of flags (0x100 - CAN_CHANGE_PLAYER_DIFFICULTY)
    //uint32 unk4;                                          // 4 4.0.1
    //uint32 isPvP;                                         // 5 0 or 1 for battlegrounds (not arenas)
    DBCString name;                                         // 6
    uint32  linked_zone;                                    // 7 common zone for instance and continent map
    //char*     hordeIntro;                                 // 8 text for PvP Zones
    //char*     allianceIntro;                              // 9 text for PvP Zones
    uint32  multimap_id;                                    // 10 index in  LoadingScreens.dbc
    //float   BattlefieldMapIconScale;                      // 11 BattlefieldMapIconScale
    int32   ghost_entrance_map;                             // 12 map_id of entrance map in ghost mode (continent always and in most cases = normal entrance)
    float   ghost_entrance_x;                               // 13 entrance x coordinate in ghost mode  (in most cases = normal entrance)
    float   ghost_entrance_y;                               // 14 entrance y coordinate in ghost mode  (in most cases = normal entrance)
    //uint32  timeOfDayOverride;                            // 15 time of day override
    uint32  addon;                                          // 16 expansion
    //uint32 unkTime;                                       // 17 some kind of time?
    //uint32 maxPlayers;                                    // 18 max players
    //uint32 unk400;                                        // 19 new 4.0.0, mapid, related to phasing

    // Helpers
    uint32 Expansion() const { return addon; }

    bool IsDungeon() const { return map_type == MAP_INSTANCE || map_type == MAP_RAID; }
    bool IsNonRaidDungeon() const { return map_type == MAP_INSTANCE; }
    bool Instanceable() const { return map_type == MAP_INSTANCE || map_type == MAP_RAID || map_type == MAP_BATTLEGROUND || map_type == MAP_ARENA; }
    bool IsRaid() const { return map_type == MAP_RAID; }
    bool IsBattleGround() const { return map_type == MAP_BATTLEGROUND; }
    bool IsBattleArena() const { return map_type == MAP_ARENA; }
    bool IsBattleGroundOrArena() const { return map_type == MAP_BATTLEGROUND || map_type == MAP_ARENA; }

    bool IsMountAllowed() const
    {
        return !IsDungeon() ||
            MapID==209 || MapID==269 || MapID==309 ||       // TanarisInstance, CavernsOfTime, Zul'gurub
            MapID==509 || MapID==534 || MapID==560 ||       // AhnQiraj, HyjalPast, HillsbradPast
            MapID==568 || MapID==580 || MapID==595 ||       // ZulAman, Sunwell Plateau, Culling of Stratholme
            MapID==603 || MapID==615 || MapID==616;         // Ulduar, The Obsidian Sanctum, The Eye Of Eternity
    }

    bool IsContinent() const
    {
        return MapID == 0 || MapID == 1 || MapID == 530 || MapID == 571;
    }
};

struct MapDifficultyEntry
{
    //uint32      Id;                                       // 0
    uint32      MapId;                                      // 1
    uint32      Difficulty;                                 // 2 (for arenas: arena slot)
    //char*       areaTriggerText;                          // 3 text showed when transfer to map failed (missing requirements)
    uint32      resetTime;                                  // 4, in secs, 0 if no fixed reset time
    uint32      maxPlayers;                                 // 5, some heroic versions have 0 when expected same amount as in normal version
    //char*       difficultyString;                         // 6
};

struct MovieEntry
{
    uint32      Id;                                         // 0 index
    //char*       filename;                                 // 1
    //uint32      unk1;                                     // 2 100 or 250
    //uint32      unk2;                                     // 3 4.0.0
};

#define MAX_OVERRIDE_SPELLS     10

struct OverrideSpellDataEntry
{
    uint32      Id;                                         // 0 index
    uint32      Spells[MAX_OVERRIDE_SPELLS];                // 1-10 spells
    //uint32      unk2;                                     // 11 possibly flag
    //uint32      unk3;                                     // 12
};

struct PvPDifficultyEntry
{
    //uint32      id;                                       // 0        m_ID
    uint32      mapId;                                      // 1
    uint32      bracketId;                                  // 2
    uint32      minLevel;                                   // 3
    uint32      maxLevel;                                   // 4
    uint32      difficulty;                                 // 5

    // helpers
    BattleGroundBracketId GetBracketId() const { return BattleGroundBracketId(bracketId); }
};

struct QuestFactionRewardEntry
{
    uint32      id;                                         // 0
    int32       rewardValue[10];                            // 1-10
};

struct QuestSortEntry
{
    uint32      id;                                         // 0        m_ID
    //char*       name;                                     // 1        m_SortName_lang
};

struct QuestXPLevel
{
    uint32      questLevel;                                 // 0
    uint32      xpIndex[9];                                 // 1-9
    //unk                                                   // 10
};

struct RandomPropertiesPointsEntry
{
    //uint32  Id;                                           // 0 hidden key
    uint32    itemLevel;                                    // 1
    uint32    EpicPropertiesPoints[5];                      // 2-6
    uint32    RarePropertiesPoints[5];                      // 7-11
    uint32    UncommonPropertiesPoints[5];                  // 12-16
};

struct ScalingStatDistributionEntry
{
    uint32  Id;                                             // 0
    int32   StatMod[10];                                    // 1-10
    uint32  Modifier[10];                                   // 11-20
    //uint32 unk1;                                          // 21
    uint32  MaxLevel;                                       // 22
};

struct ScalingStatValuesEntry
{
    uint32  Id;                                             // 0
    uint32  Level;                                          // 1
    uint32  dpsMod[6];                                      // 2-7 DPS mod for level
    uint32  spellBonus;                                     // 8 spell power for level
    uint32  ssdMultiplier[5];                               // 9-13 Multiplier for ScalingStatDistribution
    uint32  armorMod[4];                                    // 14-17 Armor for level
    uint32  armorMod2[4];                                   // 18-21 Armor for level
    //uint32 trash[24];                                     // 22-45
    //uint32 unk2;                                          // 46 unk, probably also Armor for level (flag 0x80000?)

    uint32  getssdMultiplier(uint32 mask) const
    {
        if (mask & 0x4001F)
        {
            if(mask & 0x00000001) return ssdMultiplier[1];
            if(mask & 0x00000002) return ssdMultiplier[2]; // 0 and 1 were duplicated
            if(mask & 0x00000004) return ssdMultiplier[3];
            if(mask & 0x00000008) return ssdMultiplier[0];
            if(mask & 0x00000010) return ssdMultiplier[4];
            if(mask & 0x00040000) return ssdMultiplier[2]; // 4.0.0
        }
        return 0;
    }

    uint32  getArmorMod(uint32 mask) const
    {
        if (mask & 0x00F001E0)
        {
            if(mask & 0x00000020) return armorMod[0];
            if(mask & 0x00000040) return armorMod[1];
            if(mask & 0x00000080) return armorMod[2];
            if(mask & 0x00000100) return armorMod[3];

            if(mask & 0x00100000) return armorMod2[0];      // cloth
            if(mask & 0x00200000) return armorMod2[1];      // leather
            if(mask & 0x00400000) return armorMod2[2];      // mail
            if(mask & 0x00800000) return armorMod2[3];      // plate
        }
        return 0;
    }

    uint32 getDPSMod(uint32 mask) const
    {
        if (mask & 0x7E00)
        {
            if(mask & 0x00000200) return dpsMod[0];
            if(mask & 0x00000400) return dpsMod[1];
            if(mask & 0x00000800) return dpsMod[2];
            if(mask & 0x00001000) return dpsMod[3];
            if(mask & 0x00002000) return dpsMod[4];
            if(mask & 0x00004000) return dpsMod[5];         // not used?
        }
        return 0;
    }

    uint32 getSpellBonus(uint32 mask) const
    {
        if (mask & 0x00008000)
            return spellBonus;
        return 0;
    }

    uint32 getFeralBonus(uint32 mask) const                 // removed in 3.2.x?
    {
        if (mask & 0x00010000)                              // not used?
            return 0;
        return 0;
    }
};

//struct SkillLineCategoryEntry{
//    uint32    id;                                         // 0      m_ID
//    char*     name;                                       // 1      m_name_lang
//    uint32    displayOrder;                               // 2      m_sortIndex
//};

//struct SkillRaceClassInfoEntry{
//    uint32    id;                                         // 0      m_ID
//    uint32    skillId;                                    // 1      m_skillID
//    uint32    raceMask;                                   // 2      m_raceMask
//    uint32    classMask;                                  // 3      m_classMask
//    uint32    flags;                                      // 4      m_flags
//    uint32    reqLevel;                                   // 5      m_minLevel
//    uint32    skillTierId;                                // 6      m_skillTierID
//    uint32    skillCostID;                                // 7      m_skillCostIndex
//};

//struct SkillTiersEntry{
//    uint32    id;                                         // 0      m_ID
//    uint32    skillValue[16];                             // 1-17   m_cost
//    uint32    maxSkillValue[16];                          // 18-32  m_valueMax
//};

struct SkillLineEntry
{
    uint32    id;                                           // 0        m_ID
    int32     categoryId;                                   // 1        m_categoryID
    //uint32    skillCostID;                                // 2        m_skillCostsID
    DBCString name;                                         // 3        m_displayName_lang
    //char*     description;                                // 4        m_description_lang
    uint32    spellIcon;                                    // 5        m_spellIconID
    //char*     alternateVerb;                              // 6        m_alternateVerb_lang
    uint32    canLink;                                      // 7        m_canLink (prof. with recipes)
};

struct SkillLineAbilityEntry
{
    uint32    id;                                           // 0        m_ID
    uint32    skillId;                                      // 1        m_skillLine
    uint32    spellId;                                      // 2        m_spell
    uint32    racemask;                                     // 3        m_raceMask
    uint32    classmask;                                    // 4        m_classMask
    //uint32    racemaskNot;                                // 5        m_excludeRace
    //uint32    classmaskNot;                               // 6        m_excludeClass
    uint32    req_skill_value;                              // 7        m_minSkillLineRank
    uint32    forward_spellid;                              // 8        m_supercededBySpell
    uint32    learnOnGetSkill;                              // 9        m_acquireMethod
    uint32    max_value;                                    // 10       m_trivialSkillLineRankHigh
    uint32    min_value;                                    // 11       m_trivialSkillLineRankLow
    //uint32                                                // 12
    //uint32                                                // 13       4.0.0
};

struct SoundEntriesEntry
{
    uint32    Id;                                           // 0        m_ID
    //uint32    Type;                                       // 1        m_soundType
    //char*     InternalName;                               // 2        m_name
    //char*     FileName[10];                               // 3-12     m_File[10]
    //uint32    Unk13[10];                                  // 13-22    m_Freq[10]
    //char*     Path;                                       // 23       m_DirectoryBase
                                                            // 24       m_volumeFloat
                                                            // 25       m_flags
                                                            // 26       m_minDistance
                                                            // 27       m_distanceCutoff
                                                            // 28       m_EAXDef
                                                            // 29       new in 3.1
    //unk                                                   // 30       4.0.0
    //unk                                                   // 31       4.0.0
    //unk                                                   // 32       4.0.0
    //unk                                                   // 33       4.0.0
};

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

// SpellAuraOptions.dbc
struct SpellAuraOptionsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    StackAmount;                                  // 51       m_cumulativeAura
    uint32    procChance;                                   // 38       m_procChance
    uint32    procCharges;                                  // 39       m_procCharges
    uint32    procFlags;                                    // 37       m_procTypeMask
};

// SpellAuraRestrictions.dbc
struct SpellAuraRestrictionsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    CasterAuraState;                              // 21       m_casterAuraState
    uint32    TargetAuraState;                              // 22       m_targetAuraState
    uint32    CasterAuraStateNot;                           // 23       m_excludeCasterAuraState
    uint32    TargetAuraStateNot;                           // 24       m_excludeTargetAuraState
    uint32    casterAuraSpell;                              // 25       m_casterAuraSpell
    uint32    targetAuraSpell;                              // 26       m_targetAuraSpell
    uint32    excludeCasterAuraSpell;                       // 27       m_excludeCasterAuraSpell
    uint32    excludeTargetAuraSpell;                       // 28       m_excludeTargetAuraSpell
};

// SpellCastingRequirements.dbc
struct SpellCastingRequirementsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    FacingCasterFlags;                            // 20       m_facingCasterFlags
    //uint32    MinFactionId;                               // 159      m_minFactionID not used
    //uint32    MinReputation;                              // 160      m_minReputation not used
    int32     AreaGroupId;                                  // 164      m_requiredAreaGroupId
    //uint32    RequiredAuraVision;                         // 161      m_requiredAuraVision not used
    uint32    RequiresSpellFocus;                           // 19       m_requiresSpellFocus
};

// SpellCategories.dbc
struct SpellCategoriesEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    Category;                                     // 1        m_category
    uint32    DmgClass;                                     // 153      m_defenseType
    uint32    Dispel;                                       // 2        m_dispelType
    uint32    Mechanic;                                     // 3        m_mechanic
    uint32    PreventionType;                               // 154      m_preventionType
    uint32    StartRecoveryCategory;                        // 145      m_startRecoveryCategory
};

// SpellClassOptions.dbc
struct SpellClassOptionsEntry
{
    //uint32    Id;                                           // 0        m_ID
    //uint32    modalNextSpell;                             // 50       m_modalNextSpell not used
    uint64    SpellFamilyFlags;                             // 149-150  m_spellClassMask NOTE: size is 12 bytes!!!
    uint32    SpellFamilyFlags2;                            // 151      addition to m_spellClassMask
    uint32    SpellFamilyName;                              // 148      m_spellClassSet
    //char*   Description;                                  // 6 4.0.0
};

// SpellCooldowns.dbc
struct SpellCooldownsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    CategoryRecoveryTime;                         // 31       m_categoryRecoveryTime
    uint32    RecoveryTime;                                 // 30       m_recoveryTime
    uint32    StartRecoveryTime;                            // 146      m_startRecoveryTime
};

// SpellEffect.dbc
struct SpellEffectEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    Effect;                                       // 73-75    m_effect
    float     EffectMultipleValue;                          // 106-108  m_effectAmplitude
    uint32    EffectApplyAuraName;                          // 100-102  m_effectAura
    uint32    EffectAmplitude;                              // 103-105  m_effectAuraPeriod
    int32     EffectBasePoints;                             // 82-84    m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    //float   unk_320_4;                                    // 169-171  3.2.0
    float     DmgMultiplier;                                // 156-158  m_effectChainAmplitude
    uint32    EffectChainTarget;                            // 109-111  m_effectChainTargets
    int32     EffectDieSides;                               // 76-78    m_effectDieSides
    uint32    EffectItemType;                               // 112-114  m_effectItemType
    uint32    EffectMechanic;                               // 85-87    m_effectMechanic
    int32     EffectMiscValue;                              // 115-117  m_effectMiscValue
    int32     EffectMiscValueB;                             // 118-120  m_effectMiscValueB
    float     EffectPointsPerComboPoint;                    // 124-126  m_effectPointsPerCombo
    uint32    EffectRadiusIndex;                            // 94-96    m_effectRadiusIndex - spellradius.dbc
    //uint32   EffectRadiusMaxIndex;                        // 97-99    4.0.0
    float     EffectRealPointsPerLevel;                     // 79-81    m_effectRealPointsPerLevel
    uint32    EffectSpellClassMaskA[3];                     // 127-129  m_effectSpellClassMaskA, effect 0
    uint32    EffectTriggerSpell;                           // 121-123  m_effectTriggerSpell
    uint32    EffectImplicitTargetA;                        // 88-90    m_implicitTargetA
    uint32    EffectImplicitTargetB;                        // 91-93    m_implicitTargetB
    uint32    EffectSpellId;                                // new 4.0.0
    uint32    EffectIndex;                                  // new 4.0.0
};

// SpellEquippedItems.dbc
struct SpellEquippedItemsEntry
{
    //uint32    Id;                                           // 0        m_ID
    int32     EquippedItemClass;                            // 70       m_equippedItemClass (value)
    int32     EquippedItemInventoryTypeMask;                // 72       m_equippedItemInvTypes (mask)
    int32     EquippedItemSubClassMask;                     // 71       m_equippedItemSubclass (mask)
};

// SpellInterrupts.dbc
struct SpellInterruptsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    AuraInterruptFlags;                           // 33       m_auraInterruptFlags
    //uint32                                                // 34       4.0.0
    uint32    ChannelInterruptFlags;                        // 35       m_channelInterruptFlags
    //uint32                                                // 36       4.0.0
    uint32    InterruptFlags;                               // 32       m_interruptFlags
};

// SpellLevels.dbc
struct SpellLevelsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    baseLevel;                                    // 41       m_baseLevel
    uint32    maxLevel;                                     // 40       m_maxLevel
    uint32    spellLevel;                                   // 42       m_spellLevel
};

// SpellPower.dbc
struct SpellPowerEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    manaCost;                                     // 45       m_manaCost
    uint32    manaCostPerlevel;                             // 46       m_manaCostPerLevel
    uint32    ManaCostPercentage;                           // 144      m_manaCostPct
    uint32    manaPerSecond;                                // 47       m_manaPerSecond
    //uint32  PowerDisplayId;                               // 168      m_powerDisplayID - id from PowerDisplay.dbc, new in 3.1
    //uint32  unk1;                                         // 6        4.0.0
};

// SpellReagents.dbc
struct SpellReagentsEntry
{
    //uint32    Id;                                           // 0        m_ID
    int32     Reagent[MAX_SPELL_REAGENTS];                  // 54-61    m_reagent
    uint32    ReagentCount[MAX_SPELL_REAGENTS];             // 62-69    m_reagentCount
};

// SpellScaling.dbc
struct SpellScalingEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    castTimeMin;                                  // 1
    uint32    castTimeMax;                                  // 2
    uint32    castScalingMaxLevel;                          // 3
    uint32    playerClass;                                  // 4        (index * 100) + charLevel => gtSpellScaling.dbc
    float     coefMultiplier[3];                                    // 5-7
    float     coefRandomMultiplier[3];                                    // 8-10
    float     coefUnknow[3];                                    // 11-13
    float     unkMult;                                      // 14        some coefficient, mostly 1.0f
    uint32    unkLevel;                                     // 15        some level
};

// SpellShapeshift.dbc
struct SpellShapeshiftEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    Stances;                                      // 13       m_shapeshiftMask
    // uint32 unk_320_2;                                    // 14       3.2.0
    uint32    StancesNot;                                   // 15       m_shapeshiftExclude
    // uint32 unk_320_3;                                    // 16       3.2.0
    // uint32    StanceBarOrder;                            // 155      m_stanceBarOrder not used
};

// SpellTargetRestrictions.dbc
struct SpellTargetRestrictionsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    MaxAffectedTargets;                           // 152      m_maxTargets
    uint32    MaxTargetLevel;                               // 147      m_maxTargetLevel
    uint32    TargetCreatureType;                           // 18       m_targetCreatureType
    uint32    Targets;                                      // 17       m_targets
};

// SpellTotems.dbc
struct SpellTotemsEntry
{
    //uint32    Id;                                           // 0        m_ID
    uint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];    // 162-163  m_requiredTotemCategoryID
    uint32    Totem[MAX_SPELL_TOTEMS];                      // 52-53    m_totem
};

// Spell.dbc
struct MANGOS_DLL_SPEC SpellEntry
{
    uint32    Id;                                           // 0        m_ID
    uint32    Attributes;                                   // 1        m_attribute
    uint32    AttributesEx;                                 // 2        m_attributesEx
    uint32    AttributesEx2;                                // 3        m_attributesExB
    uint32    AttributesEx3;                                // 4        m_attributesExC
    uint32    AttributesEx4;                                // 5        m_attributesExD
    uint32    AttributesEx5;                                // 6        m_attributesExE
    uint32    AttributesEx6;                                // 7        m_attributesExF
    uint32    AttributesEx7;                                // 8        m_attributesExG (0x20 - totems, 0x4 - paladin auras, etc...)
    // uint32 someFlags;                                    // 9        4.0.0
    // uint32 unk_400_1;                                    // 10       4.0.0
    uint32    CastingTimeIndex;                             // 11       m_castingTimeIndex
    uint32    DurationIndex;                                // 12       m_durationIndex
    uint32    powerType;                                    // 13       m_powerType
    uint32    rangeIndex;                                   // 14       m_rangeIndex
    float     speed;                                        // 15       m_speed
    uint32    SpellVisual[2];                               // 16-17    m_spellVisualID
    uint32    SpellIconID;                                  // 18       m_spellIconID
    uint32    activeIconID;                                 // 19       m_activeIconID
    DBCString SpellName;                                    // 20       m_name_lang
    DBCString Rank;                                         // 21       m_nameSubtext_lang
    //DBCString Description;                                // 22       m_description_lang not used
    //DBCString ToolTip;                                    // 23       m_auraDescription_lang not used
    uint32    SchoolMask;                                   // 24       m_schoolMask
    uint32    runeCostID;                                   // 25       m_runeCostID
    //uint32    spellMissileID;                             // 26       m_spellMissileID not used
    //uint32  spellDescriptionVariableID;                   // 27       m_spellDescriptionVariableID, 3.2.0
    uint32  SpellDifficultyId;                              // 28       m_spellDifficultyID - id from SpellDifficulty.dbc
    //float unk_f1;                                         // 29
    uint32 SpellScalingId;                                  // 30       SpellScaling.dbc
    uint32 SpellAuraOptionsId;                              // 31       SpellAuraOptions.dbc
    uint32 SpellAuraRestrictionsId;                         // 32       SpellAuraRestrictions.dbc
    uint32 SpellCastingRequirementsId;                      // 33       SpellCastingRequirements.dbc
    uint32 SpellCategoriesId;                               // 34       SpellCategories.dbc
    uint32 SpellClassOptionsId;                             // 35       SpellClassOptions.dbc
    uint32 SpellCooldownsId;                                // 36       SpellCooldowns.dbc
    //uint32 unkIndex7;                                     // 37       all zeros...
    uint32 SpellEquippedItemsId;                            // 38       SpellEquippedItems.dbc
    uint32 SpellInterruptsId;                               // 39       SpellInterrupts.dbc
    uint32 SpellLevelsId;                                   // 40       SpellLevels.dbc
    uint32 SpellPowerId;                                    // 41       SpellPower.dbc
    uint32 SpellReagentsId;                                 // 42       SpellReagents.dbc
    uint32 SpellShapeshiftId;                               // 43       SpellShapeshift.dbc
    uint32 SpellTargetRestrictionsId;                       // 44       SpellTargetRestrictions.dbc
    uint32 SpellTotemsId;                                   // 45       SpellTotems.dbc
    //uint32 ResearchProject;                               // 46       ResearchProject.dbc

    bool IsFitToFamilyMask(uint64 familyFlags, uint32 familyFlags2 = 0) const
    {
        const SpellClassOptionsEntry* class_opt = GetSpellClassOptions();
        return class_opt && ((class_opt->SpellFamilyFlags & familyFlags) || (class_opt->SpellFamilyFlags2 & familyFlags2));
    }

    bool IsFitToFamily(SpellFamily family, uint64 familyFlags, uint32 familyFlags2 = 0) const
    {
        const SpellClassOptionsEntry* class_opt = GetSpellClassOptions();
        return class_opt && SpellFamily(class_opt->SpellFamilyName) == family
            && ((class_opt->SpellFamilyFlags & familyFlags) || (class_opt->SpellFamilyFlags2 & familyFlags2));
    }

    // helpers
    int32 CalculateSimpleValue(SpellEffectIndex eff) const;
    uint32 const* GetEffectSpellClassMask(SpellEffectIndex eff) const;

    // struct access functions
    SpellAuraOptionsEntry const* GetSpellAuraOptions() const;
    SpellAuraRestrictionsEntry const* GetSpellAuraRestrictions() const;
    SpellCastingRequirementsEntry const* GetSpellCastingRequirements() const;
    SpellCategoriesEntry const* GetSpellCategories() const;
    SpellClassOptionsEntry const* GetSpellClassOptions() const;
    SpellCooldownsEntry const* GetSpellCooldowns() const;
    SpellEffectEntry const* GetSpellEffect(SpellEffectIndex eff) const;
    SpellEquippedItemsEntry const* GetSpellEquippedItems() const;
    SpellInterruptsEntry const* GetSpellInterrupts() const;
    SpellLevelsEntry const* GetSpellLevels() const;
    SpellPowerEntry const* GetSpellPower() const;
    SpellReagentsEntry const* GetSpellReagents() const;
    SpellScalingEntry const* GetSpellScaling() const;
    SpellShapeshiftEntry const* GetSpellShapeshift() const;
    SpellTargetRestrictionsEntry const* GetSpellTargetRestrictions() const;
    SpellTotemsEntry const* GetSpellTotems() const;

    // single fields
    uint32 GetManaCost() const;
    uint32 GetPreventionType() const;
    uint32 GetCategory() const;
    uint32 GetStartRecoveryTime() const;
    uint32 GetMechanic() const;
    uint32 GetRecoveryTime() const;
    uint32 GetCategoryRecoveryTime() const;
    uint32 GetStartRecoveryCategory() const;
    uint32 GetSpellLevel() const;
    int32 GetEquippedItemClass() const;
    uint32 GetSpellFamilyName() const;
    uint32 GetDmgClass() const;
    uint32 GetDispel() const;
    uint32 GetMaxAffectedTargets() const;
    uint32 GetStackAmount() const;
    uint32 GetManaCostPercentage() const;
    uint32 GetProcCharges() const;
    uint32 GetProcChance() const;
    uint32 GetMaxLevel() const;
    uint32 GetTargetAuraState() const;
    uint32 GetManaPerSecond() const;
    uint32 GetRequiresSpellFocus() const;
    uint32 GetSpellEffectIdByIndex(SpellEffectIndex index) const;
    uint32 GetAuraInterruptFlags() const;
    uint32 GetEffectImplicitTargetAByIndex(SpellEffectIndex index) const;
    int32 GetAreaGroupId() const;
    uint32 GetFacingCasterFlags() const;
    uint32 GetBaseLevel() const;
    uint32 GetInterruptFlags() const;
    uint32 GetTargetCreatureType() const;
    int32 GetEffectMiscValue(SpellEffectIndex index) const;
    uint32 GetStances() const;
    uint32 GetStancesNot() const;
    uint32 GetProcFlags() const;
    uint32 GetChannelInterruptFlags() const;
    uint32 GetManaCostPerLevel() const;
    uint32 GetCasterAuraState() const;
    uint32 GetTargets() const;
    uint32 GetEffectApplyAuraNameByIndex(SpellEffectIndex index) const;

private:
    // prevent creating custom entries (copy data from original in fact)
    SpellEntry(SpellEntry const&);                          // DON'T must have implementation
};

struct SpellCastTimesEntry
{
    uint32    ID;                                           // 0
    int32     CastTime;                                     // 1
    //float     CastTimePerLevel;                           // 2 unsure / per skill?
    //int32     MinCastTime;                                // 3 unsure
};

struct SpellFocusObjectEntry
{
    uint32    ID;                                           // 0
    //char*     Name;                                       // 1
};

struct SpellRadiusEntry
{
    uint32    ID;                                           // 0
    float     Radius;                                       // 1
    float     Radius2;                                      // 2
};

struct SpellRangeEntry
{
    uint32    ID;                                           // 0
    float     minRange;                                     // 1
    float     minRangeFriendly;                             // 2
    float     maxRange;                                     // 3
    float     maxRangeFriendly;                             // 4
    //uint32     Flags;                                     // 5
    //char*     range1;                                     // 6
    //char*     range2;                                     // 7
};

struct SpellRuneCostEntry
{
    uint32  ID;                                             // 0
    uint32  RuneCost[3];                                    // 1-3 (0=blood, 1=frost, 2=unholy)
    uint32  runePowerGain;                                  // 4

    bool NoRuneCost() const { return RuneCost[0] == 0 && RuneCost[1] == 0 && RuneCost[2] == 0; }
    bool NoRunicPowerGain() const { return runePowerGain == 0; }
};

struct SpellShapeshiftFormEntry
{
    uint32 ID;                                              // 0
    //uint32 buttonPosition;                                // 1 unused
    //char*  Name;                                          // 2 unused
    uint32 flags1;                                          // 3
    int32  creatureType;                                    // 4 <=0 humanoid, other normal creature types
    //uint32 unk1;                                          // 5 unused, related to next field
    uint32 attackSpeed;                                     // 6
    uint32 modelID_A;                                       // 7 alliance modelid (0 means no model)
    uint32 modelID_H;                                       // 8 horde modelid (but only for one form)
    //uint32 unk3;                                          // 9 unused always 0
    //uint32 unk4;                                          // 10 unused always 0
    uint32 spellId[8];                                      // 11-18 spells which appear in the bar after shapeshifting
    //uint32 unk5;                                          // 19
    //uint32 unk6;                                          // 20
};

struct SpellDifficultyEntry
{
    uint32 ID;                                              // 0        m_ID
    uint32 spellId[MAX_DIFFICULTY];                         // 1-4      m_spellId[4]
};

struct SpellDurationEntry
{
    uint32    ID;
    int32     Duration[3];
};

struct SpellItemEnchantmentEntry
{
    uint32      ID;                                         // 0        m_ID
    //uint32      charges;                                  // 1        m_charges
    uint32      type[3];                                    // 2-4      m_effect[3]
    uint32      amount[3];                                  // 5-7      m_effectPointsMin[3]
    //uint32      amount2[3]                                // 8-10     m_effectPointsMax[3]
    uint32      spellid[3];                                 // 11-13    m_effectArg[3]
    DBCString description;                                  // 14       m_name_lang
    uint32      aura_id;                                    // 15       m_itemVisual
    uint32      slot;                                       // 16       m_flags
    uint32      GemID;                                      // 17       m_src_itemID
    uint32      EnchantmentCondition;                       // 18       m_condition_id
    //uint32      requiredSkill;                            // 19       m_requiredSkillID
    //uint32      requiredSkillValue;                       // 20       m_requiredSkillRank
                                                            // 21       new in 3.1
                                                            // 22       new in 3.1
};

struct SpellItemEnchantmentConditionEntry
{
    uint32  ID;                                             // 0        m_ID
    uint8   Color[5];                                       // 1-5      m_lt_operandType[5]
    //uint32  LT_Operand[5];                                // 6-10     m_lt_operand[5]
    uint8   Comparator[5];                                  // 11-15    m_operator[5]
    uint8   CompareColor[5];                                // 15-20    m_rt_operandType[5]
    uint32  Value[5];                                       // 21-25    m_rt_operand[5]
    //uint8   Logic[5]                                      // 25-30    m_logic[5]
};

/*struct StableSlotPricesEntry                              // removed in 4.0.0.12479
{
    uint32 Slot;
    uint32 Price;
};*/

struct SummonPropertiesEntry
{
    uint32  Id;                                             // 0
    uint32  Group;                                          // 1, enum SummonPropGroup
    uint32  FactionId;                                      // 2,                        14 rows > 0
    uint32  Title;                                          // 3, enum UnitNameSummonTitle
    uint32  Slot;                                           // 4, if title = UNITNAME_SUMMON_TITLE_TOTEM, its actual slot (0-6).
                                                            //    if title = UNITNAME_SUMMON_TITLE_COMPANION, slot=6 -> defensive guardian, in other cases criter/minipet
                                                            //    Slot may have other uses, selection of pet type in some cases?
    uint32  Flags;                                          // 5, enum SummonPropFlags
};

#define MAX_TALENT_RANK 5
#define MAX_PET_TALENT_RANK 3                               // use in calculations, expected <= MAX_TALENT_RANK

struct TalentEntry
{
    uint32    TalentID;                                     // 0
    uint32    TalentTab;                                    // 1 index in TalentTab.dbc (TalentTabEntry)
    uint32    Row;                                          // 2
    uint32    Col;                                          // 3
    uint32    RankID[MAX_TALENT_RANK];                      // 4-8
    uint32    DependsOn;                                    // 9 index in Talent.dbc (TalentEntry)
                                                            // 10-11 not used
    uint32    DependsOnRank;                                // 12
                                                            // 13-14 not used
    //uint32  needAddInSpellBook;                           // 15  also need disable higest ranks on reset talent tree
    //uint32  unk2;                                         // 16, all 0
    //uint64  allowForPet;                                  // 17 its a 64 bit mask for pet 1<<m_categoryEnumID in CreatureFamily.dbc
};

struct TalentTabEntry
{
    uint32  TalentTabID;                                    // 0
    //char* name;                                           // 1, unused
    //unit32  spellicon;                                    // 2
    uint32  ClassMask;                                      // 3
    uint32  petTalentMask;                                  // 4
    uint32  tabpage;                                        // 5
    //char* internalname;                                   // 6
    //char* description;                                    // 7
    //uint32 rolesMask;                                     // 8 4.0.0
    //uint32 spellIds[2];                                   // 9-10 passive mastery bonus spells?
};

struct TalentTreePrimarySpellsEntry
{
    uint32 Id;                                              // 0
    uint32 TalentTabID;                                     // 1
    uint32 SpellID;                                         // 2
    //uint32 unk1                                           // 3
};

struct TaxiNodesEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    map_id;                                       // 1        m_ContinentID
    float     x;                                            // 2        m_x
    float     y;                                            // 3        m_y
    float     z;                                            // 4        m_z
    DBCString name;                                         // 5        m_Name_lang
    uint32    MountCreatureID[2];                           // 6-7      m_MountCreatureID[2]
};

struct TaxiPathEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    from;                                         // 1        m_FromTaxiNode
    uint32    to;                                           // 2        m_ToTaxiNode
    uint32    price;                                        // 3        m_Cost
};

struct TaxiPathNodeEntry
{
                                                            // 0        m_ID
    uint32    path;                                         // 1        m_PathID
    uint32    index;                                        // 2        m_NodeIndex
    uint32    mapid;                                        // 3        m_ContinentID
    float     x;                                            // 4        m_LocX
    float     y;                                            // 5        m_LocY
    float     z;                                            // 6        m_LocZ
    uint32    actionFlag;                                   // 7        m_flags
    uint32    delay;                                        // 8        m_delay
    uint32    arrivalEventID;                               // 9        m_arrivalEventID
    uint32    departureEventID;                             // 10       m_departureEventID
};

//struct TeamContributionPoints
//{
//    //uint32    Entry;                                      // 0
//    float     Value;                                        // 1 (???)
//};

struct TotemCategoryEntry
{
    uint32    ID;                                           // 0
    //char*   name;                                         // 1
    uint32    categoryType;                                 // 2 (one for specialization)
    uint32    categoryMask;                                 // 3 (compatibility mask for same type: different for totems, compatible from high to low for rods)
};

#define MAX_VEHICLE_SEAT 8

struct VehicleEntry
{
    uint32  m_ID;                                           // 0
    uint32  m_flags;                                        // 1
    float   m_turnSpeed;                                    // 2
    float   m_pitchSpeed;                                   // 3
    float   m_pitchMin;                                     // 4
    float   m_pitchMax;                                     // 5
    uint32  m_seatID[MAX_VEHICLE_SEAT];                     // 6-13
    float   m_mouseLookOffsetPitch;                         // 14
    float   m_cameraFadeDistScalarMin;                      // 15
    float   m_cameraFadeDistScalarMax;                      // 16
    float   m_cameraPitchOffset;                            // 17
    //int     m_powerType[3];                               //       removed in 3.1
    //int     m_powerToken[3];                              //       removed in 3.1
    float   m_facingLimitRight;                             // 18
    float   m_facingLimitLeft;                              // 19
    float   m_msslTrgtTurnLingering;                        // 20
    float   m_msslTrgtPitchLingering;                       // 21
    float   m_msslTrgtMouseLingering;                       // 22
    float   m_msslTrgtEndOpacity;                           // 23
    float   m_msslTrgtArcSpeed;                             // 24
    float   m_msslTrgtArcRepeat;                            // 25
    float   m_msslTrgtArcWidth;                             // 26
    float   m_msslTrgtImpactRadius[2];                      // 27-28
    DBCString m_msslTrgtArcTexture;                         // 29
    DBCString m_msslTrgtImpactTexture;                      // 30
    DBCString m_msslTrgtImpactModel[2];                     // 31-32
    float   m_cameraYawOffset;                              // 33
    uint32  m_uiLocomotionType;                             // 34
    float   m_msslTrgtImpactTexRadius;                      // 35
    uint32  m_uiSeatIndicatorType;                          // 36
                                                            // 37, new in 3.1 - powerType
                                                            // 38, new in 3.1
                                                            // 39, new in 3.1
};

struct VehicleSeatEntry
{
    uint32  m_ID;                                           // 0
    uint32  m_flags;                                        // 1
    int32   m_attachmentID;                                 // 2
    float   m_attachmentOffsetX;                            // 3
    float   m_attachmentOffsetY;                            // 4
    float   m_attachmentOffsetZ;                            // 5
    float   m_enterPreDelay;                                // 6
    float   m_enterSpeed;                                   // 7
    float   m_enterGravity;                                 // 8
    float   m_enterMinDuration;                             // 9
    float   m_enterMaxDuration;                             // 10
    float   m_enterMinArcHeight;                            // 11
    float   m_enterMaxArcHeight;                            // 12
    int32   m_enterAnimStart;                               // 13
    int32   m_enterAnimLoop;                                // 14
    int32   m_rideAnimStart;                                // 15
    int32   m_rideAnimLoop;                                 // 16
    int32   m_rideUpperAnimStart;                           // 17
    int32   m_rideUpperAnimLoop;                            // 18
    float   m_exitPreDelay;                                 // 19
    float   m_exitSpeed;                                    // 20
    float   m_exitGravity;                                  // 21
    float   m_exitMinDuration;                              // 22
    float   m_exitMaxDuration;                              // 23
    float   m_exitMinArcHeight;                             // 24
    float   m_exitMaxArcHeight;                             // 25
    int32   m_exitAnimStart;                                // 26
    int32   m_exitAnimLoop;                                 // 27
    int32   m_exitAnimEnd;                                  // 28
    float   m_passengerYaw;                                 // 29
    float   m_passengerPitch;                               // 30
    float   m_passengerRoll;                                // 31
    int32   m_passengerAttachmentID;                        // 32
    int32   m_vehicleEnterAnim;                             // 33
    int32   m_vehicleExitAnim;                              // 34
    int32   m_vehicleRideAnimLoop;                          // 35
    int32   m_vehicleEnterAnimBone;                         // 36
    int32   m_vehicleExitAnimBone;                          // 37
    int32   m_vehicleRideAnimLoopBone;                      // 38
    float   m_vehicleEnterAnimDelay;                        // 39
    float   m_vehicleExitAnimDelay;                         // 40
    uint32  m_vehicleAbilityDisplay;                        // 41
    uint32  m_enterUISoundID;                               // 42
    uint32  m_exitUISoundID;                                // 43
    int32   m_uiSkin;                                       // 44
    uint32  m_flagsB;                                       // 45
                                                            // 46-57 added in 3.1, floats mostly
    //uint32 unk[6];                                        // 58-63
    //uint32 unk2;                                          // 64 4.0.0
    //uint32 unk3;                                          // 65 4.0.1
};

struct WMOAreaTableEntry
{
    uint32 Id;                                              // 0 index
    int32 rootId;                                           // 1 used in root WMO
    int32 adtId;                                            // 2 used in adt file
    int32 groupId;                                          // 3 used in group WMO
    //uint32 field4;                                        // 4
    //uint32 field5;                                        // 5
    //uint32 field6;                                        // 6
    //uint32 field7;                                        // 7
    //uint32 field8;                                        // 8
    uint32 Flags;                                           // 9 used for indoor/outdoor determination
    uint32 areaId;                                          // 10 link to AreaTableEntry.ID
    //char *Name;                                           // 11
    //uint32 field12;                                       // 12
    //uint32 field13;                                       // 13
    //uint32 field14;                                       // 14
};

struct WorldMapAreaEntry
{
    //uint32  ID;                                           // 0
    uint32  map_id;                                         // 1
    uint32  area_id;                                        // 2 index (continent 0 areas ignored)
    //char* internal_name                                   // 3
    float   y1;                                             // 4
    float   y2;                                             // 5
    float   x1;                                             // 6
    float   x2;                                             // 7
    int32   virtual_map_id;                                 // 8 -1 (map_id have correct map) other: virtual map where zone show (map_id - where zone in fact internally)
    // int32   dungeonMap_id;                               // 9 pointer to DungeonMap.dbc (owerride x1,x2,y1,y2 coordinates)
    // uint32  someMapID;                                   // 10
    //uint32   unk1;                                        // 11 4.0.0
};

#define MAX_WORLD_MAP_OVERLAY_AREA_IDX 4

struct WorldMapOverlayEntry
{
    uint32    ID;                                           // 0
    //uint32    worldMapAreaId;                             // 1 idx in WorldMapArea.dbc
    uint32    areatableID[MAX_WORLD_MAP_OVERLAY_AREA_IDX];  // 2-5
    //char* internal_name                                   // 6
                                                            // 7-14 some ints
};

struct WorldSafeLocsEntry
{
    uint32    ID;                                           // 0
    uint32    map_id;                                       // 1
    float     x;                                            // 2
    float     y;                                            // 3
    float     z;                                            // 4
    //char*   name;                                         // 5 name, unused
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

typedef std::set<uint32> SpellCategorySet;
typedef std::map<uint32,SpellCategorySet > SpellCategoryStore;
typedef std::set<uint32> PetFamilySpellsSet;
typedef std::map<uint32,PetFamilySpellsSet > PetFamilySpellsStore;

// Structures not used for casting to loaded DBC data and not required then packing
struct MapDifficulty
{
    MapDifficulty() : resetTime(0), maxPlayers(0) {}
    MapDifficulty(uint32 _resetTime, uint32 _maxPlayers) : resetTime(_resetTime), maxPlayers(_maxPlayers) {}

    uint32 resetTime;                                       // in secs, 0 if no fixed reset time
    uint32 maxPlayers;                                      // some heroic dungeons have 0 when expect same value as in normal dificulty case
};

struct TalentSpellPos
{
    TalentSpellPos() : talent_id(0), rank(0) {}
    TalentSpellPos(uint16 _talent_id, uint8 _rank) : talent_id(_talent_id), rank(_rank) {}

    uint16 talent_id;
    uint8  rank;
};

typedef std::map<uint32,TalentSpellPos> TalentSpellPosMap;

struct SpellEffect
{
    SpellEffect()
    {
        effects[0] = NULL;
        effects[1] = NULL;
        effects[2] = NULL;
    }
    SpellEffectEntry const* effects[3];
};

typedef std::map<uint32, SpellEffect> SpellEffectMap;

struct TaxiPathBySourceAndDestination
{
    TaxiPathBySourceAndDestination() : ID(0),price(0) {}
    TaxiPathBySourceAndDestination(uint32 _id,uint32 _price) : ID(_id),price(_price) {}

    uint32    ID;
    uint32    price;
};
typedef std::map<uint32,TaxiPathBySourceAndDestination> TaxiPathSetForSource;
typedef std::map<uint32,TaxiPathSetForSource> TaxiPathSetBySource;

struct TaxiPathNodePtr
{
    TaxiPathNodePtr() : i_ptr(NULL) {}
    TaxiPathNodePtr(TaxiPathNodeEntry const* ptr) : i_ptr(ptr) {}

    TaxiPathNodeEntry const* i_ptr;

    operator TaxiPathNodeEntry const& () const { return *i_ptr; }
};

typedef Path<TaxiPathNodePtr,TaxiPathNodeEntry const> TaxiPathNodeList;
typedef std::vector<TaxiPathNodeList> TaxiPathNodesByPath;

#define TaxiMaskSize 14
typedef uint32 TaxiMask[TaxiMaskSize];
#endif
