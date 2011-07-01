<?php

$Display = Privilege(A10);

$msg = "";
$data = array();
$start = getValue($_GET, 'start', 0);
$limit = getValue($_GET, 'limit', 50);
$startdate = getValue($_GET, 'startdate');
$enddate = getValue($_GET, 'enddate');
$startOutput = getValue($_GET, 'startOutput');
$endOutput = getValue($_GET, 'endOutput');
$toggle = getValue($_GET, 'toggle');
$get_site = getValue($_GET, 'site');

$isGET = false;

if($Display != 'none') {
	$site = ($Display == 'site') ? $currentMySite : $get_site;

	/* Sites */
	$sites = getSites("district");
	$siteMenu = array("" => "District Wide");
	foreach ($sites as $s) {
		$siteMenu[$s['siteid']] = $s['siteid'];
	}
	$siteMenu["Private"] = "Private";

	/* Toggle types */
	$toggleMenu = array("teacher" => "Teacher", "student" => "Student");
	
	if(count($_GET) > 1) { // GET request
		$isGet = true;
		if($toggle == "student")
			$data = getStudentToggles($startOutput, $endOutput, $site, $start, $limit);
		else if ($toggle == "teacher")
			 $data = getTeacherToggles($startOutput, $endOutput, $site, $start, $limit);
		if(count($data) > 0) {
			$total = $data['total'];
			$data = $data['data'];
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
		}
	}
} else {
	$msg = "You do not have the correct privledges";
}


$title = "History - Count Screen";

$smarty->assign('pageTitle',$title);
$smarty->assign('Display',$Display);
$smarty->assign('siteMenu',$siteMenu);
$smarty->assign('toggleMenu',$toggleMenu);
$smarty->assign('get_site',$get_site);
$smarty->assign('data',$data);
$smarty->assign('msg',$msg);
$smarty->assign('cmd',"count");

$smarty->assign('startOutput',$startOutput);
$smarty->assign('endOutput',$endOutput);
$smarty->assign('startdate',$startdate);
$smarty->assign('enddate',$enddate);
$smarty->assign('isGET', $isGet);

$searchParameters = compact("start", "limit", "startOutput", "endOutput", "startdate", "enddate", "site", "toggle");

$smarty->assign('searchParameters',$searchParameters);

$smarty->assign('total',$total);
$smarty->assign('nextstart',$nextstart);
$smarty->assign('prevstart',$prevstart);
$smarty->assign('final',$final);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('count.tpl');
?>
