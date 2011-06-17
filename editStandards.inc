<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$subject = $_GET['subject'];
$level = $_GET['level'];

if($_POST['button'] != '') {
	$body .= "<font color=red>Values are saved</font>";
	$shortname = $_POST['shortname'];
	$sval = $_POST['subject'];
	$type = $_POST['type'];
	$slevel = $_POST['level'];
	$std = $_POST['std'];
	$link = $_POST['link'];
	$description = $_POST['description'];
	$ident = $_POST['id'];
	$order = $_POST['ord'];
	for($i=0; $i < count($ident) ; $i++) {
		$id = $ident[$i];
		$sn =  $shortname[$i];
		$desc =  $description[$i];
//		echo "$desc\n";
		$lk =  $link[$i];
		$sub = $sval[$i];
		$lev = $slevel[$i];
		$ty = $type[$i];
		$sd = $std[$i];
		$ord = $order[$i];
		
		$sql = "UPDATE standards set standards.order = '$ord', shortname = '$sn', description = '$desc', link = '$lk', type='$ty'
				where subject = '$sub' and level = '$lev' and std='$sd'";
//		echo $sql . "<br><br>";
		$db->get_results($sql);
	}
	$update = "UPDATE standards SET description = REPLACE(REPLACE(REPLACE(description, '\r', ''), '\n', ''), '\\\\', '')";
	$db->get_results($update);

}

$body .= selectEditStdMenu();
$body .= standardSelection($subject, $level);
/*
$body .= "<script>
function onChange(name) {

//	alert(name);
	document.std.change.value = document.std.change.value + ', ' + name;
}
</script>";
// <input type=text name=shortname$id value='$shortname' onChange='javascript:onChange(this.name);'>
*/

$standards = $db->get_results("select * from standards where subject = '$subject' and level = '$level' ORDER BY `standards`.`order` ASC  ");

//$db->debug();

//print_r($standards);

$body .= "<form name=std action='.?cmd=editStandards&subject=$subject&level=$level' method = post>
<input name=change type=hidden>
<table border=1 width=600><tr><th>Ord</th><th>Standard</th><th>Type</th><th>Shortname</th><th>Description</th><th>Link</th></tr>";
$s = 20;
$c = 30;
$r = 4;



foreach($standards as $std) {
	$id = $std->Identifier;
	$ord = $std->order;
	$shortname =  $std->shortname;
	$sub =  $std->subject;
	$lv =  $std->level;
	$type =  $std->type;
	${"type_" . $type} = "selected";
	$sd =  $std->std;
	$description = $std->description;
	$link = $std->link;
// echo "$subject.$level.$sd-";
	$body .= "<tr valign=top>
		<td><input name=ord[] value='$ord' size=3></td>
		<td>$subject.$level.$sd
			<input type=hidden name=id[] value='$id'>
			<input type=hidden name=subject[] value='$sub'>
			<input type=hidden name=level[] value='$lv'>
			<input type=hidden name=std[] value='$sd'>
		</td>
		<td>
			<select name=type[]>
				<option value=''></option>
				<option value='std' $type_std>Std</option>
				<option value='QPI' $type_QPI>QPI</option>
				<option value='over'  $type_over>Over</option>
			</select>
		</td>
		<td><textarea cols=$c rows=$r name=shortname[]>$shortname</textarea></td>
		<td><textarea cols=$c rows=$r name=description[]>$description</textarea></td>
		<td><textarea cols=$c rows=$r name=link[]>$link</textarea></td>
		</tr>";
	${"type_" . $type} = '';
}

$body .= "</table>
<input type=submit name=button value=Save> <input type=reset name=button value='Reset Values'>
</form>";

include ("template.inc");

function standardSelection($subject, $level) {
	global $db;
	
	${"subject_" . $subject} = "selected";
	$sql = "select distinct(level) as level from level order by level";
	$results = $db->get_results($sql, ARRAY_A);
	foreach($results as $row) {
		$val = $row['level'];
		$selected = ($val == $level)? "selected": "";
		$option .= "<option value=$val $selected>$val</option>";
	}
	$sql = "select distinct(subject) as subject from level order by subject";
	$results = $db->get_results($sql, ARRAY_A);
	foreach($results as $row) {
		$val = $row['subject'];
		$selected = ($val == $subject)? "selected": "";
		$option2 .= "<option value=$val $selected>$val</option>";
	}
	$str = <<<END
		<form action='./index.php' method=get>
		<input type=hidden name=cmd value=editStandards>
			<select name=subject>
				$option2
		<select name=level>
				$option
		<input type=submit value='Go To Standards'>
		</form>
END;
	return($str);
}

?>