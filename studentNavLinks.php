<?php

/*
 *  Copyright (C) 2011 Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 * 
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

$currentUser = "";
$currentUserID = "";
$currentUserName = "";
$currentMySite = "";
$currentSite = "";
$currentPriv = "";
$currentPrivB = "";
$currentScopeA = "";
$currentScopeB = "";

include_once("lib/YearQuarter.inc");
include_once ("lib/machine.config.php");
include_once ("lib/config.inc");
include_once ("lib/ez_sql.php");
include_once ("lib/function.inc");
require_once("ReportPrivileges.php");


getMyGlobals();

$studentID = $_GET['studentID'];

$studentInfo = getStudentInfo($studentID);
$site = $studentInfo['site'];

$siteEqual = isset($currentMySite) && $currentMySite == $site;
$idEqual = true;

if (!isset($currentStudentID) || $currentStudentID == '') {
    $edit = true;
} else {
    $edit = false;
}



$reportPrivileges = new ReportPrivileges($idEqual, $siteEqual, $studentID, $edit, $CurrentYear);

$smarty->assign('studentReports',$reportPrivileges);

$smarty->display('comp/studentNavLinks.tpl');


?>

