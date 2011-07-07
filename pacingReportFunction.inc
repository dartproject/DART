<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

function createPacingReport($studentID, $unofficial="Y") {
		global $CurrentYear, $CurrentQuarter;
/** area level scores **/

  $yeardisplay = $CurrentYear . "-" . substr($CurrentYear + 1, 2, 2) . ":Q$CurrentQuarter";
  $sublvl = getStudentLevels($studentID);
  foreach ( $sublvl as $lvl  ) {
     $sub = $lvl['subject'];
     $level = $lvl['numlevel'];
//     $til = $lvl['til'];
	 $til = "TIL: " . quarterBetweenDates ($lvl['start'], $lvl['final']); // . $lvl['start'] . "-" . $lvl['final'];
     $value = $lvl['progress'];
     $key = "$sub$level";
     $keytime = "$key" . "_time";
     $$key = "$value $til";
//     $$keytime = $til;
//     echo ("$key = $value === $keytime = $til<br>");
  }
  
  $studentInfo = getStudentInfo($studentID);
  $sname = $studentInfo['fname'] . " " . $studentInfo['lname'];
  if($unofficial=="Y") { $bkgnd = "background = '" . $rootURL . "/images/unofficial.gif'"; }
  else { $bkgnd = "";}

  $grade = $studentInfo['grade'];

  $bgk = $grade == "k" ? "black" : "ffffcc";
  $bg1 = $grade == "1" ? "black" : "ffffcc";
  $bg2 = $grade == "2" ? "black" : "ffffcc";
  $bg3 = $grade == "3" ? "black" : "ffffcc";
  $bg4 = $grade == "4" ? "black" : "ffffcc";
  $bg5 = $grade == "5" ? "black" : "ffffcc";
  $bg6 = $grade == "6" ? "black" : "ffffcc";
  $bg7 = $grade == "7" ? "black" : "ffffcc";
  $bg8 = $grade == "8" ? "black" : "ffffcc";
  $bg9 = $grade == "9" ? "black" : "ffffcc";
  $bg10 = $grade == "10" ? "black" : "ffffcc";
  $bg11 = $grade == "11" ? "black" : "ffffcc";
  $bg12 = $grade == "12" ? "black" : "ffffcc";
  
  $words = "g" . $grade;
  $$words = "Testing Level";  
  
//  echo ("grade: $grade words: $words");
  
$body = "		<link rel=\"stylesheet\" href=\"css/dart_pacing.css\" type=\"text/css\">
<div align=\"center\">
			<p><font size=\"4\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$sname</font>
         <font size=\"4\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
					
								$yeardisplay<br>
				</font></p>
				</div>
			<table border=10 cellpadding=0 cellspacing=0 width=1424 style=\"border-collapse:
 collapse;table-layout:fixed\" $bkgnd>
								<tr>
									<td class=xl73 rowspan=\"2\" bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\">
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Years in School</font></b></div>
									</td>
									</td>
									<td class=x166 bgcolor=$bgk width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$gk</b></font></div></td>
									<td class=x173 bgcolor=$bg1 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g1</b></font></div></td>
									<td class=x173 bgcolor=$bg2 width=110 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g2</b></font></div></td>
									<td class=x173 bgcolor=$bg3 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g3</b></font></div></td>
									<td class=x173 bgcolor=$bg4 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g4</b></font></div></td>
									<td class=x173 bgcolor=$bg5 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g5</b></font></div></td>
									<td class=x173 bgcolor=$bg6 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g6</b></font></div></td>
									<td class=x173 bgcolor=$bg7 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g7</b></font></div></td>
									<td class=x173 bgcolor=$bg8 width=101 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g8</b></font></div></td>
									<td class=x173 bgcolor=$bg9 width=102 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g9</b></font></div></td>
									<td class=x173 bgcolor=$bg10 width=101 style=\"border-bottom:1.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g10</b></font></div>
									</td>
									<td bgcolor=$bg11 class=x173 width=80 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g11</b></font></div></td>
									<td bgcolor=$bg12 class=x173 width=80 style=\"border-bottom:1.5pt solid black\"><div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g12</b></font></div></td>
								</tr>
								<tr height=18>
									<td class=xl73 valign=\"top\" bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<b><font size=\"3\">K</font></b></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<b><font size=\"3\">1</font></b></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=110 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<b><font size=\"3\">2</font></b></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>3</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>5</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>6</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>7</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=102 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>9</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>10</b></font></div>
									</td>
									<td class=xl73 bgcolor=\"#ffffcc\" width=101 style=\"border-bottom:1.5pt solid black\" height=\"18\">
										<div align=\"center\">
											<font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>11</b></font></div>
									</td>
									<td bgcolor=\"#ffffcc\" width=\"101\" height=18 class=xl64 style=\"border-bottom:1.5pt solid black\">
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">12</font></b></div>
									</td>
								</tr>
								<tr height=73>
									<td bgcolor=\"#ccffff\" height=73 class=xl62 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Career Skills</font></b></div>
									</td>
									<td colspan=2 class=xl79 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Exploring Work</b><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS1 </font></b><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												</font></b></div>
									</td>
									<td class=xl29 width=110>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Work Responsibilities<br>
													<br>
												</b></font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS2</font></b></div>
									</td>
									<td class=xl30 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Connecting Learning &amp; Work<br>
													<br>
												</b></font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS3</font></b><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b><br>
													<br>
												</b></font></div>
									</td>
									<td colspan=2 class=xl30 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Career Exploration<br>
													<br>
												</b></font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS4</font></b></div>
									</td>
									<td colspan=2 class=xl30 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Job Skills<br>
													<br>
												</b></font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS5</font></b></div>
									</td>
									<td colspan=2 class=xl30 width=203 style=\"border-right:.5pt solid black\" background=\"../../active_cell.gif\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Business Simulation<br>
													<br>
												</b></font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS6</font></b></div>
									</td>
									<td colspan=2 class=xl71 style=\"border-right:.5pt solid black\" valign=\"middle\" bgcolor=\"silver\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Career Planning<br>
													<br>
												</b></font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS7</font></b></div>
									</td>
									<td class=xl31 valign=\"middle\" width=\"101\">
										<div align=\"center\">
											<font size=\"2\">Internship<br>
												<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CS 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CS7</font></b></div>
									</td>
								</tr>
								<tr height=\"27\">
									<td bgcolor=\"#669999\" class=xl34 width=101 height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Time in Level</b></font></div>
									</td>
									<td class=xl34 style=\"border-right:.5pt solid black\" colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters</b></font></div>
									</td>
									<td class=xl34 width=110 height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 style=\"border-right:.5pt solid black\" colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 style=\"border-right:.5pt solid black\" colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters</b></font></div>
									</td>
									<td class=xl34 style=\"border-right:.5pt solid black\" colspan=\"2\" width=\"203\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters</b></font></div>
									</td>
									<td class=xl34 style=\"border-right:.5pt solid black\" colspan=\"2\" valign=\"middle\" bgcolor=\"silver\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">8 Quarters</font></div>
									</td>
									<td class=xl34 width=101 height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Cultural Awareness</font></b></div>
									</td>
									<td colspan=3 class=xl77 valign=\"middle\" width=312 style=\"border-right:.5pt solid black\" height=\"74\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Awareness &amp; Expression 1<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA1 </font></b><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												</font></b></div>
									</td>
									<td colspan=2 class=xl68 valign=\"middle\" width=202 style=\"border-right:.5pt solid black\" height=\"74\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Awareness &amp; Expression 2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA2 </font></b><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												</font></b></div>
									</td>
									<td class=xl35 valign=\"middle\" width=101 height=\"74\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Awareness &amp; Expression 3<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA3 </font></b></div>
									</td>
									<td class=xl35 valign=\"middle\" width=101 height=\"74\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Fine Arts &amp; Culture<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA4 </font></b></div>
									</td>
									<td class=xl35 valign=\"middle\" width=101 height=\"74\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Culture, Art &amp; Performance<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA5 </font></b></div>
									</td>
									<td class=xl35 valign=\"middle\" width=101 height=\"74\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Art in Culture<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA6 </font></b><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												</font></b></div>
									</td>
									<td class=xl48 valign=\"middle\" width=102 height=\"74\">
										<div align=\"center\">
											<font size=\"2\">Cultural Literacy<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA7 </font></b><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												</font></b></div>
									</td>
									<td class=xl35 valign=\"middle\" width=101 height=\"74\">
										<div align=\"center\">
											<font size=\"2\">Fine Arts &amp; Culture<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA8</font></b></div>
									</td>
									<td class=xl35 valign=\"middle\" width=101 height=\"74\">
										<div align=\"center\">
											<font size=\"2\">Exploration &amp; Understanding<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 9 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA9</font></b></div>
									</td>
									<td class=xl36 valign=\"middle\" width=\"101\" height=\"74\">
										<div align=\"center\">
											<font size=\"2\">Adv. Exploration &amp; Understanding<br>
												
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">CA 10 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$CA10</font></b></div>
									</td>
								</tr>
								<tr height=\"27\">
									<td bgcolor=\"#669999\" class=xl34 width=101 height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Time in Level</b></font></div>
									</td>
									<td class=xl34 colspan=\"3\" valign=\"middle\" style=\"border-right:.5pt solid black\" width=\"312\" height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">12 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 colspan=\"2\" valign=\"middle\" style=\"border-right:.5pt solid black\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">8 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 valign=\"middle\" width=101 height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 valign=\"middle\" width=\"101\" height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">4 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Math</font></b></div>
									</td>
									<td class=xl40 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Kinder Corner<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 0 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA0 </font></b><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Mathematics 1<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA1</font></b></div>
									</td>
									<td class=xl35 width=110>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Mathematics 2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA2</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Mathematics 3<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA3</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Mathematics 4<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA4</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Mathematics 5<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA5</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Integrated Math I<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA6</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Integrated Math II<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA7</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Pre Algebra<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA8</font></b></div>
									</td>
									<td class=xl48 width=102>
										<div align=\"center\">
											<font size=\"2\">Algebra<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 9 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA9</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\">Geometry<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 10 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA10</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\">Algebra II<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 11 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA11</font></b></div>
									</td>
									<td class=xl36 width=101>
										<div align=\"center\">
											<font size=\"2\">Pre Calculus<br>
                        <br>
                      </font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">MA 11 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$MA11</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=28>
									<td bgcolor=\"#669999\" class=xl34 width=\"101\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>&nbsp;Time in Level&nbsp;</b></font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=110 height=\"28\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=102 height=\"28\">
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101 height=\"28\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=\"101\" height=\"28\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Life Skills</font></b></div>
									</td>
									<td colspan=2 class=xl77 width=202>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Choices<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS1</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=211 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Working with Others<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS2</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Healthy Living<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS3</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Social Issues<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS4</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Basic Life Skills<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS5</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=203 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Advanced Life Skills<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS6</font></b></div>
									</td>
									<td colspan=2 class=xl69 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\">Healthy Living Skills<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS7</font></b></div>
									</td>
									<td class=xl41 width=\"101\">
										<div align=\"center\">
											<font size=\"2\">Leadership Development<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">LS 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LS8</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=7>
									<td bgcolor=\"#669999\" height=7 class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>&nbsp;Time in Level&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"211\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"203\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=\"101\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Reading</font></b></div>
									</td>
									<td class=xl42 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Kinder Roots<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE1<br>
												</font></b><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE2</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Roots<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE3</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=211 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"> Wings 2.1-3.2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE4</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Wings 4.1-5.2 <br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE5</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Wings 6.1-6.2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE6</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Reading Edge<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE7</font></b></div>
									</td>
									<td colspan=2 class=xl69 width=203 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\">Extended Skills Reading<br>
											</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE8</font></b></div>
									</td>
									<td colspan=2 class=xl35 style=\"border-right:1.5pt solid black\" width=\"202\">
										<div align=\"center\">
											<font size=\"2\">College Prep Reading</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font></b><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">RE 9 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$RE9</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=7>
									<td bgcolor=\"#669999\" height=7 class=xl34 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Time in Level&nbsp;</font></b></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"211\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"203\" height=\"27\">
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font>&nbsp;</div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Science</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"> </font></b></div>
									</td>
									<td colspan=3 class=xl77 width=312 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Science 1<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC1</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Science 2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC2</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Science 3<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC3</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Integrated Science<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC4</font></b></div>
									</td>
									<td class=xl35 width=102>
										<div align=\"center\">
											<font size=\"2\">Earth Science </font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC5</font></b><font size=\"2\"> </font></div>
									</td>
									<td class=xl48 width=101>
										<div align=\"center\">
											<font size=\"2\">Life Science<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC6</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\">Earth, Life or Physical<br>
												<br>
												  </font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC7</font></b></div>
									</td>
									<td class=xl36 width=\"101\">
										<div align=\"center\">
											<font size=\"2\">Advanced Studies<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SC 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SC8</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=7>
									<td bgcolor=\"#669999\" height=7 class=xl34 width=101>
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;Time in Level&nbsp;</font></b></div>
									</td>
									<td class=xl34 colspan=\"3\" width=\"312\" height=\"27\">
										<div align=\"center\">
											<b><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">12 Quarters</font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 width=102>
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=\"101\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Social Studies</font></b></div>
									</td>
									<td colspan=2 class=xl77 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Social Studies 1<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS1</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=211 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Social Studies 2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS2</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Content Survey I<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS3</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Content Survey II<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS4</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Content Survey III<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS5</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Alaska History <br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS6</font></b></div>
									</td>
									<td class=xl35 width=102>
										<div align=\"center\">
											<font size=\"2\">Global  History<br>
											</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS7</font></b></div>
									</td>
									<td class=xl48 width=101>
										<div align=\"center\">
											<font size=\"2\">US History<br>
											</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS8</font></b></div>
									</td>
									<td class=xl35 width=101>
										<div align=\"center\">
											<font size=\"2\">Social Studies 9</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 9 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS9</font></b></div>
									</td>
									<td class=xl36 width=101>
										<div align=\"center\">
											<font size=\"2\">Social Studies 10<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">SS 10 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$SS10</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=7>
									<td bgcolor=\"#669999\" height=7 class=xl34 width=101>
										<div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Time in Level</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"211\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=102>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=\"101\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font>&nbsp;</div>
									</td>
								</tr>
								<tr class=xl24 height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Technology</font></b></div>
									</td>
									<td colspan=2 class=xl77 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Technology 1<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE1</font></b></div>
									</td>
									<td class=xl35 width=110>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Technology 2<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE2</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Technology 3<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE3</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Technology 4<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE4</font></b></div>
									</td>
									<td colspan=2 class=xl68 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Technology Tools<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE5</font></b></div>
									</td>
									<td colspan=2 class=xl69 width=203 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\">Applied Technology</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE6</font></b></div>
									</td>
									<td colspan=2 class=xl68 style=\"border-right:1.5pt solid black\" width=\"202\">
										<div align=\"center\">
											<font size=\"2\">Advanced Technology Application</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">TE 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$TE7</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=7>
									<td bgcolor=\"#669999\" height=7 class=xl34 width=101>
										<div align=\"center\">
											<b><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;Time in Level</font><font color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;&nbsp;</font></div>
									</td>
									<td class=xl34 width=110>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"203\" height=\"27\">
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font>&nbsp;</div>
									</td>
								</tr>
								<tr height=74>
									<td bgcolor=\"#ccffff\" height=74 class=xl63 width=101>
										<div align=\"center\">
											<b><font size=\"3\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Writing</font></b></div>
									</td>
									<td class=xl44 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Oral Language<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 0 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR0</font></b></div>
									</td>
									<td class=xl45 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Beginning Writer<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 1 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR1</font></b></div>
									</td>
									<td class=xl45 width=110>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Developing Writer<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 2 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR2</font></b></div>
									</td>
									<td class=xl45 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Experienced Writer<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 3 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR3</font></b></div>
									</td>
									<td colspan=2 class=xl82 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Writing 4<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 4 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR4</font></b></div>
									</td>
									<td class=xl45 width=101>
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Writing 5<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 5 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR5</font></b></div>
									</td>
									<td colspan=2 class=xl82 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Basic Writing<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 6 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR6</font></b></div>
									</td>
									<td class=xl45 width=102>
										<div align=\"center\">
											<font size=\"2\">Writing Workshop </font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 7 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR7</font></b></div>
									</td>
									<td colspan=2 class=xl83 width=202 style=\"border-right:.5pt solid black\">
										<div align=\"center\">
											<font size=\"2\">Writing Workshop II</font><font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 8 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR8</font></b></div>
									</td>
									<td class=xl46 width=\"101\">
										<div align=\"center\">
											<font size=\"2\">College Prep Writing<br>
												<br>
											</font><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">WR 9 - </font><b><font size=\"1\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$WR9</font></b></div>
									</td>
								</tr>
								<tr class=xl25 height=7>
									<td bgcolor=\"#669999\" height=7 class=xl34 width=101>
										<div align=\"center\">
											<b><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;Time in Level</font><font color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></b></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=110>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font><font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=101>
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></div>
									</td>
									<td class=xl34 width=102>
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
									<td class=xl34 colspan=\"2\" width=\"202\" height=\"27\">
										<div align=\"center\">
											<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>8 Quarters&nbsp;</b></font>&nbsp;</div>
									</td>
									<td class=xl34 width=\"101\">
										<div align=\"center\">
											&nbsp;<font size=\"1\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>4 Quarters</b></font></div>
									</td>
								</tr>
								<tr height=16>
									<td class=xl82 bgcolor=\"#ffffcc\" width=101>
										<div align=\"center\"></div>
									</td>
                  <td height=16 class=xl82 bgcolor=$bgk width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$gk</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg1 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g1</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg2 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g2</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg3 width=110>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g3</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg4 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g4</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg5 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g5</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg6 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g6</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg7 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g7</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg8 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g8</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg9 width=102>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g9</b></font></div>
									</td>
									<td class=x182 bgcolor=$bg10 width=101>
										<div align=\"center\">
											<font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g10</b></font></div>
									</td>
									<td class=x182 bgcolor=$bg11 width=101>
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g11</b></font></div>
									</td>
									<td class=xl82 bgcolor=$bg12 width=\"101\">
										<div align=\"center\"><font size=\"2\" color=\"white\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>$g12</b></font></div>
									</td>
								</tr>
								<tr height=43>
									<td height=43 class=xl53 width=101>
										<div align=\"center\"></div>
									</td>
									<td colspan=13 class=xl54 width=\"1323\" height=\"43\">
										<div align=\"left\">
											<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">*The Pacing Guide is meant to provide an <b><i>approximate correlation</i></b> between student developmental abilities, estimated time to complete levels, and the number of years students have been enrolled in school.<br>
												** Shaded boxes indicate minimum competency levels in all content <span style=\"display:none\">areas.</span><br>
											</font></div>
									</td>
								</tr>
							</table>";
		return ($body);
}		
?>
