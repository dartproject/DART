<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once("lib/function_export.inc");

$listid = $_POST['listid'];
$val = $listid != "" ? getListArray($listid) : $_POST['studentID'];

$action = $_POST['action'] == "" ? $_GET['action'] : $_POST['action'];
$cmd2 = $_POST['cmd2'] =="" ? $_GET['cmd2'] : $_POST['cmd2'];
$uval = array_unique($val); // gets rid of duplicate entries
$start = $_POST['startdate'];
$end = $_POST['enddate'];

  switch($cmd2) {
    case "Group":
        $lid = handleGroup($uval, $currentUserID, $action);
        echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editlist&p1=$lid\"> ");
        break;
    case "Export":
        $fn = exportGroup($val);
        break;
    case "FallOasis":
        exportFallOasis($uval);
        break;
    case "Attendance":
    	exportAttendanceCount($uval, $start, $end);
        break;
    case "Discipline":
		exportDiscipline($uval, $start, $end);
        break;
    case "EnterExit":
		exportEnterExit($uval, $start, $end);
        break;
    case "SummerOasis":
		exportSummerOasis($uval, $start, $end);
//		exportSummerOasisList($listid, $start, $end);
        break;
    case "AllAttendance":
		exportAllAttendance($uval, $start, $end);
        break;
    default:
        echo "Bad call for cmd2 in HandleGroup.inc";
        break;
   }
  
?>
