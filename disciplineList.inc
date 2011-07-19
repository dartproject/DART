<?php

$studentid = getValue($_GET, "studentid");
$year = getValue($_GET, "year", $CurrentYear);

$res = $db->get_row("SELECT fname, lname FROM student WHERE studentid = '$studentid'");
if($res != NULL) $name = $res->fname." ".$res->lname;

$title = "Discipline List";

$smarty->assign('pageTitle',$title);
$smarty->assign('studentid',$studentid);
$smarty->assign('name',$name);
$smarty->assign('year',$year);
$smarty->assign('imageURL',$imageURL);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('disciplineList.tpl');

?>
