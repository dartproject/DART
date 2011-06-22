<?php

$msg = $_GET[msg];
$smarty->assign('currentUserName',$currentUserName);
$smarty->assign('msg',$msg);
$isSmarty =true;

//$body .= "<div align=center><br><br><font size=\"4\" color=\"#cc0000\">Change Password :: $currentUserName </font><br>
//
//										<form name=updateProfile action=index.php?cmd=updateProfile method = post>
//
//										<table border=\"1\" cellspacing=\"2\" cellpadding=\"3\">
//                        <tr>
//													<td colspan=2 bgcolor=lightpink><font size=\"2\" color=\"#cc0000\"><b>$msg</b></font></td>
//												</tr>
//                        <tr>
//													<td><font size=\"2\" color=\"#cc0000\"><b>Old Password:</b></font></td>
//													<td><input type=\"password\" name=\"oldpwd\" value=\"\" size=\"40\"></td>
//												</tr>
//                        <tr>
//													<td><font size=\"2\" color=\"#cc0000\"><b>New Password:</b></font></td>
//													<td><input type=\"password\" name=\"pwd1\"  value=\"\" size=\"40\"></td>
//												</tr>
//												<td><font size=\"2\" color=\"#cc0000\"><b>New Password Retype:</b></font></td>
//													<td><input type=\"password\" name=\"pwd2\"  value=\"\" size=\"40\"></td>
//												</tr>
//												<tr>
//													<td colspan=2>
//														<div align=\"center\">
//															<input type=submit name=Update value=Update>
//													</td>
//												</tr>
//											</table>
//                    </form></div>";

include("template.inc");
$smarty->display("editProfile.tpl");

?>
