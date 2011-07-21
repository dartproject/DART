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

require_once("lib/security/Privileges.php");


if ($loggedInUser->isAuthorized(Privileges::USER_ACCESS_SETTINGS)) {

    $vars = $_POST;

    var_dump($vars);

    $errors = array();

    $fileName = "";


    if (strlen($vars["name"]) < 3) {
        array_push($errors, "School name must be a t least 3 characters long.");
    }

    if (isset($vars["siteid"]) AND strlen($vars["siteid"]) != 3)
        array_push($errors, "School abbreviation should have three characters");


    if ((($_FILES["file"]["type"] == "image/gif")
            || ($_FILES["file"]["type"] == "image/jpeg")
            || ($_FILES["file"]["type"] == "image/pjpeg"))
            && ($_FILES["file"]["size"] < 300000)) {
        if ($_FILES["file"]["error"] > 0) {
            array_push($errors, "Return Code: " . $_FILES["file"]["error"]);
        } else {
            if (file_exists($imageURL . "SchoolLogos/" . $_FILES["file"]["name"])) {
                //echo $_FILES["file"]["name"] . " already exists. ";
            } else {
                move_uploaded_file($_FILES["file"]["tmp_name"], $rootPATH . "/images/SchoolLogos/" . $_FILES["file"]["name"]);
                $fileName = ", logo = '" . $_FILES["file"]["name"] . "'";
            }
        }
    } else {
        //array_push($errors, "Invalid file");
    }

    $isSmarty = true;
    include ("template.inc");

    if (count($errors) == 0) {
        $newName = $vars['name'];
        if ($vars['submit'] == 'Update') {
            $origSite = getSiteInfo($vars['origSiteId']);
            $sql = "UPDATE site SET ";
            $sql .= " name= '$newName'";

            $sql .= $fileName;
            $sql .= " WHERE siteid = '" . $origSite['siteid'] . "'";

            $db->query($sql);
            $smarty->assign("msg", "Site updated");
            include("sitesView.inc");
        } else {

            $fileName = $_FILES["file"]["name"];
            $siteName = $vars['name'];
            $siteid = $vars['siteid'];
            $sql = "INSERT INTO site(siteid, name,logo) VALUES";
            $sql .= " ('$siteid','$siteName','$fileName');";

            $result = $db->query($sql);
            var_dump($result . " " . $sql);
            $smarty->assign("msg", "Site created");
            include("sitesView.inc");
        }
    } else {

        $smarty->assign('errors', $errors);
        $smarty->display('sitesEdit.tpl');
    }
}
?>
