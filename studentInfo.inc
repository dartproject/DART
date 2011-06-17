<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$title = "User Management - DART System";
$id = $_GET['id'];

$student = getStudentInfo($id);
$studentScore = getStudentOverallScore($id);

$name = $student['fname']. " " . $student['lname'];
$picture = $student['picture'] != "" ? $student['picture'] : "no_photo.jpg";
$picture = $rootURL . "/images/student/" . $picture;
//$img = $rootURL . "/images/SchoolLogos/" . $student['logo'] ;
$img = $logoURL . $student['logo'];

$sitename = $student['name'] ;
 

$js = "function handleChange(value) {
     window.location=value;
     }
function editValue(title, field, fieldval)
{
    var name=prompt(\"Please edit \" + title, fieldval);
    if (name!=null && name!=\"\") {
        loc = location.href;
        window.location=\"index.php?cmd=saveStudentInfo&id=$id&field=\" + field + \"&value=\" + name; 
//        window.location.reload();
     }
 }";
// \"&loc=\" + loc;
function getv($field) {
 global $student;
 
 return ($student[$field]);
 }

function editv($name, $field, $fieldval) {
 $str = "<a href=\"javascript:editValue('$name','$field','$fieldval');\">$name</a>";
 return $str;
 }

$scoresTable = "<table width=\"100%\" border=\"1\">
												<tbody>
													<tr>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Content Area</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Level</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Overall</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>QPI</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Entered</b></font></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<b>TIL</b></div>
														</td>
														<td nowrap bgcolor=\"#ccccff\">
															<div align=\"center\">
																<font size=\"2\"><b>Status</b></font></div>
														</td>
													</tr>";
													
foreach ($studentScore as $res) {
   $scoresTable .= "<tr>
														<td nowrap><font size=\"2\">" . $res['sname'] . "</font></td>
														<td nowrap>
															<div align=\"center\">
																<font size=\"2\">" . $res['subject'] . " " . $res['level'] . "</font></div>
														</td>
														<td nowrap>
															<div align=\"center\">
																" . $res['score'] . "</div>
														</td>
														<td nowrap>
															<div align=\"center\">
																<font size=\"2\">" . $res['qpi'] . " </font></div>
														</td>
														<td nowrap>
															<div align=\"center\">
																" . $res['entered'] . " </div>
														</td>
														<td nowrap>
															<div align=\"center\">
																" . $res['til'] . " </div>
														</td>
														<td nowrap>
															<div align=\"center\">
																<csobj data=\"{ 0 = { label = &quot;Active&quot;; selected = &quot;YES&quot;; }; 1 = { label = &quot;Exit - Next Level&quot;; url = &quot;http://www.adobe.com&quot;; }; 2 = { label = &quot;Exit - Adjustment&quot;; url = &quot;http://www.adobe.com&quot;; }; }\" h=\"23\" t=\"URLPopup\" target=\"_top\" w=\"120\">
																	<form action=\"#\" method=\"post\" name=\"cs_form_name_5\">
																		<select name=\"cs_popup_name_5\" onchange=\"CSURLPopupShow(/*CMP*/'cs_form_name_5', /*CMP*/'cs_popup_name_5', '_top');\">
																			<option value=\"#\" selected>Active</option>
																			<option value=\"http://www.adobe.com\">Exit - Next Level</option>
																			<option value=\"http://www.adobe.com\">Exit - Adjustment</option>
																		</select>
																	</form>
																</csobj></div>
														</td>
													</tr>";
}

$scoresTable .= "</table>";													

$pulldown = "<form  name='go'>
							<select name='cs_popup_name_0' onChange='handleChange(this.value)'>
								<option value='#' selected>Jump to...</option>
								<option value='#toppage'>Top Of Page</option>
								<option value='#account'>Account Information</option>
								<option value='#demo'>Demographics</option>
								<option value='#profile'>Student Learning Profile</option>
								<option value='#levels'>Levels Information</option>
								<option value='#testing'>Testing Information</option>
							</select>
						</form>";

$body = "<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
								<tr>
									<td bgcolor=\"white\">
										<div align=\"left\">
											<br>
											<div align=\"left\">
												<a name='toppage'></a><font size=\"4\" color=\"#cc0000\">Individual Student Profile - Active Account</font><br>
												<br>
												$pulldown
                       </div>
											<div class=\"noteimportant\">This is the page that School Admins or District Admins would use to modify this user's account information, or to make level individual level changes. Multiple user level changes need to be handled through a different screen. Note that most of the fields below &quot;Account Information&quot; can't be directly modified by School Level Administrators. Only District Office users should be able to enter that data, and some of is auto-calculated from other screens. School Level Administrators can view this data, however.  										</div>
											<table width=\"75%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
												<tr>
													<td width=\"25%\">
														<div align=\"center\">
															<img src=\"$img\" alt=\"\" border=\"0\"></div>
													</td>
													<td nowrap width=\"50%\">
														<div align=\"center\">
															<font size=\"4\">$sitename School: $name<br>
																<br>
															</font><b><font size=\"2\">Last Access: </font></b><font size=\"2\">05/21/2006 at 3:21 p.m.</font><b><font size=\"2\"><br>
																</font></b><font size=\"4\"></font><font size=\"2\"><a href=\"index.php?cmd=history&student=$id\">Account History</a></font></div>
													</td>
													<td nowrap width=\"25%\">
														<div align=\"center\">
															<img src=\"$picture\" alt=\"$lname, $fname - SKK\" height=\"105\" width=\"95\" border=\"0\">
                              <br><form enctype=\"multipart/form-data\" name=upload method=post action=index.php?cmd=upload><input type=hidden name=id value=$id><input size=10 type=\"file\" name=\"pict_file\" class=\"textfield\" /><input type=submit name=activity value=Upload><input type=submit name=activity value=Delete></form></form></div>
													</td>
												</tr>
											</table>
											<br>
											<a name='account'></a><font size=\"4\">$name - Account Information </font><font size=\"4\"></font><br>
												$pulldown
											<br>
											<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>First Name: </b></font></td>
													<td width=\"35%\"><font size=\"2\">" . getv('fname') . "</font></td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Student ID: </b></font></td>
													<td width=\"35%\">" . getv('studentid') . "</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Middle Name: </b></font></td>
													<td width=\"35%\">" . getv('mname') . "</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Username:", "user", getv('user')) . " </b></font></td>
													<td width=\"35%\">" . getv('user') . "</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Last Name: </b></font></td>
													<td width=\"35%\">" . getv('lname') . "</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Password: </b></font></td>
													<td width=\"35%\">" . getv('pwd') . "</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">Mailing Address:</font></b></td>
													<td width=\"35%\">" . getv('addr') . "</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Alaska Student ID:</b></font></td>
													<td width=\"35%\">" . getv('alaskaid') ."</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">Village:</font></b></td>
													<td width=\"35%\">" . getv('village') ."</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>PowerSchool ID:</b></font></td>
													<td width=\"35%\">" . getv('psid') ."</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">State: </font></b></td>
													<td width=\"35%\">" . getv('state') ."</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Testing Grade Level: </b></font></td>
													<td width=\"35%\">" . getv('grade') ."</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">Zip Code: </font></b></td>
													<td width=\"35%\">" . getv('zip') ."</font></td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">Birthdate:</font></b></td>
													<td width=\"35%\">" . getv('bday') ."</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">Phone: </font></b></td>
													<td width=\"35%\">" . getv('phone') ."</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">Chronological Age: </font></b></td>
													<td width=\"35%\">" . age(getv('bday')) ."</td>
												</tr>
												<tr>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><b><font size=\"2\">" . editv("Email_Address:", "email", getv('email')) . " </font></b></td>
													<td width=\"35%\">" . getv('email') ."</td>
													<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Latest Enrollment: </b></font></td>
													<td width=\"35%\">" . getv('latestenroll') ."</td>
												</tr>
											</table>
											<div align=\"left\">
												<br>
												<a name='demo'></a><font size=\"4\">$name - Demographics </font><font size=\"4\"></font><br>
												$pulldown
												<br>
												<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Gender: </b></font></td>
														<td width=\"35%\"><font size=\"2\">" . getv('gender') ."</font></td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Ethnicity: </b></font></td>
														<td width=\"35%\">" . getv('ethnicity') ."</td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("NSLP_Eligible:", "NSLPEligible", getv('NSLPEligible')) . "</b></font></td>
														<td width=\"35%\">" . getv('NSLPEligible') . "</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Migrant:", "migrant", getv('migrant')) . "</b></font></td>
														<td width=\"35%\">" . getv('migrant') . "</td>
													</tr>
												</table>
												<br>
												<a name='profile'></a><font size=\"4\">$name - Learning Profile </font><br>
												$pulldown
                        <br>
												<br>
												<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Attendance Y1: </b></font></td>
														<td width=\"35%\">" . getv('attendance') ."</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Last Updated: </b></font></td>
														<td width=\"35%\">" . getv('lastUpdate') ."</td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>Suspensions Y1:</b></font></td>
														<td width=\"35%\">" . getv('suspensions') ."</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Activities_Eligible:", "eligibility", getv('eligibility')) . "</b></font></td>
														<td width=\"35%\">" . getv('eligibility') ."</td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("LEP:", "LEP", getv('LEP')) . "</b></font></td>
														<td width=\"35%\"><font size=\"2\">" . getv('LEP') ."</font></td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("LEP_Status:", "LEPStatus", getv('LEPStatus')) . "</b></font></td>
														<td width=\"35%\">" . getv('LEPStatus') ."</td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Indian_Education:", "nativeEd", getv('nativeEd')) . "</b></font></td>
														<td width=\"35%\">" . getv('nativeEd') ."</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Title_I:", "titleI", getv('titleI')) . "</b></font></td>
														<td width=\"35%\">" . getv('titleI') ."</td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Section_504:", "sec504", getv('sec504')) . "</b></font></td>
														<td width=\"35%\">" . getv('sec504') ."</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("SpEd_IEP:", "SpED_IEP", getv('SpED_IEP')) . "</b></font></td>
														<td width=\"35%\">" . getv('SpED_IEP') ."</td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Related_Services:", "relatedServices", getv('relatedServices')) . "</b></font></td>
														<td width=\"35%\">" . getv('relatedServices') ."</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>State &amp; District Testing: </b></font></td>
														<td width=\"35%\"><select name=\"selectName\" size=\"1\">
																<option value=\"one\">No Testing Accommodations</option>
																<option value=\"two\">Accommodations</option>
																<option value=\"three\">Modified HSGQE / EOLs</option>
																<option value=\"four\">Alternate Assessment</option>
																<option value=\"five\">No Statewide / District Testing</option>
															</select></td>
													</tr>
													<tr>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Behavior_Plan:", "behaviorPlan", getv('behaviorPlan')) . "</b></font></td>
														<td width=\"35%\">" . getv('behaviorPlan') ."</td>
														<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("G/T_Plan:", "GTPlan", getv('GTPlan')) . "</b></font></td>
														<td width=\"35%\">" . getv('GTPlan') ."</td>
													</tr>
												</table>
												<br>
												<a name='levels'></a><font size=\"4\">$name - Levels Information<br>
												</font>
                        $pulldown
                        <br>
												<br>
											</div>
											$scoresTable
										</div>
									</td>
								</tr>
								<tr>
					<td bgcolor=\"white\">
									</td>
				</tr>
								<tr>
					<td bgcolor=\"white\">
										<div align=\"center\">
											<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
												<tr>
													<td colspan=\"3\"><br>
														<a name=\"testing\"></a><font size=\"4\">$name - Testing Summary - </font><font size=\"2\"><a href=\"(EmptyReference!)\">Detailed Testing Data</a></font><font size=\"4\"> </font><br>
														$pulldown
                            <br>
														<br>
														<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
															<tr>
																<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("HSGQE_Reading:", "HSGQEReading", getv('HSGQEReading')) . " </b></font></td>
																<td width=\"35%\">" . getv('HSGQEReading') ."</td>
																<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("Latest_SRI:", "SRI", getv('SRI')) . "</b></font></td>
																<td width=\"35%\">" . getv('SRI') ."</td>
															</tr>
															<tr>
																<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("HSGQE_Writing:", "HSGQEWriting", getv('HSGQEWriting')) . "</b></font></td>
																<td width=\"35%\">" . getv('HSGQEWriting') ."</td>
																<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("STAR_Math:", "STAR", getv('STAR')) . "</b></font></td>
																<td width=\"35%\">" . getv('STAR') ."</td>
															</tr>
															<tr>
																<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("HSGQE_Math:", "HSGQEMath", getv('HSGQEMath')) . "</b></font></td>
																<td width=\"35%\"><font size=\"2\">" . getv('HSGQEMath') ."</font></td>
																<td nowrap bgcolor=\"#ccccff\" width=\"15%\"><font size=\"2\"><b>" . editv("SAT_ACT_ASVAB:", "scores", getv('scores')) . "</b></font></td>
																<td width=\"35%\">" . getv('scores') ."</td>
															</tr>
														</table>
														<br>
														<br>
													</td>
												</tr>
											</table>
										</div>
									</td>
				</tr>
							</table>";

include ("template.inc");

?>
