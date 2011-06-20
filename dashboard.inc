<?php
$B4Priv = PrivilegeB(B4);
$B3Priv = PrivilegeB(B3);

if($B3Priv == 'site') {
	$site = $currentMySite;
	$selectOptions = "<b>$site<b>";
} else if ($B3Priv == 'district') {
	$site = $_GET['site'] == "" ? ($currentMySite == 'Admin' ? 'overall' : $currentMySite) : $_GET['site'];
	$siteList = getSitesOptions($site);

	${"site_" . $site} = 'selected';
$selectOptions = <<<END
		<select name="site" onChange="submit()">
			<option value='overall' $site_overall>overall</option>
			$siteList
		</select>
END;

} else {
		
}
$drill = true;
// echo $site;
$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
$year = $_GET['year'] == "" ? $CurrentYear : $_GET['year'];
$nextyear = $year+1;
$quarter = $_GET['quarter'] == "" ? $CurrentQuarter : $_GET['quarter'];

$dates = 
$yearOptions = "<select name=\"year\" id=\"year\" onChange=\"submit()\">" . 
                       getYearOption ($year) . 
                       "</select>";
$quarterList = array(
		array("id"  => "1", "name" => "Q1"),
		array("id"  => "2", "name" => "Q2"),
		array("id"  => "3", "name" => "Q3"),
		array("id"  => "4", "name" => "Q4")
		 );
$quarterOptions = "<select name=\"quarter\" id=\"quarter\" onChange=\"submit()\">" . 
                       GetOptionList($quarterList, $quarter) . 
                       "</select>";

$sql = "select * from quarters where year = '$year' order by quarter ";
$dates = $db->get_results($sql, ARRAY_A);
$startQ = $dates[$quarter-1]['start'];
$endQ = $dates[$quarter-1]['finish'];
$startY = $dates[0]['start'];
$endY = $dates[3]['finish'];

//echo "Year ($year): $startY - $endY Quarter ($quarter): $startQ - $endQ";
/* ********************** Computation for Attendance ******************************* */
$yearinfo = $db->get_results("SELECT count(AG.GroupID)/2 as count, GroupID FROM AttendanceEvents AE, AttendanceCodeGroups AG
		WHERE $siteselect AE.Date BETWEEN '$startY' AND '$endY' AND AE.CodeID = AG.CodeID
		GROUP BY AG.GroupID", ARRAY_A);
//print_r($yearinfo);
foreach($yearinfo as $info) $yeargrp[$info['GroupID']] = $info['count'];
	
$quarterinfo = $db->get_results ("SELECT count(AG.GroupID)/2 as count, GroupID FROM AttendanceEvents AE, AttendanceCodeGroups AG
		WHERE $siteselect AE.Date BETWEEN '$startQ1' AND '$endQ' AND AE.CodeID = AG.CodeID
		GROUP BY AG.GroupID", ARRAY_A);
//print_r($quarterinfo);
foreach($quarterinfo as $info) $quartergrp[$info['GroupID']] = $info['count'];

$curdate = date('Y-m-d');
$currdatedisplay = date("m/d/Y");
//echo $curdate;
$todayinfo = $db->get_results ("SELECT count(AG.GroupID)/2 as count, GroupID FROM AttendanceEvents AE, AttendanceCodeGroups AG
		WHERE $siteselect AE.Date = '$curdate' AND AE.CodeID = AG.CodeID
		GROUP BY AG.GroupID", ARRAY_A);
//print_r($todayinfo);
foreach($todayinfo as $info) $todaygrp[$info['GroupID']] = $info['count'];

$aytd = number_format(($yeargrp[4]/($yeargrp[0] + $yeargrp[4])) * 100, 1);
$aquarter = number_format(($quartergrp[4]/($quartergrp[0] + $quartergrp[4])) * 100, 1);
$aday = number_format(($todaygrp[4]/($todaygrp[0] + $todaygrp[4])) * 100, 1);
$absent = $todaygrp[0] == "" ? 0 : number_format($todaygrp[0], 1);
$late = $todaygrp[1] == "" ? 0 : number_format($todaygrp[1], 1);

$aytd_display = $drill == "" ? "$aytd%" :
"<a href=index.php?cmd=AttendanceDrillDown&type=year&site=$site&year=$year&quarter=$quarter>$aytd%</a>";
$aquarter_display = $drill == "" ? "$aquarter%": 
"<a href=index.php?cmd=AttendanceDrillDown&type=quarter&site=$site&year=$year&quarter=$quarter>$aquarter%</a>";
$aday_display = $drill == "" ? "$aday%": 
"<a href=index.php?cmd=AttendanceDrillDown&type=day&site=$site&year=$year&quarter=$quarter&cdate=$curdate>$aday%</a>";
$absent_display = $drill == "" ? "$absent": 
"<a href='index.php?cmd=AttendanceDrillDown&type=absent&site=$site&cdate=$curdate'>$absent</a>";
$late_display = $drill == "" ? "$late": 
"<a href='index.php?cmd=AttendanceDrillDown&type=late&site=$site&cdate=$curdate'>$late</a>";

/* ********************** Computation for Discipline Logs ******************************* */

$siteselectD = $site != 'overall' ? "D.site='$site' AND" : "" ;

$yearDinfo = $db->get_results("SELECT count(consequence) as count, consequence FROM discipline D
		WHERE $siteselectD incidentdate BETWEEN '$startY' AND '$endY'
		GROUP BY consequence", ARRAY_A);
//print_r($yearinfo);
foreach($yearDinfo as $info) $yearDgrp[$info['consequence']] = $info['count'];

$quarterDinfo = $db->get_results("SELECT count(consequence) as count, consequence FROM discipline D
		WHERE $siteselectD incidentdate BETWEEN '$startQ' AND '$endQ' 
		GROUP BY consequence", ARRAY_A);
//print_r($yearinfo);
foreach($quarterDinfo as $info) $quarterDgrp[$info['consequence']] = $info['count'];

$dayDinfo = $db->get_results("SELECT count(consequence) as count, consequence FROM discipline D
		WHERE $siteselectD incidentdate  = '$curdate'
		GROUP BY consequence", ARRAY_A);
//print_r($yearinfo);
foreach($dayDinfo as $info) $dayDgrp[$info['consequence']] = $info['count'];

$susytd = $yearDgrp['S'] == "" ? 0 : number_format($yearDgrp['S'], 0);
$issytd = $yearDgrp['I'] == "" ? 0 : number_format($yearDgrp['I'], 0);
$gymytd = $yearDgrp['G'] == "" ? 0 : number_format($yearDgrp['G'], 0);

$susmtd = $quarterDgrp['S'] == "" ? 0 : number_format($quarterDgrp['S'], 0);
$issmtd = $quarterDgrp['I'] == "" ? 0 : number_format($quarterDgrp['I'], 0);
$gymmtd = $quarterDgrp['G'] == "" ? 0 : number_format($quarterDgrp['G'], 0);

$susday = $dayDgrp['S'] == "" ? 0 : number_format($dayDgrp['S'], 0);
$issday = $dayDgrp['I'] == "" ? 0 : number_format($dayDgrp['I'], 0);
$gymday = $dayDgrp['G'] == "" ? 0 : number_format($dayDgrp['G'], 0);
$drill ="";
$susytd_display = $drill == "" ? "$susytd" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=sus&type=year&site=$site&year=$year&quarter=$quarter>$susytd</a>";
$issytd_display = $drill == "" ? "$issytd" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=iss&type=year&site=$site&year=$year&quarter=$quarter>$issytd</a>";
$gymytd_display = $drill == "" ? "$gymytd" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=gym&type=year&site=$site&year=$year&quarter=$quarter>$gymytd</a>";

$susmtd_display = $drill == "" ? "$susmtd" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=sus&type=quarter&site=$site&year=$year&quarter=$quarter>$susmtd</a>";
$issmtd_display = $drill == "" ? "$issmtd" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=iss&type=quarter&site=$site&year=$year&quarter=$quarter>$issmtd</a>";
$gymmtd_display = $drill == "" ? "$gymmtd" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=gym&type=quarter&site=$site&year=$year&quarter=$quarter>$gymmtd</a>";

$susday_display = $drill == "" ? "$susday" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=sus&type=day&site=$site&year=$year&quarter=$quarter>$susday</a>";
$issday_display = $drill == "" ? "$issday" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=iss&type=day&site=$site&year=$year&quarter=$quarter>$issday</a>";
$gymday_display = $drill == "" ? "$gymday" :
"<a href=index.php?cmd=DisciplineDrillDown&kind=gym&type=day&site=$site&year=$year&quarter=$quarter>$gymday</a>";


/* ********************** Computation for Student Tracking ******************************* */

// Student Tracking
// New Students

$siteselectD = $site != 'overall' ? "enterlocation='$site' AND" : "" ;
$scodes = $site != 'overall' ? "1,2,3,4,5,6,7,8": "2,3,4,5,6";

$yearSinfo = $db->get_results("SELECT count(studentid) as count FROM movement 
		WHERE $siteselectD enterdate BETWEEN '$startY' AND '$endY'
			AND entercode in ($scodes)
		GROUP BY studentid", ARRAY_A);
$newy_display =  $yearSinfo[0]['count'] = ""? 0 : number_format($yearSinfo[0]['count']);

$quarterSinfo = $db->get_results("SELECT count(studentid) as count FROM movement
		WHERE $siteselectD enterdate BETWEEN '$startQ' AND '$endQ' 
			AND entercode in ($scodes)
		GROUP BY studentid", ARRAY_A);
$newq_display =  $quarterSinfo[0]['count'] = ""? 0 : number_format($quarterSinfo[0]['count']);

$daySinfo = $db->get_results("SELECT count(studentid) as count FROM movement
		WHERE $siteselectD enterdate  = '$curdate'
			AND entercode in ($scodes)
		GROUP BY studentid", ARRAY_A);
$newd_display = $daySinfo[0]['count'] = ""? 0 : number_format($daySinfo[0]['count'], 0);

//$newy_display = "4";
//$newq_display = "5";
//$newd_display = "6";

$siteselectD = $site != 'overall' ? "enterlocation='$site' AND" : "" ;
$ecodes = $site != 'overall' ? "1,2,3,4,5,6,7,8,9,10,11,12": "2,3,4,5,6,7,8,9,10,11,12";

$yearDropinfo = $db->get_results("SELECT count(studentid) as count FROM movement 
		WHERE $siteselectD exitdate BETWEEN '$startY' AND '$endY'
			AND exitcode in ($ecodes)
		GROUP BY studentid", ARRAY_A);
$dty_display =  $yearDropinfo[0]['count'] = ""? 0 : number_format($yearDropinfo[0]['count']);

$quarterDropinfo = $db->get_results("SELECT count(studentid) as count FROM movement
		WHERE $siteselectD exitdate BETWEEN '$startQ' AND '$endQ' 
			AND exitcode in ($ecodes)
		GROUP BY studentid", ARRAY_A);
$dtq_display =  $quarterDropinfo[0]['count'] = ""? 0 : number_format($quarterDropinfo[0]['count']);

$dayDropinfo = $db->get_results("SELECT count(studentid) as count FROM movement
		WHERE $siteselectD exitdate  = '$curdate'
			AND exitcode in ($ecodes)
		GROUP BY studentid", ARRAY_A);
$dtd_display = $dayDropinfo[0]['count'] = ""? 0 : number_format($dayDropinfo[0]['count'], 0);

// Drops/Transfer
//$dty_display = "7";
//$dtq_display = "8";
//$dtd_display = "9";

// Academics
// New Levels
$anewy_display = "10";
$anewq_display = "11";
$anewd_display = "12";

$nproy_display = "13";
$nproq_display = "14";
$nprod_display = "15";

$nadvy_display = "16";
$nadvq_display = "17";
$nadvd_display = "18";

/* ********************************************************************************* */

$siteList = getSitesOptions($site);

${"site_" . $site} = 'selected';

$pulldown = "
<form name=ptime method=get action=\"index.php\">
<input type=hidden name=cmd value=Dashboard>
<input type=hidden name=year value=$year>
<input type=hidden name=quarter value=$quarter>
<table>
	<tr><td>
		$selectOptions
	</td><td>
		$quarterOptions
	</td><td>
		$yearOptions
	</td></tr>
</table>
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
																			<b><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2" color="#0000cc">$year-$nextyear $quarterdisplay</font></font></b></div>
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
																		$aytd_display</font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Today's Rate:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																		$aday_display</font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Absent:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$absent_display</font></td>
																</tr>

																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Quarterly Rate:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																		$aquarter_display</font></td>
																	<td nowrap>
																		<div align="right">

																			</div>
																	</td>
																	<td nowrap></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Late:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$late_display</font></td>

																</tr>
<!-- DISCIPLINE -->
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
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$susytd_display</font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Suspensions - Quarter:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$susmtd_display</font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Suspended:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$susday_display</font></td>
																</tr>

																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>ISS YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$issytd_display</font></td>
																	<td nowrap>
																		<div align="right">

																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>ISS - Quarter:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$issmtd_display</font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>ISS:</b></font></div>
																	</td>

																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$issday_display</font></td>
																</tr>
																<tr>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gym List YTD:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$gymytd_display</font></td>

																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gym List - Quarter:</b></font></div>
																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$gymmtd_display</font></td>
																	<td nowrap>
																		<div align="right">
																			<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gym List:</b></font></div>

																	</td>
																	<td nowrap><font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">$gymday_display</font></td>
																</tr>
<!-- DISCIPLINE END -->


															</table>

END;

include_once("template.inc");

function getYearOption ($year) {
	global $db, $CurrentYear;
	
	$years = $db->get_results("select distinct(year) as year from quarters");
	$current = false;
  	foreach ($years as $yr) {
  		if ($yr->year != '') {
			$val = $yr->year;
			$nextval = $val + 1;
			$selected = $year == $val ? "selected": "";
			$str .= "<option value='$val' $selected>$val-$nextval</option>\n";
			$current = ($val == $CurrentYear) ? true : $current;
		}
  	}
  	$nextvalcurrent = $CurrentYear + 1;
  	$selected = $year == $CurrentYear ? "selected": "";
  	$str .= ($current == true) ? "" : "<option value='$CurrentYear' $selected>$CurrentYear-$nextvalcurrent</option>\n";
  	return ($str);	
}


?>
