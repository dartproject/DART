<?php

// ==================================================================

//  Author: Robert Joseph (dart@vizmotion.com)

//	 Web: http://wiki.bssd.org/index.php/DART_System

// ==================================================================



  include_once ("sped_functions.inc");

 

  debugPrint( "Mcmd: " . $mcmd);



  switch($mcmd) {

    case "spedhome":

        include_once("spedhome.inc");

        break;     

    case "spedlist":

        include_once("spedlist.inc");

        break;     

    case "spedhistory":

        include_once("spedhistory.inc");

        break;     

    case "spededit":

        include_once("spededit.inc");

        break;     

    case "handleSpedGroup":

        include_once("handleSpedGroup.inc");

        break;     
        
    case "setsped":

        include_once("setsped.inc");

        break;     

    default:

        include_once("spedhome.inc");

        break;

  }



?>