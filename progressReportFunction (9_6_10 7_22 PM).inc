<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

function createProgressReport($studentID, $unofficial="Y") {
  global $rootURL, $CurrentYear, $CurrentQuarter;

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
															<table width=\"940\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">
																<tr>
																	<td bgcolor=\"#ffffcc\" width=\"31\"><b><font color=\"#cc0000\">ADV:</font></b></td>
																	<td width=\"439\"><b>Advanced</b> - Student exceeds mastery expectations and is able to extend his or her knowledge to make new connections.</td>
																	<td bgcolor=\"#ffffcc\" width=\"31\"><b><font color=\"#cc0000\">PRO:</font></b></td>
																	<td width=\"439\"><b>Proficient</b> - Student has demonstrated mastery, and demonstrates real world application.</td>
																</tr>
																<tr>
																	<td bgcolor=\"#ffffcc\" width=\"31\"><b><font color=\"#cc0000\">DEV:</font></b></td>
																	<td width=\"439\"><b>Developing</b> - Student has demonstrated mastery and is beginning to show application of new knowledge.<b></b></td>
																	<td bgcolor=\"#ffffcc\" width=\"31\"><b><font color=\"#cc0000\">EMG:</font></b></td>
																	<td width=\"439\"><b>Emerging </b>- Student is attempting to make progress but has not met the expected outcomes for 'acceptable'.</td>
																</tr>
															</table>
														</div>
													</td>
												</tr>
											</table>";

											
$subjects = getStudentLevels($studentID);
$mywidth = 20;

$body .= "<table align=left border=1 cellspacing=1 cellpadding=1>";
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
         $des = $des = $standards[$std]['description'];
         $color = "";
         if ($value == "ADV" or $value == "PRO") { $color = " bgcolor=\"#ccffcc\""; }
         elseif ($value == NULL) { $value = "&nbsp;"; }
         $line1 .= "<th title=\"". $des ."\">&nbsp;&nbsp;" . $std . "&nbsp;&nbsp;</th>";
//         $name = "gr" . $type . "_" . $studentID . "_" . $sub . "_" . $lvl . "_" .$standards[$i]['std'];
         $line2 .= "<td nowrap width=\"32\"$color><font color=\"#cc0000\">$value</font></td>\n";
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
