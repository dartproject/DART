<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$id = $_GET['id'];
$msg = $_GET['msg'];

if(isset($id) and $id != "") {
$userObj = getUserInfo($id);
$name = $userObj['name'];
$user = $userObj['user'];
$email = $userObj['email'];
$type = $userObj['type'];
$site = $userObj['site'];
$status = $userObj['status'];
$homeroomMark = $userObj['homeroom'];
$readingMark = $userObj['reading'];
$tutorMark = $userObj['tutor'];
$mod = "Update";
} else {
$name = $_GET['name'];
$user = $_GET['user'];
$email = $_GET['email'];
$type = $_GET['type'];
$site = $_GET['site'];
$status = $_GET['status'];
$mod = "New";
}

if(isset($msg) and $msg != "") {
   $warning = "<tr bgcolor=lightpink><td colspan=3>$msg</td></tr>";
}

$userPictureInsert = "<table><tr><td>
													<td nowrap width=\"25%\">
														<div align=\"center\">
															<img src=\"$picture\" alt=\"$lname, $fname - SKK\" height=\"105\" width=\"95\" border=\"0\">
                              <br><form enctype=\"multipart/form-data\" name=upload method=post action=index.php?cmd=upload><input type=hidden name=id value=$id><input size=10 type=\"file\" name=\"pict_file\" class=\"textfield\" /><input type=submit name=activity value=go></div>

</td><td>&nbsp;</td></tr></table>";

$typePulldown = "<select name=\"type\" \">
	<option value=\"Student\" " . selected ($type, "Student") . ">Student</option>
	<option value=\"Teacher\" " . selected ($type, "Teacher") . ">Teacher</option>
	<option value=\"Administrator\" " . selected ($type, "Administrator") . ">Administrator</option>
</select>";

$sitePulldown = "<select name=\"site\" \">" .
     getSitesOptions($site) .
"</select>";
$statusPulldown = "<select name=\"status\" \">
	<option value=\"Active\" " . selected ($status, "Active") . ">Active</option>
	<option value=\"Inactive\" " . selected ($status, "Inactive") . ">Inactive</option>
</select>";

$homeroomPulldown = "<select name=\"homeroom\" \">
	<option value=\"\" " . selected ($homeroomMark, "") . ">No</option>
	<option value=\"X\" " . selected ($homeroomMark, "X") . ">Yes</option>
</select>";

$readingPulldown = "<select name=\"reading\" \">
	<option value=\"\" " . selected ($readingMark, "") . ">No</option>
	<option value=\"X\" " . selected ($readingMark, "X") . ">Yes</option>
</select>";

$tutorPulldown = "<select name=\"tutor\" \">
	<option value=\"\" " . selected ($tutorMark, "") . ">No</option>
	<option value=\"X\" " . selected ($tutorMark, "X") . ">Yes</option>
</select>";

function showMark ($val) {
  $ans = $val == 'X' ? "Yes" : "No";
  return $ans; 
}


$body .= "<div align=center><br><br><font size=\"4\" color=\"#cc0000\">User Access Basics :: $name - $status</font><br>

										<form name=updateUser action=index.php?cmd=updateUser method = post>
										<input type=hidden name=org_name value=$name>
										<input type=hidden name=org_user value=$user>
										<input type=hidden name=org_email value=$email>
										<input type=hidden name=org_type value=$type>
										<input type=hidden name=org_site value=$site>
										<input type=hidden name=org_status value=$status>
										<input type=hidden name=mod value=$mod>
										<input type=hidden name=id value=$id>
										
										<table border=\"1\" cellspacing=\"2\" cellpadding=\"3\">
											  $warning
												<tr>
													<td></td>
													<td bgcolor=\"#ccffff\">
														<div align=\"center\">
															<b>Current</b></div>
													</td>
													<td bgcolor=\"#ccffff\">
														<div align=\"center\">
															<b>New</b></div>
													</td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Name:</b></font></td>
													<td>$name&nbsp;</td>
													<td><input type=\"text\" value='$name' name=\"name\" size=\"40\"> </td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Username:</b></font></td>
													<td>$user&nbsp;</td>
													<td><input type=\"text\" value='$user' name=\"user\" size=\"40\"> </td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Password:</b></font></td>
													<td>***********</td>
													<td><input type=\"password\" name=\"password1\" size=\"40\"></td>
												</tr>
												<td><font size=\"2\" color=\"#cc0000\"><b>Retype:</b></font></td>
													<td>***********</td>
													<td><input type=\"password\" name=\"password2\" size=\"40\"></td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Email:</b></font></td>
													<td>$email&nbsp;</td>
													<td><input type=\"text\" value='$email' name=\"email\" size=\"40\"></td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Type:</b></font></td>
													<td>$type&nbsp;</td>
													<td>$typePulldown</td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Site:</b></font></td>
													<td>$site&nbsp;</td>
													<td>$sitePulldown</td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Status:</b></font></td>
													<td>$status&nbsp;</td>
													<td>$statusPulldown</td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Homeroom:</b></font></td>
													<td>" . showMark($homeroomMark) . "&nbsp;</td>
													<td>$homeroomPulldown</td>
												</tr>
												<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Reading:</b></font></td>
													<td>" . showMark($readingMark) . "&nbsp;</td>
													<td>$readingPulldown</td>
												</tr>
																								<tr>
													<td><font size=\"2\" color=\"#cc0000\"><b>Tutor:</b></font></td>
													<td>" . showMark($tutorMark) . "&nbsp;</td>
													<td>$tutorPulldown</td>
												</tr>
												<tr>
													<td colspan=3>
														<div align=\"center\">
															<input type=submit value=$mod name=Update> 
															<input type=submit value=Cancel name=Cancel onClick='javascript:window.location.href=\"index.php?cmd=userAdmin&site=$site&status='$status'\"; return false;'></div>
													</td>
												</tr>
											</table>
                    </form></div>";

include("template.inc");

?>
