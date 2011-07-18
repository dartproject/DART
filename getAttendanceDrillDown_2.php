<?php

$site = getValue($_GET, 'site');
$curdate = getValue($_GET, 'cdate');
$type = getValue($_GET, 'type');
$year = getValue($_GET, 'year');
$quarter = getValue($_GET, 'quarter');
$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND" : "" ;
$nextyear = $year+1;
$dates = getDates($year, $quarter, $curdate);

$start = getValue($_GET, "start", 0);
$limit = getValue($_GET, "limit", 30);
$sort = getValue($_GET, "sort", "name");
$dir = getValue($_GET, "dir", "ASC");

$titles = array(
	"year" => "Year vew: $year - ".($year+1)." for Site: $site",
	"quarter" => "Quarter vew: Q$quarter for Site: $site",
	"day" => "Day view: $currdatedisplay for Site: $site",
	"absent" => "Absent Day view: $currdatedisplay for Site: $site",
	"late" => "Late Day view: $currdatedisplay for Site: $site"
);

$groups = $db->get_results("SELECT * FROM AttendanceGroups");

$sql = NULL;
if(in_array($type, array_keys($dates))) { // year, quarter or day
	$date = $dates[$type];
	$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID 
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date BETWEEN '$date[0]' AND '$date[1]' AND AE.CodeID = AG.CodeID and S.studentid = AE.studentid
		 GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
} else if (in_array($type, $day_options)) { // absent, late
	$id = "";
	foreach($groups as $g) {
		if(strtolower($g->Description) == $type) {
			$id = $g->GroupID;
			break;
		}
	}
	$date = $dates["day"];
	$currdatedisplay = PHPDate("m/d/Y", $date[0]);
	$studentlist = getStudentIn("SELECT S.studentid as id
		FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
		WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID and AG.GroupID = $id
			and S.studentid = AE.studentid 
		GROUP BY S.studentid");
	if($studentlist != NULL) {
		$sql = "SELECT AE.SiteID, S.studentid as id, fname, lname, count(AG.GroupID)/2 as count, GroupID
			FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
			WHERE $siteselect AE.Date = '$date[0]' AND AE.CodeID = AG.CodeID and S.studentid IN ($studentlist) 
			AND S.studentid = AE.studentid AND AG.GroupID = $id 
			GROUP BY S.studentid, site, AG.GroupID ORDER BY S.lname, S.fname";
	}
}

$info = NULL;
if($sql != NULL) {
	$info = $db->get_results ($sql, ARRAY_A);
}
if($info == NULL) $info = array();

$studentid = array();
$site = array();
$fname = array();
$lname = array();

$categories = array();
foreach($groups as $g) {
	$categories[$g->GroupID] = $g->Description;
	${$categories[$g->GroupID]} = array();
}
foreach ($info as $student) {
	$id = $student['id'];
	$sitestu = $student['SiteID'];
	$group = $student['GroupID'];
	$key = $id."_".$sitestu;
	if(!isset($studentid[$key])) {
		foreach($groups as $g) {
			${$categories[$g->GroupID]}[$key] = 0;
		}
	}
	$studentid[$key] = $id;
	$fname[$key] = $student['fname'];
	$lname[$key] = $student['lname'];
	$site[$key] = $sitestu;
	${$categories[$group]}[$key] = number_format($student['count'], 1);
}

// SORT & LIMIT (it seems faster than doing it in the DB)
$direction = $dir == "ASC"? SORT_ASC : SORT_DESC;

if($sort == "name") {
	array_multisort($lname, $direction, $fname, $direction);
	$keys = array_keys($lname);
} else {
	array_multisort(${$sort}, $direction);
	$keys = array_keys(${$sort});
}

$total = count($keys);
$rows = array();
$new_keys = array_slice($keys, $start, $limit);
foreach($new_keys as $k) {
	$row = array("studentid" => $studentid[$k],
		"name" => "$fname[$k] $lname[$k]",
		"site" => $site[$k]
	);
	foreach($groups as $g) {
		$row[$g->Description] = ${$g->Description}[$k];
	}
	$rows[] = $row;
}

$results = array("totalCount" => $total, "success" => true, "rows" => $rows);

echo json_encode($results);

?>
