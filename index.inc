<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

  include_once ("sfa_functions.inc");
 
  debugPrint( "Mcmd: " . $mcmd);

  switch($mcmd) {
    case "gs":
        debugPrint("Entering gs-2");
        include_once("gs.inc");
        debugPrint("Exit gs");
        break;
    case "drilldown":
        include_once ("sfadrill.inc");
        break;
    case "sfaedit":
        include_once("sfaedit.inc");
        break;
    case "sfainput":
        include_once("sfainput.inc");
        break;
    case "savesfa":
        include_once("savesfa.inc");
        break;
    case "sfahome":
        include_once("sfahome.inc");
        break;
    case "wing":
        include_once("wing.inc");
        break;
    case "root":
        include_once("root.inc");
        break;
    case "tutor":
        include_once("tutor.inc");
        break;
    case "savetutor":
        include_once("savetutor.inc");
        break;
    case "rrprofile":
        include_once("rrprofile.inc");
        break;
    case "stsreport":
        include_once("stsreport.inc");
        break;
    case "stgreport":
        include_once("stgreport.inc");
        break;
    case "sfa8wkreport":
        include_once("sfa8wkreport.inc");
        break;     
    default:
        include_once("sfahome.inc");
        break;
  }

?>

