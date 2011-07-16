<?php

$config = parse_ini_file('config/config.ini');

    // location of root url
   //$rootURL = "https://dart.bssd.org";
   $rootURL = $config['ROOT_URL'];
   $rootPATH = dirname(__FILE__) . "/../";
   $imageURL = $rootURL . "/images/";
   $logoURL = $rootURL . "/images/SchoolLogos/";
   $pictureURL = $rootURL . "/images/student/" ;
   $pictDIR = $rootURL . "/images/student/";
   $exportDIR = $rootURL."/exp/";

// Database inforamtion
   $dbuser = $config['DB_USER'];
   //$dbpassword = $config['DB_PASS']; 
   $dbname = $config['DB_NAME'];
   
   $dbhose = $config['DB_HOST'];

// pdftk
	$pdftk = '/usr/bin/pdftk';
?>
