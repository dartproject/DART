<?php


$action=$_POST['action'];
$msg = $_GET['msg'];
$NextYear = substr($CurrentYear+1, 2, 2);

if($action == 'transcript') {
	$date = $_POST['date'];
//	$body = updateTranscript($CurrentQuarter, $CurrentYear, $date);
	moveQuarterForward($CurrentYear, $CurrentQuarter);
	echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=bigRed&msg=Transcript Set for Q$CurrentQuarter:$CurrentYear-$NextYear Level Set\"> ");
} else if ($action == 'settestinglevel') {
	setTestingLevel ($CurrentYear);
	echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=bigRed&msg=Testing Level Set for $CurrentYear-$NextYear\"> ");
} else if ($action == 'forwardgrade') {
	forwardTestingLevel ();
	echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=bigRed&msg=Testing Level Advanced for $CurrentYear-$NextYear\"> ");
} else {
	$body = putupButtons($msg);
	
}

include ("template.inc");

function moveQuarterForward($year, $quarter) {

	$nextQuarter = ($quarter == '4')? 1 : $quarter+1;
	$nextYear = ($quarter == '4') ? $year+1 : $year;
	$str = '<?php
		$CurrentYear = "'. $nextYear.'";
		$CurrentQuarter = "'.$nextQuarter.'";
?>';
	$fh = fopen('./lib/YearQuarter.inc','w+');
	if(!$fh) {
		echo "ERROR";
		exit();
	} else {
		fwrite($fh, $str);
		fclose($fh);
		flush();
	}
}

function putupButtons($msg) {
	global $CurrentYear, $CurrentQuarter;
	
	$self = $_SERVER[PHP_SELF];
	
	$NextYear = substr($CurrentYear+1, 2, 2);
	$str = <<<END
	<font color=red>$msg</font><br>
	<h1>Current Year: $CurrentYear-$NextYear Current Quarter: $CurrentQuarter</h1>
	Pressing the Move Forward button will save the quarter transcript information and move the website forward one quarter. This is to be used only at the end of the quarter. There is no undo!<p>
	<form action=$self?cmd=bigRed method=post >
		Beginning Quarter Date (Date Format: yyyy-mm-dd Eg. 2007-01-01): <input type=text name=date>
		<input type=hidden name=action value='transcript'>
		<input type=submit name=button value='Move Forward' onClick='javascript:return confirmMsg("Absolutely Run Transcript Update")'>
	</form>
	<hr>
	<form action=$self?cmd=bigRed method=post>
		Set Testing Level For Year $CurrentYear-$NextYear. Click this after all testing levels are correct for the students at the beginning of the year <input type=hidden name=action value='settestinglevel'>		
		<input type=submit name=button value='Set Testing Level' onClick='javascript:return confirmMsg("Absolutely Run Set Testing Level")'>
	</form>
	<hr>
	<form action=$self?cmd=bigRed method=post>
		Set Testing Level For Year $CurrentYear-$NextYear. Click at the end of the year
		<input type=hidden name=action value='forwardgrade'>		
		<input type=submit name=button value='Advance Testing Level' onClick='javascript:return confirmMsg("Absolutely Run Advance Testing Level")'>
	</form>
END;
	return $str;
}

function setTestingLevel ($year) {
	global $db;
	
	$sql = "INSERT INTO testinglevel (studentid, testinglevel, year) 
	SELECT
		studentid, grade, \"$year\"
	FROM
		student
	";
	$results = $db->get_results($sql);
//	echo $sql . "<br>";
}

function forwardTestingLevel () {
	global $db;
	
	$sql = "UPDATE student set grade = grade+1 where student.status = 'active' and grade != '13' ";

	$results = $db->get_results($sql);
//	echo $sql . "<br>";
}

function updateTranscript($quarter, $year, $begindate) {
	global $db;
	
	$next = substr($year+1, 2);
	$timeframe = "Q" . $quarter . ":$year-$next";
	$quarter = "Q" . $quarter;
	$year = "$year";
	
	$sql = <<<END
	INSERT INTO transcript (studentid, subjectid, subjectname, score, timeframe, schoolid, schoolname, year, quarter, gpa) 
	SELECT 
		student.studentid, 
		concat(studentlevel.subject, ".", studentlevel.level) as subjectid,
		level.name, 
		studentlevel.progress, 
		"$timeframe", 
		site.schoolNumber,
		site.name,
		"$year",
		"$quarter",
		"3"
	FROM
		student, studentlevel, level, site	
	WHERE
		studentlevel.studentid = student.studentid and
		level.subject = studentlevel.subject and
		level.level = studentlevel.level and
		student.site = site.siteid and
		studentlevel.progress = "PRO" and
		studentlevel.final > "$begindate"
END;
//	$output .= $sql . "<br>";
	$results = $db->get_results($sql);
	
	$sql = <<<END
	INSERT INTO transcript (studentid, subjectid, subjectname, score, timeframe, schoolid, schoolname, year, quarter, gpa) 
	SELECT 
		student.studentid, 
		concat(studentlevel.subject, ".", studentlevel.level) as subjectid,
		level.name, 
		studentlevel.progress, 
		"$timeframe", 
		site.schoolNumber,
		site.name,
		"$year",
		"$quarter",
		"4"
	FROM
		student, studentlevel, level, site	
	WHERE
		studentlevel.studentid = student.studentid and
		level.subject = studentlevel.subject and
		level.level = studentlevel.level and
		student.site = site.siteid and
		studentlevel.progress = "ADV" and
		studentlevel.final > "$begindate"
END;
//	$output .= $sql . "<br>";
	$results = $db->get_results($sql);
	
		$sql = <<<END
		INSERT INTO transcript (studentid, subjectid, subjectname, score, timeframe, schoolid, schoolname, year, quarter, gpa) 
	SELECT 
		student.studentid, 
		concat(studentlevel.subject, ".", studentlevel.level) as subjectid,
		level.name, 
		studentlevel.progress, 
		"$timeframe", 
		site.schoolNumber,
		site.name,
		"$year",
		"$quarter",
		""
	FROM
		student, studentlevel, level, site	
	WHERE
		studentlevel.studentid = student.studentid and
		level.subject = studentlevel.subject and
		level.level = studentlevel.level and
		student.site = site.siteid and
		studentlevel.final = "0000-00-00"
END;
//	$output .= $sql . "<br>";
	$results = $db->get_results($sql);

	return $output;
}


?>

