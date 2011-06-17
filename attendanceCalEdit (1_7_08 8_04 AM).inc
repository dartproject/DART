<?php
// ==================================================================
//  Author: Steve Eley (sfeley@gmail.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
/*
ini_set('display_errors','1');
ini_set('display_startup_errors','1');
error_reporting(E_ALL);
*/
global $db;


//Get the parameters that we need
$year = $_GET['year'];
$student = $_GET['student'];
$editmonth = $_GET['editmonth'];
$editday = $_GET['editday'];
$pre_code[0] = $_GET['code0'];
$pre_code[1] = $_GET['code1'];
$pre_site[0] = $_GET['site0'];
$pre_site[1] = $_GET['site1'];

if($pre_code[0] == "" and $pre_code[1] == "" and $pre_site[0] == "" and $pre_site[1] == "") {
	$sqldate = date("Y-m-d", mktime(0, 0, 0, $editmonth, $editday, $year));
	$sql = "select PeriodID, Code, SiteID, AttendanceEvents.CodeID from AttendanceEvents, AttendanceCodes where StudentId = '$student' and Date = '$sqldate' and AttendanceEvents.CodeID = AttendanceCodes.CodeID";
	$data = $db->get_results($sql);
	foreach($data as $code) {
		$pre_code [$code->PeriodID-0] = $code->Code;
		$pre_site [$code->PeriodID-0] = $code->SiteID;
	}
}
// Get the student's name
$StudentName = $db->get_var("SELECT CONCAT_WS(' ',fname,lname) AS StudentName FROM student WHERE studentid = $student");

// Get our site list
$Sites = $db->get_results("SELECT siteid, name FROM site ORDER BY siteid");

// Get our attendance codes
$Codes = $db->get_results("SELECT CodeID, Code, CONCAT_WS(' - ',Code,Description) AS Description FROM AttendanceCodes ORDER BY CodeID");


// Build our two dropdowns for code selection
for ($x=0;$x<2;$x++) {
	$CodeSelect[$x] = "<SELECT NAME=\"editcode$x\" SIZE=\"1\">\n";
	if ($x == 0) {
		$CodeSelect[$x] .= "<OPTION VALUE=\"X\">&lt; Available Codes &gt;</OPTION>\n";
	}
	else {
		$CodeSelect[$x] .= "<OPTION VALUE=\"Y\">&lt; Same as AM &gt;</OPTION>\n";
	}
	foreach ($Codes as $code) {
		if ($code->Code == $pre_code[$x]) {
			$Selected = 'SELECTED';
		}
		else {
			$Selected = '';
		}
		$CodeSelect[$x] .= "<OPTION $Selected VALUE=\"$code->CodeID\">$code->Description</OPTION>\n";
	}
	$CodeSelect[$x] .= "</SELECT>\n";
}

// Build our two dropdowns for site selection
for ($x=0;$x<2;$x++) {
	$SiteSelect[$x] = "<SELECT NAME=\"editsite$x\" SIZE=\"1\">\n";
	if ($x == 0) {
		$SiteSelect[$x] .= "<OPTION VALUE=\"X\">&lt; Available Sites &gt;</OPTION>\n";
	}
	else {
		$SiteSelect[$x] .= "<OPTION VALUE=\"Y\">&lt; Same as AM &gt;</OPTION>\n";
	}
	foreach ($Sites as $site) {
		if ($site->siteid == $pre_site[$x]) {
			$Selected = 'SELECTED';
		}
		else {
			$Selected = '';
		}
		$SiteSelect[$x] .= "<OPTION $Selected VALUE=\"$site->siteid\">$site->name</OPTION>\n";
	}
	$SiteSelect[$x] .= "</SELECT>\n";
}

$title = 'DART - Attendance Record Adjustment';
// $body = 'Done!';


$body = <<<ENDBODY
<table border="0" cellpadding="0" cellspacing="2" width="100%">
	<tr>
		<td>
			<div align="left">

				<br>
				<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Attendance Adjusment </font><font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- $StudentName </font><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><br>
				</font></div>
			<blockquote>
				<div align="left">
					<div class="noteimportant">
						<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">This screen is used for adjusting a student's Attendance Record page. After entering your new code, the page will return to a refreshed and recalculated view of the Attendance Record you were working on.The chart below is written in plain English to to help you set the correct code.<br>

							<br>
						</font></div>
				</div>
			</blockquote>
		</td>
	</tr>
	<tr>
		<td>
			<div align="center">

				<table border="0" cellpadding="2" cellspacing="2" width="100%">
					<tbody>
						<tr>
							<td colspan="3" bgcolor="#ccffff">
								<div align="right">
									<font class="big" size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Change Attendance Code $editmonth/$editday/$year</b></font></div>
							</td>
						</tr>

						<tr>
							<td colspan="3">
								<table width="468" border="0" cellspacing="2" cellpadding="0">
									<tr>
										<td></td>
										<td>
											<div align="right">
												<table border="0" cellspacing="2" cellpadding="2">
													<tr>

														<td colspan="2" nowrap>
															<div align="center">
																<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2" color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Attendance Code Change</b></font></font></div>
														</td>
													</tr>
												</table>

											</div>
										</td>
									</tr>
								</table>
							</td>
						</tr>
						<tr>
						<td>
								<table border="1" cellspacing="2" cellpadding="2">
									<tbody>
										<tr>
											<td nowrap width="25">
												<div align="center">

													<b><font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">.</font></b></div>
											</td>
											<td nowrap>
												<div align="center">
													<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Code List</font></b></div>
											</td>
											<td nowrap>
												<div align="center">

													<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Present</font></b></div>
											</td>
											<td nowrap>
												<div align="center">
													<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Absent</font></b></div>
											</td>
										</tr>
										<tr>

											<td nowrap width="25">
												<div align="center">
													<b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">P</font></b></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Present </font></td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>A</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Absent</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>L</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Late</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Excused Tardy</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" color="black" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font color="white">..</font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Student Activity</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font color="white">.</font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>H</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Health Absence</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Excused Absence</font></td>
											<td nowrap>
												<div align="center">
													<font color="white">.</font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b><font size="1">X</font></b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>R</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Subsistence Leave</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>W</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Workstudy</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Suspended</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" color="white"face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font size="1"  face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">In-school Suspension</font></td>
											<td nowrap>
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font color="white">.</font></div>
											</td>
										</tr>
										<tr>
											<td nowrap bgcolor="red" width="25" height="18">

												<div align="center">
													<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V</b></font></div>
											</td>
											<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Vacation</font></td>
											<td nowrap>
												<div align="center">
													<font color="white">.</font></div>

											</td>
											<td nowrap>
												<div align="center">
													<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="1"><b>X</b></font></font></div>
											</td>
										</tr>
									</tbody>
								</table>
							</td>
							<td>&nbsp;</td>
							<td>
								<form action="index.php" method="GET">
									<input type="hidden" name="cmd" value="AttendanceCalendar">
									<input type="hidden" name="year" value="$year">
									<input type="hidden" name="student" value="$student">
									<input type="hidden" name="editmonth" value="$editmonth">
									<input type="hidden" name="editday" value="$editday">
									
								<table border="1" cellspacing="2" cellpadding="2">
									<tr>
										<th></th>
										<th>Attendance Code</th>
										<th>Site Attended</th>
									</tr>
									<tr>
										<td align="left"><b>AM Period</b></td>
										<td>$CodeSelect[0]</td>
										<td>$SiteSelect[0]</td>
									</tr>
									<tr>
										<td align="left"><b>PM Period</b></td>
										<td>$CodeSelect[1]</td>
										<td>$SiteSelect[1]</td>
									</tr>
									<tr>
										<td colspan="3" align="center"><input type="submit" value="Save Change"> <input type=button onClick="javascript:window.location='index.php?cmd=AttendanceCalendar&student=$student&year=$year';" value='Cancel'></td>
									</tr>
								</table>
							</td>
						</tr>
					</tbody>
				</table>
			</div>
		</td>
	</tr>
</table>
ENDBODY;

include('template.inc');
?>
