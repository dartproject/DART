<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$uID = $_GET['user'];
$start = setIfNeeded($_GET['start'], 0);
$limit = setIfNeeded($_GET['limit'], 50);

$site = Privilege(A10) == 'site' ? $currentMySite : "";

$userList = getAllUsers($site);
$userListOptions = getOptionList($userList, $uID);


$uIDOption = "<select name=\"user\">
				<option value=\"\" " . selected("", $uID) . ">All Users</option>
				$userListOptions
				</select>";
				

$selection .= "<form action=index.php method=get>
				   <input type=hidden name=cmd value=historylogin>
				   $uIDOption
				   <input type=submit name=submit>
			   </form>";


$title = "History Login";

$historyObj = getLoginEntries($start, $limit, $uID, $site);
$total = $historyObj['total'];
$history = $historyObj['list'];
$body = "Entire History<br>";
$body .= "<a href=index.php?cmd=history&limit=$limit&start=$start&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID>Page</a><br>";
$body .= "<br>$selection<br><table border=1>";
$body .= "<tr><td>Timestamp</td><td>User</td><td>Type</td><td>P1</td></tr>";
for ($i = 0; $i < count($history); $i++) {
   $dt = date('m/d/y H:i', $history[$i]['timestamp']);
   $dt = $history[$i]['timestamp'];
   $user = $history[$i]['userid']. " - " . $history[$i]['name'];
   $type = $history[$i]['type'];
   $p1 = $history[$i]['p1'];
   $p2 = $history[$i]['p2'];
   $p3 = $history[$i]['p3'];
   $body .= "<tr><td>$dt</td><td>$user</td><td>$type</td><td>$p1</td><td></tr>";
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
<input type=hidden name='cmd' value='historylogin'>
<input type=hidden name='start' value=0>
<input type=hidden name=user value='$uID'>
<input type=text name=limit size=4 value=$limit>
<input type=submit value='Display Limit'>
</form>";
$final = min($start+$limit-1, $total);
$next = "<a href=" . "index.php?cmd=historylogin&limit=$limit&start=$nextstart&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID" . ">Next</a>";
$prev = "<a href=" . "index.php?cmd=historylogin&limit=$limit&start=$prevstart&user=$uID&subject=$subjectID&lvl=$lvlID&student=$studentID" . ">Prev</a>";
$body .= "<table><tr><td>Total: $total Viewing $start - $final $prev $next </td><td>$setLimit</td></tr></table>";


include ("template.inc");

?>
