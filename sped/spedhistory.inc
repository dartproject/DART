<?php

// ==================================================================

//  Author: Robert Joseph (dart@vizmotion.com)

//	 Web: http://wiki.bssd.org/index.php/DART_System

// ==================================================================





$uID = $_GET['user'];

$subjectID = $_GET['subject'];

$lvlID = $_GET['level'];

$studentID = ($currentStudentID == '') ? $_GET['student']: $currentStudentID;



$start = setIfNeeded($_GET['start'], 0);

$limit = setIfNeeded($_GET['limit'], 50);



$startOutput = $_GET['startOutput'];

$endOutput = $_GET['endOutput'];

$site = $_GET['site'];

$toggletype = $_GET['toggletype'];

//$startdate = '1270094400';

//$enddate = '1272772800';

//$site = 'UNK';



$Display = Privilege(A10);





if($Display != 'none') {

  $site = $Display == 'site' ? $currentMySite : "$site";

	$studentList = getPotentialListItems($uID, $Display);

	$studentListOptions = showListOptional($studentList, $studentID);



    $userList = getAllUsers($site);

    $userListOptions = getOptionList($userList, $uID);



	$uIDOption = "<select name=\"user\">

					<option value=\"\" " . selected("", $uID) . ">All Users</option>

					$userListOptions

					</select>";

					

	$studentOption = "<select name=\"student\">

					<option value=\"\" " . selected("", $student) . ">All Students</option>

					$studentListOptions

					</select>";

					

	$header =<<<END

		<style type="text/css">

		@import " $rootURL /js/jquery.datepick.package/jquery.datepick.css";

		</style>

		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>

		<script type="text/javascript" src=" $rootURL /js/jquery.datepick.package/jquery.datepick.js"></script>

		<style type="text/css">

			@import "http://keith-wood.name/css/jquery.datepick.css";

		</style>

		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>

		<script type="text/javascript" src="http://keith-wood.name/js/jquery.datepick.js"></script>	<script>

		$(function() {

			$('#startdate').datepick();

			$('#enddate').datepick();

		});

	</script>

END;



	

	$options = getSitesOptions($site);

	${"toggle_".$_GET['toggletype']} = 'selected';



	$startend =<<<END

		Start: <input id=startdate type=text name=startdate value='{$_GET['startdate']}'>

				<input id=startOutput type=hidden name=startOutput  value='{$_GET['startOutput']}'> 

		END: <input id=enddate type=text name=enddate value='{$_GET['enddate']}'> 

				<input id=endOutput type=hidden name=endOutput  value='{$_GET['endOutput']}'> 

		Site: <select name=site>

		<option value=''>District Wide</option>

		$options

		</select>

		<script>

		$('#startdate').datepick({onSelect: reformatDate}); 

		 

		function reformatDate() { 

			$('#startOutput').val($.datepick.formatDate( 

				"@", $('#startdate').datepick('getDate')[0])); 

		}

	

		$('#enddate').datepick({onSelect: reformatDateEnd}); 

		function reformatDateEnd() { 

			$('#endOutput').val($.datepick.formatDate( 

				"@", $('#enddate').datepick('getDate')[0])); 

		}

	

		</script>

END;



	$selection .= "$header

				<form action=index.php method=get>

					   <input type=hidden name=module value=sped>
					   
					   <input type=hidden name=cmd value=spedhistory>

					   $startend
					   
					   $uIDOption<br>


					   $studentOption


					   <input type=submit name=submit>

				   </form>";



}



$title = "History";



$historyObj = getSpedEntries($start, $limit, $studentID, $uID, $site, $startOutput, $endOutput, "spedupdate");

$total = $historyObj['total'];

$history = $historyObj['list'];

$body = "Entire History<br>";

$body .= "<a href=index.php?cmd=history&limit=$limit&start=$start&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID>Page</a> | 

		  <a href=index.php?cmd=count>Count Screen</a><br>";

$body .= "<br>$selection<br><table border=1>";

$body .= "<tr><td>Timestamp</td><td>Type</td><td>User</td><td>Site</td><td>Value</td><td>StudentID</td></tr>";

for ($i = 0; $i < count($history); $i++) {

   $dt = date('m/d/y H:i', $history[$i]['timestamp']);

   $user = $history[$i]['userid']. " - " . $history[$i]['name'];

   $type = $history[$i]['type'];

   $val = $history[$i]['p2'];

   $site = $history[$i]['site'];


   $student = "{$history[$i]['fname']} {$history[$i]['lname']}<br>({$history[$i]['studentID']})";

//   echo ("<br>". print_r($history[$i]));

   $body .= "<tr><td>$dt</td><td>$type</td><td>$user</td><td>$site</td><td>$val</td><td nowrap>$student</td></tr>";

}

$body .= "</table>";

if($start+$limit > $total) {

  $nextstart = $start;

} else {

  $nextstart = $start+$limit;

}

if($start-$limit > 0) {

  $prevstart = $start-$limit;

} else {

  $prevstart = $start;

}



$setLimit = "<form method=get action=index.php>

<input type=hidden name='cmd' value='history'>

<input type=hidden name='start' value=0>

<input type=hidden name=student value='$studentID'>

<input type=hidden name=lvl value='$lvlID'>

<input type=hidden name=subject value='$subjectID'>

<input type=hidden name=user value='$uID'>

<input type=text name=limit size=4 value=$limit>

<input type=submit value='Display Limit'>

</form>";

$final = min($start+$limit-1, $total);

$next = "<a href=" . "index.php?cmd=history&limit=$limit&start=$nextstart&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID" . ">Next</a>";

$prev = "<a href=" . "index.php?cmd=history&limit=$limit&start=$prevstart&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID" . ">Prev</a>";

$body .= "<table><tr><td>Total: $total Viewing $start - $final $prev $next </td><td>$setLimit</td></tr></table>";




function getSpedEntries ($start=0, $limit=30, $student="", $user="", $site="", $starttime="",$endtime="", $toggletype='') {

          global $db;

        
		  $clause2 = "history.p1 = student.studentid ";
          $clause = whereClause("history.userID", $clause, $user, "'");

          $clause = whereClause("history.p1", $clause, $student, "'");

          $clause = whereClause("history.userID", $clause, "user.userid");

          $clause2 = whereClause("student.site", $clause2, $site, "'");

          $clause = comparisonClause("history.type", $clause, $toggletype,"=", "'");

          $clause = comparisonClause("timestamp", $clause, $starttime,">", "'");

          $clause = comparisonClause("timestamp", $clause, $endtime,"<", "'");

//          echo $clause;

          $sqlcount = "select count(*) as num from history, user where $clause";

          debugPrint ("SQL Count: " . $sqlcount . "<br>");

          $res1 = $db->get_results($sqlcount); 

//          print_r($res1);

          $total = $res1[0]->num;

          debugPrint ("SQL Total: " . $total . "<br>");

          $sql = "select *, history.p1 as studentID from (history, user)

          		LEFT JOIN student ON  $clause2

          		WHERE $clause";

          $sql .= " order by timestamp desc LIMIT $start, $limit";

          debugPrint ("SQL LIMIT: " . $sql . "<br>");

          $res2 = $db->get_results($sql, ARRAY_A); 

          $results['list'] = $res2;

          $results['total'] = $total;

          return ($results);         

        }


include ("template.inc");



?>

