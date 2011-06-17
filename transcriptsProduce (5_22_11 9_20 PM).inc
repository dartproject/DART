<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once("lib/pdf_functions.php");
include_once("lib/stopwatch.inc");
include_once ("./graduation_report_aux.inc");
//include_once("lib/functions.inc");


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
$dategrad = $_POST['dategrad']."test";
$transcripttype = $_POST['transcriptType'];
$transtype = (strpos($transcripttype, "GPA") === false) ? "" : "gpa";

$maxline = 28;
$page = 1;

$results = $db->get_results("select * from subjects");
foreach($results as $w) {
	$scoreweight[$w->id] = $w->weight;
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
	$sid = $stu['studentid'];
	$sidname = $stu['fname'] . " " . $stu['lname'];
	$data['sname'] = $sidname;
	$data['grade'] = $stu['grade'];
	$data['aid'] = $stu['alaskaid'];
	$data['DOB'] = $stu['bday'];
	$data['gender'] = $stu['gender'];
	$ans = overAllGPA($sid); // 3.857
	$data['GPA'] = $ans['gpa'];
	$data['creditsearned'] =$ans['credit'];
	$data['Testing'] = $stu['testing'];
	$data['Additional Info'] = $stu['additional'];
	$data['EC Activities'] = $stu['extracurricular'];
	$data['dateissued'] = 	$dateIssued;
	$data['dategrad'] = $dateGrad;
	$data['Purpose'] = $transcripttype;

	$test = getTestScores($sid);
//	print_r($test);
	$grades = getGrades($sid, $start, $final);
	$line = 1; $side = 1; $page = 1;
	$year = '';
	foreach($grades as $g) {
//		print_r($g);
//		echo "<br>";
		if (($line == $maxline and $side == 2) or ($line == 1 and $side == 1)) {
			if($page != 1) {
				createFDF($fdf_file, $data);
				createPDFFile ($template, $pdf_temp_file, $fdf_file);
				mergePDFFile($pdf_temp_file, $pdf_file, $tmp_file);
			}
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
			$side = 1;
			$line = 1;
			$page++;
		}
		if ($line == $maxline and $side == 1) {
			$side = 2;
			$line = 1;
		} else if ($line == $maxline and $side == 2) {
			$side = 1;
			$line = 1;		
		}
		if ($year != $g['year'] ){
			$year = $g['year'] ;		
//			echo "Here: $sid: $year<br>" . print_r($test[$sid.$year], true);
			if ($test[$year]) {
	//			echo "Scores: " . $scores . "<br>";
				$data['Testing'] .= $test[$year]['year'] . " Reading " . $test[$year]['Reading'] . "\n";
				$data['Testing'] .= $test[$year]['year'] . " Writing " . $test[$year]['Writing'] . "\n";
				$data['Testing'] .= $test[$year]['year'] . " Math " . $test[$year]['Math'] . "\n";
			}
	//		echo "Testing: " . $data['testing'] . "<br><br>";
		}
		$data['name.' . $side]	.= $g['name']."\n";		
		$data['Q1.' . $side]	.= $g['Q1']."\n";		
		$data['Q2.' . $side]	.= $g['Q2']."\n";
		$data['Q3.' . $side]	.= $g['Q3']."\n";		
		$data['Q4.' . $side]	.= $g['Q4']."\n";	
//		echo "$line-$side-$maxline) {$g['name']} - {$g['Q1']} - {$g['Q2']} - {$g['Q3']} - {$g['Q4']}<br><br>";
		$line++;
	}
	
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

function getSchools($id) {
	global $db;
	echo $id;
	$sql = "SELECT SchoolYear, name FROM studentmovement, SchoolCalendar, site WHERE date >= StartDate and date <= EndDate and studentmovement.site=SchoolCalendar.SiteID and kind = 'enter' and studentid = '$id' and SchoolCalendar.siteID = site.siteid  ORDER BY date";
	$results = $db->get_results($sql, ARRAY_A); 
	foreach ($results as $m) {
		$movement[$m['SchoolYear']] = $m['name'];
	}
	$sql2 = "SELECT * from testinglevel where testinglevel.studentid = '$id' ORDER BY year";
	$results = $db->get_results($sql2, ARRAY_A); 
	foreach($results as $row) {
//		echo $row['year']."-".$movement[$row['year']]. "<br>";
		$name = $movement[$row['year']] != '' ? $movement[$row['year']]: $name;
		$school[$row['year']] = $name;
	}
	return($school);
}
//exportPDFFile($pdf_file);
function getTestScores($sid){
	global $db;
	$sql = "
		SELECT * 
		FROM testscores, student 
		WHERE 
			test = \"HSGQE\" and 
			(standard = \"Reading\" or standard = \"Writing\" or standard = \"Math\") and 
			student.alaskaid = testscores.alaskaid and 
			studentid = '$sid'
			";
//	echo "SQL: $sql<br>";
	$results = $db->get_results($sql, ARRAY_A);	
	foreach($results as $info) {
			$year = substr($info['year'], 0, 4); // . substr($info['year'], 7, 2);
			$test[$year][$info['standard']] = $info['value'];
			$test[$year]['year'] = $year;
//			echo "$studentid: $year<br>";
	}
	return($test);
}

function getGrades($sid, $lower=-2, $upper=13) {
	global $db, $CurrentYear, $CurrentQuarter;
	
	$sl = "('$sid')";
	$sql = "SELECT * FROM testinglevel WHERE studentid in $sl ";
	$results = $db->get_results($sql, ARRAY_A);
	foreach($results as $row) {
		$testinglevel[$row['studentid']][$row['year']] = $row['testinglevel'];
	}
	
	$sql = "SELECT sq.year as syear, sq.quarter as squarter, eq.year as eyear, eq.quarter as equarter, s.*, l.* FROM quarters as sq, quarters as eq,  studentlevel as s, level as l WHERE s.studentid in $sl and s.start >= sq.start and s.start <= sq.finish and  s.final >= eq.start and s.final <= eq.finish and final != '0000-00-00' and s.subject = l.subject and s.level = l.level ORDER BY studentid, syear ";
//	echo $sql;
	$results = $db->get_results($sql, ARRAY_A);
	foreach($results as $row) {
		populateEntry($data, $row);
	}
	
	$sql = "SELECT sq.year as syear, sq.quarter as squarter, '$CurrentYear' as eyear, '$CurrentQuarter' as equarter, s.*, l.* FROM quarters as sq, studentlevel as s, level as l  WHERE s.studentid in $sl and s.start >= sq.start and s.start <= sq.finish and final = '0000-00-00' and s.subject = l.subject and s.level = l.level  ORDER BY studentid, syear";
//	echo $sql;
	$results = $db->get_results($sql, ARRAY_A);
	//print_r($results);
	foreach($results as $row) {
		populateEntry($data, $row);
	}
	
	$schools = getSchools($sid);

//	print_r($data);
	$row ='';
	foreach($data as $student) {
		$studentid = $student['studentid'];
//		echo "{$studentid}<br>";
//		echo "<table border=1><td>Name</td><td>Q1</td><td>Q2</td><td>Q3</td><td>Q4</td></tr>";
		$i =0;
		foreach($student as $year) {
			if($year != $student['studentid']) {
				$y = $year['year'];
				$tl = $testinglevel[$studentid][$y];
				$school = $schools[$y];
				$yearname = "$y-".substr($y+1, 2, 2)." - $school ($tl)";
//				echo "<tr style='background-color: lightgrey;'><td colspan=5>{$yearname} &nbsp;</td></tr>";
		//			$str = print_r($year, true);
		//			$str = str_replace(array("\n", " "), array("<br>\n", "&nbsp;"), $str);
		//			echo "<tr ><td colspan=5>{$str}</td></tr>";
				if($tl >= $lower and $tl <= $upper) {
					$row[] = array("name"=>"$yearname", "Q1"=>"==", "Q2"=>"==", "Q3"=>"==", "Q4"=>"=="); 
					foreach($year as $class) {
						if($class != $year['year']) {
	//						echo "<tr><td>{$class['name']} &nbsp; </td><td>{$class['Q1']} &nbsp;</td><td>{$class['Q2']} &nbsp;</td><td>{$class['Q3']} &nbsp;</td><td>{$class['Q4']} &nbsp;</td></tr>";
				//			$str = print_r($class, true);
				//			echo "<tr ><td colspan=5>{$str}</td></tr>";
							$i++;
							$row[] = array("name"=>"{$class['name']}", "Q1"=>"{$class['Q1']}", "Q2"=>"{$class['Q2']}", "Q3"=>"{$class['Q3']}", "Q4"=>"{$class['Q4']}","year"=>"{$year['year']}"); 	
						}
					}
				}
			}
		}
//		echo "</table><br><br>";
	}
	return($row);
}
function getGradeLetter($val) {
	if($val == 'ADV') return("A");
	else if ($val == 'PRO') return ("B");
	else if ($val == '' or $val == 'EMG' or $val == 'DEV') return("-");
	else return(substr($val, 0, strpos($val," ") ) );
}
function populateEntry(&$data, $row) {

	$class = $row['name']; // . "-".$row['subject'].$row['level'] . " (". substr($row['syear'], 2,2)."Q{$row['squarter']} - " . substr($row['eyear'], 2, 2)."Q{$row['equarter']})";
//	echo "$class<br>";
	$grade = getGradeLetter($row['progress']);
	$year = $row['syear']; $quarter = $row['squarter'];
//	echo "CLASS: $class SYEAR: $year SQUARTER: $quarter EYEAR: {$row['eyear']} EQUARTER: {$row['equarter']}<br>";
	for($i=1; !($year == $row['eyear'] and $quarter == $row['equarter']) and $i<100; $i++) {
//		echo "YEAR: $year QUARTER: $quarter<br>";
//		$data[$row['studentid']][$year][$class]['Q'.$quarter]="$grade";
		$data[$row['studentid']][$year]['year']="$year";
		$data[$row['studentid']][$year][$class]['name']="  $class";
		$data[$row['studentid']][$year][$class]['Q'.$quarter]="-";
		if($quarter >= '4') { $year++; $quarter = 1;} 
		else { $quarter++; }
	}
	$year = $row['eyear']; $quarter = $row['equarter']; 
	$data[$row['studentid']][$year][$class]['Q'.$quarter]="$grade";
	$data[$row['studentid']][$year][$class]['name']="  $class";
	$data[$row['studentid']][$year]['year']="$year";
	$data[$row['studentid']]['studentid'] = $row['studentid'];
//	print_r($data[$row['studentid']][$year]);
//	echo "<br><br>";
}?>

<script language="javascript">
function StartDownload(){
	window.location.href='index.php?cmd=transcriptDL';
	return;
}
StartDownload();
</script>

