<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once("lib/functions_gs.inc");

function createProgressReport($studentID, $unofficial="Y") {
  global $rootURL, $CurrentYear, $CurrentQuarter, $db;

  $studentInfo = getStudentInfo($studentID);

  $sname = $studentInfo['fname'] . " " . $studentInfo['lname'];
//  $picture = $rootURL . "/images/student/" . $studentInfo['picture'];
  $picture = $studentInfo['picture'] != "" ? $studentInfo['picture'] : "no_photo.jpg";
  $picture = $rootURL . "/images/student/" . $picture;
  $img = $rootURL . "/images/SchoolLogos/" . $studentInfo['logo'] ;
  if($unofficial=="Y") { $bkgnd = "background = '" . $rootURL . "/images/unofficial.gif'"; }
  else { $bkgnd = "";}
  $sitename = $studentInfo['name'] ;
  $attendance = getAttendance($studentID);
  $absent = $attendance[0];
  $present = $attendance[4];
  $yeardisplay = $CurrentYear . "-" . substr($CurrentYear + 1, 2, 2) . ":Q$CurrentQuarter";
  $aid = $studentInfo['alaskaid'];

  $extID = $studentInfo['extID'];

$gradeexplain = <<<END
		<table width="100%" border="1" cellspacing="2" cellpadding="0">
			<tr>
				<td>
					<div align="center">
						<font size="2"><b><u>BSSD Standards Progress Descriptors</u></b></font></div>

				</td>
				<td nowrap>
					<div align="center">
						<font size="2"><b><u>BSSD Secondary Level Grading &amp; GPA Values</u></b></font></div>
				</td>
				<td>
					<div align="center">

						<font size="2"><b><u>BSSD Effort / Quality Peformance Indicators (QPI)</u></b></font></div>
				</td>
			</tr>
			<tr>
				<td>
					<div align="center">
						<img src="http://dart.bssd.org/images/bssd_standards_grades.gif" alt="" height="189" width="341" border="0"></div>
				</td>

				<td>
					<div align="center">
						<img src="http://dart.bssd.org/images/bssd_grading_scale.gif" alt="" height="178" width="249" align="middle" border="0">
					</div>
				</td>
				<td>
					<div align="center">
						<img src="http://dart.bssd.org/images/bssd_qpi_scale_sm.gif" alt="" height="188" width="398" align="middle" border="0"></div>
				</td>
			</tr>
		</table>
END;

$body ="		<div align=\"center\">
			<table width=\"1116\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">
				<tr>
					<td width=\"1116\">
						<div align=\"center\">
							<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\" $bkgnd>
								<tr>
									<td >
										<div align=\"center\">
											<table width=\"75%\" border=\"1\" cellspacing=\"2\" cellpadding=\"0\">
												<tr>
													<td width=\"25%\">
														<div align=\"center\">
															<img src=\"$img\" alt=\"\" border=\"0\"></div>
													</td>
													<td nowrap width=\"50%\">
														<div align=\"center\">
															<font size=\"4\" color=\"#cc0000\">$sitename School<br>$sname</font><font size=\"4\"><br>
																
																	
																	$yeardisplay<br>
															</font><b><font size=\"2\">Attendance: </font></b><font size=\"2\">Present $present <b>|</b> Absent $absent</font><b><font size=\"2\"><br>
																	
																		
																		AK Student ID: </font></b><font size=\"2\">$aid<br>
															</font><font size=\"4\"></font></div>
													</td>
													<td nowrap width=\"25%\">
														<div align=\"center\">
															<img src=\"$picture\" alt=\"Beam, James - SKK\" height=\"105\" width=\"95\" border=\"0\"></div>
													</td>
												</tr>
											</table>
										</div>
										<div align=\"center\">
											<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">
												<tr>
													<td>
														<div align=\"center\">
															$gradeexplain
														</div>
													</td>
												</tr>
											</table>
										</div>";

											
$subjects = getStudentLevels($studentID);
$mywidth = 20;


$sql = "SELECT gradetype FROM gs, student as st, gs_select
		WHERE st.site = gs_select.siteid and grade >= lowgrade and grade <= highgrade and
			st.studentid='$studentID' and gs.id = gs_select.gsid 
			";
$grdtype=$db->get_var($sql);

$body .= "<table align=left border=1 cellspacing=1 cellpadding=1 width=\"100%\">";
$body .= "<tr bgcolor=\"#ccccff\" align=left><th align=center>Level Title</th><th align=center>Level</th><th align=center>Progress on Standards</th></tr>";
foreach ($subjects as $rec) {

    $sub = $rec['subject']; //$_GET['p2'];       // subject number
    $name = $rec['sname'];
    $lvl = $rec['level']; //$_GET['p3'];      // level number
    $progress = $rec['progress']; //$_GET['p3'];      // level number
    
    $standards = getSubjectStandards ($sub, $lvl);
    $overall = getSubjectOverall ($sub, $lvl);
    $scores = getSutdentSubjectStandards($studentID, $sub, $lvl);
    $subInfo = getSubjectInfo ($sub);
    
    $subName =  $subInfo[0]['name'];
    $subTableName = $subInfo[0]['tablename'];
    $gradlvl = $subInfo[0]['gradLevel'];
    $ch_name = $studentChanges[$sub]['ch_name'];
    $ch_time = date($dateSettings, $studentChanges[$sub]['ch_time']);
    
    
    $body .= "<tr align=left><th>$name </th><th>$sub ($lvl)</th><td><table border=0 cellspacing=1 cellpadding=1>";
    $line1 = "";
    $line2 = "";

    
    for ($i = 0; $i < count($standards); $i++) {
         $std = $standards[$i]['std'];
         $value= getStdValue($std, $scores);
         $symbol = getSingleGradeSymbol($grdtype, $value);
//         print_r($scores);
         $des = $des = $standards[$std]['description'];
         $color = "";
         if ($value >  GRADETHRESHHOLD) { $color = " bgcolor=\"#ccffcc\""; }
         elseif ($value == NULL) { $value = "&nbsp;"; }
         $v = 
         $line1 .= "<th title=\"". $des ."\">&nbsp;&nbsp;" . $std . "&nbsp;&nbsp;</th>";
//         $name = "gr" . $type . "_" . $studentID . "_" . $sub . "_" . $lvl . "_" .$standards[$i]['std'];
         $line2 .= "<td nowrap align=center width=\"32\"$color><font color=\"#cc0000\">$symbol</font></td>\n";
         if(fmod($i+1, $mywidth) == 0) {
            $body .= "$line0 $line1 </tr><tr> $line2 </tr>";
            $line1 = "";
            $line2 = "";
         }      
    }
    if(fmod($i, $mywidth) <> 0) {
       $body .= "$line0 $line1 </tr><tr> $line2 </tr>";
    }

    $body .= "</table></td></tr>";
}
$body .= "</table>";

											
$body .= "
										</div>
									</td>
								</tr>
							</table>
						</div>
					</td>
				</tr>
			</table>
			<p></p>
		</div>";
return ($body);
}
?>
