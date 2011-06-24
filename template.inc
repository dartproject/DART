<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified by: Bolek Kurowski (bkurowsk@andrew.cmu.edu)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

//if (!isset($title)) {
//    $title = "DART";
//}
// Times arein seconds; 
//$timeout = 3600; Set in js/timeout.js

$smarty->assign('head', $head);
$smarty->assign('js', $js);
$smarty->assign('imageURL', $imageURL);
$smarty->assign('currentUserName', $currentUserName);

include("leftside.inc");

//is smarty template doesn't exist set $body
if ($isSmarty!=true) {
    $smarty->assign('body', $body);
    $smarty->display('layout.tpl');
}
?>