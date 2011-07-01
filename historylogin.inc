<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$start = getValue($_GET, 'start', 0);
$limit = getValue($_GET, 'limit', 50);
$user = getValue($_GET, 'user');

$site = Privilege(A10) == 'site' ? $currentMySite : "";

/* Users */
$users = getAllUsers($site);
$userMenu = array("" => "All Users");
foreach ($users as $u) {
	$userMenu[$u['id']] = $u['name'];
}

$title = "History Login";

$historyObj = getLoginEntries($start, $limit, $user, $site);
$total = $historyObj['total'];
$history = $historyObj['list'];
for ($i = 0; $i < count($history); $i++) {
   $dt = $history[$i]['timestamp'];
   $history[$i]['user'] = $history[$i]['userid']. " - " . $history[$i]['name'];
}
if($start+$limit > $total) {
  $nextstart = $start;
} else {
  $nextstart = $start+$limit;
}
if($start-$limit > 0) {
  $prevstart = $start-$limit;
} else {
  $prevstart = $start;
}
$final = min($start+$limit-1, $total);

$smarty->assign('pageTitle',$title);
$smarty->assign('userMenu',$userMenu);
$smarty->assign('cmd',"historylogin");

$searchParameters = compact("start", "limit", "user");

$smarty->assign('searchParameters',$searchParameters);

$smarty->assign('total',$total);
$smarty->assign('nextstart',$nextstart);
$smarty->assign('prevstart',$prevstart);
$smarty->assign('final',$final);
$smarty->assign('history',$history);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('historylogin.tpl');
?>
