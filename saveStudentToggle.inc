<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$location = $_POST['loc'];

$studentID = $_POST['studentid'];

$studentInfo = getStudentInfo($studentID);
$site = $studentInfo['site'];

if(Privilege(A3) == 'district' or (Privilege(A3) == 'site' and $currentMySite == $site)) {
    saveGrades ($HTTP_POST_VARS);
    if($debug <> "on") {
        echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=toggleStudent&p1=$studentID\">");
    } else {
        debugPrint ("Location: " . $location . "<br>");
        debugPrint ("<a href=$loc>Go To Page</a><br>");
    }
} else {
    NoPriv("deny saveStudentToggle", "studentID=$studentID");
}


?>
