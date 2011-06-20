<?php

$exitCode = $_POST['exitCode'];
$enterCode = $_POST['enterCode'];
$enterSite = $_POST['enterSite'];
$studentid = $_POST['studentid'];
if($exitCode == "" or $enterSite == "" or $enterSite == "") {
	$body = "<h1>All Value Must Be Filled In</h1>";
	$_GET['studentid'] = $studentid;
	include ("movement.inc");
} else {
	movestudent ($studentid, $exitCode, $enterCode, $enterSite);
	$body = "<h1>Student Sucessfully Moved</h1>";
	
	$_GET['p1'] = $studentid;
	include('toggleStudent.inc');
}

?>
