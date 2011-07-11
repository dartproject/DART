<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

require_once('lib/security/Privileges.php');
$A6Priv = Privilege(A6);

//$leftside = "";
//$auxleftside = "";
//$leftside2 = "";
//$but = "<a href=\"index.php?module=st&cmd=stshowreports\">ST Show Reports</a>";
//$but2 = "<a href=\"index.php?cmd=transcriptsProduce\">Produce Transcript</a>";
//$but3 = "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=transcriptsDefine\">Define Transcript</a>";

/* * ******* Build Complete Left Side ************ */
//$leftside .= "<div align=\"left\">
//		<b><font color=\"#0066ff\">Logged In As:</font></b><br>
//		<img src=\"" . $imageURL ."dart1.gif\" alt=\"\" height=\"67\" width=\"77\" border=\"0\"><br>
//		<b><font color=\"#0066ff\">$currentUserName</font></b>";



//******************************************************************************
// Transcripts *****************************************************************
//******************************************************************************

$smarty->assign('showTranscriptOptions', 
        $loggedInUser->isAuthorized(Privileges::MANAGE_TRANSCRIPTS));
//$leftside .= PDisplayB(B12) ? "<br>$but3<br><img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editTranscripts\">Edit Transcripts</a><br>" : "";

/* * ****** Dart Home Information ******** */
//$leftside .= "<br><b><font color=\"#0066ff\">DART Info<br></font></b>
//		  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=logout\">Log Out</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=home\">Dart Home</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editProfile\">Edit Profile</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"mailto:dart@bssd.org\" target=_blank>Feedback</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=districtrep\" target=_blank>SIP Plan</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=siterep\" target=_blank>Site SIP Plan</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=teacherrep\" target=_blank>Teacher SIP Plan</a><br>";


// *****************************************************************************
// Search **********************************************************************
//******************************************************************************

$smarty->assign('showSearch', 
        $loggedInUser->isAuthorized(Privileges::SEARCH_EXPORT_STUDENTS));

//******************************************************************************
// Dashboard *******************************************************************
//******************************************************************************

$smarty->assign('showDashboard', PDisplay(B3));
//if(PDisplayB(B3)) {
//  $leftside .="<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=Dashboard\">Dashboard</a><br>";
//}


//******************************************************************************
// My Groups *******************************************************************
//******************************************************************************

$smarty->assign('showMyGroups', PDisplay(A11));
if (PDisplay(A11)) {
    $smarty->assign('myGroups', getMyList($currentUserID));

//			$leftside .= "<br>
//			<font color=\"#0066ff\"><b>My Groups</b></font><br>" .
//      showMyList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color=\"#0066ff\"><br>');
}

//*****************************************************************************
//Shared Groups ***************************************************************
//*****************************************************************************

$smarty->assign('showSharedGroups', PDisplay(A12));
$smarty->assign('currentMySite', $currentMySite);
if (PDisplay(A12)) {
    $smarty->assign('sharedGroups', getMyList($currentUserID, $currentMySite));
//			$leftside .= "<br><font color=\"#0066ff\"><b>Shared Groups<br>$currentMySite</b></font><br>"
//    . showMyList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color="#0066ff"><br>', $currentMySite);
}

//******************************************************************************
//Private Shared Groups ********************************************************
//******************************************************************************

$sharedList = getSharedList($currentUserID);
//$sharedList = showSharedList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color="#0066ff"><br>');
//if($sharedList <> "") {
if (count($sharedList) > 0) {
    $smarty->assign('privateSharedGroups', $sharedList);
    //$leftside .= "<br><font color=\"#0066ff\"><b>Private Shared List</b></font><br>$sharedList";
}


//******************************************************************************
// Manage Groups  **************************************************************
//******************************************************************************

$smarty->assign('showManageGroups', PDisplay(A11));
//if (PDisplay(A11)) {
//    $leftside .= "<br><font color=\"#0066ff\"><b>Manage Groups</b></font><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=newlist\">New Group</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editlist\">Edit Groups</a><br>";
//}

//******************************************************************************
// Reports *********************************************************************
//******************************************************************************

$smarty->assign('showReports',PDisplay(A26 + A24));

//if (PDisplay(A26 + A24)) {
//    $leftside .= "<br><font color=\"#0066ff\"><b>Reports</b></font><br>";
//}

//******************************************************************************
// Official Report *************************************************************
//******************************************************************************

$smarty->assign('showOfficialReport',PDisplay(A24));
//if (PDisplay(A24)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=reportsInd\">Official</a><br>";
//}

//******************************************************************************
// Drill Down ******************************************************************
//******************************************************************************

$smarty->assign('showDrillDown',PDisplay(A26));
//if (PDisplay(A26)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=pivot\">Drill Down!</a><br>
//<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=extraPacingReport\">PASS</a><br>";
//}

//******************************************************************************
// Admin Area ******************************************************************
//******************************************************************************

$smarty->assign('showAdminArea',PDisplay(A30 + A29));
//if (PDisplay(A30 + A29)) {
//    $leftside .= "<br><font color=\"#0066ff\"><b>Admin Area</b></font><br>";
//}

//******************************************************************************
// Users ***********************************************************************
//******************************************************************************

$smarty->assign('showUsers',$loggedInUser->isAuthorized(Privileges::MANAGE_USERS));
//if (PDisplay(A30)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=userAdmin&site=$currentMySite&status=Active\">Users $currentMySite</a><br>";
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=InternalError\">Internal Error</a><br>";
//}

//******************************************************************************
// Red Button, Grd, Test *******************************************************
//******************************************************************************

if (PrivilegeB(B10) != 'none') 
    $smarty->assign('showRedButton_Grd_Test',1);
else
    $smarty->assign('showRedButton_Grd_Test',0);

//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=bigRed\">Big Red Button</a><br>";
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=edittestlevel\">Edit Test Level</a><br>";
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editgs\">Edit Grd Setup</a><br>";


//******************************************************************************
// Edit Standards **************************************************************
//******************************************************************************

if (PrivilegeB(B11) != 'none') {
    $smarty->assign('showEditStandards',1);
    //$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editStandards\">Edit Standards</a><br>";
}

//******************************************************************************
// Edit School Calendar ********************************************************
//******************************************************************************

$smarty->assign('showEditSchoolCal',PDisplay(A19));
$smarty->assign('currentYear',$CurrentYear);
//if (PDisplay(A19)) {
//
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=SchoolCalendar&site=DIO&year=$CurrentYear\">Edit School Cal</a><br>";
//}

//******************************************************************************
// Progress ********************************************************************
//******************************************************************************

$smarty->assign('showProgress',PDisplay(A13));
//if (PDisplay(A13)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=progress&site=$currentMySite\">Progress $currentMySite</a><br>";
//}

//******************************************************************************
// History *********************************************************************
//******************************************************************************

$smarty->assign('showHistory',PDisplay(A10));
//if (PDisplay(A10)) {
////			$leftside .= "<br><img src=\"images/check_history.gif\" alt=\"\" height=\"46\" width=\"46\" border=\"0\"><a href=\"index.php?cmd=history\"></a><br>";
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=history\">History Toggle</a><br>";
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=historylogin\">History Login</a><br>";
//}

//******************************************************************************
// Mass Import *****************************************************************
//******************************************************************************

if ($A6Priv == 'district') {
    $smarty->assign('showMassImport',1);
    //$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=uploadInput\">Mass Import</a><br>";
}

//******************************************************************************
// Mass Import *****************************************************************
//******************************************************************************
$smarty->assign('showEditNotes',PDisplay(A29));
//if (PDisplay(A29)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editNotes\">Edit Notes</a><br>";
//}

//******************************************************************************
// Edit Report Notes ***********************************************************
//******************************************************************************

$smarty->assign('showEditReportNotes',PDisplay(A8));
//if (PDisplay(A8)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editRepNotes\">Edit Report Notes</a><br>";
//}

//******************************************************************************
// Student Management Options **************************************************
//******************************************************************************

$smarty->assign('showStudentManagement', PDisplay(A29));
//if (PDisplay(A29)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Enrollment Form\" href=\"http://www.bssd.org/enrollment_form.shtml\">Add Student</a><br>
//
//<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Drop &amp; Transfer Form\" href=\"http://www.bssd.org/transfer_form.shtml\">Drop/ Transfer</a><br>
//
//<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Level Adjustment Form\" href=\"http://www.bssd.org/schedule_form.shtml\">Level Change</a><br>
//
//<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Enrollment Form\" href=\"http://www.bssd.org/forms/elective_form.shtml\">Add Elective</a><br>";
//}

//$leftside .= PDisplay(A6, $AdminSec);

//******************************************************************************
// Module Links ****************************************************************
//******************************************************************************

$smarty->assign('moduleLinks',$moduleleft);
//echo ($leftside . "<br>" . $moduleleft);
?>
