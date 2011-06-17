<?php
/***
 *
//updateStudentLevelProgress();


 *$id = $_GET['id'];

$body = "We are are <a href=index.php?cmd=test>Go Back ANd Run</a>";


$a = 'district';
$b = 'site';
$d = 1;
$c = 0;

echo ("checkStudent($c, $d, $a, $b) ===> " . checkStudent($c, $d, $a, $b));
           
include("template.inc");
****/
/****
set_time_limit(0);

include_once ("lib/stopwatch.inc");


function runTest() {
     global $db;
     $list = "";
     $stopwatch = new stopwatch;     
     $i = 100;
     for ($i=0; $i<1000;$i+=100) {
     echo ("---------------- $i ----------------<br>");
          $listid = newList($currentUserID, "L_" . $i);
          
          $sql = "select * from student LIMIT 0, $i";
          $students = $db->get_results($sql);
          
          $stopwatch->lap("ran students sql", true);
      
          foreach ($students as $student) {
                   $sql = "insert into listvalues set listid = '$listid', studentid ='" . $student->studentid . "'";
                   $db->query($sql);
           }
      
          $stopwatch->lap("ran students in list", true);
      
          getListWeight ($listid);
          
          $list .= $stopwatch->lap("getListWeight", true) . ", ";
          $list2 .= "$i,";
          
          deleteList ($listid);

          $stopwatch->lap("list deleted", true);
      }
      echo ("$list<br>$list2");
}

runTest();
***/

UpdateStudents();
?>
