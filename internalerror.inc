<?php

global $db;

set_time_limit(0);

if($_POST['submit'] != "") {
	$list = $_POST['grdval'];
//	print_r($list);
	$body = "Successfully Deleted<br>";
	foreach ($list as $grd) {
		$id = strtok($grd, ".");
		$subject = strtok(".");
		$level = strtok(".");
		$std = strtok(".");
		$value = strtok(".");
		$sql = "delete from grades where studentid = '$id' and subject = '$subject' and level = '$level' and std = '$std' and value = '$value' limit 1";
		$db->get_results($sql);
		$body .= "Delete $id - $subject.$level.std = $value<br>";
		updateSingleLevelScore($id, $subject, $level);
	}

} else {

$results = $db->get_results("SELECT grades.*, fname, lname
FROM grades, studentlevel, student
WHERE progress = 'INTERNAL ERR - Too many values see developer' and studentlevel.subject = grades.subject and studentlevel.level = grades.level and grades.studentid = studentlevel.studentid and student.studentid = grades.studentid order by grades.studentid, grades.subject, grades.level, std ", ARRAY_A);
$body .= "<form action=index.php?cmd=InternalError method=post>";
$body .= "<table border=1> <tr><th></th><th>StudentID</th><th>Name</th><th>Area</th><th>Level</th><th>Standard</th><th>Toggle</th><th><tr>";

foreach ($results as $grade) {
	$subject = $grade['subject'];
	$id = $grade['studentid'];
	$level = $grade['level'];
	$std = $grade['std'];
	$value = $grade['value'];
	$name = $grade['fname'] . " " . $grade['lname'];
	$grdval = "$id.$subject.$level.$std.$value";
//	echo $grdval;
	if($id != $oldstudent) {
		$oldstudent = $id;
		$body .= "<tr><td colspan=6 bgcolor=lighblue>&nbsp;</td></tr>";
	}
	$body .= "<tr><td><input type=\"checkbox\" name=\"grdval[]\" value=\"$grdval\" class=\"radio\"></td><td>$id</td><td>$name</td><td>$subject</td><td>$level</td><td>$std</td><td>$value</td></tr>\n";
}

$body .= "</table>";
$body .= "<input type=submit name=submit onClick='javascript: return confirmMsg(\"Are you sure you want to delete these toggles\");' value='Delete Checked'></form>";
}

include_once("template.inc");
?>
