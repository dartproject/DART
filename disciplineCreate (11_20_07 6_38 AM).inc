<?php

include_once ("lib/function_discipline.inc");

$studentid = $_GET['studentid'];
$studentInfo = getStudentInfo($studentid);

$kind = $studentInfo['sped'] == "" ? "regular" : "sped"; // regular, sped

$disciplineid = createDisipline($studentid, $CurrentYear, $kind);

if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=disciplineEdit&disciplineid=$disciplineid\">");
    }
?>
