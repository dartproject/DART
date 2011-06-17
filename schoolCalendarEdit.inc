<?php
// ==================================================================
//  Author: Steve Eley (sfeley@gmail.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

//Get the few parameters that we need
$year = $_GET['year'];
$site = $_GET['site'];
$editschool = urldecode($_GET['editschool']);
$editmonth = $_GET['editmonth'];
$editday = $_GET['editday'];

${"editvalue_" . ($_GET['editvalue']== '-' ? 'dash' : $_GET['editvalue'])} = "selected";

$title = 'DART - School Calendar Adjustment';

$body = <<<ENDBODY
						<table border="0" cellpadding="0" cellspacing="2" width="100%">
							<tr>
								<td>
									<div align="left">

										<br>
										<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Calendar Adjustment </font><font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- $editschool </font><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><br>
										</font></div>
									<div align="right">
										
									</div>
									<blockquote>
										<div align="left">
											<div class="noteimportant">

												<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">This screen is used for adjusting a school's calendar. After entering your new code, the page will return to a refreshed and recalculated view of the calendar you were working on. <br>
													<br>
													There are four basic kinds of days we count in our calendars, and three of them are totaled in below each month, and in the upper left corner of the actual calendar view.  For questions about which days count for what, see the <a title="School Calendar FAQ" href="calendar_faq.html" target="_blank">Calendar FAQ</a> page. The chart below is written in plain English to to help you set the correct code. Student Days and Inservice days are counted toward &quot;ADM&quot;, or &quot;Membership, but not for &quot;ADA&quot;, or &quot;Attendance&quot; purposes.<br>

													<br>
												</font></div>
										</div>
									</blockquote>
								</td>
							</tr>
							<tr>
								<td>
									<div align="center">
<form action="index.php" method="GET">
	<input type="hidden" name="cmd" value="SchoolCalendar">
	<input type="hidden" name="year" value="$year">
	<input type="hidden" name="site" value="$site">
	<input type="hidden" name="editmonth" value="$editmonth">
	<input type="hidden" name="editday" value="$editday">
	
										<table border="0" cellpadding="2" cellspacing="2" width="100%">
											<tbody>
												<tr>
													<td colspan="3" bgcolor="#ccffff">
														<div align="right">
															<font class="big" size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Change Calendar Settings</b></font></div>
													</td>
												</tr>

												<tr>
													<td colspan="3">
														<table width="700" border="0" cellspacing="2" cellpadding="0">
															<tr>
																<td colspan="3"></td>
																<td>
																	<div align="right">
																		<table border="0" cellspacing="2" cellpadding="2">
																			<tr>

																				<td colspan="2" nowrap>
																					<div align="center">
																						<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2" color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Calendar Date Change</b> $editmonth/$editday/$year</font></font></div>
																				</td>
																			</tr>
																			<tr>
																				<td nowrap width="71"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Adjust Code</font></td>
																				<td nowrap>

																					<div align="center">
																						<select name="editcode" size="1">
																							<option value="" $editvalue_>&lt; Available Codes &gt;</option>
																							<option value="--" $editvalue_dash >-- Regular School Day</option>
																							<option value="C" $editvalue_C>C - School Closes</option>
																							<option value="E" $editvalue_E>E - End of Quarter</option>

																							<option value="H" $editvalue_H>H - Legal Holiday</option>
																							<option value="I" $editvalue_I>I - Inservice Day</option>
																							<option value="M" $editvalue_M>M - Meeting Minumum Day</option>
																							<option value="N" $editvalue_N>N - Not Meeting Minumum Day</option>
																							<option value="O" $editvalue_O>O - School Opens</option>
																							<option value="S" $editvalue_S>S - Saturday School</option>

																							<option value="T" $editvalue_T>T - Testing</option>
																							<option value="V" $editvalue_V>V - Vacation Day</option>
																							<option value="W" $editvalue_W>W - Teacher Workday</option>
																							<option value="X" $editvalue_X>X - No School Day</option>
																						</select></div>
																				</td>
																			</tr>
																		</table>

																	</div>
																</td>
															</tr>
														</table>
														<table border="1" cellspacing="2" cellpadding="1">
															<tbody>
																<tr>
																	<td align="center" nowrap width="25">
																		<div align="center">

																			<b><font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">.</font></b></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Code List</font></b></div>
																	</td>
																	<td nowrap>
																		<div align="center">

																			<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Student Day</font></b></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Contact Day</font></b></div>
																	</td>
																	<td nowrap>
																		<div align="center">

																			<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Teacher Day</font></b></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Contract Day</font></b></div>
																	</td>
																</tr>
																<tr>

																	<td align="center" nowrap width="25">
																		<div align="center">
																			<b>--</b></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Regular School Day</font></td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>
																<tr>
																	<td align="center" nowrap bgcolor="#ffb6c1" width="25">

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>C</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">School <b>C</b>loses</font></td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>
																<tr>
																	<td align="center" nowrap width="25">

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b>nd of Quarter</font></td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>
																<tr>
																	<td align="center" nowrap bgcolor="#7fff00" width="25">

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>H</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Legal <b>H</b>oliday</font></td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>
																<tr>
																	<td align="center" nowrap bgcolor="#00ff7f" width="25">

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b>nservice Day</font></td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>

																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>
																<tr>
																	<td align="center" nowrap width="25">

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>M</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><u><b>M</b>eeting</u> <a href="minimum_day_pop.html">Min. Day</a></font></td>
																	<td nowrap>
																		<div align="center">

																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">

																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>
																<tr>

																	<td align="center" nowrap bgcolor="#ff8c00" width="25">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>N</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><u><b>N</b>ot</u> Meeting <a href="minimum_day_pop.html">Min. Day</a></font></td>
																	<td nowrap>

																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>

																<tr>
																	<td align="center" nowrap bgcolor="#ffb6c1" width="25">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>O</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">School <b>O</b>pens</font></td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>

																<tr>
																	<td align="center" nowrap bgcolor="#d2b48c" width="25">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b>aturday School</font></td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>

																<tr>
																	<td align="center" nowrap bgcolor="#00bfff" width="25">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b>esting</font></td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>

																<tr>
																	<td align="center" nowrap bgcolor="#7fff00" width="25">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V</b>acation Day</font></td>
																	<td nowrap>

																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>.</b></font></div>
																	</td>
																</tr>

																<tr>
																	<td align="center" nowrap bgcolor="#ffd700" width="25" height="18">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>W</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Teacher <b>W</b>orkday</font></td>
																	<td nowrap>

																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																</tr>

																<tr>
																	<td align="center" nowrap bgcolor="white" width="25" height="18">
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>X</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">No School Day</font></td>
																	<td nowrap>

																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font color="white">.</font></div>
																	</td>
																	<td nowrap>

																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">&nbsp;</font></div>
																	</td>
																	<td nowrap>
																		<div align="center">
																			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">&nbsp;</font></div>
																	</td>
																</tr>															</tbody>
														</table>
														<div align="center">
															<p><input type="submit" value="Save Change"> <input type=button onClick="window.location='index.php?cmd=SchoolCalendar&year=$year&site=$site'" value=Cancel> </p>
															<p></p>
														</div>
													</td>
												</tr>
											</tbody>

										</table>
</form>
									</div>
								</td>
							</tr>
						</table>
					</td></tr>
	
	<tr><td colspan="2"></td><td><br><br><div align="center">
	<table border="0" cellpadding="0" cellspacing="2" width="100%">
		<tbody><tr>

			<td colspan="3">
				
			</td>
		</tr>
	</tbody></table>
</div>
</td></tr>
	</tbody></table>
ENDBODY;

include('template.inc');
?>