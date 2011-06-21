<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$sipid = $_GET['sid'];

if($_POST['action'] == 'save') {
	saveTeacherSiteSip ($HTTP_POST_VARS);
	$body = "Information successfully saved<br>";
}
$sip = getSip($sipid);
$year = $sip['year'];
$nextyear = $year+1;
//$test = $sip['test'];
//$listid = $sip['listid'];
$sipname = $sip['name'];
$area = ($sip['area'] == 'r') ? "RE" : (($sip['area'] == 'w') ? "WR" : (($sip['area'] == 'm') ? "MA" : $sip['area']));
$oldarea = strtolower(substr($area, 0, 1));
if($oldarea != 'r' or $oldarea != 'm') {
	$initialarea = 'w';
	$initialareaname = 'WR';
} else {
	$initialarea = $oldarea;
	$initialareaname = $area;
}
$districtsip = getSipYearKind($year, 'district');

/*
$studentlist = getListStudents($listid);

$sitesip = getSipYearKind($year, 'site', $sip['site']);

$sql = "SELECT standards.subject, standards.level, standards.std, value, student.studentid, student.fname, student.lname, student.alaskaid
	FROM (student,studentlevel, standards)
	LEFT JOIN grades ON 
		(grades.subject = standards.subject and
		grades.level = standards.level and
		grades.std = standards.std and
		grades.studentid = studentlevel.studentid)
	WHERE
		studentlevel.subject = '$area' and
		studentlevel.final = '0000-00-00 00:00:00' and
		standards.subject = studentlevel.subject and
		standards.level = studentlevel.level and
		standards.type = 'std' and
		student.studentid in ($studentlist) and
		studentlevel.studentid = student.studentid 
		ORDER BY `student`.`lname` ASC,`student`.`fname` ASC, `standards`.`level` ASC, `standards`.`order` ASC  ";
//echo $sql;
$studentStdScores = $db->get_results("$sql", ARRAY_A);


foreach ($studentStdScores as $stu) { 
//	echo $stu['studentid'] . "." . $stu['level'] . "." . $stu['std'] . "<br>";
	$students[$stu['studentid'] . "." . $stu['level']]['std'][$stu['std']] = $stu['value'];
	$students[$stu['studentid'] . "." . $stu['level']]['name'] = $stu['fname'] . " " . $stu['lname'];
	$students[$stu['studentid'] . "." . $stu['level']]['id'] = $stu['studentid'];
	$students[$stu['studentid'] . "." . $stu['level']]['alaskaid'] = $stu['alaskaid'];
	$students[$stu['studentid'] . "." . $stu['level']]['subjectlevel'] = $stu['subject'] . "." . $stu['level'];
}
*/
if($_GET['print'] == "") {
$body .= "<a href=index.php?cmd=teachersip&module=sip&sid=$sipid&print=t>Go To Print Layout</a><br>";

} else {
$body .= "<style>
table {
  font-size: 14px;
}
</style>
<a href=index.php?cmd=teachersip&module=sip&sid=$sipid>Go To Edit Layout</a> | <a href=javascript:window.print()>Print</a><br>";

}
$body .= "<style>
.siptitle {
	font-size: 14px;
}
.sipheading {
	font-weight: bold;
}
</style>
<span class=siptitle><b>$sipname - $year-$nextyear: $area </b></span><br><br>";

$body .= "<table border=0><tr><td>&nbsp;</td><td>

		<span class=sipheading>District SIP Message</span><br>
		<span class=boxed>" . $districtsip['district'] . "</span><br><br>

				
		</td></tr></table>";
/*
foreach ($students as $row) {
	$name = $row['name'];
	$id = $row['id'];
	$aid = $row['alaskaid'];
	$header = "";
	$value = "";

	$body .= "<table border=1><tr><th valign=top>$name</th><td>";
	
// This is the standards for each student
	$sublvl = $row['subjectlevel'];
	while(list($var, $val) = each($row['std'])) {
		$header .= "<th width=30>$var</th>";
		$value .= "<td>$val &nbsp;</td>";
	}
	$body .= "<table border=1><th rowspan=2 valign=top>$sublvl</th>$header</tr><tr>$value</tr></table>";
// Test Scores Start
	$sql = "SELECT testscores.* FROM testscores, testscoresmap
			WHERE testscores.alaskaid = '$aid' and
				testscores.year = '$year' and
				testscoresmap.test = testscores.test and			
				testscoresmap.standard = testscores.standard and				
				testscoresmap.subject = '$area'
			GROUP BY testscores.standard
			ORDER BY testscoresmap.order";
//	echo $sql;
	$testscores = $db->get_results($sql, ARRAY_A);

	
	if ($testscores != "") {
		$theader = "";
		$tvalue = "";
		foreach($testscores as $row) {
			$title = $row['standard'];
			$tval = $row['value'];
			$theader .= "<th width=30>$title</th>";
			$tvalue .= "<td>$tval &nbsp;</td>";
			$test = $row['test'];
		}
		$body .= "<table border=1><tr><th rowspan=2 align=top>$test</th>$theader</tr><tr>$tvalue </tr></table>";
	}
	
// SFA starts
	if($oldarea == 'r') {
		$sql = "SELECT * from sfascores where studentid = '$id' and year='$year' ";
		$results = $db->get_results($sql, ARRAY_A);
		if($results[0]['studentid'] != '') {
			$body .= "<table border=1>";
			$body .= "<tr><th rowspan=2 valign=top>SFA Scores</th><th size=30>Base</th><th size=30>1st Score</th><th size=30>2nd Score</th><th size=30>3rd Score</th></tr>";
			$body .= "<tr><td>" . $results[0]['base_score'] ."</td><td>" . $results[0]['first_score'] ."</td><td>" . $results[0]['second_score'] ."</td><td>" . $results[0]['third_score'] ."</td></tr>";
			$body .= "</table>";
		}
		
	}
// Close student information	
	$body .= "</td></tr></table>";
}
*/
if($_GET['print'] == "") {
$body .= "<iframe id=maintframe1 name=maintframe1
			frameborder=1
			src =\"index.php?module=sip&cmd=showaction&area=$area&id=$sipid\"
			width=\"600px\"
			height= \"400px\">
		</iframe><br>
		
";


} else {

  $row = "";
  $sql = "select * from sipaction where sid = '$sipid' and (area='$area' or area='$oldarea') ";
  $results = $db->get_results ($sql);
  $i = 0;
  foreach ($results as $res) {
    $row .= "<tr valign=top style=\"font-size: 14px;\">
		
		<td>" . $res->action . " &nbsp</td>
		<td>" . $res->eval . "&nbsp</td>
	</tr>"; 
  }

  $body .= "<br><br><table id=\"phoneClone\" class=\"graybg\" border=1 width=600>
	<thead>
	<tr class=\"bluebarsub\"><th>Smart Plan</th><th>Evaluation</th></tr>
	</thead>
	$row
</table>
";

}
include_once ("template.inc");
?>