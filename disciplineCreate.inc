<?php

include_once ("lib/function_discipline.inc");

$studentid = $_GET['studentid'];
$studentInfo = getStudentInfo($studentid);
$site = $studentInfo['site'];

$kind = $studentInfo['sped'] == "N" ? "regular" : "sped"; // regular, sped

$disciplineid = createDiscipline($studentid, $CurrentYear, $kind, $site);
if($debug <> "on") {
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=disciplineEdit&disciplineid=$disciplineid\">");
    }
?>
