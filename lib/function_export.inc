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
	
	$selection = "student.studentid,alaskaid,lname,fname,mname,student.village,zip,bday,gender,ethnicity,schoolID,grade,dc,lre,LEP,LEPStatus,if(entrysped>exitdate,'Y','N') as SpEdStatus";
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

function exportAllAttendance($students, $start, $end) {
	global $db;
	
	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : "," . $stu; 
	$search .= ($start != '') ? " and date >= '$start' " : "";
	$search .= ($end != '') ? " and date <= '$end' " : "";	
	$selection = "student.studentid as student_id,date, periodid, AttendanceCodes.code, GroupID,alaskaid,lname,fname,mname,student.village,zip,bday,gender,ethnicity,grade";
	$sql = "SELECT $selection
				FROM `AttendanceEvents` , student, AttendanceCodes, AttendanceCodeGroups
				WHERE AttendanceEvents.StudentID = student.studentid
				AND AttendanceEvents.CodeId = AttendanceCodes.CodeId 
				and AttendanceCodeGroups.CodeId =  AttendanceEvents.CodeId
				$search
				and student.studentid IN ($studentlist) 
				ORDER BY student.studentid, date 
			";
//			echo $sql;
	exportSQL ($sql);

}

function exportDiscipline($students, $start, $end) {
	global $db;
	
	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : "," . $stu; 
	$selection = "student.studentid as student_id,alaskaid,lname,fname,mname,student.village,zip,bday,gender,ethnicity,grade,
					if(entrysped>exitdate,'Y','N') as SpEdStatus,speddata.pcode,migrant";
	$sql = "SELECT $selection, discipline.* from (student, discipline) 
			LEFT JOIN speddata ON speddata.studentid = student.studentid
			WHERE student.studentid IN ($studentlist) 
				AND discipline.studentid = student.studentid 
				AND discipline.incidentdate BETWEEN '$start' AND '$end' 
			ORDER BY lname, fname";
//			echo $sql;
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
function exportSummerOasisList($listid, $start, $end) {
	global $db;

//	echo "HERE AT exportSummerOasis $students, $start, $end<br><br>";
//	print_r($students);
//	echo "<br><br>";
	$list =  $db->get_results ("select * from lists where listid = '$listid' ", ARRAY_A);
	if($list[0]['kind'] == 'search') {
		$studentsql = str_replace("*, (CURDATE() - bday) as age", "student.studentid", $list[0]['sql']);
	} else {
		$studentsql = "select studentid from listvalues where listid = '$listid'";
	}
//	echo "<br><br>--$studentsql<br><br>";
	$selection = "S.studentid,alaskaid,lname,fname,mname,S.village,zip,bday,gender,ethnicity,grade, AE.SiteID, LEP,Date,AE.CodeID, speddata.dc as dc, LEP, LEPStatus,nativeEd,if(entrysped>exitdate,'Y','N') as SpEdStatus,speddata.pcode,migrant";

	$sql = "SELECT $selection FROM AttendanceEvents AE, AttendanceCodes AC, student S
			LEFT JOIN speddata ON speddata.studentid = S.studentid
			WHERE AE.Date BETWEEN '$start' AND '$end' AND AE.CodeID = AC.CodeID 
				AND S.studentid = AE.studentid AND S.studentid IN ( $studentsql )
			ORDER BY S.studentid, Date, PeriodID";
	echo "<br><br>SQL: ".$sql;
	$results = $db->get_results($sql, ARRAY_A);
	
	$sql2 = "select * from studentmovement where date >= '$start' and date <= '$end' AND studentid IN ($studentsql) ORDER by date";
	echo "<br><br>SQL2-".$sql2;
	$results2 = $db->get_results($sql2, ARRAY_A);
	foreach ($results2 as $entry) {
		$sid = $entry['studentid'];
		$site = $entry['site'];
		$code = $entry['code'];
		$kind = $entry['kind'];
		$movement[$sid][$site][$kind] .= ($movement[$sid][$site][$kind] == "") ? "$code" : "-$code";
	}
//print_r($movement); echo "<br><br>";
	$i = 0;
	$value[$i]['aid'] = "AK Student ID";
	$value[$i]['lname'] = "Student Name Last";
	$value[$i]['fname'] = "Student Name First";
	$value[$i]['mname'] = "Student Name Middle";
	$value[$i]['site'] ="Site";
	$value[$i]['city'] ="City/Town/Village";
	$value[$i]['zip'] = "Zip or Postal Code";
	$value[$i]['bday'] = "Birth Date";
	$value[$i]['gender'] = "Gender";
	$value[$i]['race'] = "Race or Ethnicity";
	$value[$i]['grade'] = "Grade";
	$value[$i]['disability'] = "Disability";
	$value[$i]['iep'] = "IEP in Place July 1";
	$value[$i]['entrydate'] = "Entry Date";
	$value[$i]['entrytype'] = "Entry Type";
	$value[$i]['exitdate'] = "Exit Date";
	$value[$i]['exittype'] = "Exit Type";
	$value[$i]['lep'] = "LEP";
	$value[$i]['lepstatus'] = "LEP Status";
	$value[$i]['ada'] = "Aggregate Days Attendance (ADA)";
	$value[$i]['adm'] = "Aggregate Days Membership";
	$value[$i]['nativeEd'] = "NativeEd";
	$value[$i]['sped'] = "SpEdStatus";
	$value[$i]['pcode'] = "P-Code";
	$value[$i]['dc'] = "D-Code";
	$value[$i]['migrant'] = "Migrant";

	$oldid = "";
	$oldsite = "";
	foreach($results as $stu) {
		$id = $stu['studentid'];
		$site = $stu['SiteID'];
//		echo "$id - $site";
		if($id != $oldid or $site != $oldsite) {
			$oldid = $id;
			$oldsite = $site;
			$i++;
			$value[$i]['ada'] = 0;
			$value[$i]['adm'] = 0;
			$value[$i]['entrydate'] = $stu['Date'];
			$value[$i]['aid'] = $stu['alaskaid'];
			$value[$i]['lname'] = $stu['lname'];
			$value[$i]['fname'] = $stu['fname'];
			$value[$i]['mname'] = $stu['mname'];
			$value[$i]['site'] = $stu['SiteID'];
			$value[$i]['city'] = $stu['village'];
			$value[$i]['zip'] = $stu['zip'];
			$value[$i]['bday'] = $stu['bday'];
			$value[$i]['gender'] = $stu['gender'];
			$value[$i]['race'] = $stu['ethnicity'];
			$value[$i]['grade'] = $stu['grade'];
			$value[$i]['lep'] = $stu['LEP'];
			$value[$i]['lepstats'] = $stu['LEPStatus'];
			$value[$i]['ada'] += adaCode($stu['CodeID']);
			$value[$i]['adm'] += admCode($stu['CodeID']);
//			echo "<br><br>$id, $site, 'enter'" . $movement[$id][$site]['enter'] . "<br><br>";
			$value[$i]['entrytype'] = $movement[$id][$site]['enter'];
			$value[$i]['exittype'] = $movement[$id][$site]['exit'];
			$value[$i]['nativeEd'] = $stu['nativeEd'];
			$value[$i]['sped'] = $stu['SpEdStatus'];
			$value[$i]['pcode'] = $stu['pcode'];
			$value[$i]['dc'] = $stu['dc'];
			$value[$i]['migrant'] = $stu['migrant'];
			
		} else {
			$value[$i]['ada'] += adaCode($stu['CodeID']);
			$value[$i]['adm'] += admCode($stu['CodeID']);
			$value[$i]['exitdate'] = $stu['Date'];
		}
	}
//	echo "<br><br>";
//	print_r($value);
//	exportArray ($value);
	exportText(displayArray($value));
//	echo (displayArray($value));
}

function exportSummerOasis($students, $start, $end) {
	global $db;

//	echo "HERE AT exportSummerOasis $students, $start, $end<br><br>";
//	print_r($students);
//	echo "<br><br>";
	
	foreach($students as $stu) $studentlist .= ($studentlist == "") ? $stu : ", " . $stu; 
	
	$selection = "S.studentid,alaskaid,lname,fname,mname,S.village,zip,bday,gender,ethnicity,grade, AE.SiteID, LEP,Date,AE.CodeID, speddata.dc as dc, LEP, LEPStatus,nativeEd,if(entrysped>exitdate,'Y','N') as SpEdStatus,speddata.pcode,migrant";

	$sql = "SELECT $selection FROM AttendanceEvents AE, AttendanceCodes AC, student S
			LEFT JOIN speddata ON speddata.studentid = S.studentid
			WHERE AE.Date BETWEEN '$start' AND '$end' AND AE.CodeID = AC.CodeID 
				AND S.studentid = AE.studentid AND S.studentid IN ($studentlist)
			ORDER BY S.studentid, Date, PeriodID";
	$results = $db->get_results($sql, ARRAY_A);
	
	$sql2 = "select * from studentmovement where date >= '$start' and date <= '$end' AND studentid IN ($studentlist) ORDER by date";
	$results2 = $db->get_results($sql2, ARRAY_A);
	foreach ($results2 as $entry) {
		$sid = $entry['studentid'];
		$site = $entry['site'];
		$code = $entry['code'];
		$kind = $entry['kind'];
		$movement[$sid][$site][$kind] .= ($movement[$sid][$site][$kind] == "") ? "$code" : "-$code";
	}
//print_r($movement); echo "<br><br>";
	$i = 0;
	$value[$i]['aid'] = "AK Student ID";
	$value[$i]['lname'] = "Student Name Last";
	$value[$i]['fname'] = "Student Name First";
	$value[$i]['mname'] = "Student Name Middle";
	$value[$i]['site'] ="Site";
	$value[$i]['city'] ="City/Town/Village";
	$value[$i]['zip'] = "Zip or Postal Code";
	$value[$i]['bday'] = "Birth Date";
	$value[$i]['gender'] = "Gender";
	$value[$i]['race'] = "Race or Ethnicity";
	$value[$i]['grade'] = "Grade";
	$value[$i]['disability'] = "Disability";
	$value[$i]['iep'] = "IEP in Place July 1";
	$value[$i]['entrydate'] = "Entry Date";
	$value[$i]['entrytype'] = "Entry Type";
	$value[$i]['exitdate'] = "Exit Date";
	$value[$i]['exittype'] = "Exit Type";
	$value[$i]['lep'] = "LEP";
	$value[$i]['lepstatus'] = "LEP Status";
	$value[$i]['ada'] = "Aggregate Days Attendance (ADA)";
	$value[$i]['adm'] = "Aggregate Days Membership";
	$value[$i]['nativeEd'] = "NativeEd";
	$value[$i]['sped'] = "SpEdStatus";
	$value[$i]['pcode'] = "P-Code";
	$value[$i]['dc'] = "D-Code";
	$value[$i]['migrant'] = "Migrant";

	$oldid = "";
	$oldsite = "";
	foreach($results as $stu) {
		$id = $stu['studentid'];
		$site = $stu['SiteID'];
//		echo "$id - $site";
		if($id != $oldid or $site != $oldsite) {
			$oldid = $id;
			$oldsite = $site;
			$i++;
			$value[$i]['ada'] = 0;
			$value[$i]['adm'] = 0;
			$value[$i]['entrydate'] = $stu['Date'];
			$value[$i]['aid'] = $stu['alaskaid'];
			$value[$i]['lname'] = $stu['lname'];
			$value[$i]['fname'] = $stu['fname'];
			$value[$i]['mname'] = $stu['mname'];
			$value[$i]['site'] = $stu['SiteID'];
			$value[$i]['city'] = $stu['village'];
			$value[$i]['zip'] = $stu['zip'];
			$value[$i]['bday'] = $stu['bday'];
			$value[$i]['gender'] = $stu['gender'];
			$value[$i]['race'] = $stu['ethnicity'];
			$value[$i]['grade'] = $stu['grade'];
			$value[$i]['lep'] = $stu['LEP'];
			$value[$i]['lepstats'] = $stu['LEPStatus'];
			$value[$i]['ada'] += adaCode($stu['CodeID']);
			$value[$i]['adm'] += admCode($stu['CodeID']);
//			echo "<br><br>$id, $site, 'enter'" . $movement[$id][$site]['enter'] . "<br><br>";
			$value[$i]['entrytype'] = $movement[$id][$site]['enter'];
			$value[$i]['exittype'] = $movement[$id][$site]['exit'];
			$value[$i]['nativeEd'] = $stu['nativeEd'];
			$value[$i]['sped'] = $stu['SpEdStatus'];
			$value[$i]['pcode'] = $stu['pcode'];
			$value[$i]['dc'] = $stu['dc'];
			$value[$i]['migrant'] = $stu['migrant'];
			
		} else {
			$value[$i]['ada'] += adaCode($stu['CodeID']);
			$value[$i]['adm'] += admCode($stu['CodeID']);
			$value[$i]['exitdate'] = $stu['Date'];
		}
	}
//	print_r($value);
//	exportArray ($value);
	exportText(displayArray($value));
//	echo (displayArray($value));
}


function displayArray($value) {
		$list = explode(",", "aid,lname,fname,mname,site,city,zip,bday,gender,race,grade,disability,lep,lepstatus,entrydate,entrytype,exitdate,exittype,ada,adm,nativeEd,sped,pcode,dc,migrant");
	foreach($value as $row) {
		foreach($list as $val) { 
			if($val != 'aid') $str .= "\t";
			$str .= $row[$val];
		}
		$str .= "\n";
	}	
	return($str);

}
function admCode($code) {
	switch($code) {
		case 11:
		case 12:
			return(0);
			break;
		default:
			return(0.5);
	}
}

function adaCode($code) {
	switch($code) {
		case 0:
		case 2:
		case 3:
		case 4:
		case 8:
		case 10:
			return(0.5);
			break;
		default:
			return(0);
	}
//	if($code == 0 or $code == 2) return (0.5); 
//	else return (0);
}

?>