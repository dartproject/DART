<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


debugPrint("Here");
$quarter = $_GET['quarter'];
$teacher = $_GET['teacher'];
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=root&teacher=$teacher&quarter=$quarter&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";

function stage($value) {
  if($value == "Pre" or $value == "KC" or $value = "") { return (0); }
  else if ($value == "1-5") { return (1); }
  else if ($value == "6-10") { return (2); }
  else if ($value == "11-15") { return (3); }
  else if ($value == "16-20") { return (4); }
  else if ($value == "21-52") { return (5); }
  else if ($value == "26-31") { return (6); }
  else if ($value == "32-37") { return (7); }
  else if ($value == "38-42") { return (8); }
  else if ($value == "43-48") { return (9); }
  else { return (10); }
  
}

function ongradelevel ($score, $minscore) {
  if($score < $minscore) { return ("Below"); }
  else if ($score == $minscore) { return ("On"); }
  else if ($score > $minscore) { return ("Above"); }
  return("Error see<br>tech support");
}

function expectation($stage1, $estage) {
  if ($stage1 == $estage) { return ("M"); }
  else if ($stage1 < $estage) { return ("NM"); }
  else if ($stage1 > $estage) { return ("E"); }
  else { return("NA"); }
}

switch($quarter) {
   case "first":
      $title = "First Assessment - Q1";
      $heading1_1 = "Baseline<br>Assessment<br>Mastery";
      $heading1_2 = "Baseline<br>Stage";
      $heading2_1 = "1st<br>Assessment<br>Mastery";
      $heading2_2 = "1st Stage";
      $h1_1 = "base_rawscore"; $h1_2 = "base_score";
      $h2_1 = "first_rawscore"; $h2_2 = "first_score";
      $search = "base";
      $sfa = "base_sfa";
      $expect = "base_expect";
      break;
   case "second":
      $title = "Second Assessment - Q2";
      $heading1_1 = "1st<br>Lexile";
      $heading1_2 = "1st<br>Level<br>Conversion";
      $heading2_1 = "2nd<br>Assessment<br>Lexile";
      $heading2_2 = "2nd Assess<br>Level<br>Conversion";
      $h1_1 = "first_rawscore"; $h1_2 = "first_score";
      $h2_1 = "second_rawscore"; $h2_2 = "second_score";
      $search = "first";
      $sfa = "first_sfa";
      $expect = "first_expect";
      break;
   case "third":
      $title = "Third Assessment - Q2";
      $heading1_1 = "2nd<br>Lexile";
      $heading1_2 = "2nd<br>Level<br>Conversion";
      $heading2_1 = "3rd<br>Assessment<br>Lexile";
      $heading2_2 = "3rd Assess<br>Level<br>Conversion";
      $h1_1 = "second_rawscore"; $h1_2 = "second_score";
      $h2_1 = "third_rawscore"; $h2_2 = "third_score";
      $search = "second";
      $sfa = "second_sfa";
      $expect = "second_expect";
      break;
   case "fourth":
      $title = "Fourth Assessment - Q2";
      $heading1_1 = "3rd<br>Lexile";
      $heading1_2 = "3rd<br>Level<br>Conversion";
      $heading2_1 = "4th<br>Assessment<br>Lexile";
      $heading2_2 = "4th Assess<br>Level<br>Conversion";
      $h1_1 = "third_rawscore"; $h1_2 = "third_score";
      $h2_1 = "fourth_rawscore"; $h2_2 = "fourth_score";
      $search = "third";
      $sfa = "third_sfa";
      $expect = "third_expect";
      break;
   default:
      break;
}

$levels = getContentReadingAreaStudents($teacher, $search, $year);
$students = getSFATeacherStudents($teacher, $search, $year);
$teacherName = $students[0]['name'];
$title .= " ($teacherName)";


$body .= "<h2>Class Progress-Roots<br>$title</h2>$selection<table border=1>";

$body .= "<tr bgcolor=lightgrey>
            <th>Grade</th>
            <th>Student</th>
            <th>Content<br>Area<br>Reading<br>Level</th>
            <th>$heading1_1</th>
            <th>$heading1_2</th>
            <th>Expected Growth</th>
            <th>Expected Stage</th>
            <th>$heading2_1</th>
            <th>$heading2_2</th>
            <th>Exceeded/<br>Met/<br>Not Met</th>
            <th>Growth</th>
            <th>Above/On/Below<br>Grade Level</th>
           </tr>";
 $i = 0; 
 settype ($growth, "int");
 foreach ($students as $stu) {
    debugPrint("=> here");
//    print_r($stu);
    $id = $stu['studentid'];
    $grade = $stu['testinglevel'];
    $student = $stu['lname'] . ", " . $stu['fname'];
    $rlevel = "RE." . $levels[$id];
    $sfamat = $stu[$sfa];
    $firstscore = $stu[$h1_1];
    $firststage = scorevalue($firstscore);
    $expectedscore = $stu[$expect];
    $expectedstage = scorevalue($expectedscore);
    $secondscore = $stu[$h2_1];
    $secondstage = scorevalue($secondscore);
    $eval = expectation($secondstage, $expectedstage);
    $neededmin = $stu['neededmin'];
    $growth = $secondstage - $firststage;
    $gradelevel = ongradelevel($secondstage, $neededmin);
    $total1 += $firststage;
    $total2 += $secondstage;
    $total3 += $growth;
    $i++;
    debugPrint("Growth: $growth dv($grouwth)=>" . dv($growth));
    $body .=  "<tr>
				<td>" . dv($grade) . "</td>
				<td>" . dv($student) . "</td>
				<td align=right>" . dv($rlevel) . "</td>
				<td align=right>" . dv($firstscore) . "</td>
				<td align=right>" . dv($firststage) . "</td>
				<td align=right>" . dv($expectedscore) . "</td>
				<td align=right>" . dv($expectedstage) . "</td>
				<td align=right>" . dv($secondscore) . "</td>
				<td align=right>" . dv($secondstage) . "</td>
				<td align=right>" . dv($eval) . "</td>
				<td align=right>" . dv($growth) . "</td>
				<td align=right>" . dv($gradelevel) . "</td>
			   </tr>";
			   
     $group .= "<input type=hidden name=studentID[] value = $id>";               
 }

$avg1 = round($total1/$i, 2);
$avg2 = round($total2/$i, 2);
$avg3 = round($total3/$i, 2);

$body .= "<tr bgcolor=lightgrey>
            <th> </th>
            <th> </th>
            <th> </th>
            <th align=right>TOTAL</th>
            <th align=right>$total1</th>
            <th> </th>
            <th> </th>
            <th align=right>TOTAL</th>
            <th align=right>$total2</th>
            <th align=right>TOTAL</th>
            <th align=right>$total3</th>
            <th> </th>
           </tr>";
$body .= "<tr bgcolor=lightgrey>
            <th> </th>
            <th> </th>
            <th> </th>
            <th align=right>AVERAGE</th>
            <th align=right>$avg1</th>
            <th> </th>
            <th> </th>
            <th align=right>AVERAGE</th>
            <th align=right>$avg2</th>
            <th align=right>AVERAGE</th>
            <th align=right>$avg3</th>
            <th> </th>
           </tr>";
         
 $body .= "</table>";

$body .= "<form name=\"group\" action=\"index.php?cmd=handleGroup\" method=\"post\" >
          $group
          <input type=submit name=cmd2 value='Group'></form>";
           
 include_once("template.inc");
         
?>