<?php

include_once ("ListMembers.php");

$listID = getValue($_GET, "listID");
$time = time();
$year = getValue($_GET, "year", date("Y", $time));
$month = getValue($_GET, "month", date("n", $time));
$day = getValue($_GET, "day", date("j", $time));
$date = "$year-$month-$day";
$period = getValue($_GET, "period", 0);

$start = getValue($_GET, "start", 0);
$limit = getValue($_GET, "limit", 30);
$sort = getValue($_GET, "sort", "lname");
$dir = getValue($_GET, "dir", "ASC");

if($sort == 'name') $sort = "lname"; // Sort by last name instead of by "fname lname"
else if($sort == 'studentid') $sort = 'list_members_tmp.studentid';
else if($sort == 'grade_order') { //  For PK & K grades (grade_order = 0)
	$other_dir = $dir == "ASC" ? "DESC" : "ASC";
	$sort = "grade_order $dir, grade $other_dir";
	$dir = "";
}

$listMembers = new ListMembers($db, $listID, $currentUserID); // $currentUserID is a global variable

$sql = "SELECT list_members_tmp.studentid, CONCAT_WS(' ', fname, lname) AS name, site, alaskaid, grade, cast(grade as unsigned) AS grade_order, bday, datediff(current_date(),bday) AS age_order, AC.Code, AG.Description AS attendance ".
		"FROM (list_members_tmp, student) ".
		"LEFT JOIN ".
		"(AttendanceCodeGroups AS ACG, AttendanceCodes AS AC, AttendanceGroups AS AG, AttendanceEvents AS AE) ".
		"ON (AC.CodeID = ACG.CodeID AND AG.GroupID = ACG.GroupID AND AE.date = '$date' AND AE.PeriodID = '$period' AND AE.studentid = list_members_tmp.studentid AND AE.CodeID = AC.CodeID AND (AG.Description = 'Absent' OR AG.Description = 'Present')) ".
		"WHERE ".
		"student.studentid = list_members_tmp.studentid AND list_members_tmp.process_id = '".$listMembers->getId()."' ".
		"ORDER BY $sort $dir ".
		"LIMIT $start, $limit";

$list = $db->get_results($sql, ARRAY_A);

$results = array("totalCount" => $listMembers->count(), "success" => true, "students" => array());
if($list != null) {
	foreach($list as $row) {
		$row['age'] = age($row['bday']);
		$results['students'][] = $row;
	}
}

echo json_encode($results);

?>
