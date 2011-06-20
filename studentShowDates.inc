<?php

$id = $_GET['id'];
$student = getStudentInfo($id);
$studentName = $student['fname'] . " " . $student['lname'];

$dates = getEnterExitDates($id);

$body ="Transitions for: $studentName<br>
		<table border=1><tr bgcolor=lightblue>
			<th>Date</th>
			<th>Type</th>
			<th>Code</th>
			<th>Site</th>
			<td>Comments</td>";
		
foreach ($dates as $date) {
	$body .= "<tr>
				<td>" . $date['date'] . "</td>
				<td>" . $date['kind'] . "</td>
				<td>" . $date['code'] . "</td>
				<td>" . $date['site'] . "</td>
				<td>" . $date['comment'] . "&nbsp;</td>
			  </tr>";
}
$body .= "</tr></table><br><button onClick='window.close();'>Close Window</button>";

echo $body;
//include('template.inc');
?>
