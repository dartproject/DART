<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$msg = $_GET['msg'];
if(isset($msg)) {
   $msg = "<tr><td colspan=3 bgcolor=pink>$msg</td></tr>";
}
$body .="<form method=get action=index.php>
<input type=hidden name=cmd value=getPwd>
							<table width=\"95%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
								<tr>
									<td bgcolor=\"white\">
										<div align=\"left\">
											<br>
											<div align=\"left\">
												<font size=\"4\" color=\"#cc0000\">DART Password Recovery</font><br>
												<br>
											</div>

											<div class=\"noteimportant\">
												Enter your username below, and your password will be sent to the email address associated with your account.  If you do not remember your username, please <a title=\"DART Support\" href=\"mailto:dart@bssd.org\">email us</a> for instructions.  All password recovery attempts are logged with IP and timestamp. You should receive your password within a few minutes.</div>
										</div>
										<div align=\"center\">
											<br>
											<table border=\"1\">
												<tbody>
$msg
													<tr>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<img src=\"http://dart.bssd.org/images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Example</b></font></div>

														</td>
														<td bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Your Username</b></font></div>
														</td>
													</tr>
													<tr>
														<td nowrap><font size=\"3\" color=\"#cc0000\"><b>DART Username:</b></font></td>

														<td nowrap>
															<div align=\"center\">
																<font size=\"2\">tommystudent</font></div>
														</td>
														<td nowrap>
															<div align=\"center\">
																<input name=\"username\" type=\"text\" size=\"40\"></div>
														</td>

													</tr>
												</tbody>
											</table>
											<br>
											<input type=submit name=\"buttonName\" value=\"Request Password\"><br>
										</div>
									</td>
								</tr>
							</table>
            </form>";
                

include("template_wo_left.inc");
	
?>
