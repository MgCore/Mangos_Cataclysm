ALTER TABLE `item_template`
	DROP COLUMN `StatsCount`,
	DROP COLUMN `dmg_min1`,
	DROP COLUMN `dmg_max1`,
	DROP COLUMN `dmg_min2`,
	DROP COLUMN `dmg_max2`,
	DROP COLUMN `dmg_type2`,
	DROP COLUMN `holy_res`,
	DROP COLUMN `fire_res`,
	DROP COLUMN `nature_res`,
	DROP COLUMN `frost_res`,
	DROP COLUMN `shadow_res`,
	DROP COLUMN `arcane_res`,
	DROP COLUMN `ammo_type`,
	DROP COLUMN `armor`,
	DROP COLUMN `block`,
	CHANGE COLUMN `dmg_type1` `damageType` tinyint(3) UNSIGNED NOT NULL DEFAULT '0';