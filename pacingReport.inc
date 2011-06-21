<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
include ("pacingReportFunction.inc");

$studentID = $_GET['id'];
$studentInfo = getStudentInfo($studentID);
$site = $studentInfo['site'];

$siteEqual = $currentMySite == $site;
$idEqual = $currentAffiliatedID == $studentID;

if(!viewReport($idEqual, $siteEqual, Privilege(A22))) {
  NoPriv("report", "site=$site");
}

$title = "Pacing Guide - DART System";
$body = createPacingReport($studentID);
					  
include ("template.inc");
?>
