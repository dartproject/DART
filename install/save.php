<?php

// $Id: save.php 807 2008-04-05 19:24:10Z Ruebenwurzel $

/*

 Website Baker Project <http://www.websitebaker.org/>
 Copyright (C) 2004-2008, Ryan Djurovich

 Website Baker is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Website Baker is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Website Baker; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/
include_once ("../lib/PasswordHash.php");
// Start a session
if(!defined('SESSION_STARTED')) {
	session_name('dart_session_id');
	session_start();
	define('SESSION_STARTED', true);
}
// get random-part for session_name()
list($usec,$sec) = explode(' ',microtime());
srand((float)$sec+((float)$usec*100000));
$session_rand = rand(1000,9999);

// Function to set error
function set_error($message, $field_name = '') {
	global $_POST;
	if(isset($message) AND $message != '') {
		// Copy values entered into session so user doesn't have to re-enter everything
		if(isset($_POST['website_url'])) {
			$_SESSION['database_host'] = $_POST['database_host'];
			$_SESSION['database_username'] = $_POST['database_username'];
			$_SESSION['database_password'] = $_POST['database_password'];
			$_SESSION['database_name'] = $_POST['database_name'];
			$_SESSION['install_tables'] = false;
			$_SESSION['install_demo'] = false;
			if(isset($_POST['install'])) {
				switch($_POST['install']) {
					case 'tables': $_SESSION['install_tables'] = true; break;
					case 'demo': $_SESSION['install_demo'] = true; break;
				}
			}
			$_SESSION['website_url'] = $_POST['website_url'];
			$_SESSION['admin_username'] = $_POST['admin_username'];
			$_SESSION['admin_email'] = $_POST['admin_email'];
			$_SESSION['admin_password'] = $_POST['admin_password'];
			$_SESSION['admin_repassword'] = $_POST['admin_repassword'];
			$_SESSION['district_name'] = $_POST['district_name'];
			$_SESSION['district_slogan'] = $_POST['district_slogan'];
			$_SESSION['district_contact'] = $_POST['district_contact'];
		}
		// Set the message
		$_SESSION['message'] = $message;
		// Set the element(s) to highlight
		if($field_name != '') {
			$_SESSION['ERROR_FIELD'] = $field_name;
		}
		// Specify that session support is enabled
		$_SESSION['session_support'] = '<font class="good">Enabled</font>';
		// Redirect to first page again and exit
//		exit();
		header('Location: index.php?sessions_checked=true');
		exit();
	}
}

// Dummy class to allow modules' install scripts to call $admin->print_error
class admin_dummy
{
	var $error='';
	function print_error($message)
	{
		$this->error=$message;
	}
}

// Function to workout what the default permissions are for files created by the webserver
function default_file_mode($temp_dir) {
	$v = explode(".",PHP_VERSION);
	$v = $v[0].$v[1];
	if($v > 41 AND is_writable($temp_dir)) {
		$filename = $temp_dir.'/test_permissions.txt';
		$handle = fopen($filename, 'w');
		fwrite($handle, 'This file is to get the default file permissions');
		fclose($handle);
		$default_file_mode = '0'.substr(sprintf('%o', fileperms($filename)), -3);
		unlink($filename);
	} else {
		$default_file_mode = '0777';
	}
	return $default_file_mode;
}

// Function to workout what the default permissions are for directories created by the webserver
function default_dir_mode($temp_dir) {
	$v = explode(".",PHP_VERSION);
	$v = $v[0].$v[1];
	if($v > 41 AND is_writable($temp_dir)) {
		$dirname = $temp_dir.'/test_permissions/';
		mkdir($dirname);
		$default_dir_mode = '0'.substr(sprintf('%o', fileperms($dirname)), -3);
		rmdir($dirname);
	} else {
		$default_dir_mode = '0777';
	}
	return $default_dir_mode;
}

function add_slashes($input) {
		if ( get_magic_quotes_gpc() || ( !is_string($input) ) ) {
			return $input;
		}
		$output = addslashes($input);
		return $output;
	}

// Begin check to see if form was even submitted
// Set error if no post vars found
if(!isset($_POST['website_url'])) {
	set_error('Please fill-in the form below');
}
// End check to see if form was even submitted

// Set error if no post vars found
if(!isset($_POST['website_url']) OR $_POST['website_url'] == '') {
	set_error('Please enter base URL', 'website_url');
} else {
	$website_url = $_POST['website_url'];
}

// End check to see if form was even submitted

// Begin database details code
// Check if user has entered a database host
if(!isset($_POST['database_host']) OR $_POST['database_host'] == '') {
	set_error('Please enter a database host name', 'database_host');
} else {
	$database_host = $_POST['database_host'];
}
// Check if user has entered a database username
if(!isset($_POST['database_username']) OR $_POST['database_username'] == '') {
	set_error('Please enter a database username','database_username');
} else {
	$database_username = $_POST['database_username'];
}
// Check if user has entered a database password
if(!isset($_POST['database_password'])) {
	set_error('Please enter a database password', 'database_password');
} else {
	$database_password = $_POST['database_password'];
}
// Check if user has entered a database name
if(!isset($_POST['database_name']) OR $_POST['database_name'] == '') {
	set_error('Please enter a database name', 'database_name');
} else {
	// make sure only allowed characters are specified
	if(preg_match('/[^a-z0-9_-]+/i', $_POST['database_name'])) {
		// contains invalid characters (only a-z, A-Z, 0-9 and _ allowed to avoid problems with table/field names)
		set_error('Only characters a-z, A-Z, 0-9, - and _ allowed in database name.', 'database_name');
	}
	$database_name = $_POST['database_name'];
}

// Find out what installation the user wants
$install_tables = false;
$install_demo = false;
if(isset($_POST['install'])) {
	switch($_POST['install']) {
		case 'tables': $install_tables = true; break;
		case 'demo': $install_demo = true; break;
	}
}


// End database details code

// Begin admin user details code
// Get admin username
if(!isset($_POST['admin_username']) OR $_POST['admin_username'] == '') {
	set_error('Please enter a username for the Administrator account','admin_username');
} else {
	$admin_username = $_POST['admin_username'];
}
// Get admin email and validate it
if(!isset($_POST['admin_email']) OR $_POST['admin_email'] == '') {
	set_error('Please enter an email for the Administrator account','admin_email');
} else {
	if(eregi("^([0-9a-zA-Z]+[-._+&])*[0-9a-zA-Z]+@([-0-9a-zA-Z]+[.])+[a-zA-Z]{2,6}$", $_POST['admin_email'])) {
		$admin_email = $_POST['admin_email'];
	} else {
		set_error('Please enter a valid email address for the Administrator account','admin_email');
	}
}
// Get the two admin passwords entered, and check that they match
if(!isset($_POST['admin_password']) OR $_POST['admin_password'] == '') {
	set_error('Please enter a password for the Administrator account','admin_password');
} else {
	$admin_password = $_POST['admin_password'];
}
if(!isset($_POST['admin_repassword']) OR $_POST['admin_repassword'] == '') {
	set_error('Please make sure you re-enter the password for the Administrator account','admin_repassword');
} else {
	$admin_repassword = $_POST['admin_repassword'];
}
if($admin_password != $admin_repassword) {
	set_error('Sorry, the two Administrator account passwords you entered do not match','admin_repassword');
}
// End admin user details code

// Begin district info code
// Get district name
if(!isset($_POST['district_name']) OR $_POST['district_name'] == '') {
	set_error('Please enter a name for the school district','district_name');
} else {
	$district_name = $_POST['district_name'];
}
// Get district slogan
if(!isset($_POST['district_slogan'])) {
	$_POST['district_slogan'] = "";
} else {
	$district_slogan = $_POST['district_slogan'];
}
// Get district contact email
if(!isset($_POST['district_contact']) OR $_POST['district_contact'] == '') {
	set_error('Please enter a contact email that will be displayed in the website','district_contact');
} else {
	if(eregi("^([0-9a-zA-Z]+[-._+&])*[0-9a-zA-Z]+@([-0-9a-zA-Z]+[.])+[a-zA-Z]{2,6}$", $_POST['district_contact'])) {
		$district_contact = $_POST['district_contact'];
	} else {
		set_error('Please enter a contact email that will be displayed in the website','district_contact');
	}
}
// End district info code

$path = str_replace(array('/install','\install'), '',dirname(__FILE__));
// Try and write settings to config file
$config_content = <<<END
; This is the main configuration file for DART

;Server configuration

;URL of the server where the site is hosted
ROOT_URL = $website_url
;Path of www folder
ROOT_PATH = $path
;Path of pdftk
PDFTK_PATH = /usr/bin/pdftk

;*******************************************************************************
;********** Database configuration *********************************************
;*******************************************************************************
;Database username
DB_USER = $database_username
;Database password
DB_PASS = $database_password

DB_NAME = $database_name
;Database host - address where the database server resides
DB_HOST = $database_host

;*******************************************************************************
;********* Date/time settings **************************************************
;*******************************************************************************
DATE_TIME_FORMAT = m/d/y-H:i
TIMEZONE = US/Alaska

;*******************************************************************************
;******** Used Modules *********************************************************
;*******************************************************************************

;Comment if you do not want to use a specific module
MODULES[] = sfa
MODULES[] = sip
MODULES[] = sped
MODULES[] = testing

;*******************************************************************************
;**************** District Settings ********************************************
;*******************************************************************************
DISTRICT_NAME = "$district_name"
DISTRICT_PHRASE = "$district_slogan"

CONTACT_EMAIL = $district_contact
;*******************************************************************************
;*************** Administration email settings *********************************
;*******************************************************************************
SMTP_SERVER = smtp.gmail.com
SMTP_PORT = 465
; Y or N
SMTP_SSL = Y
SMTP_USERNAME = YOUR@EMAIL.ADDRESS.com
SMTP_PASSWORD = PASS

;*******************************************************************************
;*********** Student Enrollment form settings **********************************
;*******************************************************************************
SEF_Recipient_Email = admin@bssd.org
SEF_Recipient_Name = Administrator

; Old version parameters that should be removed in the future
color1 = #FFFFCC
color2 = WHITE
width = 9
END;

$config_filename = '../config/config.ini';

// Check if the file exists and is writable first.
if(!$handle = fopen($config_filename, 'w')) {
		set_error("Cannot open the configuration file ($config_filename)");
} else {
	if (fwrite($handle, $config_content) === FALSE) {
		set_error("Cannot write to the configuration file ($config_filename)");
	}
	// Close file
	fclose($handle);
}

// Define configuration vars
define('DB_TYPE', 'mysql');
define('DB_HOST', $database_host);
define('DB_USERNAME', $database_username);
define('DB_PASSWORD', $database_password);
define('DB_NAME', $database_name);
define('WB_PATH', $path);
define('WB_URL', $website_url);

// Try connecting to database	
$db = mysql_connect (DB_HOST, DB_USERNAME, DB_PASSWORD);
if(!$db) {
	set_error('Database host name, username and/or password incorrect. MySQL Error:<br />'.mysql_error());
}

if(!mysql_select_db($database_name, $db)) {
	set_error('Database name incorrect. MySQL Error:<br />'.mysql_error());
}

$queries = array();
if($install_tables) {
	
	$filename = "core.sql";
	$fp = fopen($filename, 'r');
	if($fp) {
		$queries = fread($fp, filesize($filename));
		$queries = explode(";\n",$queries);
	
		$hasher = new PasswordHash(8, FALSE);
		$hash = $hasher->HashPassword($admin_password);
	
		$queries[] = "INSERT INTO `user` set user='$admin_username', pwd='$hash', privilegeA='1073741822', privilegeB='1073741822', scopeA='1073741822', scopeB='1073741822', name='Administrator', status='Active', email='$admin_email', site='Admin', type='Administrator', homeroom='X', reading='X'";
	} else {
		set_error('Error loading file core.sql');
	}
	
} else if($install_demo) {
	$filename = "sample.sql";
	$fp = @fopen($filename, 'r');
	if($fp) {
		$queries = fread($fp, filesize($filename));
		$queries = explode(";\n",$queries);
	} else {
		set_error('Sample database not found, please download the file from --- and save it in '.dirname(__FILE__));
	}
}

// Install database
foreach ($queries as $q) {
	mysql_query($q);
}
mysql_close();

header('Location: ../index.php?msg=Installation complete now login');

?>
