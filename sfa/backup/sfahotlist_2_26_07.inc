<?php 

$students = "";
$body = "";
$listid = $_GET['listid'];
$quarter = $_GET['quarter'];

switch($quarter) {
   case "first":
      break;
   case "second":
      break;
   case "third":
      break;
   case "fourth":
      break;
   default:
      break;
}

$listname = getListName($listid);

$body .= "<h3>Quarter ($quarter) for list \"$listname\"</h3><br><table width=200 border=0>
  <tr>
  	<td nowrap align=right>School Name</td>
  	<td colspan=9>_______________________________________________________________</td>
  </tr>
  <tr>
  	<td align=right>Date</td>
  	<td colspan=9>_______________________________________________________________</td>
  </tr>
  <tr>
  	<td align=right>Assessment</td>
  	<td colspan=9>_______________________________________________________________</td>
  </tr>
  <tr bgcolor=lightgrey>
    <th>Student Name</th>
    <th>Grade</th>
    <th>Homeroom<br>Teacher</th>
    <th>SFA Teacher</th>
    <th>Current<br>Assessment</th>
    <th>Expected<br>Outcomes</th>
    <th>Currently<br>On Level</th>
    <th>Currently<br>Below<br>Level</th>
    <th>Stayed on<br>Level</th>
    <th>Achieved<br>Level</th>
  </tr>";
  
//  $groupInfo = getSFAStudents($listid);
//  $students = $groupInfo['list'];
//  $scores = $groupInfo['score'];
  
$students = GetHotlist($listid, $quarter);
$cuttoff = getCutOffs();
$hotlist = getHotlistValues();

function abovelevel ($grade, $score, $stage) {
  global $cuttoff;
  
  $score = scorevalue($score);
  $neededmin =  $cuttoff[$grade][$stage];
  
  $answer = $score >= $neededmin and $score != "" ? true : false;
  debugPrint("Score: $score Grade: $grade Stage: $stage NeededMin: $neededmin Answer: $answer");
  return ($answer);
}
//print_r($students);

$i = 0;
foreach ($students as $stu) {

    $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
	$name = $stu->fname . " " . $stu->lname;
	$grade = $stu->grade;
	$id = $stu->studentid;
	$hteacher = $stu->homeroom;
	switch($quarter) {
	   case "base":
	      $rteacher = $stu->base_reading;
	      $score = $stu->base_score;
	      $expect = $stu->base_expect;
	      $rawscore = $stu->base_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'base') ? "1": "0";
	      $belowlevel = $onlevel == "1" ? "0" : "1";
	      $stayonlevel = "NA";
	      $achievelevel = "NA";
		  break;
	   case "first":
	      $rteacher = $stu->first_reading;
	      $expect = $stu->first_expect;
	      $rawscore = $stu->first_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'first') ? "1": "0";
	      $belowlevel = $onlevel == "1" ? "0" : "1";
	      $preonlevel = abovelevel($grade, $rawscore, 'base') ? "1": "0";
	      $stayonlevel = ($onlevel == "1" and $preonlevel == "1") ? "1" : "0";
	      $achievelevel = ($onlevel == "1" and $preonlevel == "0") ? "1" : "0";
		  break;
	   case "second":
	      $rteacher = $stu->second_reading;
	      $expect = $stu->second_expect;
	      $rawscore = $stu->second_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'second') ? "1": "0";
	      $belowlevel = $onlevel == "1" ? "0" : "1";
	      $preonlevel = abovelevel($grade, $rawscore, 'first') ? "1": "0";
	      $stayonlevel = ($onlevel == "1" and $preonlevel == "1") ? "1" : "0";
	      $achievelevel = ($onlevel == "1" and $preonlevel == "0") ? "1" : "0";
		  break;
	   case "third":
	      $rteacher = $stu->third_reading;
	      $expect = $stu->third_expect;
	      $rawscore = $stu->third_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'third') ? "1": "0";
	      $belowlevel = $onlevel == "1" ? "0" : "1";
		  break;
	      $preonlevel = abovelevel($grade, $rawscore, 'second') ? "1": "0";
	      $stayonlevel = ($onlevel == "1" and $preonlevel == "1") ? "1" : "0";
	      $achievelevel = ($onlevel == "1" and $preonlevel == "0") ? "1" : "0";
	   case "fourth":
		  break;
	   default:
	  }
//	$rteacher = $stu->"$quarter_reading";

 
 	$body .=  "<tr bgcolor=$color>
		<td nowrap> $name</td>
		<td> $grade</td>
		<td> $hteacher</td>
		<td> $rteacher</td>
		<td> $rawscore</td>
		<td> $expect</td>
		<td> $onlevel</td>
		<td> $belowlevel</td>
		<td> $stayonlevel</td>
		<td> $achievelevel</td>
	  </tr>";
	
}

$body .= "</table>";


include ("template.inc");

?>