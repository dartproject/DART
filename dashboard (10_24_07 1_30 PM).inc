<?php

$site = $_GET['site'];
$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
$year = $_GET['year'];
$nextyear = $year+1;
$month = $_GET['month'];
$nextmonth = $month+1;
	switch($month) {
		case 8:
		case 9:
		case 10:
		case 11:
			$startmonth = $year . "-" . $month;
			$nextmonth = $year . "-" . $nextmonth;
			break;
		case 12:
			$startmonth = $year . "-" . $month;
			$nextmonth = $nextyear . "-01";
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			$startmonth = $nextyear . "-" . $month;
			$nextmonth = $nextyear . "-" . $nextmonth;
			break;
	}

$yearinfo = $db->get_results("SELECT count(AG.GroupID)/2 as count, GroupID FROM AttendanceEvents AE, AttendanceCodeGroups AG
		WHERE $siteselect AE.Date BETWEEN '$year-08-01' AND '$nextyear-06-30' AND AE.CodeID = AG.CodeID
		GROUP BY AG.GroupID", ARRAY_A);
//print_r($yearinfo);
foreach($yearinfo as $info) $yeargrp[$info['GroupID']] = $info['count'];
	
$monthinfo = $db->get_results ("SELECT count(AG.GroupID)/2 as count, GroupID FROM AttendanceEvents AE, AttendanceCodeGroups AG
		WHERE $siteselect AE.Date BETWEEN '$startmonth-01' AND '$nextmonth-01' AND AE.CodeID = AG.CodeID
		GROUP BY AG.GroupID", ARRAY_A);
//print_r($monthinfo);
foreach($monthinfo as $info) $monthgrp[$info['GroupID']] = $info['count'];

$curdate = date('Y-m-d');
$currdatedisplay = date("m/d/Y");
//echo $curdate;
$todayinfo = $db->get_results ("SELECT count(AG.GroupID)/2 as count, GroupID FROM AttendanceEvents AE, AttendanceCodeGroups AG
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID
		GROUP BY AG.GroupID", ARRAY_A);
//print_r($todayinfo);
foreach($todayinfo as $info) $todaygrp[$info['GroupID']] = $info['count'];

$aytd = number_format(($yeargrp[4]/($yeargrp[0] + $yeargrp[4])) * 100, 1);
$amonth = number_format(($monthgrp[4]/($monthgrp[0] + $monthgrp[4])) * 100, 1);
$aday = number_format(($todaygrp[4]/($todaygrp[0] + $todaygrp[4])) * 100, 1);
$absent = $todaygrp[0] == "" ? 0 : $todaygrp[0];
$late = $todaygrp[1] == "" ? 0 : $todaygrp[1];

$siteList = getSitesOptions($site);

${"site_" . $site} = 'selected';

$pulldown = "
<form name=ptime method=get action=\"index.php\">
<input type=hidden name=cmd value=Dashboard>
<input type=hidden name=year value=$year>
<input type=hidden name=month value=$month>
<select name=\"site\" onChange=\"submit()\">
    <option value='overall' $site_overall>overall</option>
	$siteList
</select>
</form>";

$body .= <<<END
<div align="center">
$pulldown
															
															<table width="90%" border="0" cellspacing="0" cellpadding="2">
																<tr>
																	<td nowrap></td>
																	<td nowrap>
																		<div align="center">
																			</div>
																	</td>

																	<td nowrap>
																		<div align="center">
																			<b><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2" color="#0000cc">$year-$nextyear Month: $month</font></font></b></div>
																	</td>
																	<td nowrap></td>
																	<td colspan="2" nowrap>
																		<div align="right">
																			<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="1"><b>Today is: </b>$currdatedisplay</font></font></div>

																	</td>
																</tr>
																<tr>
																	<td nowrap bgcolor="#ffffcc">
																		<div align="left">
																			<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2"><b>Attendance Data</b></font></font></div>
																	</td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>

																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"></td>
																	<td nowrap bgcolor="#ffffcc"></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">

																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Attendance - YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																		<a href=index.php?cmd=AttendanceDrillDown&type=year&site=$site&year=$year&month=$month>$aytd%</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Today's Rate:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																		<a href=index.php?cmd=AttendanceDrillDown&type=day&site=$site&year=$year&month=$month>$aday%</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Absent:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">$absent</a></font></td>
																</tr>

																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Monthly Rate:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																		<a href=index.php?cmd=AttendanceDrillDown&type=month&site=$site&year=$year&month=$month>$amonth%</a></font></td>
																	<td nowrap>
																		<div align="right">

																			</div>
																	</td>
																	<td nowrap></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Late:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">$late</a></font></td>

																</tr>
																<tr>
																	<td nowrap bgcolor="#ffffcc"><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2"><b>Discipline</b></font></font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">..</font></td>
																	<td nowrap bgcolor="#ffffcc">
																		<div align="right">
																			<font color="#ffffcc">.</font></div>

																	</td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"></td>
																	<td nowrap bgcolor="#ffffcc"></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">

																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Suspensions YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">27</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Suspensions - Month:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">4</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Suspended:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">1</a></font></td>
																</tr>

																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>ISS YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">57</a></font></td>
																	<td nowrap>
																		<div align="right">

																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>ISS- Month:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">18</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>ISS:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">4</a></font></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gym List YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">122</a></font></td>

																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gym List - Month </b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">53</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gym List:</b></font></div>

																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">17</a></font></td>
																</tr>
																<tr>
																	<td nowrap bgcolor="#ffffcc"><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2"><b>Student Tracking</b></font></font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>

																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"></td>
																	<td nowrap bgcolor="#ffffcc"></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New Students - YTD:</b></font></div>

																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">2</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New Students - Month:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">17</a></font></td>

																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New Students:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">1</a></font></td>
																</tr>
																<tr>
																	<td nowrap>

																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Drops / Transfers - YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">1</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Drops / Transfers - Month:</b></font></div>

																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">9</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Drops / Transfers:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">1</a></font></td>

																</tr>
																<tr>
																	<td nowrap bgcolor="#ffffcc"><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2"><b>Academics</b></font></font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"><font color="#ffffcc">.</font></td>
																	<td nowrap bgcolor="#ffffcc"></td>

																	<td nowrap bgcolor="#ffffcc"></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New Levels Today:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">7</a></font></td>

																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New Levels - Month:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">7</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New Levels:</b></font></div>

																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">11</a></font></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New PRO Today:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">16</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Newly PRO - Month:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">198</a></font></td>
																	<td nowrap>

																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Newly PRO:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">4</a></font></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">

																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>New ADV Today:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">7</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Newly ADV - Month:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">76</a></font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Newly ADV:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="(EmptyReference!)">1</a></font></td>
																</tr>

															</table>
															<br>
															<select onchange="javascript:window.location=value;">
																<option selected="selected" value="">Choose One</option>
																<option value="aa">Attendance by Age -Month</option>
																<option value="aa">Attendance by Age - 2007-08 SY</option>
																<option value="aa">Movement by Content Area - Month</option>

																<option value="aa">Movement by Content Area - 2007-08 SY</option>
																<option value="aa">Discipline by Age - Month</option>
																<option value="aa">Discipline by Age - 2007-08 SY</option>
															</select><br>
															<br>
															<div class="notewarning">
																All numbers link to a list of students for teachers and administrators to view. Students and parents will not see embedded links. The student and public views also suppress numbers below five (5) with &quot;&lt;5&quot; symbol. </div>
															<p></p>

														</div>
END;

include_once("template.inc");
?>