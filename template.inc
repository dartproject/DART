<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified by: Bolek Kurowski (bkurowsk@andrew.cmu.edu)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
//if (!isset($title)) {
//    $title = "DART";
//}
// Times arein seconds; 
//$timeout = 3600; Set in js/timeout.js

require_once("ReportPrivileges.php");


$smarty->assign('imageURL', $imageURL);
$smarty->assign('logo', $logo);
$smarty->assign('districtName', $districtName);
$smarty->assign('districtPhrase', $districtPhrase);

if (isset($_SESSION['currentStudentName']))
    $smarty->assign('currentStudentName', $_SESSION['currentStudentName']);
if (isset($_SESSION['currentStudentID'])) {
    $smarty->assign('currentStudentID', $_SESSION['currentStudentID']);

    $studentInfo = getStudentInfo($_SESSION['currentStudentID']);
    $site = $studentInfo['site'];

    $siteEqual = isset($currentMySite) && $currentMySite == $site;
    $idEqual = true;

    if (!isset($currentStudentID) || $currentStudentID == '') {
        $edit = true;
    } else {
        $edit = false;
    }

    $reportPrivileges = new ReportPrivileges($idEqual, $siteEqual, $_SESSION['currentStudentID'], $edit, $CurrentYear);

    $smarty->assign('studentReports', $reportPrivileges);
}

$smarty->assign('currentUserName', $loggedInUser->getName());



include("leftside.inc");

//is smarty template doesn't exist set $body
if (!isset($isSmarty) || $isSmarty != true) {
    $isSmarty = false;
    if (isset($head))
        $smarty->assign('head', $head);

    if (isset($js))
        $smarty->assign('js', $js);
    $smarty->assign('isSmarty', $isSmarty);
    $smarty->assign('body', $body);
    $smarty->display('layout.tpl');
}

$smarty->assign('isSmarty', $isSmarty);
?>
