<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$user = getValue($_GET, 'user');
$student = (!isset($currentStudentID) || $currentStudentID == '') ? getValue($_GET, 'student'): $currentStudentID;

$start = getValue($_GET, 'start', 0);
$limit = getValue($_GET, 'limit', 50);

$startOutput = getValue($_GET, 'startOutput');
$endOutput = getValue($_GET, 'endOutput');
$site = getValue($_GET, 'site');
$startdate = getValue($_GET, 'startdate');
$enddate = getValue($_GET, 'enddate');
$userMenu = NULL;
$studentMenu = NULL;
$siteMenu = NULL;

$Display = Privilege(A10);

if($Display != 'none') {
	$site = $Display == 'site' ? $currentMySite : "$site";

	/* Users */
	$users = getAllUsers($site);
	$userMenu = array("" => "All Users");
	foreach ($users as $u) {
		$userMenu[$u['id']] = $u['name'];
	}

	/* Students */
	$students = getPotentialListItems($user, $Display);
	$studentMenu = array("" => "All Students");
	foreach ($students as $s) {
		$studentMenu[$s['studentid']] = $s['lname'].", ".$s['fname'];
	}

	/* Sites */
	$sites = getSites("district");
	$siteMenu = array("" => "District Wide");
	foreach ($sites as $s) {
		$siteMenu[$s['siteid']] = $s['siteid'];
	}
	$siteMenu["Private"] = "Private";

}

$title = "History";

$historyObj = getSpedEntries($start, $limit, $student, $user, $site, $startOutput, $endOutput, "spedupdate");
$total = $historyObj['total'];
$history = $historyObj['list'];
for ($i = 0; $i < count($history); $i++) {
	$history[$i]['user'] = $history[$i]['userid']. " - " . $history[$i]['name'];
	$history[$i]['studentName'] = $history[$i]['fname']." ".$history[$i]['lname'];
}
if($start+$limit >= $total) {
	$nextstart = $start;
} else {
	$nextstart = $start+$limit;
}
if($start-$limit >= 0) {
	$prevstart = $start-$limit;
} else {
	$prevstart = $start;
}

$final = min($start+$limit, $total);

$module="sped";

$smarty->assign('pageTitle',$title);
$smarty->assign('Display',$Display);
$smarty->assign('userMenu',$userMenu);
$smarty->assign('studentMenu',$studentMenu);
$smarty->assign('siteMenu',$siteMenu);
$smarty->assign('cmd',"spedhistory");

$searchParameters = compact("start", "limit", "startOutput", "endOutput", "startdate", "enddate", "student", "user", "site", "module");

$smarty->assign('searchParameters',$searchParameters);

$smarty->assign('total',$total);
$smarty->assign('nextstart',$nextstart);
$smarty->assign('prevstart',$prevstart);
$smarty->assign('final',$final);
$smarty->assign('history',$history);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('sped/spedhistory.tpl');
?>
