<?php

set_time_limit(0);

define('DB_HOST', 'localhost');
define('DB_USERNAME', 'dartdb_dartdb');
define('DB_PASSWORD', 'U8zrpJ4f');
define('DB_NAME', 'dartdb_dartdb');
define('WB_PATH', dirname(__FILE__));
define('WB_URL', 'https://dart.bssd.org');

$db[] = array("standards", "full");
$db[] = array("subjects", "full");
$db[] = array("level", "full");
$db[] = array("site", "full");
$db[] = array("scoreweight", "full");
$db[] = array("AttendanceCodeGroups", "full");
$db[] = array("AttendanceCodes", "full");
$db[] = array("AttendanceGroups", "full");
$db[] = array("AttendancePeriods", "full");
$db[] = array("SchoolCalendar", "full");
$db[] = array("SchoolEventCodeGroups", "full");
$db[] = array("SchoolEventCodes", "full");
$db[] = array("SchoolEventGroups", "full");
$db[] = array("SchoolEvents", "full");
$db[] = array("DistrictDates", "full");

$db[] = array("sfainfo", "full");
$db[] = array("hotlist", "full");
$db[] = array("line", "full");

$db[] = array("sip", "skeleton");
$db[] = array("sipaction", "skeleton");
$db[] = array("sipaux", "skeleton");
$db[] = array("siptestfields", "skeleton");

$db[] = array("reportlist", "skeleton");
$db[] = array("testreports", "full");
$db[] = array("testscoresmap", "full");
$db[] = array("tests", "full");

$db[] = array("lists", "skeleton");
$db[] = array("listshare", "skeleton");
$db[] = array("listvalues", "skeleton");
$db[] = array("history", "skeleton");
$db[] = array("history2", "skeleton");
$db[] = array("repnotes", "skeleton");
$db[] = array("quarters", "full");


//// Student Data that needs special handling
$db[] = array("sfascores", "skeleton");

$db[] = array("sped_aux", "skeleton");
$db[] = array("speddata", "skeleton");

$db[] = array("AttendanceEvents", "skeleton");
$db[] = array("movement", "skeleton");
$db[] = array("student", "skeleton");
$db[] = array("studentlevel", "skeleton");
$db[] = array("grades", "skeleton");
$db[] = array("testinglevel", "skeleton");
$db[] = array("testscores", "skeleton");
$db[] = array("discipline", "skeleton");
$db[] = array("transcript", "skeleton");
$db[] = array("user", "skeleton");



$filename = WB_PATH . "/coredata.sql";
$filename2 = WB_PATH . "/exp/testdata.sql";

echo "HERE2";
updateAll();
//makeTestCase($filename2);
// backupSkeleton($db, $filename);
// backupFullContent($dbname, $filename);

/*
Truncate table student
Truncate table studentlevel
Truncate table testinglevel
Truncate table grades
Truncate table testscores
Truncate table AttendanceEvents;

*/

function updateAll () {

	$link = mysql_connect(DB_HOST, DB_USERNAME, DB_PASSWORD);
	if (!$link) {
		error('Could not connect: ' . mysql_error());
	}
	mysql_select_db(DB_NAME);

  $sql = "select * from student where status = 'Active'";	
  echo $sql;
	$records = mysql_query($sql); 
	if($records != "") {
	  $i = 0;
	  $j = 0;
//	  echo "here in";
		while($rec = mysql_fetch_array($records, MYSQL_ASSOC)) {
     $studentid .= ($studentid == "") ? $rec['studentid'] : ",".$rec['studentid'];
      if($i == 40) {
        $filename = WB_PATH . "/exp/testdata_40stu_$j.sql"; 
        echo "$filename - $studentid<br>";
        makeTestCase ($filename, $studentid);
        $j++;
        $i=0;
        $studentid = "";
//        break;
      }
      $i++;
		}
	}
	mysql_close($link);	
	echo "Finished updateall";
}

function makeTestCase ($filename, $studentlist='') {

  if($studentlist != '') 
    $studentlist = " and studentmap.studentid in ($studentlist) ";
//	echo "FILENAME $filename<br>";
	if (!$handle = fopen($filename, 'w')) {
			 error("Cannot open file ($filename)");
	}
//	echo "HERE3";
	// Writes the header to the file out
	testwrite($handle,
		"--\n".
		"-- Database: \n".
		"-- ".gmdate("M d Y", mktime()).", ".gmdate("g:i A", mktime())."\n".
		"--".
		"\n"
	);
	
// student demographic info
	makeInsert("student", "SELECT studentmap.fakestudentid as studentid, studentmap.fakealaskaid as alaskaid, studentmap.fname, studentmap.lname, status, code, site, grade, bday
	FROM student, studentmap 
	WHERE student.studentid = studentmap.studentid $studentlist
	", $handle);
	
	// studentlevel
	makeinsert("studentlevel", "SELECT studentmap.fakestudentid as studentid, subject, level, progress, start, final, change_username, change_user, change_timestamp, igrp
	FROM studentlevel, studentmap
	WHERE studentlevel.studentid = studentmap.studentid $studentlist
	", $handle);
	
	// testinglevel
	makeinsert("testinglevel", "SELECT studentmap.fakestudentid as studentid, testinglevel, year
	FROM testinglevel, studentmap
	WHERE testinglevel.studentid = studentmap.studentid $studentlist
	", $handle);
	
  	// grades
	makeinsert("grades", "SELECT studentmap.fakestudentid as studentid, subject, level,std,value,num,psid,storecode, igrp, achange
	FROM grades, studentmap
	WHERE grades.studentid = studentmap.studentid and std != 'comment' $studentlist
	", $handle);
	
/*
	makeinsert("testscores", "SELECT studentmap.fakealaskaid as alaskaid, year, test, testscores.site, gradelevel, standard, testscores.status, value, needed, difference, raw_difference, raw_needed, raw_value, level, test_date, importgrp
	FROM testscores, studentmap, student
	WHERE student.studentid = studentmap.studentid and
	student.alaskaid = testscores.alaskaid $studentlist
	", $handle);
*/

	makeinsert("transcript", "SELECT studentmap.fakestudentid as studentid, subjectid, subjectname, score, timeframe, schoolid, schoolname, year, quarter, gpa
	FROM transcript, studentmap
	WHERE transcript.studentid = studentmap.studentid $studentlist
	", $handle);
	
	makeinsert("AttendanceEvents", "SELECT studentmap.fakestudentid as studentid, SiteID, Date, PeriodID, CodeID
	FROM AttendanceEvents, studentmap
	WHERE AttendanceEvents.StudentID = studentmap.studentid $studentlist
	", $handle);


	fclose($handle);
}

function backupSkeleton($dbnames, $filename) {


	$link = mysql_connect(DB_HOST, DB_USERNAME, DB_PASSWORD);
	if (!$link) {
		error('Could not connect: ' . mysql_error());
	}
	mysql_select_db(DB_NAME);
	
	if (!$handle = fopen($filename, 'w')) {
			 error("Cannot open file ($filename)");
	}
	
	// Writes the header to the file out
	testwrite($handle,
		"--\n".
		"-- Database: ".DB_NAME."\n".
		"-- ".gmdate("M d Y", mktime()).", ".gmdate("g:i A", mktime())."\n".
		"--".
		"\n"
	);
	
	$tables = mysql_query("SHOW TABLES");
	$i=0;
	foreach ($dbnames as $table) {
		$tablename = $table[0];
//		echo "$tablename, ";
		$i++;
		$tablecreation = mysql_query('SHOW CREATE TABLE '.$tablename); 
		$ctable = mysql_fetch_array($tablecreation, MYSQL_NUM);
		
		testwrite($handle, "\n\n-- Create table $tablename\n\n"); 
		testwrite($handle, "DROP TABLE IF EXISTS `$tablename`;\n\n"); 

		testwrite($handle, $ctable[1] .";");
		
		if($table[1] == 'full') {
			testwrite($handle, "\n\n-- Dump data for ".$tablename."\n\n");
			$records = mysql_query('SELECT * FROM '.$tablename); 
			if($records != "") {
				while($rec = mysql_fetch_array($records, MYSQL_ASSOC)) { 
					$sql_code = "INSERT INTO `$tablename` VALUES (";
					$set ='';
					foreach($rec as $insert => $value) {
						$set .= ($set == '') ? '': ', ';
						$set .= "'".addslashes($value)."'";
					}
					testwrite($handle, "$sql_code $set);\n");
				}
			}
		}
	}
	
	fclose($handle);
	
	mysql_close($link);
//	echo "#$i";

}

function testwrite($handle, $body) {
	fwrite($handle, $body);
//	echo str_replace("\n", "<br>", $body);
}

function makeInsert($table, $sql, $handle) {

	testwrite($handle, "\n\n-- Inserts for table $table\n\n"); 
//	echo "-- Inserts for table $table => $sql<br>";
	$link = mysql_connect(DB_HOST, DB_USERNAME, DB_PASSWORD);
	if (!$link) {
		error('Could not connect: ' . mysql_error());
	}
	mysql_select_db(DB_NAME);

 	$records = mysql_query($sql); 

	if($records != "") {
		while($rec = mysql_fetch_array($records, MYSQL_ASSOC)) { 
			$sql_code = "INSERT INTO `$table` SET ";
			$set ='';
			foreach($rec as $insert => $value) {
				$set .= ($set == '') ? '': ', ';
				$set .= "$insert = '".addslashes($value)."'";
			}
//			echo "$sql_code $set<br>";
			testwrite($handle, "$sql_code $set;\n");
		}
	}
	
	mysql_close($link);	
}
?>