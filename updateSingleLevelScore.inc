<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
        $id = $_GET['id'];
        $subject = $_GET['subject'];
        $level = $_GET['level'];


debugPrint ("ID: " . $id . "<br>");
debugPrint ("Subject: " . $subject . "<br>");
debugPrint ("Level: " . $level . "<br>");

updateSingleLevelScore($id, $subject, $level);


if($debug <> "on") {
    echo "<html><body onLoad=\"javascript:history.go(-1)\"></body></html>";
//    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=$loc">");
    }
    
?>
