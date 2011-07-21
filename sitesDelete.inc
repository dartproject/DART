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


if($loggedInUser->isAuthorized(Privileges::USER_ACCESS_SETTINGS)){
    
    $siteid = $_GET['siteid'];
    $sql = "DELETE FROM site WHERE siteid= '$siteid'";
    
    $db->query($sql);
    $smarty->assign("msg", 'Site deleted');
    include('sitesView.inc');
}
?>