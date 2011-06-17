<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
        $msg = $_GET['msg'];
        logHistory("Logout - $cmd", $userID, "", "");
        unsetStudentLogon();

        echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=logon&msg=$msg\">");
?>
