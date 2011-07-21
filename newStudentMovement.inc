<?php

require_once 'lib/dict/Dict.php';
require_once 'lib/dict/DictType.php';

$A6Priv = Privilege(A6);

if($A6Priv != 'district') {
	NoPriv("denied newStudent", "You should not be trying to creating new student. Email sent to admin");
}

$site = $_GET['site'];
$msg = NULL;

// Site created by newStudent.inc.
if($_POST['submit'] <> "") {

	$entryCode = $_POST['entryCode'];
	$alaskaid = $_POST['alaskaid'];

	if($alaskaid != "" and $entryCode != "") {
		$date = MySQLDate($_POST['month'], $_POST['day'], $_POST['year']);
		$site = $_POST['site'];
		$comments = addslashes($_POST['comments']);
		$id = createNewStudent($site);
		saveEntry($id, $entryCode, $site, $date, $alaskaid, $comments);
		header("Location: ./index.php?cmd=StudentEdit&id=$id");
	} else {
		$msg =  "Need to have alaskaid or entry code entered";
	}
}

//$calday = getDay('day', date('j'));
//$calmonth = getMonth('month', date('n'));
//$calyear = getYear('year', date('Y'));

$monthMenu = getMonthOptions();
$month = date('n');

$dayMenu = range(1,31);
$day = date('j');

$yearMenu = range(2005,2020);
$yearMenu = array_combine($yearMenu,$yearMenu);
$year = date('Y');

$sites = getSites("district");
$siteMenu = array();
foreach ($sites as $s) {
	$siteMenu[$s['siteid']] = $s['siteid'];
}
$siteMenu["Private"] = "Private";

$entry_codes = Dict::getDict(DictType::MOVEMENT_ENTRY_TYPES);
$examples = array();
$codes_names = array();
$entryCodeMenu = array("one" => "&lt; Available Codes &gt;");
foreach($entry_codes as $e) {
	$entryCodeMenu[$e['id']] = $e['id']." (".$e['description'].")";
	$examples[$e['id']] = $e['example'];
	$code_names[$e['id']] = $e['name'];
}

$title = "New Student";

$smarty->assign('pageTitle',$title);
$smarty->assign('site',$site);
$smarty->assign('siteMenu',$siteMenu);
$smarty->assign('entryCodeMenu',$entryCodeMenu);
$smarty->assign('examples',$examples);
$smarty->assign('code_names',$code_names);
$smarty->assign('day',$day);
$smarty->assign('dayMenu',$dayMenu);
$smarty->assign('month',$month);
$smarty->assign('monthMenu',$monthMenu);
$smarty->assign('year',$year);
$smarty->assign('yearMenu',$yearMenu);
$smarty->assign('msg',$msg);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('newStudentMovement.tpl');

?>