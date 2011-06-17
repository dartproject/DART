<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
        $listid = $_POST['listID'];
        $sub = $_POST['sub'];
        $lvl = $_POST['lvl'];

$location = $_POST['loc'];

debugPrint ("Location: " . $location . "<br>");
debugPrint ("<a href=$loc>Go To Page</a>");

    saveGrades ($HTTP_POST_VARS);

if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=$location\">");
    }
    
?>
