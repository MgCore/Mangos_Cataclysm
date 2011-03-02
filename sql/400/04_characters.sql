-- Table structure for table `character_branchspec`
--

DROP TABLE IF EXISTS `character_branchspec`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS `character_branchspec` (
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `spec` int(11) unsigned NOT NULL DEFAULT '0',
  `branchSpec` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`spec`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
