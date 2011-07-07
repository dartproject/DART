<?php

/*
 *  Copyright (C) 2011 Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 *  Web: http://wiki.bssd.org/index.php/DART_System
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


$type = "";
if (isset($_GET['type']))
    $type = $_GET['type'];

if ($type == 'delete') {
    $ids = $_POST['selectNames'];
    removeStudentFromReport($ids, $currentUserID);
} else if ($type == 'clear') {
    removeAllfromReport($currentUserID);
} else if ($type == 'add') {
    $listid = $_GET['listid'];
    addListtoReport($listid, $currentUserID);
}

$reportstudents = getReportListItems($currentUserID);

$list1 = getMyList($currentUserID);
$ct = count($list1);
$list1[$ct]['listid'] = "";
$list1[$ct]['listname'] = "------ Server ------";
$list2 = getMyList($currentUserID, $currentMySite);
$lists = array_merge((array) $list1, (array) $list2);


$smarty->assign('studentList', $reportstudents);
$smarty->assign('listOptions', $lists);
$isSmarty = true;

include ("template.inc");

$smarty->display('transcriptsDefine.tpl');
?>

