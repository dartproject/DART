<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified by: Bolek Kurowski (bkurowsk@andrew.cmu.edu)
//  Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
//
//
// *****************************************************************************
// Get District Messages *******************************************************
//******************************************************************************

if (Privilege(A28) == 'district')
    $district = getNotes('Admin');
else
    $district = null;

//******************************************************************************
// Get Site Messages ***********************************************************
//******************************************************************************
if (($currentMySite != "Admin") and (Privilege(A28) != 'none'))
    $snotes = getNotes($currentMySite);
else
    $snotes=null;

//******************************************************************************
// Show District Reminders *****************************************************
//******************************************************************************
if ($district != null) {
    if ($district['important'] <> "" or $district['warning'] <> "" or $district['tip'] <> "") {

        $smarty->assign('showDistrictReminders', 1);
        //$body .= '<font size="4" color="#cc0000">DART System Status &amp; Reminders</font>';
    }

    if ($district['important'] <> "") {
        $smarty->assign('district_important', $district['important']);
        //$body .= "<div class=\"noteimportant\">" . $district['important'] . "</div>";
    }

    if ($district['warning'] <> "") {
        $smarty->assign('district_warning', $district['warning']);
        //$body .= "<div class=\"notewarning\">" . $district['warning'] . "</div>";
    }

    if ($district['tip'] <> "") {
        $smarty->assign('district_tip', $district['tip']);
        //$body .= "<div class=\"notetip\">" . $district['tip'] . "</div>";
    }
}
//******************************************************************************
// Show Site Reminders *********************************************************
//******************************************************************************
if ($snotes != null) {
    if ($snotes['important'] <> "" or $snotes['warning'] <> "" or $snotes['tip'] <> "") {
        $smarty->assign('showSiteReminders', 1);
        //$body .= "<font size=\"4\" color=\"#cc0000\">DART Site $currentMySite System Status &amp; Reminders</font>";
    }

    if ($snotes['important'] <> "") {
        $smarty->assign('site_important', $snotes['important']);
        //$body .= "<div class=\"noteimportant\">" . $snotes['important'] . "</div>";
    }

    if ($snotes['warning'] <> "") {
        $smarty->assign('site_warning', $snotes['warning']);
        //$body .= "<div class=\"notewarning\">" . $snotes['warning'] . "</div>";
    }

    if ($snotes['tip'] <> "") {
        $smarty->assign('site_tip', $snotes['tip']);
        //$body .= "<div class=\"notetip\">" . $snotes['tip'] . "</div>";
    }
}
//set flag to indicate that smarty template exists for this page
$isSmarty = true;
include ("template.inc");



$smarty->display('home.tpl');

?>
