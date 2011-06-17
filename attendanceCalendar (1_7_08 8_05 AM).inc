<?php
// ==================================================================
//  Author: Steve Eley (sfeley@gmail.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
/*
ini_set('display_errors','1');
ini_set('display_startup_errors','1');
error_reporting(E_WARNING);
*/

// PRIVILEGE - this variable determines who gets to edit the events
// (For Robert to set proper values)
$editable = PDisplay(A19) ? true : false;

global $db;
$year = $_GET['year'];
$student_id = $_GET['student'];


// Retrieve our student name and the list of sites we'll have to look up
$nextyear = $year + 1;

$sql = "SELECT DISTINCT CONCAT_WS(' ',St.fname,St.lname) AS StudentName, Si.name AS SiteName, Si.siteid 
        FROM student St LEFT OUTER JOIN AttendanceEvents AE ON (AE.StudentID = St.studentID)
                                 LEFT OUTER JOIN site Si ON (AE.SiteID = Si.siteid)
  		WHERE St.studentid = $student_id AND AE.Date BETWEEN '$year-08-01' AND '$nextyear-06-30'
		ORDER BY AE.Date DESC";
		
$sitelookup = $db->get_results($sql);
$StudentName = $sitelookup[0]->StudentName;
foreach ($sitelookup as $site) {
	$Sites[$site->siteid] = $site->SiteName;
}


$title = "$StudentName - Attendance $year-$nextyear";


// These parameters only exist if we're setting a new event code
$editmonth = $_GET['editmonth'];
$editday = $_GET['editday'];
$editcode[0] = $_GET['editcode0'];
$editcode[1] = $_GET['editcode1'];
$editsite[0] = $_GET['editsite0'];
$editsite[1] = $_GET['editsite1'];

if (is_null($editcode[1]) || ($editcode[1] == 'Y') || ($editcode[1] == '')) {
	$editcode[1] = $editcode[0];
}
if (is_null($editsite[1]) || ($editsite[1] == 'Y') || ($editsite[1] == '')) {
	$editsite[1] = $editsite[0];
}

// Perform the edit before we do the rest of the work
if ($editable && $editmonth && $editday) {
	if ($editmonth < 8) {
		$edityear = $year + 1;
	}
	else {
		$edityear = $year;
	}
	for ($x=0;$x<2;$x++) {
		if (!(is_null($editcode[$x]) || ($editcode[$x] == 'X') || ($editcode[$x] == '')) &&
		    !(is_null($editsite[$x]) || ($editsite[$x] == 'X') || ($editsite[$x] == ''))) {
			$sql = "DELETE FROM AttendanceEvents 
					WHERE StudentID = $student_id AND Date = '$edityear-$editmonth-$editday' AND PeriodID = $x";
			$db->query($sql);
			$sql = "INSERT INTO AttendanceEvents (StudentID, Date, PeriodID, SiteID, CodeID) 
					VALUES ($student_id, '$edityear-$editmonth-$editday', $x, '$editsite[$x]', $editcode[$x])";
			$db->query($sql);
		}
		
	}	
}


// Get our code groups
$sql = "SELECT ACG.CodeID, AG.Description
		FROM AttendanceCodeGroups ACG JOIN AttendanceGroups AG ON (ACG.GroupID = AG.GroupID)
		ORDER BY AG.Description";
$grouplookup = $db->get_results($sql);
foreach ($grouplookup as $group) { // break it into an easier lookup table
	$groups[$group->CodeID][] = $group->Description;
	for ($month=1;$month<=12;$month++) {
		$TotalGroups[$group->Description] = 0;
		$MonthGroups[$month][$group->Description] = 0;
	}
}

// ...Okay.  For our event codes, we're going to take a layered approach.  We're first going to retrieve 
// all the event codes for the student:
$sql = "SELECT YEAR(AE.Date) as Year, MONTH(AE.Date) as Month, DAYOFMONTH(AE.Date) as Day, AE.PeriodID,
               AE.SiteID, AE.CodeID, AC.Code, AC.Color
		FROM AttendanceEvents AE JOIN AttendanceCodes AC ON (AE.CodeID = AC.CodeID)
		WHERE AE.StudentID = $student_id AND AE.Date BETWEEN '$year-08-01' AND '$nextyear-06-30'
		ORDER BY YEAR(AE.Date), MONTH(AE.Date), DAYOFMONTH(AE.Date), AE.PeriodID";
$events = $db->get_results($sql);

if (is_null($events)) { 
	// No attendance records for this student, so we need to look in the student table to determine the site
	$sql = "SELECT site, name, CONCAT_WS(' ',fname,lname) AS StudentName FROM student, site WHERE studentid = $student_id and siteid = site";
	$studentinfo = $db->get_results($sql); 
	$StudentName = $studentinfo[0]->StudentName;
	$currentsite = $studentinfo[0]->site;
	$Sites[$currentsite] = $studentinfo[0]->name;
	}
else {
	$currentsite = $events[0]->SiteID;
}

// Get the first site and start figuring out our site date ranges
$CurrentSiteName = $Sites[$currentsite];
$MonthSites[8][] = $currentsite;
$SiteRanges[] = array('Site' => $currentsite, 'Start' => "$year-08-01");
$sitecounter = 0;

// Pre-sift our results into months and generate sums
foreach ($events as $event) {
	$thisyear=$event->Year;
	$thismonth=$event->Month;
	$thisday=$event->Day;
	$thisdate = "$thisyear-$thismonth-$thisday";
	if ($thisdate != $lastdate) {
		$MonthEvents[$event->Month][$event->Day] = $event->Code;
		$MonthColors[$event->Month][$event->Day] = $event->Color;
	}
	else {
		if ($MonthEvents[$event->Month][$event->Day] != $event->Code) { // Don't add twice
			$MonthEvents[$event->Month][$event->Day] .= $event->Code;
		}
		if (!$MonthColors[$event->Month][$event->Day]) {
			$MonthColors[$event->Month][$event->Day] = $event->Color;			
		}
	}
	if (array_key_exists($event->CodeID,$groups)) {
		foreach ($groups[$event->CodeID] as $group) {
			if (!(array_key_exists($event->Month,$MonthGroups)) and (array_key_exists($group,$MonthGroups[$event->Month]))) {
				$MonthGroups[$event->Month][$group] = 0.5;
			}
			else {
				$MonthGroups[$event->Month][$group] = $MonthGroups[$event->Month][$group] + 0.5;
			}
			if (!array_key_exists($group,$TotalGroups)) {
				$TotalGroups[$group] = 0.5;
			}
			else {
				$TotalGroups[$group] = $TotalGroups[$group] + 0.5;
			}
		}
	}
	// Figure out if the site has changed, and if so, update the SiteRanges array
	if ($event->SiteID != $currentsite) {
		$SiteRanges[$sitecounter++]['End'] = $lastdate;
		$currentsite = $event->SiteID;
		$MonthSites[$thismonth][] = $currentsite;
		$SiteRanges[$sitecounter] = array('Site' => $currentsite, 'Start' => $thisdate);
	}
	// Increment our date tracker
	$lastdate = $thisdate;
}
$SiteRanges[$sitecounter]['End'] = "$nextyear-06-30";  // Finish off our range array

// Next we need to pull site data and overlay events if (and only if) there was nothing
// in the attendance events
foreach ($SiteRanges as $site) {
	// Retrieve all our event codes for this school
	$sql = "SELECT MONTH(SE.Date) as Month, DAYOFMONTH(SE.Date) as Day, SE.CodeID, SEC.Code, SEC.Color 
			FROM SchoolCalendar SC JOIN SchoolEvents SE ON (SC.CalendarID = SE.CalendarID)
			     JOIN SchoolEventCodes SEC ON (SE.CodeID = SEC.CodeID)
			WHERE SC.SiteID = '$site[Site]' AND SC.SchoolYear = $year AND 
			      SE.Date BETWEEN '$site[Start]' AND '$site[End]'
			ORDER BY MONTH(SE.Date), DAYOFMONTH(SE.Date)";
	$events = $db->get_results($sql);

	// Pre-sift our results into months, updating only if the event or color value was empty
	foreach ($events as $event) {
		if (!$MonthEvents[$event->Month][$event->Day]) {
			$MonthEvents[$event->Month][$event->Day] = $event->Code;
		}
		if (!$MonthColors[$event->Month][$event->Day]) {
		 	$MonthColors[$event->Month][$event->Day] = $event->Color;
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
	global $student_id;
	global $editable;
	global $MonthEvents;
	global $MonthColors;
	global $MonthGroups;
	global $MonthSites;
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
	
	// Create the string of sites and their hyperlinks
	if (array_key_exists($month,$MonthSites)) {
		$SiteString = '(';
		$firstsite = true;
		foreach ($MonthSites[$month] as $site) {
			if ($firstsite) {
				$firstsite = false;
			}
			else {
				$SiteString .= ', ';
			}
			$SiteString .= "<a href=\"index.php?cmd=SchoolCalendar&year=$year&site=$site\">$site</a>";
		}
		$SiteString .= ')';
	}
	else {
		$SiteString = '';
	}
	

	// Now let's start to put our table together
	$cal = <<<ENDHEADER
	<td align="center" valign="top">
		<table width="100%" border="1" cellspacing="0">
				<tbody>
					<tr>
						<td colspan="7" align="center" valign="middle"><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$monthname $calyear<br/>$SiteString</font></b></td>
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
				$editlink = "index.php?cmd=AttendanceCalendarEdit&year=$year&student=$student_id&editmonth=$month";
				$editlink .= "&editday=$today";
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
					$LinkCode = "<a href=\"$editlink\">$ColorCode</a>";
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
											<td colspan="7"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$group: <b>$grouptotal</b></font></td>
										</tr>
ENDGROUP;

	}
	
	// And we're done!
	$cal .= "</tbody>\n</table>\n</td>\n";
	return $cal;
}

$firstsite = true;
// Generate our "Other Schools" string
foreach (array_keys($Sites) as $site) {
	if ($firstsite) {
		$firstsite = false;
	}
	else {
		$OtherSchools .= ', ';
	}
	$OtherSchools .= "$Sites[$site] (<a href=\"index.php?cmd=SchoolCalendar&year=$year&site=$site\">$site</a>)";
}

// Now print the first part of the calendar
$body = <<<ENDSTART
			<div align="left">
				<table class="note" align="center" border="1" cellpadding="3" cellspacing="1" width="760">
					<caption align="center"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><span class="head">Cumulative Attendance: $year-$nextyear SY</span><br>

						</font><span class="head"></span></caption>
					<tbody>
						<tr>
							<td colspan="2"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><strong>Student Name:</strong>&nbsp;&nbsp;<a href="index.php?cmd=toggleStudent&p1=$student_id">$StudentName</font></td>
							<td colspan="2"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><strong>Current School Calendar:</strong>&nbsp;&nbsp;<b><font color="#ff0033">$CurrentSiteName</font></b></font></td>
						</tr>
						<tr>

							<td colspan="4"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><strong>Other Schools $year-$nextyear SY:</strong>&nbsp;&nbsp;$OtherSchools</font></td>
						</tr>
						<tr>
							<td align="center" valign="top" width="25%">
								<table width="100%">
									<tbody>
										<tr>

											<td colspan="2" align="center" nowrap><b><font size="1" color="#ff0033" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$year-$nextyear SY Totals</font><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"> </font></b><b><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><br>
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
	$body .= "<td colspan=\"2\" valign=\"bottom\" nowrap><font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Days $group: $grouptotal</font></td>\n";
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
											<td align="center" valign="middle" width="25"></td>
											<td valign="middle">
												<div align="center">

													<b><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">BSSD Attendance Codes</font></b></div>
											</td>
										</tr>
										<tr>
											<td align="center" valign="middle" bgcolor="red" width="25"><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>A</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Absent (No reason given)</font></td>
										</tr>

										<tr>
											<td align="center" valign="middle" bgcolor="red"><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>L</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Late</font></td>
										</tr>
										<tr>
											<td align="center" valign="middle" bgcolor="red"><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">ISS</font></td>

										</tr>
										<tr>
											<td align="center" valign="middle" bgcolor="red"><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Suspended</font></td>
										</tr>
										<tr>
											<td align="center" valign="middle" bgcolor="red"><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>?</b></font></td>

											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><a href="" onClick="javascript:popUp2('index.php?cmd=AttendanceCalendarCode', 200, 350)">All Other Codes (List)</a></font></td>
										</tr>
										<tr>
											<td align="center" valign="middle"></td>
											<td valign="middle">
												<div align="center">
													<b><font size="1" color="#330099" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">EED Calendar Codes</font></b></div>
											</td>

										</tr>
										<tr>
											<td align="center" bgcolor="#ffb6c1" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>C</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">School <b>C</b>loses</font></td>
										</tr>
										<tr>
											<td align="center" valign="middle" bgcolor="#ffb6c1"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b></font></td>

											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>E</b>nd of Quarter</font></td>
										</tr>
										<tr>
											<td align="center" bgcolor="#7fff00" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>H</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Legal <b>H</b>oliday</font></td>
										</tr>

										<tr>
											<td align="center" bgcolor="#00ff7f" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>I</b>nservice Day</font></td>
										</tr>
										<tr>
											<td align="center" bgcolor="#ffb6c1" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>O</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">School <b>O</b>pens</font></td>

										</tr>
										<tr>
											<td align="center" bgcolor="#d2b48c" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>S</b>aturday School</font></td>
										</tr>
										<tr>
											<td align="center" bgcolor="#00bfff" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b></font></td>

											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>T</b>esting</font></td>
										</tr>
										<tr>
											<td align="center" bgcolor="#7fff00" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>V</b>acation Day</font></td>
										</tr>

										<tr>
											<td align="center" bgcolor="#ffd700" height="18" valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>W</b></font></td>
											<td valign="middle"><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Teacher <b>W</b>orkday</font></td>
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