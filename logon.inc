<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified by: Bolek Kurowski (bkurowsk@andrew.cmu.edu)
//  Last Modification: 6/20/2011
//  Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


if (isset($_GET['msg']))
    $smarty->assign('msg', $_GET['msg']);
$smarty->assign('imageURL', $imageURL);

$smarty->display('logon.tpl');
?>