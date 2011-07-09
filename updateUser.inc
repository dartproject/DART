<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$id = $_POST['id'];
$name = $_POST['name'];
$user = $_POST['user'];
$email = $_POST['email'];
$type = $_POST['type'];
$site = $_POST['site'];
$status = $_POST['status'];
$psswd1 = $_POST['password1'];
$psswd2 = $_POST['password2'];
$homeroom = $_POST['homeroom'];
$reading = $_POST['reading'];
$tutor = $_POST['tutor'];

$org_name = $_POST['org_name'];
$org_user = $_POST['org_user'];
$org_email = $_POST['org_email'];
$org_type = $_POST['org_type'];
$org_site = $_POST['org_site'];
$org_status = $_POST['org_status'];

$mod = $_POST['mod'];

$msg = "";
$userInfo = getUserNameInfo($user);
//$msg = print_r($userInfo, true);

if($psswd1 != $psswd2) {
  $msg .= "Error with passwords. Not matching.<br>";
}
if($user == "") {
    $msg .= "Users must have a user name<br>";
}
if($mod == "New") {
  if($psswd1 == "") {
    $msg .= "New users must have a password<br>";
  }
  if($userInfo['userid'] != "") {
    $msg .= "User Name " . $user . " already taken by name in site " . $userInfo['site'];
  }
} else {
  if($userInfo['userid'] != $id and $userInfo['userid'] != "") {
    $msg .= "Logon $user is used by " . $userInfo['name'] . " at site " . $userInfo['site'];
  }
}

debugPrint ("MSG: $msg<br>");

if ($msg == "") {
      if($psswd1 != "") {
      	$hash = getHash($psswd1);
        $passwdSet = "pwd='$hash',";
      }
           
      $set = "set name='$name',
                  user='$user',
                  email='$email',
                  type='$type',
                  site='$site',
                  homeroom='$homeroom',
                  reading='$reading',
                  tutor='$tutor',
                  $passwdSet
                  status='$status'";
                  
      if($mod=="New") {
         $sql = "insert user $set";
      } else {
         $sql = "update user $set where userID=$id";
      }
      debugPrint ("Mod: $mod - $sql");
      $db->get_results($sql);
      debugPrint ("after");
      
      echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=userAdmin&site=$site&status=$status\">");
    } else {
      echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=userInfo&name=$name&user=$user&email=$email&type=$type&site=$site&status=$status&id=$id&msg=$msg\">");
   }

?>
