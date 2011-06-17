<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once("lib/pdf_functions.php");
include_once("lib/stopwatch.inc");


set_time_limit(0);

echo " ";
flush();

$stopwatch = new stopwatch;
$flag = false; // true is print ; false is hold it
$transtype = 'notgpa';
$fdf_file = "exp/$currentUserID.txt";
$pdf_file = "exp/$currentUserID.pdf";
$pdf_temp_file = "exp/$currentUserID" . "_temp.pdf";
$test_file = "exp/test.pdf"; // initial file for setting everything up.
$tmp_file = "exp/tmp.pdf";
$template = "transcript.pdf";

unlink ($pdf_file);
unlink ($pdf_temp_file);
unlink ($fdf_file);
copyFile($test_file, $pdf_file);

$names = getReportListItems($currentUserID);
debugPrint("Names: " . print_r($names, true));
$start = $_POST['start'];
$final = $_POST['final'];
$dateIssued = $_POST['dateIssued'];
$transcripttype = $_POST['transcriptType'];
$transtype = (strpos($transcripttype, "GPA") === false) ? "" : "gpa";

$results = $db->get_results("select * from scoreweight");
foreach($results as $w) {
	$scoreweight[$w->subjectid] = $w->weight;
}

/*
foreach ($names as $stu) {
   $id = $stu['studentid'];
   $selection .= $selection ? " or " : "";
   $selection .= "  student.studentid = '$id' ";
}
//*/
//echo ">>>>>> START: $start FINAL: $final<br>";
//flush();

if($start != "" and $final != "" and $transcripttype != "") {
	for($i = $start; $i <= $final; $i++) {
	   $testinglevel .= $testinglevel ? " or " : "";
	   $testinglevel .= "  testinglevel.testinglevel = '$i' ";
	}
	echo "This may take a while. Please be patient.<br>";
} else {
	echo "<h1>ERROR: Please use the back button and set the report type, start and finish information</h1>";
	exit();
}

function scoreEntry($value) {
	return(($value == "" or $value == "0") ? "---": $value);
}
function nameEntry($name) {
//	return(" " . substr($name, 0, 25));
	return("   $name");
}

function dateConversion($date) {
	return (substr($date, 5, 2) . "/" . substr($date, 8, 2) . "/" . substr($date, 0, 4));
}

function letterGrade($value) {
	if($value < 3.5) {
		return("B");
	} else if($value >= 3.5 and $value < 3.75) {
		return("B+");
	} else if($value >= 3.75 and $value < 3.85) {
		return("A-");
	} else if($value > 3.85) {
		return("A");
	}
}
/////////////////////////////////////////////////
// Get data for grades for each student
/////////////////////////////////////////////////
function scoreCheck ($score, $help = '') {
	if($score == 'ADV' or $score == 'PRO' or $score == 'DEV' or $score == 'EMG' or $score == '') {
		$ans = $score;
	} elseif ($score == 'NA' or $score == 'NI') {
		$ans = '';
	} else {
		echo "PROBLEM: $help<br>";
		$ans = '';
	}
	flush();
	return ($ans);
}

$ct = 1;
$cttotal = count($names);

echo "Total to produce: $cttotal<br>";
foreach ($names as $stu) {
	echo "$ct,";
	if (fmod($ct, 100) == 0) { echo "<br>"; flush(); }
	$sid = $stu['studentid'];
	$sidname = $stu['fname'] . " " . $stu['lname'];
//	echo "$ct of $cttotal) Studentid: $sid $sidname<br>";
	$ct++;
//	if ($ct > 2) { exit(); }
	$grades = "";
	$test = "";
	$data = "";
	$gpaarray = "";
	$stopwatch->lap("Before SQL", $flag);
	$selection = "  student.studentid = '$sid' ";
	$sql = ($selection and $testinglevel) ?
		"SELECT * FROM student, transcript, testinglevel 
			WHERE ($selection) and ($testinglevel) and student.studentid = transcript.studentid 
					and student.studentid = testinglevel.studentid and testinglevel.year = transcript.year 
			ORDER BY transcript.year, transcript.subjectid, transcript.quarter 
		" :
		"";
//	$sql = ($selection and $testinglevel) ?
//			"SELECT *
//			FROM student
//			LEFT JOIN testinglevel ON
//    			student.studentid = testinglevel.studentid
//				AND ($testinglevel
//				)
//			LEFT JOIN transcript ON student.studentid = transcript.studentid
//				AND testinglevel.year = transcript.year
//			WHERE $selection
//			" :
//			"";
// ORDER BY student.studentid, transcript.year, transcript.quarter, transcript.subjectid
	
//	echo "SQL: $sql<br>";
	$results = $db->get_results($sql, ARRAY_A);
	if($results == "") {
		$sql = "select * from student where $selection";
		$results = $db->get_results($sql, ARRAY_A);
	}	
	$stopwatch->lap("After SQL", $flag);	
	
	foreach($results as $info) {
		if (substr_count($info['subjectid'], '.') == 1 ){
			$studentid = $info['studentid'];
			$quarter = substr($info['timeframe'], 0, 2);
			$year = substr($info['timeframe'], 3, 100);
			$subjectid = $info['subjectid'];
			$area = substr($subjectid, 0, 2);
			$weight = $scoreweight[$area];
			if($transtype == 'gpa') {
//				echo "$studentid.$year.$subjectid, $quarter " . $info['gpa'] . "<br>";
				if($info['gpa'] != 0 and $info['gpa'] != "") {
					$letter = letterGrade($info['gpa']);
					$score = "$letter/" . number_format($weight, 2, '.', '');
				} else {
					$score = "";
				}
			} else {
				$score = scoreCheck($info['score'], "StudentID: " . $studentid . " Subject Info: " . $subjectid . "_" . $year . "_" . $quarter. " ==> " . $score);
			}
//			echo $info['gpa'] . "==>" . $gpaarray[$subjectid] . "<br>";
			if($info['gpa'] != 0 and $info['gpa'] != "") {
				$gpaarray['org'][$subjectid] = max($info['gpa'], $gpaarray['org'][$subjectid]);
				$gpaarray['gpa'][$subjectid] = max($info['gpa']*$weight, $gpaarray['gpa'][$subjectid]);
				$gpaarray['count'][$subjectid] = $weight;
			}
			$grades[$studentid.$year.$subjectid]['year'] = $year;
			$grades[$studentid.$year.$subjectid]['sort'] = $studentid.$subjectid.$year.$quarter;
			$grades[$studentid.$year.$subjectid]['schoolname'] = $info['schoolname'];
			$grades[$studentid.$year.$subjectid]['schoolid'] = $info['schoolid'];
			$grades[$studentid.$year.$subjectid]['studentid'] = $info['studentid'];
			$grades[$studentid.$year.$subjectid]['sname'] = $info['fname'] . " " . $info['lname'];
			$grades[$studentid.$year.$subjectid]['grade']  = $info['grade'];
			$grades[$studentid.$year.$subjectid]['alaskaid']  = $info['alaskaid'];
			$grades[$studentid.$year.$subjectid]['subjectid']  = $info['subjectid'];
			$grades[$studentid.$year.$subjectid]['subjectname']  = $info['subjectname'];
			$grades[$studentid.$year.$subjectid]['bday']  = dateConversion($info['bday']);
			$grades[$studentid.$year.$subjectid]['gender']  = $info['gender'];
			$grades[$studentid.$year.$subjectid][$quarter] = $score;
			$grades[$studentid.$year.$subjectid]['timeframe'] = $year;		
			$grades[$studentid.$year.$subjectid]['testinglevel'] = $info['testinglevel'];
		} else {
			$studentid = $info['studentid'];
			$grades[$studentid.$year.$subjectid]['studentid'] = $info['studentid'];
			$grades[$studentid.$year.$subjectid]['sname'] = $info['fname'] . " " . $info['lname'];
			$grades[$studentid.$year.$subjectid]['grade']  = $info['grade'];
			$grades[$studentid.$year.$subjectid]['alaskaid']  = $info['alaskaid'];
			$grades[$studentid.$year.$subjectid]['bday']  = dateConversion($info['bday']);
			$grades[$studentid.$year.$subjectid]['gender']  = $info['gender'];
//			echo "====> $studentid<br>";
		}	
	}
	
	$stopwatch->lap("After Putting in Array", $flag);
	
//	array_sort($grades, 'sort');
//	
//	$stopwatch->lap("After Sorting The Array", $flag);
//	
//	$i = 1;
//	foreach($grades as $test) {
//		echo $test['sort']."<br>";
//		if ($i++ == 10) break;
//	}
//	
//	$stopwatch->lap("Printout from sort", $flag);
	
	/////////////////////////////////////////////////
	// Get data for grades for each student
	/////////////////////////////////////////////////
	
	$sql = "
		SELECT * 
		FROM testscores, student 
		WHERE 
			test = \"HSGQE\" and 
			(standard = \"Reading\" or standard = \"Writing\" or standard = \"Math\") and 
			student.alaskaid = testscores.alaskaid and 
			($selection)
			";
	//echo "SQL: $sql<br>";
//	echo $sql;
	$results = $db->get_results($sql, ARRAY_A);
	
	foreach($results as $info) {
			$year = substr($info['year'], 0, 5) . substr($info['year'], 7, 2);
			$studentid = $info['studentid'];
			$test[$studentid.$year][$info['standard']] = $info['value'];
			$test[$studentid.$year]['year'] = $year;
//			echo "$studentid: $year<br>";
	}
	
	$stopwatch->lap("Testscores from each student", $flag);
	
	/////////////////////////////////////////////////
	// Put Data into Transcripts
	/////////////////////////////////////////////////
	
	$holder = "===";
	$studentid = '';
	$timeframe = '';
	$side = 1;
	$line = 1;
	$maxline = 28;
	$page = 1;
	$num = array_sum($gpaarray['count']);
	$total = array_sum($gpaarray['gpa']);
	$gpa = round($total/$num, 2);
	$dateissued = date("m/d/Y");
//	echo "COUNT: " . print_r($gpaarray['count'], true) . "<br><br>ORG: " . print_r($gpaarray['org'], true) . "<br><br>GPA: " . print_r($gpaarray['gpa'], true) . "<br>$gpa<br><br>";
	
//	echo 	print_r ($gpaarray, false) . "===> $gpa<br>";
	
	foreach($grades as $info) {
		if (($line == $maxline and $side == 2) or ($studentid != $info['studentid'] and $studentid != "")) {
			createFDF($fdf_file, $data);
			createPDFFile ($template, $pdf_temp_file, $fdf_file);
			mergePDFFile($pdf_temp_file, $pdf_file, $tmp_file);
			$data['name.1'] = "";
			$data['name.2'] = "";
			$data['Q1.1'] = "";
			$data['Q2.1'] = "";
			$data['Q3.1'] = "";
			$data['Q4.1'] = "";
			$data['Q1.2'] = "";
			$data['Q2.2'] = "";
			$data['Q3.2'] = "";
			$data['Q4.2'] = "";
			$data['Testing'] = "";
			$studentid = '';
			$timeframe = '';
			$side = 1;
			$line = 1;
			$page++;
		}
		if ($studentid != $info['studentid'] ){
			$data['sname'] = $info['sname'];
			$data['grade'] = $info['grade'];
			$data['aid'] = $info['alaskaid'];
			$data['DOB'] = $info['bday'];
			$data['gender'] = $info['gender'];
			$studentid = $info['studentid'];	
//			echo "STUDENTID $studentid DOB:" . $data['DOB'] . "<br>";
		}
		if ($timeframe != $info['timeframe'] ){
			$data['GPA'] = $gpa;
			$data['dateissued'] = $dateIssued;
			$data['creditsearned'] = $num;
			$data['Purpose'] = $transcripttype;
			$data['Page'] = "Page $page";
			$data['name.' . $side]	.= $info['timeframe'] . " - " . $info['schoolname'] . "(" . $info['testinglevel'] .  ")\n";		
			$data['Q1.' . $side]	.= "$holder\n";		
			$data['Q2.' . $side]	.= "$holder\n";		
			$data['Q3.' . $side]	.= "$holder\n";		
			$data['Q4.' . $side]	.= "$holder\n";		
			$timeframe = $info['timeframe'] ;		
			$year = $info['year'];
//			echo "Here: $studentid: $year<br>" . print_r($test[$studentid.$year], true);
			if ($test[$studentid.$year]) {
	//			echo "Scores: " . $scores . "<br>";
				$data['Testing'] .= $test[$studentid.$year]['year'] . " Reading " . $test[$studentid.$year]['Reading'] . "\n";
				$data['Testing'] .= $test[$studentid.$year]['year'] . " Writing " . $test[$studentid.$year]['Writing'] . "\n";
				$data['Testing'] .= $test[$studentid.$year]['year'] . " Math " . $test[$studentid.$year]['Math'] . "\n";
			}
	//		echo "Testing: " . $data['testing'] . "<br><br>";
		}
		if ($line == $maxline and $side == 1) {
			$side = 2;
			$line = 1;
			$data['name.' . $side]	.= $info['timeframe'] . " - " . $info['schoolname'] . "\n";		
			$data['Q1.' . $side]	.= "$holder\n";		
			$data['Q2.' . $side]	.= "$holder\n";		
			$data['Q3.' . $side]	.= "$holder\n";		
			$data['Q4.' . $side]	.= "$holder\n";		
		}
		$data['name.' . $side]	.= nameEntry($info['subjectname']) . "\n";
		$data['Q1.' . $side]	.= scoreEntry($info['Q1']) . "\n";
		$data['Q2.' . $side]	.= scoreEntry($info['Q2']) . "\n";
		$data['Q3.' . $side]	.= scoreEntry($info['Q3']) . "\n";
		$data['Q4.' . $side]	.= scoreEntry($info['Q4']) . "\n";
//		echo $info['subjectid'] . " Q1: " . scoreEntry($info['Q1']) ." Q2: " . $info['Q2'] ." Q3: " . $info['Q3'] ." Q4: " . $info['Q4'] . "<br>";
		$line++;
	}
//	print_r($data);
	
	// Create the FDF file of data used to populate the template
	createFDF($fdf_file, $data);
	createPDFFile ($template, $pdf_temp_file, $fdf_file);
	mergePDFFile($pdf_temp_file, $pdf_file, $tmp_file);
	
//	$stopwatch->lap("STUDENTID: $studentid PDF creation", true);
}
// this will export the pdf file. Make sure that there is no text print out before this is called.

echo "<br><br><a href='index.php?cmd=transcriptDL'>If Download Does Not Start Click Here</a> <br><br>
<a href='index.php?cmd=transcriptsDefine'>Go Back</a>";
flush();

//exportPDFFile($pdf_file);
?>

<script language="javascript">
function StartDownload(){
	window.location.href='index.php?cmd=transcriptDL';
	return;
}
StartDownload();
</script>
