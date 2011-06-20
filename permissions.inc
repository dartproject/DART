<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$user = $_GET['user'];

$info = getUserInfo($user);
$privA = $info['privilegeA'];
$privB = $info['privilegeB'];
$scopeA = $info['scopeA'];
$scopeB = $info['scopeB'];
$name = $info['name'];
$email = $info['email'];
$type = $info['type'];
$site = $info['site'];
$Display = Privilege(A30);

//echo $Display;
//$Display = 'district';
$setDefaults = $Display == 'district' ? "
<a href=index.php?cmd=setPermissions&privA=103427102&scopeA=0&id=$user>Teacher</a><br>

<a href=index.php?cmd=setPermissions&privA=514468894&scopeA=268443664&id=$user>Principals</a><br>

<a href=index.php?cmd=setPermissions&privA=237644814&scopeA=237642766&id=$user>District Admin</a><br>

<a href=index.php?cmd=setPermissions&privA=246033418&scopeA=246033418&id=$user>NACTEC Staff</a><br>

<a href=index.php?cmd=setPermissions&privA=1051339806&scopeA=1051339806&id=$user>SUPERADMIN</a><br>

" : "";

$auxleftside = "<img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">P$privA<br><img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">S$scopeA"; 

function AddDistict($flag, $value) {
  return($flag == 'district' ? $value : "&nbsp;");
}

$body ="<div align=\"center\">
							<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
								<tr>
									<td>
										<div align=\"left\">
											<br>
											<div align=\"left\">
												<font size=\"4\" color=\"#cc0000\">DART User Access Settings </font><br>
											</div>
											<div class=\"noteimportant\">Each group of users  - teachers, classified staff, site administrators and district wide administrators - have default &quot;presets&quot; of access priveleges. In addition, this screen can be used by DART SysAdmins to make exception.  Site administrators can also use this screen to set the permission differently for any teacher or classified staff member at their site. </div>
										</div>
									</td>
								</tr>
								<tr align=center>
									<td>
												<form method=post action=index.php?cmd=savePermissions>
												<input type=hidden name=user value=$user>

											<font size=\"4\" color=\"#cc0000\">User :: $name - $type :: <a href=index.php?cmd=userAdmin&site=$site&status=Active>$site</a></font><br>
											<br>


												<div align=\"center\">
											  <p><button onClick='submit()'name=\"buttonName\" type=\"button\">Update</button></p>
									      </div>

											<fieldset style=\"width: 50%;\">
												<legend><font size=\"4\" color=\"#cc0000\">User Privileges - Granular View</font></legend>
									
                        <table align=\"left\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\">
													<tr>
														<td nowrap bgcolor=\"#ccffff\" >
																<b>Privilege</b>
														</td>
														<td nowrap align=center bgcolor=\"#ccffff\" >
																<b>None</b>
														</td>
														<td nowrap  align=center bgcolor=\"#ccffff\" >
																<b>Site</b>
														</td>
														<td nowrap  align=center bgcolor=\"#ccffff\" >
																<b>District</b>
														</td>
													</tr>
													
													
<!--------------------------------------------------------->


<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Be able to see the students toggle information without editing. Editing privileges over rule this setting.')\">
          A2) See Toggle Information Students Record
   </td>
    <td nowrap>
         <input type=\"radio\" name='A2' value='0' " .  addChecked(A2, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A2' value='A1_2'" .  addChecked(A2, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A2' value='A2_2'" .  addChecked(A2, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Be able to toggle student information.')\">
          A3) Edit Student Toggle Screen 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A3' value='0' " .  addChecked(A3, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A3' value='A1_4'" .  addChecked(A3, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A3' value='A2_4'" .  addChecked(A3, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('View basic student demographics information.')\">
          A4) View Basic Student Information Screen 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A4' value='0' " .  addChecked(A4, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A4' value='A1_8'" .  addChecked(A4, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A4' value='A2_8'" .  addChecked(A4, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Edit basic demographic information.')\">
          A5) Edit Student Information Data
   </td>
    <td nowrap>
         <input type=\"radio\" name='A5' value='0' " .  addChecked(A5, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A5' value='A1_16'" .  addChecked(A5, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A5' value='A2_16'" .  addChecked(A5, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to build/edit your own ad hoc list.')\">
          A11) Create Ad Hoc Groups 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A11' value='0' " .  addChecked(A11, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A11' value='A1_1024'" .  addChecked(A11, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A11' value='A2_1024'" .  addChecked(A11, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('The ability to see shared group lists')\">
          A12) View Site Shared Groups 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A12' value='0' " .  addChecked(A12, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A12' value='A1_2048'" .  addChecked(A12, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A12' value='A2_2048'" .  addChecked(A12, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('The ability to build/edit ad hoc list that are shared')\">
          A14) Create/Edit Shared Site Groups 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A14' value='0' " .  addChecked(A14, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A14' value='A1_8192'" .  addChecked(A14, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A14' value='A2_8192'" .  addChecked(A14, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to see unofficial report card for student information they have access to.')\">
          A18) View Report Card - Browser View 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A18' value='0' " .  addChecked(A18, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A18' value='A1_131072'" .  addChecked(A18, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A18' value='A2_131072'" .  addChecked(A18, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to see unofficial progress report for student information they have access to.')\">
          A20) View Progress Report - Browser Version 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A20' value='0' " .  addChecked(A20, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A20' value='A1_524288'" .  addChecked(A20, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A20' value='A2_524288'" .  addChecked(A20, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to see unofficial pacing report for student information they have access to.')\">
          A22) View Pacing Guide - Browser Version 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A22' value='0' " .  addChecked(A22, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A22' value='A1_2097152'" .  addChecked(A22, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A22' value='A2_2097152'" .  addChecked(A22, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to view and print out the official report cards.')\">
          A24) View / Run Report Card - Official Copy 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A24' value='0' " .  addChecked(A24, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A24' value='A1_8388608'" .  addChecked(A24, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A24' value='A2_8388608'" .  addChecked(A24, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to see and use the pivot table.')\">
          A26) View / Export Pivot Table Data 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A26' value='0' " .  addChecked(A26, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A26' value='A1_33554432'" .  addChecked(A26, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A26' value='A2_33554432'" .  addChecked(A26, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to use search')\">
          A27) Search / View / Export DART User Records 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A27' value='0' " .  addChecked(A27, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A27' value='A1_67108864'" .  addChecked(A27, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A27' value='A2_67108864'" .  addChecked(A27, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('View the notes from the site or district')\">
          A28) View Site Notes Fields 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A28' value='0' " .  addChecked(A28, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A28' value='A1_134217728'" .  addChecked(A28, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A28' value='A2_134217728'" .  addChecked(A28, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Create notes for site or district depending on privilege')\">
          A29) Create / Edit Notes Fields 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A29' value='0' " .  addChecked(A29, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A29' value='A1_268435456'" .  addChecked(A29, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A29' value='A2_268435456'" .  addChecked(A29, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Ability to access the privilege information.')\">
          A30) Set User Access Settings 
   </td>
    <td nowrap>
         <input type=\"radio\" name='A30' value='0' " .  addChecked(A30, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A30' value='A1_536870912'" .  addChecked(A30, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A30' value='A2_536870912'" .  addChecked(A30, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('ADVANCE: Create and Edit All Student Information')\">
          A6) Edit Student Information Data
   </td>
    <td nowrap>
         <input type=\"radio\" name='A6' value='0' " .  addChecked(A6, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A6' value='A1_32'" .  addChecked(A6, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A6' value='A2_32'" .  addChecked(A6, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to SFA module')\">
          A8) Report Card Notes
   </td>
    <td nowrap>
         <input type=\"radio\" name='A8' value='0' " .  addChecked(A8, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A8' value='A1_128'" .  addChecked(A8, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A8' value='A2_128'" .  addChecked(A8, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access advance history specifications')\">
          A10) Capability to access advance history capabilities
   </td>
    <td nowrap>
         <input type=\"radio\" name='A10' value='0' " .  addChecked(A10, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A10' value='A1_512'" .  addChecked(A10, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A10' value='A2_512'" .  addChecked(A10, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access student promotion system')\">
          A13) Capability to promote students
   </td>
    <td nowrap>
         <input type=\"radio\" name='A13' value='0' " .  addChecked(A13, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A13' value='A1_4096'" .  addChecked(A13, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A13' value='A2_4096'" .  addChecked(A13, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access student promotion system')\">
          A17) Setting up Attendance Lists
   </td>
    <td nowrap>
         <input type=\"radio\" name='A17' value='0' " .  addChecked(A17, $privA, $scopeA, "No") . ">
   </td>
   <td>
          
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A17' value='A2_65536'" .  addChecked(A17, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access student promotion system')\">
          A19) Edit School Calendar
   </td>
    <td nowrap>
         <input type=\"radio\" name='A19' value='0' " .  addChecked(A19, $privA, $scopeA, "No") . ">
   </td>
   <td>
          
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A19' value='A2_262144'" .  addChecked(A19, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to discipline pages')\">
          A21) Access to Discipline Pages
   </td>
    <td nowrap>
         <input type=\"radio\" name='A21' value='0' " .  addChecked(A21, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A21' value='A1_1048576'" .  addChecked(A21, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A21' value='A2_1048576'" .  addChecked(A21, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to moving students')\">
          A23) Access to Move Student
   </td>
    <td nowrap>
         <input type=\"radio\" name='A23' value='0' " .  addChecked(A23, $privA, $scopeA, "No") . ">
         
   </td>
   <td>
          
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A23' value='A2_4194304'" .  addChecked(A23, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to edit levels')\">
          A25) Access to Edit Level Information
   </td>
    <td nowrap>
         <input type=\"radio\" name='A25' value='0' " .  addChecked(A25, $privA, $scopeA, "No") . ">
         
   </td>
   <td>
          
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A25' value='A2_16777216'" .  addChecked(A25, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>
<tr> <td colspan=4 align=center> ----- SFA MODULE PRIVILEDGES BELOW ---</td></tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to SFA module')\">
          A7) Access to SFA Module
   </td>
    <td nowrap>
         <input type=\"radio\" name='A7' value='0' " .  addChecked(A7, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A7' value='A1_64'" .  addChecked(A7, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A7' value='A2_64'" .  addChecked(A7, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Edit Student information about SFA module')\">
          A9) Edit SFA Data
   </td>
    <td nowrap>
         <input type=\"radio\" name='A9' value='0' " .  addChecked(A9, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A9' value='A1_256'" .  addChecked(A9, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A9' value='A2_256'" .  addChecked(A9, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>


<tr> <td colspan=4 align=center> ----- SIP MODULE PRIVILEDGES BELOW ---</td></tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to SFA module')\">
          A15) Access to SIP Module
   </td>
    <td nowrap>
         <input type=\"radio\" name='A15' value='0' " .  addChecked(A15, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A15' value='A1_16384'" .  addChecked(A15, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A15' value='A2_16384'" .  addChecked(A15, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"#ffffcc\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Edit Student information about SIP module')\">
          A16) Edit SIP Data
   </td>
    <td nowrap>
         <input type=\"radio\" name='A16' value='0' " .  addChecked(A16, $privA, $scopeA, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='A16' value='A1_32768'" .  addChecked(A16, $privA, $scopeA, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='A16' value='A2_32768'" .  addChecked(A16, $privA, $scopeA, "Dist") .">") .
   "</td>
</tr>

<tr> <td colspan=4 align=center> ----- SPED MODULE PRIVILEDGES BELOW ---</td></tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to SPED module')\">
          B2) Access to SPED Module
   </td>
    <td nowrap>
        <input type=\"radio\" name='B2' value='0' " .  addChecked(B2, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B2' value='B1_2'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B2' value='B2_2'" .  addChecked(B2, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr> <td colspan=4 align=center> ----- TESTING MODULE PRIVILEDGES BELOW ---</td></tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to Testing module')\">
          B13) Access to Viewing Testing Module
   </td>
    <td nowrap>
        <input type=\"radio\" name='B13' value='0' " .  addChecked(B13, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B13' value='B1_4096'" .  addChecked(B13, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B13' value='B2_4096'" .  addChecked(B13, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to Testing module')\">
          B13) Access to Editing Testing Module
   </td>
    <td nowrap>
        <input type=\"radio\" name='B14' value='0' " .  addChecked(B14, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B14' value='B1_8192'" .  addChecked(B14, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B14' value='B2_8192'" .  addChecked(B14, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>


<tr> <td colspan=4 align=center> ----- EXPORT PRIVILEDGES BELOW ---</td></tr>
<tr align=center>
    <td nowrap align=left onMouseOver=\"return escape('Access to SFA module')\">
          B3) Dashoard Viewing
   </td>
    <td nowrap>
         <input type=\"radio\" name='B3' value='0' " .  addChecked(A8, $PRIVB, $scopeB, "No") . ">
   </td>
   <td>
          <input type=\"radio\" name='B3' value='B1_4'" .  addChecked(B3, $privB, $scopeB, "Site") . ">
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B3' value='B2_4'" .  addChecked(B3, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Export Discipline')\">
          B4) Drill Down Dashboard
   </td>
    <td nowrap>
        <input type=\"radio\" name='B4' value='0' " .  addChecked(B4, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B4' value='B1_8'" .  addChecked(B4, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B4' value='B2_8'" .  addChecked(B4, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Export Discipline')\">
          B5) Export Discipline
   </td>
    <td nowrap>
        <input type=\"radio\" name='B5' value='0' " .  addChecked(B5, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B5' value='B1_16'" .  addChecked(B5, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B5' value='B2_16'" .  addChecked(B5, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Export Discipline')\">
          B6) Export Attendance
   </td>
    <td nowrap>
        <input type=\"radio\" name='B6' value='0' " .  addChecked(B6, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B6' value='B1_32'" .  addChecked(B6, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B6' value='B2_32'" .  addChecked(B6, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Export Discipline')\">
          B7) Export Enter Exit
   </td>
    <td nowrap>
        <input type=\"radio\" name='B7' value='0' " .  addChecked(B7, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B2' value='B1_64'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B7' value='B2_64'" .  addChecked(B7, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Export Discipline')\">
          B8) Export Fall Oasis
   </td>
    <td nowrap>
        <input type=\"radio\" name='B8' value='0' " .  addChecked(B8, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B8' value='B1_128'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B8' value='B2_128'" .  addChecked(B8, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Modify Transcript')\">
          B9) Modify Additional Information on Transcripts
   </td>
    <td nowrap>
        <input type=\"radio\" name='B9' value='0' " .  addChecked(B9, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B9' value='B1_256'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B9' value='B2_256'" .  addChecked(B9, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>
<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Big Red Button')\">
          B10) Big Red Button
   </td>
    <td nowrap>
        <input type=\"radio\" name='B10' value='0' " .  addChecked(B10, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B10' value='B1_512'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B10' value='B2_512'" .  addChecked(B10, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Edit Standard Information')\">
          B11) Edit Standard Information
   </td>
    <td nowrap>
        <input type=\"radio\" name='B11' value='0' " .  addChecked(B11, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B11' value='B1_1024'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B11' value='B2_1024'" .  addChecked(B11, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<tr bgcolor=\"white\"  align=center>
    <td nowrap align=left onMouseOver=\"return escape('Edit Transcript Information')\">
          B12) Edit Transcript Information
   </td>
    <td nowrap>
        <input type=\"radio\" name='B12' value='0' " .  addChecked(B12, $privB, $scopeB, "No") . ">

   </td>
   <td>
<!--           <input type=\"radio\" name='B12' value='B1_2048'" .  addChecked(B2, $privB, $scopeB, "Site") . ">
-->
   </td>
   <td>" .
          AddDistict($Display, "<input type=\"radio\"  name='B12' value='B2_2048'" .  addChecked(B12, $privB, $scopeB, "Dist") .">") .
   "</td>
</tr>

<!--------------------------------------------------------->

													<tr>
														<td nowrap width=\"50%\"></td>
														<td nowrap width=\"25%\">
															<div align=\"center\">
																
															</div>
														</td>
														<td nowrap width=\"25%\">
															<div align=\"center\">
																
															</div>
														</td>
													</tr>
												</table>
											</fieldset>
										</div>
										<div align=\"center\">
											<p><button onClick='submit()'name=\"buttonName\" type=\"button\">Update</button></p>
										</div>
										<div align=\"center\">$setDefaults
											<br>
										</div>
									</td>
								</tr>
							</table>
							</form>
						</div>";
						
include ("template.inc");
?>
