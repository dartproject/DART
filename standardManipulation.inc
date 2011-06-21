<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

while(list($var, $val) = each($_POST)) {
	${$var} = $val;
}

if($action == 'Change') {
	$cmsg = ChangeStandards($subject, $level, $standard, $newstandard);
} else if ($action == 'New') {
	$nmsg = NewStandards($subject, $level, $newstandard);
} else if ($action == 'Delete') {
	$dmsg = DeleteStandards($subject, $level, $standard);
}

$sql = "select distinct(level) as level from level order by level";
$results = $db->get_results($sql, ARRAY_A);
foreach($results as $row) {
	$val = $row['level'];
	$levelOptions .= "<option value=$val $selected>$val</option>";
}
$sql = "select distinct(subject) as subject from level order by subject";
$results = $db->get_results($sql, ARRAY_A);
foreach($results as $row) {
	$val = $row['subject'];
	$subjectOptions .= "<option value=$val $selected>$val</option>";
}
$sql = "select distinct(std) as std from standards order by std";
$results = $db->get_results($sql, ARRAY_A);
foreach($results as $row) {
	$val = $row['std'];
	$standardsOptions .= "<option value=$val $selected>$val</option>";
}

$body .= selectEditStdMenu();

$body .= <<<END
<form action=index.php?cmd=standardManipulation method=post>
<h2>Changes Standard</h2>
This will change the standard and all grades for every student associated with that standard.<br><font color=red>$cmsg</font><br>
	<table>
		<tr>
			<td>Subject: <select name=subject><option value="">-select-</option>$subjectOptions</select></td>	
			<td>Level: <select name=level><option value="">-select-</option>$levelOptions</select></td>
			<td>Old Standard <select name=standard><option value="">-select-</option>$standardsOptions</select></td>
			<td>Change to ===></td>
			<td><input type=text name=newstandard size=4></td>
			<td><input type=submit name=action value=Change></td>
		</tr>
	</table>	
</form>
<hr>
<br>
<form action=index.php?cmd=standardManipulation method=post>
<h2>Create New Standard</h2>
<font color=red>$nmsg</font><br>
	<table>
		<tr>
			<td>Subject: <select name=subject><option value="">-select-</option>$subjectOptions</select></td>	
			<td>Level: <select name=level><option value="">-select-</option>$levelOptions</select></td>
			<td>New Standard</td>
			<td><input type=text name=newstandard size=4></td>
			<td><input type=submit name=action value=New></td>
		</tr>
	</table>	
</form>
<hr>
<br>

<form action=index.php?cmd=standardManipulation method=post>
<h2>Delete Standard</h2>
This will delete the standard and all grades for every student associated with that standard.<br>
<font color=red>$dmsg</font><br>
	<table>
		<tr>
			<td>Subject: <select name=subject><option value="">-select-</option>$subjectOptions</select></td>	
			<td>Level: <select name=level><option value="">-select-</option>$levelOptions</select></td>
			<td>Old Standard <select name=standard><option value="">-select-</option>$standardsOptions</select></td>
			<td><input type=submit name=action value=Delete></td>
		</tr>
	</table>	
</form>

END;

function ChangeStandards($subject, $level, $standard, $newstandard) {
	global $db;

	$newresults = $db->get_results("select * from standards where subject = '$subject' and level = '$level' and std = '$newstandard' ");
	$results = $db->get_results("select * from standards where subject = '$subject' and level = '$level' and std = '$standard' ");
	if($newresults == '' and $results != '') {
		$db->get_results("update standards set std = '$newstandard' where subject = '$subject' and level = '$level' and std = '$standard' ");
//		$db->get_results("update grades set std = '$newstandard' where subject = '$subject' and level = '$level' and std = '$standard' ");
		$str = "Standard change successfully from $subject.$level.$standard => $subject.$level.$newstandard";
	} else if ($newresults != '') {
		$str = "New Standard already exists $subject.$level.$newstandard";
	} else {
		$str = "Old Standard does not exists $subject.$level.$standard";
	}
	return ($str);
}

function NewStandards($subject, $level, $newstandard) {
	global $db;
	
	$newresults = $db->get_results("select * from standards where subject = '$subject' and level = '$level' and std = '$newstandard' ");
	if($newresults == '' ) {
		$db->get_results("insert standards set subject = '$subject', level = '$level', std = '$newstandard' ");
		$str = "Standard added successfully $subject.$level.$newstandard ";
	} else if ($newresults != '') {
		$str = "New Standard already exists $subject.$level.$newstandard";
	}
	return ($str);
}
function DeleteStandards($subject, $level, $standard) {
	global $db;
	
	$results = $db->get_results("select * from standards where subject = '$subject' and level = '$level' and std = '$standard' ");
	if($results != '' ) {
		$db->get_results("delete from standards where subject = '$subject' and level = '$level' and std = '$standard' ");
		$db->get_results("delete from grades where subject = '$subject' and level = '$level' and std = '$standard' ");
		$str = "Standard deleted successfully $subject.$level.$standard ";
	} else if ($results == '') {
		$str = "Standard does not exists $subject.$level.$standard";
	}
	return ($str);

	return ("Delete");
}

include_once('template.inc');
?>
