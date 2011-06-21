<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
        $user=$_POST['user'];;
        $pwd=$_POST['password'];
        $id = logon($user, $pwd);
        debugPrint("Process Login ID: $id<br>");
        if ($id != "0") {
             setLogon ();
             logHistory("Login", $user, $password, "", $id);
             echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=home\">");
        } else {
             logHistory("Bad Login", $user, $password, "");
             echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=logon\">");
        }
?>
