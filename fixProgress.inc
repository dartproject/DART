<?php
include_once ("lib/stopwatch.inc");

function runFix () {
  global $db;
  
   $size = 5000;
  
   echo ("HERE");
   set_time_limit(0);
   $stopwatch = new stopwatch;
   $sql = "truncate table repair";
   $results = $db->query($sql);
   echo ("<br>$sql<br>");
   
   $sql = "select count(student.studentid) as count from studentlevel, student where student.status = \"Active\" and student.studentid = studentlevel.studentid";
   $results = $db->get_results($sql, ARRAY_A);  
   $ct = $results[0]['count'];
//   $ct = 49;
  echo ("COUNT: $ct<br>");
  $i = 0;
  for ($j = 0; $j < $ct; $j = $j + $size) {
      $stopwatch->lap("($i)");
      $top = $j+$size-1;		  
	  $sql = "select *, student.studentid as id from studentlevel, student where student.status = \"Active\" and student.studentid = studentlevel.studentid limit $j, $size";
	  echo("<br>$sql<br>");
	   $results = $db->get_results($sql);
	   foreach ($results as $res) {
		  echo (fmod($i++, 100) == 0 ? "<br>." : ".");
		  $id = $res->id;
		  $sub = $res->subject;
		  $lvl = $res->level;
		  updateSingleLevelScore($id, $sub, $lvl);
/***
          $score = updateOverall ($id, $sub, $lvl);
		  $sql = "INSERT into repair
						SET studentid='$id',
							subject='$sub',
							level = '$lvl',
							progress='$score'";
		  $db->get_results($sql);
****/
	   }
	}
    $stopwatch->lap("Final ($i)");
	echo ("<br>Timing: " . $stopwatch->getText());
}

runFix();

/******
update studentlevel, fixRepair set studentlevel.progress = fixRepair.progress where studentlevel.studentid = fixRepair.studentid and studentlevel.subject = fixRepair.subject and studentlevel.level = fixRepair.level
*******/
?>
