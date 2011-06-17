<?php 

set_time_limit(0);

include_once("lib/stopwatch.inc");

echo "Start stopwatch<br>";
flush();
$stopwatch = new stopwatch;
$flag = true; // true is print ; false is hold it

// --------- SET UP STANDARDS ARRAY ------------
$sql = "select * from standards where std != 'QPI'";
$results = $db->get_results($sql, ARRAY_A);

foreach ($results as $standard) {
//	$subarray[$standard['subject'] . "." . $standard['level']][$standard['std']] = $standard['shortname'];
	$subarray[$standard['subject'] . "." . $standard['level']][] = $standard['std'];
}

// --------- SET UP STANDARDS COUNT ------------
$sql = "SELECT standards.subject, standards.level, \"2006\" as year, concat(standards.subject, \".\", standards.level) as std, count( standards.std ) AS count
FROM standards
WHERE TYPE = 'std' or type = 'over'
GROUP BY standards.subject, standards.level";
$results = $db->get_results($sql, ARRAY_A);

$stopwatch->lap("SQL Standards Count: $sql", $flag);

foreach ($results as $item) {
	$stdcount[$item['year']][$item['std']] = $item['count'];
}

$sql = "SELECT * FROM level";
$results = $db->get_results($sql, ARRAY_A);

foreach ($results as $item) {
	$stdcount['name'][$item['subject'] . "." . $item['level']] = $item['name'];
}

// ****************
$sql = "select distinct(studentid) as studentid from transcript where score = 'ERR'";

$students = $db->get_results($sql, ARRAY_A);
$c = count($students);

$stopwatch->lap("Got Students: $c", $flag);

$i = 0;
foreach($students as $stu) {

	// Get the transcript values and starts to compute the GPA for each standard
	$studentid = $stu['studentid'];
	$sql = "select distinct(subjectid) as subject from transcript where
			studentid = '$studentid' and score = 'ERR'";
	$errsubjects = $db->get_results($sql, ARRAY_A);
	foreach ($errsubjects as $item) {
		$sub = $item['subject'];
		$where .= $where != ""? " or ": "";
		$where .= " subjectid like '$sub%' ";
	}

	$sql = "select * from transcript where studentid = '$studentid' and ($where) ORDER BY year, quarter, subjectid DESC";
	$results = $db->get_results($sql, ARRAY_A);
	
	$n = count($results);
//	$stopwatch->lap("SQL[$n]: $sql", $flag);
	
	$score = "";
	$scorecount = "";
// *************** Computer Grades for Level Per Quarter

	foreach ($results as $item) {
		$grade = $item['score'];
		$subject = $item['subjectid'];
		$pos = strpos($subject, ".", strpos($subject, ".", 0)+1);
		$pos = $pos == 0 ? 89: $pos;
		$id = substr($subject, 0, $pos);
		$strrev = strrev($subject);
		$other = strrev(substr($strrev, 0, strpos($strrev, ".", 0)));
//		$other = substr($subject, $pos+1, 100) ?  : "";
		$year = $item['year'];
		$quarter = $item['quarter'];
		$sid = $item['sid'];
		
//		echo "---$year, $quarter, $subject, $grade, $pos, $id, $other, $subjectname<br>";
		
		if($id == $subject) {
		 	if($year == '2006') {
//				$subjectname = $stdname[$id];
//print_r($subarray);
//echo "<br>***********<br>";
//print_r($subarray[$id]);
//echo "<br>-----<br>";
//print_r($scorecount[$studentid.$id]['value']);
//echo "<br>-----<br>";
//$computeArray = array_intersect_key($subarray[$id], $scorecount[$studentid.$id]['value']);
				$computeArray = "";
				for($z = 0; $z < count($subarray[$id]); $z++) {
					$computeArray[$subarray[$id][$z]] = $scorecount[$studentid.$id]['value'][$subarray[$id][$z]];
				}
//print_r($computeArray);
//$n1 = count($subarray[$id]);
//$n2 = count($computeArray);
//echo "<br>-$n1--$n2--<br>";

				$value = overallCount($computeArray, $stdcount[$year][$id]);
				$sql = "UPDATE transcript
						SET score = '$value'
						WHERE
							studentid = '$studentid' and
							subjectid = '$id' and
							quarter = '$quarter' and
							year = '$year'
						";
//				echo "SQL: $sql<br>";
				$db->query($sql);
			} else {
				$value = $grade;
			}
//			echo "***$sql<br>$studentid, $id, $year, $quarter, $value<br>";
			if($value == 'PRO') {
//				$score[$studentid.$id.$year.$quarter]['score'] = 'PRO';
				if ($tracking[$studentid.$id] != 'PRO') {
					$tracking[$studentid.$id] = 'PRO';
					$score[$studentid.$id.$year.$quarter]['studentid'] = $studentid;
					$score[$studentid.$id.$year.$quarter]['id'] = $id;
					$score[$studentid.$id.$year.$quarter]['quarter'] = $quarter;
					$score[$studentid.$id.$year.$quarter]['year'] = $year;

					$otherArray = "";
					for($z = 0; $z < count($subarray[$id]); $z++) {
						$otherArray[$subarray[$id][$z]] = $scorecount[$studentid.$id]['other'][$subarray[$id][$z]];
					}

//					$otherArray = array_intersect_key($subarray[$subjectid], $scorecount[$studentid.$id]['other']);
					$num = count($otherArray);
					$total = array_sum($otherArray);
					$gpa = round($total/$num, 2);
					$correction = max($gpa, 3.00);
					$score[$studentid.$id.$year.$quarter]['gpa'] = $correction;
//print_r($otherArray);

//					echo "*** PRO: $sid ($id): $year, $quarter Total: $total NUM Found: $num GPA: $gpa Correction: $correction Value: $value<br>";
				}
//				flush();
			}
			if($value == 'ADV') {
//				$score[$studentid.$id.$year.$quarter]['score'] = 'ADV';
				if ($tracking[$studentid.$id] != 'ADV') {
					$tracking[$studentid.$id] = 'ADV';
					$score[$studentid.$id.$year.$quarter]['studentid'] = $studentid;
					$score[$studentid.$id.$year.$quarter]['id'] = $id;
					$score[$studentid.$id.$year.$quarter]['quarter'] = $quarter;
					$score[$studentid.$id.$year.$quarter]['year'] = $year;

					$otherArray = "";
					for($z = 0; $z < count($subarray[$id]); $z++) {
						$otherArray[$subarray[$id][$z]] = $scorecount[$studentid.$id]['other'][$subarray[$id][$z]];
					}

//					$otherArray = array_intersect_key($subarray[$subjectid], $scorecount[$studentid.$id]['other']);
					$num = count($otherArray);
					$total = array_sum($otherArray);
					$gpa = round($total/$num, 2);
					$correction = max($gpa, 3.00);
					$score[$studentid.$id.$year.$quarter]['gpa'] = $correction;
//					echo "*** ADV: $sid ($id): $year, $quarter Total: $total NUM Found: $num GPA: $gpa Value: $value<br>";
				}
//				flush();
			}
		} else if ($other == 'comment' or $other == 'TIL' or $other == 'INS' or $other == 'QPI' or $other == "" or $other=='qpi') {
		} else {
			$ind = $other;
//			echo "IND: $ind,";
			$largervalue = getLargerValue($grade, $scorecount[$studentid.$id]['value'][$ind]);
			$scorecount[$studentid.$id]['other'][$ind] = getNumericValue($largervalue);
			$scorecount[$studentid.$id]['value'][$ind] = $largervalue;
		}
//		echo "---END: $year, $quarter, $subject, $grade, $pos, $id, $other, $subjectname<br>";
	}
	
	// Should update the gpa scores stored in the transcript
	foreach ($score as $item) {
		$quarter = $item['quarter'];
//		$value = $item['value'];
		$year = $item['year'];
//		$studentid = $item['studentid'];
		$id = $item['id'];
		$count = $stdcount[$year][$id];
		$total = $item['total'];
		$count =  $count ? $count: 1;
		$gpa = $item['gpa'];
		$overall = $item['overall'];
		$sql = "UPDATE transcript
				SET gpa = '$gpa'
				WHERE
					studentid = '$studentid' and
					subjectid = '$id' and
					quarter = '$quarter' and
					year = '$year'
				";
		$db->query($sql);
//		echo "********* SCORE: $sql<br>";
	}
	$stopwatch->lap("$i) Student [$studentid]", true);
	$i++;
//	if($i > 10) { exit(); }


	
}

function overallCount ($values, $total) {
//	echo "Total: $total<br>";

   while(list($var, $val) = each($values)) {
//   	echo "$var=>$val, ";
   	$v[$val] += 1;
   }
   $v['total'] = $total;
   $ans = theOverallScore($v);

//   echo "<br>";
//   print_toggles($values);
//   print_r($v);
//   echo "Score: $ans<br><br>";

   return($ans);
}


function theOverallScore($over) {

  $emgNum = $over['EMG'];
  $devNum = $over['DEV'];
  $proNum = $over['PRO'];
  $advNum = $over['ADV'];
  $totalValues = $proNum + $emgNum + $advNum + $devNum;
  $total = $over['total'];
  
  if ($emgNum == 0 and $devNum == 0 and $advNum > 0 and ($advNum/($proNum+$advNum) >= .9) and $totalValues == $total) { $ans = "ADV"; }
  else if ($emgNum == 0 and $devNum == 0 and $totalValues == $total) { $ans = "PRO"; }
  else if (($proNum > 0 or $advNum > 0) and $total >= $totalValues) { $ans = "DEV"; }
  else if ($total >= $totalValues) { $ans = "EMG"; } 
  else {$ans = "ERR"; }
  debugPrint ("<br>******$sub.$lvl-EMG $emgNum: DEV $devNum: PRO $proNum :ADV $advNum: Total $total: TotalValues $totalValues: - $ans<br>");
  return ($ans);

}

// computes the numericValues of the different Transcores
function getNumericValue($value) {
   if($value == "ADV") {
   		return(4);
   } elseif ($value == "PRO") {
   		return(3);
   } elseif ($value == "DEV") {
   		return(2);
   } elseif ($value == "EMG") {
   		return(1);
   } elseif($value == "" or $value == "NI" or $value == "NA") {
   		return(0);
   } else {
//   		echo "getNumericValue: There is a problem with $value<br>";
   		return(0);
   }
}   

function getLargerValue($val1, $val2) {
   if($val1 == "ADV" or $val2 == 'ADV') {
   		return('ADV');
   } elseif ($val1 == "PRO" or $val2 == "PRO") {
   		return("PRO");
   } elseif ($val1 == "DEV" or $val2 == "DEV") {
   		return("DEV");
   } elseif ($val1 == "EMG" or $val2 == "EMG") {
   		return("EMG");
   } else {
   		return("");
   }
}   

function print_toggles ($values) {
   while(list($var, $val) = each($values)) {
   	echo "$var=>$val, ";
   	$val['std'] = $var;
   	$val['val'] = $val;
   }
   echo "<br>";
}

?>