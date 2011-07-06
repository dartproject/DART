<?php

$cmd2 = getValue($_POST, 'cmd2');
if($cmd2 == "Group") {
		$val = $_POST['studentID'];
        $uval = array_unique($val); // gets rid of duplicate entries
        $lid = handleGroup($uval, $currentUserID, $action);
        header("Location:index.php?cmd=editlist&p1=$lid");
}

$site = getValue($_GET, 'site');
$curdate = getValue($_GET, 'cdate');
$type = getValue($_GET, 'type');
$year = getValue($_GET, 'year');
$month = getValue($_GET, 'month');
$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
$nextyear = $year+1;
$nextmonth = $month+1;
switch($month) {
	case 8:
	case 9:
	case 10:
	case 11:
		$startmonth = $year . "-" . $month;
		$nextmonth = $year . "-" . $nextmonth;
		break;
	case 12:
		$startmonth = $year . "-" . $month;
		$nextmonth = $nextyear . "-01";
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		$startmonth = $nextyear . "-" . $month;
		$nextmonth = $nextyear . "-" . $nextmonth;
		break;
}
$sql = NULL;
$view = "";
if ($type == 'year') {
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID 
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$year-08-01' AND '$nextyear-06-30' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
		 GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
		$view = "Year View: $year - $nextyear for Site: $site";
} else if ($type == 'month') {
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID  
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$startmonth-01' AND '$nextmonth-01' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
 		GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
		$view = "Month View: $month for Site: $site";
} else if ($type == 'day') {
	$currdatedisplay = PHPDate("m/d/Y", $curdate);
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID  and S.studentid = AE.studentid
		GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
		$view = "Day View: $currdatedisplay for Site: $site";
} else  if ($type == 'absent') {
	$currdatedisplay = PHPDate("m/d/Y", $curdate);
	$studentlist = getStudentIn("SELECT S.studentid as id
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and AG.GroupID = 0
			and S.studentid = AE.studentid 
		GROUP BY S.studentid");
	if($studentlist != NULL) {
		$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist) 
			AND S.studentid = AE.studentid AND AG.GroupID = 0 
			GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
	}
	$view = "Absent Day View: $currdatedisplay for Site: $site";
} else  if ($type == 'late') {
	$currdatedisplay = PHPDate("m/d/Y", $curdate);
	$studentlist = getStudentIn("SELECT S.studentid as id
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and AG.GroupID = 1
			and S.studentid = AE.studentid 
		GROUP BY S.studentid");
	if($studentlist != NULL) {
		$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist)
			AND S.studentid = AE.studentid AND AG.GroupID = 1 
			GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
	}
	$view = "Late Day View: $currdatedisplay for Site: $site";
}

$info = NULL;
if($sql != NULL) {
	$info = $db->get_results ($sql, ARRAY_A);
}
if($info == NULL) $info = array();

$table = array();
foreach ($info as $student) {
	$id = $student['id'];
	$sitestu = $student['SiteID'];
	$group = $student['GroupID'];
	$key = $id."_".$sitestu;
	$name = $student['fname'] . " " . $student['lname'];
	if(!isset($table[$key])) 
		$table[$key] = array("g_0" => "", "g_1" => "", "g_2" => "", "g_3" => "", "g_4" => "");
	$table[$key]['g_' . $group] = number_format($student['count'], 1);
	$table[$key]['name'] = $name;
	$table[$key]['id'] = $id;
	$table[$key]['site'] = $sitestu;
}

$export = "Name\tStudent ID\tSite\tAbsent\tLate\tISS\tSuspended\tPresent\n";
foreach($table as $ind) {
	$export .= $ind['name'] . "\t" . $ind['id'] . "\t"  . $ind['site'] . "\t" .  $ind['g_0'] . "\t" .  $ind['g_1'] . "\t" .  $ind['g_2'] . "\t" . $ind['g_3'] . "\t" .  $ind['g_4'] . "\n";
}

if($cmd2 == "Export All") {
	exportText($export);
}

$title = "Attendance - $view";

$smarty->assign('pageTitle',$title);
$smarty->assign('view',$view);
$smarty->assign('type',$type);
$smarty->assign('site',$site);
$smarty->assign('year',$year);
$smarty->assign('month',$month);
$smarty->assign('cdate',$curdate);
$smarty->assign('table',$table);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('attendanceDrillDown.tpl');

?>
