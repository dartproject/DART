<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$A6Priv = Privilege(A6);

$leftside = "";
$auxleftside = "";
$leftside2 = "";
$but = "<a href=\"index.php?module=st&cmd=stshowreports\">ST Show Reports</a>";
$but2 = "<a href=\"index.php?cmd=transcriptsProduce\">Produce Transcript</a>";
$but3 = "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=transcriptsDefine\">Define Transcript</a>";

/********* Build Complete Left Side *************/
$leftside .= "<div align=\"left\">
		<b><font color=\"#0066ff\">Logged In As:</font></b><br>
		<img src=\"" . $imageURL ."dart1.gif\" alt=\"\" height=\"67\" width=\"77\" border=\"0\"><br>
		<b><font color=\"#0066ff\">$currentUserName</font></b>";

$leftside .= PDisplayB(B12) ? "<br>$but3<br><img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editTranscripts\">Edit Transcripts</a><br>" : "";
			
/******** Dart Home Information *********/		
$leftside .= "<br><b><font color=\"#0066ff\">DART Info<br></font></b>
		  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=logout\">Log Out</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=home\">Dart Home</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editProfile\">Edit Profile</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"mailto:dart@bssd.org\" target=_blank>Feedback</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=districtrep\" target=_blank>SIP Plan</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=siterep\" target=_blank>Site SIP Plan</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=teacherrep\" target=_blank>Teacher SIP Plan</a><br>";

/******* Able to Search ***********/
if(PDisplay(A27)) {
  $leftside .="<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=search\">Search</a><br>";
}

if(PDisplayB(B3)) {
  $leftside .="<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=Dashboard\">Dashboard</a><br>";
}

/***** Able to get to my groups *****/
if(PDisplay(A11)) {
			$leftside .= "<br>
			<font color=\"#0066ff\"><b>My Groups</b></font><br>" .	
      showMyList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color=\"#0066ff\"><br>');
}

if(PDisplay(A12)) {
			$leftside .= "<br><font color=\"#0066ff\"><b>Shared Groups<br>$currentMySite</b></font><br>"
    . showMyList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color="#0066ff"><br>', $currentMySite);
}

$sharedList = showSharedList($currentUserID, '<img src="images/10_h.gif" alt="" height="2" width="10" border="0">','<font color="#0066ff"><br>');
if($sharedList <> "") {
		$leftside .= "<br><font color=\"#0066ff\"><b>Private Shared List</b></font><br>$sharedList";
}

if(PDisplay(A11)) {
    $leftside .= "<br><font color=\"#0066ff\"><b>Manage Groups</b></font><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=newlist\">New Group</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editlist\">Edit Groups</a><br>";
}

if(PDisplay(A26+A24)) {
      $leftside .= "<br><font color=\"#0066ff\"><b>Reports</b></font><br>";
      }
      
if(PDisplay(A24)) {      
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=reportsInd\">Official</a><br>";
}

if(PDisplay(A26)) { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=pivot\">Drill Down!</a><br>
<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=extraPacingReport\">PASS</a><br>";
}

if(PDisplay(A30+A29)) { 
			$leftside .= "<br><font color=\"#0066ff\"><b>Admin Area</b></font><br>";
}			


if(PDisplay(A30)) { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=userAdmin&site=$currentMySite&status=Active\">Users $currentMySite</a><br>";
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=InternalError\">Internal Error</a><br>";
}
if(PrivilegeB(B10) != 'none') { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=bigRed\">Big Red Button</a><br>";
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=edittestlevel\">Edit Test Level</a><br>";
}
if(PrivilegeB(B11) != 'none') { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editStandards\">Edit Standards</a><br>";
}
if(PDisplay(A19)) { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=SchoolCalendar&site=DIO&year=$CurrentYear\">Edit School Cal</a><br>";
}

if(PDisplay(A13)) { 
            $leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=progress&site=$currentMySite\">Progress $currentMySite</a><br>";
}

if(PDisplay(A10)) { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=history\">History Toggle</a><br>";
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=historylogin\">History Login</a><br>";
}

if($A6Priv == 'district') {
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=uploadInput\">Mass Import</a><br>";
}

if(PDisplay(A29)) { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editNotes\">Edit Notes</a><br>";
}
if(PDisplay(A8)) { 
			$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editRepNotes\">Edit Report Notes</a><br>";
}

if(PDisplay(A29)) {
$leftside .= "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Enrollment Form\" href=\"http://www.bssd.org/enrollment_form.shtml\">Add Student</a><br>

<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Drop &amp; Transfer Form\" href=\"http://www.bssd.org/transfer_form.shtml\">Drop/ Transfer</a><br>

<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a title=\"DART Level Adjustment Form\" href=\"http://www.bssd.org/schedule_form.shtml\">Level Change</a><br>";
}

//$leftside .= PDisplay(A6, $AdminSec);

$leftside2 .= "<br><br><br><hr>
			<font color=\"#0066ff\"><b>Testing Area<br>1051339807</b></font><br>
			
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=permissions&user=208\">Permissions Robert</a><br>
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=permissions&user=62\">Permissions Margart</a><br>
			
			<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=toggleStudent&p1=560150\">Student TLA</a><br>
		$auxleftside
		</p>
</div>";

echo ($leftside . "<br>" . $moduleleft);
?>
