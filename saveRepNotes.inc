<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

    $site = urlencode($_POST['selectedSite']);
    $notes = $_POST['notes'];

  saveRepNotes($site, $notes);
  
debugPrint("<a href=index.php?cmd=editRepNotes&site=$site>Go To Page</a>");

if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editRepNotes&site=$site\">");
    }


?>
