<?php

//$studentid = $studentid == "" ? $_GET['studentid'] : $studentid;
$studentid = $_GET['studentid'];
$studentInfo = getStudentInfo($studentid);
$site = $studentInfo['site'];
$studentname = $studentInfo['fname'] .  " " . $studentInfo['lname'];

$body = "<h1>Movement For $studentname<br><br><br>STILL UNDER CONSTRUCTION</h1>";

include('template.inc');
?>
