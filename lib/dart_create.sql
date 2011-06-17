-- phpMyAdmin SQL Dump
-- version 2.9.0.2
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Nov 30, 2006 at 01:54 PM
-- Server version: 4.1.21
-- PHP Version: 4.4.2
-- 
-- Database: `dartdb_dartdb`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `alert_toggles`
-- 

CREATE TABLE `alert_toggles` (
  `subject` varchar(254) NOT NULL default '',
  `lvl` varchar(254) NOT NULL default '',
  `days` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `bugs`
-- 

CREATE TABLE `bugs` (
  `id` int(11) NOT NULL auto_increment,
  `contact` varchar(254) NOT NULL default '',
  `problemDate` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `problem` text NOT NULL,
  `resolveDate` timestamp NOT NULL default '0000-00-00 00:00:00',
  `resolution` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `grades`
-- 

CREATE TABLE `grades` (
  `studentid` int(11) NOT NULL default '0',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '0',
  `std` varchar(254) NOT NULL default '',
  `value` text NOT NULL,
  `num` int(11) NOT NULL default '0',
  `psid` varchar(254) NOT NULL default '',
  `storecode` varchar(254) NOT NULL default '',
  `igrp` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`),
  KEY `level` (`level`),
  KEY `std` (`std`),
  KEY `subject` (`subject`),
  KEY `num` (`num`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `grades2`
-- 

CREATE TABLE `grades2` (
  `studentid` int(11) NOT NULL default '0',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '0',
  `std` varchar(254) NOT NULL default '',
  `value` varchar(254) NOT NULL default '',
  `num` int(11) NOT NULL default '0',
  `psid` varchar(254) NOT NULL default '',
  `storecode` varchar(254) NOT NULL default '',
  `igrp` varchar(254) NOT NULL default '',
  KEY `studentid` (`studentid`),
  KEY `level` (`level`),
  KEY `std` (`std`),
  KEY `subject` (`subject`),
  KEY `value` (`value`),
  KEY `num` (`num`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `history`
-- 

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
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=31682 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `history2`
-- 

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
  KEY `userid` (`userid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=128012 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `hotlist`
-- 

CREATE TABLE `hotlist` (
  `grade` varchar(254) NOT NULL default '',
  `stage` varchar(254) NOT NULL default '',
  `score` varchar(254) NOT NULL default '',
  `neededmin` varchar(254) NOT NULL default '',
  KEY `grade` (`grade`),
  KEY `stage` (`stage`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `importgrp`
-- 

CREATE TABLE `importgrp` (
  `id` int(11) NOT NULL auto_increment,
  `timstamp` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `userid` int(11) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=35 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `level`
-- 

CREATE TABLE `level` (
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '',
  `name` varchar(254) NOT NULL default '',
  `standardID` varchar(254) NOT NULL default '',
  `Identifier` varchar(254) NOT NULL default '',
  `numlevel` int(11) NOT NULL default '0',
  KEY `subject` (`subject`),
  KEY `level` (`level`),
  KEY `numlevel` (`numlevel`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `lists`
-- 

CREATE TABLE `lists` (
  `userid` int(11) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  `listid` int(11) NOT NULL auto_increment,
  `listname` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`listid`),
  KEY `userid` (`userid`),
  KEY `type` (`type`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2315 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `listvalues`
-- 

CREATE TABLE `listvalues` (
  `listid` int(11) NOT NULL default '0',
  `studentid` int(11) NOT NULL default '0',
  KEY `listid` (`listid`),
  KEY `studentid` (`studentid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `loadtable`
-- 

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

-- --------------------------------------------------------

-- 
-- Table structure for table `nextlevel`
-- 

CREATE TABLE `nextlevel` (
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '',
  `nextlevel` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `repair`
-- 

CREATE TABLE `repair` (
  `studentid` varchar(254) NOT NULL default '',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '',
  `progress` varchar(254) NOT NULL default ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `repnotes`
-- 

CREATE TABLE `repnotes` (
  `timeframe` varchar(254) NOT NULL default '',
  `site` varchar(254) NOT NULL default '',
  `comment` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `reportlist`
-- 

CREATE TABLE `reportlist` (
  `id` int(11) NOT NULL auto_increment,
  `userid` int(11) NOT NULL default '0',
  `studentid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=25089 ;

-- --------------------------------------------------------

-- 
-- Table structure for table `sfascores`
-- 

CREATE TABLE `sfascores` (
  `year` varchar(254) NOT NULL default '',
  `studentid` varchar(254) NOT NULL default '',
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

-- --------------------------------------------------------

-- 
-- Table structure for table `site`
-- 

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
  PRIMARY KEY  (`siteid`),
  KEY `order` (`order`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `standards`
-- 

CREATE TABLE `standards` (
  `id` varchar(254) NOT NULL default '',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) NOT NULL default '0',
  `type` varchar(254) NOT NULL default '',
  `std` varchar(254) NOT NULL default '',
  `order` int(11) NOT NULL default '0',
  `description` varchar(254) NOT NULL default '',
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

-- --------------------------------------------------------

-- 
-- Table structure for table `student`
-- 

CREATE TABLE `student` (
  `studentid` int(11) NOT NULL default '0',
  `fname` varchar(254) NOT NULL default '',
  `mname` varchar(254) NOT NULL default '',
  `lname` varchar(254) NOT NULL default '',
  `status` varchar(254) NOT NULL default '',
  `code` varchar(254) NOT NULL default '',
  `extID` varchar(254) NOT NULL default '0',
  `site` varchar(254) NOT NULL default '',
  `present` float NOT NULL default '0',
  `absent` float NOT NULL default '0',
  `attper` decimal(10,0) NOT NULL default '0',
  `picture` varchar(254) NOT NULL default '',
  `addr` varchar(254) NOT NULL default '',
  `village` varchar(254) NOT NULL default '',
  `state` varchar(254) NOT NULL default '',
  `zip` varchar(254) NOT NULL default '',
  `phone` varchar(254) NOT NULL default '',
  `email` varchar(254) NOT NULL default '',
  `dartid` varchar(254) NOT NULL default '',
  `user` varchar(254) NOT NULL default '',
  `pwd` varchar(254) NOT NULL default '',
  `alaskaid` varchar(254) NOT NULL default '',
  `psid` varchar(254) NOT NULL default '',
  `grade` varchar(254) NOT NULL default '',
  `bday_old` varchar(254) NOT NULL default '',
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
  `nativeEd` varchar(254) NOT NULL default '',
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
  `scores` varchar(254) NOT NULL default '',
  `mark` varchar(254) NOT NULL default '',
  `mark2` varchar(254) NOT NULL default '',
  PRIMARY KEY  (`studentid`),
  KEY `site` (`site`),
  KEY `status` (`status`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `studentlevel`
-- 

CREATE TABLE `studentlevel` (
  `studentid` int(11) NOT NULL default '0',
  `subject` varchar(254) NOT NULL default '',
  `level` varchar(254) default NULL,
  `progress` varchar(254) NOT NULL default 'EMG',
  `start` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
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

-- --------------------------------------------------------

-- 
-- Table structure for table `subjects`
-- 

CREATE TABLE `subjects` (
  `id` varchar(254) NOT NULL default '',
  `name` varchar(254) NOT NULL default '',
  `gradLevel` int(11) NOT NULL default '0',
  `order` int(11) NOT NULL default '0',
  `standardID` varchar(254) NOT NULL default '',
  `identifier` varchar(254) NOT NULL default '',
  KEY `id` (`id`),
  KEY `gradLevel` (`gradLevel`),
  KEY `order` (`order`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Table structure for table `user`
-- 

CREATE TABLE `user` (
  `userid` int(11) NOT NULL auto_increment,
  `user` varchar(254) NOT NULL default '',
  `pwd` varchar(254) NOT NULL default '',
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
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=322 ;

