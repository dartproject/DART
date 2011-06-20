<?php


newWay();
$body = "Success";
function newWay() {
    global $CurrentYear, $CurrentQuarter, $db;

	$year = $CurrentYear;
	$next = substr($year+1, 2);
	$quarter = $CurrentQuarter;
	$timeframe = "Q" . $quarter . ":$year-$next";
	$now = date("Y-m-d H:m:s");
	
	$sql = <<<END
		INSERT INTO transcript (studentid, subjectid, subjectname, score, timeframe, schoolid, schoolname, year, quarter, gpa, cdate, grp) 
	(SELECT 
		student.studentid, 
		concat(studentlevel.subject, ".", studentlevel.level) as subjectid,
		level.name, 
		studentlevel.progress, 
		concat("Q",quarters.quarter,":",quarters.year,"-", right(quarters.year+1, 2) ) as timeframe, 
		site.schoolNumber,
		site.name,
		quarters.year,
		concat("Q",quarters.quarter) as quarter,
		"3",
		studentlevel.final,
		"$now"
	FROM
		(student, studentlevel, level, site, quarters)
	LEFT JOIN transcript ON
		transcript.studentid = studentlevel.studentid and
		transcript.subjectid = concat(studentlevel.subject, ".", studentlevel.level) and
		transcript.year = quarters.year and 
		transcript.quarter = concat("Q",quarters.quarter)
	WHERE
		studentlevel.studentid = student.studentid and
		level.subject = studentlevel.subject and
		level.level = studentlevel.level and
		student.site = site.siteid and
		studentlevel.progress = "PRO" and
		quarters.start <= studentlevel.final and 
		quarters.finish >= studentlevel.final and 
ISNULL(transcript.studentid)		
		)


END;
//	$output .= $sql . "<br>";
	$results = $db->get_results($sql);
//	echo $results;
	
	$sql = <<<END
		INSERT INTO transcript (studentid, subjectid, subjectname, score, timeframe, schoolid, schoolname, year, quarter, gpa, cdate, grp) 
	(SELECT 
		student.studentid, 
		concat(studentlevel.subject, ".", studentlevel.level) as subjectid,
		level.name, 
		studentlevel.progress, 
		concat("Q",quarters.quarter,":",quarters.year,"-", right(quarters.year+1, 2) ) as timeframe, 
		site.schoolNumber,
		site.name,
		quarters.year,
		concat("Q",quarters.quarter) as quarter,
		"4",
		studentlevel.final,
		"$now"
	FROM
		(student, studentlevel, level, site, quarters)
	LEFT JOIN transcript ON
		transcript.studentid = studentlevel.studentid and
		transcript.subjectid = concat(studentlevel.subject, ".", studentlevel.level) and
		transcript.year = quarters.year and 
		transcript.quarter = concat("Q",quarters.quarter)
	WHERE
		studentlevel.studentid = student.studentid and
		level.subject = studentlevel.subject and
		level.level = studentlevel.level and
		student.site = site.siteid and
		studentlevel.progress = "ADV" and
		quarters.start <= studentlevel.final and 
		quarters.finish >= studentlevel.final and 
ISNULL(transcript.studentid)		
		)

END;
//	$output .= $sql . "<br>";
	$results = $db->get_results($sql);
}


include ("template.inc");
?>
