<?php

$Display = Privilege(A10);

$msg = "";
$data = array();
$endOutput = getValue($_GET, 'endOutput');
$startOutput = getValue($_GET, 'startOutput');
$toggle = getValue($_GET, 'toggle');
$start = getValue($_GET, 'start');
$end = getValue($_GET, 'end');
$site = getValue($_GET, 'start');
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
	
	if(isset($_GET['button'])) {
		$isGet = true;
		if($toggle == "student")
			$data = getStudentToggles($startOutput, $endOutput, $site);
		else if ($toggle == "teacher")
			 $data = getTeacherToggles($startOutput, $endOutput, $site);
	}
} else {
	$msg = "You do not have the correct privledges";
}


$title = "History - Count Screen";

$smarty->assign('pageTitle',$title);
$smarty->assign('Display',$Display);
$smarty->assign('siteMenu',$siteMenu);
$smarty->assign('toggleMenu',$toggleMenu);
$smarty->assign('site',$site);
$smarty->assign('get_site',$get_site);
$smarty->assign('toggle',$toggle);
$smarty->assign('data',$data);
$smarty->assign('msg',$msg);

$smarty->assign('startOutput',$startOutput);
$smarty->assign('endOutput',$endOutput);
$smarty->assign('start',$start);
$smarty->assign('end',$end);
$smarty->assign('isGET', $isGet);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('count.tpl');
?>
