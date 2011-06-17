<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

  include_once ("testing_functions.inc");
 
  debugPrint( "Mcmd: " . $mcmd);

  switch($mcmd) {
    case "testingHome":
        include_once("testingHome.inc");
        break;     
    case "importScores":
        include_once("importScores.inc");
        break;     
    case "editTestScores":
        include_once("editTestScores.inc");
        break;     
    case "showGroupTestScores":
        include_once("showGroupTestScores.inc");
        break;     
    case "showIndividualTestScores":
        include_once("showIndividualTestScores.inc");
        break;     
    case "importData":
        include_once("importData.inc");
        break; 
    case "compare":
        include_once("compare.php");
        break;
    default:
        include_once("testingHome.inc");
        break;
  }

?>