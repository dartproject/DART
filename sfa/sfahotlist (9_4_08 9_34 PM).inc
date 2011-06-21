<?php 

$students = "";
$body = "";
$listid = $_GET['listid'];
$quarter = $_GET['quarter'];
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=sfahotlist&quarter=$quarter&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";

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

$body .= "<h3>Quarter ($quarter) for list \"$listname\"</h3><br>$selection<table width=200 border=0>
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
  
$students = GetHotlist($listid, $quarter, $year);
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

$teachers = getTeachers();


$i = 0;
foreach ($students as $stu) {

    $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
	$name = $stu->fname . " " . $stu->lname;
	$grade = $stu->grade;
	$id = $stu->studentid;
	$hteacher = $teachers[$stu->homeroom]['name'];
	switch($quarter) {
	   case "base":
	      $rteacher = $teachers[$stu->base_reading]['name'];
	      $score = $stu->base_score;
	      $expect = $stu->base_expect;
	      $rawscore = $stu->base_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'base') ? "X": "O";
	      $belowlevel = $onlevel == "1" ? "O" : "X";
	      $stayonlevel = "NA";
	      $achievelevel = "NA";
		  break;
	   case "first":
	      $rteacher = $teachers[$stu->first_reading]['name'];
	      $expect = $stu->first_expect;
	      $rawscore = $stu->first_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'first') ? "X": "O";
	      $belowlevel = $onlevel == "1" ? "O" : "X";
	      $preonlevel = abovelevel($grade, $rawscore, 'base') ? "X": "O";
	      $stayonlevel = ($onlevel == "1" and $preonlevel == "X") ? "X" : "O";
	      $achievelevel = ($onlevel == "1" and $preonlevel == "O") ? "X" : "O";
		  break;
	   case "second":
	      $rteacher = $teachers[$stu->second_reading]['name'];
	      $expect = $stu->second_expect;
	      $rawscore = $stu->second_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'second') ? "X": "O";
	      $belowlevel = $onlevel == "1" ? "O" : "X";
	      $preonlevel = abovelevel($grade, $rawscore, 'first') ? "X": "O";
	      $stayonlevel = ($onlevel == "1" and $preonlevel == "X") ? "X" : "O";
	      $achievelevel = ($onlevel == "1" and $preonlevel == "O") ? "X" : "O";
		  break;
	   case "third":
	      $rteacher = $teachers[$stu->third_reading]['name'];
	      $expect = $stu->third_expect;
	      $rawscore = $stu->third_rawscore;
	      $onlevel = abovelevel($grade, $rawscore, 'third') ? "X": "O";
	      $belowlevel = $onlevel == "1" ? "O" : "X";
	      $preonlevel = abovelevel($grade, $rawscore, 'second') ? "X": "O";
	      $stayonlevel = ($onlevel == "1" and $preonlevel == "X") ? "X" : "O";
	      $achievelevel = ($onlevel == "1" and $preonlevel == "O") ? "X" : "O";
		  break;
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
		<td align=center> $onlevel</td>
		<td align=center> $belowlevel</td>
		<td align=center> $stayonlevel</td>
		<td align=center> $achievelevel</td>
	  </tr>";
	
}

$body .= "</table>";


include ("template.inc");

?>