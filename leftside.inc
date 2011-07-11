<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

require_once('lib/security/Privileges.php');
require_once('lib/security/PScopeType.php');
$A6Priv = Privilege(A6);

//******************************************************************************
// Transcripts *****************************************************************
//******************************************************************************

$smarty->assign('showTranscriptOptions', $loggedInUser->isAuthorized(Privileges::TRANSCRIPTS_MANAGE));
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
        $loggedInUser->isAuthorized(Privileges::STUDENT_SEARCH_VIEW_EXPORT));

//******************************************************************************
// Dashboard *******************************************************************
//******************************************************************************

$smarty->assign('showDashboard', $loggedInUser->isAuthorized(Privileges::DASHBOARD_VIEW));
//if(PDisplayB(B3)) {
//  $leftside .="<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=Dashboard\">Dashboard</a><br>";
//}
//******************************************************************************
// My Groups *******************************************************************
//******************************************************************************

$groupAuth = $loggedInUser->isAuthorized(Privileges::GROUPS);
$smarty->assign('showMyGroups', $groupAuth);
if ($groupAuth) {
$smarty->assign('myGroups', getMyList($currentUserID));

//			$leftside .= "<br>
//			<font color=\"#0066ff\"><b>My Groups</b></font><br>" .
//      showMyList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color=\"#0066ff\"><br>');
}

//*****************************************************************************
//Shared Groups ***************************************************************
//*****************************************************************************

$groupSiteAuth =
$loggedInUser->isAuthorized(Privileges::SITE_SHARED_GROUPS_VIEW);

$smarty->assign('showSharedGroups', $groupAuth);
$smarty->assign('currentMySite', $currentMySite);
if ($groupAuth) {
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

$smarty->assign('showManageGroups',
 $loggedInUser->isAuthorized(Privileges::GROUPS));
//if (PDisplay(A11)) {
//    $leftside .= "<br><font color=\"#0066ff\"><b>Manage Groups</b></font><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=newlist\">New Group</a><br>
//			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editlist\">Edit Groups</a><br>";
//}
//******************************************************************************
// Reports *********************************************************************
//******************************************************************************

$smarty->assign('showReports', PDisplay(A26 + A24));

//******************************************************************************
// Official Report *************************************************************
//******************************************************************************

$smarty->assign('showOfficialReport',
 $loggedInUser->isAuthorized(Privileges::REPORT_CARD));

//******************************************************************************
// Drill Down ******************************************************************
//******************************************************************************

$smarty->assign('showDrillDown',
 $loggedInUser->isAuthorized(Privileges::PIVOT_TABLE_DATA_VIEW));

//******************************************************************************
// Admin Area ******************************************************************
//******************************************************************************

$smarty->assign('showAdminArea', PDisplay(A30 + A29));
//if (PDisplay(A30 + A29)) {
//    $leftside .= "<br><font color=\"#0066ff\"><b>Admin Area</b></font><br>";
//}
//******************************************************************************
// Users ***********************************************************************
//******************************************************************************

$smarty->assign('showUsers', 
        $loggedInUser->isAuthorized(Privileges::USER_ACCESS_SETTINGS));
//if (PDisplay(A30)) {
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=userAdmin&site=$currentMySite&status=Active\">Users $currentMySite</a><br>";
//    $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=InternalError\">Internal Error</a><br>";
//}
//******************************************************************************
// Red Button, Grd, Test *******************************************************
//******************************************************************************
//if (PrivilegeB(B10) != 'none')
if($loggedInUser->isAuthorized(Privileges::BIG_RED_BUTTON))
$smarty->assign('showRedButton_Grd_Test', 1);
else
$smarty->assign('showRedButton_Grd_Test', 0);

//******************************************************************************
// Edit Standards **************************************************************
//******************************************************************************
//if (PrivilegeB(B11) != 'none') {
if($loggedInUser->isAuthorized(Privileges::STANDARD_INFORMATION_EDIT))
$smarty->assign('showEditStandards', 1);

//******************************************************************************
// Edit School Calendar ********************************************************
//******************************************************************************

$smarty->assign('showEditSchoolCal',
 $loggedInUser->isAuthorized(Privileges::SCHOOL_CALENDAR));
$smarty->assign('currentYear', $CurrentYear);

//******************************************************************************
// Progress ********************************************************************
//******************************************************************************

$smarty->assign('showProgress',
 $loggedInUser->isAuthorized(Privileges::PROMOTE_STUDENTS));

//******************************************************************************
// History *********************************************************************
//******************************************************************************

$smarty->assign('showHistory',
 $loggedInUser->isAuthorized(Privileges::HISTORY_VIEW));

//******************************************************************************
// Mass Import *****************************************************************
//******************************************************************************

$smarty->assign('showMassImport',
 $loggedInUser->isScopeAuthorized(Privileges::STUDENT_INFO_EDIT, 
         PScopeType::DISTRICT));

//******************************************************************************
// Mass Import *****************************************************************
//******************************************************************************

$smarty->assign('showEditNotes', 
        $loggedInUser->isAuthorized(Privileges::SITE_NOTES_EDIT));

//******************************************************************************
// Edit Report Notes ***********************************************************
//******************************************************************************

$smarty->assign('showEditReportNotes', 
        $loggedInUser->isAuthorized(Privileges::REPORT_CARD_NOTES));

$smarty->assign('showStudentManagement', 1);

//******************************************************************************
// Module Links ****************************************************************
//******************************************************************************

$smarty->assign('moduleLinks', $moduleleft);
//echo ($leftside . "<br>" . $moduleleft);
?>
