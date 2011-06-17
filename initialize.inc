<?php

include_once ("lib/stopwatch.inc");

echo ("Start Initialization<br>");
set_time_limit(0);

$stopwatch = new stopwatch;

$num = updateStudentLevelProgress();


$stopwatch->lap("ran updateStudentLevelProgress() => [$num]");

echo ("Start updateGradeNum<br>");

//$num = updateGradeNum();

$stopwatch->lap("ran updateGradeNum() => [$num]");

echo ("Timing: " . $stopwatch->getText());

?>
