<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

  include_once ("sip_functions.inc");
 
  debugPrint( "Mcmd: " . $mcmd);

  switch($mcmd) {
    case "siphome":
        include_once("siphome.inc");
        break;     
    case "sipdrilldown":
        include_once("sipdrilldown.inc");
        break;     
    case "scores":
        include_once("scores.inc");
        break;     
    case "scoresadmin":
        include_once("scoresadmin.inc");
        break;     
    case "districtsip":
        include_once("districtsip.inc");
        break;     
    case "sitesip":
        include_once("sitesip.inc");
        break;     
    case "teachersip":
        include_once("teachersip.inc");
        break;     
    case "staterep":
        include_once("staterep.inc");
        break;     
    case "overallsip":
        include_once("overallsip.inc");
        break;     
    case "createsip":
        include_once("createsip.inc");
        break;     
    case "showaction":
        include_once("actiontest.inc");
        break;     
    case "actionsave":
        include_once("actionsave.inc");
        break;     
    case "createTeacherSip":
        include_once("createTeacherSip.inc");
        break;     
    case "initialize":
    	echo "Starting Initialization:<br>";
        initializeYear();
        break;     
    case "addAction":
    case "deleteAction":
        include_once("actionHandler.inc");
        break;     
    case "editAction":
        include_once("editAction.inc");
        break;     
    case "sipedit":
        include_once("sipedit.inc");
        break;     
    case "testsip":
        include_once("testsip.inc");
        break;     
    case "deletesip":
        include_once("deletesip.inc");
        break;     
    default:
        include_once("siphome.inc");
        break;
  }

?>

