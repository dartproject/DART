<?php

$val = $_GET['val'];
$field = $_GET['field'];
$weighted = $_GET['weighted'];

$sval = explode ("_", $val);
$sfield = explode("_", $field);

if($sval[2] == '') {
	$sql = "DELETE FROM gb_scores WHERE
		sid = '{$sval[0]}' and aid = '{$sval[1]}'
		";
} else { 
	$sql = "INSERT INTO gb_scores
		SET
			sid = '{$sval[0]}',
			aid = '{$sval[1]}',
			score = '{$sval[2]}'
		ON DUPLICATE KEY UPDATE
			score = '{$sval[2]}'
		";
}
$db->get_results($sql);

if($weighted == '0') {
	$sql = "SELECT AVG(score) FROM gb_scores, gb_assignments
			where sid = '{$sfield[0]}' and gb_scores.aid = gb_assignments.aid and
				gid = '{$sfield[1]}' and score != ''
			";
	$total = $db->get_var($sql);
} else {
	$sql = "SELECT AVG(score) as scoreavg, weight FROM  (gb_assignments, gb_catwt)
			LEFT JOIN gb_scores ON gb_scores.aid = gb_assignments.aid and sid = '{$sfield[0]}'
			where  
				gb_assignments.gid = '{$sfield[1]}' and 
				gb_catwt.cid = gb_assignments.category
			GROUP BY gb_catwt.cid
			";
	$scores = $db->get_results($sql, ARRAY_A);
	foreach($scores as $s) {
		if($s['scoreavg'] != '') {
			$cum += $s['scoreavg'] * $s['weight'];
			$weight += $s['weight'];
		}
	}
	$total = $cum/$weight;
}
$total = round($total, 0);
/*
$sql = "INSERT INTO gb_scores
		SET
			sid = '{$sval[0]}',
			aid = '{$sval[1]}',
			score = '{$sval[2]}'
		ON DUPLICATE KEY UPDATE
			score = '{$sval[2]}'
		";
$db->get_results($sql);

DELETE gb_scores WHERE 		sid = '670452' and aid = '5' 		<blockquote><font face=arial size=2 color=ff0000><b>SQL/DB Error --</b> [<font color=000077>You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'WHERE 		sid = '670452' and aid = '5'' at line 1</font>]</font></blockquote>75/TBD
*/
echo "$total/TBD";
//echo $sql;		

?>