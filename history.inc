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
					
	$subjectIDOption = "<select name=\"subject\">
						<option value=\"\" " . selected("", $subjectID) . ">All Content Areas</option>
						<option value=\"CS\" " . selected("CS", $subjectID) . ">Career Skills</option>
						<option value=\"CA\" " . selected("CA", $subjectID) . ">Cultural Awareness</option>
						<option value=\"LS\" " . selected("LS", $subjectID) . ">Life Skills</option>
						<option value=\"MA\" " . selected("MA", $subjectID) . ">Math</option>
						<option value=\"RE\" " . selected("RE", $subjectID) . ">Reading</option>
						<option value=\"SC\" " . selected("SC", $subjectID) . ">Science</option>
						<option value=\"SS\" " . selected("SS", $subjectID) . ">Social Studies</option>
						<option value=\"TE\" " . selected("TE", $subjectID) . ">Technology</option>
						<option value=\"WR\" " . selected("WR", $subjectID) . ">Writing</option>
					  </select>";
					
	$levelOption = "<select name=\"level\">
					<option value=\"\" " . selected("", $lvlID) . ">All Levels</option>
					<option value=\"0\" " . selected("0", $lvlID) . ">0</option>
					<option value=\"1\" " . selected("1", $lvlID) . ">1</option>
					<option value=\"2\" " . selected("2", $lvlID) . ">2</option>
					<option value=\"3\" " . selected("3", $lvlID) . ">3</option>
					<option value=\"3A\" " . selected("3A", $lvlID) . ">3A</option>
					<option value=\"3G\" " . selected("3G", $lvlID) . ">3G</option>
					<option value=\"3U\" " . selected("3U", $lvlID) . ">3U</option>
					<option value=\"4\" " . selected("4", $lvlID) . ">4</option>
					<option value=\"4A\" " . selected("4A", $lvlID) . ">4A</option>
					<option value=\"4G\" " . selected("4G", $lvlID) . ">4G</option>
					<option value=\"4U\" " . selected("4U", $lvlID) . ">4U</option>
					<option value=\"5\" " . selected("5", $lvlID) . ">5</option>
					<option value=\"5A\" " . selected("5A", $lvlID) . ">5A</option>
					<option value=\"5G\" " . selected("5G", $lvlID) . ">5G</option>
					<option value=\"5U\" " . selected("5G", $lvlID) . ">5U</option>
					<option value=\"5E\" " . selected("5E", $lvlID) . ">5E</option>
					<option value=\"5L\" " . selected("5L", $lvlID) . ">5L</option>
					<option value=\"5P\" " . selected("5P", $lvlID) . ">5P</option>
					<option value=\"6\" " . selected("6", $lvlID) . ">6</option>
					<option value=\"6A\" " . selected("6A", $lvlID) . ">6A</option>
					<option value=\"6G\" " . selected("6G", $lvlID) . ">6G</option>
					<option value=\"6U\" " . selected("6U", $lvlID) . ">6U</option>
					<option value=\"6E\" " . selected("6E", $lvlID) . ">6E</option>
					<option value=\"6L\" " . selected("6L", $lvlID) . ">6L</option>
					<option value=\"6P\" " . selected("6P", $lvlID) . ">6P</option>
					<option value=\"7\" " . selected("7", $lvlID) . ">7</option>
					<option value=\"7A\" " . selected("7A", $lvlID) . ">7A</option>
					<option value=\"7G\" " . selected("7G", $lvlID) . ">7G</option>
					<option value=\"7U\" " . selected("7U", $lvlID) . ">7U</option>
					<option value=\"7E\" " . selected("7E", $lvlID) . ">7E</option>
					<option value=\"7L\" " . selected("7L", $lvlID) . ">7L</option>
					<option value=\"7P\" " . selected("7P", $lvlID) . ">7P</option>
					<option value=\"8\" " . selected("8", $lvlID) . ">8</option>
					<option value=\"8A\" " . selected("8A", $lvlID) . ">8A</option>
					<option value=\"8G\" " . selected("8G", $lvlID) . ">8G</option>
					<option value=\"8U\" " . selected("8U", $lvlID) . ">8U</option>
					<option value=\"9\" " . selected("9", $lvlID) . ">9</option>
					<option value=\"10\" " . selected("10", $lvlID) . ">10</option>
					<option value=\"11\" " . selected("11", $lvlID) . ">11</option>
					<option value=\"12\" " . selected("12", $lvlID) . ">12</option>
				</select>";
	
	$studentOption = "<select name=\"student\">
					<option value=\"\" " . selected("", $student) . ">All Students</option>
					$studentListOptions
					</select>";
					
	$header =<<<END
		<style type="text/css">
		@import "$base/jquery.datepick.package/jquery.datepick.css";
		</style>
		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
		<script type="text/javascript" src="$base/jquery.datepick.package/js/jquery.datepick.js"></script>
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

	$base = "https://dart.bssd.org/";
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
		Toggle Type: <select name=toggletype>
			<option value=''>None</option>
			<option value='comment' $toggle_comment>comment</option>
			<option value='std' $toggle_std>std</option>
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
					   <input type=hidden name=cmd value=history>
					   $startend<br>
					   $uIDOption
					   $studentOption
					   $subjectIDOption
					   $levelOption
					   <input type=submit name=submit>
				   </form>";

}

$title = "History";

$historyObj = getEntries($start, $limit, $studentID, $uID, $subjectID, $lvlID, $site, $startOutput, $endOutput, $toggletype);
$total = $historyObj['total'];
$history = $historyObj['list'];
$body = "Entire History<br>";
$body .= "<a href=index.php?cmd=history&limit=$limit&start=$start&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID>Page</a> | 
		  <a href=index.php?cmd=count>Count Screen</a><br>";
$body .= "<br>$selection<br><table border=1>";
$body .= "<tr><td>Timestamp</td><td>Type</td><td>User</td><td>Subject</td><td>Level</td><td>Std</td><td>Value</td><td>StudentID</td></tr>";
for ($i = 0; $i < count($history); $i++) {
   $dt = date('m/d/y H:i', $history[$i]['timestamp']);
   $user = $history[$i]['userid']. " - " . $history[$i]['name'];
   $type = $history[$i]['type'];
   $val = $history[$i]['value'];
   $subject = $history[$i]['subject'];
   $lvl = $history[$i]['lvl'];
   $std = $history[$i]['std'];
   $student = "{$history[$i]['fname']} {$history[$i]['lname']}<br>({$history[$i]['studentID']})";
//   echo ("<br>". print_r($history[$i]));
   $body .= "<tr><td>$dt</td><td>$type</td><td>$user</td><td>$subject</td><td>$lvl</td><td>$std</td><td>$val</td><td nowrap>$student</td></tr>";
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


include ("template.inc");

?>
