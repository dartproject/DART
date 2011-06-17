<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$site = $_GET['site'];
$siteList = getSitesOptions($site);
${"siterep_" . $site} = "selected";
$siteSelection = "<form action=index.php method=get>
					<input type=hidden name=cmd value=siterep>
					<select name=\"site\" id=\"site\" onChange=\"submit()\"><option value=''>-select-</option> 
					<option value='SMK' $siterep_SMK>Anthony A. Andrews</option> 
					<option value='WBB' $siterep_WBB>Tukurngailnguq School</option> 
					<option value='SHH' $siterep_SHH>Shishmaref School</option> 
					<option value='ELI' $siterep_ELI>Aniguiin School</option> 
					<option value='KKA' $siterep_KKA>Koyuk-Malemute School</option> 
					<option value='SVA' $siterep_SVA>Hogarth Kingeekuk Memorial School</option> 
					<option value='GAM' $siterep_GAM>Gambell School</option>
					<option value='DIO' $siterep_DIO>Diomede School</option>
					</select>
				 </form>";

$sip = $db->get_row("select * from sip, sipaux where kind='site' and year = '$CurrentYear' and id = sid and sip.site = '$site' ");
while (list($var, $val) = each($sip) ) ${$var} = $val;

$actionReadings = $db->get_results("select * from sipaction where sid = '$sid' and area = 'r' ", ARRAY_A);
foreach($actionReadings as $act1) {
	while (list($var, $val) = each($act1) ) ${$var} = $val;
	$actionR .= "<tr><td>$action</td><td>$person</td><td>$ptype</td><td>$timeline</td><td>$eval</td><td>$final</td></tr>";
}

$actionWriting = $db->get_results("select * from sipaction where sid = '$sid' and area = 'w' ", ARRAY_A);
foreach($actionWriting as $act2) {
	while (list($var, $val) = each($act2) ) ${$var} = $val;
	$actionW .= "<tr><td>$action</td><td>$person</td><td>$ptype</td><td>$timeline</td><td>$eval</td><td>$final</td></tr>";
}

$actionMath = $db->get_results("select * from sipaction where sid = '$sid' and area = 'm' ", ARRAY_A);
foreach($actionMath as $act3) {
	while (list($var, $val) = each($act3) ) ${$var} = $val;
	$actionM .= "<tr><td>$action</td><td>$person</td><td>$ptype</td><td>$timeline</td><td>$eval</td><td>$final</td></tr>";
}

$actionIntervention = $db->get_results("select * from sipaction where sid = '$sid' and area = 'i' ", ARRAY_A);
foreach($actionIntervention as $act4) {
	while (list($var, $val) = each($act4) ) ${$var} = $val;
	$actionI .= "<tr><td>$action</td><td>$person</td><td>$ptype</td><td>$timeline</td><td>$eval</td><td>$final</td></tr>";
}

$filestr = file_get_contents('siteReportTemplate.html');
$str = "\"" . addslashes($filestr) . "\"";
$str2 = "return($str);";
$body .= eval($str2);

include("template.inc");
?>
