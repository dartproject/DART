<?php

// $Id: index.php 811 2008-04-07 17:23:11Z thorn $

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

// Start a session
if(!defined('SESSION_STARTED')) {
	session_name('dart_session_id');
	session_start();
	define('SESSION_STARTED', true);
}

if(isset($_GET['reset']) && $_GET['reset'] != '') {
	session_destroy();
	header('Location: index.php');

}

// Function to highlight input fields which contain wrong/missing data
function field_error($field_name='') {
	if(!defined('SESSION_STARTED') || $field_name == '') return;
	if(isset($_SESSION['ERROR_FIELD']) && $_SESSION['ERROR_FIELD'] == $field_name) {
		return ' class="wrong"';
	}
}
/*
// Check if the page has been reloaded
if(!isset($_GET['sessions_checked']) OR $_GET['sessions_checked'] != 'true') {
	// Set session variable
	$_SESSION['session_support'] = '<font class="good">Enabled</font>';
	// Reload page
	header('Location: index.php?sessions_checked=true');
	exit(0);
} else {
	// Check if session variable has been saved after reload
	if(isset($_SESSION['session_support'])) {
		$session_support = $_SESSION['session_support'];
	} else {   
		$session_support = '<font class="bad">Disabled</font>';
	}
}

// Check if AddDefaultCharset is set
$e_adc=false;
$sapi=php_sapi_name();
if(strpos($sapi, 'apache')!==FALSE || strpos($sapi, 'nsapi')!==FALSE) {
	flush();
	$apache_rheaders=apache_response_headers();
	foreach($apache_rheaders AS $h) {
		if(strpos($h, 'html; charset')!==FALSE) {
			preg_match('/charset\s*=\s*([a-zA-Z0-9- _]+)/', $h, $match);
			$apache_charset=$match[1];
			$e_adc=$apache_charset;
		}
	}
}
*/
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title>DART Installation Wizard</title>
<link href="stylesheet.css" rel="stylesheet" type="text/css">
<script language="javascript" type="text/javascript">

function confirm_link(message, url) {
	if(confirm(message)) location.href = url;
}
function change_os(type) {
	if(type == 'linux') {
		document.getElementById('operating_system_linux').checked = true;
		document.getElementById('operating_system_windows').checked = false;
		document.getElementById('file_perms_box').style.display = 'block';
	} else if(type == 'windows') {
		document.getElementById('operating_system_linux').checked = false;
		document.getElementById('operating_system_windows').checked = true;
		document.getElementById('file_perms_box').style.display = 'none';
	}
}

</script>
</head>
<body>

<table cellpadding="0" cellspacing="0" border="0" width="750" align="center">
<tr>
	<td width="60" valign="top">
		<img src="../images/dart1.gif" alt="Logo" />
	</td>
	<td width="5">&nbsp;</td>
	<td style="font-size: 20px;">
		<font style="color: #FFF;">Installation Wizard</font>
	</td>
</tr>
</table>

<form name="dart_installation_wizard" action="save.php" method="post">

<table cellpadding="0" cellspacing="0" border="0" width="750" align="center" style="margin-top: 10px;">
<tr>
	<td class="content">
	
		<center style="padding: 5px;">
			Welcome to the Dart Installation Wizard.
		</center>
		
		<?php
		if(isset($_SESSION['message']) AND $_SESSION['message'] != '') {
			?><div style="width: 700px; padding: 10px; margin-bottom: 5px; border: 1px solid #FF0000; background-color: #FFDBDB;"><b>Error:</b> <?php echo $_SESSION['message']; ?></div><?php
		}
		?>
		<table cellpadding="5" cellspacing="0" width="100%" align="center">
		<tr>
			<td colspan="3"><h1>Location</h1>Please enter the URL below...</td>
		</tr>		<tr>
			<td style="color: #666666;" colspan="1">Website URL:</td>
			<td colspan="4">
				<input <?php echo field_error('website_url');?> type="text" tabindex="6" name="website_url" style="width: 99%;" value="<?php if(isset($_SESSION['website_url'])) { echo $_SESSION['website_url']; } else { echo str_replace("/install/index.php", '', "http://" . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF']) ; } ?>" />
			</td>
		</tr>

		<tr>
			<td colspan="3"><h1>Database Setup</h1>Please enter your MySQL database server details below...</td>
		</tr>
		<tr>
			<td width="120" style="color: #666666;">Host Name:</td>
			<td width="230">
				<input <?php echo field_error('database_host');?> type="text" tabindex="7" name="database_host" style="width: 98%;" value="<?php if(isset($_SESSION['database_host'])) { echo $_SESSION['database_host']; } else { echo 'localhost'; } ?>" />
			</td>
			<td width="7">&nbsp;</td>
			<td width="70" style="color: #666666;">Username:</td>
			<td>
				<input <?php echo field_error('database_username');?> type="text" tabindex="9" name="database_username" style="width: 98%;" value="<?php if(isset($_SESSION['database_username'])) { echo $_SESSION['database_username']; } else { echo 'root'; } ?>" />
			</td>
		</tr>
		<tr>
			<td style="color: #666666;">Database Name:<br />[a-zA-Z0-9_-]</td>
			<td>
				<input <?php echo field_error('database_name');?> type="text" tabindex="8" name="database_name" style="width: 98%;" value="<?php if(isset($_SESSION['database_name'])) { echo $_SESSION['database_name']; } else { echo 'dart'; } ?>" />
			</td>
			<td>&nbsp;</td>
			<td style="color: #666666;">Password:</td>
			<td>
				<input type="password" tabindex="10" name="database_password" style="width: 98%;"<?php if(isset($_SESSION['database_password'])) { echo ' value = "'.$_SESSION['database_password'].'"'; } ?> />
			</td>
		</tr>

		<tr>
			<td colspan="5"><h1>Installation Setup</h1>Please choose the type of installation you want</td>
		</tr>
		<tr>
			<td colspan="3">
				<input type="radio" tabindex="12" name="install" id="install_tables" value="tables" <?php if(!isset($_SESSION['install_tables'])){ echo 'checked="checked"'; } elseif($_SESSION['install_tables']) { echo 'cheked="checked"'; } ?> />
				<label for="install_tables" style="color: #666666;">Standard Installation</label>
				<br />
				<span style="font-size: 10px; color: #666666;">(This will remove existing tables and data)</span>
			</td>
			<td colspan="2">&nbsp;</td>
		</tr>
		<tr>
			<td colspan="3">
				<input type="radio" tabindex="13" name="install" id="install_demo" value="demo" <?php if(isset($_SESSION['install_demo']) && $_SESSION['install_demo']) { echo 'checked="checked"'; } ?> />
				<label for="install_demo" style="color: #666666;">Demo Installation</label>
				<br />
				<span style="font-size: 10px; color: #666666;">(Test the system with sample data. This may be a slow process.)</span>
			</td>
			<td colspan="2">&nbsp;</td>
		</tr>
		<tr>
			<td colspan="5"><h1>Administration Information</h1>Please enter your Administrator account details for Dart below...</td>
		</tr>
		<tr>
			<td style="color: #666666;">Username:</td>
			<td>
				<input <?php echo field_error('admin_username');?> type="text" tabindex="15" name="admin_username" style="width: 98%;" value="<?php if(isset($_SESSION['admin_username'])) { echo $_SESSION['admin_username']; } else { echo 'admin'; } ?>" />
			</td>
			<td>&nbsp;</td>
			<td style="color: #666666;">Password:</td>
			<td>
				<input <?php echo field_error('admin_password');?> type="password" tabindex="17" name="admin_password" style="width: 98%;"<?php if(isset($_SESSION['admin_password'])) { echo ' value = "'.$_SESSION['admin_password'].'"'; } ?> />
			</td>
		</tr>
		<tr>
			<td style="color: #666666;">Email:</td>
			<td>
				<input <?php echo field_error('admin_email');?> type="text" tabindex="16" name="admin_email" style="width: 98%;"<?php if(isset($_SESSION['admin_email'])) { echo ' value = "'.$_SESSION['admin_email'].'"'; } ?> />
			</td>
			<td>&nbsp;</td>
			<td style="color: #666666;">Re-Password:</td>
			<td>
				<input <?php echo field_error('admin_repassword');?> type="password" tabindex="18" name="admin_repassword" style="width: 98%;"<?php if(isset($_SESSION['admin_repassword'])) { echo ' value = "'.$_SESSION['admin_repassword'].'"'; } ?> />
			</td>
		</tr>
		<!-- Start District Info -->
		<tr>
			<td colspan="3"><h1>District School Information</h1></td>
		</tr>
		<tr>
			<td width="120" style="color: #666666;">District Name:</td>
			<td width="230">
				<input <?php echo field_error('district_name');?> type="text" tabindex="19" name="district_name" style="width: 98%;" value="<?php if(isset($_SESSION['district_name'])) { echo $_SESSION['district_name']; } ?>" />
			</td>
			<td width="7">&nbsp;</td>
			<td width="70" style="color: #666666;">Slogan:</td>
			<td>
				<input <?php echo field_error('district_slogan');?> type="text" tabindex="21" name="district_slogan" style="width: 98%;" value="<?php if(isset($_SESSION['district_slogan'])) { echo $_SESSION['district_slogan']; } ?>" />
			</td>
		</tr>
		<tr>
			<td width="120" style="color: #666666;">Contact Email:</td>
			<td width="230">
				<input <?php echo field_error('district_contact');?> type="text" tabindex="20" name="district_contact" style="width: 98%;" value="<?php if(isset($_SESSION['district_contact'])) { echo $_SESSION['district_contact']; } ?>" />
			</td>
			<td width="7">&nbsp;</td>
			<td width="70" style="color: #666666;">&nbsp;</td>
			<td>&nbsp;</td>
		</tr>
		<!-- End District Info -->
		<tr>
			<td colspan="5" style="padding: 10px; padding-bottom: 0;"><h1 style="font-size: 0px;">&nbsp;</h1></td>
		</tr>
		<tr>
			<td colspan="4">
				<table cellpadding="0" cellspacing="0" width="100%" border="0">
				<tr valign="top">
					<td>Please note: &nbsp;</td>
					<td>
						Dart is released under the 
						<a href="http://creativecommons.org/licenses/GPL/2.0/" target="_blank">GNU Public License</a>
						<br />
						By clicking install, you are accepting the license.
					</td>
				</tr>
				</table>
			</td>
			<td colspan="1" align="right">
				<input type="submit" tabindex="30" name="submit" value="Install Dart" class="submit" />
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

</form>

<table cellpadding="0" cellspacing="0" border="0" width="100%" style="padding: 10px 0px 10px 0px;">
<tr>
	<td align="center" style="font-size: 10px;">
		<!-- Please note: the below reference to the GNU GPL should not be removed, as it provides a link for users to read about warranty, etc. -->
		Dart is	released under the
		<a href="http://creativecommons.org/licenses/GPL/2.0/" style="color: #000000;" target="_blank">GNU Public License</a>
		<!-- Please note: the above reference to the GNU GPL should not be removed, as it provides a link for users to read about warranty, etc. -->
	</td>
</tr>
</table>

</body>
</html>
