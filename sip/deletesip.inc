<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$sid = $_GET['sid'];
$year = $_GET['year'];

deleteTeacherSip($sid);

if($debug <> "on") {
    header("Location: index.php?module=sip&cmd=siphome&year=$year");
    }
    
?>