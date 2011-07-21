-- MySQL dump 10.11
--
-- Host: localhost    Database: dartdem2_empty
-- ------------------------------------------------------
-- Server version	5.0.92-community-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `SchoolCalendar`
--

DROP TABLE IF EXISTS `SchoolCalendar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SchoolCalendar` (
  `CalendarID` int(11) NOT NULL auto_increment,
  `SiteID` varchar(254) NOT NULL default '',
  `SchoolYear` int(11) NOT NULL default '2007',
  `Description` varchar(255) default 'School Calendar 2007-2008',
  `ApprovedBy` varchar(255) default 'Jim Hickerson, Superintendent',
  `StartDate` date default '2007-08-01',
  `EndDate` date default '2008-06-30',
  PRIMARY KEY  (`CalendarID`),
  UNIQUE KEY `SiteID` (`SiteID`,`SchoolYear`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SchoolCalendar`
--

LOCK TABLES `SchoolCalendar` WRITE;
/*!40000 ALTER TABLE `SchoolCalendar` DISABLE KEYS */;
/*!40000 ALTER TABLE `SchoolCalendar` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `alert_toggles`
--

DROP TABLE IF EXISTS `alert_toggles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alert_toggles` (
  `subject` varchar(254) NOT NULL default '',
  `lvl` varchar(254) NOT NULL default '',
  `days` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `alert_toggles`
--

LOCK TABLES `alert_toggles` WRITE;
/*!40000 ALTER TABLE `alert_toggles` DISABLE KEYS */;
/*!40000 ALTER TABLE `alert_toggles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `AttendanceCodeGroups`
--

DROP TABLE IF EXISTS `AttendanceCodeGroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `AttendanceCodeGroups` (
  `CodeID` int(11) NOT NULL default '0',
  `GroupID` int(11) NOT NULL default '0',
  PRIMARY KEY  (`CodeID`,`GroupID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `AttendanceCodeGroups`
--

LOCK TABLES `AttendanceCodeGroups` WRITE;
/*!40000 ALTER TABLE `AttendanceCodeGroups` DISABLE KEYS */;
INSERT INTO `AttendanceCodeGroups` (`CodeID`, `GroupID`) VALUES (0,4),(1,0),(2,1),(2,4),(3,1),(3,4),(4,4),(5,0),(6,0),(7,0),(8,4),(9,0),(9,3),(10,2),(10,4),(11,0);
/*!40000 ALTER TABLE `AttendanceCodeGroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `attendancecodes`
--

DROP TABLE IF EXISTS `attendancecodes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `attendancecodes` (
  `CodeID` int(11) NOT NULL default '0',
  `Code` varchar(5) NOT NULL default '',
  `Description` varchar(255) default NULL,
  `Color` varchar(6) default NULL,
  PRIMARY KEY  (`CodeID`),
  UNIQUE KEY `Code` (`Code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `attendancecodes`
--

LOCK TABLES `attendancecodes` WRITE;
/*!40000 ALTER TABLE `attendancecodes` DISABLE KEYS */;
INSERT INTO `attendancecodes` (`CodeID`, `Code`, `Description`, `Color`) VALUES (0,'P','Present',NULL),(1,'A','Absent','FF0000'),(2,'L','Late','FF0000'),(3,'E','Excused Tardy','FF0000'),(4,'T','Student Activity',NULL),(5,'H','Health Absence','FF0000'),(6,'X','Excused Absence','FF0000'),(7,'R','Subsistence Leave','FF0000'),(8,'W','Workstudy','FF0000'),(9,'S','Suspended','FF0000'),(10,'I','In-school Suspension','FF0000'),(11,'V','Vacation',''),(12,'--','No School Day','FF0000');
/*!40000 ALTER TABLE `attendancecodes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `attendanceevents`
--

DROP TABLE IF EXISTS `attendanceevents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `attendanceevents` (
  `StudentID` int(11) NOT NULL default '0',
  `SiteID` varchar(3) NOT NULL default '',
  `Date` date NOT NULL default '0000-00-00',
  `PeriodID` int(2) NOT NULL default '0',
  `CodeID` int(2) default NULL,
  PRIMARY KEY  (`StudentID`,`Date`,`PeriodID`),
  KEY `StudentID` (`StudentID`),
  KEY `AttendanceEvents_Date` (`Date`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `attendanceevents`
--

LOCK TABLES `attendanceevents` WRITE;
/*!40000 ALTER TABLE `attendanceevents` DISABLE KEYS */;
/*!40000 ALTER TABLE `attendanceevents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `attendancegroups`
--

DROP TABLE IF EXISTS `attendancegroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `attendancegroups` (
  `GroupID` int(11) NOT NULL default '0',
  `Description` varchar(255) default NULL,
  PRIMARY KEY  (`GroupID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `attendancegroups`
--

LOCK TABLES `attendancegroups` WRITE;
/*!40000 ALTER TABLE `attendancegroups` DISABLE KEYS */;
INSERT INTO `attendancegroups` (`GroupID`, `Description`) VALUES (0,'Absent'),(1,'Late'),(2,'ISS'),(3,'Suspended'),(4,'Present');
/*!40000 ALTER TABLE `attendancegroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `attendanceperiods`
--

DROP TABLE IF EXISTS `attendanceperiods`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `attendanceperiods` (
  `PeriodID` int(11) NOT NULL default '0',
  `Description` varchar(255) default NULL,
  PRIMARY KEY  (`PeriodID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `attendanceperiods`
--

LOCK TABLES `attendanceperiods` WRITE;
/*!40000 ALTER TABLE `attendanceperiods` DISABLE KEYS */;
INSERT INTO `attendanceperiods` (`PeriodID`, `Description`) VALUES (0,'AM'),(1,'PM');
/*!40000 ALTER TABLE `attendanceperiods` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bugs`
--

DROP TABLE IF EXISTS `bugs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bugs` (
  `id` int(11) NOT NULL auto_increment,
  `contact` varchar(254) NOT NULL default '',
  `problemDate` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `problem` text NOT NULL,
  `resolveDate` timestamp NOT NULL default '0000-00-00 00:00:00',
  `resolution` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bugs`
--

LOCK TABLES `bugs` WRITE;
/*!40000 ALTER TABLE `bugs` DISABLE KEYS */;
/*!40000 ALTER TABLE `bugs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `discipline`
--

DROP TABLE IF EXISTS `discipline`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `discipline` (
  `disciplineid` int(11) NOT NULL auto_increment,
  `studentid` int(11) NOT NULL default '0',
  `year` int(11) NOT NULL default '0',
  `kind` varchar(254) NOT NULL default '',
  `creation` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `cuser` int(11) NOT NULL default '0',
  `site` varchar(254) NOT NULL default '',
  `incidentdate` date NOT NULL default '0000-00-00',
  `nonweapon` varchar(254) NOT NULL default '',
  `victimno` int(11) NOT NULL default '0',
  `police` varchar(254) NOT NULL default '',
  `consequence` varchar(254) NOT NULL default '',
  `lengthdays` int(11) NOT NULL default '0',
  `dstatus` varchar(254) NOT NULL default '',
  `suspension` varchar(254) NOT NULL default '',
  `weapon` varchar(254) NOT NULL default '',
  `victimtype` varchar(254) NOT NULL default '',
  `startdate` date NOT NULL default '0000-00-00',
  `enddate` date NOT NULL default '0000-00-00',
  `guardian` text NOT NULL,
  `notes` text NOT NULL,
  `relateddisability` varchar(254) NOT NULL default '',
  `iepmeet` varchar(254) NOT NULL default '',
  `eduservice` varchar(254) NOT NULL default '',
  `meetdate` date NOT NULL default '0000-00-00',
  `foo` varchar(254) NOT NULL default '',
  `foo1` varchar(254) NOT NULL default '',
  `foo2` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`disciplineid`),
  KEY `studentid` (`studentid`,`year`,`kind`),
  KEY `discipline_incidentdate` (`incidentdate`),
  KEY `discipline_consequence` (`consequence`(5))
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `discipline`
--

LOCK TABLES `discipline` WRITE;
/*!40000 ALTER TABLE `discipline` DISABLE KEYS */;
/*!40000 ALTER TABLE `discipline` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gb_assignments`
--

DROP TABLE IF EXISTS `gb_assignments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gb_assignments` (
  `aid` int(11) NOT NULL auto_increment,
  `gid` int(11) NOT NULL,
  `ord` int(11) NOT NULL,
  `name` varchar(254) NOT NULL,
  `category` int(11) NOT NULL,
  PRIMARY KEY  (`aid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gb_assignments`
--

LOCK TABLES `gb_assignments` WRITE;
/*!40000 ALTER TABLE `gb_assignments` DISABLE KEYS */;
/*!40000 ALTER TABLE `gb_assignments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gb_assignstand`
--

DROP TABLE IF EXISTS `gb_assignstand`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gb_assignstand` (
  `aid` int(11) NOT NULL,
  `subject` varchar(254) NOT NULL,
  `level` varchar(254) NOT NULL,
  `std` varchar(254) NOT NULL,
  PRIMARY KEY  (`aid`,`subject`,`level`,`std`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gb_assignstand`
--

LOCK TABLES `gb_assignstand` WRITE;
/*!40000 ALTER TABLE `gb_assignstand` DISABLE KEYS */;
/*!40000 ALTER TABLE `gb_assignstand` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gb_categories`
--

DROP TABLE IF EXISTS `gb_categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gb_categories` (
  `cid` int(11) NOT NULL auto_increment,
  `userid` int(11) NOT NULL,
  `catname` varchar(254) NOT NULL,
  PRIMARY KEY  (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gb_categories`
--

LOCK TABLES `gb_categories` WRITE;
/*!40000 ALTER TABLE `gb_categories` DISABLE KEYS */;
/*!40000 ALTER TABLE `gb_categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gb_catwt`
--

DROP TABLE IF EXISTS `gb_catwt`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gb_catwt` (
  `cwid` int(11) NOT NULL auto_increment,
  `gid` int(11) NOT NULL,
  `cid` int(11) NOT NULL,
  `weight` float NOT NULL,
  PRIMARY KEY  (`cwid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gb_catwt`
--

LOCK TABLES `gb_catwt` WRITE;
/*!40000 ALTER TABLE `gb_catwt` DISABLE KEYS */;
/*!40000 ALTER TABLE `gb_catwt` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gb_main`
--

DROP TABLE IF EXISTS `gb_main`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gb_main` (
  `gid` int(11) NOT NULL auto_increment,
  `lid` int(11) NOT NULL,
  `name` varchar(254) NOT NULL,
  `weighted` int(11) NOT NULL,
  PRIMARY KEY  (`gid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gb_main`
--

LOCK TABLES `gb_main` WRITE;
/*!40000 ALTER TABLE `gb_main` DISABLE KEYS */;
/*!40000 ALTER TABLE `gb_main` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gb_scores`
--

DROP TABLE IF EXISTS `gb_scores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gb_scores` (
  `aid` int(11) NOT NULL,
  `sid` int(11) NOT NULL,
  `score` int(11) NOT NULL,
  PRIMARY KEY  (`aid`,`sid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gb_scores`
--

LOCK TABLES `gb_scores` WRITE;
/*!40000 ALTER TABLE `gb_scores` DISABLE KEYS */;
/*!40000 ALTER TABLE `gb_scores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gp`
--

DROP TABLE IF EXISTS `gp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gp` (
  `gpid` int(11) NOT NULL auto_increment,
  `gpname` varchar(254) NOT NULL,
  `electives` int(11) NOT NULL,
  `side` int(11) NOT NULL,
  PRIMARY KEY  (`gpid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gp`
--

LOCK TABLES `gp` WRITE;
/*!40000 ALTER TABLE `gp` DISABLE KEYS */;
/*!40000 ALTER TABLE `gp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gpelectives`
--

DROP TABLE IF EXISTS `gpelectives`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gpelectives` (
  `gpeid` int(11) NOT NULL auto_increment,
  `gpid` int(11) NOT NULL,
  `subject` varchar(254) NOT NULL,
  `level` varchar(254) NOT NULL,
  PRIMARY KEY  (`gpeid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gpelectives`
--

LOCK TABLES `gpelectives` WRITE;
/*!40000 ALTER TABLE `gpelectives` DISABLE KEYS */;
/*!40000 ALTER TABLE `gpelectives` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gpvalues`
--

DROP TABLE IF EXISTS `gpvalues`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gpvalues` (
  `gpvid` int(11) NOT NULL auto_increment,
  `gpid` int(11) NOT NULL,
  `kind` int(11) NOT NULL,
  `loc` int(11) NOT NULL,
  `side` int(11) NOT NULL,
  `title` varchar(254) NOT NULL,
  `subject` varchar(254) NOT NULL,
  `level` int(11) NOT NULL,
  PRIMARY KEY  (`gpvid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gpvalues`
--

LOCK TABLES `gpvalues` WRITE;
/*!40000 ALTER TABLE `gpvalues` DISABLE KEYS */;
/*!40000 ALTER TABLE `gpvalues` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `grades`
--

DROP TABLE IF EXISTS `grades`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `grades` (
  `gradeid` int(11) NOT NULL auto_increment,
  `studentid` int(11) NOT NULL default '0',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '0',
  `std` varchar(254) NOT NULL default '',
  `value` text NOT NULL,
  `num` int(11) NOT NULL default '0',
  `psid` varchar(254) NOT NULL default '',
  `storecode` varchar(254) NOT NULL default '',
  `igrp` varchar(254) NOT NULL default '',
  `achange` varchar(254) NOT NULL default '',
  `trans2010` varchar(254) NOT NULL,
  PRIMARY KEY  (`gradeid`),
  KEY `studentid` (`studentid`),
  KEY `level` (`level`),
  KEY `std` (`std`),
  KEY `subject` (`subject`),
  KEY `num` (`num`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grades`
--

LOCK TABLES `grades` WRITE;
/*!40000 ALTER TABLE `grades` DISABLE KEYS */;
/*!40000 ALTER TABLE `grades` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `grp_info`
--

DROP TABLE IF EXISTS `grp_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `grp_info` (
  `infoid` int(11) NOT NULL auto_increment,
  `tabid` int(11) NOT NULL,
  `ord` float NOT NULL,
  `kind` varchar(254) NOT NULL,
  `value` text NOT NULL,
  `width` int(11) NOT NULL,
  `height` int(11) NOT NULL,
  PRIMARY KEY  (`infoid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grp_info`
--

LOCK TABLES `grp_info` WRITE;
/*!40000 ALTER TABLE `grp_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `grp_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `grp_tab`
--

DROP TABLE IF EXISTS `grp_tab`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `grp_tab` (
  `tabid` int(11) NOT NULL auto_increment,
  `listid` int(11) NOT NULL,
  `tabname` varchar(254) NOT NULL,
  `ord` float NOT NULL,
  PRIMARY KEY  (`tabid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grp_tab`
--

LOCK TABLES `grp_tab` WRITE;
/*!40000 ALTER TABLE `grp_tab` DISABLE KEYS */;
/*!40000 ALTER TABLE `grp_tab` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gs`
--

DROP TABLE IF EXISTS `gs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gs` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(254) NOT NULL,
  `gradetype` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gs`
--

LOCK TABLES `gs` WRITE;
/*!40000 ALTER TABLE `gs` DISABLE KEYS */;
INSERT INTO `gs` (`id`, `name`, `gradetype`) VALUES (1,'Standards',1),(2,'BSD Secondary Scale',2),(3,'Average Upper Grades',2);
/*!40000 ALTER TABLE `gs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gs_grades`
--

DROP TABLE IF EXISTS `gs_grades`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gs_grades` (
  `id` int(11) NOT NULL auto_increment,
  `gsid` int(11) NOT NULL,
  `symbol` varchar(254) NOT NULL,
  `high` int(11) NOT NULL,
  `low` int(11) NOT NULL,
  `val` int(11) NOT NULL,
  `points` float NOT NULL,
  `ord` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=25 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gs_grades`
--

LOCK TABLES `gs_grades` WRITE;
/*!40000 ALTER TABLE `gs_grades` DISABLE KEYS */;
INSERT INTO `gs_grades` (`id`, `gsid`, `symbol`, `high`, `low`, `val`, `points`, `ord`) VALUES (1,1,'EMG',69,1,60,1,1),(2,1,'DEV',79,70,76,2,2),(3,1,'PRO',89,80,86,3,3),(4,1,'ADV',100,90,96,4,4),(5,2,'A+',100,97,100,4,1),(6,2,'A',96,93,96,4,2),(7,2,'A-',92,90,92,3.7,3),(8,2,'B+',89,87,89,3.3,4),(9,2,'B',86,83,86,3,5),(10,2,'B-',82,80,82,2.7,6),(11,2,'C+',79,77,79,2.3,7),(12,2,'C',76,73,76,2,8),(13,2,'C-',72,70,72,1.7,9),(14,2,'F',69,1,60,0,10),(15,3,'A+',100,97,100,4,1),(16,3,'A',96,93,96,4,2),(17,3,'A-',92,90,92,3.7,3),(18,3,'B+',89,87,89,3.3,4),(19,3,'B',86,83,86,3,5),(20,3,'B-',82,80,82,2.7,6),(21,3,'C+',79,77,79,2.3,7),(22,3,'C',76,73,76,2,8),(23,3,'C-',72,70,72,1.7,9),(24,3,'F',60,1,60,0,11);
/*!40000 ALTER TABLE `gs_grades` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gs_select`
--

DROP TABLE IF EXISTS `gs_select`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gs_select` (
  `id` int(11) NOT NULL auto_increment,
  `gsid` int(11) NOT NULL,
  `siteid` varchar(254) NOT NULL,
  `lowgrade` int(11) NOT NULL,
  `highgrade` int(11) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `siteid` (`siteid`,`lowgrade`,`highgrade`)
) ENGINE=MyISAM AUTO_INCREMENT=32 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gs_select`
--

LOCK TABLES `gs_select` WRITE;
/*!40000 ALTER TABLE `gs_select` DISABLE KEYS */;
INSERT INTO `gs_select` (`id`, `gsid`, `siteid`, `lowgrade`, `highgrade`) VALUES (1,1,'IBS',-2,6),(2,1,'IBS',7,13),(3,1,'HLS',-2,13),(4,1,'THS',-2,13),(5,3,'WPS',-2,13),(6,1,'ROS',-2,13),(7,1,'LES',-2,13),(8,1,'RFS',-2,13),(9,1,'HUS',-2,13),(10,1,'COS',-2,13),(11,1,'WCS',-2,13),(12,1,'VIS',-2,13),(13,2,'CLS',-2,13),(14,2,'RAS',-2,13),(15,1,'JZS',-2,13),(16,1,'SHS',-2,13);
/*!40000 ALTER TABLE `gs_select` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(11) NOT NULL auto_increment,
  `timestamp` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `ip` varchar(254) NOT NULL default '',
  `userID` int(254) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  `p1` varchar(254) NOT NULL default '',
  `p2` varchar(254) NOT NULL default '',
  `p3` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `history2`
--

DROP TABLE IF EXISTS `history2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history2` (
  `id` int(11) NOT NULL auto_increment,
  `type` varchar(254) NOT NULL default '',
  `userid` varchar(254) NOT NULL default '',
  `ip` varchar(254) NOT NULL default '',
  `value` varchar(254) NOT NULL default '',
  `subject` varchar(254) NOT NULL default '',
  `lvl` varchar(254) NOT NULL default '',
  `std` varchar(254) NOT NULL default '',
  `timestamp` int(11) default NULL,
  `studentID` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `timestamp` (`timestamp`),
  KEY `userid` (`userid`),
  KEY `studentID` (`studentID`),
  KEY `history2_type` (`type`(10)),
  KEY `history2_std` (`std`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history2`
--

LOCK TABLES `history2` WRITE;
/*!40000 ALTER TABLE `history2` DISABLE KEYS */;
/*!40000 ALTER TABLE `history2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hotlist`
--

DROP TABLE IF EXISTS `hotlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hotlist` (
  `grade` varchar(254) NOT NULL default '',
  `stage` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `neededmin` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hotlist`
--

LOCK TABLES `hotlist` WRITE;
/*!40000 ALTER TABLE `hotlist` DISABLE KEYS */;
/*!40000 ALTER TABLE `hotlist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `importgrp`
--

DROP TABLE IF EXISTS `importgrp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `importgrp` (
  `id` int(11) NOT NULL auto_increment,
  `timstamp` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `userid` int(11) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `importgrp`
--

LOCK TABLES `importgrp` WRITE;
/*!40000 ALTER TABLE `importgrp` DISABLE KEYS */;
/*!40000 ALTER TABLE `importgrp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `level`
--

DROP TABLE IF EXISTS `level`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `level` (
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '',
  `name` varchar(254) NOT NULL default '',
  `standardID` varchar(254) NOT NULL default '',
  `Identifier` varchar(254) NOT NULL default '',
  `numlevel` int(11) NOT NULL default '0',
  `weight` float NOT NULL default '0',
  KEY `subject` (`subject`),
  KEY `level` (`level`),
  KEY `numlevel` (`numlevel`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `level`
--

LOCK TABLES `level` WRITE;
/*!40000 ALTER TABLE `level` DISABLE KEYS */;
/*!40000 ALTER TABLE `level` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `line`
--

DROP TABLE IF EXISTS `line`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `line` (
  `grade` varchar(254) NOT NULL default '',
  `stage` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `value` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `line`
--

LOCK TABLES `line` WRITE;
/*!40000 ALTER TABLE `line` DISABLE KEYS */;
INSERT INTO `line` (`grade`, `stage`, `score`, `value`) VALUES ('PreK','base','PK','leftline'),('PreK','first','PK','leftline'),('PreK','second','PK','leftline'),('PreK','third','PK','leftline'),('PreK','fourth','PK','leftbottomline'),('K','base','KC','leftline'),('K','first','KC','leftline'),('K','second','KC','leftbottomline'),('K','third','KR','leftline'),('K','fourth','KR','leftbottomline'),('1','base','1-5','leftbottomline'),('1','first','6-10','leftbottomline'),('1','first','11-15','bottomline'),('1','second','16-20','leftbottomline'),('1','second','21-25','bottomline'),('1','second','26-31','bottomline'),('1','third','32-37','leftbottomline'),('1','third','38-42','bottomline'),('1','fourth','43-48','leftline'),('2','base','43-48','leftline'),('2','first','43-48','leftbottomline'),('2','first','BR','bottomline'),('2','second','2.1','leftline'),('2','third','2.1','leftbottomline'),('2','fourth','2.2','leftline'),('3','base','2.2','leftline'),('3','first','2.2','leftbottomline'),('3','second','3.1','leftline'),('3','third','3.1','leftbottomline'),('3','fourth','3.2','leftline'),('4','base','3.2','leftline'),('4','first','3.2','leftbottomline'),('4','second','4.1','leftline'),('4','third','4.1','leftbottomline'),('4','fourth','4.2','leftline'),('5','base','4.2','leftline'),('5','first','4.2','leftbottomline'),('5','second','5.1','leftline'),('5','third','5.1','leftbottomline'),('5','fourth','5.2','leftline'),('6','base','5.2','leftline'),('6','first','5.2','leftbottomline'),('6','second','6.1','leftline'),('6','third','6.1','leftbottomline'),('6','fourth','6.2','leftline'),('7','base','6.2','leftline'),('7','first','6.2','leftbottomline'),('7','second','7.1','leftline'),('7','third','7.1','leftbottomline'),('7','fourth','7.2','leftline'),('8','base','7.2','leftline'),('8','first','7.2','leftbottomline'),('8','second','8.1','leftline'),('8','third','8.1','leftbottomline'),('8','fourth','8.2','leftline'),('9','base','8.2','leftline'),('9','first','8.2','leftbottomline'),('9','second','9.1','leftline'),('9','third','9.1','leftbottomline'),('9','fourth','9.2','leftline'),('10','base','9.2','leftline'),('10','first','9.2','leftbottomline'),('10','second','10.1','leftline'),('10','third','10.1','leftbottomline'),('10','fourth','10.2','leftline'),('11','base','10.2','leftline'),('11','first','10.2','leftbottomline'),('11','second','11.1','leftline'),('11','third','11.1','leftbottomline'),('11','fourth','11.2','leftline'),('12','base','11.2','leftline'),('12','first','11.2','leftbottomline'),('12','second','12.1','leftline'),('12','third','12.1','leftbottomline'),('12','fourth','12.2','leftline'),('13','base','12.2','leftline'),('13','first','12.2','leftline'),('13','second','12.2','leftline'),('13','third','12.2','leftline'),('13','fourth','12.2','leftbottomline');
/*!40000 ALTER TABLE `line` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `list_members_tmp`
--

DROP TABLE IF EXISTS `list_members_tmp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `list_members_tmp` (
  `process_id` varchar(25) default NULL,
  `studentid` int(11) default NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `list_members_tmp`
--

LOCK TABLES `list_members_tmp` WRITE;
/*!40000 ALTER TABLE `list_members_tmp` DISABLE KEYS */;
/*!40000 ALTER TABLE `list_members_tmp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `lists`
--

DROP TABLE IF EXISTS `lists`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `lists` (
  `userid` int(11) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `sql` text NOT NULL,
  `listid` int(11) NOT NULL auto_increment,
  `listname` varchar(254) NOT NULL default '',
  `am` int(11) NOT NULL default '0',
  `pm` int(11) NOT NULL default '0',
  PRIMARY KEY  (`listid`),
  KEY `userid` (`userid`),
  KEY `type` (`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `lists`
--

LOCK TABLES `lists` WRITE;
/*!40000 ALTER TABLE `lists` DISABLE KEYS */;
/*!40000 ALTER TABLE `lists` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `listshare`
--

DROP TABLE IF EXISTS `listshare`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `listshare` (
  `listid` int(11) NOT NULL default '0',
  `userid` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `listshare`
--

LOCK TABLES `listshare` WRITE;
/*!40000 ALTER TABLE `listshare` DISABLE KEYS */;
/*!40000 ALTER TABLE `listshare` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `listvalues`
--

DROP TABLE IF EXISTS `listvalues`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `listvalues` (
  `listid` int(11) NOT NULL default '0',
  `studentid` int(11) NOT NULL default '0',
  KEY `listid` (`listid`),
  KEY `studentid` (`studentid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `listvalues`
--

LOCK TABLES `listvalues` WRITE;
/*!40000 ALTER TABLE `listvalues` DISABLE KEYS */;
/*!40000 ALTER TABLE `listvalues` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loadtable`
--

DROP TABLE IF EXISTS `loadtable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `loadtable` (
  `param1` varchar(254) NOT NULL default '',
  `param2` varchar(254) NOT NULL default '',
  `param3` varchar(254) NOT NULL default '',
  `param4` varchar(254) NOT NULL default '',
  `param5` varchar(254) NOT NULL default '',
  `param6` varchar(254) NOT NULL default '',
  `param7` varchar(254) NOT NULL default '',
  `param8` varchar(254) NOT NULL default '',
  `param9` varchar(254) NOT NULL default '',
  `param10` varchar(254) NOT NULL default '',
  `mark` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loadtable`
--

LOCK TABLES `loadtable` WRITE;
/*!40000 ALTER TABLE `loadtable` DISABLE KEYS */;
/*!40000 ALTER TABLE `loadtable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `movement`
--

DROP TABLE IF EXISTS `movement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `movement` (
  `studentid` int(11) NOT NULL default '0',
  `exitcode` int(11) NOT NULL default '0',
  `exitlocation` varchar(254) NOT NULL default '',
  `exitdate` date NOT NULL default '0000-00-00',
  `exityear` int(11) NOT NULL default '0',
  `exitquarter` int(11) NOT NULL default '0',
  `exitgrade` varchar(254) NOT NULL default '',
  `entercode` int(11) NOT NULL default '0',
  `enterlocation` varchar(254) NOT NULL default '',
  `enterdate` date NOT NULL default '0000-00-00',
  `enteryear` int(11) NOT NULL default '0',
  `enterquarter` int(11) NOT NULL default '0',
  `entergrade` varchar(254) NOT NULL default '',
  `movementnotes` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `movement`
--

LOCK TABLES `movement` WRITE;
/*!40000 ALTER TABLE `movement` DISABLE KEYS */;
/*!40000 ALTER TABLE `movement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nextlevel`
--

DROP TABLE IF EXISTS `nextlevel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `nextlevel` (
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '',
  `nextlevel` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nextlevel`
--

LOCK TABLES `nextlevel` WRITE;
/*!40000 ALTER TABLE `nextlevel` DISABLE KEYS */;
/*!40000 ALTER TABLE `nextlevel` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pwd_recovery`
--

DROP TABLE IF EXISTS `pwd_recovery`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pwd_recovery` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `userid` int(11) default NULL,
  `code` varchar(100) default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pwd_recovery`
--

LOCK TABLES `pwd_recovery` WRITE;
/*!40000 ALTER TABLE `pwd_recovery` DISABLE KEYS */;
/*!40000 ALTER TABLE `pwd_recovery` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pwd_recovery_students`
--

DROP TABLE IF EXISTS `pwd_recovery_students`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pwd_recovery_students` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `studentid` int(11) default NULL,
  `code` varchar(100) default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pwd_recovery_students`
--

LOCK TABLES `pwd_recovery_students` WRITE;
/*!40000 ALTER TABLE `pwd_recovery_students` DISABLE KEYS */;
/*!40000 ALTER TABLE `pwd_recovery_students` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `quarters`
--

DROP TABLE IF EXISTS `quarters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `quarters` (
  `year` int(11) NOT NULL default '0',
  `quarter` int(11) NOT NULL default '0',
  `start` date NOT NULL default '0000-00-00',
  `finish` date NOT NULL default '0000-00-00',
  PRIMARY KEY  (`year`,`quarter`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quarters`
--

LOCK TABLES `quarters` WRITE;
/*!40000 ALTER TABLE `quarters` DISABLE KEYS */;
INSERT INTO `quarters` (`year`, `quarter`, `start`, `finish`) VALUES (2010,4,'2011-03-19','2011-07-15');
/*!40000 ALTER TABLE `quarters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `repair`
--

DROP TABLE IF EXISTS `repair`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `repair` (
  `studentid` varchar(254) NOT NULL default '',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '',
  `progress` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `repair`
--

LOCK TABLES `repair` WRITE;
/*!40000 ALTER TABLE `repair` DISABLE KEYS */;
/*!40000 ALTER TABLE `repair` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `repnotes`
--

DROP TABLE IF EXISTS `repnotes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `repnotes` (
  `timeframe` varchar(254) NOT NULL default '',
  `site` varchar(254) NOT NULL default '',
  `comment` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `repnotes`
--

LOCK TABLES `repnotes` WRITE;
/*!40000 ALTER TABLE `repnotes` DISABLE KEYS */;
/*!40000 ALTER TABLE `repnotes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reportlist`
--

DROP TABLE IF EXISTS `reportlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reportlist` (
  `id` int(11) NOT NULL auto_increment,
  `userid` int(11) NOT NULL default '0',
  `studentid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reportlist`
--

LOCK TABLES `reportlist` WRITE;
/*!40000 ALTER TABLE `reportlist` DISABLE KEYS */;
/*!40000 ALTER TABLE `reportlist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schooleventcodegroups`
--

DROP TABLE IF EXISTS `schooleventcodegroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schooleventcodegroups` (
  `CodeID` int(11) NOT NULL default '0',
  `GroupID` int(11) NOT NULL default '0',
  PRIMARY KEY  (`CodeID`,`GroupID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schooleventcodegroups`
--

LOCK TABLES `schooleventcodegroups` WRITE;
/*!40000 ALTER TABLE `schooleventcodegroups` DISABLE KEYS */;
INSERT INTO `schooleventcodegroups` (`CodeID`, `GroupID`) VALUES (0,2),(0,3),(1,2),(1,3),(2,2),(2,3),(4,1),(4,3),(7,2),(7,3),(8,2),(8,3),(9,2),(9,3),(11,3);
/*!40000 ALTER TABLE `schooleventcodegroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schooleventcodes`
--

DROP TABLE IF EXISTS `schooleventcodes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schooleventcodes` (
  `CodeID` int(11) NOT NULL default '0',
  `Code` varchar(5) NOT NULL default '',
  `Description` varchar(255) default NULL,
  `IsRequired` tinyint(1) NOT NULL default '0',
  `Color` varchar(6) default NULL,
  PRIMARY KEY  (`CodeID`),
  UNIQUE KEY `Code` (`Code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schooleventcodes`
--

LOCK TABLES `schooleventcodes` WRITE;
/*!40000 ALTER TABLE `schooleventcodes` DISABLE KEYS */;
INSERT INTO `schooleventcodes` (`CodeID`, `Code`, `Description`, `IsRequired`, `Color`) VALUES (0,'--','Regular School Day',1,NULL),(1,'C','School Closes',1,'ffb6c1'),(2,'E','End of Quarter',0,NULL),(3,'H','Legal Holiday',0,'7fff00'),(4,'I','Inservice Day',1,'00ff7f'),(5,'M','Meeting',1,NULL),(6,'N','Not Meeting',1,'ff8c00'),(7,'O','School Opens',1,'ffb6c1'),(8,'S','Saturday School',1,'d2b48c'),(9,'T','Testing',0,'00bfff'),(10,'V','Vacation Day',1,'7fff00'),(11,'W','Teacher Workday',0,'ffd700'),(12,'X','No School',0,'e7e7e7');
/*!40000 ALTER TABLE `schooleventcodes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schooleventgroups`
--

DROP TABLE IF EXISTS `schooleventgroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schooleventgroups` (
  `GroupID` int(11) NOT NULL auto_increment,
  `Description` varchar(255) default NULL,
  PRIMARY KEY  (`GroupID`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schooleventgroups`
--

LOCK TABLES `schooleventgroups` WRITE;
/*!40000 ALTER TABLE `schooleventgroups` DISABLE KEYS */;
INSERT INTO `schooleventgroups` (`GroupID`, `Description`) VALUES (1,'Inservice'),(2,'Student'),(3,'Teacher');
/*!40000 ALTER TABLE `schooleventgroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schoolevents`
--

DROP TABLE IF EXISTS `schoolevents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schoolevents` (
  `CalendarID` int(11) NOT NULL default '0',
  `Date` date NOT NULL default '0000-00-00',
  `CodeID` int(11) default NULL,
  PRIMARY KEY  (`CalendarID`,`Date`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schoolevents`
--

LOCK TABLES `schoolevents` WRITE;
/*!40000 ALTER TABLE `schoolevents` DISABLE KEYS */;
/*!40000 ALTER TABLE `schoolevents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `scoreweight`
--

DROP TABLE IF EXISTS `scoreweight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scoreweight` (
  `subjectid` varchar(254) NOT NULL default '',
  `weight_2` float NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scoreweight`
--

LOCK TABLES `scoreweight` WRITE;
/*!40000 ALTER TABLE `scoreweight` DISABLE KEYS */;
/*!40000 ALTER TABLE `scoreweight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sfainfo`
--

DROP TABLE IF EXISTS `sfainfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sfainfo` (
  `year` varchar(254) NOT NULL default '',
  `base_date` varchar(254) NOT NULL default '',
  `first_date` varchar(254) NOT NULL default '',
  `second_date` varchar(254) NOT NULL default '',
  `third_date` varchar(254) NOT NULL default '',
  `fourth_date` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sfainfo`
--

LOCK TABLES `sfainfo` WRITE;
/*!40000 ALTER TABLE `sfainfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `sfainfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sfascores`
--

DROP TABLE IF EXISTS `sfascores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sfascores` (
  `year` varchar(254) NOT NULL default '',
  `studentid` varchar(254) NOT NULL default '',
  `gradelevel` varchar(254) NOT NULL default '',
  `site` varchar(254) NOT NULL default '',
  `homeroom` varchar(254) NOT NULL default '',
  `base_reading` varchar(254) NOT NULL default '',
  `base_rawscore` varchar(254) NOT NULL default '',
  `base_score` varchar(254) NOT NULL default '',
  `base_rr` varchar(254) NOT NULL default '',
  `first_reading` varchar(254) NOT NULL default '',
  `first_rawscore` varchar(254) NOT NULL default '',
  `first_score` varchar(254) NOT NULL default '',
  `first_rr` varchar(254) NOT NULL default '',
  `second_reading` varchar(254) NOT NULL default '',
  `second_rawscore` varchar(254) NOT NULL default '',
  `second_score` varchar(254) NOT NULL default '',
  `second_rr` varchar(254) NOT NULL default '',
  `third_reading` varchar(254) NOT NULL default '',
  `third_rawscore` varchar(254) NOT NULL default '',
  `third_score` varchar(254) NOT NULL default '',
  `third_rr` varchar(254) NOT NULL default '',
  `fourth_reading` varchar(254) NOT NULL default '',
  `fourth_rawscore` varchar(254) NOT NULL default '',
  `fourth_score` varchar(254) NOT NULL default '',
  `fourth_rr` varchar(254) NOT NULL default '',
  `base_sfa` varchar(254) NOT NULL default '',
  `first_sfa` varchar(254) NOT NULL default '',
  `second_sfa` varchar(254) NOT NULL default '',
  `third_sfa` varchar(254) NOT NULL default '',
  `base_expect` varchar(254) NOT NULL default '',
  `first_expect` varchar(254) NOT NULL default '',
  `second_expect` varchar(254) NOT NULL default '',
  `third_expect` varchar(254) NOT NULL default '',
  `base_tutor` varchar(254) NOT NULL default '',
  `first_tutor` varchar(254) NOT NULL default '',
  `second_tutor` varchar(254) NOT NULL default '',
  `third_tutor` varchar(254) NOT NULL default '',
  `base_hlremove` varchar(254) NOT NULL default '',
  `first_hlremove` varchar(254) NOT NULL default '',
  `second_hlremove` varchar(254) NOT NULL default '',
  `third_hlremove` varchar(254) NOT NULL default '',
  `fourth_hlremove` varchar(254) NOT NULL default '',
  `base_stime` varchar(254) NOT NULL default '',
  `base_etime` varchar(254) NOT NULL default '',
  `first_stime` varchar(254) NOT NULL default '',
  `first_etime` varchar(254) NOT NULL default '',
  `second_stime` varchar(254) NOT NULL default '',
  `second_etime` varchar(254) NOT NULL default '',
  `third_stime` varchar(254) NOT NULL default '',
  `third_etime` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`),
  KEY `year` (`year`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sfascores`
--

LOCK TABLES `sfascores` WRITE;
/*!40000 ALTER TABLE `sfascores` DISABLE KEYS */;
/*!40000 ALTER TABLE `sfascores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sip`
--

DROP TABLE IF EXISTS `sip`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sip` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `test` varchar(254) NOT NULL default '',
  `listid` int(11) NOT NULL default '0',
  `site` varchar(254) NOT NULL default '',
  `area` varchar(254) NOT NULL default '',
  `owner` int(11) NOT NULL default '0',
  `year` varchar(254) NOT NULL default '',
  `status` varchar(254) NOT NULL default '',
  `datecreated` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sip`
--

LOCK TABLES `sip` WRITE;
/*!40000 ALTER TABLE `sip` DISABLE KEYS */;
/*!40000 ALTER TABLE `sip` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sipaction`
--

DROP TABLE IF EXISTS `sipaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sipaction` (
  `aid` int(11) NOT NULL auto_increment,
  `sid` int(11) NOT NULL default '0',
  `area` varchar(254) NOT NULL default '',
  `action` text NOT NULL,
  `person` varchar(254) NOT NULL default '',
  `ptype` varchar(254) NOT NULL default '',
  `timeline` varchar(254) NOT NULL default '',
  `eval` text NOT NULL,
  `final` text NOT NULL,
  PRIMARY KEY  (`aid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sipaction`
--

LOCK TABLES `sipaction` WRITE;
/*!40000 ALTER TABLE `sipaction` DISABLE KEYS */;
/*!40000 ALTER TABLE `sipaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sipaux`
--

DROP TABLE IF EXISTS `sipaux`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sipaux` (
  `sid` int(11) NOT NULL default '0',
  `subjectorder` text NOT NULL,
  `graderating` text NOT NULL,
  `emphasisR` varchar(254) NOT NULL default '',
  `emphasisW` varchar(254) NOT NULL default '',
  `emphasisM` varchar(254) NOT NULL default '',
  `district` text NOT NULL,
  `stateques` text NOT NULL,
  `link` text NOT NULL,
  `ques2` text NOT NULL,
  `link2` text NOT NULL,
  `ques3` text NOT NULL,
  `link3` text NOT NULL,
  `ques4` text NOT NULL,
  `link4` text NOT NULL,
  `r1` text NOT NULL,
  `r2` text NOT NULL,
  `r3` text NOT NULL,
  `r4` text NOT NULL,
  `w1` text NOT NULL,
  `w2` text NOT NULL,
  `w3` text NOT NULL,
  `w4` text NOT NULL,
  `m1` text NOT NULL,
  `m2` text NOT NULL,
  `m3` text NOT NULL,
  `m4` text NOT NULL,
  `i1` text NOT NULL,
  `i2` text NOT NULL,
  `i3` text NOT NULL,
  `i4` text NOT NULL,
  `g11` varchar(4) NOT NULL default '',
  `g12` varchar(4) NOT NULL default '',
  `g13` varchar(4) NOT NULL default '',
  `g14` varchar(4) NOT NULL default '',
  `g15` varchar(4) NOT NULL default '',
  `g21` varchar(4) NOT NULL default '',
  `g22` varchar(4) NOT NULL default '',
  `g23` varchar(4) NOT NULL default '',
  `g24` varchar(4) NOT NULL default '',
  `g25` varchar(4) NOT NULL default '',
  `g31` varchar(4) NOT NULL default '',
  `g32` varchar(4) NOT NULL default '',
  `g33` varchar(4) NOT NULL default '',
  `g34` varchar(4) NOT NULL default '',
  `g35` varchar(4) NOT NULL default '',
  `g41` varchar(4) NOT NULL default '',
  `g42` varchar(4) NOT NULL default '',
  `g43` varchar(4) NOT NULL default '',
  `g44` varchar(4) NOT NULL default '',
  `g45` varchar(4) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sipaux`
--

LOCK TABLES `sipaux` WRITE;
/*!40000 ALTER TABLE `sipaux` DISABLE KEYS */;
/*!40000 ALTER TABLE `sipaux` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `siptestfields`
--

DROP TABLE IF EXISTS `siptestfields`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `siptestfields` (
  `name` varchar(254) NOT NULL default '',
  `value` varchar(254) NOT NULL default '',
  `tip` varchar(254) NOT NULL default '',
  `test` varchar(254) NOT NULL default '',
  `year` varchar(254) NOT NULL default '',
  `ord` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `siptestfields`
--

LOCK TABLES `siptestfields` WRITE;
/*!40000 ALTER TABLE `siptestfields` DISABLE KEYS */;
INSERT INTO `siptestfields` (`name`, `value`, `tip`, `test`, `year`, `ord`) VALUES ('Reading','Reading','','SBA','',0),('R-SC1','R-SC1','Word Identificatin Skills','SBA','',1),('R-SC2','R-SC2','Forming a General Understanding','SBA','',2),('R-SC3','R-SC3','Analysis of Content and Structure','SBA','',3),('Writing','Writing','','SBA','',4),('W-SC1','W-SC1','Write Using a Variety of Forms','SBA','',5),('W-SC2','W-SC2','Structures and Conventions','SBA','',6),('W-SC3','W-SC3','Revise','SBA','',7),('Math','Math','','SBA','',8),('M-SC1','M-SC1','Numeration','SBA','',9),('M-SC2','M-SC2','Measurement','SBA','',10),('M-SC3','M-SC3','Estimation and Computation','SBA','',11),('M-SC4','M-SC4','Functions and Relationships','SBA','',12),('M-SC5','M-SC5','Geometry','SBA','',13),('M-SC6','M-SC6','Statistics/Probability','SBA','',14),('Grand Total','grandsum','','SBA','',15),('Reading','Reading','','HSGQE','',0),('R4.1','R4.1','','HSGQE','',1),('R4.2','R4.2','','HSGQE','',2),('R4.3','R4.3','','HSGQE','',3),('R4.4','R4.4','','HSGQE','',4),('R4.7','R4.7','','HSGQE','',5),('R4.8','R4.8','','HSGQE','',6),('Writing','Writing','','HSGQE','',7),('W4.1/4.2','W4.1/4.2','','HSGQE','',8),('W4.3','W4.3','','HSGQE','',9),('W4.4','W4.4','','HSGQE','',10),('Math','Math','','HSGQE','',11),('M1.4','M1.4','','HSGQE','',12),('M2.4','M2.4','','HSGQE','',13),('M3.4','M3.4','','HSGQE','',14),('M4.4','M4.4','','HSGQE','',15),('M5.4','M5.4','','HSGQE','',16),('M6.4','M6.4','','HSGQE','',17),('Grand Total','grandsum','','HSGQE','',18);
/*!40000 ALTER TABLE `siptestfields` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `site`
--

DROP TABLE IF EXISTS `site`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `site` (
  `siteid` varchar(254) NOT NULL default '',
  `name` varchar(254) NOT NULL default '',
  `logo` varchar(254) NOT NULL default '',
  `schoolNumber` varchar(254) NOT NULL default '',
  `schoolID` varchar(254) NOT NULL default '',
  `village` varchar(254) NOT NULL default '',
  `classic` text NOT NULL,
  `important` text NOT NULL,
  `warning` text NOT NULL,
  `tip` text NOT NULL,
  `order` int(11) NOT NULL default '0',
  `oldSite` char(5) NOT NULL,
  `ssite` varchar(10) NOT NULL,
  PRIMARY KEY  (`siteid`),
  KEY `order` (`order`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `site`
--

LOCK TABLES `site` WRITE;
/*!40000 ALTER TABLE `site` DISABLE KEYS */;
INSERT INTO `site` (`siteid`, `name`, `logo`, `schoolNumber`, `schoolID`, `village`, `classic`, `important`, `warning`, `tip`, `order`, `oldSite`, `ssite`) VALUES ('Admin','Admin','delta_school_district_sm.gif','','','','','We hope that 2010-11 is productive and satisfying and that you continue to grow with your students, with your staff and with your communities.  ','The Educational Technology staff continues to welcome suggestions for improving DART.  Many of the comments made by district staff have already prompted changes, and it\'s essential  to maintain that commitment to continuous improvement.  Please click the \"Feedback\" link to offer suggestions or to report errors.\r\n','One of DART\'s powerful features is its ability to link relative student weaknesses directly to instructional resources that both teachers and students can edit. This means that DART has a built-in ability for users to build curriculum and resources collaboratively that directly tied to student instructional needs.  No other student information system currently has that ability!',16,'Admin','Site');
/*!40000 ALTER TABLE `site` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sped_aux`
--

DROP TABLE IF EXISTS `sped_aux`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sped_aux` (
  `spedid` int(11) NOT NULL auto_increment,
  `studentid` varchar(255) default NULL,
  `percent` varchar(255) default NULL,
  `AT` varchar(255) default NULL,
  `EC` varchar(255) default NULL,
  `End` varchar(255) default NULL,
  `Entry` varchar(255) default NULL,
  `ESER` varchar(255) default NULL,
  `aLeave` varchar(255) default NULL,
  `GR` varchar(255) default NULL,
  `HC` varchar(255) default NULL,
  `HC2` varchar(255) default NULL,
  `Month` varchar(255) default NULL,
  `Month_IEP` varchar(255) default NULL,
  `Month_Psy` varchar(255) default NULL,
  `OT` varchar(255) default NULL,
  `Psy` varchar(255) default NULL,
  `Psy_ReEval` varchar(255) default NULL,
  `PT` varchar(255) default NULL,
  `Sp` varchar(255) default NULL,
  `Sp_Code` varchar(255) default NULL,
  `Sp_ReEval` varchar(255) default NULL,
  `Start` varchar(255) default NULL,
  `SUR_P` varchar(255) default NULL,
  `S_L` varchar(255) default NULL,
  `Test_AC` varchar(255) default NULL,
  `Total` varchar(255) default NULL,
  `TRP` varchar(255) default NULL,
  `TRS` varchar(255) default NULL,
  `Agency` varchar(255) default NULL,
  `Code` varchar(255) default NULL,
  `Today` varchar(255) default NULL,
  `spedcomments` text NOT NULL,
  `LEP_Status` varchar(254) NOT NULL,
  `Add_45_Days` varchar(254) NOT NULL,
  PRIMARY KEY  (`spedid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sped_aux`
--

LOCK TABLES `sped_aux` WRITE;
/*!40000 ALTER TABLE `sped_aux` DISABLE KEYS */;
/*!40000 ALTER TABLE `sped_aux` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `speddata`
--

DROP TABLE IF EXISTS `speddata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `speddata` (
  `studentid` int(11) NOT NULL default '0',
  `Sped_Status` varchar(254) NOT NULL,
  `GoalViewID` varchar(254) NOT NULL,
  `dc` varchar(254) NOT NULL default '',
  `pcode` varchar(254) NOT NULL default '',
  `pcode_old` varchar(254) NOT NULL,
  `referral` date NOT NULL,
  `entrysped` date NOT NULL default '0000-00-00',
  `iepstart` date NOT NULL default '0000-00-00',
  `iepend` date NOT NULL default '0000-00-00',
  `percent` varchar(254) NOT NULL default '',
  `psyreeval` date NOT NULL default '0000-00-00',
  `splangreeval` date NOT NULL default '0000-00-00',
  `eser` date NOT NULL default '0000-00-00',
  `exitdate` date NOT NULL default '0000-00-00',
  `exitreason` text NOT NULL,
  `testac` varchar(254) NOT NULL default '',
  `rs_sp_lang` varchar(254) NOT NULL default '',
  `rs_gross_motor` varchar(254) NOT NULL default '',
  `rs_fine_motor` varchar(254) NOT NULL default '',
  `cos_1` varchar(254) NOT NULL default '',
  `cos_2` varchar(254) NOT NULL default '',
  `cos_3` varchar(254) NOT NULL default '',
  `childfind` varchar(254) NOT NULL default '',
  `ect` varchar(254) NOT NULL default '',
  `sec_trans` varchar(254) NOT NULL default '',
  `pso` varchar(254) NOT NULL default '',
  `count` varchar(254) NOT NULL default '',
  `lre` varchar(254) NOT NULL default '',
  `behaviorplan` varchar(254) NOT NULL default '',
  `Last_OT_Eval` date NOT NULL,
  `Last_PT_Eval` date NOT NULL,
  `Other_Eval` varchar(254) NOT NULL,
  `Other_Eval_Date` date NOT NULL,
  `Current_ESER` date NOT NULL,
  `ESER_plus3` date NOT NULL,
  `Latest_Consent` varchar(254) NOT NULL,
  `45_Days` varchar(254) NOT NULL,
  `Reason_Code` varchar(254) NOT NULL,
  `SpEd_Exit_Date` date NOT NULL,
  `SpEd_Exit_Code` varchar(254) NOT NULL,
  `IEPLessAge3` varchar(254) NOT NULL,
  `Trans_Plan` varchar(254) NOT NULL,
  `ISS` varchar(254) NOT NULL,
  `OSS` varchar(254) NOT NULL,
  `MD_Held` varchar(254) NOT NULL,
  `Test_AC` varchar(254) NOT NULL,
  `Mod_HSGQE` varchar(254) NOT NULL,
  `Alt_Assmt` varchar(254) NOT NULL,
  `Int_Needs` varchar(254) NOT NULL,
  `RS_Sp` varchar(254) NOT NULL,
  `RS_FM` varchar(254) NOT NULL,
  `RS_GM` varchar(254) NOT NULL,
  `RS_Coun` varchar(254) NOT NULL,
  `RS_Tran` varchar(254) NOT NULL,
  `RS_Other` varchar(254) NOT NULL,
  `H_Aid` varchar(254) NOT NULL,
  `spedcomments` text NOT NULL,
  `Add_45_Days` varchar(254) NOT NULL,
  `LEP_Status` varchar(254) NOT NULL,
  PRIMARY KEY  (`studentid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `speddata`
--

LOCK TABLES `speddata` WRITE;
/*!40000 ALTER TABLE `speddata` DISABLE KEYS */;
/*!40000 ALTER TABLE `speddata` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `standards`
--

DROP TABLE IF EXISTS `standards`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `standards` (
  `id` varchar(254) NOT NULL default '',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  `std` varchar(254) NOT NULL default '',
  `order` int(11) NOT NULL default '0',
  `description` text NOT NULL,
  `shortname` varchar(254) NOT NULL default '',
  `link` varchar(254) NOT NULL default '',
  `standardID` varchar(254) NOT NULL default '',
  `Identifier` varchar(254) NOT NULL default '',
  `numlevel` int(11) NOT NULL default '0',
  KEY `subject` (`subject`),
  KEY `level` (`level`),
  KEY `type` (`type`),
  KEY `std` (`std`),
  KEY `order` (`order`),
  KEY `shortname` (`shortname`),
  KEY `link` (`link`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `standards`
--

LOCK TABLES `standards` WRITE;
/*!40000 ALTER TABLE `standards` DISABLE KEYS */;
/*!40000 ALTER TABLE `standards` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `student` (
  `studentid` int(11) NOT NULL auto_increment,
  `fname` varchar(24) NOT NULL default '',
  `mname` varchar(24) NOT NULL default '',
  `lname` varchar(24) NOT NULL default '',
  `status` enum('Active','Inactive') NOT NULL default 'Active',
  `code` varchar(10) NOT NULL default '',
  `extID` varchar(10) NOT NULL default '0',
  `site` varchar(5) NOT NULL default '',
  `present` float NOT NULL default '0',
  `absent` float NOT NULL default '0',
  `attper` decimal(10,0) NOT NULL default '0',
  `picture` varchar(128) NOT NULL default '',
  `addr` varchar(254) NOT NULL default '',
  `village` varchar(254) NOT NULL default '',
  `state` varchar(32) NOT NULL default '',
  `zip` varchar(10) NOT NULL default '',
  `phone` varchar(24) NOT NULL default '',
  `email` varchar(64) NOT NULL default '',
  `dartid` varchar(254) NOT NULL default '',
  `user` varchar(64) NOT NULL default '',
  `pwd` varchar(128) NOT NULL default '',
  `alaskaid` varchar(254) NOT NULL default '',
  `psid` varchar(254) NOT NULL default '',
  `grade` varchar(254) NOT NULL default '',
  `bday` date NOT NULL default '0000-00-00',
  `age` varchar(254) NOT NULL default '',
  `latestenroll` varchar(254) NOT NULL default '',
  `gender` varchar(254) NOT NULL default '',
  `nslp` varchar(254) NOT NULL default '',
  `ethnicity` varchar(254) NOT NULL default '',
  `NSLPEligible` varchar(254) NOT NULL default '',
  `migrant` varchar(254) NOT NULL default '',
  `attendance` varchar(254) NOT NULL default '',
  `lastUpdate` varchar(254) NOT NULL default '',
  `eligibility` varchar(254) NOT NULL default '',
  `SpED_IEP` varchar(254) NOT NULL default '',
  `LEP` varchar(254) NOT NULL default '',
  `LEPStatus` varchar(254) NOT NULL default '',
  `nativeEd` date NOT NULL default '0000-00-00',
  `titleI` varchar(254) NOT NULL default '',
  `sec504` varchar(254) NOT NULL default '',
  `relatedServices` varchar(254) NOT NULL default '',
  `behaviorPlan` varchar(254) NOT NULL default '',
  `GTPlan` varchar(254) NOT NULL default '',
  `HSGQEReading` varchar(254) NOT NULL default '',
  `SRI` varchar(254) NOT NULL default '',
  `HSGQEWriting` varchar(254) NOT NULL default '',
  `STAR` varchar(254) NOT NULL default '',
  `HSGQEMath` varchar(254) NOT NULL default '',
  `scores` varchar(24) NOT NULL default '',
  `mark` varchar(254) NOT NULL default '',
  `mark2` varchar(254) NOT NULL default '',
  `sped` char(1) NOT NULL default 'N',
  `maddr` varchar(128) NOT NULL default '',
  `siblings` tinytext NOT NULL,
  `siblingsnames` tinytext NOT NULL,
  `parent` varchar(128) NOT NULL default '',
  `parentphone` varchar(24) NOT NULL default '',
  `parentmaddr` varchar(128) NOT NULL default '',
  `parentaddr` varchar(128) NOT NULL default '',
  `parentvillage` varchar(64) NOT NULL default '',
  `parentzip` varchar(10) NOT NULL default '',
  `parentwstudent` enum('Y','N','') NOT NULL default '',
  `snotes` tinytext NOT NULL,
  `testing` tinytext NOT NULL,
  `additional` tinytext NOT NULL,
  `extracurricular` tinytext NOT NULL,
  `gpid` int(11) NOT NULL,
  PRIMARY KEY  (`studentid`),
  KEY `site` (`site`),
  KEY `status` (`status`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `studentlevel`
--

DROP TABLE IF EXISTS `studentlevel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `studentlevel` (
  `studentid` int(11) NOT NULL default '0',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) default NULL,
  `progress` varchar(254) NOT NULL default 'EMG',
  `spoints` float NOT NULL,
  `sweight` float NOT NULL,
  `percentcomp` float NOT NULL,
  `avg` float NOT NULL,
  `start` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `final` timestamp NOT NULL default '0000-00-00 00:00:00',
  `change_username` varchar(254) NOT NULL default '',
  `change_user` int(11) NOT NULL default '0',
  `change_timestamp` int(11) NOT NULL default '0',
  `igrp` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`),
  KEY `subject` (`subject`),
  KEY `level` (`level`),
  KEY `progress` (`progress`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `studentlevel`
--

LOCK TABLES `studentlevel` WRITE;
/*!40000 ALTER TABLE `studentlevel` DISABLE KEYS */;
/*!40000 ALTER TABLE `studentlevel` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `studentmovement`
--

DROP TABLE IF EXISTS `studentmovement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `studentmovement` (
  `studentid` int(11) NOT NULL default '0',
  `kind` varchar(254) NOT NULL default '',
  `code` text NOT NULL,
  `date` date NOT NULL default '0000-00-00',
  `site` varchar(254) NOT NULL default '',
  `comment` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `studentmovement`
--

LOCK TABLES `studentmovement` WRITE;
/*!40000 ALTER TABLE `studentmovement` DISABLE KEYS */;
/*!40000 ALTER TABLE `studentmovement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `subjects`
--

DROP TABLE IF EXISTS `subjects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `subjects` (
  `id` varchar(254) NOT NULL default '',
  `name` varchar(254) NOT NULL default '',
  `gradLevel` int(11) NOT NULL default '0',
  `order` int(11) NOT NULL default '99',
  `standardID` varchar(254) NOT NULL default '',
  `identifier` varchar(254) NOT NULL default '',
  `core` varchar(254) NOT NULL default '',
  `weight` float NOT NULL default '0',
  KEY `id` (`id`),
  KEY `gradLevel` (`gradLevel`),
  KEY `order` (`order`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `subjects`
--

LOCK TABLES `subjects` WRITE;
/*!40000 ALTER TABLE `subjects` DISABLE KEYS */;
INSERT INTO `subjects` (`id`, `name`, `gradLevel`, `order`, `standardID`, `identifier`, `core`, `weight`) VALUES ('CA','Cultural Awareness',5,1,'2670','CA','x',0.5),('CS','Career Skills',5,2,'2881','CD','x',0.5),('LS','Life Skills',5,3,'3802','PS','x',0.5),('MA','Mathematics',9,4,'1491','MA','x',1),('RE','Reading',8,5,'2002','RE','x',1),('SC','Science',6,6,'2251','SC','x',1),('SS','Social Studies',8,7,'4032','SS','x',1),('TE','Technology',5,8,'3014','TE','x',0.5),('WR','Writing',8,9,'2516','WR','x',1),('TI','Technology Internship',0,99,'','','',0.5),('FB','Field Biology',0,99,'','','',0.5),('MU','Music',0,99,'','','',0.5),('SU','Subsistence',0,99,'','','',0.5),('GP','Graduation Pacing',0,99,'','','',0.5),('PH','Physics',0,99,'','','',0.5),('AN','Anthropology',0,99,'','','',0.5),('JN','Journalism',0,99,'','','',0.5),('AV','Aviation',0,99,'','','',0.5),('IT','Industrial Technology',0,99,'','','',0.5),('CE','Career Exploration',0,99,'','','',0.5),('PE','Physical Education',0,99,'','','',0.5),('AC','Art and Culture',0,99,'','','',0.5),('MF','Manufacturing',0,99,'','','',0.5),('LA','Languages',0,99,'','','',0.5),('EV','Current Events',0,99,'','','',0.5),('AW','Academic Writing',0,99,'','','',0.5),('DM','Developmental Math',0,99,'','','',0.5),('BI','Biology',0,99,'','','',0.5),('EC','Economics',0,99,'','','',0),('GV','Government',0,99,'','','',0);
/*!40000 ALTER TABLE `subjects` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test_save_import_order`
--

DROP TABLE IF EXISTS `test_save_import_order`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test_save_import_order` (
  `test` varchar(254) NOT NULL default '',
  `import` text NOT NULL,
  PRIMARY KEY  (`test`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test_save_import_order`
--

LOCK TABLES `test_save_import_order` WRITE;
/*!40000 ALTER TABLE `test_save_import_order` DISABLE KEYS */;
INSERT INTO `test_save_import_order` (`test`, `import`) VALUES ('SBA','a:159:{i:0;s:1:\"1\";i:1;s:1:\"0\";i:2;s:1:\"2\";i:3;s:2:\"18\";i:4;s:2:\"19\";i:5;s:2:\"20\";i:6;s:2:\"21\";i:7;s:2:\"22\";i:8;s:2:\"23\";i:9;s:2:\"24\";i:10;s:2:\"25\";i:11;s:2:\"26\";i:12;s:2:\"27\";i:13;s:2:\"28\";i:14;s:2:\"29\";i:15;s:2:\"30\";i:16;s:2:\"31\";i:17;s:2:\"32\";i:18;s:2:\"33\";i:19;s:2:\"34\";i:20;s:2:\"35\";i:21;s:2:\"36\";i:22;s:2:\"37\";i:23;s:2:\"38\";i:24;s:2:\"39\";i:25;s:2:\"40\";i:26;s:2:\"41\";i:27;s:2:\"42\";i:28;s:2:\"43\";i:29;s:2:\"44\";i:30;s:2:\"45\";i:31;s:2:\"46\";i:32;s:2:\"47\";i:33;s:2:\"48\";i:34;s:2:\"51\";i:35;s:2:\"52\";i:36;s:2:\"53\";i:37;s:2:\"54\";i:38;s:2:\"55\";i:39;s:2:\"56\";i:40;s:2:\"57\";i:41;s:2:\"58\";i:42;s:2:\"59\";i:43;s:2:\"60\";i:44;s:2:\"61\";i:45;s:2:\"62\";i:46;s:2:\"63\";i:47;s:2:\"64\";i:48;s:2:\"65\";i:49;s:2:\"66\";i:50;s:2:\"67\";i:51;s:2:\"68\";i:52;s:2:\"69\";i:53;s:2:\"70\";i:54;s:2:\"71\";i:55;s:2:\"72\";i:56;s:2:\"73\";i:57;s:2:\"74\";i:58;s:2:\"75\";i:59;s:2:\"76\";i:60;s:2:\"77\";i:61;s:2:\"78\";i:62;s:2:\"79\";i:63;s:2:\"80\";i:64;s:2:\"81\";i:65;s:2:\"84\";i:66;s:2:\"85\";i:67;s:2:\"86\";i:68;s:2:\"87\";i:69;s:2:\"88\";i:70;s:2:\"89\";i:71;s:2:\"90\";i:72;s:2:\"91\";i:73;s:2:\"92\";i:74;s:2:\"93\";i:75;s:2:\"94\";i:76;s:2:\"95\";i:77;s:2:\"96\";i:78;s:2:\"97\";i:79;s:2:\"98\";i:80;s:2:\"99\";i:81;s:3:\"100\";i:82;s:3:\"101\";i:83;s:3:\"102\";i:84;s:3:\"103\";i:85;s:3:\"104\";i:86;s:3:\"105\";i:87;s:3:\"106\";i:88;s:3:\"107\";i:89;s:3:\"108\";i:90;s:3:\"109\";i:91;s:3:\"110\";i:92;s:3:\"111\";i:93;s:3:\"112\";i:94;s:3:\"113\";i:95;s:3:\"114\";i:96;s:3:\"115\";i:97;s:3:\"116\";i:98;s:3:\"117\";i:99;s:3:\"118\";i:100;s:3:\"119\";i:101;s:3:\"120\";i:102;s:3:\"121\";i:103;s:3:\"122\";i:104;s:3:\"123\";i:105;s:3:\"124\";i:106;s:3:\"125\";i:107;s:3:\"126\";i:108;s:3:\"127\";i:109;s:3:\"128\";i:110;s:3:\"129\";i:111;s:3:\"130\";i:112;s:3:\"131\";i:113;s:3:\"132\";i:114;s:3:\"133\";i:115;s:3:\"134\";i:116;s:3:\"135\";i:117;s:3:\"136\";i:118;s:3:\"137\";i:119;s:3:\"138\";i:120;s:3:\"141\";i:121;s:3:\"142\";i:122;s:3:\"143\";i:123;s:3:\"144\";i:124;s:3:\"145\";i:125;s:3:\"146\";i:126;s:3:\"147\";i:127;s:3:\"148\";i:128;s:3:\"149\";i:129;s:3:\"150\";i:130;s:3:\"151\";i:131;s:3:\"152\";i:132;s:3:\"153\";i:133;s:3:\"154\";i:134;s:3:\"155\";i:135;s:3:\"156\";i:136;s:3:\"157\";i:137;s:3:\"158\";i:138;s:3:\"159\";i:139;s:3:\"160\";i:140;s:3:\"161\";i:141;s:3:\"162\";i:142;s:3:\"163\";i:143;s:3:\"164\";i:144;s:3:\"165\";i:145;s:3:\"166\";i:146;s:3:\"167\";i:147;s:3:\"168\";i:148;s:3:\"169\";i:149;s:3:\"170\";i:150;s:3:\"171\";i:151;s:3:\"172\";i:152;s:3:\"173\";i:153;s:3:\"174\";i:154;s:3:\"175\";i:155;s:3:\"176\";i:156;s:3:\"177\";i:157;s:3:\"178\";i:158;s:3:\"179\";}'),('PPVT','a:23:{i:0;s:1:\"0\";i:1;s:1:\"2\";i:2;s:1:\"3\";i:3;s:1:\"5\";i:4;s:1:\"6\";i:5;s:1:\"7\";i:6;s:1:\"8\";i:7;s:1:\"9\";i:8;s:2:\"10\";i:9;s:2:\"11\";i:10;s:2:\"12\";i:11;s:2:\"13\";i:12;s:2:\"14\";i:13;s:2:\"15\";i:14;s:2:\"16\";i:15;s:2:\"17\";i:16;s:2:\"18\";i:17;s:2:\"19\";i:18;s:2:\"20\";i:19;s:2:\"21\";i:20;s:2:\"22\";i:21;s:2:\"23\";i:22;s:2:\"24\";}'),('HSGQE','a:144:{i:0;s:1:\"0\";i:1;s:1:\"1\";i:2;s:1:\"2\";i:3;s:2:\"14\";i:4;s:2:\"15\";i:5;s:2:\"16\";i:6;s:2:\"17\";i:7;s:2:\"18\";i:8;s:2:\"19\";i:9;s:2:\"20\";i:10;s:2:\"21\";i:11;s:2:\"22\";i:12;s:2:\"23\";i:13;s:2:\"24\";i:14;s:2:\"25\";i:15;s:2:\"26\";i:16;s:2:\"27\";i:17;s:2:\"28\";i:18;s:2:\"29\";i:19;s:2:\"30\";i:20;s:2:\"31\";i:21;s:2:\"32\";i:22;s:2:\"33\";i:23;s:2:\"34\";i:24;s:2:\"35\";i:25;s:2:\"36\";i:26;s:2:\"37\";i:27;s:2:\"38\";i:28;s:2:\"39\";i:29;s:2:\"40\";i:30;s:2:\"41\";i:31;s:2:\"42\";i:32;s:2:\"43\";i:33;s:2:\"44\";i:34;s:2:\"45\";i:35;s:2:\"46\";i:36;s:2:\"47\";i:37;s:2:\"48\";i:38;s:2:\"49\";i:39;s:2:\"50\";i:40;s:2:\"51\";i:41;s:2:\"52\";i:42;s:2:\"53\";i:43;s:2:\"54\";i:44;s:2:\"55\";i:45;s:2:\"56\";i:46;s:2:\"57\";i:47;s:2:\"58\";i:48;s:2:\"59\";i:49;s:2:\"60\";i:50;s:2:\"61\";i:51;s:2:\"62\";i:52;s:2:\"63\";i:53;s:2:\"64\";i:54;s:2:\"65\";i:55;s:2:\"66\";i:56;s:2:\"67\";i:57;s:2:\"68\";i:58;s:2:\"69\";i:59;s:2:\"70\";i:60;s:2:\"71\";i:61;s:2:\"72\";i:62;s:2:\"73\";i:63;s:2:\"74\";i:64;s:2:\"75\";i:65;s:2:\"76\";i:66;s:2:\"77\";i:67;s:2:\"78\";i:68;s:2:\"79\";i:69;s:2:\"80\";i:70;s:2:\"81\";i:71;s:2:\"82\";i:72;s:2:\"83\";i:73;s:2:\"84\";i:74;s:2:\"85\";i:75;s:2:\"86\";i:76;s:2:\"87\";i:77;s:2:\"88\";i:78;s:2:\"89\";i:79;s:2:\"90\";i:80;s:2:\"91\";i:81;s:2:\"92\";i:82;s:2:\"93\";i:83;s:2:\"94\";i:84;s:2:\"95\";i:85;s:2:\"96\";i:86;s:2:\"97\";i:87;s:2:\"98\";i:88;s:2:\"99\";i:89;s:3:\"100\";i:90;s:3:\"101\";i:91;s:3:\"102\";i:92;s:3:\"103\";i:93;s:3:\"104\";i:94;s:3:\"105\";i:95;s:3:\"106\";i:96;s:3:\"107\";i:97;s:3:\"108\";i:98;s:3:\"109\";i:99;s:3:\"110\";i:100;s:3:\"111\";i:101;s:3:\"112\";i:102;s:3:\"113\";i:103;s:3:\"114\";i:104;s:3:\"115\";i:105;s:3:\"116\";i:106;s:3:\"117\";i:107;s:3:\"118\";i:108;s:3:\"119\";i:109;s:3:\"120\";i:110;s:3:\"121\";i:111;s:3:\"122\";i:112;s:3:\"123\";i:113;s:3:\"124\";i:114;s:3:\"125\";i:115;s:3:\"126\";i:116;s:3:\"127\";i:117;s:3:\"128\";i:118;s:3:\"129\";i:119;s:3:\"130\";i:120;s:3:\"131\";i:121;s:3:\"132\";i:122;s:3:\"133\";i:123;s:3:\"134\";i:124;s:3:\"135\";i:125;s:3:\"136\";i:126;s:3:\"137\";i:127;s:3:\"138\";i:128;s:3:\"139\";i:129;s:3:\"140\";i:130;s:3:\"141\";i:131;s:3:\"142\";i:132;s:3:\"143\";i:133;s:3:\"144\";i:134;s:3:\"145\";i:135;s:3:\"146\";i:136;s:3:\"147\";i:137;s:3:\"148\";i:138;s:3:\"149\";i:139;s:3:\"150\";i:140;s:3:\"151\";i:141;s:3:\"152\";i:142;s:3:\"153\";i:143;s:3:\"154\";}'),('ELP','a:17:{i:0;s:1:\"0\";i:1;s:1:\"1\";i:2;s:1:\"4\";i:3;s:2:\"11\";i:4;s:2:\"12\";i:5;s:2:\"13\";i:6;s:2:\"14\";i:7;s:2:\"15\";i:8;s:2:\"16\";i:9;s:2:\"23\";i:10;s:2:\"24\";i:11;s:2:\"25\";i:12;s:2:\"26\";i:13;s:2:\"27\";i:14;s:2:\"28\";i:15;s:2:\"29\";i:16;s:0:\"\";}'),('ESP','a:35:{i:0;s:1:\"0\";i:1;s:1:\"2\";i:2;s:1:\"3\";i:3;s:1:\"4\";i:4;s:1:\"6\";i:5;s:1:\"7\";i:6;s:1:\"8\";i:7;s:1:\"9\";i:8;s:2:\"10\";i:9;s:2:\"11\";i:10;s:2:\"12\";i:11;s:2:\"13\";i:12;s:2:\"14\";i:13;s:2:\"15\";i:14;s:2:\"16\";i:15;s:2:\"17\";i:16;s:2:\"18\";i:17;s:2:\"19\";i:18;s:2:\"20\";i:19;s:2:\"21\";i:20;s:2:\"22\";i:21;s:2:\"23\";i:22;s:2:\"24\";i:23;s:2:\"25\";i:24;s:2:\"26\";i:25;s:2:\"27\";i:26;s:2:\"28\";i:27;s:2:\"29\";i:28;s:2:\"30\";i:29;s:2:\"31\";i:30;s:2:\"32\";i:31;s:2:\"33\";i:32;s:2:\"34\";i:33;s:2:\"35\";i:34;s:2:\"36\";}'),('TerraNova','a:45:{i:0;s:1:\"0\";i:1;s:1:\"2\";i:2;s:1:\"5\";i:3;s:1:\"9\";i:4;s:2:\"10\";i:5;s:2:\"11\";i:6;s:2:\"12\";i:7;s:2:\"13\";i:8;s:2:\"14\";i:9;s:2:\"15\";i:10;s:2:\"16\";i:11;s:2:\"17\";i:12;s:2:\"18\";i:13;s:2:\"19\";i:14;s:2:\"20\";i:15;s:2:\"21\";i:16;s:2:\"22\";i:17;s:2:\"23\";i:18;s:2:\"24\";i:19;s:2:\"25\";i:20;s:2:\"26\";i:21;s:2:\"27\";i:22;s:2:\"28\";i:23;s:2:\"29\";i:24;s:2:\"30\";i:25;s:2:\"31\";i:26;s:2:\"32\";i:27;s:2:\"33\";i:28;s:2:\"34\";i:29;s:2:\"35\";i:30;s:2:\"36\";i:31;s:2:\"37\";i:32;s:2:\"38\";i:33;s:2:\"39\";i:34;s:2:\"40\";i:35;s:2:\"41\";i:36;s:2:\"42\";i:37;s:2:\"43\";i:38;s:2:\"44\";i:39;s:2:\"45\";i:40;s:2:\"46\";i:41;s:2:\"47\";i:42;s:2:\"48\";i:43;s:2:\"49\";i:44;s:2:\"50\";}');
/*!40000 ALTER TABLE `test_save_import_order` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `testinglevel`
--

DROP TABLE IF EXISTS `testinglevel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `testinglevel` (
  `studentid` int(11) NOT NULL default '0',
  `testinglevel` varchar(254) NOT NULL default '',
  `year` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`studentid`,`testinglevel`,`year`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `testinglevel`
--

LOCK TABLES `testinglevel` WRITE;
/*!40000 ALTER TABLE `testinglevel` DISABLE KEYS */;
/*!40000 ALTER TABLE `testinglevel` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `testreports`
--

DROP TABLE IF EXISTS `testreports`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `testreports` (
  `test` varchar(254) NOT NULL default '',
  `testtype` varchar(254) NOT NULL default '',
  `heading` text NOT NULL,
  `fields` text NOT NULL,
  `row` text NOT NULL,
  `ord` int(11) NOT NULL default '0',
  PRIMARY KEY  (`test`,`testtype`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `testreports`
--

LOCK TABLES `testreports` WRITE;
/*!40000 ALTER TABLE `testreports` DISABLE KEYS */;
INSERT INTO `testreports` (`test`, `testtype`, `heading`, `fields`, `row`, `ord`) VALUES ('SBA','Reading','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueReading&dir=$raw_valueReadingdir&orderval=raw_value&stdval=Reading&sorttype=SIGNED\'>Raw Score $raw_valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededReading&dir=$raw_neededReadingdir&orderval=raw_needed&stdval=Reading&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceReading&dir=$raw_differenceReadingdir&orderval=raw_difference&stdval=Reading&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Proficiency<br>Level $valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Scale Score $valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededReading&dir=$neededReadingdir&orderval=needed&stdval=Reading&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceReading&dir=$differenceReadingdir&orderval=difference&stdval=Reading&sorttype=SIGNED\'>Scale Score<br>Difference $differenceReadingarrow</a></th>','aid fname lname gradelevel Reading Reading_class Reading_status Reading_value Reading_diff Reading_needed Reading_scale_value Reading_scale_diff Reading_scale_needed Reading_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Reading</td><td>$Reading_value &nbsp;</td>\r\n			<td>$Reading_needed &nbsp;</td>\r\n			<td>$Reading_diff &nbsp;</td>\r\n			<td>$Reading_level &nbsp;</td>\r\n			<td class=\\\"$Reading_class\\\">$Reading_scale_value &nbsp;</td>\r\n			<td>$Reading_scale_needed &nbsp;</td>\r\n			<td>$Reading_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',1),('SBA','R-SC1','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueRSC1&dir=$raw_valueRSC1dir&orderval=raw_value&stdval=R-SC1&sorttype=SIGNED\'>Raw Score $raw_valueRSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededRSC1&dir=$raw_neededRSC1dir&orderval=raw_needed&stdval=R-SC1&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededRSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceRSC1&dir=$raw_differenceRSC1dir&orderval=raw_difference&stdval=R-SC1&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceRSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueRSC1&dir=$valueRSC1dir&orderval=value&stdval=R-SC1&sorttype=SIGNED\'>Proficiency<br>Level $valueRSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueRSC1&dir=$valueRSC1dir&orderval=value&stdval=R-SC1&sorttype=SIGNED\'>Scale Score $valueRSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededRSC1&dir=$neededRSC1dir&orderval=needed&stdval=R-SC1&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededRSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceRSC1&dir=$differenceRSC1dir&orderval=difference&stdval=R-SC1&sorttype=SIGNED\'>Scale Score<br>Difference $differenceRSC1arrow</a></th>','aid fname lname gradelevel R-SC1 R_SC1_class R_SC1_status R_SC1_value R_SC1_diff R_SC1_needed R_SC1_scale_value R_SC1_scale_diff R_SC1_scale_needed R_SC1_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R-SC1</td><td>$R_SC1_status &nbsp;</td><td>$R_SC1_value &nbsp;</td>\r\n			<td>$R_SC1_needed &nbsp;</td>\r\n			<td>$R_SC1_diff &nbsp;</td>\r\n			<td>$R_SC1_level &nbsp;</td>\r\n			<td class=\\\"$R_SC1_class\\\">$R_SC1_scale_value &nbsp;</td>\r\n			<td>$R_SC1_scale_needed &nbsp;</td>\r\n			<td>$R_SC1_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',2),('SBA','R-SC2','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueRSC2&dir=$raw_valueRSC2dir&orderval=raw_value&stdval=R-SC2&sorttype=SIGNED\'>Raw Score $raw_valueRSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededRSC2&dir=$raw_neededRSC2dir&orderval=raw_needed&stdval=R-SC2&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededRSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceRSC2&dir=$raw_differenceRSC2dir&orderval=raw_difference&stdval=R-SC2&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceRSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueRSC2&dir=$valueRSC2dir&orderval=value&stdval=R-SC2&sorttype=SIGNED\'>Proficiency<br>Level $valueRSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueRSC2&dir=$valueRSC2dir&orderval=value&stdval=R-SC2&sorttype=SIGNED\'>Scale Score $valueRSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededRSC2&dir=$neededRSC2dir&orderval=needed&stdval=R-SC2&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededRSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceRSC2&dir=$differenceRSC2dir&orderval=difference&stdval=R-SC2&sorttype=SIGNED\'>Scale Score<br>Difference $differenceRSC2arrow</a></th>','aid fname lname gradelevel R-SC2 R_SC2_class R_SC2_status R_SC2_value R_SC2_diff R_SC2_needed R_SC2_scale_value R_SC2_scale_diff R_SC2_scale_needed R_SC2_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R-SC2</td><td>$R_SC2_status &nbsp;</td><td>$R_SC2_value &nbsp;</td>\r\n			<td>$R_SC2_needed &nbsp;</td>\r\n			<td>$R_SC2_diff &nbsp;</td>\r\n			<td>$R_SC2_level &nbsp;</td>\r\n			<td class=\\\"$R_SC2_class\\\">$R_SC2_scale_value &nbsp;</td>\r\n			<td>$R_SC2_scale_needed &nbsp;</td>\r\n			<td>$R_SC2_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',3),('SBA','R-SC3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueRSC3&dir=$raw_valueRSC3dir&orderval=raw_value&stdval=R-SC3&sorttype=SIGNED\'>Raw Score $raw_valueRSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededRSC3&dir=$raw_neededRSC3dir&orderval=raw_needed&stdval=R-SC3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededRSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceRSC3&dir=$raw_differenceRSC3dir&orderval=raw_difference&stdval=R-SC3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceRSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueRSC3&dir=$valueRSC3dir&orderval=value&stdval=R-SC3&sorttype=SIGNED\'>Proficiency<br>Level $valueRSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueRSC3&dir=$valueRSC3dir&orderval=value&stdval=R-SC3&sorttype=SIGNED\'>Scale Score $valueRSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededRSC3&dir=$neededRSC3dir&orderval=needed&stdval=R-SC3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededRSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceRSC3&dir=$differenceRSC3dir&orderval=difference&stdval=R-SC3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceRSC3arrow</a></th>','aid fname lname gradelevel R-SC3 R_SC3_class R_SC3_status R_SC3_value R_SC3_diff R_SC3_needed R_SC3_scale_value R_SC3_scale_diff R_SC3_scale_needed R_SC3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R-SC3</td><td>$R_SC3_status &nbsp;</td><td>$R_SC3_value &nbsp;</td>\r\n			<td>$R_SC3_needed &nbsp;</td>\r\n			<td>$R_SC3_diff &nbsp;</td>\r\n			<td>$R_SC3_level &nbsp;</td>\r\n			<td class=\\\"$R_SC3_class\\\">$R_SC3_scale_value &nbsp;</td>\r\n			<td>$R_SC3_scale_needed &nbsp;</td>\r\n			<td>$R_SC3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',4),('SBA','Writing','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueWriting&dir=$raw_valueWritingdir&orderval=raw_value&stdval=Writing&sorttype=SIGNED\'>Raw Score $raw_valueWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededWriting&dir=$raw_neededWritingdir&orderval=raw_needed&stdval=Writing&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceWriting&dir=$raw_differenceWritingdir&orderval=raw_difference&stdval=Writing&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=SIGNED\'>Proficiency<br>Level $valueWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=SIGNED\'>Scale Score $valueWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededWriting&dir=$neededWritingdir&orderval=needed&stdval=Writing&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceWriting&dir=$differenceWritingdir&orderval=difference&stdval=Writing&sorttype=SIGNED\'>Scale Score<br>Difference $differenceWritingarrow</a></th>','aid fname lname gradelevel Writing Writing_class Writing_status Writing_value Writing_diff Writing_needed Writing_scale_value Writing_scale_diff Writing_scale_needed Writing_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Writing</td><td>$Writing_value &nbsp;</td>\r\n			<td>$Writing_needed &nbsp;</td>\r\n			<td>$Writing_diff &nbsp;</td>\r\n			<td>$Writing_level &nbsp;</td>\r\n			<td class=\\\"$Writing_class\\\">$Writing_scale_value &nbsp;</td>\r\n			<td>$Writing_scale_needed &nbsp;</td>\r\n			<td>$Writing_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',5),('SBA','W-SC1','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueWSC1&dir=$raw_valueWSC1dir&orderval=raw_value&stdval=W-SC1&sorttype=SIGNED\'>Raw Score $raw_valueWSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededWSC1&dir=$raw_neededWSC1dir&orderval=raw_needed&stdval=W-SC1&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededWSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceWSC1&dir=$raw_differenceWSC1dir&orderval=raw_difference&stdval=W-SC1&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceWSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWSC1&dir=$valueWSC1dir&orderval=value&stdval=W-SC1&sorttype=SIGNED\'>Proficiency<br>Level $valueWSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWSC1&dir=$valueWSC1dir&orderval=value&stdval=W-SC1&sorttype=SIGNED\'>Scale Score $valueWSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededWSC1&dir=$neededWSC1dir&orderval=needed&stdval=W-SC1&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededWSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceWSC1&dir=$differenceWSC1dir&orderval=difference&stdval=W-SC1&sorttype=SIGNED\'>Scale Score<br>Difference $differenceWSC1arrow</a></th>','aid fname lname gradelevel W-SC1 W_SC1_class W_SC1_status W_SC1_value W_SC1_diff W_SC1_needed W_SC1_scale_value W_SC1_scale_diff W_SC1_scale_needed W_SC1_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>W-SC1</td><td>$W_SC1_status &nbsp;</td><td>$W_SC1_value &nbsp;</td>\r\n			<td>$W_SC1_needed &nbsp;</td>\r\n			<td>$W_SC1_diff &nbsp;</td>\r\n			<td>$W_SC1_level &nbsp;</td>\r\n			<td class=\\\"$W_SC1_class\\\">$W_SC1_scale_value &nbsp;</td>\r\n			<td>$W_SC1_scale_needed &nbsp;</td>\r\n			<td>$W_SC1_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',6),('SBA','W-SC2','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueWSC2&dir=$raw_valueWSC2dir&orderval=raw_value&stdval=W-SC2&sorttype=SIGNED\'>Raw Score $raw_valueWSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededWSC2&dir=$raw_neededWSC2dir&orderval=raw_needed&stdval=W-SC2&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededWSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceWSC2&dir=$raw_differenceWSC2dir&orderval=raw_difference&stdval=W-SC2&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceWSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWSC2&dir=$valueWSC2dir&orderval=value&stdval=W-SC2&sorttype=SIGNED\'>Proficiency<br>Level $valueWSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWSC2&dir=$valueWSC2dir&orderval=value&stdval=W-SC2&sorttype=SIGNED\'>Scale Score $valueWSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededWSC2&dir=$neededWSC2dir&orderval=needed&stdval=W-SC2&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededWSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceWSC2&dir=$differenceWSC2dir&orderval=difference&stdval=W-SC2&sorttype=SIGNED\'>Scale Score<br>Difference $differenceWSC2arrow</a></th>','aid fname lname gradelevel W-SC2 W_SC2_class W_SC2_status W_SC2_value W_SC2_diff W_SC2_needed W_SC2_scale_value W_SC2_scale_diff W_SC2_scale_needed W_SC2_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>W-SC2</td><td>$W_SC2_status &nbsp;</td><td>$W_SC2_value &nbsp;</td>\r\n			<td>$W_SC2_needed &nbsp;</td>\r\n			<td>$W_SC2_diff &nbsp;</td>\r\n			<td>$W_SC2_level &nbsp;</td>\r\n			<td class=\\\"$W_SC2_class\\\">$W_SC2_scale_value &nbsp;</td>\r\n			<td>$W_SC2_scale_needed &nbsp;</td>\r\n			<td>$W_SC2_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',7),('SBA','W-SC3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueWSC3&dir=$raw_valueWSC3dir&orderval=raw_value&stdval=W-SC3&sorttype=SIGNED\'>Raw Score $raw_valueWSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededWSC3&dir=$raw_neededWSC3dir&orderval=raw_needed&stdval=W-SC3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededWSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceWSC3&dir=$raw_differenceWSC3dir&orderval=raw_difference&stdval=W-SC3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceWSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWSC3&dir=$valueWSC3dir&orderval=value&stdval=W-SC3&sorttype=SIGNED\'>Proficiency<br>Level $valueWSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWSC3&dir=$valueWSC3dir&orderval=value&stdval=W-SC3&sorttype=SIGNED\'>Scale Score $valueWSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededWSC3&dir=$neededWSC3dir&orderval=needed&stdval=W-SC3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededWSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceWSC3&dir=$differenceWSC3dir&orderval=difference&stdval=W-SC3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceWSC3arrow</a></th>','aid fname lname gradelevel W-SC3 W_SC3_class W_SC3_status W_SC3_value W_SC3_diff W_SC3_needed W_SC3_scale_value W_SC3_scale_diff W_SC3_scale_needed W_SC3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>W-SC3</td><td>$W_SC3_status &nbsp;</td><td>$W_SC3_value &nbsp;</td>\r\n			<td>$W_SC3_needed &nbsp;</td>\r\n			<td>$W_SC3_diff &nbsp;</td>\r\n			<td>$W_SC3_level &nbsp;</td>\r\n			<td class=\\\"$W_SC3_class\\\">$W_SC3_scale_value &nbsp;</td>\r\n			<td>$W_SC3_scale_needed &nbsp;</td>\r\n			<td>$W_SC3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',8),('SBA','Math','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueMath&dir=$raw_valueMathdir&orderval=raw_value&stdval=Math&sorttype=SIGNED\'>Raw Score $raw_valueMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMath&dir=$raw_neededMathdir&orderval=raw_needed&stdval=Math&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMath&dir=$raw_differenceMathdir&orderval=raw_difference&stdval=Math&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=SIGNED\'>Proficiency<br>Level $valueMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=SIGNED\'>Scale Score $valueMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMath&dir=$neededMathdir&orderval=needed&stdval=Math&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMath&dir=$differenceMathdir&orderval=difference&stdval=Math&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMatharrow</a></th>','aid fname lname gradelevel Math Math_class Math_status Math_value Math_diff Math_needed Math_scale_value Math_scale_diff Math_scale_needed Math_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Math</td><td>$Math_value &nbsp;</td>\r\n			<td>$Math_needed &nbsp;</td>\r\n			<td>$Math_diff &nbsp;</td>\r\n			<td>$Math_level &nbsp;</td>\r\n			<td class=\\\"$Math_class\\\">$Math_scale_value &nbsp;</td>\r\n			<td>$Math_scale_needed &nbsp;</td>\r\n			<td>$Math_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',9),('SBA','M-SC1','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueMSC1&dir=$raw_valueMSC1dir&orderval=raw_value&stdval=M-SC1&sorttype=SIGNED\'>Raw Score $raw_valueMSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMSC1&dir=$raw_neededMSC1dir&orderval=raw_needed&stdval=M-SC1&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMSC1&dir=$raw_differenceMSC1dir&orderval=raw_difference&stdval=M-SC1&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC1&dir=$valueMSC1dir&orderval=value&stdval=M-SC1&sorttype=SIGNED\'>Proficiency<br>Level $valueMSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC1&dir=$valueMSC1dir&orderval=value&stdval=M-SC1&sorttype=SIGNED\'>Scale Score $valueMSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMSC1&dir=$neededMSC1dir&orderval=needed&stdval=M-SC1&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMSC1&dir=$differenceMSC1dir&orderval=difference&stdval=M-SC1&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMSC1arrow</a></th>','aid fname lname gradelevel M-SC1 M_SC1_class M_SC1_status M_SC1_value M_SC1_diff M_SC1_needed M_SC1_scale_value M_SC1_scale_diff M_SC1_scale_needed M_SC1_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M-SC1</td><td>$M_SC1_status &nbsp;</td><td>$M_SC1_value &nbsp;</td>\r\n			<td>$M_SC1_needed &nbsp;</td>\r\n			<td>$M_SC1_diff &nbsp;</td>\r\n			<td>$M_SC1_level &nbsp;</td>\r\n			<td class=\\\"$M_SC1_class\\\">$M_SC1_scale_value &nbsp;</td>\r\n			<td>$M_SC1_scale_needed &nbsp;</td>\r\n			<td>$M_SC1_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',10),('SBA','M-SC2','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueMSC2&dir=$raw_valueMSC2dir&orderval=raw_value&stdval=M-SC2&sorttype=SIGNED\'>Raw Score $raw_valueMSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMSC2&dir=$raw_neededMSC2dir&orderval=raw_needed&stdval=M-SC2&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMSC2&dir=$raw_differenceMSC2dir&orderval=raw_difference&stdval=M-SC2&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC2&dir=$valueMSC2dir&orderval=value&stdval=M-SC2&sorttype=SIGNED\'>Proficiency<br>Level $valueMSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC2&dir=$valueMSC2dir&orderval=value&stdval=M-SC2&sorttype=SIGNED\'>Scale Score $valueMSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMSC2&dir=$neededMSC2dir&orderval=needed&stdval=M-SC2&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMSC2&dir=$differenceMSC2dir&orderval=difference&stdval=M-SC2&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMSC2arrow</a></th>','aid fname lname gradelevel M-SC2 M_SC2_class M_SC2_status M_SC2_value M_SC2_diff M_SC2_needed M_SC2_scale_value M_SC2_scale_diff M_SC2_scale_needed M_SC2_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M-SC2</td><td>$M_SC2_status &nbsp;</td><td>$M_SC2_value &nbsp;</td>\r\n			<td>$M_SC2_needed &nbsp;</td>\r\n			<td>$M_SC2_diff &nbsp;</td>\r\n			<td>$M_SC2_level &nbsp;</td>\r\n			<td class=\\\"$M_SC2_class\\\">$M_SC2_scale_value &nbsp;</td>\r\n			<td>$M_SC2_scale_needed &nbsp;</td>\r\n			<td>$M_SC2_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',11),('SBA','M-SC3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueMSC3&dir=$raw_valueMSC3dir&orderval=raw_value&stdval=M-SC3&sorttype=SIGNED\'>Raw Score $raw_valueMSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMSC3&dir=$raw_neededMSC3dir&orderval=raw_needed&stdval=M-SC3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMSC3&dir=$raw_differenceMSC3dir&orderval=raw_difference&stdval=M-SC3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC3&dir=$valueMSC3dir&orderval=value&stdval=M-SC3&sorttype=SIGNED\'>Proficiency<br>Level $valueMSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC3&dir=$valueMSC3dir&orderval=value&stdval=M-SC3&sorttype=SIGNED\'>Scale Score $valueMSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMSC3&dir=$neededMSC3dir&orderval=needed&stdval=M-SC3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMSC3&dir=$differenceMSC3dir&orderval=difference&stdval=M-SC3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMSC3arrow</a></th>','aid fname lname gradelevel M-SC3 M_SC3_class M_SC3_status M_SC3_value M_SC3_diff M_SC3_needed M_SC3_scale_value M_SC3_scale_diff M_SC3_scale_needed M_SC3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M-SC3</td><td>$M_SC3_status &nbsp;</td><td>$M_SC3_value &nbsp;</td>\r\n			<td>$M_SC3_needed &nbsp;</td>\r\n			<td>$M_SC3_diff &nbsp;</td>\r\n			<td>$M_SC3_level &nbsp;</td>\r\n			<td class=\\\"$M_SC3_class\\\">$M_SC3_scale_value &nbsp;</td>\r\n			<td>$M_SC3_scale_needed &nbsp;</td>\r\n			<td>$M_SC3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',12),('SBA','M-SC4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueMSC4&dir=$raw_valueMSC4dir&orderval=raw_value&stdval=M-SC4&sorttype=SIGNED\'>Raw Score $raw_valueMSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMSC4&dir=$raw_neededMSC4dir&orderval=raw_needed&stdval=M-SC4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMSC4&dir=$raw_differenceMSC4dir&orderval=raw_difference&stdval=M-SC4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC4&dir=$valueMSC4dir&orderval=value&stdval=M-SC4&sorttype=SIGNED\'>Proficiency<br>Level $valueMSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC4&dir=$valueMSC4dir&orderval=value&stdval=M-SC4&sorttype=SIGNED\'>Scale Score $valueMSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMSC4&dir=$neededMSC4dir&orderval=needed&stdval=M-SC4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMSC4&dir=$differenceMSC4dir&orderval=difference&stdval=M-SC4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMSC4arrow</a></th>','aid fname lname gradelevel M-SC4 M_SC4_class M_SC4_status M_SC4_value M_SC4_diff M_SC4_needed M_SC4_scale_value M_SC4_scale_diff M_SC4_scale_needed M_SC4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M-SC4</td><td>$M_SC4_status &nbsp;</td><td>$M_SC4_value &nbsp;</td>\r\n			<td>$M_SC4_needed &nbsp;</td>\r\n			<td>$M_SC4_diff &nbsp;</td>\r\n			<td>$M_SC4_level &nbsp;</td>\r\n			<td class=\\\"$M_SC4_class\\\">$M_SC4_scale_value &nbsp;</td>\r\n			<td>$M_SC4_scale_needed &nbsp;</td>\r\n			<td>$M_SC4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',13),('SBA','M-SC5','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueMSC5&dir=$raw_valueMSC5dir&orderval=raw_value&stdval=M-SC5&sorttype=SIGNED\'>Raw Score $raw_valueMSC5arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMSC5&dir=$raw_neededMSC5dir&orderval=raw_needed&stdval=M-SC5&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMSC5arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMSC5&dir=$raw_differenceMSC5dir&orderval=raw_difference&stdval=M-SC5&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMSC5arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC5&dir=$valueMSC5dir&orderval=value&stdval=M-SC5&sorttype=SIGNED\'>Proficiency<br>Level $valueMSC5arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC5&dir=$valueMSC5dir&orderval=value&stdval=M-SC5&sorttype=SIGNED\'>Scale Score $valueMSC5arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMSC5&dir=$neededMSC5dir&orderval=needed&stdval=M-SC5&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMSC5arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMSC5&dir=$differenceMSC5dir&orderval=difference&stdval=M-SC5&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMSC5arrow</a></th>','aid fname lname gradelevel M-SC5 M_SC5_class M_SC5_status M_SC5_value M_SC5_diff M_SC5_needed M_SC5_scale_value M_SC5_scale_diff M_SC5_scale_needed M_SC5_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M-SC5</td><td>$M_SC5_status &nbsp;</td><td>$M_SC5_value &nbsp;</td>\r\n			<td>$M_SC5_needed &nbsp;</td>\r\n			<td>$M_SC5_diff &nbsp;</td>\r\n			<td>$M_SC5_level &nbsp;</td>\r\n			<td class=\\\"$M_SC5_class\\\">$M_SC5_scale_value &nbsp;</td>\r\n			<td>$M_SC5_scale_needed &nbsp;</td>\r\n			<td>$M_SC5_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',14),('SBA','M-SC6','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueMSC6&dir=$raw_valueMSC6dir&orderval=raw_value&stdval=M-SC6&sorttype=SIGNED\'>Raw Score $raw_valueMSC6arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMSC6&dir=$raw_neededMSC6dir&orderval=raw_needed&stdval=M-SC6&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMSC6arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMSC6&dir=$raw_differenceMSC6dir&orderval=raw_difference&stdval=M-SC6&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMSC6arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC6&dir=$valueMSC6dir&orderval=value&stdval=M-SC6&sorttype=SIGNED\'>Proficiency<br>Level $valueMSC6arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMSC6&dir=$valueMSC6dir&orderval=value&stdval=M-SC6&sorttype=SIGNED\'>Scale Score $valueMSC6arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMSC6&dir=$neededMSC6dir&orderval=needed&stdval=M-SC6&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMSC6arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMSC6&dir=$differenceMSC6dir&orderval=difference&stdval=M-SC6&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMSC6arrow</a></th>','aid fname lname gradelevel M-SC6 M_SC6_class M_SC6_status M_SC6_value M_SC6_diff M_SC6_needed M_SC6_scale_value M_SC6_scale_diff M_SC6_scale_needed M_SC6_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M-SC6</td><td>$M_SC6_status &nbsp;</td><td>$M_SC6_value &nbsp;</td>\r\n			<td>$M_SC6_needed &nbsp;</td>\r\n			<td>$M_SC6_diff &nbsp;</td>\r\n			<td>$M_SC6_level &nbsp;</td>\r\n			<td class=\\\"$M_SC6_class\\\">$M_SC6_scale_value &nbsp;</td>\r\n			<td>$M_SC6_scale_needed &nbsp;</td>\r\n			<td>$M_SC6_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',15),('SBA','Science','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueScience&dir=$raw_valueSciencedir&orderval=raw_value&stdval=Science&sorttype=SIGNED\'>Raw Score $raw_valueSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededScience&dir=$raw_neededSciencedir&orderval=raw_needed&stdval=Science&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceScience&dir=$raw_differenceSciencedir&orderval=raw_difference&stdval=Science&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueScience&dir=$valueSciencedir&orderval=value&stdval=Science&sorttype=SIGNED\'>Proficiency<br>Level $valueSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueScience&dir=$valueSciencedir&orderval=value&stdval=Science&sorttype=SIGNED\'>Scale Score $valueSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededScience&dir=$neededSciencedir&orderval=needed&stdval=Science&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceScience&dir=$differenceSciencedir&orderval=difference&stdval=Science&sorttype=SIGNED\'>Scale Score<br>Difference $differenceSciencearrow</a></th>','aid fname lname gradelevel Science Science_class Science_status Science_value Science_diff Science_needed Science_scale_value Science_scale_diff Science_scale_needed Science_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Science</td><td>$Science_value &nbsp;</td>\r\n			<td>$Science_needed &nbsp;</td>\r\n			<td>$Science_diff &nbsp;</td>\r\n			<td>$Science_level &nbsp;</td>\r\n			<td class=\\\"$Science_class\\\">$Science_scale_value &nbsp;</td>\r\n			<td>$Science_scale_needed &nbsp;</td>\r\n			<td>$Science_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',16),('SBA','S-SC1','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueSSC1&dir=$raw_valueSSC1dir&orderval=raw_value&stdval=S-SC1&sorttype=SIGNED\'>Raw Score $raw_valueSSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededSSC1&dir=$raw_neededSSC1dir&orderval=raw_needed&stdval=S-SC1&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededSSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceSSC1&dir=$raw_differenceSSC1dir&orderval=raw_difference&stdval=S-SC1&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceSSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC1&dir=$valueSSC1dir&orderval=value&stdval=S-SC1&sorttype=SIGNED\'>Proficiency<br>Level $valueSSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC1&dir=$valueSSC1dir&orderval=value&stdval=S-SC1&sorttype=SIGNED\'>Scale Score $valueSSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededSSC1&dir=$neededSSC1dir&orderval=needed&stdval=S-SC1&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededSSC1arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceSSC1&dir=$differenceSSC1dir&orderval=difference&stdval=S-SC1&sorttype=SIGNED\'>Scale Score<br>Difference $differenceSSC1arrow</a></th>','aid fname lname gradelevel S-SC1 S_SC1_class S_SC1_status S_SC1_value S_SC1_diff S_SC1_needed S_SC1_scale_value S_SC1_scale_diff S_SC1_scale_needed S_SC1_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>S-SC1</td><td>$S_SC1_status &nbsp;</td><td>$S_SC1_value &nbsp;</td>\r\n			<td>$S_SC1_needed &nbsp;</td>\r\n			<td>$S_SC1_diff &nbsp;</td>\r\n			<td>$S_SC1_level &nbsp;</td>\r\n			<td class=\\\"$S_SC1_class\\\">$S_SC1_scale_value &nbsp;</td>\r\n			<td>$S_SC1_scale_needed &nbsp;</td>\r\n			<td>$S_SC1_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',17),('SBA','S-SC2','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueSSC2&dir=$raw_valueSSC2dir&orderval=raw_value&stdval=S-SC2&sorttype=SIGNED\'>Raw Score $raw_valueSSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededSSC2&dir=$raw_neededSSC2dir&orderval=raw_needed&stdval=S-SC2&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededSSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceSSC2&dir=$raw_differenceSSC2dir&orderval=raw_difference&stdval=S-SC2&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceSSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC2&dir=$valueSSC2dir&orderval=value&stdval=S-SC2&sorttype=SIGNED\'>Proficiency<br>Level $valueSSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC2&dir=$valueSSC2dir&orderval=value&stdval=S-SC2&sorttype=SIGNED\'>Scale Score $valueSSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededSSC2&dir=$neededSSC2dir&orderval=needed&stdval=S-SC2&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededSSC2arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceSSC2&dir=$differenceSSC2dir&orderval=difference&stdval=S-SC2&sorttype=SIGNED\'>Scale Score<br>Difference $differenceSSC2arrow</a></th>','aid fname lname gradelevel S-SC2 S_SC2_class S_SC2_status S_SC2_value S_SC2_diff S_SC2_needed S_SC2_scale_value S_SC2_scale_diff S_SC2_scale_needed S_SC2_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>S-SC2</td><td>$S_SC2_status &nbsp;</td><td>$S_SC2_value &nbsp;</td>\r\n			<td>$S_SC2_needed &nbsp;</td>\r\n			<td>$S_SC2_diff &nbsp;</td>\r\n			<td>$S_SC2_level &nbsp;</td>\r\n			<td class=\\\"$S_SC2_class\\\">$S_SC2_scale_value &nbsp;</td>\r\n			<td>$S_SC2_scale_needed &nbsp;</td>\r\n			<td>$S_SC2_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',18),('SBA','S-SC3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueSSC3&dir=$raw_valueSSC3dir&orderval=raw_value&stdval=S-SC3&sorttype=SIGNED\'>Raw Score $raw_valueSSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededSSC3&dir=$raw_neededSSC3dir&orderval=raw_needed&stdval=S-SC3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededSSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceSSC3&dir=$raw_differenceSSC3dir&orderval=raw_difference&stdval=S-SC3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceSSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC3&dir=$valueSSC3dir&orderval=value&stdval=S-SC3&sorttype=SIGNED\'>Proficiency<br>Level $valueSSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC3&dir=$valueSSC3dir&orderval=value&stdval=S-SC3&sorttype=SIGNED\'>Scale Score $valueSSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededSSC3&dir=$neededSSC3dir&orderval=needed&stdval=S-SC3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededSSC3arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceSSC3&dir=$differenceSSC3dir&orderval=difference&stdval=S-SC3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceSSC3arrow</a></th>','aid fname lname gradelevel S-SC3 S_SC3_class S_SC3_status S_SC3_value S_SC3_diff S_SC3_needed S_SC3_scale_value S_SC3_scale_diff S_SC3_scale_needed S_SC3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>S-SC3</td><td>$S_SC3_status &nbsp;</td><td>$S_SC3_value &nbsp;</td>\r\n			<td>$S_SC3_needed &nbsp;</td>\r\n			<td>$S_SC3_diff &nbsp;</td>\r\n			<td>$S_SC3_level &nbsp;</td>\r\n			<td class=\\\"$S_SC3_class\\\">$S_SC3_scale_value &nbsp;</td>\r\n			<td>$S_SC3_scale_needed &nbsp;</td>\r\n			<td>$S_SC3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',19),('SBA','S-SC4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueSSC4&dir=$raw_valueSSC4dir&orderval=raw_value&stdval=S-SC4&sorttype=SIGNED\'>Raw Score $raw_valueSSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededSSC4&dir=$raw_neededSSC4dir&orderval=raw_needed&stdval=S-SC4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededSSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceSSC4&dir=$raw_differenceSSC4dir&orderval=raw_difference&stdval=S-SC4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceSSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC4&dir=$valueSSC4dir&orderval=value&stdval=S-SC4&sorttype=SIGNED\'>Proficiency<br>Level $valueSSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSSC4&dir=$valueSSC4dir&orderval=value&stdval=S-SC4&sorttype=SIGNED\'>Scale Score $valueSSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededSSC4&dir=$neededSSC4dir&orderval=needed&stdval=S-SC4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededSSC4arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceSSC4&dir=$differenceSSC4dir&orderval=difference&stdval=S-SC4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceSSC4arrow</a></th>','aid fname lname gradelevel S-SC4 S_SC4_class S_SC4_status S_SC4_value S_SC4_diff S_SC4_needed S_SC4_scale_value S_SC4_scale_diff S_SC4_scale_needed S_SC4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>S-SC4</td><td>$S_SC4_status &nbsp;</td><td>$S_SC4_value &nbsp;</td>\r\n			<td>$S_SC4_needed &nbsp;</td>\r\n			<td>$S_SC4_diff &nbsp;</td>\r\n			<td>$S_SC4_level &nbsp;</td>\r\n			<td class=\\\"$S_SC4_class\\\">$S_SC4_scale_value &nbsp;</td>\r\n			<td>$S_SC4_scale_needed &nbsp;</td>\r\n			<td>$S_SC4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',20),('HSGQE','Reading','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueReading&dir=$raw_valueReadingdir&orderval=raw_value&stdval=Reading&sorttype=SIGNED\'>Raw Score $raw_valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededReading&dir=$raw_neededReadingdir&orderval=raw_needed&stdval=Reading&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceReading&dir=$raw_differenceReadingdir&orderval=raw_difference&stdval=Reading&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Proficiency<br>Level $valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Scale Score $valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededReading&dir=$neededReadingdir&orderval=needed&stdval=Reading&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceReading&dir=$differenceReadingdir&orderval=difference&stdval=Reading&sorttype=SIGNED\'>Scale Score<br>Difference $differenceReadingarrow</a></th>','aid fname lname gradelevel Reading Reading_class Reading_status Reading_value Reading_diff Reading_needed Reading_scale_value Reading_scale_diff Reading_scale_needed Reading_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Reading</td><td>$Reading_value &nbsp;</td>\r\n			<td>$Reading_needed &nbsp;</td>\r\n			<td>$Reading_diff &nbsp;</td>\r\n			<td>$Reading_level &nbsp;</td>\r\n			<td class=\\\"$Reading_class\\\">$Reading_scale_value &nbsp;</td>\r\n			<td>$Reading_scale_needed &nbsp;</td>\r\n			<td>$Reading_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',1),('HSGQE','R4.1','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueR41&dir=$raw_valueR41dir&orderval=raw_value&stdval=R4.1&sorttype=SIGNED\'>Raw Score $raw_valueR41arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededR41&dir=$raw_neededR41dir&orderval=raw_needed&stdval=R4.1&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededR41arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceR41&dir=$raw_differenceR41dir&orderval=raw_difference&stdval=R4.1&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceR41arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR41&dir=$valueR41dir&orderval=value&stdval=R4.1&sorttype=SIGNED\'>Proficiency<br>Level $valueR41arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR41&dir=$valueR41dir&orderval=value&stdval=R4.1&sorttype=SIGNED\'>Scale Score $valueR41arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededR41&dir=$neededR41dir&orderval=needed&stdval=R4.1&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededR41arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceR41&dir=$differenceR41dir&orderval=difference&stdval=R4.1&sorttype=SIGNED\'>Scale Score<br>Difference $differenceR41arrow</a></th>','aid fname lname gradelevel R4.1 R4_1_class R4_1_status R4_1_value R4_1_diff R4_1_needed R4_1_scale_value R4_1_scale_diff R4_1_scale_needed R4_1_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R4.1</td><td>$R4_1_status &nbsp;</td><td>$R4_1_value &nbsp;</td>\r\n			<td>$R4_1_needed &nbsp;</td>\r\n			<td>$R4_1_diff &nbsp;</td>\r\n			<td>$R4_1_level &nbsp;</td>\r\n			<td class=\\\"$R4_1_class\\\">$R4_1_scale_value &nbsp;</td>\r\n			<td>$R4_1_scale_needed &nbsp;</td>\r\n			<td>$R4_1_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',2),('HSGQE','R4.2','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueR42&dir=$raw_valueR42dir&orderval=raw_value&stdval=R4.2&sorttype=SIGNED\'>Raw Score $raw_valueR42arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededR42&dir=$raw_neededR42dir&orderval=raw_needed&stdval=R4.2&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededR42arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceR42&dir=$raw_differenceR42dir&orderval=raw_difference&stdval=R4.2&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceR42arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR42&dir=$valueR42dir&orderval=value&stdval=R4.2&sorttype=SIGNED\'>Proficiency<br>Level $valueR42arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR42&dir=$valueR42dir&orderval=value&stdval=R4.2&sorttype=SIGNED\'>Scale Score $valueR42arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededR42&dir=$neededR42dir&orderval=needed&stdval=R4.2&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededR42arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceR42&dir=$differenceR42dir&orderval=difference&stdval=R4.2&sorttype=SIGNED\'>Scale Score<br>Difference $differenceR42arrow</a></th>','aid fname lname gradelevel R4.2 R4_2_class R4_2_status R4_2_value R4_2_diff R4_2_needed R4_2_scale_value R4_2_scale_diff R4_2_scale_needed R4_2_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R4.2</td><td>$R4_2_status &nbsp;</td><td>$R4_2_value &nbsp;</td>\r\n			<td>$R4_2_needed &nbsp;</td>\r\n			<td>$R4_2_diff &nbsp;</td>\r\n			<td>$R4_2_level &nbsp;</td>\r\n			<td class=\\\"$R4_2_class\\\">$R4_2_scale_value &nbsp;</td>\r\n			<td>$R4_2_scale_needed &nbsp;</td>\r\n			<td>$R4_2_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',3),('HSGQE','R4.3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueR43&dir=$raw_valueR43dir&orderval=raw_value&stdval=R4.3&sorttype=SIGNED\'>Raw Score $raw_valueR43arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededR43&dir=$raw_neededR43dir&orderval=raw_needed&stdval=R4.3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededR43arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceR43&dir=$raw_differenceR43dir&orderval=raw_difference&stdval=R4.3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceR43arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR43&dir=$valueR43dir&orderval=value&stdval=R4.3&sorttype=SIGNED\'>Proficiency<br>Level $valueR43arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR43&dir=$valueR43dir&orderval=value&stdval=R4.3&sorttype=SIGNED\'>Scale Score $valueR43arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededR43&dir=$neededR43dir&orderval=needed&stdval=R4.3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededR43arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceR43&dir=$differenceR43dir&orderval=difference&stdval=R4.3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceR43arrow</a></th>','aid fname lname gradelevel R4.3 R4_3_class R4_3_status R4_3_value R4_3_diff R4_3_needed R4_3_scale_value R4_3_scale_diff R4_3_scale_needed R4_3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R4.3</td><td>$R4_3_status &nbsp;</td><td>$R4_3_value &nbsp;</td>\r\n			<td>$R4_3_needed &nbsp;</td>\r\n			<td>$R4_3_diff &nbsp;</td>\r\n			<td>$R4_3_level &nbsp;</td>\r\n			<td class=\\\"$R4_3_class\\\">$R4_3_scale_value &nbsp;</td>\r\n			<td>$R4_3_scale_needed &nbsp;</td>\r\n			<td>$R4_3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',4),('HSGQE','R4.4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueR44&dir=$raw_valueR44dir&orderval=raw_value&stdval=R4.4&sorttype=SIGNED\'>Raw Score $raw_valueR44arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededR44&dir=$raw_neededR44dir&orderval=raw_needed&stdval=R4.4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededR44arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceR44&dir=$raw_differenceR44dir&orderval=raw_difference&stdval=R4.4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceR44arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR44&dir=$valueR44dir&orderval=value&stdval=R4.4&sorttype=SIGNED\'>Proficiency<br>Level $valueR44arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR44&dir=$valueR44dir&orderval=value&stdval=R4.4&sorttype=SIGNED\'>Scale Score $valueR44arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededR44&dir=$neededR44dir&orderval=needed&stdval=R4.4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededR44arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceR44&dir=$differenceR44dir&orderval=difference&stdval=R4.4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceR44arrow</a></th>','aid fname lname gradelevel R4.4 R4_4_class R4_4_status R4_4_value R4_4_diff R4_4_needed R4_4_scale_value R4_4_scale_diff R4_4_scale_needed R4_4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R4.4</td><td>$R4_4_status &nbsp;</td><td>$R4_4_value &nbsp;</td>\r\n			<td>$R4_4_needed &nbsp;</td>\r\n			<td>$R4_4_diff &nbsp;</td>\r\n			<td>$R4_4_level &nbsp;</td>\r\n			<td class=\\\"$R4_4_class\\\">$R4_4_scale_value &nbsp;</td>\r\n			<td>$R4_4_scale_needed &nbsp;</td>\r\n			<td>$R4_4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',5),('HSGQE','R4.7','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueR47&dir=$raw_valueR47dir&orderval=raw_value&stdval=R4.7&sorttype=SIGNED\'>Raw Score $raw_valueR47arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededR47&dir=$raw_neededR47dir&orderval=raw_needed&stdval=R4.7&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededR47arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceR47&dir=$raw_differenceR47dir&orderval=raw_difference&stdval=R4.7&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceR47arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR47&dir=$valueR47dir&orderval=value&stdval=R4.7&sorttype=SIGNED\'>Proficiency<br>Level $valueR47arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR47&dir=$valueR47dir&orderval=value&stdval=R4.7&sorttype=SIGNED\'>Scale Score $valueR47arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededR47&dir=$neededR47dir&orderval=needed&stdval=R4.7&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededR47arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceR47&dir=$differenceR47dir&orderval=difference&stdval=R4.7&sorttype=SIGNED\'>Scale Score<br>Difference $differenceR47arrow</a></th>','aid fname lname gradelevel R4.7 R4_7_class R4_7_status R4_7_value R4_7_diff R4_7_needed R4_7_scale_value R4_7_scale_diff R4_7_scale_needed R4_7_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R4.7</td><td>$R4_7_status &nbsp;</td><td>$R4_7_value &nbsp;</td>\r\n			<td>$R4_7_needed &nbsp;</td>\r\n			<td>$R4_7_diff &nbsp;</td>\r\n			<td>$R4_7_level &nbsp;</td>\r\n			<td class=\\\"$R4_7_class\\\">$R4_7_scale_value &nbsp;</td>\r\n			<td>$R4_7_scale_needed &nbsp;</td>\r\n			<td>$R4_7_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',6),('HSGQE','R4.8','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueR48&dir=$raw_valueR48dir&orderval=raw_value&stdval=R4.8&sorttype=SIGNED\'>Raw Score $raw_valueR48arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededR48&dir=$raw_neededR48dir&orderval=raw_needed&stdval=R4.8&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededR48arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceR48&dir=$raw_differenceR48dir&orderval=raw_difference&stdval=R4.8&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceR48arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR48&dir=$valueR48dir&orderval=value&stdval=R4.8&sorttype=SIGNED\'>Proficiency<br>Level $valueR48arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueR48&dir=$valueR48dir&orderval=value&stdval=R4.8&sorttype=SIGNED\'>Scale Score $valueR48arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededR48&dir=$neededR48dir&orderval=needed&stdval=R4.8&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededR48arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceR48&dir=$differenceR48dir&orderval=difference&stdval=R4.8&sorttype=SIGNED\'>Scale Score<br>Difference $differenceR48arrow</a></th>','aid fname lname gradelevel R4.8 R4_8_class R4_8_status R4_8_value R4_8_diff R4_8_needed R4_8_scale_value R4_8_scale_diff R4_8_scale_needed R4_8_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>R4.8</td><td>$R4_8_status &nbsp;</td><td>$R4_8_value &nbsp;</td>\r\n			<td>$R4_8_needed &nbsp;</td>\r\n			<td>$R4_8_diff &nbsp;</td>\r\n			<td>$R4_8_level &nbsp;</td>\r\n			<td class=\\\"$R4_8_class\\\">$R4_8_scale_value &nbsp;</td>\r\n			<td>$R4_8_scale_needed &nbsp;</td>\r\n			<td>$R4_8_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',7),('HSGQE','Writing','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueWriting&dir=$raw_valueWritingdir&orderval=raw_value&stdval=Writing&sorttype=SIGNED\'>Raw Score $raw_valueWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededWriting&dir=$raw_neededWritingdir&orderval=raw_needed&stdval=Writing&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceWriting&dir=$raw_differenceWritingdir&orderval=raw_difference&stdval=Writing&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=SIGNED\'>Proficiency<br>Level $valueWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=SIGNED\'>Scale Score $valueWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededWriting&dir=$neededWritingdir&orderval=needed&stdval=Writing&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededWritingarrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceWriting&dir=$differenceWritingdir&orderval=difference&stdval=Writing&sorttype=SIGNED\'>Scale Score<br>Difference $differenceWritingarrow</a></th>','aid fname lname gradelevel Writing Writing_class Writing_status Writing_value Writing_diff Writing_needed Writing_scale_value Writing_scale_diff Writing_scale_needed Writing_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Writing</td><td>$Writing_value &nbsp;</td>\r\n			<td>$Writing_needed &nbsp;</td>\r\n			<td>$Writing_diff &nbsp;</td>\r\n			<td>$Writing_level &nbsp;</td>\r\n			<td class=\\\"$Writing_class\\\">$Writing_scale_value &nbsp;</td>\r\n			<td>$Writing_scale_needed &nbsp;</td>\r\n			<td>$Writing_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',8),('HSGQE','W4.1/4.2','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueW4142&dir=$raw_valueW4142dir&orderval=raw_value&stdval=W4.1/4.2&sorttype=SIGNED\'>Raw Score $raw_valueW4142arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededW4142&dir=$raw_neededW4142dir&orderval=raw_needed&stdval=W4.1/4.2&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededW4142arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceW4142&dir=$raw_differenceW4142dir&orderval=raw_difference&stdval=W4.1/4.2&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceW4142arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueW4142&dir=$valueW4142dir&orderval=value&stdval=W4.1/4.2&sorttype=SIGNED\'>Proficiency<br>Level $valueW4142arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueW4142&dir=$valueW4142dir&orderval=value&stdval=W4.1/4.2&sorttype=SIGNED\'>Scale Score $valueW4142arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededW4142&dir=$neededW4142dir&orderval=needed&stdval=W4.1/4.2&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededW4142arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceW4142&dir=$differenceW4142dir&orderval=difference&stdval=W4.1/4.2&sorttype=SIGNED\'>Scale Score<br>Difference $differenceW4142arrow</a></th>','aid fname lname gradelevel W4.1/4.2 W4_1_4_2_class W4_1_4_2_status W4_1_4_2_value W4_1_4_2_diff W4_1_4_2_needed W4_1_4_2_scale_value W4_1_4_2_scale_diff W4_1_4_2_scale_needed W4_1_4_2_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>W4.1/4.2</td><td>$W4_1_4_2_status &nbsp;</td><td>$W4_1_4_2_value &nbsp;</td>\r\n			<td>$W4_1_4_2_needed &nbsp;</td>\r\n			<td>$W4_1_4_2_diff &nbsp;</td>\r\n			<td>$W4_1_4_2_level &nbsp;</td>\r\n			<td class=\\\"$W4_1_4_2_class\\\">$W4_1_4_2_scale_value &nbsp;</td>\r\n			<td>$W4_1_4_2_scale_needed &nbsp;</td>\r\n			<td>$W4_1_4_2_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',9),('HSGQE','W4.3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueW43&dir=$raw_valueW43dir&orderval=raw_value&stdval=W4.3&sorttype=SIGNED\'>Raw Score $raw_valueW43arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededW43&dir=$raw_neededW43dir&orderval=raw_needed&stdval=W4.3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededW43arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceW43&dir=$raw_differenceW43dir&orderval=raw_difference&stdval=W4.3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceW43arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueW43&dir=$valueW43dir&orderval=value&stdval=W4.3&sorttype=SIGNED\'>Proficiency<br>Level $valueW43arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueW43&dir=$valueW43dir&orderval=value&stdval=W4.3&sorttype=SIGNED\'>Scale Score $valueW43arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededW43&dir=$neededW43dir&orderval=needed&stdval=W4.3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededW43arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceW43&dir=$differenceW43dir&orderval=difference&stdval=W4.3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceW43arrow</a></th>','aid fname lname gradelevel W4.3 W4_3_class W4_3_status W4_3_value W4_3_diff W4_3_needed W4_3_scale_value W4_3_scale_diff W4_3_scale_needed W4_3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>W4.3</td><td>$W4_3_status &nbsp;</td><td>$W4_3_value &nbsp;</td>\r\n			<td>$W4_3_needed &nbsp;</td>\r\n			<td>$W4_3_diff &nbsp;</td>\r\n			<td>$W4_3_level &nbsp;</td>\r\n			<td class=\\\"$W4_3_class\\\">$W4_3_scale_value &nbsp;</td>\r\n			<td>$W4_3_scale_needed &nbsp;</td>\r\n			<td>$W4_3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',10),('HSGQE','W4.4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueW44&dir=$raw_valueW44dir&orderval=raw_value&stdval=W4.4&sorttype=SIGNED\'>Raw Score $raw_valueW44arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededW44&dir=$raw_neededW44dir&orderval=raw_needed&stdval=W4.4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededW44arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceW44&dir=$raw_differenceW44dir&orderval=raw_difference&stdval=W4.4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceW44arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueW44&dir=$valueW44dir&orderval=value&stdval=W4.4&sorttype=SIGNED\'>Proficiency<br>Level $valueW44arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueW44&dir=$valueW44dir&orderval=value&stdval=W4.4&sorttype=SIGNED\'>Scale Score $valueW44arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededW44&dir=$neededW44dir&orderval=needed&stdval=W4.4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededW44arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceW44&dir=$differenceW44dir&orderval=difference&stdval=W4.4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceW44arrow</a></th>','aid fname lname gradelevel W4.4 W4_4_class W4_4_status W4_4_value W4_4_diff W4_4_needed W4_4_scale_value W4_4_scale_diff W4_4_scale_needed W4_4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>W4.4</td><td>$W4_4_status &nbsp;</td><td>$W4_4_value &nbsp;</td>\r\n			<td>$W4_4_needed &nbsp;</td>\r\n			<td>$W4_4_diff &nbsp;</td>\r\n			<td>$W4_4_level &nbsp;</td>\r\n			<td class=\\\"$W4_4_class\\\">$W4_4_scale_value &nbsp;</td>\r\n			<td>$W4_4_scale_needed &nbsp;</td>\r\n			<td>$W4_4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',11),('HSGQE','Math','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		\r\n		<th><a href=\'{$url}sort=raw_valueMath&dir=$raw_valueMathdir&orderval=raw_value&stdval=Math&sorttype=SIGNED\'>Raw Score $raw_valueMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededMath&dir=$raw_neededMathdir&orderval=raw_needed&stdval=Math&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceMath&dir=$raw_differenceMathdir&orderval=raw_difference&stdval=Math&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=SIGNED\'>Proficiency<br>Level $valueMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=SIGNED\'>Scale Score $valueMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMath&dir=$neededMathdir&orderval=needed&stdval=Math&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededMatharrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceMath&dir=$differenceMathdir&orderval=difference&stdval=Math&sorttype=SIGNED\'>Scale Score<br>Difference $differenceMatharrow</a></th>','aid fname lname gradelevel Math Math_class Math_status Math_value Math_diff Math_needed Math_scale_value Math_scale_diff Math_scale_needed Math_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>Math</td><td>$Math_value &nbsp;</td>\r\n			<td>$Math_needed &nbsp;</td>\r\n			<td>$Math_diff &nbsp;</td>\r\n			<td>$Math_level &nbsp;</td>\r\n			<td class=\\\"$Math_class\\\">$Math_scale_value &nbsp;</td>\r\n			<td>$Math_scale_needed &nbsp;</td>\r\n			<td>$Math_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',12),('HSGQE','M1.4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueM14&dir=$raw_valueM14dir&orderval=raw_value&stdval=M1.4&sorttype=SIGNED\'>Raw Score $raw_valueM14arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededM14&dir=$raw_neededM14dir&orderval=raw_needed&stdval=M1.4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededM14arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceM14&dir=$raw_differenceM14dir&orderval=raw_difference&stdval=M1.4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceM14arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM14&dir=$valueM14dir&orderval=value&stdval=M1.4&sorttype=SIGNED\'>Proficiency<br>Level $valueM14arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM14&dir=$valueM14dir&orderval=value&stdval=M1.4&sorttype=SIGNED\'>Scale Score $valueM14arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededM14&dir=$neededM14dir&orderval=needed&stdval=M1.4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededM14arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceM14&dir=$differenceM14dir&orderval=difference&stdval=M1.4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceM14arrow</a></th>','aid fname lname gradelevel M1.4 M1_4_class M1_4_status M1_4_value M1_4_diff M1_4_needed M1_4_scale_value M1_4_scale_diff M1_4_scale_needed M1_4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M1.4</td><td>$M1_4_status &nbsp;</td><td>$M1_4_value &nbsp;</td>\r\n			<td>$M1_4_needed &nbsp;</td>\r\n			<td>$M1_4_diff &nbsp;</td>\r\n			<td>$M1_4_level &nbsp;</td>\r\n			<td class=\\\"$M1_4_class\\\">$M1_4_scale_value &nbsp;</td>\r\n			<td>$M1_4_scale_needed &nbsp;</td>\r\n			<td>$M1_4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',13),('HSGQE','M2.4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueM24&dir=$raw_valueM24dir&orderval=raw_value&stdval=M2.4&sorttype=SIGNED\'>Raw Score $raw_valueM24arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededM24&dir=$raw_neededM24dir&orderval=raw_needed&stdval=M2.4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededM24arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceM24&dir=$raw_differenceM24dir&orderval=raw_difference&stdval=M2.4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceM24arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM24&dir=$valueM24dir&orderval=value&stdval=M2.4&sorttype=SIGNED\'>Proficiency<br>Level $valueM24arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM24&dir=$valueM24dir&orderval=value&stdval=M2.4&sorttype=SIGNED\'>Scale Score $valueM24arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededM24&dir=$neededM24dir&orderval=needed&stdval=M2.4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededM24arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceM24&dir=$differenceM24dir&orderval=difference&stdval=M2.4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceM24arrow</a></th>','aid fname lname gradelevel M2.4 M2_4_class M2_4_status M2_4_value M2_4_diff M2_4_needed M2_4_scale_value M2_4_scale_diff M2_4_scale_needed M2_4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M2.4</td><td>$M2_4_status &nbsp;</td><td>$M2_4_value &nbsp;</td>\r\n			<td>$M2_4_needed &nbsp;</td>\r\n			<td>$M2_4_diff &nbsp;</td>\r\n			<td>$M2_4_level &nbsp;</td>\r\n			<td class=\\\"$M2_4_class\\\">$M2_4_scale_value &nbsp;</td>\r\n			<td>$M2_4_scale_needed &nbsp;</td>\r\n			<td>$M2_4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',14),('HSGQE','M3.4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueM34&dir=$raw_valueM34dir&orderval=raw_value&stdval=M3.4&sorttype=SIGNED\'>Raw Score $raw_valueM34arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededM34&dir=$raw_neededM34dir&orderval=raw_needed&stdval=M3.4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededM34arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceM34&dir=$raw_differenceM34dir&orderval=raw_difference&stdval=M3.4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceM34arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM34&dir=$valueM34dir&orderval=value&stdval=M3.4&sorttype=SIGNED\'>Proficiency<br>Level $valueM34arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM34&dir=$valueM34dir&orderval=value&stdval=M3.4&sorttype=SIGNED\'>Scale Score $valueM34arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededM34&dir=$neededM34dir&orderval=needed&stdval=M3.4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededM34arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceM34&dir=$differenceM34dir&orderval=difference&stdval=M3.4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceM34arrow</a></th>','aid fname lname gradelevel M3.4 M3_4_class M3_4_status M3_4_value M3_4_diff M3_4_needed M3_4_scale_value M3_4_scale_diff M3_4_scale_needed M3_4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M3.4</td><td>$M3_4_status &nbsp;</td><td>$M3_4_value &nbsp;</td>\r\n			<td>$M3_4_needed &nbsp;</td>\r\n			<td>$M3_4_diff &nbsp;</td>\r\n			<td>$M3_4_level &nbsp;</td>\r\n			<td class=\\\"$M3_4_class\\\">$M3_4_scale_value &nbsp;</td>\r\n			<td>$M3_4_scale_needed &nbsp;</td>\r\n			<td>$M3_4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',15),('HSGQE','M4.4','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueM44&dir=$raw_valueM44dir&orderval=raw_value&stdval=M4.4&sorttype=SIGNED\'>Raw Score $raw_valueM44arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededM44&dir=$raw_neededM44dir&orderval=raw_needed&stdval=M4.4&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededM44arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceM44&dir=$raw_differenceM44dir&orderval=raw_difference&stdval=M4.4&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceM44arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM44&dir=$valueM44dir&orderval=value&stdval=M4.4&sorttype=SIGNED\'>Proficiency<br>Level $valueM44arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM44&dir=$valueM44dir&orderval=value&stdval=M4.4&sorttype=SIGNED\'>Scale Score $valueM44arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededM44&dir=$neededM44dir&orderval=needed&stdval=M4.4&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededM44arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceM44&dir=$differenceM44dir&orderval=difference&stdval=M4.4&sorttype=SIGNED\'>Scale Score<br>Difference $differenceM44arrow</a></th>','aid fname lname gradelevel M4.4 M4_4_class M4_4_status M4_4_value M4_4_diff M4_4_needed M4_4_scale_value M4_4_scale_diff M4_4_scale_needed M4_4_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M4.4</td><td>$M4_4_status &nbsp;</td><td>$M4_4_value &nbsp;</td>\r\n			<td>$M4_4_needed &nbsp;</td>\r\n			<td>$M4_4_diff &nbsp;</td>\r\n			<td>$M4_4_level &nbsp;</td>\r\n			<td class=\\\"$M4_4_class\\\">$M4_4_scale_value &nbsp;</td>\r\n			<td>$M4_4_scale_needed &nbsp;</td>\r\n			<td>$M4_4_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',16),('HSGQE','M5.3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueM53&dir=$raw_valueM53dir&orderval=raw_value&stdval=M5.3&sorttype=SIGNED\'>Raw Score $raw_valueM53arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededM53&dir=$raw_neededM53dir&orderval=raw_needed&stdval=M5.3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededM53arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceM53&dir=$raw_differenceM53dir&orderval=raw_difference&stdval=M5.3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceM53arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM53&dir=$valueM53dir&orderval=value&stdval=M5.3&sorttype=SIGNED\'>Proficiency<br>Level $valueM53arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM53&dir=$valueM53dir&orderval=value&stdval=M5.3&sorttype=SIGNED\'>Scale Score $valueM53arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededM53&dir=$neededM53dir&orderval=needed&stdval=M5.3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededM53arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceM53&dir=$differenceM53dir&orderval=difference&stdval=M5.3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceM53arrow</a></th>','aid fname lname gradelevel M5.3 M5_3_class M5_3_status M5_3_value M5_3_diff M5_3_needed M5_3_scale_value M5_3_scale_diff M5_3_scale_needed M5_3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M5.3</td><td>$M5_3_status &nbsp;</td><td>$M5_3_value &nbsp;</td>\r\n			<td>$M5_3_needed &nbsp;</td>\r\n			<td>$M5_3_diff &nbsp;</td>\r\n			<td>$M5_3_level &nbsp;</td>\r\n			<td class=\\\"$M5_3_class\\\">$M5_3_scale_value &nbsp;</td>\r\n			<td>$M5_3_scale_needed &nbsp;</td>\r\n			<td>$M5_3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',17),('HSGQE','M6.3','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th>Strand</th>\r\n		<th>Strand Name</th>\r\n		<th><a href=\'{$url}sort=raw_valueM63&dir=$raw_valueM63dir&orderval=raw_value&stdval=M6.3&sorttype=SIGNED\'>Raw Score $raw_valueM63arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededM63&dir=$raw_neededM63dir&orderval=raw_needed&stdval=M6.3&sorttype=SIGNED\'>Raw Score<br>Needed $raw_neededM63arrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_differenceM63&dir=$raw_differenceM63dir&orderval=raw_difference&stdval=M6.3&sorttype=SIGNED\'>Raw Score<br>Difference $raw_differenceM63arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM63&dir=$valueM63dir&orderval=value&stdval=M6.3&sorttype=SIGNED\'>Proficiency<br>Level $valueM63arrow</a></th>\r\n		<th><a href=\'{$url}sort=valueM63&dir=$valueM63dir&orderval=value&stdval=M6.3&sorttype=SIGNED\'>Scale Score $valueM63arrow</a></th>\r\n		<th><a href=\'{$url}sort=neededM63&dir=$neededM63dir&orderval=needed&stdval=M6.3&sorttype=SIGNED\'>Scale Score<br>Needed for<br>Proficiency $neededM63arrow</a></th>\r\n		<th><a href=\'{$url}sort=differenceM63&dir=$differenceM63dir&orderval=difference&stdval=M6.3&sorttype=SIGNED\'>Scale Score<br>Difference $differenceM63arrow</a></th>','aid fname lname gradelevel M6.3 M6_3_class M6_3_status M6_3_value M6_3_diff M6_3_needed M6_3_scale_value M6_3_scale_diff M6_3_scale_needed M6_3_level needed_proficiency scale_score_dif','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>M6.3</td><td>$M6_3_status &nbsp;</td><td>$M6_3_value &nbsp;</td>\r\n			<td>$M6_3_needed &nbsp;</td>\r\n			<td>$M6_3_diff &nbsp;</td>\r\n			<td>$M6_3_level &nbsp;</td>\r\n			<td class=\\\"$M6_3_class\\\">$M6_3_scale_value &nbsp;</td>\r\n			<td>$M6_3_scale_needed &nbsp;</td>\r\n			<td>$M6_3_scale_diff &nbsp;</td>\r\n			</tr>\\n\r\n		',18),('ESP','Verbal Concepts','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueVerbalConcepts&dir=$raw_valueVerbalConceptsdir&orderval=raw_value&stdval=Verbal Concepts&sorttype=SIGNED\'>Point Score $raw_valueVerbalConceptsarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededVerbalConcepts&dir=$raw_neededVerbalConceptsdir&orderval=raw_needed&stdval=Verbal Concepts&sorttype=SIGNED\'>Screening Index $raw_neededVerbalConceptsarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueVerbalConcepts&dir=$valueVerbalConceptsdir&orderval=value&stdval=Verbal Concepts&sorttype=SIGNED\'>Standard Score $valueVerbalConceptsarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededVerbalConcepts&dir=$neededVerbalConceptsdir&orderval=needed&stdval=Verbal Concepts&sorttype=SIGNED\'>National Percentile $neededVerbalConceptsarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Verbal_Concepts_scale_diff Verbal_Concepts_scale_needed Verbal_Concepts_scale_value Verbal_Concepts_value Verbal_Concepts_needed Verbal_Concepts_raw_diff Verbal_Concepts_test_date Verbal_Concepts_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Verbal_Concepts_value &nbsp;</td>\r\n			<td class=c$Verbal_Concepts_needed >$Verbal_Concepts_needed &nbsp;</td>\r\n			<td>$Verbal_Concepts_scale_value &nbsp;</td>\r\n			<td>$Verbal_Concepts_scale_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',1),('ESP','Visual Discrimination','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueVisualDiscrimination&dir=$raw_valueVisualDiscriminationdir&orderval=raw_value&stdval=Visual Discrimination&sorttype=SIGNED\'>Point Score $raw_valueVisualDiscriminationarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededVisualDiscrimination&dir=$raw_neededVisualDiscriminationdir&orderval=raw_needed&stdval=Visual Discrimination&sorttype=SIGNED\'>Screening Index $raw_neededVisualDiscriminationarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueVisualDiscrimination&dir=$valueVisualDiscriminationdir&orderval=value&stdval=Visual Discrimination&sorttype=SIGNED\'>Standard Score $valueVisualDiscriminationarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededVisualDiscrimination&dir=$neededVisualDiscriminationdir&orderval=needed&stdval=Visual Discrimination&sorttype=SIGNED\'>National Percentile $neededVisualDiscriminationarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Visual_Discrimination_scale_diff Visual_Discrimination_scale_needed Visual_Discrimination_scale_value Visual_Discrimination_value Visual_Discrimination_needed Visual_Discrimination_raw_diff Visual_Discrimination_test_date Visual_Discrimination_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Visual_Discrimination_value &nbsp;</td>\r\n			<td class=c$Visual_Discrimination_needed >$Visual_Discrimination_needed &nbsp;</td>\r\n			<td>$Visual_Discrimination_scale_value &nbsp;</td>\r\n			<td>$Visual_Discrimination_scale_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',2),('ESP','Logical Relations','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueLogicalRelations&dir=$raw_valueLogicalRelationsdir&orderval=raw_value&stdval=Logical Relations&sorttype=SIGNED\'>Point Score $raw_valueLogicalRelationsarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededLogicalRelations&dir=$raw_neededLogicalRelationsdir&orderval=raw_needed&stdval=Logical Relations&sorttype=SIGNED\'>Screening Index $raw_neededLogicalRelationsarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueLogicalRelations&dir=$valueLogicalRelationsdir&orderval=value&stdval=Logical Relations&sorttype=SIGNED\'>Standard Score $valueLogicalRelationsarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededLogicalRelations&dir=$neededLogicalRelationsdir&orderval=needed&stdval=Logical Relations&sorttype=SIGNED\'>National Percentile $neededLogicalRelationsarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Logical_Relations_scale_diff Logical_Relations_scale_needed Logical_Relations_scale_value Logical_Relations_value Logical_Relations_needed Logical_Relations_raw_diff Logical_Relations_test_date Logical_Relations_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Logical_Relations_value &nbsp;</td>\r\n			<td class=c$Logical_Relations_needed >$Logical_Relations_needed &nbsp;</td>\r\n			<td>$Logical_Relations_scale_value &nbsp;</td>\r\n			<td>$Logical_Relations_scale_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',3),('ESP','Basic School Skills','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueBasicSchoolSkills&dir=$raw_valueBasicSchoolSkillsdir&orderval=raw_value&stdval=Basic School Skills&sorttype=SIGNED\'>Point Score $raw_valueBasicSchoolSkillsarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededBasicSchoolSkills&dir=$raw_neededBasicSchoolSkillsdir&orderval=raw_needed&stdval=Basic School Skills&sorttype=SIGNED\'>Screening Index $raw_neededBasicSchoolSkillsarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueBasicSchoolSkills&dir=$valueBasicSchoolSkillsdir&orderval=value&stdval=Basic School Skills&sorttype=SIGNED\'>Standard Score $valueBasicSchoolSkillsarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededBasicSchoolSkills&dir=$neededBasicSchoolSkillsdir&orderval=needed&stdval=Basic School Skills&sorttype=SIGNED\'>National Percentile $neededBasicSchoolSkillsarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Basic_School_Skills_scale_diff Basic_School_Skills_scale_needed Basic_School_Skills_scale_value Basic_School_Skills_value Basic_School_Skills_needed Basic_School_Skills_raw_diff Basic_School_Skills_test_date Basic_School_Skills_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Basic_School_Skills_value &nbsp;</td>\r\n			<td class=c$Basic_School_Skills_needed >$Basic_School_Skills_needed &nbsp;</td>\r\n			<td>$Basic_School_Skills_scale_value &nbsp;</td>\r\n			<td>$Basic_School_Skills_scale_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',4),('ESP','Expressive Language','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueExpressiveLanguage&dir=$raw_valueExpressiveLanguagedir&orderval=raw_value&stdval=Expressive Language&sorttype=SIGNED\'>Point Score $raw_valueExpressiveLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededExpressiveLanguage&dir=$raw_neededExpressiveLanguagedir&orderval=raw_needed&stdval=Expressive Language&sorttype=SIGNED\'>Screening Index $raw_neededExpressiveLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueExpressiveLanguage&dir=$valueExpressiveLanguagedir&orderval=value&stdval=Expressive Language&sorttype=SIGNED\'>Standard Score $valueExpressiveLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededExpressiveLanguage&dir=$neededExpressiveLanguagedir&orderval=needed&stdval=Expressive Language&sorttype=SIGNED\'>National Percentile $neededExpressiveLanguagearrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Expressive_Language_scale_diff Expressive_Language_scale_needed Expressive_Language_scale_value Expressive_Language_value Expressive_Language_needed Expressive_Language_raw_diff Expressive_Language_test_date Expressive_Language_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Expressive_Language_value &nbsp;</td>\r\n			<td class=c$Expressive_Language_needed >$Expressive_Language_needed &nbsp;</td>\r\n			<td>$Expressive_Language_scale_value &nbsp;</td>\r\n			<td>$Expressive_Language_scale_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',5),('ESP','Receptive Language','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueReceptiveLanguage&dir=$raw_valueReceptiveLanguagedir&orderval=raw_value&stdval=Receptive Language&sorttype=SIGNED\'>Point Score $raw_valueReceptiveLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededReceptiveLanguage&dir=$raw_neededReceptiveLanguagedir&orderval=raw_needed&stdval=Receptive Language&sorttype=SIGNED\'>Screening Index $raw_neededReceptiveLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReceptiveLanguage&dir=$valueReceptiveLanguagedir&orderval=value&stdval=Receptive Language&sorttype=SIGNED\'>Standard Score $valueReceptiveLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededReceptiveLanguage&dir=$neededReceptiveLanguagedir&orderval=needed&stdval=Receptive Language&sorttype=SIGNED\'>National Percentile $neededReceptiveLanguagearrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Receptive_Language_scale_diff Receptive_Language_scale_needed Receptive_Language_scale_value Receptive_Language_value Receptive_Language_needed Receptive_Language_raw_diff Receptive_Language_test_date Receptive_Language_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Receptive_Language_value &nbsp;</td>\r\n			<td class=c$Receptive_Language_needed >$Receptive_Language_needed &nbsp;</td>\r\n			<td>$Receptive_Language_scale_value &nbsp;</td>\r\n			<td>$Receptive_Language_scale_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',6),('ESP','Gross Motor','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueTestingdate&dir=$raw_valueTestingdatedir&orderval=raw_value&stdval=Testing date&sorttype=CHAR\'>Test Date $raw_valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=ChronologicalAge&dir=$ChronologicalAgedir&orderval=Chronological Age&stdval=&sorttype=CHAR\'>Chronological Age $ChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueGrossMotor&dir=$raw_valueGrossMotordir&orderval=raw_value&stdval=Gross Motor&sorttype=CHAR\'>Point Score $raw_valueGrossMotorarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededGrossMotor&dir=$raw_neededGrossMotordir&orderval=raw_needed&stdval=Gross Motor&sorttype=CHAR\'>Screening Index $raw_neededGrossMotorarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Gross_Motor_scale_diff Gross_Motor_scale_needed Gross_Motor_scale_value Gross_Motor_value Gross_Motor_needed Gross_Motor_raw_diff Gross_Motor_test_date Gross_Motor_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Gross_Motor_value &nbsp;</td>\r\n			<td class=c$Gross_Motor_needed >$Gross_Motor_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',7),('ESP','Fine Motor','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueTestingdate&dir=$raw_valueTestingdatedir&orderval=raw_value&stdval=Testing date&sorttype=CHAR\'>Test Date $raw_valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=ChronologicalAge&dir=$ChronologicalAgedir&orderval=Chronological Age&stdval=&sorttype=CHAR\'>Chronological Age $ChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueFineMotor&dir=$raw_valueFineMotordir&orderval=raw_value&stdval=Fine Motor&sorttype=CHAR\'>Point Score $raw_valueFineMotorarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededFineMotor&dir=$raw_neededFineMotordir&orderval=raw_needed&stdval=Fine Motor&sorttype=CHAR\'>Screening Index $raw_neededFineMotorarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Fine_Motor_scale_diff Fine_Motor_scale_needed Fine_Motor_scale_value Fine_Motor_value Fine_Motor_needed Fine_Motor_raw_diff Fine_Motor_test_date Fine_Motor_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Fine_Motor_value &nbsp;</td>\r\n			<td class=c$Fine_Motor_needed >$Fine_Motor_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',8),('ESP','Articulation','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n		<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Test Date $valueTestingdatearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=CHAR\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueArticulation&dir=$raw_valueArticulationdir&orderval=raw_value&stdval=Articulation&sorttype=CHAR\'>Raw Score $raw_valueArticulationarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_neededArticulation&dir=$raw_neededArticulationdir&orderval=raw_needed&stdval=Articulation&sorttype=CHAR\'>Descriptive Category $raw_neededArticulationarrow</a></th>\r\n		','aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value Articulation_scale_diff Articulation_scale_needed Articulation_scale_value Articulation_value Articulation_needed Articulation_raw_diff Articulation_test_date Articulation_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Testing_date_scale_value &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n			<td>$Articulation_value &nbsp;</td>\r\n			<td  class=$Articulation_needed >$Articulation_needed &nbsp;</td>\r\n			</tr>\\n\r\n		',9),('TerraNova','Reading','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelReading&dir=$gradelevelReadingdir&orderval=gradelevel&stdval=Reading&sorttype=SIGNED\'>Grade<br>Level $gradelevelReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueReading&dir=$raw_valueReadingdir&orderval=raw_value&stdval=Reading&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededReading&dir=$neededReadingdir&orderval=needed&stdval=Reading&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededReadingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Scale<br>Score</th> $valueReadingarrow</a>','aid fname lname gradelevel Reading_value Reading_scale_needed Reading_scale_value Reading_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Reading_class\\\">$Reading_value &nbsp;</td>\r\n			<td>$Reading_scale_needed &nbsp;</td>\r\n			<td>$Reading_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',1),('TerraNova','Vocabulary','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelVocabulary&dir=$gradelevelVocabularydir&orderval=gradelevel&stdval=Vocabulary&sorttype=SIGNED\'>Grade<br>Level $gradelevelVocabularyarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueVocabulary&dir=$raw_valueVocabularydir&orderval=raw_value&stdval=Vocabulary&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueVocabularyarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededVocabulary&dir=$neededVocabularydir&orderval=needed&stdval=Vocabulary&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededVocabularyarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueVocabulary&dir=$valueVocabularydir&orderval=value&stdval=Vocabulary&sorttype=SIGNED\'>Scale<br>Score</th> $valueVocabularyarrow</a>','aid fname lname gradelevel Vocabulary_value Vocabulary_scale_needed Vocabulary_scale_value Vocabulary_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Vocabulary_class\\\">$Vocabulary_value &nbsp;</td>\r\n			<td>$Vocabulary_scale_needed &nbsp;</td>\r\n			<td>$Vocabulary_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',2),('TerraNova','Reading Composite','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelReadingComposite&dir=$gradelevelReadingCompositedir&orderval=gradelevel&stdval=Reading Composite&sorttype=SIGNED\'>Grade<br>Level $gradelevelReadingCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueReadingComposite&dir=$raw_valueReadingCompositedir&orderval=raw_value&stdval=Reading Composite&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueReadingCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededReadingComposite&dir=$neededReadingCompositedir&orderval=needed&stdval=Reading Composite&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededReadingCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueReadingComposite&dir=$valueReadingCompositedir&orderval=value&stdval=Reading Composite&sorttype=SIGNED\'>Scale<br>Score</th> $valueReadingCompositearrow</a>','aid fname lname gradelevel Reading_Composite_value Reading_Composite_scale_needed Reading_Composite_scale_value Reading_Composite_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Reading_Composite_class\\\">$Reading_Composite_value &nbsp;</td>\r\n			<td>$Reading_Composite_scale_needed &nbsp;</td>\r\n			<td>$Reading_Composite_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',3),('TerraNova','Language','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelLanguage&dir=$gradelevelLanguagedir&orderval=gradelevel&stdval=Language&sorttype=SIGNED\'>Grade<br>Level $gradelevelLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueLanguage&dir=$raw_valueLanguagedir&orderval=raw_value&stdval=Language&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededLanguage&dir=$neededLanguagedir&orderval=needed&stdval=Language&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededLanguagearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueLanguage&dir=$valueLanguagedir&orderval=value&stdval=Language&sorttype=SIGNED\'>Scale<br>Score</th> $valueLanguagearrow</a>','aid fname lname gradelevel Language_value Language_scale_needed Language_scale_value Language_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Language_class\\\">$Language_value &nbsp;</td>\r\n			<td>$Language_scale_needed &nbsp;</td>\r\n			<td>$Language_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',4),('TerraNova','Language Mechanics','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelLanguageMechanics&dir=$gradelevelLanguageMechanicsdir&orderval=gradelevel&stdval=Language Mechanics&sorttype=SIGNED\'>Grade<br>Level $gradelevelLanguageMechanicsarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueLanguageMechanics&dir=$raw_valueLanguageMechanicsdir&orderval=raw_value&stdval=Language Mechanics&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueLanguageMechanicsarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededLanguageMechanics&dir=$neededLanguageMechanicsdir&orderval=needed&stdval=Language Mechanics&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededLanguageMechanicsarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueLanguageMechanics&dir=$valueLanguageMechanicsdir&orderval=value&stdval=Language Mechanics&sorttype=SIGNED\'>Scale<br>Score</th> $valueLanguageMechanicsarrow</a>','aid fname lname gradelevel Language_Mechanics_value Language_Mechanics_scale_needed Language_Mechanics_scale_value Language_Mechanics_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Language_Mechanics_class\\\">$Language_Mechanics_value &nbsp;</td>\r\n			<td>$Language_Mechanics_scale_needed &nbsp;</td>\r\n			<td>$Language_Mechanics_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',5),('TerraNova','Language Composite','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelLanguageComposite&dir=$gradelevelLanguageCompositedir&orderval=gradelevel&stdval=Language Composite&sorttype=SIGNED\'>Grade<br>Level $gradelevelLanguageCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueLanguageComposite&dir=$raw_valueLanguageCompositedir&orderval=raw_value&stdval=Language Composite&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueLanguageCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededLanguageComposite&dir=$neededLanguageCompositedir&orderval=needed&stdval=Language Composite&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededLanguageCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueLanguageComposite&dir=$valueLanguageCompositedir&orderval=value&stdval=Language Composite&sorttype=SIGNED\'>Scale<br>Score</th> $valueLanguageCompositearrow</a>','aid fname lname gradelevel Language_Composite_value Language_Composite_scale_needed Language_Composite_scale_value Language_Composite_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Language_Composite_class\\\">$Language_Composite_value &nbsp;</td>\r\n			<td>$Language_Composite_scale_needed &nbsp;</td>\r\n			<td>$Language_Composite_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',6),('TerraNova','Mathematics','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelMathematics&dir=$gradelevelMathematicsdir&orderval=gradelevel&stdval=Mathematics&sorttype=SIGNED\'>Grade<br>Level $gradelevelMathematicsarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueMathematics&dir=$raw_valueMathematicsdir&orderval=raw_value&stdval=Mathematics&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueMathematicsarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMathematics&dir=$neededMathematicsdir&orderval=needed&stdval=Mathematics&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededMathematicsarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMathematics&dir=$valueMathematicsdir&orderval=value&stdval=Mathematics&sorttype=SIGNED\'>Scale<br>Score</th> $valueMathematicsarrow</a>','aid fname lname gradelevel Mathematics_value Mathematics_scale_needed Mathematics_scale_value Mathematics_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Mathematics_class\\\">$Mathematics_value &nbsp;</td>\r\n			<td>$Mathematics_scale_needed &nbsp;</td>\r\n			<td>$Mathematics_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',7),('TerraNova','Math Computation','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelMathComputation&dir=$gradelevelMathComputationdir&orderval=gradelevel&stdval=Math Computation&sorttype=SIGNED\'>Grade<br>Level $gradelevelMathComputationarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueMathComputation&dir=$raw_valueMathComputationdir&orderval=raw_value&stdval=Math Computation&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueMathComputationarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMathComputation&dir=$neededMathComputationdir&orderval=needed&stdval=Math Computation&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededMathComputationarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMathComputation&dir=$valueMathComputationdir&orderval=value&stdval=Math Computation&sorttype=SIGNED\'>Scale<br>Score</th> $valueMathComputationarrow</a>','aid fname lname gradelevel Math_Computation_value Math_Computation_scale_needed Math_Computation_scale_value Math_Computation_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Math_Computation_class\\\">$Math_Computation_value &nbsp;</td>\r\n			<td>$Math_Computation_scale_needed &nbsp;</td>\r\n			<td>$Math_Computation_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',8),('TerraNova','Math Composite','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelMathComposite&dir=$gradelevelMathCompositedir&orderval=gradelevel&stdval=Math Composite&sorttype=SIGNED\'>Grade<br>Level $gradelevelMathCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueMathComposite&dir=$raw_valueMathCompositedir&orderval=raw_value&stdval=Math Composite&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueMathCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededMathComposite&dir=$neededMathCompositedir&orderval=needed&stdval=Math Composite&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededMathCompositearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueMathComposite&dir=$valueMathCompositedir&orderval=value&stdval=Math Composite&sorttype=SIGNED\'>Scale<br>Score</th> $valueMathCompositearrow</a>','aid fname lname gradelevel Math_Composite_value Math_Composite_scale_needed Math_Composite_scale_value Math_Composite_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Math_Composite_class\\\">$Math_Composite_value &nbsp;</td>\r\n			<td>$Math_Composite_scale_needed &nbsp;</td>\r\n			<td>$Math_Composite_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',9),('TerraNova','Total Score','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelTotalScore&dir=$gradelevelTotalScoredir&orderval=gradelevel&stdval=Total Score&sorttype=SIGNED\'>Grade<br>Level $gradelevelTotalScorearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueTotalScore&dir=$raw_valueTotalScoredir&orderval=raw_value&stdval=Total Score&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueTotalScorearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededTotalScore&dir=$neededTotalScoredir&orderval=needed&stdval=Total Score&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededTotalScorearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueTotalScore&dir=$valueTotalScoredir&orderval=value&stdval=Total Score&sorttype=SIGNED\'>Scale<br>Score</th> $valueTotalScorearrow</a>','aid fname lname gradelevel Total_Score_value Total_Score_scale_needed Total_Score_scale_value Total_Score_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Total_Score_class\\\">$Total_Score_value &nbsp;</td>\r\n			<td>$Total_Score_scale_needed &nbsp;</td>\r\n			<td>$Total_Score_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',10),('TerraNova','Science','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelScience&dir=$gradelevelSciencedir&orderval=gradelevel&stdval=Science&sorttype=SIGNED\'>Grade<br>Level $gradelevelSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueScience&dir=$raw_valueSciencedir&orderval=raw_value&stdval=Science&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=neededScience&dir=$neededSciencedir&orderval=needed&stdval=Science&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededSciencearrow</a></th>\r\n		<th><a href=\'{$url}sort=valueScience&dir=$valueSciencedir&orderval=value&stdval=Science&sorttype=SIGNED\'>Scale<br>Score</th> $valueSciencearrow</a>','aid fname lname gradelevel Science_value Science_scale_needed Science_scale_value Science_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Science_class\\\">$Science_value &nbsp;</td>\r\n			<td>$Science_scale_needed &nbsp;</td>\r\n			<td>$Science_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',11),('TerraNova','Social Studies','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelSocialStudies&dir=$gradelevelSocialStudiesdir&orderval=gradelevel&stdval=Social Studies&sorttype=SIGNED\'>Grade<br>Level $gradelevelSocialStudiesarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueSocialStudies&dir=$raw_valueSocialStudiesdir&orderval=raw_value&stdval=Social Studies&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueSocialStudiesarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededSocialStudies&dir=$neededSocialStudiesdir&orderval=needed&stdval=Social Studies&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededSocialStudiesarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSocialStudies&dir=$valueSocialStudiesdir&orderval=value&stdval=Social Studies&sorttype=SIGNED\'>Scale<br>Score</th> $valueSocialStudiesarrow</a>','aid fname lname gradelevel Social_Studies_value Social_Studies_scale_needed Social_Studies_scale_value Social_Studies_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Social_Studies_class\\\">$Social_Studies_value &nbsp;</td>\r\n			<td>$Social_Studies_scale_needed &nbsp;</td>\r\n			<td>$Social_Studies_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',12),('TerraNova','Spelling','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelSpelling&dir=$gradelevelSpellingdir&orderval=gradelevel&stdval=Spelling&sorttype=SIGNED\'>Grade<br>Level $gradelevelSpellingarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueSpelling&dir=$raw_valueSpellingdir&orderval=raw_value&stdval=Spelling&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueSpellingarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededSpelling&dir=$neededSpellingdir&orderval=needed&stdval=Spelling&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededSpellingarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueSpelling&dir=$valueSpellingdir&orderval=value&stdval=Spelling&sorttype=SIGNED\'>Scale<br>Score</th> $valueSpellingarrow</a>','aid fname lname gradelevel Spelling_value Spelling_scale_needed Spelling_scale_value Spelling_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Spelling_class\\\">$Spelling_value &nbsp;</td>\r\n			<td>$Spelling_scale_needed &nbsp;</td>\r\n			<td>$Spelling_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',13),('TerraNova','Word Analysis','\r\n		<th>Alaska ID</th>\r\n		<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n		<th><a href=\'{$url}sort=gradelevelWordAnalysis&dir=$gradelevelWordAnalysisdir&orderval=gradelevel&stdval=Word Analysis&sorttype=SIGNED\'>Grade<br>Level $gradelevelWordAnalysisarrow</a></th>\r\n		<th><a href=\'{$url}sort=raw_valueWordAnalysis&dir=$raw_valueWordAnalysisdir&orderval=raw_value&stdval=Word Analysis&sorttype=SIGNED\'>Normal<br>Curve<br>Equivalent $raw_valueWordAnalysisarrow</a></th>\r\n		<th><a href=\'{$url}sort=neededWordAnalysis&dir=$neededWordAnalysisdir&orderval=needed&stdval=Word Analysis&sorttype=SIGNED\'>National<br>Percentile<br>Rank $neededWordAnalysisarrow</a></th>\r\n		<th><a href=\'{$url}sort=valueWordAnalysis&dir=$valueWordAnalysisdir&orderval=value&stdval=Word Analysis&sorttype=SIGNED\'>Scale<br>Score</th> $valueWordAnalysisarrow</a>','aid fname lname gradelevel Word_Analysis_value Word_Analysis_scale_needed Word_Analysis_scale_value Word_Analysis_class ','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td class=\\\"$Word_Analysis_class\\\">$Word_Analysis_value &nbsp;</td>\r\n			<td>$Word_Analysis_scale_needed &nbsp;</td>\r\n			<td>$Word_Analysis_scale_value &nbsp;</td>\r\n			</tr>\\n\r\n		',14),('TerraNova','Overall','\r\n	\r\n<th>Student ID</th>\r\n<th><a href=\'{$url}sort=value&dir=$valuedir&orderval=value&stdval=&sorttype=CHAR\'>Name $valuearrow</a>Name</th>\r\n<th><a href=\'{$url}sort=value&dir=$valuedir&orderval=value&stdval=&sorttype=CHAR\'>Grade<br>Level $valuearrow</a></th>\r\n<th><a href=\'{$url}sort=value&dir=$valuedir&orderval=value&stdval=&sorttype=CHAR\'>Score Type $valuearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueReading&dir=$raw_valueReadingdir&orderval=raw_value&stdval=Reading&sorttype=SIGNED\'>Reading $raw_valueReadingarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueVocabulary&dir=$raw_valueVocabularydir&orderval=raw_value&stdval=Vocabulary&sorttype=SIGNED\'>Vocabulary $raw_valueVocabularyarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueReadingComposite&dir=$raw_valueReadingCompositedir&orderval=raw_value&stdval=Reading Composite&sorttype=SIGNED\'>Reading Composite $raw_valueReadingCompositearrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=raw_valueLanguage&dir=$raw_valueLanguagedir&orderval=raw_value&stdval=Language&sorttype=SIGNED\'>Language $raw_valueLanguagearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueLanguageMechanics&dir=$raw_valueLanguageMechanicsdir&orderval=raw_value&stdval=Language Mechanics&sorttype=SIGNED\'>Language<br>Mechanics $raw_valueLanguageMechanicsarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueLanguageComposite&dir=$raw_valueLanguageCompositedir&orderval=raw_value&stdval=Language Composite&sorttype=SIGNED\'>Language<br>Composite $raw_valueLanguageCompositearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueMathematics&dir=$raw_valueMathematicsdir&orderval=raw_value&stdval=Mathematics&sorttype=SIGNED\'>Mathematics $raw_valueMathematicsarrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=raw_valueMathComputation&dir=$raw_valueMathComputationdir&orderval=raw_value&stdval=Math Computation&sorttype=SIGNED\'>Mathematics<br>Computation $raw_valueMathComputationarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueMathComposite&dir=$raw_valueMathCompositedir&orderval=raw_value&stdval=Math Composite&sorttype=SIGNED\'>Mathematics<br>Composite $raw_valueMathCompositearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueTotalScore&dir=$raw_valueTotalScoredir&orderval=raw_value&stdval=Total Score&sorttype=SIGNED\'>Total<br>Score $raw_valueTotalScorearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueScience&dir=$raw_valueSciencedir&orderval=raw_value&stdval=Science&sorttype=SIGNED\'>Science $raw_valueSciencearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueSocialStudies&dir=$raw_valueSocialStudiesdir&orderval=raw_value&stdval=Social Studies&sorttype=SIGNED\'>Social Studies $raw_valueSocialStudiesarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueSpelling&dir=$raw_valueSpellingdir&orderval=raw_value&stdval=Spelling&sorttype=SIGNED\'>Spelling $raw_valueSpellingarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueWordAnalysis&dir=$raw_valueWordAnalysisdir&orderval=raw_value&stdval=Word Analysis&sorttype=SIGNED\'>Word<br>Analysis $raw_valueWordAnalysisarrow</a></th>\r\n\r\n','aid fname lname gradelevel Reading Reading_scale_needed Reading_scale_value Reading_raw_needed Reading_value Reading_level Vocabulary Vocabulary_scale_needed Vocabulary_scale_value Vocabulary_raw_needed Vocabulary_value Vocabulary_level Reading_Composite Reading_Composite_scale_needed Reading_Composite_scale_value Reading_Composite_raw_needed Reading_Composite_value Reading_Composite_level Language Language_scale_needed Language_scale_value Language_raw_needed Language_value Language_level Language_Mechanics Language_Mechanics_scale_needed Language_Mechanics_scale_value Language_Mechanics_raw_needed Language_Mechanics_value Language_Mechanics_level Language_Composite Language_Composite_scale_needed Language_Composite_scale_value Language_Composite_raw_needed Language_Composite_value Language_Composite_level Mathematics Mathematics_scale_needed Mathematics_scale_value Mathematics_raw_needed Mathematics_value Mathematics_level Math_Computation Math_Computation_scale_needed Math_Computation_scale_value Math_Computation_raw_needed Math_Computation_value Math_Computation_level Math_Composite Math_Composite_scale_needed Math_Composite_scale_value Math_Composite_raw_needed Math_Composite_value Math_Composite_level Total_Score Total_Score_scale_needed Total_Score_scale_value Total_Score_raw_needed Total_Score_value Total_Score_level Science Science_scale_needed Science_scale_value Science_raw_needed Science_value Science_level Social_Studies Social_Studies_scale_needed Social_Studies_scale_value Social_Studies_raw_needed Social_Studies_value Social_Studies_level Spelling Spelling_scale_needed Spelling_scale_value Spelling_raw_needed Spelling_value Spelling_level Word_Analysis Word_Analysis_scale_needed Word_Analysis_scale_value Word_Analysis_raw_needed Word_Analysis_value Word_Analysis_level gender ethnicity NSLPEligible LEP sped sec504','<tr>\r\n<td rowspan=3><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n<td rowspan=3>$fname $lname</td>\r\n<td rowspan=3>$gradelevel &nbsp;</td>\r\n<td>NP</td>\r\n\r\n<td>$Reading_scale_needed &nbsp;</td>\r\n<td>$Vocabulary_scale_needed &nbsp;</td>\r\n<td>$Reading_Composite_scale_needed &nbsp;</td>\r\n<td>$Language_scale_needed &nbsp;</td>\r\n<td>$Language_Mechanics_scale_needed &nbsp;</td>\r\n<td>$Language_Composite_scale_needed &nbsp;</td>\r\n<td>$Mathematics_scale_needed &nbsp;</td>\r\n<td>$Math_Computation_scale_needed &nbsp;</td>\r\n<td>$Math_Composite_scale_needed &nbsp;</td>\r\n<td>$Total_Score_scale_needed &nbsp;</td>\r\n<td>$Science_scale_needed &nbsp;</td>\r\n<td>$Social_Studies_scale_needed &nbsp;</td>\r\n<td>$Spelling_scale_needed &nbsp;</td>\r\n<td>$Word_Analysis_scale_needed &nbsp;</td>\r\n</tr>\r\n\r\n<tr>\r\n<td>NCE</td>\r\n\r\n<td class=\\\"$Reading_level\\\">$Reading_value &nbsp;</td>\r\n<td class=\\\"$Vocabulary_level\\\">$Vocabulary_value &nbsp;</td>\r\n<td class=\\\"$Reading_Composite_level\\\">$Reading_Composite_value &nbsp;</td>\r\n<td class=\\\"$Language_level\\\">$Language_value &nbsp;</td>\r\n<td class=\\\"$Language_Mechanics_level\\\">$Language_Mechanics_value &nbsp;</td>\r\n<td class=\\\"$Language_Composite_level\\\">$Language_Composite_value &nbsp;</td>\r\n<td class=\\\"$Mathematics_level\\\">$Mathematics_value &nbsp;</td>\r\n<td class=\\\"$Math_Computation_level\\\">$Math_Computation_value &nbsp;</td>\r\n<td class=\\\"$Math_Composite_level\\\">$Math_Composite_value &nbsp;</td>\r\n<td class=\\\"$Total_Score_level\\\">$Total_Score_value &nbsp;</td>\r\n<td class=\\\"$Science_level\\\">$Science_value &nbsp;</td>\r\n<td class=\\\"$Social_Studies_level\\\">$Social_Studies_value &nbsp;</td>\r\n<td class=\\\"$Spelling_level\\\">$Spelling_value &nbsp;</td>\r\n<td class=\\\"$Word_Analysis_level\\\">$Word_Analysis_value &nbsp;</td>\r\n\r\n\r\n</tr>\r\n\r\n<tr>\r\n<td>Scale Score</td>\r\n\r\n<td>$Reading_scale_value &nbsp;</td>\r\n<td>$Vocabulary_scale_value &nbsp;</td>\r\n<td>$Reading_Composite_scale_value &nbsp;</td>\r\n<td>$Language_scale_value &nbsp;</td>\r\n<td>$Language_Mechanics_scale_value &nbsp;</td>\r\n<td>$Language_Composite_scale_value &nbsp;</td>\r\n<td>$Mathematics_scale_value &nbsp;</td>\r\n<td>$Math_Computation_scale_value &nbsp;</td>\r\n<td>$Math_Composite_scale_value &nbsp;</td>\r\n<td>$Total_Score_scale_value &nbsp;</td>\r\n<td>$Science_scale_value &nbsp;</td>\r\n<td>$Social_Studies_scale_value &nbsp;</td>\r\n<td>$Spelling_scale_value &nbsp;</td>\r\n<td>$Word_Analysis_scale_value &nbsp;</td>\r\n</tr>\r\n',0),('ELP','Overall','\r\n	\r\n<th>Alaska ID</th>\r\n<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Testing Grade $gradelevelarrow</a></th>\r\n<th><a href=\'{$url}sort=valueListeningScaleScore&dir=$valueListeningScaleScoredir&orderval=value&stdval=Listening Scale Score&sorttype=CHAR\'>Listening Standard Score $valueListeningScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueSpeakingScaleScore&dir=$valueSpeakingScaleScoredir&orderval=value&stdval=Speaking Scale Score&sorttype=CHAR\'>Speaking Standard Score $valueSpeakingScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueReadingScaleScore&dir=$valueReadingScaleScoredir&orderval=value&stdval=Reading Scale Score&sorttype=CHAR\'>Reading Standard Score $valueReadingScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueWritingScaleScore&dir=$valueWritingScaleScoredir&orderval=value&stdval=Writing Scale Score&sorttype=CHAR\'>Writing Standard Score $valueWritingScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueComprehensionScaleScore&dir=$valueComprehensionScaleScoredir&orderval=value&stdval=Comprehension Scale Score&sorttype=CHAR\'>Comprehension Standard Score $valueComprehensionScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueOverallScaleScore&dir=$valueOverallScaleScoredir&orderval=value&stdval=Overall Scale Score&sorttype=CHAR\'>Overall Standard Score $valueOverallScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueListeningScaleScore&dir=$valueListeningScaleScoredir&orderval=value&stdval=Listening Scale Score&sorttype=CHAR\'>ELP Listening Proficiency Level $valueListeningScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueSpeakingScaleScore&dir=$valueSpeakingScaleScoredir&orderval=value&stdval=Speaking Scale Score&sorttype=CHAR\'>ELP Speaking Proficiency Level $valueSpeakingScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueReadingScaleScore&dir=$valueReadingScaleScoredir&orderval=value&stdval=Reading Scale Score&sorttype=CHAR\'>ELP Reading Proficiency Level $valueReadingScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueWritingScaleScore&dir=$valueWritingScaleScoredir&orderval=value&stdval=Writing Scale Score&sorttype=CHAR\'>ELP Writing Proficiency Level $valueWritingScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueComprehensionScaleScore&dir=$valueComprehensionScaleScoredir&orderval=value&stdval=Comprehension Scale Score&sorttype=CHAR\'>ELP Comprehension Proficiency Level $valueComprehensionScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueOverallScaleScore&dir=$valueOverallScaleScoredir&orderval=value&stdval=Overall Scale Score&sorttype=CHAR\'>ELP Overall Proficiency Level $valueOverallScaleScorearrow</a></th>\r\n<th><a href=\'{$url}sort=valueELPMadeProgress&dir=$valueELPMadeProgressdir&orderval=value&stdval=ELP Made Progress&sorttype=CHAR\'>ELP Made Progress $valueELPMadeProgressarrow</a></th>\r\n\r\n','aid fname lname gradelevel Listening_Scale_Score_scale_value Speaking_Scale_Score_scale_value Reading_Scale_Score_scale_value Writing_Scale_Score_scale_value Comprehension_Scale_Score_scale_value Overall_Scale_Score_scale_value Overall_Scale_Score_level Listening_Scale_Score_level Speaking_Scale_Score_level Reading_Scale_Score_level Writing_Scale_Score_level Comprehension_Scale_Score_level Overall_Scale_Score_level ELP_Made_Progress_scale_value','<tr>\r\n			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n<td class=\\\"$Listening_Scale_Score_level\\\">$Listening_Scale_Score_scale_value &nbsp;</td>\r\n<td class=\\\"$Speaking_Scale_Score_level\\\">$Speaking_Scale_Score_scale_value &nbsp;</td>\r\n<td class=\\\"$Reading_Scale_Score_level\\\">$Reading_Scale_Score_scale_value &nbsp;</td>\r\n<td class=\\\"$Writing_Scale_Score_level\\\">$Writing_Scale_Score_scale_value &nbsp;</td>\r\n<td class=\\\"$Comprehension_Scale_Score_level\\\">$Comprehension_Scale_Score_scale_value &nbsp;</td>\r\n<td class=\\\"$Overall_Scale_Score_level\\\">$Overall_Scale_Score_scale_value &nbsp;</td>\r\n<td>$Listening_Scale_Score_level &nbsp;</td>\r\n<td>$Speaking_Scale_Score_level &nbsp;</td>\r\n<td>$Reading_Scale_Score_level &nbsp;</td>\r\n<td>$Writing_Scale_Score_level &nbsp;</td>\r\n<td>$Comprehension_Scale_Score_level &nbsp;</td>\r\n<td>$Overall_Scale_Score_level &nbsp;</td>\r\n<td>$ELP_Made_Progress_scale_value &nbsp;</td></tr>\\n',0),('PPVT','Overall','\r\n	\r\n\r\n<th>Alaska ID</th>\r\n<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Testing Grade $gradelevelarrow</a></th>\r\n<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Pre Testing Date $fnamearrow</a></th>\r\n<th><a href=\'{$url}sort=valueCA&dir=$valueCAdir&orderval=value&stdval=CA&sorttype=CHAR\'>Pre CA years-months $valueCAarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePreRS&dir=$valuePreRSdir&orderval=value&stdval=PreRS&sorttype=SIGNED\'>Pre RS $valuePreRSarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePreSS&dir=$valuePreSSdir&orderval=value&stdval=PreSS&sorttype=SIGNED\'>Pre SS $valuePreSSarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePrePercentile&dir=$valuePrePercentiledir&orderval=value&stdval=PrePercentile&sorttype=SIGNED\'>Pre Percentile $valuePrePercentilearrow</a></th>\r\n<th><a href=\'{$url}sort=valuePreNCE&dir=$valuePreNCEdir&orderval=value&stdval=PreNCE&sorttype=SIGNED\'>Pre NCE $valuePreNCEarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePreGrowthScale&dir=$valuePreGrowthScaledir&orderval=value&stdval=PreGrowthScale&sorttype=SIGNED\'>Pre Growth Scale Value $valuePreGrowthScalearrow</a></th>\r\n<th><a href=\'{$url}sort=valuePreAE&dir=$valuePreAEdir&orderval=value&stdval=PreAE&sorttype=CHAR\'>Pre AE $valuePreAEarrow</a></th>\r\n<th><a href=\'{$url}sort=valueDiff&dir=$valueDiffdir&orderval=value&stdval=Diff&sorttype=CHAR\'>Pre Difference between CA and AE in years-months $valueDiffarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePreRange&dir=$valuePreRangedir&orderval=value&stdval=Pre Range&sorttype=CHAR\'>Pre Range in Years $valuePreRangearrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostTesting&dir=$valuePostTestingdir&orderval=value&stdval=Post Testing&sorttype=CHAR\'>Post Testing Date $valuePostTestingarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostRS&dir=$valuePostRSdir&orderval=value&stdval=PostRS&sorttype=CHAR\'>Post CA years-months $valuePostRSarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostSS&dir=$valuePostSSdir&orderval=value&stdval=PostSS&sorttype=SIGNED\'>Post RS $valuePostSSarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostSS&dir=$valuePostSSdir&orderval=value&stdval=PostSS&sorttype=SIGNED\'>Post SS $valuePostSSarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostPercentile&dir=$valuePostPercentiledir&orderval=value&stdval=PostPercentile&sorttype=SIGNED\'>Post Percentile $valuePostPercentilearrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostNCE&dir=$valuePostNCEdir&orderval=value&stdval=PostNCE&sorttype=SIGNED\'>Post NCE $valuePostNCEarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostGrowScale&dir=$valuePostGrowScaledir&orderval=value&stdval=PostGrowScale&sorttype=SIGNED\'>Post Growth Scale Value $valuePostGrowScalearrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostAE&dir=$valuePostAEdir&orderval=value&stdval=PostAE&sorttype=CHAR\'>Post AE $valuePostAEarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostDiff&dir=$valuePostDiffdir&orderval=value&stdval=Post Diff&sorttype=CHAR\'>Post Difference between CA and AE in years-months $valuePostDiffarrow</a></th>\r\n<th><a href=\'{$url}sort=valuePostRange&dir=$valuePostRangedir&orderval=value&stdval=Post Range&sorttype=CHAR\'>Post Range in Years $valuePostRangearrow</a></th>\r\n\r\n','aid fname lname gradelevel bday Testing_date_scale_value CA_scale_value PreRS_scale_value PreSS_scale_value PreAE_scale_value Diff_scale_value Pre_Range_scale_value Post_Testing_date_scale_value Post_CA_scale_value PostRS_scale_value PostSS_scale_value PostAE_scale_value Post_Diff_scale_value Post_Range_date_scale_value PostPercentile_scale_value PostNCE_scale_value PostGrowScale_scale_value PrePercentile_scale_value PreNCE_scale_value PreGrowthScale_scale_value PrePercentile_scale_value PreGrowthScale_scale_value PreNCE_scale_value','<tr>\r\n			<td nowrap><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td nowrap>$fname $lname</td>\r\n			<td nowrap>$gradelevel &nbsp;</td>\r\n			<td nowrap>$bday &nbsp;</td>\r\n<td nowrap>$Testing_date_scale_value &nbsp;</td>\r\n<td nowrap>$CA_scale_value &nbsp;</td>\r\n<td nowrap>$PreRS_scale_value &nbsp;</td>\r\n<td nowrap>$PreSS_scale_value &nbsp;</td>\r\n<td nowrap>$PrePercentile_scale_value &nbsp;</td>\r\n<td nowrap>$PreNCE_scale_value &nbsp;</td>\r\n<td nowrap>$PreGrowthScale_scale_value &nbsp;</td>\r\n<td nowrap>$PreAE_scale_value &nbsp;</td>\r\n<td nowrap>$Diff_scale_value &nbsp;</td>\r\n<td nowrap>$Pre_Range_scale_value &nbsp;</td>\r\n<td nowrap>$Post_Testing_date_scale_value &nbsp;</td>\r\n<td nowrap>$Post_CA_scale_value &nbsp;</td>\r\n<td nowrap>$PostRS_scale_value &nbsp;</td>\r\n<td nowrap>$PostSS_scale_value &nbsp;</td>\r\n<td nowrap>$PostPercentile_scale_value &nbsp;</td>\r\n<td nowrap>$PostNCE_scale_value &nbsp;</td>\r\n<td nowrap>$PostGrowScale_scale_value &nbsp;</td>\r\n<td nowrap>$PostAE_scale_value &nbsp;</td>\r\n<td nowrap>$Post_Diff_scale_value &nbsp;</td>\r\n<td nowrap>$Post_Range_scale_value &nbsp;</td>\r\n</tr>\\n',0),('ESP','Overall','\r\n	\r\n\r\n<th>Alaska ID</th>\r\n<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Testing Grade $gradelevelarrow</a></th>\r\n<th><a href=\'{$url}sort=bday&dir=$bdaydir&orderval=bday&stdval=&sorttype=CHAR\'>Birthdate $bdayarrow</a></th>\r\n<th><a href=\'{$url}sort=valueChronologicalAge&dir=$valueChronologicalAgedir&orderval=value&stdval=Chronological Age&sorttype=SIGNED\'>Chronological Age $valueChronologicalAgearrow</a></th>\r\n<th><a href=\'{$url}sort=valueTestingdate&dir=$valueTestingdatedir&orderval=value&stdval=Testing date&sorttype=CHAR\'>Testing Date $valueTestingdatearrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=valueVerbalConcepts&dir=$valueVerbalConceptsdir&orderval=value&stdval=Verbal Concepts&sorttype=SIGNED\'>Verbal Concepts Standard Score $valueVerbalConceptsarrow</a></th>\r\n<th><a href=\'{$url}sort=valueVisualDiscrimination&dir=$valueVisualDiscriminationdir&orderval=value&stdval=Visual Discrimination&sorttype=SIGNED\'>Visual Discrimination Standard Score $valueVisualDiscriminationarrow</a></th>\r\n<th><a href=\'{$url}sort=valueLogicalRelations&dir=$valueLogicalRelationsdir&orderval=value&stdval=Logical Relations&sorttype=SIGNED\'>Logical Relations Standard Score $valueLogicalRelationsarrow</a></th>\r\n<th><a href=\'{$url}sort=valueBasicSchoolSkills&dir=$valueBasicSchoolSkillsdir&orderval=value&stdval=Basic School Skills&sorttype=SIGNED\'>Basic School Skills Standard Score $valueBasicSchoolSkillsarrow</a></th>\r\n<th><a href=\'{$url}sort=valueExpressiveLanguage&dir=$valueExpressiveLanguagedir&orderval=value&stdval=Expressive Language&sorttype=SIGNED\'>Expressive Language Standard Score $valueExpressiveLanguagearrow</a></th>\r\n<th><a href=\'{$url}sort=valueReceptiveLanguage&dir=$valueReceptiveLanguagedir&orderval=value&stdval=Receptive Language&sorttype=SIGNED\'>Receptive Language Standard Score $valueReceptiveLanguagearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueGrossMotor&dir=$raw_valueGrossMotordir&orderval=raw_value&stdval=Gross Motor&sorttype=SIGNED\'>Gross Motor Point Score $raw_valueGrossMotorarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueFineMotor&dir=$raw_valueFineMotordir&orderval=raw_value&stdval=Fine Motor&sorttype=SIGNED\'>Fine Motor Point Score $raw_valueFineMotorarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_valueArticulation&dir=$raw_valueArticulationdir&orderval=raw_value&stdval=Articulation&sorttype=SIGNED\'>Articulation Category $raw_valueArticulationarrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=raw_neededVerbalConcepts&dir=$raw_neededVerbalConceptsdir&orderval=raw_needed&stdval=Verbal Concepts&sorttype=CHAR\'>Verbal Concepts Screening Index $raw_neededVerbalConceptsarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededVisualDiscrimination&dir=$raw_neededVisualDiscriminationdir&orderval=raw_needed&stdval=Visual Discrimination&sorttype=SIGNED\'>Visual Discrimination Screening Index $raw_neededVisualDiscriminationarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededLogicalRelations&dir=$raw_neededLogicalRelationsdir&orderval=raw_needed&stdval=Logical Relations&sorttype=SIGNED\'>Logical Relations Screening Index $raw_neededLogicalRelationsarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededBasicSchoolSkills&dir=$raw_neededBasicSchoolSkillsdir&orderval=raw_needed&stdval=Basic School Skills&sorttype=SIGNED\'>Basic School Skills Screening Index $raw_neededBasicSchoolSkillsarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededExpressiveLanguage&dir=$raw_neededExpressiveLanguagedir&orderval=raw_needed&stdval=Expressive Language&sorttype=SIGNED\'>Expressive Language Screening Index $raw_neededExpressiveLanguagearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededReceptiveLanguage&dir=$raw_neededReceptiveLanguagedir&orderval=raw_needed&stdval=Receptive Language&sorttype=SIGNED\'>Receptive Language Screening Index $raw_neededReceptiveLanguagearrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededGrossMotor&dir=$raw_neededGrossMotordir&orderval=raw_needed&stdval=Gross Motor&sorttype=SIGNED\'>Gross Motor Screening Index $raw_neededGrossMotorarrow</a></th>\r\n<th><a href=\'{$url}sort=raw_neededFineMotor&dir=$raw_neededFineMotordir&orderval=raw_needed&stdval=Fine Motor&sorttype=SIGNED\'>Fine Motor Screening Index $raw_neededFineMotorarrow</a></th>\r\n\r\n','aid fname lname gradelevel bday Testing_date_scale_value Verbal_Concepts_scale_value Visual_Discrimination_scale_value Logical_Relations_scale_value Basic_School_Skills_scale_value Expressive_Language_scale_value Receptive_Language_scale_value Gross_Motor_scale_value Fine_Motor_scale_value Articulation_scale_value  Verbal_Concepts_needed Visual_Discrimination_needed Logical_Relations_needed Basic_School_Skills_needed Expressive_Language_needed Receptive_Language_needed Gross_Motor_needed Fine_Motor_needed Articulation_needed Fine_Motor_value Gross_Motor_value Articulation_value Chronological_Age_scale_value','<tr>\r\n		<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n			<td>$fname $lname</td>\r\n			<td>$gradelevel &nbsp;</td>\r\n			<td>$bday &nbsp;</td>\r\n			<td>$Chronological_Age_scale_value &nbsp;</td>\r\n<td>$Testing_date_scale_value &nbsp;</td>\r\n<td class=\\\"c$Verbal_Concepts_needed\\\">$Verbal_Concepts_scale_value &nbsp;</td>\r\n<td class=\\\"c$Visual_Discrimination_needed\\\">$Visual_Discrimination_scale_value &nbsp;</td>\r\n<td class=\\\"c$Logical_Relations_needed\\\">$Logical_Relations_scale_value &nbsp;</td>\r\n<td class=\\\"c$Basic_School_Skills_needed\\\">$Basic_School_Skills_scale_value &nbsp;</td>\r\n<td class=\\\"c$Expressive_Language_needed\\\">$Expressive_Language_scale_value &nbsp;</td>\r\n<td class=\\\"c$Receptive_Language_needed\\\">$Receptive_Language_scale_value &nbsp;</td>\r\n<td class=\\\"c$Gross_Motor_needed\\\">$Gross_Motor_value &nbsp;</td>\r\n<td class=\\\"c$Fine_Motor_needed\\\">$Fine_Motor_value &nbsp;</td>\r\n<td class=\\\"$Articulation_needed\\\">$Articulation_needed &nbsp;</td>\r\n\r\n<td >$Verbal_Concepts_needed &nbsp;</td>\r\n<td>$Visual_Discrimination_needed &nbsp;</td>\r\n<td>$Logical_Relations_needed &nbsp;</td>\r\n<td>$Basic_School_Skills_needed &nbsp;</td>\r\n<td>$Expressive_Language_needed &nbsp;</td>\r\n<td>$Receptive_Language_needed &nbsp;</td>\r\n<td>$Gross_Motor_needed &nbsp;</td>\r\n<td>$Fine_Motor_needed &nbsp;</td>\r\n\r\n</tr>\\n',0),('HSGQE','Overall','\r\n	\r\n<th>Alaska ID</th>\r\n<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade Level $gradelevelarrow</a></th>\r\n<th><a href=\'{$url}sort=levelReading&dir=$levelReadingdir&orderval=level&stdval=Reading&sorttype=CHAR\'>Reading Proficiency $levelReadingarrow</a></th>\r\n<th><a href=\'{$url}sort=levelWriting&dir=$levelWritingdir&orderval=level&stdval=Writing&sorttype=CHAR\'>Writing Proficiency $levelWritingarrow</a></th>\r\n<th><a href=\'{$url}sort=levelMath&dir=$levelMathdir&orderval=level&stdval=Math&sorttype=CHAR\'>Math Proficiency $levelMatharrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=CHAR\'>Reading<br>Scale Scores $valueReadingarrow</a></th>\r\n<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=CHAR\'>Writing<br>Scale Scores $valueWritingarrow</a></th>\r\n<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=CHAR\'>Math<br>Scale Scores $valueMatharrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=gender&dir=$genderdir&orderval=gender&stdval=&sorttype=CHAR\'>Gender $genderarrow</a></th>\r\n<th><a href=\'{$url}sort=ethnicity&dir=$ethnicitydir&orderval=ethnicity&stdval=&sorttype=CHAR\'>Ethnicity $ethnicityarrow</a></th>\r\n<th><a href=\'{$url}sort=NSLPEligible&dir=$NSLPEligibledir&orderval=NSLPEligible&stdval=&sorttype=CHAR\'>Economically<br>Disadvantage $NSLPEligiblearrow</a></th>\r\n<th><a href=\'{$url}sort=lep&dir=$lepdir&orderval=lep&stdval=&sorttype=CHAR\'>LEP $leparrow</a></th>\r\n<th><a href=\'{$url}sort=sped&dir=$speddir&orderval=sped&stdval=&sorttype=CHAR\'>SPED $spedarrow</a></th>\r\n<th><a href=\'{$url}sort=sec504&dir=$sec504dir&orderval=sec504&stdval=&sorttype=CHAR\'>SEC $sec504arrow</a></th>\r\n\r\n\r\n','aid fname lname gradelevel Reading_class Reading_level Reading Writing_class Writing_level  Writing Math_class Math_level Math gender ethnicity NSLPEligible LEP sped sec504','<tr>\r\n<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n<td>$fname $lname</td>\r\n<td>$gradelevel &nbsp;</td>\r\n<td>$Reading_level &nbsp;</td>\r\n<td>$Writing_level &nbsp;</td>\r\n<td>$Math_level &nbsp;</td>\r\n<td class=\\\"$Reading_class\\\">$Reading &nbsp;</td>\r\n<td class=\\\"$Writing_class\\\">$Writing &nbsp;</td>\r\n<td class=\\\"$Math_class\\\">$Math &nbsp;</td>\r\n\r\n<td>$gender</td><td>$ethnicity &nbsp;</td><td>$NSLPEligible &nbsp;</td><td>$LEP &nbsp;</td>\r\n<td>$sped &nbsp;</td><td>$sec504 &nbsp;</td></tr>\\n',0),('SBA','Overall','\r\n	\r\n<th>Alaska ID</th>\r\n<th><a href=\'{$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=&sorttype=CHAR\'>Name $fnamearrow</a></th>\r\n<th><a href=\'{$url}sort=gradelevel&dir=$gradeleveldir&orderval=gradelevel&stdval=&sorttype=SIGNED\'>Grade<br>Level $gradelevelarrow</a></th>\r\n<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Reading<br>Proficiency $valueReadingarrow</a></th>\r\n<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=SIGNED\'>Writing<br>Proficiency $valueWritingarrow</a></th>\r\n<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=SIGNED\'>Math<br>Proficiency $valueMatharrow</a></th>\r\n<th><a href=\'{$url}sort=valueScience&dir=$valueSciencedir&orderval=value&stdval=Science&sorttype=SIGNED\'>Science<br>Proficiency $valueSciencearrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=valueReading&dir=$valueReadingdir&orderval=value&stdval=Reading&sorttype=SIGNED\'>Reading<br>Scale Scores $valueReadingarrow</a></th>\r\n<th><a href=\'{$url}sort=valueWriting&dir=$valueWritingdir&orderval=value&stdval=Writing&sorttype=SIGNED\'>Writing<br>Scale Scores $valueWritingarrow</a></th>\r\n<th><a href=\'{$url}sort=valueMath&dir=$valueMathdir&orderval=value&stdval=Math&sorttype=SIGNED\'>Math<br>Scale Scores $valueMatharrow</a></th>\r\n<th><a href=\'{$url}sort=valueScience&dir=$valueSciencedir&orderval=value&stdval=Science&sorttype=SIGNED\'>Science<br>Scale Scores $valueSciencearrow</a></th>\r\n\r\n<th><a href=\'{$url}sort=gender&dir=$genderdir&orderval=gender&stdval=&sorttype=CHAR\'>Gender $genderarrow</a></th>\r\n<th><a href=\'{$url}sort=ethnicity&dir=$ethnicitydir&orderval=ethnicity&stdval=&sorttype=CHAR\'>Ethnicity $ethnicityarrow</a></th>\r\n<th><a href=\'{$url}sort=NSLPEligible&dir=$NSLPEligibledir&orderval=NSLPEligible&stdval=&sorttype=CHAR\'>Economically<br>Disadvantage $NSLPEligiblearrow</a></th>\r\n<th><a href=\'{$url}sort=LEP&dir=$LEPdir&orderval=LEP&stdval=&sorttype=CHAR\'>LEP $LEParrow</a></th>\r\n<th><a href=\'{$url}sort=sped&dir=$speddir&orderval=sped&stdval=&sorttype=CHAR\'>SPED $spedarrow</a></th>\r\n<th><a href=\'{$url}sort=sec504&dir=$sec504dir&orderval=sec504&stdval=&sorttype=CHAR\'>504 $sec504arrow</a></th>\r\n\r\n','aid fname lname gradelevel Reading_level Reading_class Reading Writing_level Writing_class Writing Math_level Math_class Math Science_level Science_class Science gender ethnicity NSLPEligible LEP sped sec504','<tr>\r\n<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>\r\n<td>$fname $lname</td><td>$gradelevel &nbsp;</td>\r\n<td>$Reading_level &nbsp;</td>\r\n<td>$Writing_level &nbsp;</td>\r\n<td>$Math_level &nbsp;</td>\r\n<td>$Science_level &nbsp;</td>\r\n\r\n<td class=\\\"$Reading_class\\\">$Reading &nbsp;</td>\r\n<td class=\\\"$Writing_class\\\">$Writing &nbsp;</td>\r\n<td class=\\\"$Math_class\\\">$Math &nbsp;</td>\r\n<td class=\\\"$Science_class\\\">$Science &nbsp;</td>\r\n\r\n<td>$gender</td><td>$ethnicity &nbsp;</td>\r\n<td>$NSLPEligible &nbsp;</td><td>$LEP &nbsp;</td>\r\n<td>$sped &nbsp;</td>\r\n<td>$sec504 &nbsp;</td></tr>\\n',0);
/*!40000 ALTER TABLE `testreports` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tests`
--

DROP TABLE IF EXISTS `tests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tests` (
  `id` varchar(254) NOT NULL default '',
  `name` varchar(254) NOT NULL default '',
  `legend` text NOT NULL,
  `ord` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tests`
--

LOCK TABLES `tests` WRITE;
/*!40000 ALTER TABLE `tests` DISABLE KEYS */;
INSERT INTO `tests` (`id`, `name`, `legend`, `ord`) VALUES ('ELP','ELP','<table>\r\n  <tr><td colspan=2>Proficiency Levels </td></tr>\r\n  <tr><td class=BL>1-Beginner Low (BL)</td><td class=IH>4-Intermediate High (IH) </td></tr>\r\n  <tr><td class=BH>2-Beginner High (BH)</td><td class=PR>5-Proficient (PR) </td></tr>\r\n  <tr><td class=IL>3-Intermediate Low (IL)</td><td class=PH>6-Proficient High (PH) </td></tr>\r\n</table>',3),('HSGQE','HSGQE','<table border=0 cellpadding=3> <tr>\r\n<th>Legend:</th>\r\n<td class=Proficient>Proficient</td>\r\n<td class=Not_Proficient>Not Proficient</td>\r\n</tr></table>',2),('SBA','SBA','<table border=0 cellpadding=3> <tr>\r\n<th>Legend:</th>\r\n<td class=Adv>Advanced</td>\r\n<td class=Prof>Proficient</td>\r\n<td class=bp>Below Proficient</td>\r\n<td class=fbp>Far Below Proficient</td>\r\n</tr></table>',1),('TerraNova','','<table>\r\n  <tr><td class=Q4>76-99 NCE (Above Average)</td></tr>\r\n  <tr><td class=Q3>51-75 NCE (High Average)</td></tr>\r\n  <tr><td class=Q2>26-50 NCE (Low Average)</td></tr>\r\n  <tr><td class=Q1>0-25 NCE (Below Average)</td></tr>\r\n</table>',4),('ESP','ESP','<table><tr>\r\n  <td class=c4>4, 5, & 6 = Average/Above Average</td></tr>\r\n<tr>\r\n  <td class=c3>3 = Below Average</td></tr>\r\n<tr>\r\n  <td class=c1>1 & 2 = Far Below Average</td></tr>\r\n</table>\r\n',5),('PPVT','PPVT','',6);
/*!40000 ALTER TABLE `tests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `testscores`
--

DROP TABLE IF EXISTS `testscores`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `testscores` (
  `tid` int(11) NOT NULL auto_increment,
  `alaskaid` int(11) NOT NULL default '0',
  `year` varchar(254) NOT NULL default '',
  `test` varchar(254) NOT NULL default '',
  `site` varchar(254) NOT NULL default '',
  `gradelevel` varchar(254) NOT NULL default '',
  `standard` varchar(254) NOT NULL default '0',
  `status` varchar(254) NOT NULL default '',
  `needed` varchar(254) NOT NULL default '',
  `value` varchar(254) NOT NULL default '',
  `difference` int(11) NOT NULL default '0',
  `raw_needed` varchar(254) NOT NULL default '',
  `raw_value` varchar(254) NOT NULL default '',
  `raw_difference` int(11) NOT NULL default '0',
  `level` varchar(254) NOT NULL default '',
  `test_date` varchar(254) NOT NULL default '',
  `importgrp` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`tid`),
  KEY `test` (`test`),
  KEY `year` (`year`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `testscores`
--

LOCK TABLES `testscores` WRITE;
/*!40000 ALTER TABLE `testscores` DISABLE KEYS */;
/*!40000 ALTER TABLE `testscores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `testscoresmap`
--

DROP TABLE IF EXISTS `testscoresmap`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `testscoresmap` (
  `test` varchar(254) NOT NULL default '',
  `standard` varchar(254) NOT NULL default '',
  `heading` varchar(254) NOT NULL default '',
  `subject` varchar(254) NOT NULL default '',
  `order` int(11) NOT NULL default '0',
  `second` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`test`,`standard`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `testscoresmap`
--

LOCK TABLES `testscoresmap` WRITE;
/*!40000 ALTER TABLE `testscoresmap` DISABLE KEYS */;
INSERT INTO `testscoresmap` (`test`, `standard`, `heading`, `subject`, `order`, `second`) VALUES ('SBA','Reading','Reading Scale Scores','',0,''),('SBA','R-SC1','','',1,''),('SBA','R-SC2','','',2,''),('SBA','R-SC3','','',3,''),('SBA','Writing','Writing Scale Scores','',4,''),('SBA','W-SC1','','',5,''),('SBA','W-SC2','','',6,''),('SBA','W-SC3','','',7,''),('SBA','Math','Math Scale Scores','',8,''),('SBA','M-SC1','','',9,''),('SBA','M-SC2','','',10,''),('SBA','M-SC3','','',11,''),('SBA','M-SC4','','',12,''),('SBA','M-SC5','','',13,''),('SBA','M-SC6','','',14,''),('SBA','Science','Science Scale Scores','',15,''),('SBA','S-SC1','','',16,''),('SBA','S-SC2','','',17,''),('SBA','S-SC3','','',18,''),('SBA','S-SC4','','',19,''),('HSGQE','Reading','','',20,''),('HSGQE','R4.1','','',21,''),('HSGQE','R4.2','','',22,''),('HSGQE','R4.3','','',23,''),('HSGQE','R4.4','','',24,''),('HSGQE','R4.7','','',25,''),('HSGQE','R4.8','','',26,''),('HSGQE','Writing','','',27,''),('HSGQE','W4.1/4.2','','',28,''),('HSGQE','W4.3','','',29,''),('HSGQE','W4.4','','',30,''),('HSGQE','Math','','',31,''),('HSGQE','M1.4','','',32,''),('HSGQE','M2.4','','',33,''),('HSGQE','M3.4','','',34,''),('HSGQE','M4.4','','',35,''),('HSGQE','M5.3','','',36,''),('HSGQE','M6.3','','',37,''),('PPVT','Testing date','Pre Testing Date','',38,''),('PPVT','CA','Pre CA years-months','',39,''),('PPVT','PreRS','Pre RS','',40,''),('PPVT','PreSS','Pre SS','',41,''),('PPVT','PrePercentile','Pre Percentile','',42,''),('PPVT','PreNCE','Pre NCE','',43,''),('PPVT','PreGrowthScale','Pre Growth','',44,''),('PPVT','PreAE','Pre AE','',45,''),('PPVT','Diff','Pre Difference between CA and AE in years-months','',46,''),('PPVT','Pre Range','Pre Range in Years','',47,''),('PPVT','Post Testing date','Post Testing date','',48,''),('PPVT','Post CA','Post CA years-months','',49,''),('PPVT','PostRS','Post RS','',50,''),('PPVT','PostSS','Post SS','',51,''),('PPVT','PostPercentile','Post Percentile','',52,''),('PPVT','PostNCE','Post NCE','',53,''),('PPVT','PostGrowScale','Post Growth','',54,''),('PPVT','PostAE','Post AE','',55,''),('PPVT','Post Diff','Post Difference between CA and AE in years-months','',56,''),('PPVT','Post Range','Post Range in Years','',57,''),('ESP','Testing date','Testing Date','',58,''),('ESP','Chronological Age','Chronological Age','',59,''),('ESP','Verbal Concepts','Verbal Concepts Standard Score','',60,'Verbal Concepts Screening Index'),('ESP','Visual Discrimination','Visual Discrimination Standard Score','',61,'Visual Discrimination Screening Index'),('ESP','Logical Relations','Logical Relations Standard Score','',62,'Logical Relations Screening Index'),('ESP','Basic School Skills','Basic School Skills Standard Score','',63,'Basic School Skills Screening Index'),('ESP','Expressive Language','Expressive Language Standard Score','',64,'Expressive Language Screening Index'),('ESP','Receptive Language','Receptive Language Standard Score','',65,'Receptive Language Screening Index'),('ESP','Gross Motor','Gross Motor Point Score','',66,'Gross MotorPoint Screening Index'),('ESP','Fine Motor','Fine Motor Point Score','',67,'Fine Motor Screening Index'),('ESP','Articulation','Articulation Category','',68,'second'),('ELP','Listening Scale Score','Listening Standard Score','',69,'ELP Listening Proficiency Level'),('ELP','Speaking Scale Score','Speaking Standard Score','',70,'ELP Speaking Proficiency Level'),('ELP','Reading Scale Score','Reading Standard Score','',71,'ELP Reading Proficiency Level'),('ELP','Writing Scale Score','Writing Standard Score','',72,'ELP Writing Proficiency Level'),('ELP','Comprehension Scale Score','Comprehension Standard Score','',73,'ELP Comprehension Proficiency Level'),('ELP','Overall Scale Score','Overall Scale Score','',74,'ELP Overall Proficiency Level'),('ELP','ELP Made Progress','ELP Made Progress','',75,'third'),('TerraNova','Reading','Reading','',1,''),('TerraNova','Vocabulary','Vocabulary','',2,''),('TerraNova','Reading Composite','Reading Composite','',3,''),('TerraNova','Language','Language','',4,''),('TerraNova','Language Mechanics','Language Mechanics','',5,''),('TerraNova','Language Composite','Language Composite','',6,''),('TerraNova','Mathematics','Mathematics','',7,''),('TerraNova','Math Computation','Math Computation','',8,''),('TerraNova','Math Composite','Math Composite','',9,''),('TerraNova','Total Score','Total Score','',10,''),('TerraNova','Science','Science','',11,''),('TerraNova','Social Studies','Social Studies','',12,''),('TerraNova','Spelling','Spelling','',13,''),('TerraNova','Word Analysis','Word Analysis','',14,'');
/*!40000 ALTER TABLE `testscoresmap` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_grades`
--

DROP TABLE IF EXISTS `tmp_grades`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_grades` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `subjectname` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `timeframe` varchar(254) NOT NULL default '',
  `schoolname` varchar(254) NOT NULL default '',
  `schoolid` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  UNIQUE KEY `studentid` (`studentid`,`subjectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_grades`
--

LOCK TABLES `tmp_grades` WRITE;
/*!40000 ALTER TABLE `tmp_grades` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_grades` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q1`
--

DROP TABLE IF EXISTS `tmp_q1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q1` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `subjectname` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `sublvl` varchar(254) NOT NULL default '',
  `timeframe` varchar(254) NOT NULL default '',
  `schoolid` varchar(254) NOT NULL default '',
  `schoolname` varchar(254) NOT NULL default '',
  `stayback` varchar(254) NOT NULL default '',
  `combine` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`),
  KEY `subjectid` (`subjectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q1`
--

LOCK TABLES `tmp_q1` WRITE;
/*!40000 ALTER TABLE `tmp_q1` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q1` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q1_update`
--

DROP TABLE IF EXISTS `tmp_q1_update`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q1_update` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `scorehigh` varchar(254) NOT NULL default '',
  `scorelow` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q1_update`
--

LOCK TABLES `tmp_q1_update` WRITE;
/*!40000 ALTER TABLE `tmp_q1_update` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q1_update` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q1_update_low`
--

DROP TABLE IF EXISTS `tmp_q1_update_low`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q1_update_low` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q1_update_low`
--

LOCK TABLES `tmp_q1_update_low` WRITE;
/*!40000 ALTER TABLE `tmp_q1_update_low` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q1_update_low` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q2`
--

DROP TABLE IF EXISTS `tmp_q2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q2` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `subjectname` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `sublvl` varchar(254) NOT NULL default '',
  `timeframe` varchar(254) NOT NULL default '',
  `schoolid` varchar(254) NOT NULL default '',
  `schoolname` varchar(254) NOT NULL default '',
  `stayback` varchar(254) NOT NULL default '',
  `combine` varchar(254) NOT NULL default '',
  UNIQUE KEY `studentid_2` (`studentid`,`subjectid`),
  KEY `studentid` (`studentid`),
  KEY `subjectid` (`subjectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q2`
--

LOCK TABLES `tmp_q2` WRITE;
/*!40000 ALTER TABLE `tmp_q2` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q2_update`
--

DROP TABLE IF EXISTS `tmp_q2_update`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q2_update` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `scorehigh` varchar(254) NOT NULL default '',
  `scorelow` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q2_update`
--

LOCK TABLES `tmp_q2_update` WRITE;
/*!40000 ALTER TABLE `tmp_q2_update` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q2_update` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q2_update_low`
--

DROP TABLE IF EXISTS `tmp_q2_update_low`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q2_update_low` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q2_update_low`
--

LOCK TABLES `tmp_q2_update_low` WRITE;
/*!40000 ALTER TABLE `tmp_q2_update_low` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q2_update_low` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q3`
--

DROP TABLE IF EXISTS `tmp_q3`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q3` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `subjectname` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `sublvl` varchar(254) NOT NULL default '',
  `timeframe` varchar(254) NOT NULL default '',
  `schoolid` varchar(254) NOT NULL default '',
  `schoolname` varchar(254) NOT NULL default '',
  `stayback` varchar(254) NOT NULL default '',
  `combine` varchar(254) NOT NULL default '',
  UNIQUE KEY `studentid_2` (`studentid`,`subjectid`),
  KEY `studentid` (`studentid`),
  KEY `subjectid` (`subjectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q3`
--

LOCK TABLES `tmp_q3` WRITE;
/*!40000 ALTER TABLE `tmp_q3` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q3` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q3_update`
--

DROP TABLE IF EXISTS `tmp_q3_update`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q3_update` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `scorehigh` varchar(254) NOT NULL default '',
  `scorelow` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q3_update`
--

LOCK TABLES `tmp_q3_update` WRITE;
/*!40000 ALTER TABLE `tmp_q3_update` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q3_update` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q3_update_low`
--

DROP TABLE IF EXISTS `tmp_q3_update_low`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q3_update_low` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q3_update_low`
--

LOCK TABLES `tmp_q3_update_low` WRITE;
/*!40000 ALTER TABLE `tmp_q3_update_low` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q3_update_low` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q4`
--

DROP TABLE IF EXISTS `tmp_q4`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q4` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `subjectname` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `sublvl` varchar(254) NOT NULL default '',
  `timeframe` varchar(254) NOT NULL default '',
  `schoolid` varchar(254) NOT NULL default '',
  `schoolname` varchar(254) NOT NULL default '',
  `stayback` varchar(254) NOT NULL default '',
  `combine` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`),
  KEY `subjectid` (`subjectid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q4`
--

LOCK TABLES `tmp_q4` WRITE;
/*!40000 ALTER TABLE `tmp_q4` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q4` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q4_update`
--

DROP TABLE IF EXISTS `tmp_q4_update`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q4_update` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `scorehigh` varchar(254) NOT NULL default '',
  `scorelow` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q4_update`
--

LOCK TABLES `tmp_q4_update` WRITE;
/*!40000 ALTER TABLE `tmp_q4_update` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q4_update` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmp_q4_update_low`
--

DROP TABLE IF EXISTS `tmp_q4_update_low`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmp_q4_update_low` (
  `studentid` varchar(254) NOT NULL default '',
  `subjectid` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `updatescore` varchar(254) NOT NULL default '',
  `kind` varchar(254) NOT NULL default '',
  `dummy1` varchar(254) NOT NULL default '',
  `dummy2` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`,`subjectid`,`kind`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmp_q4_update_low`
--

LOCK TABLES `tmp_q4_update_low` WRITE;
/*!40000 ALTER TABLE `tmp_q4_update_low` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmp_q4_update_low` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tmpimport`
--

DROP TABLE IF EXISTS `tmpimport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tmpimport` (
  `p0` text NOT NULL,
  `p1` text NOT NULL,
  `p2` text NOT NULL,
  `p3` text NOT NULL,
  `p4` text NOT NULL,
  `p5` text NOT NULL,
  `p6` text NOT NULL,
  `p7` text NOT NULL,
  `p8` text NOT NULL,
  `p9` text NOT NULL,
  `p10` text NOT NULL,
  `p11` text NOT NULL,
  `p12` text NOT NULL,
  `p13` text NOT NULL,
  `p14` text NOT NULL,
  `p15` text NOT NULL,
  `p16` text NOT NULL,
  `p17` text NOT NULL,
  `p18` text NOT NULL,
  `p19` text NOT NULL,
  `p20` text NOT NULL,
  `p21` text NOT NULL,
  `p22` text NOT NULL,
  `p23` text NOT NULL,
  `p24` text NOT NULL,
  `p25` text NOT NULL,
  `p26` text NOT NULL,
  `p27` text NOT NULL,
  `p28` text NOT NULL,
  `p29` text NOT NULL,
  `p30` text NOT NULL,
  `p31` text NOT NULL,
  `p32` text NOT NULL,
  `p33` text NOT NULL,
  `p34` text NOT NULL,
  `p35` text NOT NULL,
  `p36` text NOT NULL,
  `p37` text NOT NULL,
  `p38` text NOT NULL,
  `p39` text NOT NULL,
  `p40` text NOT NULL,
  `p41` text NOT NULL,
  `p42` text NOT NULL,
  `p43` text NOT NULL,
  `p44` text NOT NULL,
  `p45` text NOT NULL,
  `p46` text NOT NULL,
  `p47` text NOT NULL,
  `p48` text NOT NULL,
  `p49` text NOT NULL,
  `p50` text NOT NULL,
  `p51` text NOT NULL,
  `p52` text NOT NULL,
  `p53` text NOT NULL,
  `p54` text NOT NULL,
  `p55` text NOT NULL,
  `p56` text NOT NULL,
  `p57` text NOT NULL,
  `p58` text NOT NULL,
  `p59` text NOT NULL,
  `p60` text NOT NULL,
  `p61` text NOT NULL,
  `p62` text NOT NULL,
  `p63` text NOT NULL,
  `p64` text NOT NULL,
  `p65` text NOT NULL,
  `p66` text NOT NULL,
  `p67` text NOT NULL,
  `p68` text NOT NULL,
  `p69` text NOT NULL,
  `p70` text NOT NULL,
  `p71` text NOT NULL,
  `p72` text NOT NULL,
  `p73` text NOT NULL,
  `p74` text NOT NULL,
  `p75` text NOT NULL,
  `p76` text NOT NULL,
  `p77` text NOT NULL,
  `p78` text NOT NULL,
  `p79` text NOT NULL,
  `p80` text NOT NULL,
  `p81` text NOT NULL,
  `p82` text NOT NULL,
  `p83` text NOT NULL,
  `p84` text NOT NULL,
  `p85` text NOT NULL,
  `p86` text NOT NULL,
  `p87` text NOT NULL,
  `p88` text NOT NULL,
  `p89` text NOT NULL,
  `p90` text NOT NULL,
  `p91` text NOT NULL,
  `p92` text NOT NULL,
  `p93` text NOT NULL,
  `p94` text NOT NULL,
  `p95` text NOT NULL,
  `p96` text NOT NULL,
  `p97` text NOT NULL,
  `p98` text NOT NULL,
  `p99` text NOT NULL,
  `p100` text NOT NULL,
  `p101` text NOT NULL,
  `p102` text NOT NULL,
  `p103` text NOT NULL,
  `p104` text NOT NULL,
  `p105` text NOT NULL,
  `p106` text NOT NULL,
  `p107` text NOT NULL,
  `p108` text NOT NULL,
  `p109` text NOT NULL,
  `p110` text NOT NULL,
  `p111` text NOT NULL,
  `p112` text NOT NULL,
  `p113` text NOT NULL,
  `p114` text NOT NULL,
  `p115` text NOT NULL,
  `p116` text NOT NULL,
  `p117` text NOT NULL,
  `p118` text NOT NULL,
  `p119` text NOT NULL,
  `p120` text NOT NULL,
  `p121` text NOT NULL,
  `p122` text NOT NULL,
  `p123` text NOT NULL,
  `p124` text NOT NULL,
  `p125` text NOT NULL,
  `p126` text NOT NULL,
  `p127` text NOT NULL,
  `p128` text NOT NULL,
  `p129` text NOT NULL,
  `p130` text NOT NULL,
  `p131` text NOT NULL,
  `p132` text NOT NULL,
  `p133` text NOT NULL,
  `p134` text NOT NULL,
  `p135` text NOT NULL,
  `p136` text NOT NULL,
  `p137` text NOT NULL,
  `p138` text NOT NULL,
  `p139` text NOT NULL,
  `p140` text NOT NULL,
  `p141` text NOT NULL,
  `p142` text NOT NULL,
  `p143` text NOT NULL,
  `p144` text NOT NULL,
  `p145` text NOT NULL,
  `p146` text NOT NULL,
  `p147` text NOT NULL,
  `p148` text NOT NULL,
  `p149` text NOT NULL,
  `p150` text NOT NULL,
  `p151` text NOT NULL,
  `p152` text NOT NULL,
  `p153` text NOT NULL,
  `p154` text NOT NULL,
  `p155` text NOT NULL,
  `p156` text NOT NULL,
  `p157` text NOT NULL,
  `p158` text NOT NULL,
  `p159` text NOT NULL,
  `p160` text NOT NULL,
  `p161` text NOT NULL,
  `p162` text NOT NULL,
  `p163` text NOT NULL,
  `p164` text NOT NULL,
  `p165` text NOT NULL,
  `p166` text NOT NULL,
  `p167` text NOT NULL,
  `p168` text NOT NULL,
  `p169` text NOT NULL,
  `p170` text NOT NULL,
  `p171` text NOT NULL,
  `p172` text NOT NULL,
  `p173` text NOT NULL,
  `p174` text NOT NULL,
  `p175` text NOT NULL,
  `p176` text NOT NULL,
  `p177` text NOT NULL,
  `p178` text NOT NULL,
  `p179` text NOT NULL,
  `p180` text NOT NULL,
  `p181` text NOT NULL,
  `p182` text NOT NULL,
  `p183` text NOT NULL,
  `p184` text NOT NULL,
  `p185` text NOT NULL,
  `p186` text NOT NULL,
  `p187` text NOT NULL,
  `p188` text NOT NULL,
  `p189` text NOT NULL,
  `p190` text NOT NULL,
  `p191` text NOT NULL,
  `p192` text NOT NULL,
  `p193` text NOT NULL,
  `p194` text NOT NULL,
  `p195` text NOT NULL,
  `p196` text NOT NULL,
  `p197` text NOT NULL,
  `p198` text NOT NULL,
  `p199` text NOT NULL,
  `p200` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tmpimport`
--

LOCK TABLES `tmpimport` WRITE;
/*!40000 ALTER TABLE `tmpimport` DISABLE KEYS */;
/*!40000 ALTER TABLE `tmpimport` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transcript`
--

DROP TABLE IF EXISTS `transcript`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transcript` (
  `studentid` int(11) NOT NULL default '0',
  `subjectid` varchar(254) NOT NULL default '',
  `subjectname` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `timeframe` varchar(254) NOT NULL default '',
  `schoolid` varchar(254) NOT NULL default '',
  `schoolname` varchar(254) NOT NULL default '',
  `year` int(11) NOT NULL default '0',
  `quarter` varchar(254) NOT NULL default '',
  `gpa` float NOT NULL default '0',
  `cdate` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `grp` timestamp NOT NULL default '0000-00-00 00:00:00',
  KEY `timeframe` (`timeframe`),
  KEY `quarter` (`quarter`),
  KEY `score` (`score`),
  KEY `studentid` (`studentid`),
  KEY `year` (`year`),
  KEY `subjectid` (`subjectid`),
  KEY `subjectname` (`subjectname`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transcript`
--

LOCK TABLES `transcript` WRITE;
/*!40000 ALTER TABLE `transcript` DISABLE KEYS */;
/*!40000 ALTER TABLE `transcript` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `userid` int(11) NOT NULL auto_increment,
  `user` varchar(254) NOT NULL default '',
  `pwd` varchar(64) NOT NULL default '',
  `privilegeA` bigint(20) NOT NULL default '0',
  `privilegeB` bigint(20) NOT NULL default '0',
  `scopeA` bigint(254) NOT NULL default '0',
  `scopeB` bigint(20) NOT NULL default '0',
  `name` varchar(254) NOT NULL default '',
  `status` varchar(254) NOT NULL default 'active',
  `email` varchar(254) NOT NULL default '',
  `site` varchar(254) NOT NULL default '',
  `type` varchar(254) NOT NULL default '',
  `studentID` varchar(254) NOT NULL default '',
  `homeroom` varchar(254) NOT NULL default '',
  `reading` varchar(254) NOT NULL default '',
  `tutor` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`userid`),
  KEY `user` (`user`),
  KEY `pwd` (`pwd`),
  KEY `status` (`status`),
  KEY `site` (`site`),
  KEY `type` (`type`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-07-20 12:51:39
