<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

    $site = urlencode($_POST['selectedSite']);
    $important = $_POST['important'];
    $warning = $_POST['warning'];
    $tip = $_POST['tip'];

  saveNotes($site, $important, $warning, $tip);
  
debugPrint("<a href=index.php?cmd=editNotes&site=$site>Go To Page</a>");

if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editNotes&site=$site\">");
    }


?>
