<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$subject = getValue($_GET, "subject");
$level = getValue($_GET,"level");

$msg = NULL;
if(getValue($_POST,"button") != NULL) {
	$msg = "Values are saved";
	$shortname = getValue($_POST, "shortname");
	$sval = getValue($_POST, "subject");
	$type = getValue($_POST, "type");
	$slevel = getValue($_POST, "level");
	$std = getValue($_POST, "std");
	$link = getValue($_POST, "link");
	$description = getValue($_POST, "description");
	$ident = getValue($_POST, "id");
	$order = getValue($_POST, "ord");
	for($i=0; $i < count($ident) ; $i++) {
		$id = $ident[$i];
		$sn =  $shortname[$i];
		$desc =  $description[$i];
		$lk =  $link[$i];
		$sub = $sval[$i];
		$lev = $slevel[$i];
		$ty = $type[$i];
		$sd = $std[$i];
		$ord = $order[$i];

		$sql = "UPDATE standards set standards.order = '$ord', shortname = '$sn', description = '$desc', link = '$lk', type='$ty'
				where subject = '$sub' and level = '$lev' and std='$sd'";
		$db->query($sql);
	}
	$update = "UPDATE standards SET description = REPLACE(REPLACE(REPLACE(description, '\r', ''), '\n', ''), '\\\\', '')";
	$db->query($update);

}

$sql = "SELECT DISTINCT(level) AS level FROM level ORDER BY level";
$results = $db->get_results($sql, ARRAY_A);
$levelMenu = array();
foreach($results as $row) {
	$levelMenu[$row['level']] = $row['level'];
}
$sql = "SELECT DISTINCT(subject) AS subject FROM level ORDER BY subject";
$results = $db->get_results($sql, ARRAY_A);
$subjectMenu = array();
foreach($results as $row) {
	$subjectMenu[$row['subject']] = $row['subject'];
}

$standards = $db->get_results("select * from standards where subject = '$subject' and level = '$level' ORDER BY `standards`.`order` ASC  ");

$s = 20;
$c = 30;
$r = 4;

$typeMenu = array("std" => "Std", "QPI" => "QPI", "over" => "Over");

$title = "Standards";

$smarty->assign('pageTitle',$title);
$smarty->assign('msg',$msg);
$smarty->assign('levelMenu',$levelMenu);
$smarty->assign('subjectMenu',$subjectMenu);
$smarty->assign('subject',$subject);
$smarty->assign('level',$level);
$smarty->assign('standards',$standards);
$smarty->assign('typeMenu',$typeMenu);
$smarty->assign('s',$s);
$smarty->assign('c',$c);
$smarty->assign('r',$r);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('editStandards.tpl');

?>
