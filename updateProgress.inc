<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

promoteStudents ($HTTP_POST_VARS);

$site = $_POST['site'];
debugPrint("Here");

echo "Your information has been saved.";

if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=progress&site=$site\">");
    }
    
?>