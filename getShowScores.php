<?php

include_once 'ListMembers.php';

$listID = getValue($_GET, "listID");

$start = getValue($_GET, "start", 0);
$limit = getValue($_GET, "limit", 30);
$sort = getValue($_GET, "sort", "name");
$dir = getValue($_GET, "dir", "ASC");

$subjects = getCoreSubjects();
$electives = getElectiveSubjects();

if($sort == 'name') $sort = "lname"; // Sort by last name instead of by "fname lname"
else if($sort == 'studentid') $sort = 'list_members_tmp.studentid';

$listMembers = new ListMembers($db, $listID, $currentUserID); // $currentUserID is a global variable

if($sort == "studentid")
	$sort = "list_members_tmp.studentid'";
else if($sort == "name")// Sort by last name instead of by "fname lname"
	$sort = "lname";

$fields = array();
$joins = array();
foreach($subjects as $s) {
	$fields[] = $s['id'].".level AS level_".$s['id'].", cast(".$s['id'].".level AS unsigned) AS level_".$s['id']."_order";
	$joins[] = "LEFT JOIN studentlevel AS ".$s['id']." ON ".$s['id'].".studentid = s.studentid ".
		"AND ".$s['id'].".subject = '".$s['id']."' AND ".$s['id'].".final = '00000000'";
}
$rows = array();
if(count($subjects) > 1) {
	$sql = "SELECT s.studentid, CONCAT_WS(' ', fname, lname) AS name, ".
		implode(", ", $fields).", ".
		"GROUP_CONCAT(e.subject) AS electives, GROUP_CONCAT(e.level) AS electives_level ".
		"FROM list_members_tmp, student AS s ".
		implode(" ", $joins)." ".
	   	"LEFT JOIN (studentlevel AS e, subjects AS sub) ON s.studentid = e.studentid AND sub.core <> 'x' AND sub.id = e.subject AND e.final = '00000000' ".
		"WHERE s.studentid = list_members_tmp.studentid AND list_members_tmp.process_id = '".$listMembers->getId()."' ".
		"GROUP BY s.studentid ". 
		"ORDER BY $sort $dir ".
		"LIMIT $start, $limit";

	$rows = $db->get_results($sql, ARRAY_A);
	// For students in more than one level per subject (it shouldn't happen but it does), electives will be duplicated
	for($i = 0; $i < count($rows); $i++) {
		$electives = explode(",", $rows[$i]['electives']);
		$levels = explode(",", $rows[$i]['electives_level']);
		if(count($electives) < 2) continue;
		$aux = array();
		for($j = 0; $j < count($electives); $j++)
			$aux[] = $electives[$j]."-^-".$levels[$j];
		$aux = array_unique($aux); // Remove only values with same elective and level
		$electives = array();
		$levels = array();
		foreach($aux as $x) {
			$row = explode("-^-", $x);
			$electives[] = $row[0];
			$levels[] = $row[1];
		}

		$rows[$i]['electives'] = implode(",", $electives);
		$rows[$i]['electives_level'] = implode(",", $levels);
	}
}
$results = array("totalCount" => $listMembers->count(), "success" => true, "students" => $rows);

echo json_encode($results);

?>
