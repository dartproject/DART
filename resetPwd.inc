<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified by: Bolek Kurowski (bkurowsk@andrew.cmu.edu)
//  Last Modification: 6/20/2011
//  Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$code = getValue($_GET, "code");
$username = NULL;

$sql = "SELECT id, userid FROM pwd_recovery where code='$code'";
$res = $db->get_row($sql);
if($res == NULL) {
	$msg = "Code not found. Check you copied the link correctly.";
} else {
	$userid = $res->userid;
	$request_id = $res->id;
	if(getValue($_POST,"Update") != NULL) { // POST request
		$new_pwd = getValue($_POST, "pwd1");
		$new_pwd_2 = getValue($_POST, "pwd2");
		if($new_pwd == NULL) {
			$msg = "You have to type your new password.";
		} else if($new_pwd_2 == NULL) {
			$msg = "You have to retype your new password.";
		} else if($new_pwd != $new_pwd_2) {
			$msg = "Passwords not matching.";
		} else {
      		saveUserInfo($userid, 'pwd', getHash($new_pwd));
			$db->get_results("DELETE FROM pwd_recovery WHERE id = '$request_id'");
      		echo "<script>alert(\"Your new password has been saved.\")</script>";
      		echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=home\">");
		}
	} else {
		$msg = "Enter your new password.";
	}
	$sql = "SELECT name FROM user WHERE userid='$userid'";
	$res = $db->get_row($sql);
	$username = $res->name;
}
$smarty->assign('msg', $msg);
$smarty->assign('username', $username);
$smarty->assign('imageURL', $imageURL);

$smarty->display('resetPwd.tpl');
?>
