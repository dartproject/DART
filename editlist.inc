<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$A11Priv = Privilege(A11);
$A14Priv = Privilege(A14);
$A7Priv = Privilege(A7);
$A17Priv = Privilege(A17);

if($A11Priv == 'none') { NoPriv("denied Ad Hoc List", ""); }

$mylists = getMyList($currentUserID, 'all');
if($p1 == "") {
  $p1 = $mylists[0]['listid'];
  if($p1 == "") {
      $p1 = newList($userID);;
  }
}
$list = getListItems($p1);
$listInfo = getListInfo($p1);
$listname = $listInfo['listname'];
$listType = $listInfo['type'];
$listKind = $listInfo['kind'];
$dates = getQuarterDates();
$qstart = $dates['start'];
$qend = $dates['stop'];

//*****************************************************************************
// Set Export Options
//*****************************************************************************
$exportMenu = array();
if (PrivilegeB(B5) == 'district') {
    $exportMenu["Discipline"] = "Discipline Export";
}

if (PrivilegeB(B6) == 'district') {
    $exportMenu["Attendance"] = "Attendance Export";
}

if (PrivilegeB(B7) == 'district') {
    $exportMenu["EnterExit"] = "Enter Exit Export";
}

if (PrivilegeB(B8) == 'district') {
    $exportMenu["FallOasis"] = "Fall Oasis Export";
}

if (PrivilegeB(B8) == 'district') {
    $exportMenu["SummerOasis"] = "Summer Oasis Export";
}

if (PrivilegeB(B8) == 'district') {
    $exportMenu["AllAttendance"] = "All Attendance Export";
}
$showExport = (PDisplay(B5) or PDisplay(B6) or PDisplay(B7) or PDisplay(B8));

$showSFA = $A7Priv != 'none';

function getShared($listid) {
	global $db;

	$sql = "select user.userid, name from user, listshare where listid=$listid and user.userid = listshare.userid";
	$results = $db->get_results ($sql, ARRAY_A);
	return($results);
}

$showAttendance = $A17Priv <> 'none' && $listType == 'Private'; 
if ($showAttendance) {
	if(getValue($_GET, 'attSubmit') != NULL) {
		$am = getValue($_GET,'am',0);
		$pm = getValue($_GET,'pm',0);
		$db->get_results ("Update lists set am = '$am', pm = '$pm' where listid = '$p1'");
		$listInfo['am'] = $am;
		$listInfo['pm'] = $pm;
		$db->get_results ("Delete from listshare where listid = '$p1'");
		foreach ($_GET['test'] as $selection) {
			$db->get_results ("Insert into listshare set listid = '$p1', userid = $selection");
		}
	}
	$selected = getShared($p1);
	$users = getAllUsers();
	$userMenu = array();
	foreach($users as $u) {
		$userMenu[$u['id']] = $u['name'];
	}
	$currentUserIDs = array();
	$currentUserNames = array();
	if($selected != NULL) {
		foreach ($selected as $u) {
			$currentUserIDs[] = $u['userid'];
			$currentUserNames[] = $u['name'];
		}
	}
}

$membersMenu = array();
if($list != "") {
	foreach ($list as $s) {
		$membersMenu[$s['studentid']] = $s['lname'].", ".$s['fname'];
	}
   $showcount = count($membersMenu);
} else {
	$membersMenu[""] = "{Empty Group}";
	$showcount = 0;
}

/********* array difference code that could be improved but works *********/
function my_serialize(&$arr,$pos){
  $arr = serialize($arr);
}

function my_unserialize(&$arr,$pos){
  $arr = unserialize($arr);
}

$student = getPotentialListItems(NULL, Privilege(A11));

if(count($list) != 0) {
     //make a copy
    $first_array_s = $student;
    $second_array_s = $list;
    
    // serialize all sub-arrays
    array_walk($first_array_s,'my_serialize');
    array_walk($second_array_s,'my_serialize');
    
    // array_diff the serialized versions
    $diff = array_diff($first_array_s,$second_array_s);
    
    // unserialize the result
    array_walk($diff,'my_unserialize');
} else {
    $diff = $student;
}
/********* array difference code that could be improved but works *********/

$potentialMenu = array();
foreach ($diff as $s) {
	$potentialMenu[$s['studentid']] = $s['lname'].", ".$s['fname'];
}
$potentialCount = count($potentialMenu);

$listMenu = array();
foreach($mylists as $my) {
	$listMenu[$my['listid']] = $my['listname'];
}

/* Gradebook */
$gb = $db->get_results("select gid, name from gb_main where lid='$p1'", ARRAY_A);
$gradebooks = array();
if($gb != NULL) {
	foreach($gb as $g) {
		$gradebooks[$g['gid']] = $g['name'];
	}
}
/* --------- */

$sites = getSites($A14Priv);
$typeMenu = array("self" => "Mine!");
foreach($sites as $s) {
	$typeMenu[$s['siteid']] = $s['siteid'];
}
$typeMenu['Private'] = "Private";

$title = "Edit Group";

$smarty->assign('pageTitle',$title);
$smarty->assign('listMenu',$listMenu);
$smarty->assign('listID',$p1);
$smarty->assign('listname',$listname);
$smarty->assign('listType',$listType);
$smarty->assign('typeMenu',$typeMenu);
$smarty->assign('type',$listType);
$smarty->assign('currentUserID',$currentUserID);
$smarty->assign('listKind',$listKind);
$smarty->assign('membersMenu',$membersMenu);
$smarty->assign('showcount',$showcount);
$smarty->assign('potentialMenu',$potentialMenu);
$smarty->assign('potentialCount',$potentialCount);
$smarty->assign('exportMenu',$exportMenu);
$smarty->assign('qstart',$qstart);
$smarty->assign('qend',$qend);
$smarty->assign('showExport',$showExport);
$smarty->assign('showSFA',$showSFA);

$smarty->assign('showAttendance',$showAttendance);
if($showAttendance) {
	$smarty->assign('am',$listInfo['am']);
	$smarty->assign('pm',$listInfo['pm']);
	$smarty->assign('currentUserIDs',$currentUserIDs);
	$smarty->assign('currentUserNames',$currentUserNames);
	$smarty->assign('userMenu',$userMenu);
}
$smarty->assign('gradebooks',$gradebooks);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('editlist.tpl');
?>
