<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

function createSReport($studentID, $qpistatus="off", $unofficial="Y") {
  global $rootURL, $CurrentYear, $CurrentQuarter;
  
  $studentInfo = getStudentInfo($studentID);

  $sname = $studentInfo['fname'] . " " . $studentInfo['lname'];
//  $picture = $rootURL . "/images/student/" . $studentInfo['picture'];
  $picture = $studentInfo['picture'] != "" ? $studentInfo['picture'] : "no_photo.jpg";
  $picture = $rootURL . "/images/student/" . $picture;
  if($unofficial=="Y") { $bkgnd = "background = '" . $rootURL . "/images/unofficial.gif'"; }
  else { $bkgnd = "";}
  $img = $rootURL . "/images/SchoolLogos/" . $studentInfo['logo'] ;
  $sitename = $studentInfo['name'];
  $attendance = getAttendance($studentID);
  $absent = $attendance[0];
  $present = $attendance[4];
  $alaskaid = $studentInfo['alaskaid'];
  $yeardisplay = $CurrentYear . "-" . substr($CurrentYear + 1, 2, 2) . ":Q$CurrentQuarter";

  $site = $studentInfo['siteid'];
  $sn = getRepNotes($site);
  $content = stripslashes($sn['comment']);
  $content = preg_replace(array('/</', '/>/', '/"/', '/\n/'), array('&lt;', '&gt;', '&quot;', '<br>'), $content);
 // echo $sn;
  if($sn['comment'] != "" and $sn != NULL) {
    $snotes = "<div class=\"noteclassic\" align=\"left\">" .
  							$content 
               . "</div>";
  }


  $studentScore = getStudentOverallScore($studentID);
  foreach ($studentScore as $rec) {
    $sub = $rec['subject']; 
    $lvl = $rec['level'];
    $score = $rec['score'];
    $comment = commentSpace($rec['comment']);
    $qpi = commentSpace($rec['qpi']);
    $name = $rec['sname'];

    $evaluation .= "<tr>
															<td nowrap width=\"15%\"><font size=\"2\"><b>$name</b></font></td>
															<td nowrap width=\"5%\">
																<div align=\"center\">
																	<font size=\"2\"><b>$sub $lvl</b></font></div>
															</td>
															<td nowrap width=\"5%\">
																<div align=\"center\">
																	<font size=\"2\" color=\"#cc0000\"><b>$score</b></font></div>
															</td>";
															
     if($qpistatus == "on") {
   	    $evaluation .= "
         											<td nowrap width=\"10%\">
																<div align=\"center\">
																	<font size=\"2\"><b>$qpi</b></font></div>
															</td>";
				}
     $evaluation .= "						  <td>
                                <div align=\"left\">$comment</div>
															</td>
														</tr>";
		}												

$body ="
		<div align=\"center\">
			<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" $bkgnd >
				<tbody>
					<tr>
						<td valign=\"top\" width=\"100%\">
							<div align=\"center\">
								<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
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
																<font size=\"4\" color=\"#cc0000\">$sitename<br>
																	$sname</font><font size=\"4\"><br>
																	$yeardisplay<br>
																</font><b><font size=\"2\">Attendance: </font></b><font size=\"2\">Present $present <b>|</b> Absent $absent</font><b><font size=\"2\"><br>
																		AK Student ID: </font></b><font size=\"2\"> $alaskaid <br>
																</font><font size=\"4\"></font></div>
														</td>
														<td nowrap width=\"25%\">
															<div align=\"center\">
																<img src=\"$picture\" alt=\"$sname - $sitename\" height=\"105\" width=\"95\" border=\"0\"></div>
														</td>
													</tr>
												</table>
											</div>

$snotes

											<font size=\"4\"></font><font size=\"4\"></font>
											<div align=\"center\">";
											
$body .= $qpistatus =='on' ? "<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">
													<tr>
														<td></td>
														<td>
															<div align=\"center\">
																<font size=\"2\"><b><u>Level Progress Descriptors</u></b></font><font size=\"2\"><b><u> </u></b></font></div>
														</td>
														<td></td>
														<td>
															<div align=\"center\">
																<font size=\"2\"><b><u>Quality Performance Indicators</u></b></font></div>
														</td>
													</tr>
													<tr>
														<td><b><font color=\"#cc0000\">ADV:</font></b></td>
														<td>Advanced - Student exceeds mastery expectations and is able to extend his or her knowledge to make new connections in this content area.</td>
														<td><b><font color=\"#cc0000\">Exemplary:</font></b></td>
														<td>Student is a self-directed learner and exceeds teacher expectations in all areas of work quality, progress toward mastery of standards and timeliness for class work.</td>
													</tr>
													<tr>
														<td><b><font color=\"#cc0000\">PRO:</font></b></td>
														<td><b></b>Proficient - Student has demonstrated mastery of all standards, all district assessments have been passed, student demonstrates real world application.</td>
														<td><b><font color=\"#cc0000\">Acceptable:</font></b></td>
														<td>Student performance met teacher expectations in the following areas: quality of work; progress toward mastery of standards; meeting 80% timelines for class work.</td>
													</tr>
													<tr>
														<td><b><font color=\"#cc0000\">DEV:</font></b></td>
														<td>Developing - Student has demonstrated mastery of some standards and is beginning to show application of new knowledge.</td>
														<td><b><font color=\"#cc0000\">Deficient:</font></b></td>
														<td>Student is attempting to make progress but has not met one or more of the expected outcomes for 'acceptable'.</td>
													</tr>
													<tr>
														<td><b><font color=\"#cc0000\">EMG:</font></b></td>
														<td>Emerging - Student is beginning to acquire the knowledge necessary to demonstrate the successful mastery of standards in this level.</td>
														<td nowrap><b><font color=\"#cc0000\">Disengaged:<br>
																	Not Instructed:</font></b></td>
														<td>Student is making little or no progress due to the lack of performance or participation.<br>
															This content was not taught during the last quarter.</td>
													</tr>
												</table>" :
                       "<table width=\"90%\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">
												<tr>
													<td bgcolor=\"#ffffcc\"><b><font color=\"#cc0000\">ADV:</font></b></td>
													<td><b>Advanced</b> - Student exceeds mastery expectations and is able to extend his or her knowledge to make new connections.</td>

													<td bgcolor=\"#ffffcc\"><b><font color=\"#cc0000\">PRO:</font></b></td>
													<td><b>Proficient</b> - Student has demonstrated mastery of all standards, all district assessments have been passed, student demonstrates real world application.</td>
												</tr>
												<tr>
													<td bgcolor=\"#ffffcc\"><b><font color=\"#cc0000\">DEV:</font></b></td>
													<td><b>Developing</b> - Student has demonstrated mastery of some standards and is beginning to show application of new knowledge.<b></b></td>

													<td bgcolor=\"#ffffcc\"><b><font color=\"#cc0000\">EMG:</font></b></td>
													<td><b>Emerging </b>- Student is attempting to make progress but has not met one or more of the expected outcomes for 'acceptable'.</td>
												</tr>
											</table>";
                        
$body .=							 "<table width=\"100%\" border=\"1\" >
													<tbody>
														<tr>
															<td nowrap bgcolor=\"#ccccff\" width=\"15%\">
																<div class=\"tablehead1\">
																	<div align=\"center\">
																		<font size=\"2\"><b>Level Title</b></font></div>
																</div>
															</td>
															<td nowrap bgcolor=\"#ccccff\" width=\"5%\">
																<div class=\"tablehead1\">
																	<div align=\"center\">
																		<font size=\"2\"><b>Level</b></font></div>
																</div>
															</td>
															<td nowrap bgcolor=\"#ccccff\" width=\"5%\">
																<div class=\"tablehead1\">
																	<div align=\"center\">
																		<font size=\"2\"><b>Overall</b></font></div>
																</div>
															</td>";
   if($qpistatus == "on") {
      $body .= "
															<td nowrap bgcolor=\"#ccccff\" width=\"10%\">
																<div class=\"tablehead1\">
																	<div align=\"center\">
																		<font size=\"2\"><b>QPI</b></font></div>
																</div>
										         	</td>";
        	}
				$body .= "
															<td bgcolor=\"#ccccff\">
																<div class=\"tablehead1\">
																	<div align=\"center\">
																		<font size=\"2\"><b>Comments</b></font></div>
																</div>
															</td>
														</tr>
														$evaluation
													</tbody>
												</table>
											</div>
										</td>
									</tr>
								</table>
							</div>
						</td>
					</tr>
					<tr>
						<td>
							<div align=\"center\">
							
						</div>
						</td>
					</tr>
				</tbody>
			</table>
		</div>";
		
		return ($body);
		}

?>
