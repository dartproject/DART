<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$site = $_GET['site'];

$students = getOpenStudentLevels($site);
$nextItems = getNextLevel($site);

$ct = count($students);

$priv = Privilege(A13);

if($priv == 'district') {
  $siteList = getSitesOptions($site);

  $pulldownsites = "<form method=get action=index.php>
						<input type=hidden name=cmd value=progress>
						<select name=\"site\" onChange=\"submit()\">
	  <option value=\"\" " . selected ($site, "") . ">All Locations</option>
	  $siteList 
                        </select>
                    </form>";
}

$body = "Total: $ct <br><br>$pulldownsites
        <form method=post action=index.php?cmd=updateProgress>
            <table border = 1>
               <tr><th>Student</th><th>Student<br>Number</th><th>Area</th><th>Level</th><th>Progress</th><th>Promote?</th></tr>";
               
foreach ($nextItems as $next) {
   $value = $next->nextlevel;
   $nextlevel[$next->subject][$next->level] .= "<option value=$value>$value</option>";
   debugPrint($nextlevel[$next->subject][$next->level]);
 }

foreach ($students as $stu) {
   $name = $stu['lname'] . ", " . $stu['fname'];
   $area = $stu['subject'];
   $level = $stu['level'];
   $progress = $stu['progress'];
   $id = $stu['studentid'];
   $promotename = "lvl_" . $id ."_" . $area . "_" . $level;
   
   $nextlevelOption = $nextlevel[$area][$level];
   $selection = "<select name=$promotename><option value=\"\" selected>No</option>$nextlevelOption</select>";
   
   $body .= "<tr><td><a href=index.php?cmd=toggleStudent&p1=$id>$name</a></td><td>$id</td><td>$area</td><td>$level</td><td>$progress</td><td>
$selection</td></tr>";  
  }
  
 $body .= "</table><input type=submit name=submit value=Update></form>";
include ("template.inc");
  
?>