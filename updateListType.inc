<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
    $listID = $_POST['p1'];
    $type = $_POST['p2'];
    $userid = $_POST['userid'];


    updateListType($listID, $type, $userid);

    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editlist&p1=$listID\">");


?>
