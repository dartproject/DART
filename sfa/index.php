<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

  $debugflag = $_GET['debug'];
  $currentUser = "";
  $currentUserID = "";
  $currentUserName = "";
  $currentMySite = "";
  $currentSite = "";
  $currentPriv = "";
  $currentPrivB = "";
  $currentScopeA = "";
  $currentScopeB = "";
  
  session_start();
  
  error_reporting (0);

  include_once ("lib/machine.config.inc");
  include_once ("lib/config.inc");
  include_once ("lib/ez_sql.php");
  include_once ("lib/function.inc");
  
  debugPrint("DebugFlag before session: $debugflag<br>");

  getMyGlobals();


  debugPrint("Debug Flag right after session_start: $debugflag<br>");
 
 
  //$userID =  $currentUserID;
  debugPrint("Debug Flag before SiteID: $debugflag<br>");
  //$siteID = getSite();
  debugPrint("Debug Flag after SiteID: $debugflag<br>");
  
  $cmd = $_GET['cmd'];
  $p1 = $_GET['p1'];
  $p2 = $_GET['p2'];
  $p3 = $_GET['p3'];
  $module = $_GET['module'];
  if(isset($module)) {
     $mcmd = $cmd;
     $cmd = "module";
  }
  

  if(isset($debugflag) and $debugflag <> "") { setDebug($debugflag);}

  debugPrint ("<b>CMD=> $cmd USERID - $currentUserID SITEID - $currentMySite P1=>$p1 P2=>$p2 P3=>$p3</b><br>");

  if(checkLogon() == FALSE and $cmd != 'processLogon' and $cmd != 'getPwd' and $cmd != 'expired' and $cmd != 'logon' and $cmd != 'forget') {
   $cmd = 'logon';
  }  

  switch($cmd) {
    case "module":
        include($module . "/index.inc");
        break;
    case "newStudent":
        include ("newStudent.inc");
        break;
    case "saveAdvEditStudentInfo":
        include ("saveAdvEditStudentInfo.inc");
        break;
    case "editProfile":
        include ("editProfile.inc");
        break;
    case "updateProfile":
        include ("updateProfile.inc");
        break;
    case "advEdit":
        include ("advEdit.inc");
        break;
    case "saveAdvToggle":
        include ("saveAdvToggle.inc");
        break;
    case "saveLevels":
        include ("saveLevels.inc");
        break;
    case "handleLevel":
        include ("handleLevel.inc");
        break;
    case "editNotes":
        include ("editNotes.inc");
        break;
    case "initialize":
        include ("initialize.inc");
        break;
    case "forget":
        include ("forget.inc");
        break;
    case "getPwd":
        include ("getPwd.inc");
        break;
    case "sreport":
        include ("sreport.inc");
        break;
    case "permissions":
        include ("permissions.inc");
        break;
    case "setPermissions":
        include ("setPermissions.inc");
        break;
    case "userAdmin":
        include ("userAdmin.inc");
        break;
    case "userInfo":
        include ("userInfo.inc");
        break;
    case "updateUser":
        include ("updateUser.inc");
        break;
    case "upload":
        include ("upload.inc");
        break;
    case "savePermissions":
        include ("savePermissions.inc");
        break;
    case "reportsInd":
        include ("reportsInd.inc");
        break;
    case "reports":
        include ("reports.inc");
        break;
    case "pacingReport":
        include ("pacingReport.inc");
        break;
    case "progressReport":
        include ("progressReport.inc");
        break;
    case "pivot":
        include ("pivot.inc");
        break;
    case "drilldown":
        include ("drilldown.inc");
        break;
    case "search":
        include ("search.inc");
        break;
    case "searchResults":
        include ("searchResults.inc");
        break;
    case "handleGroup":
        include ("handleGroup.inc");
        break;
    case "test":
        include ("test.inc");
        break;
    case "saveNotes":
        include ("saveNotes.inc");
        break;
    case "history":
        include ("history.inc");
        break;
    case "toggleStudent":
        include ("toggleStudent.inc");
        break;
    case "saveStudentToggle":
        include ("saveStudentToggle.inc");
        break;
    case "showscores":
        include ("showscores.inc");
        break;
    case "toggle":
        include ("toggleSubjectLevel.inc");
        break;
    case "saveToggle":
        include ("saveToggle.inc");
        break;
    case "studentInfo":
        include ("studentInfo.inc");
        break;
    case "saveStudentInfo":
        include ("saveStudentInfo.inc");
        break;
    case "processLogon":
        include ("processLogon.inc");
        break;
    case "home":
        include ("home.inc");
        break;
    case "editlist":
        include ("editlist.inc");
        break;
    case "deletelist":
        include ("deleteList.inc");
        break;
    case "updateListName":
        include ("updateListName.inc");
        break;
    case "updateListType":
        include ("updateListType.inc");
        break;
    case "newlist":
        include ("newList.inc");
        break;
    case "updatelist":
        include ("updatelist.inc");
        break;
    case "expired":
    case "logout":
        include ("logout.inc");
        break;
    case "logon":
        include("logon.inc");
        break;
    case "noPrivilege":
        include("noPrivilege.inc");
        break;
    default:
        include("home.inc");
        break;
  }

?>
