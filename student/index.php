<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

  $debugflag = $_GET['debug'];

  $currentStudent = "";
  $currentStudentID = "";
  $currentStudentName = "";
  $currentMySite = "";
  $currentSite = "";
  $currentPriv = "";
  $currentPrivB = "";
  $currentScopeA = "";
  $currentScopeB = "";
  
  session_start();
  
//  error_reporting (0);

  include_once ("../lib/machine.config.php");
  include_once ("../lib/config.inc");
  include_once ("../lib/ez_sql.php");
  include_once ("../lib/function.inc");
 
  getStudentGlobals();
   
  $cmd = $_GET['cmd'];
  
  if(isset($debugflag) and $debugflag <> "") { setDebug($debugflag);}

  debugPrint ("<b>CMD=> $cmd USERID - $currentStudentID SITEID - $currentMySite P1=>$p1 P2=>$p2 P3=>$p3</b><br>");

  if(checkStudentLogon() == FALSE and $cmd != 'processLogon' and $cmd != 'getPwd' and $cmd != 'expired' and $cmd != 'logon' and $cmd != 'forget') {
   $cmd = 'logon';
  }  
debugPrint("Cmd = $cmd");

  switch($cmd) {
    case "pacingReport":
        include ("../pacingReport.inc");
        break;
    case "progressReport":
        include ("../progressReport.inc");
        break;
    case "sreport":
        include ("../sreport.inc");
        break;
    case "processLogon":
        include ("processLogon.inc");
        break;
    case "editProfile":
        include ("editProfile.inc");
        break;
    case "updateProfile":
        include ("updateProfile.inc");
        break;
    case "logon":
        include("logon.inc");
        break;
    case "forget":
        include ("forget.inc");
        break;
    case "getPwd":
        include ("getPwd.inc");
        break;
    case "expired":
    case "logout":
        include ("logout.inc");
        break;
    case "me":
        include ("studentScores.inc");
        break;
    case "history":
        include ("../history.inc");
        break;

    case "home":
        include ("../toggleStudent.inc");
        break;
    default:
        include ("../toggleStudent.inc");
        break;
  }

?>
