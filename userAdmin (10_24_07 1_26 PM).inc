<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$js = "function newStudent(id, site)
{
    var id=prompt(\"Enter Student Number for new student \");
    if (id!=null && id!=\"\") {
        loc = location.href;
        window.location=\"index.php?cmd=newStudent&id=\" + id + \"&site=\" + site; 
     }
 }
";
 
$site = $_GET['site'];
$status = $_GET['status'];


if ($status=="Active") {
  $opstatus = "Inactive";
  $statusDisplay = "<font size=4 color=green>$status</font>";
}
else { 
  $opstatus = "Active";
  $statusDisplay = "<font size=4 color=red>$status</font>";
}

debugPrint("STATUS: $status OPSTATUS $opstatus");

$users = getUsers($site, $status);
$siteInfo = getSiteInfo($site);
$sitename = $siteInfo['name'];
$sitelogo = $logoURL . $siteInfo['logo'];
$Display = Privilege(A30);
/*
$newStudent = "<center><a href=\"javascript:newStudent('$id','$site');\">New Student</a></center>";

$newStudent = "<center><form><input type=button value=\"New Student\" onClick=\"javascript:newStudent('$id','$site');\"></form></center>";
*/
$newStudent = "<center><form><input type=button value=\"New Student\" onClick=\"javascript:window.location='index.php?cmd=newStudent&site=$site ';\"></form></center>";

//$newStudent = "<a href=\"javascript:alert('test');\">test</a>";

for ($i=0;$i<count($users); $i++) {
  $name = $users[$i]['name'];
  $user = $users[$i]['user'];
  $type = $users[$i]['type'];
  $email = $users[$i]['email'];
  $id = $users[$i]['userid'];
 
  if(Privilege(A30) == 'district') {
      $setEdit = "<a href=index.php?cmd=userInfo&id=$id>Status/Info</a> &nbsp;&nbsp;<a href=index.php?cmd=permissions&user=$id>Privileges</a>";
      $newTeacher = "<div>
                      <form name=newteacher method=get action=index.php>
                        <input type=hidden name=cmd value=userInfo>
                        <input type=hidden name=type value=Teacher>
                        <input type=hidden name=site value=$site>                      
                        <input type=hidden name=status value=$status>                      
                        <input type=submit value='New Teacher'>
                      </form></div>";
      $newAdmin = "<div><br>
                      <form name=newadmin method=get action=index.php>
                        <input type=hidden name=cmd value=userInfo>
                        <input type=hidden name=type value=Administrator>
                        <input type=hidden name=site value=$site>                      
                        <input type=hidden name=status value=$status>                      
                        <input type=submit value='New Admin'>
                      </form></div>
										</div>";
  }
 
  $entry = "<tr><td>$name</td><td>$user</td><td>$email&nbsp;</td><td>$setEdit&nbsp;</td></tr>";
//  if($type == "Student") { $studentList .= $entry; }
  if($type == "Teacher") { $teacherList .= $entry; }
  if($type == "Administrator") { $adminList .= $entry; }
}

$siteList = getSitesOptions($site);

$pulldown = "
<form name=ptime method=get action=\"index.php\">
<input type=hidden name=cmd value=userAdmin>
<input type=hidden name=status value=$status>
<select name=\"site\" onChange=\"submit()\">
	$siteList
</select>
</form>";

$body .= "<div align=\"center\">
							<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
								<tr>
									<td>
										<div align=\"left\">
											<br>
											<div align=\"left\">
												<font size=\"4\" color=\"#cc0000\">DART User Management Area</font><br>$pulldown
												<br>
                      </div>
											<div class=\"noteimportant\">
												This is the area for admins to perform most user-related functions. Only school admins and district office support staff can view these items, although principals can delegate some duties to teachers. District Office view will have to be different - due to multiple sites and many users - it will have to have 100 users to a page, and several separate pages for management.</div><br><br>$newStudent<br><br>
											<table width=\"75%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
												<tr>
													<td width=\"34%\">
														<div align=\"center\">
															<img src=\"$sitelogo\" alt=\"\" border=\"0\"></div>
													</td>
													<td nowrap width=\"66%\">
														<div align=\"center\">
															<font size=\"4\">$sitename: Teacher Management<br>$statusDisplay<br>
																<br>

															</font><font size=\"2\"><a href=index.php?cmd=userAdmin&site=$site&status=$opstatus>$opstatus User List</a></font></div>
													</td>
												</tr>
											</table>

											<div align=center>
											<table width=600 border=\"1\">
												<tbody>
													<tr>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Name</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Username</b></font></div>
														</td>

														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Email</b></font></div>
														</td>
														<td bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Changes</b></font></div>
														</td>
													</tr>
													$teacherList
												</tbody>
											</table>
											
                      <br><br>$newTeacher<br><br>	
                      										
											<div align=left>
                      <table width=\"75%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
												<tr>
													<td width=\"34%\">
														<div align=\"center\">
															<img src=\"$sitelogo\" alt=\"\" border=\"0\"></div>
													</td>
													<td nowrap width=\"66%\">
														<div align=\"center\">
															<font size=\"4\">$sitename: Administrator Management<br>$statusDisplay<br>
																<br>

															</font><font size=\"2\"><a href=index.php?cmd=userAdmin&site=$site&status=$opstatus>$opstatus User List</a></font></div>
													</td>
												</tr>
											</table>
											</div>
											<div align=center>
											<table width=600 border=\"1\">
												<tbody>
													<tr>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Name</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Username</b></font></div>
														</td>

														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Email</b></font></div>
														</td>
														<td bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Changes</b></font></div>
														</td>
													</tr>
													$adminList
												</tbody>
											</table></div>
                    $newAdmin											
									</td>
				        </tr>
							</table>
						</td>
	        </tr>
				</table>
			</div>";

include ("template.inc");
?>
