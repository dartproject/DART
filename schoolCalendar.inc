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

// PRIVILEGE - this variable determines who gets to edit the events
// (For Robert to set proper values)

$editable = PDisplay(A19) ? true : false;

global $db;
$year = $_GET['year'];
$site = $_GET['site'];

${"selection_" . $year} = 'selected';

$siteList = getSitesOptions($site);

$pulldown_hold = "
<select name=site on>
	$siteList
</select>
";
$pulldown = "
<form name=ptime method=get action=\"index.php\">
<input type=hidden name=cmd value=SchoolCalendar>
<input type=hidden name=year value=$year>
<!--
<select name=year>
      <option value='2007' $selection_2007>2007-2008</option>
  </select>
-->
<select name=site onChange=\"submit()\">
	$siteList
</select>
<!-- <input type=submit name=submitButton value=Submit> -->
</form>";

// Get our high-level information -- calendar name, site, etc.
$sql = "SELECT SC.CalendarID, SC.Description, S.name, SC.ApprovedBy
		FROM SchoolCalendar SC JOIN site S ON (SC.SiteID = S.siteid)
		WHERE SC.SchoolYear = $year AND SC.SiteID = '$site'";
$result = $db->get_row($sql);
$cal_id =     $result->CalendarID;
$Desc =       $result->Description;
$School =     $result->name;
$ApprovedBy = $result->ApprovedBy;

$title = "$School - $Desc";


// These parameters only exist if we're setting a new event code
$editmonth = $_GET['editmonth'];
$editday = $_GET['editday'];
$editcode = $_GET['editcode'];

// Perform the edit before we do the rest of the work
if ($editable && $editmonth && $editday && $editcode) {
	if ($editmonth < 8) {
		$edityear = $year + 1;
	}
	else {
		$edityear = $year;
	}
	// Get the right id
	$editcodeid = $db->get_var("SELECT CodeID FROM SchoolEventCodes WHERE Code = '$editcode'");
	if (is_numeric($editcodeid)) {
//		$sql = "UPDATE SchoolEvents SET CodeID = $editcodeid WHERE CalendarID = $cal_id AND DATE = '$edityear-$editmonth-$editday'";
		$sql = "INSERT INTO SchoolEvents SET CodeID = '$editcodeid', CalendarID = '$cal_id',  DATE = '$edityear-$editmonth-$editday' ON DUPLICATE KEY UPDATE CodeID='$editcodeid'";
		$db->query($sql);
	}
}


// Get our code groups
$sql = "SELECT SECG.CodeID, SEG.Description
		FROM SchoolEventCodeGroups SECG JOIN SchoolEventGroups SEG ON (SECG.GroupID = SEG.GroupID)
		ORDER BY SEG.Description";
$grouplookup = $db->get_results($sql);
foreach ($grouplookup as $group) { // break it into an easier lookup table
	$groups[$group->CodeID][] = $group->Description;
}

// Retrieve all our event codes for this school
$sql = "SELECT MONTH(SE.Date) as Month, DAYOFMONTH(SE.Date) as Day, SE.CodeID, SEC.Code, SEC.Color 
		FROM SchoolEvents SE JOIN SchoolEventCodes SEC ON (SE.CodeID = SEC.CodeID)
		WHERE SE.CalendarID = '$cal_id'
		ORDER BY MONTH(SE.Date), DAYOFMONTH(SE.Date)";
$events = $db->get_results($sql);

// Pre-sift our results into months and generate sums
foreach ($events as $event) {
	$MonthEvents[$event->Month][$event->Day] = $event->Code;
	$MonthColors[$event->Month][$event->Day] = $event->Color;
	if (array_key_exists($event->CodeID,$groups)) {
		foreach ($groups[$event->CodeID] as $group) {
			if (!(array_key_exists($event->Month,$MonthGroups)) and (array_key_exists($group,$MonthGroups[$event->Month]))) {
				$MonthGroups[$event->Month][$group] = 1;
			}
			else {
				$MonthGroups[$event->Month][$group]++;
			}
			if (!array_key_exists($group,$TotalGroups)) {
				$TotalGroups[$group] = 1;
			}
			else {
				$TotalGroups[$group]++;
			}
		}
	}
}

/*
print("MonthGroups:");
print_r($MonthGroups);
print("\n\nTotalGroups:");
print_r($TotalGroups);
print("\n\nMonthEvents:");
print_r($MonthEvents);
print("\n\nMonthColors:");
print_r($MonthColors);
*/

// Print out the calendar mini-table
function MonthCalendar($month) {
	global $year;
	global $site;
	global $School;
	global $editable;
	global $MonthEvents;
	global $MonthColors;
	global $MonthGroups;
	if ($month >= 8) { // Is this the given year, or the following year?
		$calyear = $year;
	} 
	else {
		$calyear = $year + 1;
	}
	// What day of the week does the first day start on?
	$tmpdate = getdate(mktime(0,0,0,$month,1,$calyear));
	$startday = $tmpdate['wday'];
	$monthname = $tmpdate['month'];
	
	// And how many weeks do we have?
	switch($month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			$days = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			$days = 30;
			break;
		case 2:
			if ((($calyear % 4) == 0) && (($calyear % 100) != 0)) {
				$days = 29;
			}
			else {
				$days = 28;
			}	
	}
	$weeks = ceil(($days + $startday)/7);

	// Now let's start to put our table together
	$cal = <<<ENDHEADER
	<td align="center" valign="top">
		<table width="100%" border="1" cellspacing="0">
				<tbody>
					<tr>
						<td colspan="7" align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$monthname $calyear</font></b></td>

					</tr>
					<tr>
						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">S</font></b></td>
						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">M</font></b></td>
						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">T</font></b></td>
						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">W</font></b></td>
						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">T</font></b></td>

						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">F</font></b></td>
						<td align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">S</font></b></td>
					</tr>
ENDHEADER;
    $weekstart = 1 - $startday;
	for ($week=1;$week<=$weeks;$week++) {
		
		
		// First we do the day numbers
		$cal .= "<tr valign='top'>\n";
		for ($today=$weekstart;$today<$weekstart+7;$today++) {
			$Color = $MonthColors[$month][$today];
			if (!$Color) {
				$Color = "FFFFFF";
			}
			if (($today < 1) || ($today > $days)) { // First week, and Day 1 hasn't started yet
				$cal .= "<td align=\"center\" valign=\"middle\"><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></td>\n";
			}
			else {
				$cal .= "<td align=\"center\" valign=\"middle\" bgcolor=\"#$Color\"><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$today<br></font></td>\n";					
			}
		}
		$cal .= "</tr>\n";
		
		// Then the event codes
		$cal .= "<tr valign='top'>\n";
		for ($today=$weekstart;$today<$weekstart+7;$today++) {
			$Color = $MonthColors[$month][$today];
			if (!$Color) {
				$Color = "FFFFFF";
			}
			// If the user can edit, build the link to the edit screen
			if ($editable) {
				$editlink = "index.php?cmd=SchoolCalendarEdit&year=$year&site=$site&editmonth=$month";
				$editlink .= "&editday=$today&editschool=" . urlencode($School);
			}
			
			if (($today < 1) || ($today > $days)) { // First week, and Day 1 hasn't started yet
				$cal .= "<td align=\"center\" valign=\"middle\"><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">&nbsp;</font></td>\n";
			}
			else {
				$EventCode = $MonthEvents[$month][$today];
				if (!$EventCode) {
					$EventCode = '&nbsp;';
				}
				// Make the '--' and 'X' codes invisible
				if (($EventCode == '--') || ($EventCode == 'X')) {
					$ColorCode = "<font color='#$Color'>$EventCode</font>";
				}
				else {
					$ColorCode = $EventCode;
				}
				if ($editable) {
					$LinkCode = "<a href=\"$editlink&editvalue=$EventCode\">$ColorCode</a>";
				}
				else {
					$LinkCode = $ColorCode;
				}
				$cal .= "<td align=\"center\" valign=\"middle\" bgcolor=\"#$Color\"><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$LinkCode<br></font></td>\n";					
			}
		}
		$cal .= "</tr>\n";
		
		// And that's it for this week, so tick forward the day counter
		$weekstart = $weekstart + 7;
	}
	
	// Now print the group totals
	foreach (array_keys($MonthGroups[$month]) as $group) {
		$grouptotal = $MonthGroups[$month][$group];
		if (!$grouptotal) {
			$grouptotal = 0;
		}
		$cal .= <<<ENDGROUP
		<tr valign="top">
											<td colspan="7"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Number of $group Days: <b>$grouptotal</b></font></td>
										</tr>
ENDGROUP;

	}
	
	// And we're done!
	$cal .= "</tbody>\n</table>\n</td>\n";
	return $cal;
}

// Now print the first part of the calendar
$body = <<<ENDSTART
			<div align="left">$pulldown
				<table class="note" align="center" border="1" cellpadding="3" cellspacing="1" width="760">
					<caption align="center"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><span class="head">$Desc</span><br>

						</font><span class="head"></span></caption>
					<tbody>
						<tr>
							<td colspan="2"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><strong>District Name:</strong>&nbsp;&nbsp;Bering Strait School District	</font></td>
							<td colspan="2"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><strong>School:</strong>&nbsp;&nbsp;<b><font color="#ff0033">$School</font></b></font></td>
						</tr>
						<tr>

							<td colspan="4"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><strong>Approved By:</strong>&nbsp;&nbsp;$ApprovedBy<b>, </b>Superintendent</font></td>
						</tr>
						<tr>
							<td align="center" valign="top" width="25%">
								<table width="100%">
									<tbody>
										<tr>

											<td colspan="2" align="center" nowrap><b><font size="1" color="#ff0033" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$year SY Calendar</font><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"> </font></b><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><br>
													</font></b></td>
										</tr>
ENDSTART;

// Total groups
foreach (array_keys($TotalGroups) as $group) {
	$grouptotal = $TotalGroups[$group];
	if (!$grouptotal) {
		$grouptotal = 0;
	}
	$body .= "<tr valign=\"top\"\n";
	$body .= "<td colspan=\"2\" valign=\"bottom\" nowrap><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$group Days: $grouptotal</font></td>\n";
	$body .= "</tr>\n";
}

// Continue on with the key
$body .= <<<ENDLEGEND
									</tbody>
								</table>
								<br>

								<table width="100%" border="1" cellspacing="0" cellpadding="1">
									<tbody>
										<tr>
											<td align="center" valign="top" width="25">
												<div align="center">
													<b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">*</font></b></div>
											</td>
											<td valign="top"><b><font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"> Required</font></b></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#ffb6c1" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>C<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">School <b>C</b>loses</font></td>

										</tr>
										<tr>
											<td align="center" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b>nd of Quarter</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#7fff00" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>H</b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Legal <b>H</b>oliday</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#00ff7f" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b>nservice Day</font></td>

										</tr>
										<tr>
											<td align="center" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>M<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><u><b>M</b>eeting</u> <a href="../../eed_calendars/minimum_day.html">Min. Day</a></font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#ff8c00" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>N<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><u><b>N</b>ot</u> Meeting <a href="../../eed_calendars/minimum_day.html">Min. Day</a></font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#ffb6c1" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>O<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">School <b>O</b>pens</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#d2b48c" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b>aturday School</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#00bfff" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b>esting</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#7fff00" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V<font color="#ff0000">*</font></b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V</b>acation Day</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#ffd700" height="18" valign="top">
												<div align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>W</b></font></div>
											</td>
											<td valign="top"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Teacher <b>W</b>orkday</font></td>

										</tr>
									</tbody>
								</table>
							</td>
ENDLEGEND;

// Now the calendar cells!
$body .= MonthCalendar(8);
$body .= MonthCalendar(9);
$body .= MonthCalendar(10);
$body .= "</tr>\n<tr>\n";
$body .= MonthCalendar(11); // row 2
$body .= MonthCalendar(12);
$body .= MonthCalendar(1);
$body .= MonthCalendar(2);
$body .= "</tr>\n<tr>\n";
$body .= MonthCalendar(3); // row 3
$body .= MonthCalendar(4);
$body .= MonthCalendar(5);
$body .= MonthCalendar(6);
$body .= "</tr>\n</tbody>\n</table>\n</div>\n";

// And we're done...
include("template.inc");
?>
