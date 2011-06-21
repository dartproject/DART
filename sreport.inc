<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include ("sreportFunction.inc");

$studentID = $_GET['id'];
$qpistatus = $_GET['qpi'];
$studentInfo = getStudentInfo($studentID);
$site = $studentInfo['site'];

$siteEqual = $currentMySite == $site;
$idEqual = $currentAffiliatedID == $studentID;

if(!viewReport($idEqual, $siteEqual, Privilege(A18))) {
  NoPriv("report", "site=$site");
}

$title = "User Management - DART System";

$body = createSReport($studentID, $qpistatus, 'Y');		

include ("template.inc");
?>
