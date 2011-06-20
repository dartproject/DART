<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

     require_once('Smarty.class.php');
	 
	 $expireTime = 1200; // in seconds
     $color1 =  "#FFFFCC";
     $color2 =  "WHITE";
     $width = 9;
     $dateSettings = 'm/d/y-H:i';
     $dartEmail = "dart@vizmotion.com";
     $modules[0] = "sfa";
     $modules[1] = "sip";
     $modules[2] = "sped";
     $modules[3] = "testing";
	 
	 $smarty = new Smarty();
	 $smarty->setTemplateDir($rootPATH.'/smarty/templates');
	 $smarty->setCompileDir($rootPATH.'/smarty/templates_c');
	 $smarty->setCacheDir($rootPATH.'/smarty/cache');
	 $smarty->setConfigDir($rootPATH.'/smarty/configs');
	 
	 $smarty->testInstall();

?>
