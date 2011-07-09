<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$user = getUserInfo ($currentUserID);
$currentpwd = $user['pwd'];
$oldpwd = $_POST['oldpwd'];
$pwd1 = $_POST['pwd1'];
$pwd2 = $_POST['pwd2'];

$msg = "";

if(($pwd1 != $pwd2) and ($pwd1 != "")) {
  $msg .= "Error with passwords. Not matching.<br>";
}
if(!checkHash($oldpwd, $currentpwd)) {
    $msg .= "Old password incorrect<br>";
}

debugPrint ("<br>CurrentPWd=$currentpwd; OldPwd=$oldpwd; PWD1=$pwd1; PFD2=$pwd2;<br>");


if ($msg == "") {
      saveUserInfo($currentUserID, 'pwd', getHash($pwd1));
      echo "<script>alert(\"Your password has been updated.\")</script>";
      echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=home\">");
    } else {
      echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editProfile&msg=$msg\">");
   }

?>
