<?php

  include_once ("./lib/machine.config.php");
  include_once ("./lib/config.inc");
  include_once ("./lib/ez_sql.php");
  include_once ("./lib/function.inc");

$repair = $_GET['repair'];

$sql = "SELECT *
        FROM studentlevel
        WHERE studentlevel.progress LIKE '%ERR%'";

//echo("<br>ERROR Student Query: $sql<br>");

if($repair == 'on') {
echo("<br>---- UPDATE EROORS ---- <br>");
        
   $results = $db->get_results($sql);
   foreach ($results as $res) {
	  $id = $res->studentid;
	  $sub = $res->subject;
	  $lvl = $res->level;
	  updateSingleLevelScore($id, $sub, $lvl);
	  echo "Student, Subject, Level ($id, $sub, $lvl) : " . $res->fname . " " . $res->lname . "<br>";
   }

   echo("<br>---- LEFT OVER EROORS ---- <br>");

} else {
   echo("<br>---- CURENT STUDENTS WITH EROORS ---- <br>");
}        
   $results = $db->get_results($sql);
   foreach ($results as $res) {
	  $id = $res->studentid;
	  $sub = $res->subject;
	  $lvl = $res->level;
//	  updateSingleLevelScore($id, $sub, $lvl);
	  echo "Student, Subject, Level ($id, $sub, $lvl) : " . $res->fname . " " . $res->lname . "<br>";
   }
   
echo "<br><a href='cleanup.php?repair=on'>Click here to run updateon Errors</a>
      <br><br><a href='cleanup.php'>Click here to see which students have Errors</a>"

?>