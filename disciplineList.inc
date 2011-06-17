<?php

include_once ("lib/function_discipline.inc");

$studentid = $_GET['studentid'];

$disciplines = getDisipline($studentid, $CurrentYear);

$header = "<tr><th>Type</th><th>Creation Date</th><th>Incident Date</th><th>Status</th><th>Edit</th></tr>";

foreach ($disciplines as $dis) {
	$id = $dis['disciplineid'];
	$kind = $dis['kind'];
	$date = $dis['creation'];
	$idate = $dis['incidentdate'];	
	$dstatus = varValue($dstatusValues, $dis['dstatus']);
	$data .= "<tr>
				<td>$kind</td>
				<td>$date</td>
				<td>$idate</td>
				<td>$dstatus</td>
				<td><a href=index.php?cmd=disciplineEdit&disciplineid=$id>Edit</a>
			  </tr>
			  ";
}

$body = <<<END
<table border=1>
$header
$data
</table>
<a href=index.php?cmd=disciplineCreate&studentid=$studentid>Create Discipline</a>
END;

include ("template.inc");

?>
