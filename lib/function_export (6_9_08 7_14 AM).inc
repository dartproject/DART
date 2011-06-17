<?php


function getListArray($listid) {
  global $db;
  	$sql = "select studentid from listvalues where listid = '$listid'";
  	$students = $db->get_results($sql, ARRAY_A);
  	foreach ($students as $stu) $ret[] = $stu['studentid'];
	return($ret);
}

function exportFallOasis($students) {
	global $db;
	
	$selection = "student.studentid,alaskaid,lname,fname,mname,student.village,zip,bday,gender,ethnicity,schoolID,grade,dc,lre,LEP,LEPStatus";
//	print_r($students);
	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : "," . $stu; 
	$sql = "SELECT $selection from student 
			LEFT JOIN site ON student.site = site.siteid 
			LEFT JOIN speddata ON speddata.studentid = student.studentid 
			WHERE student.studentid IN ($studentlist) 
			ORDER BY lname, fname";
//	echo $sql;
	exportSQL ($sql);
}

function exportAttendanceCount($students, $start, $end) {
	global $db;

	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : ", " . $stu; 
	
	$selection = "S.studentid,alaskaid,lname,fname,mname,S.village,zip,bday,gender,ethnicity,grade";
	$sql = "SELECT $selection, AE.SiteID as site, S.studentid as id, fname, lname, count(AC.CodeID)/2 as count, AC.CodeID, Description
			FROM AttendanceEvents AE, AttendanceCodes AC, student S
		WHERE AE.Date BETWEEN '$start' AND '$end' AND AE.CodeID = AC.CodeID and S.studentid = AE.studentid
			AND S.studentid IN ($studentlist)
		 GROUP BY S.studentid, AC.CodeID";
//	echo $sql;
	$results = $db->get_results($sql, ARRAY_A);
	$export .= "Name\tAlaskaID\tSite\tPresent\tAbsent\tLate\tExcused Tardy\tStudent Activity\tHealth Absence\tExcused Absence\tSubsistence Leave\tWorkstudy\tSuspended\tIn-school Suspension\tVacation\n";
	foreach ($results as $student) {
		$id = $student['alaskaid'];
		$sitestu = $student['site'];
		$code = $student['CodeID'];
		$key = $id."_".$sitestu;
		$name = $student['fname'] . " " . $student['lname'];
		$table[$key]['g_' . $code] = $student['count'];
		$table[$key]['name'] = $name;
		$table[$key]['id'] = $id;
		$table[$key]['site'] = $sitestu;
	}
	foreach($table as $ind) {

		$export .= $ind['name'] . "\t" . $ind['id'] . "\t"  . $ind['site'] . "\t" .  $ind['g_0'] . "\t" .  $ind['g_1'] . "\t" .  $ind['g_2'] . "\t" . $ind['g_3'] . "\t" .  $ind['g_4'] . "\t" .  $ind['g_5'] . "\t" .  $ind['g_6'] . "\t" .  $ind['g_7'] . "\t" .  $ind['g_8'] . "\t" .  $ind['g_9'] . "\t" .  $ind['g_10'] . "\t" .  $ind['g_11'] . "\n";	
	}
	exportText($export);

}

function exportDiscipline($students, $start, $end) {
	global $db;
	
	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : "," . $stu; 
	$selection = "student.studentid as student_id,alaskaid,lname,fname,mname,student.village,zip,bday,gender,ethnicity,grade";
	$sql = "SELECT $selection, discipline.* from student 
			LEFT JOIN discipline ON discipline.studentid = student.studentid 
			WHERE student.studentid IN ($studentlist) 
			ORDER BY lname, fname";
	exportSQL ($sql);

}

function exportEnterExit($students, $start, $end) {
	global $db;
	
	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : "," . $stu; 
	$selection = "student.studentid as id,alaskaid,lname,fname,mname,student.village,zip,bday,gender,ethnicity,schoolNumber,schoolID,grade";
	$sql = "SELECT $selection, studentmovement.* from student 
			LEFT JOIN studentmovement ON studentmovement.studentid = student.studentid
			LEFT JOIN site ON site.siteid = studentmovement.site
			WHERE student.studentid IN ($studentlist) 
			ORDER BY lname, fname";
	exportSQL ($sql);

}

?>
