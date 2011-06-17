<?php


$listid = $_GET['listid'];
$quarter = $_GET['quarter'];


include ("rrprofileFunction.inc");

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
$students = getSFAStudents($listid);
$teachers = getTeachers();

foreach ($students['list'] as $stu) {
  $name = $stu->lname . ", " . $stu->fname;
  $grade = $stu->grade;
  $id = $stu->studentid;
  if($quarter=='first') { $reading = $teachers[$students['score'][$id]['first_reading']]['name']; }
  if($quarter=='second') { $reading = $teachers[$students['score'][$id]['second_reading']]['name']; }
  if($quarter=='third') { $reading = $teachers[$students['score'][$id]['third_reading']]['name']; }
  if($quarter=='fourth') { $reading = $teachers[$students['score'][$id]['fourth_reading']]['name']; }
  debugPrint("LISTID: $listid NAME: $name<br>");
  $body .= "<DIV style=\"page-break-after:always\">";
  $body .= rrprofile($quarter, $name, $grade, $rr, $reading, $tardies, $absenses);
  $body .= "</DIV><hr>";
}

echo $body;

?>