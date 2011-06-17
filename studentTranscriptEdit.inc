<?php


$B9Priv = PrivilegeB(B9);

if($B9Priv != 'district') { NoPriv("denied advEdit", "You should not be trying to do advance editing. Email sent to admin"); }

$id = $_GET['id'];

if($_POST['save'] <> "") {
	$testing = addslashes($_POST['testing']);
	$additional = addslashes($_POST['additional']);
	$extracurricular = addslashes($_POST['extracurricular']);
	
	$db->query("update student set testing='$testing', additional='$additional', extracurricular='$extracurricular' where studentid = '$id'");
}

$student = getStudentInfo($id);
$url = $_SERVER[PHP_SELF];

$name = $student['fname'] . " " . $student['lname'];
$test = $student['testing'];
$add = $student['additional'];
$extra = $student['extracurricular'];

$body = <<<END
<h1>Transcript Information For $name</h1><br>
	<form action=$url?cmd=StudentTranscriptEdit&id=$id method=post>
	Testing:<br>
	<textarea name=testing cols=40 rows=10>$test</textarea></br>
	Additional:<br>
	<textarea name=additional cols=40 rows=10>$add</textarea></br>
	Extracurricular:<br>
	<textarea name=extracurricular cols=40 rows=10>$extra</textarea></br>
	<input type=submit name=save value=Save><input type=reset name=reset value=Reset>
	</form>

END;

include ("template.inc");

?>