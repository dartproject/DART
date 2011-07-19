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

include_once ("lib/machine.config.php");
include_once ("lib/config.inc");
include_once ("lib/ez_sql.php");
include_once ("lib/function.inc");


getMyGlobals();

$res2 = array();
$sql = "SELECT studentid, student.fname, student.lname  FROM student WHERE ";

//limit search to site if user not district wide
if (Privilege(A27) == 'site') {
    $sql .= "site='" . $currentMySite . "' AND";
}

if (isset($_GET['term']))
    $sql .= ' (student.fname LIKE "' . $_GET['term'] . '%" OR 
            student.lname LIKE "' . $_GET['term'] . '%" OR 
            CONCAT_WS(\' \', student.fname, student.lname) LIKE "' . $_GET['term'] . '%") ';

$sql .= "order by 2 asc;";

//run query
$query_results = $db->get_results($sql, ARRAY_A);

//read results
$result=array();
if($query_results != NULL) {
foreach ($query_results as $i) {
        $k['value'] = $i['fname'] . ' ' . $i['lname'];
        $k['studentID'] = $i['studentid'];
        array_push($result, $k);
    }
}

echo json_encode($result);
?>
