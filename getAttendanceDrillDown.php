<?php

$site = getValue($_GET, 'site');
$curdate = getValue($_GET, 'cdate', date('Y-m-d'));
$type = getValue($_GET, 'type');
$year = getValue($_GET, 'year', $CurrentYear);
$quarter = getValue($_GET, 'quarter', $CurrentQuarter);

$siteselect = $site != 'overall' ? "AE.SiteID='$site' AND " : "" ;

$start = getValue($_GET, "start", 0);
$limit = getValue($_GET, "limit", 30);
$sort = getValue($_GET, "sort", "name");
$dir = getValue($_GET, "dir", "ASC");

if($sort == 'name') $sort = "lname $dir, fname";
else if($sort == 'studentid') $sort = 's.studentid';

$d = explode("-",$curdate);
$currdatedisplay = date("m/d/Y", mktime(0,0,0,$d[1],$d[2],$d[0]));
$dates = getDates($year, $quarter, $curdate);

$day_options = array("absent", "late");

$groups = $db->get_results("SELECT * FROM AttendanceGroups");

if(in_array($type, array_keys($dates))) { // year, quarter or day
	$date = $dates[$type];
	$sql = "SELECT ";
	foreach($groups as $g) {
		$sql .= "SUM(IF(groupId = ".$g->GroupID.", 1,0))/2 as ".$g->Description.", ";
	}
	$sql .= "s.studentid, CONCAT_WS(' ', fname, lname) AS name, AE.siteID AS site ".
		"FROM student s, AttendanceEvents as AE, AttendanceCodeGroups as ACG ".
		"WHERE AE.codeID = ACG.codeID AND $siteselect".
		"AE.date between '$date[0]' and '$date[1]' AND ".
		"S.studentid = AE.studentid ".
		"GROUP BY S.studentid, AE.siteID ".
		"ORDER BY $sort $dir ".
		"LIMIT $start, $limit";
	$totalSql = "SELECT COUNT(DISTINCT AE.studentid, AE.siteID) AS total ".
		"FROM AttendanceEvents AS AE ".
		"WHERE $siteselect AE.date between '$date[0]' and '$date[1]'";
} else if (in_array($type, $day_options)) { // absent, late
	$id = "";
	foreach($groups as $g) {
		if(strtolower($g->Description) == $type) {
			$id = $g->GroupID;
			break;
		}
	}
	$sql = "SELECT s.studentid, CONCAT_WS(' ', fname, lname) AS name, AE.siteID AS site, ".
		"COUNT(*)/2 AS ".$g->Description." ".
		"FROM student s, AttendanceEvents as AE, AttendanceCodeGroups as ACG ".
		"WHERE AE.codeID = ACG.codeID AND $siteselect".
		"AE.date = '".$dates["day"][0]."' AND ".
		"S.studentid = AE.studentid AND ".
		"GroupID = $id ".
		"GROUP BY S.studentid, AE.siteID ".
		"ORDER BY $sort $dir ".
		"LIMIT $start, $limit";
	$totalSql = "SELECT COUNT(DISTINCT AE.studentid, AE.siteID) AS total FROM ".
		"AttendanceEvents AS AE, AttendanceCodeGroups AS ACG ".
		"WHERE AE.codeID = ACG.codeID AND $siteselect".
		"AE.date = '".$dates["day"][0]."' AND ".
		"GroupID = $id ";
}

$rows = $db->get_results($sql);
$res = $db->get_row($totalSql);

$results = array("totalCount" => $res->total, "success" => true, "rows" => $rows);

echo json_encode($results);

?>
