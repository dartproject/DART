<?php

$site = $_GET['site'];
$type = $_GET['type'];
$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
$year = $_GET['year'];
$nextyear = $year+1;
$month = $_GET['month'];
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
if ($type == 'year') {
	$info = $db->get_results("SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID 
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$year-08-01' AND '$nextyear-06-30' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
		GROUP BY S.studentid, site, AG.GroupID", ARRAY_A);
		$view = "Year View: $year - $nextyear for Site: $site";
//print_r($yearinfo);
} else if ($type == 'month') {
	$info = $db->get_results ("SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID  
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$startmonth-01' AND '$nextmonth-01' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
		GROUP BY S.studentid, site, AG.GroupID", ARRAY_A);
		$view = "Month View: $month for Site: $site";
//print_r($info);
} else if ($type == 'day') {
	$curdate = date('Y-m-d');
	$currdatedisplay = date("m/d/Y");
	//echo $curdate;
	$info = $db->get_results ("SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID and S.studentid = AE.studentid
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID
		GROUP BY S.studentid, site, AG.GroupID", ARRAY_A);
		$view = "Day View: $currdatedisplay for Site: $site";
	//print_r($todayinfo);
} else {

}

foreach ($info as $student) {
	$id = $student['id'];
	$site = $student['SiteID'];
	$group = $student['GroupID'];
	$key = $id."_".$site;
	$name = $student['fname'] . " " . $student['lname'];
	$table[$key]['g_' . $group] = $student['count'];
	$table[$key]['name'] = $name;
	$table[$key]['id'] = $id;
	$table[$key]['site'] = $site;
//	$body .= "$id<br>";
}

$body .= "$view<br><table border=1>";
$body .= "<tr><th>Name</th><th>Student ID</th><th>Site</th><th>Absent</th><th>Late</th><th>ISS</th><th>Suspended</th><th>Present</th></tr>";
foreach($table as $ind) {
	
	$body .= "<tr><td>" . $ind['name'] . "&nbsp;</td><td>" . $ind['id'] . "&nbsp;</td><td>"  . $ind['site'] . "&nbsp;</td><td>" .  $ind['g_0'] . "&nbsp;</td><td>" .  $ind['g_1'] . "&nbsp;</td><td>" .  $ind['g_2'] . "&nbsp;</td><td>" . $ind['g_3'] . "&nbsp;</td><td>" .  $ind['g_4'] . "&nbsp;</td></tr>";
}
$body .= "</table>";

include_once("template.inc");
?>