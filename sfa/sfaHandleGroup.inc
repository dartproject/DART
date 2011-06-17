<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$val = $_POST['studentID'];
$action = $_POST['action'];
$cmd2 = $_POST['cmd2'];

  switch($cmd2) {
    case "Group":
        $uval = array_unique($val); // gets rid of duplicate entries
        $lid = handleGroup($uval, $currentUserID, $action);
        echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editlist&p1=$lid\"> ");
        break;
    case "Export":
        $fn = exportSFAGroup($val);
        echo ("<html><body OnLoad=\"javascript: history.back();\" bgcolor=\"#F0F0F0\"></body></html>");
        break;
    default:
        echo "Bad call for cmd2 in HandleGroup.inc";
        break;
   }
  
?>
