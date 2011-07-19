<?php

include_once ("lib/function_discipline.inc");

$msg = NULL;
if(getValue($_POST,"gobutton") != NULL) {
	$n_rows = saveDiscipline($_POST);
	if($n_rows == 1) // $n_rows = 0: there was an error or there were no new values to update
		$msg = "Changes saved";
}

$dispID = getValue($_GET,"disciplineid");
$disp = getDisciplineData($dispID);

$logentries = "XX";
$issdays = "XX";
$susdays = "XX";

$spedEd = $disp->kind == 'sped';

if($disp->picture == "") $disp->picture = "no_photo.jpg";

$picture = $rootURL."/images/student/". $disp->picture;

/* *****************************************************************************
 * Get Dictionaries
 * **************************************************************************** */
$non_weaponMenu = Dict::getDict(DictType::DISCIPLINE_NON_WEAPON);
$policeMenu = Dict::getDict(DictType::DISCIPLINE_POLICE);
$consequenceMenu = Dict::getDict(DictType::DISCIPLINE_CONSEQUENCE);
$lengthMenu = Dict::getDict(DictType::DISCIPLINE_LENGTH);
$weaponMenu = Dict::getDict(DictType::DISCIPLINE_WEAPON);
$victimMenu = Dict::getDict(DictType::DISCIPLINE_VICTIM);
$victim_noMenu = Dict::getDict(DictType::DISCIPLINE_VICTIM_NO);
$disabilityMenu = Dict::getDict(DictType::DISCIPLINE_DISABILITY);
$iepMenu = Dict::getDict(DictType::DISCIPLINE_IEP);
$serviceMenu = Dict::getDict(DictType::DISCIPLINE_SERVICE);
$statusMenu = Dict::getDict(DictType::DISCIPLINE_STATUS);

$title = "Discipline Log";

$smarty->assign('pageTitle',$title);
$smarty->assign('imageURL',$imageURL);
$smarty->assign('msg', $msg); 

$smarty->assign('dispID',$dispID);
$smarty->assign('studentid',$disp->studentid);
$smarty->assign('studentname',$disp->studentname);
$smarty->assign('incidentdate',$disp->incidentdate);
$smarty->assign('picture',$picture);
$smarty->assign('guardian',$disp->guardian);
$smarty->assign('startdate',$disp->startdate);
$smarty->assign('enddate',$disp->enddate);
$smarty->assign('notes',$disp->notes);

$smarty->assign('nonweapon', $disp->nonweapon); 
$smarty->assign('victimno', $disp->victimno); 
$smarty->assign('police', $disp->police); 
$smarty->assign('consequence', $disp->consequence); 
$smarty->assign('dstatus', $disp->dstatus); 
$smarty->assign('lengthdays', $disp->lengthdays); 
$smarty->assign('weapon', $disp->weapon); 
$smarty->assign('victimtype', $disp->victimtype); 
$smarty->assign('relateddisability', $disp->relateddisability); 
$smarty->assign('iepmeet', $disp->iepmeet); 
$smarty->assign('eduservice', $disp->eduservice); 

$smarty->assign('nonweaponMenu', $non_weaponMenu);
$smarty->assign('victimnoMenu', $victim_noMenu); 
$smarty->assign('policeMenu', $policeMenu); 
$smarty->assign('consequenceMenu', $consequenceMenu); 
$smarty->assign('statusMenu', $statusMenu); 
$smarty->assign('lengthMenu', $lengthMenu); 
$smarty->assign('weaponMenu', $weaponMenu); 
$smarty->assign('victimMenu', $victimMenu); 
$smarty->assign('disabilityMenu', $disabilityMenu); 
$smarty->assign('iepMenu', $iepMenu); 
$smarty->assign('serviceMenu', $serviceMenu); 
$smarty->assign('spedEd', $spedEd); 

if($spedEd) {
	$smarty->assign('meetdate', $disp->meetdate);
	$smarty->assign('disabilityLabel', "Disability Code:");
	$smarty->assign('disabilityCode', "XX");
	$smarty->assign('logentriesLink', "?cmd=disciplineList&studentid=".$disp->studentid);
	$smarty->assign('logentries',$logentries);
	$smarty->assign('daysAvailableLabel', "Days Available");
	$smarty->assign('daysAvailableNote', "Not more than <b><font color=\"red\">7</font></b>");
	$smarty->assign('issDays', $issdays);
	$smarty->assign('suspensionDays', $susdays);
} else {
	$smarty->assign('logentriesLink', "%28EmptyReference%21%29");
	$smarty->assign('logentries',4);
	$smarty->assign('issDays', "<a href=\"%28EmptyReference%21%29\"> 1 </a>");
	$smarty->assign('suspensionDays', "<a href=\"%28EmptyReference%21%29\"> 3 </a>");
}
//set flag to indicate that smarty template exists for this page

$isSmarty=true;
include ("template.inc");

$smarty->display('disciplineEdit.tpl');

?>
