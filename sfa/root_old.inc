<?php

$quarter = $_GET['quarter'];
$teacher = $_GET['teacher'];


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
      break;
   case "third":
      break;
   case "fourth":
      break;
   default:
      break;
}
      
$students = getSFATeacherStudents($teacher, $search);
$teacherName = $students[0]['name'];
$title .= " ($teacherName)";

$body .= "<h2>$title</h2><table border=1>";

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
    $grade = $stu['grade'];
    $student = $stu['lname'] . ", " . $stu['fname'];
    $rlevel = "";
    $sfamat = "";
    $firstscore = $stu[$h1_1];
    $firstconversion = $stu[$h1_2];
    $secondscore = $stu[$h2_1];
    $secondconversion = $stu[$h2_2];
    $lexneeded = "";
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
				<td>" . dv($rlevel) . "</td>
				<td>" . dv($sfamat) . "</td>
				<td>" . dv($firstscore) . "</td>
				<td>" . dv($firstconversion) . "</td>
				<td>" . dv($secondscore) . "</td>
				<td>" . dv($secondconversion) . "</td>
				<td>" . dv($lexneeded) . "</td>
				<td>" . dv($gmade) . "</td>
				<td>" . dv($gneeded) . "</td>
			   </tr>";
           
 }

$avg1 = round($total1/$i, 2);
$avg2 = round($total2/$i, 2);
$avg3 = round($total3/$i, 2);
$avg4 = round($total4/$i, 2);

$body .= "<tr bgcolor=lightgrey>
            <th> </th>
            <th> </th>
            <th> </th>
            <th>TOTAL</th>
            <th>$total1</th>
            <th>TOTAL</th>
            <th>$total2</th>
            <th> </th>
            <th>TOTAL</th>
            <th>$total3</th>
            <th>$total4</th>
           </tr>";
$body .= "<tr bgcolor=lightgrey>
            <th> </th>
            <th> </th>
            <th> </th>
            <th>AVERAGE</th>
            <th>$avg1</th>
            <th>AVERAGE</th>
            <th>$avg2</th>
            <th> </th>
            <th>AVERAGE</th>
            <th>$avg3</th>
            <th>$avg4</th>
           </tr>";
         
 $body .= "</table>";
 
 include_once("template.inc");
         
?>