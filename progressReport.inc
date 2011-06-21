<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
include("progressReportFunction.inc");

$studentID = $_GET['id'];
$studentInfo = getStudentInfo($studentID);
$site = $studentInfo['site'];

$siteEqual = $currentMySite == $site;
$idEqual = $currentAffiliatedID == $studentID;

if(!viewReport($idEqual, $siteEqual, Privilege(A20))) {
  NoPriv("report", "site=$site");
}

$title = "Progress Summary- DART System";
$body = createProgressReport($studentID, "Y");

include ("template.inc");
?>
