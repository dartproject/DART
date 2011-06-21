<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$year = $_POST['year'];
$test = $_POST['test'];
$area = $_POST['area'];
$grp = $_POST['grp'];
$name = $_POST['name'];


echo ("Please wait while your review of $repname is being recorded<br>");
$sid = createTeacherSipNew($year, $test, $area, $grp, $name);
echo ("Thank You");

echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=teachersip&module=sip&sid=$sid\">");

?>