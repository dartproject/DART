<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$val = $_POST['studentID'];
$listid =  $_POST['listid'];
$month =  $_POST['month'];
$year =  $_POST['year'];
$day =  $_POST['day'];
$period =  $_POST['period'];
$code =  $_POST['selectCode'];

//print_r($val);

 $uval = array_unique($val); // gets rid of duplicate entries
//echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editlist&p1=$lid\"> ");

foreach ( $uval as $id) {
 	  $info = explode(" ", $id);
// 	  print_r($id);
      $id = $info[0];
      $site = $info[1];
	$sql = "DELETE FROM AttendanceEvents 
			WHERE StudentID = $id AND Date = '$year-$month-$day' AND PeriodID = '$period'";
//	echo "DELETE: $sql<br>";
	$db->query($sql);
	$sql = "INSERT INTO AttendanceEvents (StudentID, Date, PeriodID, SiteID, CodeID) 
			VALUES ($id, '$year-$month-$day', '$period', '$site', '$code')";
	$db->query($sql);
//	echo "INSERT: $sql<br>";

}

 echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=AttendanceList&listid=$listid&year=$year&month=$month&day=$day&period=$period\">");
 
 ?>
