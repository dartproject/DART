<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$listID = $_GET['listid'];
$time = time();
$year = defaultValue($_GET['year'], date("Y", $time));
$month = defaultValue($_GET['month'], date("n", $time));
$day = defaultValue($_GET['day'], date("j", $time));
$period = $_GET['period'];

$periodname = $period == 0 ? "am" : "pm";

$listName = getListName($listID);
$students = getStudentListCalendar($listID, "$year-$month-$day", $period);
$stdcount = count($students);
$toggleColor = 2;

${"day_" . $day} = "selected";
${"month_" . $month} = "selected";
${"period_" . $period} = "selected";

$codecount['P'] = 1;
$codecount['A'] = 2;
$codecount['L'] = 1;
$codecount['E'] = 1;
$codecount['T'] = 1;
$codecount['H'] = 2;
$codecount['X'] = 2;
$codecount['R'] = 2;
$codecount['W'] = 1;
$codecount['S'] = 1;
$codecount['I'] = 1;
$codecount['V'] = 2;

$head = "<SCRIPT LANGUAGE=\"JavaScript\" SRC=\"lib/CalendarPopup.js\"></SCRIPT>
	<SCRIPT LANGUAGE=\"JavaScript\">
var cal11 = new CalendarPopup();
cal11.setReturnFunction(\"setMultipleValues3\");
function setMultipleValues3(y,m,d) {
     document.forms[0].year.value=y;
     document.forms[0].month.selectedIndex=m;
     document.forms[0].day.selectedIndex=d;
//     alert('test');
     document.forms[0].submit();
     }	</SCRIPT>";

$getdate = <<<END
<!--
<FORM NAME="example">
(View Source of this page to see the example code)<br>

<INPUT TYPE="text" NAME="date1" VALUE="" SIZE=25>
<A HREF="#"
   onClick="cal.select(document.forms['example'].date1,'anchor1','MM/dd/yyyy'); return false;"
   NAME="anchor1" ID="anchor1">select</A>
</FORM>
-->
<form action=index.php method=get>
<input type=hidden name=cmd value=AttendanceList>
<input type=hidden name=listid value=$listID>
<input type=hidden name=period value=$period>

<!--
<select name="period" onChange='javascript:submit();'>
	<option>
	</option><option value="1" $period_1>am
	</option><option value="2" $period_2>pm
</option></select> Period
-->
<select name="month">
	<option>
	</option><option value="1" $month_1>January
	</option><option value="2" $month_2>February
	</option><option value="3" $month_3>March
	</option><option value="4" $month_4>April
	</option><option value="5" $month_5>May
	</option><option value="6" $month_6>June
	</option><option value="7" $month_7>July
	</option><option value="8" $month_8>August
	</option><option value="9" $month_9>September
	</option><option value="10" $month_10>October
	</option><option value="11" $month_11>November
	</option><option value="12" $month_12>December
</option></select>

<select name="day">
	<option>
	</option><option value="1" $day_1>1
	</option><option value="2" $day_2>2
	</option><option value="3" $day_3>3
	</option><option value="4" $day_4>4
	</option><option value="5" $day_5>5
	</option><option value="6" $day_6>6
	</option><option value="7" $day_7>7
	</option><option value="8" $day_8>8
	</option><option value="9" $day_9>9
	</option><option value="10" $day_10>10
	</option><option value="11" $day_11>11
	</option><option value="12" $day_12>12
	</option><option value="13" $day_13>13
	</option><option value="14" $day_14>14
	</option><option value="15" $day_15>15
	</option><option value="16" $day_16>16
	</option><option value="17" $day_17>17
	</option><option value="18" $day_18>18
	</option><option value="19" $day_19>19
	</option><option value="20" $day_20>20
	</option><option value="21" $day_21>21
	</option><option value="22" $day_22>22
	</option><option value="23" $day_23>23
	</option><option value="24" $day_24>24
	</option><option value="25" $day_25>25
	</option><option value="26" $day_26>26
	</option><option value="27" $day_27>27
	</option><option value="28" $day_28>28
	</option><option value="29" $day_29>29
	</option><option value="30" $day_30>30
	</option><option value="31" $day_31>31

</option></select>
<input name="year" value="$year" size="5" type="text">
<a href="#" onclick="cal11.showCalendar('anchor11'); return false;" title="cal11.showCalendar('anchor11'); return false;" name="anchor11" id="anchor11">Select Date</a><input type=submit>

</form>
END;
// Get our attendance codes
$Codes = $db->get_results("SELECT CodeID, Code, CONCAT_WS(' - ',Code,Description) AS Description FROM AttendanceCodes ORDER BY CodeID");



// Build our two dropdowns for code selection
$CodeSelect = "<SELECT NAME=\"selectCode\" SIZE=\"1\">\n
				<OPTION VALUE=\"X\">&lt; Available Codes &gt;</OPTION>\n";
foreach ($Codes as $code) {
	$CodeSelect .= "<OPTION VALUE=\"$code->CodeID\">$code->Description</OPTION>\n";
	}
$CodeSelect .= "</SELECT>\n";

"select * from student left join sfascores ON sfascores.studentid = student.studentid where ($exp)";		


function getStudentListCalendar($listID, $date, $period) {
	 global $debugLevel, $db;
	 
     $studentlist = getListStudents($listID);
     
	 $query = "select * from student 
	 			left join AttendanceEvents ON AttendanceEvents.studentid = student.studentid and AttendanceEvents.date = '$date' and AttendanceEvents.PeriodID = '$period'
				left join AttendanceCodes ON AttendanceEvents.CodeID = AttendanceCodes.CodeID
	 			where student.studentid in ($studentlist)
	 			order by lname";
//	 echo $query;
	 $list = $db->get_results($query, ARRAY_A);
	
	 return $list;
}
  $js = "function setCheckboxes(the_form, do_check)
{
    var elts      = (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
                  ? document.forms[the_form].elements['studentID[]']
                  : (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
          ? document.forms[the_form].elements['studentID[]']
          : document.forms[the_form].elements['studentID[]'];
    var elts_cnt  = (typeof(elts.length) != 'undefined')
                  ? elts.length
                  : 0;

    if (elts_cnt) {
        for (var i = 0; i < elts_cnt; i++) {
            elts[i].checked = do_check;
        } // end for
    } else {
        elts.checked        = do_check;
    } // end if... else

    return true;
} // end of the 'setCheckboxes()' function

function checkChecks () {
//    var elts      = (typeof(document.forms['fieldsForm'].elements['studentID[]']) != 'undefined')
//                  ? document.forms['fieldsForm'].elements['studentID[]']
//                  : document.forms['fieldsForm'].elements['studentID'])
//    var elts_cnt  = (typeof(elts.length) != 'undefined')
//                  ? elts.length
//                  : 0;
    var elts = document.forms['fieldsForm'].elements['studentID[]'];
    var elts_cnt = elts.length;
//    alert ('length' + elts_cnt);
//    if(elts_cnt == 0) { return false; }
    for (var i = 0; i < elts_cnt; i++) {
        if(elts[i].checked == true) { return true; }
    } 
    alert ('There are no students checked.' + elts_cnt);
    return false;
}

function nextSubmit() { document.nextForm.submit(); }

function prevSubmit() { document.prevForm.submit(); }
";

$body .= <<<END
<table border="0" cellpadding="0" cellspacing="2" width="100%">
							<tr>
								<td>
									<div align="left">

										<br>
										<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Group Attendance Entry  </font><font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- $listName</font></div>
									<blockquote>
										<div align="left">
											<div class="noteimportant">
												<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Attendance is taken in batches. Select the checkbox next to all of the names that will be marked in this batch, and then select the correct code at the bottom of the screen. This screen will refresh, and the next batch of codes can be entered. </font></div>
										</div>

									</blockquote>
								</td>
							</tr>
							<tr>
								<td>
									<div>
						
END;
$body .= "
<div align=\"right\" style=\"background-color:#ccffff;\">
  <b><font size=\"2\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">$getdate</font></b></div>

<div align=\"center\">
	Attendance Date: $month/$day/$year Period: $periodname
</div>	
<div align=\"center\">
  <font size=\"4\" color=\"#cc0000\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\">Keeping a List &amp; Checking it Twice...</font><font size=\"4\" color=\"#cc0000\"> </font></div>

							
";

$bodyform .= "
<form name=\"fieldsForm\" action=\"index.php?cmd=AttendanceListRecord\" method=\"post\" >
			<input type=hidden name=listid value=$listID>
			<input type=hidden name=month value=$month>
			<input type=hidden name=year value=$year>
			<input type=hidden name=day value=$day>		
			<input type=hidden name=period value=$period>
		<table>
";

$bodyform .= "<tr class=\"listhead\">
      				<td></td>
			<td align=\"center\" nowrap><a href=\"(EmptyReference!)\">&nbsp;Name&nbsp;</a></td>
			<td align=\"center\">
				<div align=\"center\">
					<a href=\"(EmptyReference!)\">Student Number</a></div>
			</td>
			<td align=\"center\">
				<div align=\"center\">
					<a href=\"(EmptyReference!)\">AK Student ID</a></div>
			</td>
			<td align=\"center\">
				<div align=\"center\">
					<a href=\"(EmptyReference!)\">School Site</a></div>
			</td>
			<td align=\"center\">
				<div align=\"center\">
					<a href=\"(EmptyReference!)\">Testing<br>Grade</a></div>
			</td>
			<td align=\"center\">
				<div align=\"center\">
					<a href=\"(EmptyReference!)\">Age</div>
			</td>
			<td align=\"center\">
				<div align=\"center\">
					<a href=\"(EmptyReference!)\">Code</div>
			</td>
			<td align=\"center\" nowrap>
				<div align=\"center\">
					&nbsp;Action&nbsp;</div>
			</td>
			<td align=\"center\" nowrap>
				<div align=\"center\">
					&nbsp;Edit&nbsp;</div>
			</td>
			$advHeader
		</tr>
";
$present = 0;
$absent=0;
$count=0;
 foreach ($students as $student) {   
      $id = $student['studentid'];
      $site = $student['site'];
      $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
      if ($codecount[$student['Code']] == 1) { $present++; } 
      elseif ($codecount[$student['Code']] == 2) { echo $student['Code'] . "-"; $absent++; } 
      $count++;
      $adv = Privilege(A6) == 'district' ?
            "<td><a href=\"index.php?cmd=advEdit&id=" . $student['studentid'] . "\">>>Edit</a></td>" :
            "";
//       $adv = "<td>t</td>";
      $bodyform .= "<tr bgcolor=$color>
					<td align=\"center\" nowrap>
						<input type=\"checkbox\" name=\"studentID[]\" value=\"$id $site\" class=\"radio\">
					</td>
					<td nowrap><a href=\"index.php?cmd=toggleStudent&p1=". $student['studentid'] . "\">". $student['fname'] . " " . $student['lname'] . "</a></td>
					<td>
						<div align=\"center\">
							" . $student['studentid'] . "</div>
					</td>
					<td>
						<div align=\"center\">
							" . $student['alaskaid'] . "</div>
					</td>
					<td>
						<div align=\"center\">
						" .	$student['site'] ."</div>
					</td>
					<td align=\"center\">
						<div align=\"center\">
							" .	$student['grade'] ."</div>
					</td>
					<td align=\"center\">
						<div align=\"center\">
							" .	age($student['bday']) ."</div>
					</td>
					<td align=\"center\">
						<div align=\"center\">
							" .	$student['Code'] ."</div>
					</td>
					<td align=\"center\" nowrap=\"nowrap\">
						<div align=\"center\"><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\" size=\"2\">
						<a href=\"index.php?cmd=toggleStudent&p1=$id\">Details</a> &gt;&gt; 
						<a href=\"index.php?cmd=AttendanceCalendar&student=$id&year=$CurrentYear\" >Attendance</a>
						</font></div>
					</td>
					<td nowrap=\"nowrap\"><font face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\" size=\"2\">
						&gt;&gt;<a href=\"index.php?cmd=advEdit&id=$id\">Edit</a></font>
					</td>
					</tr>";
}

$bodyform .="</table>";

$checkall = "<div align=\"left\">&nbsp;
				<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', true); return false;\" class=\"action\">Check All</a>&nbsp;/&nbsp;
				<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', false); return false;\" class=\"action\">UnCheck All</a>				 
            </div>";
$checkall = $stdcount == 0 ? "" : $checkall;

$rate = round(($present / $count)*100, 0);
$body .= "<font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Absent:</b> $absent :: <b>Present:</b> $present :: <b>Today's Rate:</b> $rate%</font><br>";

$body .= $bodyform;

$body .= "<table align=\"center\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">
				<tr>
					<td colspan=\"2\"><img src=\"http://dart.bssd.org/images/1pix.gif\" width=\"1\" height=\"5\" border=\"0\" alt=\"\"></td>
				</tr>
				<tr>
					<td valign=\"middle\" nowrap>
					$checkall
					</td>
					<td align=\"right\">$navigate</td>
				</tr>
			</table>
";

$body .= <<<END
<table border=0>
<tr>

	<td width=500>
		<div align="left"><div class="notewarning">
			<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Discipline-related attendance codes can only be adjusted through the Discipline Log screens. Click the code to view.</font></div></div>
	</td>
	<td width="145">
		<div align="center">
			<table border="0" cellspacing="2" cellpadding="2">
				<tr>

					<td nowrap>
						<div align="center">
							<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2" color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Attendance Code Entry</b></font></font></div>
					</td>
				</tr>
				<tr>
					<td>
						<div align="center">

<!--							<select name="selectCode" size="1">
								<option value="one">&lt; Available Codes &gt;</option>
								<option value="P">P - Present</option>
								<option value="L">L - Late</option>
								<option value="A">A - Absent</option>
								<option value="E">E - Excused Tardy</option>

								<option value="T">T - Student Activity</option>
								<option value="H">H - Health Absence</option>
								<option value="X">X - Excused Absence</option>
								<option value="R">R - Subsistence Leave</option>
								<option value="W">W - Workstudy</option>
								<option value="V">V - Vacation</option>

							</select> 
-->							$CodeSelect</div>
					</td>
				</tr>
			</table>
		</div>
	</td>
	<td width="145">
		<div align="center">
			<input name="cmd2" onclick="javascript: return checkChecks();" value="Make it So!" type="submit"><br>

		</div>
</tr>
</table>
END;

$body .= <<<END
			</div>
				</td>
			</tr>
		</table>
END;
include ("template.inc");

?>
