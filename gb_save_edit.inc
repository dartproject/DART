<?php

$val = $_GET['val'];
$sep = $_GET['sep'];

$sval = explode ($sep, $val);

// echo "$sep***$val";

$table = $sval[0];
$name = $sval[1];
$field = $sval[2];
$id = $sval[3];
$value = $sval[4];

$sql = "UPDATE $table set $name = '$value' where $field='$id' ";
//echo $sql;
$db->get_results($sql);
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
//echo "TBD";
//echo $sql;		

?>
