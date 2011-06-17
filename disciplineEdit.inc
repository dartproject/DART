<?php

include_once ("lib/function_discipline.inc");
//echo "HERE" . $_POST['gobutton']. "--<br>";
//print_r($HTTP_POST_VARS);
if($_POST['gobutton'] != "") {
	saveDiscipline($_POST);
}
	
$dispID = $_GET['disciplineid'];
$disp = getDisciplineData($dispID);
//print_r ($disp);
while(list($var, $value) = each($disp)) {
//echo "$var -$value-, ";
	${$var} = $value;
}

$body = "Edit Discipline: " . $dispID;
$body .= "<br><a href=index.php?cmd=disciplineList&studentid=$studentid>List Discipline</a>";

$logentries = "XX";
$issdays = "XX";
$susdays = "XX";

if($kind == 'regular') {
	$filestr = file_get_contents('disciplineEditRegular.html');
} else {
	$disabilityCode = "XX";
	$filestr = file_get_contents('disciplineEditSped.html');
}

$picture = ($picture != "") ? $picture : "no_photo.jpg";
$picture .= $rootURL."/images/student/". $picture;

$nonweaponSelect = "<select name=\"i_nonweapon\" id=\"nonweapon\">" . 
                       GetOptionList($nonweaponValues, $nonweapon) . 
                       "</select>";
$victimNoSelect = "<select name=\"i_victimno\" id=\"victimno\">" . 
                       GetOptionList($victimNoValues, $victimno) . 
                       "</select>";
$policeSelect = "<select name=\"i_police\" id=\"police\">" . 
                       GetOptionList($policeValues, $police) . 
                       "</select>";
$consequenceSelect = "<select name=\"i_consequence\" id=\"consequence\">" . 
                       GetOptionList($consequenceValues, $consequence) . 
                       "</select>";
$dstatusSelect = "<select name=\"i_dstatus\" id=\"dstatus\">" . 
                       GetOptionList($dstatusValues, $dstatus) . 
                       "</select>";
$lengthSelect = "<select name=\"i_lengthdays\" id=\"lengthdays\">" . 
                       GetOptionList($lengthValues, $lengthdays) . 
                       "</select>";
$weaponSelect = "<select name=\"i_weapon\" id=\"weapon\">" . 
                       GetOptionList($weaponValues, $weapon) . 
                       "</select>";
$victimTypeSelect = "<select name=\"i_victimtype\" id=\"victimtype\">" . 
                       GetOptionList($victimTypeValues, $victimtype) . 
                       "</select>";

$relatedDisabilitySelect =  "<select name=\"i_relateddisability\" id=\"relateddisability\">" . 
                       GetOptionList($relatedDisabilitySelect, $relateddisability) . 
                       "</select>";
		
$IEPMeetSelect =  "<select name=\"i_iepmeet\" id=\"iepmeet\">" . 
                       GetOptionList($IEPMeetSelect, $iepmeet) . 
                       "</select>";
		
$eduServicesSelect =  "<select name=\"i_eduservice\" id=\"eduservice\">" . 
                       GetOptionList($eduServicesSelect, $eduservice) . 
                       "</select>";
                       
$str = "\"" . addslashes($filestr) . "\"";
$str2 = "return($str);";
$body .= eval($str2);

include ("template.inc");

?>
