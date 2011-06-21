<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$timeframe = $CurrentYear . "-" . substr($CurrentYear+1, 2, 2);

$sip = $db->get_row("select * from sip, sipaux where kind='district' and year = '$CurrentYear' and id = sid ");
while (list($var, $val) = each($sip) ) ${$var} = $val;

$actionReadings = $db->get_results("select * from sipaction where sid = '$sid' and area = 'r' ", ARRAY_A);
foreach($actionReadings as $act1) {
	while (list($var, $val) = each($act1) ) ${$var} = $val;
	$actionR .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
}

$actionWriting = $db->get_results("select * from sipaction where sid = '$sid' and area = 'w' ", ARRAY_A);
foreach($actionWriting as $act2) {
	while (list($var, $val) = each($act2) ) ${$var} = $val;
	$actionW .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
}

$actionMath = $db->get_results("select * from sipaction where sid = '$sid' and area = 'm' ", ARRAY_A);
foreach($actionMath as $act3) {
	while (list($var, $val) = each($act3) ) ${$var} = $val;
	$actionM .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
}

$actionIntervention = $db->get_results("select * from sipaction where sid = '$sid' and area = 'i' ", ARRAY_A);
foreach($actionIntervention as $act4) {
	while (list($var, $val) = each($act4) ) ${$var} = $val;
	$actionI .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
}

$filestr = file_get_contents('districtReportTemplate.html');
$str = "\"" . addslashes($filestr) . "\"";
$str2 = "return($str);";
$body .= eval($str2);

include("template.inc");
?>
