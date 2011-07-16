<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified by: Bolek Kurowski (bkurowsk@andrew.cmu.edu
//  Last Modification: 6/20/2011
//  Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

require_once('lib\Smarty\libs\Smarty.class.php');

$config = parse_ini_file('config/config.ini');

$expireTime = 1200; // in seconds
$color1 = $config['color1'];
$color2 = $config['color2'];
$width = $config['width'];

//Datetime Settings
$dateSettings = $config['DATE_TIME_FORMAT'];

$timezone = $config['TIMEZONE'];

//Email
$dartEmail = $config['CONTACT_EMAIL'];


//Modules
$modules = $config['MODULES'];

//Smarty Setup
$smarty = new Smarty();
$smarty->setTemplateDir($rootPATH . 'smarty/templates');
$smarty->setCompileDir($rootPATH . 'smarty/templates_c');
$smarty->setCacheDir($rootPATH . 'smarty/cache');
$smarty->setConfigDir($rootPATH . 'smarty/configs');
$smarty->plugins_dir[]='smarty/plugins';

//To check Smarty setup uncomment
//$smarty->testInstall();
?>
