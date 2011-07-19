<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once("lib/YearQuarter.inc");

if (isset($_GET['debug']))
    $debugflag = $_GET['debug'];
//  $debugflag="on";
//For Chrome PHPConsole
require_once('debugTools/PhpConsole.php');
PhpConsole::start();

$currentUser = "";
$currentUserID = "";
$currentUserName = "";
$currentMySite = "";
$currentSite = "";
$currentPriv = "";
$currentPrivB = "";
$currentScopeA = "";
$currentScopeB = "";
$loggedInUser = null;

session_start();

error_reporting(1);
error_reporting(E_ALL);

include_once ("lib/machine.config.php");
include_once ("lib/config.inc");
include_once ("lib/ez_sql.php");
include_once ("lib/function.inc");
include_once ("lib/PasswordHash.php");
require_once ("lib/security/Privileges.php");
require_once ("lib/security/PScopeType.php");

date_default_timezone_set($timezone);

if (isset($debugflag))
    debugPrint("DebugFlag before session: $debugflag<br>");
else
    debugPrint("DebugFlag before session: DebugFlag is not initiated <br>");

if (isset($_SESSION['sessionUserID'])) {
     $loggedInUser = new User($_SESSION['sessionUserID'], $db);
}

getMyGlobals();


foreach ($modules as $module) {
    include_once("$module/config.inc");
}

if (isset($debugflag))
    debugPrint("Debug Flag right after session_start: $debugflag<br>");
else
    debugPrint("Debug Flag right after session_start: DebugFlag is not initiated <br>");

//$userID =  $currentUserID;

if (isset($debugflag))
    debugPrint("Debug Flag before SiteID: $debugflag<br>");
else
    debugPrint("Debug Flag before SiteID: \$debugflag not initiated<br>");
//$siteID = getSite();

if (isset($debugflag))
    debugPrint("Debug Flag after SiteID: $debugflag<br>");
else
    debugPrint("Debug Flag after SiteID: \$debugflag not initiated<br>");

if (isset($_GET['cmd']))
    $cmd = $_GET['cmd'];
else
    $cmd="";

if (isset($_GET['p1']))
    $p1 = $_GET['p1'];
else
    $p1="";

if (isset($_GET['p2']))
    $p2 = $_GET['p2'];
else
    $p2="";

if (isset($_GET['p3']))
    $p3 = $_GET['p3'];
else
    $p3="";


if (isset($_GET['module'])) {
    $mcmd = $cmd;
    $cmd = "module";
    $module = $_GET['module'];
}


if (isset($debugflag) and ($debugflag <> "")) {
    setDebug($debugflag);
}

debugPrint("<b>CMD=> $cmd USERID - $currentUserID SITEID - $currentMySite P1=>$p1 P2=>$p2 P3=>$p3</b><br>");
/*
  $loggedIn = checkLogon();

  if( $loggedIn != "" and $cmd != 'processLogon' and $cmd != 'getPwd' and $cmd != 'expired' and $cmd != 'logon' and $cmd != 'forget') {
  if($loggedIn != "") {
  $_GET['msg'] = $loggedIn;
  }
  $cmd = 'logon';
  }
 */
if (checkLogon() == FALSE and $cmd != 'processLogon' and $cmd != 'getPwd' and $cmd != 'expired' and $cmd != 'logon' and $cmd != 'forget' && $cmd != 'resetPwd') {
    if (isset($loggedIn))
        if ($loggedIn != "") {
            $_GET['msg'] = $loggedIn;
            $_SESSION['sessionUserID'] = $loggedInUser->getID();
        }
    $cmd = 'logon';
}
//encryptPasswords();

switch ($cmd) {
    case "districtrep":
        include("districtrep.inc");
        break;
    case "teacherrep":
        include("teacherrep.inc");
        break;
    case "siterep":
        include("siterep.inc");
        break;
    case "fixProgress":
        include("fixProgress.inc");
        break;
    case "module":
        include($module . "/index.inc");
        break;
    case "rss":
        debugPrint("Here is we");
        include("rss.inc");
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
    case "editRepNotes":
        include ("editRepNotes.inc");
        break;
    case "saveRepNotes":
        include ("saveRepNotes.inc");
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
    case "resetPwd":
        include ("resetPwd.inc");
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
    case "test2":
        include ("test2.inc");
        break;
    case "test4":
        include ("test4.inc");
        break;
    case "saveNotes":
        include ("saveNotes.inc");
        break;
    case "history":
        include ("history.inc");
        break;
    case "historylogin":
        include ("historylogin.inc");
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
    case "updateSingleLevelScore":
        include ("updateSingleLevelScore.inc");
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
    case "exportlist":
        include ("exportlist.inc");
        break;
    case "duplist":
        include ("duplist.inc");
        break;
    case "updatelist":
        include ("updatelist.inc");
        break;
    case "uploadUpdate":
        include ("uploadUpdate.inc");
        break;
    case "uploadInput":
        include ("uploadInput.inc");
        break;
    case "progress":
        include ("progress.inc");
        break;
    case "updateProgress":
        include ("updateProgress.inc");
        break;
    case "alerts":
        include ("alerts.inc");
        break;
    case "expired":
    case "logout":
        include ("logout.inc");
        break;
    case "logon":
        include("logon.inc");
        break;
    case "modifyLevelState":
        include("modifyLevelState.inc");
        break;
    case "noPrivilege":
        include("noPrivilege.inc");
        break;
    /*
      // UNDER REPAIR
      case "transcriptsDefine":
      include("underrepair.inc");
      break;
      case "transcriptsProduce":
      include("underrepair.inc");
      break;
      case "transcriptInternals":
      include("underrepair.inc");
      break;
      case "transcriptDL":
      include("underrepair.inc");
      break;
      case "transcriptGrades":
      include("underrepair.inc");
      break;
      case "transcript2006":
      include("underrepair.inc");
      break;
      case "transcriptLoad":
      include("underrepair.inc");
      break;
      case "transcriptComputeNames":
      include("underrepair.inc");
      break;
      // ------ END UNDER REPAIR
     */ case "transcriptsDefine":
        include("transcriptsDefine.inc");
        break;
    case "transcriptsProduce":
        include("transcriptsProduce.inc");
        break;
    case "transcriptInternals":
        include("transcriptInternals.inc");
        break;
    case "transcriptDL":
        include("transcriptDL.inc");
        break;
    case "transcriptGrades":
        include("transcriptGrades.inc");
        break;
    case "transcript2006":
        include("transcript2006.inc");
        break;
    case "transcriptLoad":
        include("transcriptLoad.inc");
        break;
    case "transcriptComputeNames":
        include("transcriptComputeNames.inc");
        break;
    case "updateStudentLevel":
        include("updateStudentLevel.inc");
        break;
    case "disciplineList":
        include("disciplineList.inc");
        break;
    case "disciplineEdit":
        include("disciplineEdit.inc");
        break;
    case "disciplineCreate":
        include("disciplineCreate.inc");
        break;
    case "fix":
        include("transcript_ERR_Fix.inc");
        break;
    case "AttendanceCalendar":
        include("attendanceCalendar.inc");
        break;
    case "AttendanceCalendarEdit":
        include("attendanceCalEdit.inc");
        break;
    case "SchoolCalendar":
        include("schoolCalendar.inc");
        break;
    case "SchoolCalendarEdit":
        include("schoolCalendarEdit.inc");
        break;
    case "AttendanceList":
        include("attendanceList.inc");
        break;
    case "AttendanceListRecord":
        include("attendanceListRecord.inc");
        break;
    case "studentEnrollmentForm":
        include("studentEnrollmentForm.inc");
        break;
    case "studentTransferForm":
        include("studentTransferForm.inc");
        break;
    case "ChangeExitCode":
        include("changeExitCode.inc");
        break;
    case "ChangeEnterCode":
        include("changeEnterCode.inc");
        break;
    case "Movement":
        include("movement.inc");
        break;
    case "MovementSave":
        include("movementsave.inc");
        break;
    case "MovementView":
        include("movementview.inc");
        break;
    case "StudentEdit":
        include("studentEdit.inc");
        break;
    case "NewStudentMovement":
        include("newStudentMovement.inc");
        break;
    case "StudentEnter":
        include("studentEnter.inc");
        break;
    case "StudentExit":
        include("studentExit.inc");
        break;
    case "StudentShowDates":
        include("studentShowDates.inc");
        break;
    case "InternalError":
        include("internalerror.inc");
        break;
    case "Dashboard":
        include("dashboard.inc");
        break;
    case "AttendanceDrillDown":
        include("attendanceDrillDown.inc");
        break;
    case "HandleAttendanceGroup":
        include("handleAttendanceGroup.inc");
        break;
    case "ImportInterface":
        include("importInterface.inc");
        break;
    case "ImportFile":
        include("importFile.inc");
        break;
    case "StudentTranscriptEdit":
        include("studentTranscriptEdit.inc");
        break;
    case "bigRed":
        include("bigRed.inc");
        break;
    case "editStandards":
        include("editStandards.inc");
        break;
    case "standardManipulation":
        include("standardManipulation.inc");
        break;
    case "nextLevelEdit":
        include("nextLevelEdit.inc");
        break;
    case "standardOrder":
        include("standardOrder.inc");
        break;
    case "editQuarter":
        include("editQuarter.inc");
        break;
    case "saveSearchGroup":
        include("saveSearchGroup.inc");
        break;
    case "extraPacingReport":
        include("extraPacingReport.inc");
        break;
    case "editTranscripts":
        include("editTranscripts.inc");
        break;
    case "importWin":
        include("./lib/import/importWin.inc");
        break;
    case "importHTML":
        include("./lib/import/importHTML.inc");
        break;
    case "importCSV":
        include("./lib/import/importCSV.inc");
        break;
    case "preview":
        include("./lib/import/preview.inc");
        break;
    case "fixtestinglevel":
        include("fixtestinglevel.inc");
        break;
    case "edittestlevel":
        include("editTestLevel.inc");
        break;
    case "createsubject":
        include("createsubject.inc");
        break;
    case "createlevels":
        include("createlevels.inc");
        break;
    case "groupmanage":
        include("groupmanage.inc");
        break;
    case "graduation_report":
        include("graduation_report.inc");
        break;
    case "count":
        include("count.inc");
        break;
    case "updateTranscripts":
        include("updateTranscripts.inc");
        break;
    case "editsite":
        include("editsite.inc");
        break;
    case "editgs":
        include("editgs.inc");
        break;
    case "repcurrentcreate":
        include("repcurrentcreate.inc");
        break;
    case "update":
        include("Update.inc");
        break;
    case "gb":
        include("gb.inc");
        break;
    case "gb_edit":
        include("gb_edit.inc");
        break;
    case "gb_save":
        include("gb_save.inc");
        break;
    case "gb_save_edit":
        include("gb_save_edit.inc");
        break;
    case "gb_assignstd":
        include("gb_assignstd.inc");
        break;
    case "resetPass":
        encryptPasswords();
        break;
    case "updateAll":
        set_time_limit(900);
        $results = $db->get_results("SELECT * FROM studentlevel where final = '0000-00-00 00:00:00' ", ARRAY_A);
        $i = 0;
        $starttime = microtime(true);
        $prev = $startime;
        $num = $db->num_rows;
        echo "Start Update All (" . $num . ")";
        flush();
        ob_flush();
        foreach ($results as $r) {
            if (fmod($i++, 1000) == 0) {
                $time = round(microtime(true) - $prev, 2);
                $elapse = microtime(true) - $starttime;
                $prev = microtime(true);
                echo "<br>$i) $time - $elapse<br><br>";
                flush();
                ob_flush();
            }
//			echo "{$r['studentid']}-{$r['subject']}-{$r['level']};";
            flush();
            updateChange($r['studentid'], $r['subject'], $r['level']);
        }
        $final = microtime(true) - $starttime;
        echo "<br><br>Final Elaspe Time: $final<br><br>";
        echo round($final / ($num / 1000), 2) . " time per 100";
        break;
    case "showscoresEditInfo":
        include("showscoresEditInfo.inc");
        break;
    case "saveDB":
        include("saveDB.inc");
        break;
    case "ajax":
        $url = getValue($_GET, "url");
        if($url != null)
            include($url);
        break;
    default:
        include("home.inc");
        break;
}
?>
