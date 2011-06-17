<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
        $id = $_GET['id'];
        $loc = $_GET['loc'];
        $field = $_GET['field'];
        $value = $_GET['value'];


debugPrint ("Location: " . $loc . "<br>");
debugPrint ("ID: " . $id . "<br>");
debugPrint ("Field: " . $field . "<br>");
debugPrint ("Value: " . $value . "<br>");

saveStudentValue($id, $field, $value);

echo "<html><body onLoad=\"javascript:history.go(-1)\"></body></html>";
/*
if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=$loc">");
    }
*/    
?>
