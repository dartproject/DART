<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once('ListMembers.php');

$listID = getValue($_GET, "listid");
$time = time();
$year = getValue($_GET, "year", date("Y", $time));
$month = getValue($_GET, "month", date("n", $time));
$day = getValue($_GET, "day", date("j", $time));
$period = getValue($_GET, "period", 0);

$periodname = $period == 0 ? "am" : "pm";

$listName = getListName($listID);
$stdcount = count($students);

$monthMenu = getMonthOptions();
$keys = array_keys($monthMenu);
array_unshift($keys, "");
$values = array_values($monthMenu);
array_unshift($values, "");
$monthMenu = array_combine($keys, $values);

$dayMenu = range(1,31);
array_unshift($dayMenu, "");
$dayMenu =array_combine($dayMenu, $dayMenu);

$codes = getAttendanceCodes();

$codeMenu = array("X" => "&lt; Available Codes &gt;");
foreach ($codes as $code) {
	$codeMenu[$code->CodeID] = $code->Description;
}

$attendance =  getAttendanceRates($listID, "$year-$month-$day", $period);
$total = $attendance['Present'] + $attendance['Absent'];

$rate = $total > 0? round(($attendance['Present']/$total)*100, 0) : 0;

function getAttendanceCodes() {
	global $db;
	$codes = $db->get_results("SELECT CodeID, CONCAT_WS(' - ',Code,Description) AS Description FROM AttendanceCodes ORDER BY CodeID");
	return $codes;
}

function getAttendanceRates($listID, $date, $period) {
	global $db;
	$list = $db->get_results("select lists.kind, lists.sql from lists where listid = '$listID' ", ARRAY_A);
	if ($list[0]['kind'] == 'search') {
		$sql = $list[0]['sql'];
		$studentClause = "student.studentid";
	} else {
		$sql = "select studentid from listvalues where listid = '$listID'";
		$studentClause = "listvalues.studentid";
	}

	$listMembers = new ListMembers($db, $sql, $studentClause, $currentUserID); // $currentUserID is a global variable

	$sql = "SELECT AG.Description AS attendance, COUNT(*) AS total ".
			"FROM ".
			"list_members_tmp, attendancecodegroups AS ACG, attendancegroups AS AG, AttendanceEvents AS AE ".
			"WHERE ".
			"AE.studentid = list_members_tmp.studentid AND list_members_tmp.process_id = '".$listMembers->getId()."' AND ".
			"AE.CodeID = ACG.CodeID AND AG.GroupID = ACG.GroupID AND AE.date = '$date' AND AE.PeriodID = '$period' AND ".
			"(AG.Description = 'Absent' OR AG.Description = 'Present') ".
			"GROUP BY ".
			"attendance";

	$results = $db->get_results($sql, ARRAY_A);
	$rates = array("Present" => 0, "Absent" => 0);
	if($results != NULL) {
		foreach($results as $row)
			$rates[$row['attendance']] = $row['total'];
	}
	return $rates;
}

$title = "Group Attendance";

$smarty->assign('dayMenu',$dayMenu);
$smarty->assign('monthMenu',$monthMenu);
$smarty->assign('codeMenu',$codeMenu);
$smarty->assign('day',$day);
$smarty->assign('month',$month);
$smarty->assign('year',$year);
$smarty->assign('periodname',$periodname);
$smarty->assign('period',$period);
$smarty->assign('CurrentYear',$CurrentYear);
$smarty->assign('listID',$listID);
$smarty->assign('listName',$listName);
$smarty->assign('rate',$rate);
$smarty->assign('absent',$attendance['Absent']);
$smarty->assign('present',$attendance['Present']);
$smarty->assign('imageURL',$imageURL);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('attendanceList.tpl');
?>
