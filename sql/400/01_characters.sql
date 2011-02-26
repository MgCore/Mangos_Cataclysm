alter table `characters`
    add column `power8` int(10) UNSIGNED DEFAULT '0' NOT NULL after `power7`,
    add column `power9` int(10) UNSIGNED DEFAULT '0' NOT NULL after `power8`,
	add column `achievementPoints` SMALLINT(5) UNSIGNED NOT NULL DEFAULT 0 AFTER `knownTitles`;
	add column `talentSpec` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `achievementPoints`;

alter table `character_stats`
    add column `maxpower8` int(10) UNSIGNED DEFAULT '0' NOT NULL after `maxpower7`,
    add column `maxpower9` int(10) UNSIGNED DEFAULT '0' NOT NULL after `maxpower8`;

DROP TABLE IF EXISTS `character_currency`;
CREATE TABLE `character_currency` (
  `guid` INT(11) UNSIGNED NOT NULL,
  `currency` SMALLINT(5) UNSIGNED NOT NULL,
  `count` SMALLINT(5) UNSIGNED NOT NULL,
  `thisweek` SMALLINT(5) UNSIGNED NOT NULL,
  PRIMARY KEY (`guid`,`currency`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
