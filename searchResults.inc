<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified: Bolek Kurowski (bkurowsk@andrew.cmu.edu
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

global $db;

$defaultLimit = 50;

if ($_POST['continue'] == "yes") {
    $limit = $_POST['limit'];
    if ($limit < 1) {
        $limit = $defaultLimit;
    }
    $start = $_POST['start'];
    $limitstart = $start - 1;
    $total = $_POST['total'];
    $sql = $_POST['sql'];
    $sql = URLdecode($sql);
    $sql1 = $sql . " order by lname LIMIT $limitstart, $limit";
    $students = $db->get_results($sql1, ARRAY_A);
} else {
    $limit = $defaultLimit;
    $start = 1;
    $values = getStudentSearchResults($_POST, $start - 1, $limit);
    $students = $values['list'];
    $total = $values['total'];
    $sql = $values['sql'];
}

$end = min($total, $start + $limit - 1);

if ($start + $limit > $total) {
    $nextstart = $start;
} else {
    $nextstart = $start + $limit;
}
if ($start - $limit > 0) {
    $prevstart = $start - $limit;
} else {
    $prevstart = $start;
}

$dates = getQuarterDates();
$qstart = $dates['start'];
$qend = $dates['stop'];

//*****************************************************************************
// Set Export Options
//*****************************************************************************
$showExportOptions = array();
if (PrivilegeB(B5) == 'district') {
    $showExportOptions["Discipline"] = "Discipline Export";
}

if (PrivilegeB(B6) == 'district') {
    $showExportOptions["Attendance"] = "Attendance Export";
}

if (PrivilegeB(B7) == 'district') {
    $showExportOptions["EnterExit"] = "Enter Exit Export";
}

if (PrivilegeB(B8) == 'district') {
    $showExportOptions["FallOasis"] = "Fall Oasis Export";
}

$checkall = $total == 0 ? "" : $checkall;

if (Privilege(A6) == 'district')
    $showEdit = 1;
else
    $showEdit = 0;

$yearDisplay = $CurrentYear . "-" . substr($CurrentYear + 1, 2, 2) . ":Q$CurrentQuarter";

$showStudentStatusLink = 0;
if (PDisplay(A30))
    $showStudentStatusLink = 1;

//******************************************************************************
// Assign variable to Smarty
//******************************************************************************
$smarty->assign("total", $total);
$smarty->assign("prevstart", $prevstart);
$smarty->assign("nextstart", $nextstart);
$smarty->assign("urlSQL", urlencode($sql));
$smarty->assign("limit", $limit);
$smarty->assign("start", $start);
$smarty->assign("end", $end);
$smarty->assign("qstart", $qstart);
$smarty->assign("qend",$qend);
$smarty->assign("showExportOptions",$showExportOptions);
$smarty->assign("students", $students);
$smarty->assign("showStudentStatusLink", $showStudentStatusLink);
$smarty->assign("yearDisplay", $yearDisplay);
$smarty->assign("showEdit", $showEdit);


$isSmarty = true;

include ("template.inc");

$smarty->display("searchResults.tpl");
?>
