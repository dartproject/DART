<?php

include_once("lib/function_discipline.inc");
$B4Priv = PrivilegeB(B4);
$B3Priv = PrivilegeB(B3);

if($B3Priv == 'site') {
	$site = $currentMySite;
	$selectOptions = "<b>$site</b>";
} else if ($B3Priv == 'district') {
	$site = getValue($_GET, 'site', ($currentMySite == 'Admin' ? 'overall' : $currentMySite));

	/* Sites */
	$sites = getSites("district");
	$siteMenu = array("overall" => "Overall");
	foreach ($sites as $s) {
		$siteMenu[$s['siteid']] = $s['siteid'];
	}
	$siteMenu["Private"] = "Private";
}

$drill = true;
$year = getValue($_GET, 'year', $CurrentYear);
$quarter = getValue($_GET, 'quarter', $CurrentQuarter);
$nextyear = $year+1;

/* Years */
$years = getYearOption();
$yearMenu = array();
foreach ($years as $y) {
	$yearMenu[$y->curr] = $y->curr."-".$y->next;
}

/* Quarters */
$quarterMenu = array(
	1 => "Q1",
	2 => "Q2",
	3 => "Q3",
	4 => "Q4"
);

$dates = getDates($year, $quarter);
$curdate = date('Y-m-d');
$currdatedisplay = date("m/d/Y");
$sections = array();

/* ********************** Computation for Attendance ******************************* */

$attendance =  getAttendanceSummary($site, $dates);

$sections["Attendance"] = array();
$sections["Attendance"][] = array(
	"year" => array(
		"label" => "Attendance - YTD",
		"value" => $attendance["year"]."%",
		"param" => "year=$year&quarter=$quarter"),
	"day" => array(
		"label" => "Today's Rate",
		"value" => $attendance["day"]."%",
		"param" => "year=$year&quarter=$quarter"),
	"absent" => array(
		"label" => "Absent",
		"value" => $attendance["absent"],
		"param" => "cdate=$curdate")
);
$sections["Attendance"][] = array(
	"quarter" => array(
		"label" => "Quartely Rate",
		"value" => $attendance["quarter"]."%",
		"param" => "year=$year&quarter=$quarter"),
	"" => array(
		"label" => "",
		"value" => ""),
	"absent" => array(
		"label" => "Late",
		"value" => $attendance["late"],
		"param" => "cdate=$curdate")
);

/* ********************** Computation for Discipline Logs ******************************* */
/* TODO: $consequenceValues: This array is defined in lib/function_discipline */
$discipline = getDisciplineSummary($site, $dates, $consequenceValues);

$sections["Discipline"] = array(
	"year" => array(
		"label" => "YTD",
		"value" => $discipline["year"]),
	"quarter" => array(
		"label" => "Quarter",
		"value" => $discipline["quarter"]),
	"day" => array(
		"label" => "Today",
		"value" => $discipline["day"])
);
$disciplineLabels = array(
	"suspended" => "Suspensions",
	"iss" => "ISS",
	"gym" => "Gym List"
);

/* ********************** Computation for Student Tracking ******************************* */

/* TODO: None of the following code is used */
// Student Tracking
// New Students

/*
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
 */
/* ********************************************************************************* */

function getYearOption () {
	global $db, $CurrentYear;
	$years = $db->get_results("SELECT DISTINCT(year) as curr, (year+1) AS next FROM quarters WHERE year <> 0 ORDER BY year DESC");
  	return $years;	
}

function getDates($year, $quarter) {
	global $db;
	$sql = "select * from quarters where year = '$year' order by quarter ";
	$res = $db->get_results($sql, ARRAY_A);
	$startQ = $res[$quarter-1]['start'];
	$endQ = $res[$quarter-1]['finish'];
	$startY = $res[0]['start'];
	$endY = $res[3]['finish'];
	$curdate = date('Y-m-d');
	$dates = array(
		"quarter" => array($res[$quarter-1]['start'], $res[$quarter-1]['finish']),
		"year" => array($res[0]['start'], $res[3]['finish']),
		"day" => array($curdate, $curdate)
	);
	return $dates;
}

function getAttendanceSummary($site, $dates) {
	global $db;
	$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
	$attendance = array();

	foreach($dates AS $key => $date) {
		$res = $db->get_results ("SELECT description, count(AG.GroupID)/2 as count FROM AttendanceEvents AE, AttendanceCodeGroups AG, AttendanceGroups G 
			WHERE $siteselect AE.Date BETWEEN '$date[0]' AND '$date[1]' AND AE.CodeID = AG.CodeID AND G.GroupID = AG.GroupID 
			GROUP BY G.description");
		$present = 0; $absent = 0; $late = 0;
		if($res != NULL) {
			foreach($res as $row) {
				switch($row->description) {
					case 'Present': $present = $row->count; break;
					case 'Absent': $absent = $row->count; break;
					case 'Late': $late = $row->count;
				}
			}
		}
		if($absent+$present > 0)
			$attendance[$key] = number_format(($present/($absent + $present)) * 100, 1); 
		else
			$attendance[$key] = 0;
		if($key == "day") {
			$attendance["absent"] = number_format($absent, 1);
			$attendance["late"] = number_format($late, 1);
		}
	}

	return $attendance;
}

function getDisciplineSummary($site, $dates, $consequenceValues) {
	global $db;
	$siteselectD = $site != 'overall' ? "D.site='$site' AND" : "" ;
	$discipline = array();
	$consequences = makeArr($consequenceValues); /* Function in lib/function_discipline */
	$consequences = array_flip($consequences);

	foreach($dates AS $key => $date) {
		$discipline[$key] = array("suspended" => 0, "iss" => 0, "gym" => 0);
		$res = $db->get_results ("SELECT count(consequence) as count, consequence FROM discipline D 
		WHERE $siteselectD incidentdate BETWEEN '$date[0]' AND '$date[1]'
		GROUP BY consequence", ARRAY_A);
		if($res != NULL) {
			foreach($res as $row) {
				switch($row['consequence']) {
					case $consequences['Suspended']: $discipline[$key]['suspended'] = $row['count']; break;
					case $consequences['ISS']: $discipline[$key]['iss'] = $row['count']; break;
					case $consequences['Gym List']: $discipline[$key]['gym'] = $row['count'];
				}
			}
		}
	}
	return $discipline;
}

$title = "Dashboard";
$var = array("site", "quarter", "year");
foreach($var as $v) {
	$menus[$v] = array(
		"selected" => ${$v},
		"menu" => ${$v."Menu"}
	);
}

$smarty->assign('pageTitle',$title);
$smarty->assign('menus',$menus);
$smarty->assign('sections',$sections);
$smarty->assign('disciplineLabels',$disciplineLabels);
$smarty->assign('year',$year);
$smarty->assign('quarter',$quarter);
$smarty->assign('currdatedisplay',$currdatedisplay);
$smarty->assign('site',$site);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('dashboard.tpl');


?>
