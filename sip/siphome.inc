<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$A15Priv = Privilege(A15);
$A16Priv = Privilege(A16);

$year = ($_GET['year'] == "") ? $CurrentYear : $_GET['year'];

if($A16Priv == 'none') { 
	$teacherGrp = showSipGroups($A16Priv, $currentUserID, $year); 
} else if($A16Priv == 'site') {
	$teacherGrp = showSipGroups($A16Priv, $currentMySite, $year);
} else {
	$teacherGrp = showSipGroups($A16Priv, '', $year); 
}
 

$yearOptions = getSipYearOption($year);

$body = "
<div class=\"notetip\">
Welcome to the BSSD SIP Module.
</div>
<center>
	<form action=index.php method=get>
		<input type=hidden name=cmd value=siphome>
		<input type=hidden name=module value=sip>
		<select name=year onChange='javascript:submit()'>
			$yearOptions
		</select>
	</form>
</center>
<table align=center border=1>
	<tr>
		<td>
			<a href=index.php?module=sip&cmd=scores>Test Scores Analysis Screen</a>
		</td>		
	</tr>";

$body .= ($A16Priv == 'district') ? "
	<tr>
		<td>
			<a href=index.php?module=sip&cmd=districtsip>District SIP<a>
		</td>		
	</tr>" :
	"";
echo $A16Priv;	
$body .= ($A16Priv <> 'none') ?
 	"<tr>
		<td>
			<a href=index.php?module=sip&cmd=sitesip&site=$currentMySite>Site SIP [$currentMySite]<a>
		</td>		
	</tr>" : "";
	
$body .= ($A16Priv <> 'none') ?
 	"<tr>
		<td>
			<a href=index.php?cmd=siterep>Display Site Sips <a>
		</td>		
	</tr>" : "";
	
$body .= "
	<tr>
		<td>
			<a href=index.php?module=sip&cmd=staterep>State Report Input Screen<a>
		</td>		
	</tr>";
	
$body .= ($A15Priv <> 'none') ?
	"<tr>
		<td>
			<a href=index.php?module=sip&cmd=overallsip>Overall Disctrict/Sites Reports<a>
		</td>		
	</tr>" : "";

$body .= "
	<tr>
		<td>
			<a href=index.php?module=sip&cmd=createsip>Create Individual Sip<a>
		</td>		
	</tr>
</table>

$teacherGrp";

include_once ("template.inc");


?>

