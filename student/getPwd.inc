<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$username = $_GET['username'];
$ans = getStudentPwd($username);
$msg = $ans['msg'];
$res = $ans['result'];

debugPrint("Here3 - $msg Ans - $res");

logHistory("Get Student Password", $username, $res, $msg);


if($res) {
debugPrint("<br>TRUE<br>");
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=logon&msg=$msg\">");
} else {
debugPrint("<br>FALSE<br>");
      echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=forget&msg=$msg\">");
}

?>
