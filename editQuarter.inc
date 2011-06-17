<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


if(PrivilegeB(B11) == 'none') { NoPriv("denied Quarter Information"); }

if($_POST['button'] == 'Save') {
	$body .= "<font color=red>Values are saved</font>";
	$yearArray = $_POST['year'];
	$quarterArray = $_POST['quarter'];
	$startArray = $_POST['start'];
	$finishArray = $_POST['finish'];
	for($i=0; $i < count($yearArray) ; $i++) {
		$year = $yearArray[$i];
		$quarter = $quarterArray[$i];
		$start = $startArray[$i];
		$finish = $finishArray[$i];
		
		$sql = "UPDATE quarters set start = '$start', finish = '$finish'
				where year = '$year' and quarter = '$quarter'
				";
//		echo $sql . "<br><br>";
		$db->get_results($sql);
	}
} else if ($_POST['button'] == 'Add Entry') {
	$year = $_POST['year'];
	$quarter =$_POST['quarter'];
	$start = $_POST['start'];
	$finish = $_POST['finish'];

	$sql = "INSERT quarters set start = '$start', finish = '$finish', year = '$year', quarter = '$quarter' ON DUPLICATE KEY UPDATE start = '$start', finish = '$finish'
			";
	$db->get_results($sql);
	$body .= "<font color=red>New Entry Created or Updated</font>";

} else if ($_GET['button'] == 'Delete') {
	$body .= "<font color=red>Entry Deleted</font>";
	$year = $_GET['year'];
	$quarter =$_GET['quarter'];

	$sql = "DELETE FROM quarters where year='$year' and quarter='$quarter'
			";
	$db->get_results($sql);
}

$body .= selectEditStdMenu();

$qs = $db->get_results("select * from quarters order by year, quarter ");

$body .= "<form name=std action='.?cmd=editQuarter' method = post>
<table border=1 width=600><tr><th>Year</th><th>Quarter</th><th>Start</th><th>finish</th><th>&nbsp;</th></tr>";
$s = 12;
foreach($qs as $row) {
	$year = $row->year;
	$quarter = $row->quarter;
	$start = $row->start;
	$finish = $row->finish;
	$button = "<a href='index.php?cmd=editQuarter&year=$year&quarter=$quarter&button=Delete'>Delete</a>";
	
	$body .= "<tr valign=top>
		<td>$year <input type=hidden name=year[] value='$year'></td>
		<td>$quarter<input type=hidden name=quarter[] value='$quarter'></td>
		<td><input type=text name=start[] value='$start' size=$s></td>
		<td><input type=text name=finish[] value='$finish' size=$s></td>
		<td>$button</td>
		</tr>";

}

$body .= "</table>
<input type=submit name=button value=Save> <input type=reset name=button value='Reset Values'>
</form><br><br>";

$body .= <<<END
	<form name=std action='.?cmd=editQuarter' method = post>
		Year: <input type=text name=year >
		Quarter: <input type=text name=quarter ><br>
		Start: <input type=text name=start >
		Finish: <input type=text name=finish ><br>
		<input type=submit name=button value='Add Entry'>
	</form>
END;

include ("template.inc");


?>
