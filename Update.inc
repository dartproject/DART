<?php
$ct = 1;
$nextnum = '';
function runSQL2($sql) {
	global $db, $ct, $body, $nextnum;
	
	$num = $_GET['num'];
	
	if($ct == $num) {
		$body .= "$sql<br><br>";
		$db->get_results($sql);
		$nextnum = $num +1;
		$body .=  "<a href=?cmd=update&num=$nextnum>Continue - $num</a>";
	} 
	if ($ct == $nextnum) {
		$body .=  "<br><br>Next SQL: $sql";
	}
	$ct++;
}
echo "HERE";
function runSQL($sql) {
	global $db, $ct, $body, $nextnum;

//		$body .= "$sql<br><br>";
//		$db->get_results($sql);
}

$sql = "DROP TABLE `grades2`, `grades_9_30_2007`, `sip_9_24_08`, `standards_9_5_2008`, `standards_9_30_2007`, `standard_9_9_2008`, `studentlevel_09_03_09`, `testinglevel 4_6_09`, `testinglevel 12_17_08`, `transcript 6_5_07`, `transcript 6_10_07`, `transcript 8_28_08`, `transcripts_5_14_10`, `transcript_4_6_09`, `transcript_11_21_08`, `transcript_12_31_08`, `transcript_old`;";
runSQL($sql);

$sql = "UPDATE `studentlevel` set progress = 'ADV', igrp = concat(igrp,' 2010-08-15') 
		WHERE (`progress` = 'DEV' or progress = 'EMG') AND `final` != '0000-00-00 00:00:00' 
           and studentid != '0' ";
runSQL($sql);

$sql = "ALTER TABLE `grades` ADD `trans2010` VARCHAR( 254 ) NOT NULL";
runSQL($sql);

$sql ="ALTER TABLE `studentlevel` ADD `spoints` FLOAT NOT NULL AFTER `progress` ,
ADD `sweight` FLOAT NOT NULL AFTER `spoints`  ";
runSQL($sql);

$sql = "UPDATE level,subjects set level.weight = subjects.weight where core != 'x' and level.subject = subjects.id ";
runSQL($sql);

$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'CA' and cast(level as unsigned) in ('4', '5', '6', '7', '8','9','10') ";
runSQL($sql);


$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'SC' and cast(level as unsigned) in ('4', '5', '6', '7', '8') ";
runSQL($sql);


$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'CS' and cast(level as unsigned) in ('4', '5', '6', '7', '8') ";
runSQL($sql);


$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'SS' and cast(level as unsigned) in ('5', '6', '7', '8', '9', '10') ";
runSQL($sql);

$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'LS' and cast(level as unsigned) in ('4', '5', '6', '7', '8') ";
runSQL($sql);

$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'TE' and cast(level as unsigned) in ('4', '5', '6', '7') ";
runSQL($sql);

$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'MA' and cast(level as unsigned) in ('7', '8', '9', '10', '11', '12') ";
runSQL($sql);

$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'WR' and cast(level as unsigned) in ('5', '6', '7', '8', '9') ";
runSQL($sql);

$sql = "UPDATE  level,subjects set level.weight = subjects.weight where level.subject = 'RE' and cast(level as unsigned) in ( '6', '7', '8', '9') ";
runSQL($sql);

$sql = "UPDATE  studentlevel,level set sweight = weight where studentlevel.subject = level.subject and studentlevel.level = level.level";
runSQL($sql);

$sql = "UPDATE  studentlevel set spoints = '4' where progress = 'ADV'";
runSQL($sql);

$sql = "UPDATE  studentlevel set spoints = '3' where progress = 'PRO'";
runSQL($sql);

$sql = "UPDATE  studentlevel set spoints = '2' where progress = 'DEV'";
runSQL($sql);

$sql = "UPDATE  studentlevel set spoints = '1' where progress = 'EMG'";
runSQL($sql);

/* ************ compute GPA ********************
SELECT sum( sweight * spoints ) / sum( sweight )
FROM studentlevel
WHERE studentid = '10219' and sweight > 0

SELECT subject, level, progress, sweight, spoints, final FROM studentlevel where studentid = '10219' and sweight > 0
******************* */


$sql = "ALTER TABLE `grades` ADD `trans2010` VARCHAR( 254 ) NOT NULL";
runSQL($sql);

$sql = "UPDATE grades set trans2010 = value";
runSQL($sql);

$sql = "UPDATE grades set value = '100' where value = 'ADV'";
runSQL($sql);

$sql = "UPDATE grades set value = '89' where value = 'PRO'";
runSQL($sql);

$sql = "UPDATE grades set value = '79' where value = 'DEV'";
runSQL($sql);

$sql = "UPDATE grades set value = '69' where value = 'EMG'";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gs` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(254) NOT NULL,
  `gradetype` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;
";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gs_grades` (
  `id` int(11) NOT NULL auto_increment,
  `gsid` int(11) NOT NULL,
  `symbol` varchar(254) NOT NULL,
  `high` int(11) NOT NULL,
  `low` int(11) NOT NULL,
  `val` int(11) NOT NULL,
  `points` float NOT NULL,
  `ord` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=28 ;
";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gs_select` (
  `id` int(11) NOT NULL auto_increment,
  `gsid` int(11) NOT NULL,
  `siteid` varchar(254) NOT NULL,
  `lowgrade` int(11) NOT NULL,
  `highgrade` int(11) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `siteid` (`siteid`,`lowgrade`,`highgrade`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=31 ;
";
runSQL($sql);

$sql = "INSERT INTO `gs` (`id`, `name`, `gradetype`) VALUES
(1, 'Standards', 1),
(2, 'BSD Secondary Scale', 2),
(3, 'Average Upper Grades', 2);
";
runSQL($sql);

$sql = "INSERT INTO `gs_grades` (`id`, `gsid`, `symbol`, `high`, `low`, `val`, `points`, `ord`) VALUES
(1, 1, 'EMG', 69, 1, 60, 1, 1),
(2, 1, 'DEV', 79, 70, 76, 2, 2),
(3, 1, 'PRO', 89, 80, 86, 3, 3),
(4, 1, 'ADV', 100, 90, 96, 4, 4),
(5, 2, 'A+', 100, 97, 100, 4, 1),
(6, 2, 'A', 96, 93, 96, 4, 2),
(7, 2, 'A-', 92, 90, 92, 3.7, 3),
(8, 2, 'B+', 89, 87, 89, 3.3, 4),
(9, 2, 'B', 86, 83, 86, 3, 5),
(10, 2, 'B-', 82, 80, 82, 2.7, 6),
(11, 2, 'C+', 79, 77, 79, 2.3, 7),
(12, 2, 'C', 76, 73, 76, 2, 8),
(13, 2, 'C-', 72, 70, 72, 1.7, 9),
(14, 2, 'F', 69, 0, 60, 0, 10),
(15, 3, 'A+', 100, 97, 100, 4, 1),
(16, 3, 'A', 96, 93, 96, 4, 2),
(17, 3, 'A-', 92, 90, 92, 3.7, 3),
(18, 3, 'B+', 89, 87, 89, 3.3, 4),
(19, 3, 'B', 86, 83, 86, 3, 5),
(20, 3, 'B-', 82, 80, 82, 2.7, 6),
(21, 3, 'C+', 79, 77, 79, 2.3, 7),
(22, 3, 'C', 76, 73, 76, 2, 8),
(23, 3, 'C-', 72, 70, 72, 1.7, 9),
(24, 3, 'F', 60, 1, 60, 0, 11),
(27, 3, 'D', 69, 61, 69, 1, 10);
";
runSQL($sql);

$sql = "INSERT INTO `gs_select` (`id`, `gsid`, `siteid`, `lowgrade`, `highgrade`) VALUES
(1, 1, 'KTS', -2, 6),
(2, 2, 'KTS', 7, 13),
(3, 1, 'DIO', -2, 13),
(4, 1, 'ELI', -2, 13),
(5, 3, 'GAM', 12, 13),
(6, 1, 'GLV', -2, 13),
(7, 1, 'KKA', -2, 13),
(8, 1, 'UNK', -2, 5),
(9, 1, 'SHH', -2, 13),
(10, 1, 'SKK', -2, 13),
(11, 1, 'SMK', -2, 13),
(12, 1, 'SVA', -2, 13),
(13, 1, 'TLA', -2, 13),
(14, 1, 'WAA', -2, 13),
(15, 1, 'WBB', -2, 13),
(16, 1, 'WMO', -2, 13),
(30, 3, 'UNK', 6, 13);
";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gb_assignments` (
  `aid` int(11) NOT NULL auto_increment,
  `gid` int(11) NOT NULL,
  `ord` int(11) NOT NULL,
  `name` varchar(254) NOT NULL,
  `category` int(11) NOT NULL,
  PRIMARY KEY  (`aid`)
) ";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gb_categories` (
  `cid` int(11) NOT NULL auto_increment,
  `userid` int(11) NOT NULL,
  `catname` varchar(254) NOT NULL,
  PRIMARY KEY  (`cid`)
)";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gb_catwt` (
  `cwid` int(11) NOT NULL auto_increment,
  `gid` int(11) NOT NULL,
  `cid` int(11) NOT NULL,
  `weight` float NOT NULL,
  PRIMARY KEY  (`cwid`)
)";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gb_main` (
  `gid` int(11) NOT NULL auto_increment,
  `lid` int(11) NOT NULL,
  `name` varchar(254) NOT NULL,
  `weighted` int(11) NOT NULL,
  PRIMARY KEY  (`gid`)
)";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gb_scores` (
  `aid` int(11) NOT NULL,
  `sid` int(11) NOT NULL,
  `score` int(11) NOT NULL,
  PRIMARY KEY  (`aid`,`sid`)
)";
runSQL($sql);

$sql = "CREATE TABLE IF NOT EXISTS `gb_assignstand` (
  `aid` int(11) NOT NULL,
  `subject` varchar(254) NOT NULL,
  `level` varchar(254) NOT NULL,
  `std` varchar(254) NOT NULL,
  PRIMARY KEY  (`aid`,`subject`,`level`,`std`)
)";
runSQL($sql);

include ("template.inc");

?>
