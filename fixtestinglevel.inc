<?php


$sql = "SELECT student.studentid, grade, testinglevel.year, testinglevel.testinglevel from student 
LEFT JOIN testinglevel ON student.studentid = testinglevel.studentid and testinglevel.year = '$CurrentYear'
WHERE student.status = 'Active' and testinglevel.studentid is NULL";

echo "$sql<br>";

$results = $db->get_results($sql, ARRAY_A);

foreach ($results as $row) {
	$studentid = $row['studentid'];
	$grade = $row['grade'];
	$insert = "INSERT testinglevel set year='$CurrentYear', studentid = '$studentid', testinglevel = '$grade' ";
	echo "$insert<br>";
	$db->get_results($insert);
}

?>
