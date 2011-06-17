<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$quarter = $_GET['quarter'];
$teacher = $_GET['teacher'];
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=wing&teacher=$teacher&quarter=$quarter&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";


switch($quarter) {
   case "first":
      $title = "First Assessment - Q1";
      $heading1_1 = "Baseline<br>Lexile";
      $heading1_2 = "Baseline<br>Level<br>Conversion";
      $heading2_1 = "1st<br>Assessment<br>Lexile";
      $heading2_2 = "1st Assess<br>Level<br>Conversion";
      $h1_1 = "base_rawscore"; $h1_2 = "base_score";
      $h2_1 = "first_rawscore"; $h2_2 = "first_score";
      $search = "base";
      $sfa = "base_sfa";
      $nextq = "first";
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
      $nextq = "second";
      break;
   case "third":
      $title = "Third Assessment - Q3";
      $heading1_1 = "2nd<br>Lexile";
      $heading1_2 = "2nd<br>Level<br>Conversion";
      $heading2_1 = "3rd<br>Assessment<br>Lexile";
      $heading2_2 = "3rd Assess<br>Level<br>Conversion";
      $h1_1 = "second_rawscore"; $h1_2 = "second_score";
      $h2_1 = "third_rawscore"; $h2_2 = "third_score";
      $search = "second";
      $sfa = "second_sfa";
      $nextq = "third";
      break;
   case "fourth":
      $title = "Fourth Assessment - Q4";
      $heading1_1 = "3rd<br>Lexile";
      $heading1_2 = "3rd<br>Level<br>Conversion";
      $heading2_1 = "4th<br>Assessment<br>Lexile";
      $heading2_2 = "4th Assess<br>Level<br>Conversion";
      $h1_1 = "third_rawscore"; $h1_2 = "third_score";
      $h2_1 = "fourth_rawscore"; $h2_2 = "fourth_score";
      $search = "third";
      $sfa = "third_sfa";
      $nextq = "fourth";
      break;
   default:
      break;
}

$levels = getContentReadingAreaStudents($teacher, $search, $year);
$students = getSFATeacherStudents($teacher, $search, $year);
$teacherName = $students[0]['name'];
$title .= " ($teacherName)";
$lexOnLevel= getCutOffs();

$body .= "<h2>Class Progress-Wings-RE-SA<br>$title</h2>$selection<table border=1>";

$body .= "<tr bgcolor=lightgrey>
            <th>Grade</th>
            <th>Student</th>
            <th>Content<br>Area<br>Reading<br>Level</th>
            <th>SFA<br>Material<br>Level</th>
            <th>$heading1_1</th>
            <th>$heading1_2</th>
            <th>$heading2_1</th>
            <th>$heading2_2</th>
            <th>Lexile<br>Needed to<br>be on Level</th>
            <th>Growth<br>Made</th>
            <th>Growth<br>Needed</th>
           </tr>";
 $i = 0;          
 foreach ($students as $stu) {
    $id = $stu['studentid'];
    $grade = $stu['gradelevel'];
    $student = $stu['lname'] . ", " . $stu['fname'];
    $rlevel = "RE." . $levels[$id];
    $sfamat = $stu[$sfa];
    $firstscore = $stu[$h1_1];
    $firstconversion = $stu[$h1_2];
    $secondscore = $stu[$h2_1];
    $secondconversion = $stu[$h2_2];
//    $lexneeded = $stu['neededmin'];
    $lexneeded = $lexOnLevel[$grade][$nextq];
//    echo ("Grade: $grade NextQ: $nextq Lex: " . $lexneeded . "<br>");
    $gmade = $secondscore - $firstscore;
    $gneeded = $lexneeded - $firstscore;
    $total1 += $firstscore;
    $total2 += $secondscore;
    $total3 += $gmade;
    $total4 += $gneeded;
    $i++;
    $body .=  "<tr>
				<td>" . dv($grade) . "</td>
				<td>" . dv($student) . "</td>
				<td align=right>" . dv($rlevel) . "</td>
				<td align=right>" . dv($sfamat) . "</td>
				<td align=right>" . dv($firstscore) . "</td>
				<td align=right>" . dv($firstconversion) . "</td>
				<td align=right>" . dv($secondscore) . "</td>
				<td align=right>" . dv($secondconversion) . "</td>
				<td align=right>" . dv($lexneeded) . "</td>
				<td align=right>" . dv($gmade) . "</td>
				<td align=right>" . dv($gneeded) . "</td>
			   </tr>";
			   
     $group .= "<input type=hidden name=studentID[] value = $id>";                          
 }

$avg1 = round($total1/$i, 2);
$avg2 = round($total2/$i, 2);
$avg3 = round($total3/$i, 2);
$avg4 = round($total4/$i, 2);

$body .= "<tr bgcolor=lightgrey>
            <th> </th>
            <th> </th>
            <th> </th>
            <th align=right>TOTAL</th>
            <th align=right>$total1</th>
            <th align=right>TOTAL</th>
            <th align=right>$total2</th>
            <th> </th>
            <th align=right>TOTAL</th>
            <th align=right>$total3</th>
            <th align=right>$total4</th>
           </tr>";
$body .= "<tr bgcolor=lightgrey>
            <th> </th>
            <th> </th>
            <th> </th>
            <th align=right>AVERAGE</th>
            <th align=right>$avg1</th>
            <th align=right>AVERAGE</th>
            <th align=right>$avg2</th>
            <th> </th>
            <th align=right>AVERAGE</th>
            <th align=right>$avg3</th>
            <th align=right>$avg4</th>
           </tr>";
         
 $body .= "</table>";
 
 $body .= "<form name=\"group\" action=\"index.php?cmd=handleGroup\" method=\"post\" >
          $group
          <input type=submit name=cmd2 value='Group'></form>";
 include_once("template.inc");
         
?>