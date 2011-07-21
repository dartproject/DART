<?php
// ==================================================================
//  Author: Steve Eley (sfeley@gmail.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

//Get the parameters that we need
$year = getValue($_GET, "year");
$student = getValue($_GET, "student");
$editmonth = getValue($_GET, "editmonth");
$editday = getValue($_GET, "editday");
// It assumes two schedule periods
$pre_code = array(
	getValue($_GET, "code0"),
	getValue($_GET, "code1"),
	getValue($_GET, "site0"),
	getValue($_GET, "site1")
);

if($pre_code[0] == NULL && $pre_code[1] == NULL && $pre_site[0] == NULL && $pre_site[1] == NULL) {
	$sqldate = date("Y-m-d", mktime(0, 0, 0, $editmonth, $editday, $year));
	$sql = "SELECT PeriodID, Code, SiteID, AttendanceEvents.CodeID FROM AttendanceEvents, AttendanceCodes WHERE studentId = '$student' AND Date = '$sqldate' AND AttendanceEvents.CodeID = AttendanceCodes.CodeID";
	$data = $db->get_results($sql);
	if($data != NULL) {
		foreach($data as $code) {
			$pre_code [$code->PeriodID] = $code->Code;
			$pre_site [$code->PeriodID] = $code->SiteID;
		}
	}
}
// Get the student's name
$StudentName = $db->get_var("SELECT CONCAT_WS(' ',fname,lname) AS StudentName FROM student WHERE studentid = $student");

// Get our site list
$Sites = $db->get_results("SELECT siteid, name FROM site ORDER BY siteid");

// Get our attendance codes
$Codes = $db->get_results("SELECT CodeID, Code, CONCAT_WS(' - ',Code,Description) AS Description FROM AttendanceCodes ORDER BY CodeID");

$codeMenuAM = array("X" => "&lt; Available Codes &gt;");
$siteMenuAM = array("X" => "&lt; Available Sites &gt;");
$codeMenuPM = array("Y" => "&lt; Same as AM &gt;");
$siteMenuPM = array("Y" => "&lt; Same as AM &gt;");

foreach($Codes as $c) {
	if ($c->Code == $pre_code[0]) {
		$codeAM = $c->CodeID;
	}
	$codeMenuAM[$c->CodeID] = $c->Description;
	if ($c->Code == $pre_code[1]) {
		$codePM = $c->CodeID;
	}
	$codeMenuPM[$c->CodeID] = $c->Description;
}
foreach($Sites as $s) {
	if ($s->siteid == $pre_site[0]) {
		$siteAM = $s->siteid;
	}
	$siteMenuAM[$s->siteid] = $s->name;
	if ($s->siteid == $pre_site[1]) {
		$sitePM = $s->siteid;
	}
	$siteMenuPM[$s->siteid] = $s->name;
}

// Get chart with codes
$chart = $db->get_results("SELECT AC.Code, AC.Description, ".
		"IF(AG.Description = 'Present', 'X', NULL) AS Present, ".
		"IF(AG.Description = 'Absent', 'X', NULL) AS Absent ".
		"FROM AttendanceCodes AS AC, AttendanceCodeGroups ACG, AttendanceGroups AG ".
		"WHERE AC.CodeID = ACG.CodeID AND AG.GroupID = ACG.GroupID AND ".
		"AG.Description IN ('Present', 'Absent') ".
		"ORDER BY AC.CodeID");

$title = 'DART - Attendance Record Adjustment';

$smarty->assign('pageTitle',$title);
$smarty->assign('StudentName',$StudentName);
$smarty->assign('editmonth',$editmonth);
$smarty->assign('editday',$editday);
$smarty->assign('year',$year);
$smarty->assign('student',$student);
$smarty->assign('CurrentYear',$CurrentYear);

$smarty->assign("codeMenuAM", $codeMenuAM);
$smarty->assign("siteMenuAM", $siteMenuAM);
$smarty->assign("codeMenuPM", $codeMenuPM);
$smarty->assign("siteMenuPM", $siteMenuPM);
$smarty->assign("codeAM", $codeAM);
$smarty->assign("siteAM", $siteAM);
$smarty->assign("codePM", $codePM);
$smarty->assign("sitePM", $sitePM);
$smarty->assign('chart',$chart);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('attendanceCalEdit.tpl');

?>
