<?php

$cmd2 = $_POST['cmd2'];
if($cmd2 == "Group") {
		$val = $_POST['studentID'];
        $uval = array_unique($val); // gets rid of duplicate entries
        $lid = handleGroup($uval, $currentUserID, $action);
        header("Location:index.php?cmd=editlist&p1=$lid");
}

$site = $_GET['site'];
$curdate = $_GET['cdate'];
$type = $_GET['type'];
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
    var elts = document.forms['fieldsForm'].elements['studentID[]'];
    var elts_cnt = elts.length;
//    alert ('length' + elts_cnt);
//    if(elts_cnt == 0) { return false; }
    for (var i = 0; i < elts_cnt; i++) {
        if(elts[i].checked == true) { return true; }
    } 
    alert ('There are no students checked.');
    return false;
}
";

$checkall = "<div align=\"left\">
																			&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('selectionForm', true); return false;\" class=\"action\">Check All</a>&nbsp;/&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('selectionForm', false); return false;\" class=\"action\">UnCheck All</a>
																		<i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Group'>
<br><input type=submit name=cmd2 value='Export All'>
               </div>";
               
if ($type == 'year') {
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID 
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$year-08-01' AND '$nextyear-06-30' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
		 GROUP BY S.studentid, site, AG.GroupID";
		$view = "Year View: $year - $nextyear for Site: $site";
//print_r($yearinfo);
} else if ($type == 'month') {
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID  
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$startmonth-01' AND '$nextmonth-01' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
 		GROUP BY S.studentid, site, AG.GroupID";
		$view = "Month View: $month for Site: $site";
//print_r($info);
} else if ($type == 'day') {
	$currdatedisplay = PHPDate("m/d/Y", $curdate);
	//echo $curdate;
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID  and S.studentid = AE.studentid
		GROUP BY S.studentid, site, AG.GroupID";
		$view = "Day View: $currdatedisplay for Site: $site";
	//print_r($todayinfo);
} else  if ($type == 'absent') {
	$currdatedisplay = PHPDate("m/d/Y", $curdate);
	$studentlist = getStudentIn("SELECT S.studentid as id
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and AG.GroupID = 0
			and S.studentid = AE.studentid 
		GROUP BY S.studentid");
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist)
		GROUP BY S.studentid, site, AG.GroupID";
		$view = "Absent Day View: $currdatedisplay for Site: $site";

} else  if ($type == 'late') {
	$currdatedisplay = PHPDate("m/d/Y", $curdate);
	$studentlist = getStudentIn("SELECT S.studentid as id
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and AG.GroupID = 1
			and S.studentid = AE.studentid 
		GROUP BY S.studentid");
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist)
		GROUP BY S.studentid, site, AG.GroupID";
	$view = "Late Day View: $currdatedisplay for Site: $site";

}

	$info = $db->get_results ($sql, ARRAY_A);

foreach ($info as $student) {
	$id = $student['id'];
	$sitestu = $student['SiteID'];
	$group = $student['GroupID'];
	$key = $id."_".$sitestu;
	$name = $student['fname'] . " " . $student['lname'];
	$table[$key]['g_' . $group] = number_format($student['count'], 1);
	$table[$key]['name'] = $name;
	$table[$key]['id'] = $id;
	$table[$key]['site'] = $sitestu;
//	$body .= "$id<br>";
}

$body .= "$view<br>";
$body .= "<form name=\"selectionForm\" action=\"index.php?cmd=AttendanceDrillDown&type=$type&site=$site&year=$year&month=$month\" method=\"post\" >";
//$body .= "<input type=hidden name=sql value=\"$sql\">";
$body .= "<table border=1>";
$body .= "<tr><th></th><th>Name</th><th>Student ID</th><th>Site</th><th>Absent</th><th>Late</th><th>ISS</th><th>Suspended</th><th>Present</th></tr>";
$export = "Name\tStudent ID\tSite\tAbsent\tLate\tISS\tSuspended\tPresent\n";
foreach($table as $ind) {
	
	$body .= "<tr><td><input type=\"checkbox\" name=\"studentID[]\" value=\"" . $ind['id'] . "\" class=\"radio\"></td><td>" . $ind['name'] . "&nbsp;</td><td>" . $ind['id'] . "&nbsp;</td><td>"  . $ind['site'] . "&nbsp;</td><td>" .  $ind['g_0'] . "&nbsp;</td><td>" .  $ind['g_1'] . "&nbsp;</td><td>" .  $ind['g_2'] . "&nbsp;</td><td>" . $ind['g_3'] . "&nbsp;</td><td>" .  $ind['g_4'] . "&nbsp;</td></tr>";
	$export .= $ind['name'] . "\t" . $ind['id'] . "\t"  . $ind['site'] . "\t" .  $ind['g_0'] . "\t" .  $ind['g_1'] . "\t" .  $ind['g_2'] . "\t" . $ind['g_3'] . "\t" .  $ind['g_4'] . "\n";
}

$body .= "</table>$checkall</form>";

if($cmd2 == "Export All") {
	exportText($export);
}

include_once("template.inc");
?>