<?php

include ("repcurrentcreatefunc.inc");

$studentID = $_GET['id'];
$start = $_GET['start'];
$finish = $_GET['finish'];


$body = createRepCurRep($studentID, $start, $finish);		

include ("template.inc");

?>