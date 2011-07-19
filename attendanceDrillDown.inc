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
$quarter = getValue($_GET, 'quarter');
$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
$nextyear = $year+1;
$dates = getDates($year, $quarter, $curdate);
$titles = array(
	"year" => "Year vew: $year - ".($year+1)." for Site: $site",
	"quarter" => "Quarter vew: Q$quarter for Site: $site",
	"day" => "Day view: $currdatedisplay for Site: $site",
	"absent" => "Absent Day view: $currdatedisplay for Site: $site",
	"late" => "Late Day view: $currdatedisplay for Site: $site"
);


$sql = NULL;
if($cmd2 == "Export All") {
	if ($type == 'year') {
		$date = $dates[$type];
		$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID 
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date BETWEEN '$date[0]' AND '$date[1]' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
			 GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
	} else if ($type == 'quarter') {
		$date = $dates[$type];
		$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID  
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date BETWEEN '$date[0]' AND '$date[1]' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
	 		GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
	} else if ($type == 'day') {
		$date = $dates[$type];
		$currdatedisplay = PHPDate("m/d/Y", $date[0]);
		$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID  and S.studentid = AE.studentid
			GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
	} else  if ($type == 'absent') {
		$date = $dates["day"];
		$currdatedisplay = PHPDate("m/d/Y", $date[0]);
		$studentlist = getStudentIn("SELECT S.studentid as id
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID and AG.GroupID = 0
				and S.studentid = AE.studentid 
			GROUP BY S.studentid");
		if($studentlist != NULL) {
			$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
				FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
				WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist) 
				AND S.studentid = AE.studentid AND AG.GroupID = 0 
				GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
		}
	} else  if ($type == 'late') {
		$date = $dates["day"];
		$currdatedisplay = PHPDate("m/d/Y", $date[0]);
		$studentlist = getStudentIn("SELECT S.studentid as id
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID and AG.GroupID = 1
				and S.studentid = AE.studentid 
			GROUP BY S.studentid");
		if($studentlist != NULL) {
			$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
				FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
				WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist)
				AND S.studentid = AE.studentid AND AG.GroupID = 1 
				GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
		}
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
	exportText($export);
}

$view = $titles[$type];
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
