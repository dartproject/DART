<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

  $js = " 
function update(sid, stage) { 
  obj = document.getElementsByName(\"ch_\" + sid)[0];
  obj.value = \"x\";

}";

debugPrint("Here");
$quarter = $_GET['quarter'];
$tutor = $_GET['tutor'];
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=tutor&tutor=$tutor&quarter=$quarter&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";



switch($quarter) {
   case "first":
      $title = "Q1";
      $tutorQ = "base_tutor";
      $teacherQ = "base_reading";
      $sheader = "base_stime";
      $eheader = "base_etime";
      $rheader = "base_hlremove";
      $heading1_1 = "Baseline<br>Assessment<br>Mastery";
      $heading1_2 = "Baseline<br>Stage";
      $heading2_1 = "1st<br>Assessment<br>Mastery";
      $heading2_2 = "1st Stage";
      $h1_1 = "base_rawscore"; $h1_2 = "base_score";
      $h2_1 = "first_rawscore"; $h2_2 = "first_score";
      $search = "base";
      $sfa = "base_sfa";
      $scorevalue = "base_score";
      $expect = "base_expect";
      break;
   case "second":
      $title = "Q2";
      $tutorQ = "first_tutor";
      $teacherQ = "first_reading";
      $sheader = "first_stime";
      $eheader = "first_etime";
      $rheader = "first_hlremove";
      $heading1_1 = "1st<br>Lexile";
      $heading1_2 = "1st<br>Level<br>Conversion";
      $heading2_1 = "2nd<br>Assessment<br>Lexile";
      $heading2_2 = "2nd Assess<br>Level<br>Conversion";
      $h1_1 = "first_rawscore"; $h1_2 = "first_score";
      $h2_1 = "second_rawscore"; $h2_2 = "second_score";
      $search = "first";
      $sfa = "first_sfa";
      $scorevalue = "first_score";
      $expect = "first_expect";
      break;
   case "third":
      $title = "Q3";
      $tutorQ = "second_tutor";
      $teacherQ = "second_reading";
      $sheader = "second_stime";
      $eheader = "second_etime";
      $rheader = "second_hlremove";
      $heading1_1 = "2nd<br>Lexile";
      $heading1_2 = "2nd<br>Level<br>Conversion";
      $heading2_1 = "3rd<br>Assessment<br>Lexile";
      $heading2_2 = "3rd Assess<br>Level<br>Conversion";
      $h1_1 = "second_rawscore"; $h1_2 = "second_score";
      $h2_1 = "third_rawscore"; $h2_2 = "third_score";
      $search = "second";
      $sfa = "second_sfa";
      $scorevalue = "second_score";
      $expect = "second_expect";
      break;
   case "fourth":
      $title = "Q4";
      $tutorQ = "third_tutor";
      $teacherQ = "third_reading";
      $sheader = "third_stime";
      $eheader = "third_etime";
      $rheader = "third_hlremove";
      $heading1_1 = "3rd<br>Lexile";
      $heading1_2 = "3rd<br>Level<br>Conversion";
      $heading2_1 = "4th<br>Assessment<br>Lexile";
      $heading2_2 = "4th Assess<br>Level<br>Conversion";
      $h1_1 = "third_rawscore"; $h1_2 = "third_score";
      $h2_1 = "fourth_rawscore"; $h2_2 = "fourth_score";
      $search = "third";
      $sfa = "third_sfa";
      $scorevalue = "third_score";
      $expect = "third_expect";
      break;
   default:
      break;
}

$students = getTutorStudents($tutor, $tutorQ, $year);
$user = getUserInfo($tutor);
$tutorname = $user['name'];
//$levels = getListContentAreaStudents($listid, $search);
//$list = getListInfo($listid);
//$listname = $list['listname'];
$title .= " Tutor Profile ($tutorname)";
$hl = GetTutorHotListArray($tutor, $search, $year);

$users = getTeacherTutorHomeroom($year);


$body .= "<h2>$title</h2>$selection
         <form method=post action=index.php?module=sfa&cmd=savetutor>
         <input type=hidden name=year value='$year'>
         <input type=hidden name=tutor value='$tutor'>
         <input type=hidden name=quarter value='$quarter'>
         <input type=submit name=submit value='save home'>
         <input type=submit name=submit value='save continue'>
          <table border=1>";

$body .= "<tr bgcolor=lightgrey>
            <th>Reading Teacher</th>
            <th>Student</th>
            <th>Grade</th>
            <th>Mastery<br>Level</th>
            <th>Placement<br>Level</th>
            <th>Tutor</th>
            <th>Start<br>Time</th>
            <th>End<br>Time</th>
            <th>Hot List</th>
           </tr>";
           
 foreach ($students as $stu) {
    debugPrint("=> here");
    $id = $stu['studentid'];
    $recname = $id ."_" . $search;
    $grade = $stu['gradelevel'];
    $studentname = $stu['lname'] . ", " . $stu['fname'];
    $teacher = $users[$stu[$teacherQ]];
    $tutor = $users[$stu[$tutorQ]];
    $score = $stu[$scorevalue];
    $sfamat = $stu[$sfa];
    $stime = $stu[$sheader];
    $etime = $stu[$eheader];
    $remove = $stu[$rheader];
    $mark = ($hl[$id] == "X" and $remove != "X") ? "X" : "&nbsp;";
//    $rlevel = "RE." . $levels[$id];
    $body .=  "<tr>
				<td>" . dv($teacher) . "
				   <input type=hidden id=ch_" . $recname . " name=ch_" . $recname . " value=empty>
				</td>
				<td>$studentname</td>
				<td>$grade</td>
				<td>" . dv($score) . "</td>
				<td>" . dv($sfamat) . "</td>
				<td>" . dv($tutor) . "</td>
				<td><input type=hidden id=" . $recname . "_rec_stime name=" . $recname . "_rec_stime value=$stime>
                    <input value='$stime' size=8 type=text name=\"". $recname . "_inp_stime\" id=\"" . $recname . "_inp_stime\" onChange=\"javascript:update('$recname'); return false\"> </td>

				<td><input type=hidden id=" . $recname . "_rec_etime name=" . $recname . "_rec_etime value=$etime>
                    <input value='$etime' size=8 type=text name=\"". $recname . "_inp_etime\" id=\"" . $recname . "_inp_etime\" onChange=\"javascript:update('$recname'); return false\"> </td>

				<td align=center> $mark</td>
			   </tr>";
			   
 }

$body .= "</table>
         <input type=submit name=submit value='save home'>
         <input type=submit name=submit value='save continue'>
</form>";

           
 include_once("template.inc");
         
?>