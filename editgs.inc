<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

if(PrivilegeB(B10) == 'none')  { NoPriv("denied privledge to edit grades", ""); }

$gsid = $_GET['gsid'];

if($_GET['subcmd'] == 'newgs') {
	$db->get_results("INSERT INTO gs set name = 'new' ");
	$gsid = mysql_insert_id();
} else if ($_GET['subcmd'] == 'deletegs') {
	$db->get_results("DELETE FROM gs where id = '{$gsid}' ");
	$db->get_results("DELETE FROM gs_grades where gsid = '{$gsid}' ");
	$gsid = '';
} else if ($_GET['subcmd'] == 'newgrd') {
	$ord = $db->get_var("SELECT max(ord) FROM gs_grades where gsid = '$gsid' ");
	$ord++;
	$db->get_results("INSERT INTO gs_grades set gsid = '$gsid', ord='$ord' ");
} else if ($_GET['subcmd'] == 'deletegrd') {
	$db->get_results("DELETE FROM gs_grades where id = '{$_GET['id']}' ");
} else if ($_GET['subcmd'] == 'save') {
	$body .= 'Save<br>';
	extract($_POST);
//	$name=$_POST['name']; $gradetype=$_POST['gradetype'];
	$db->get_results("UPDATE gs SET name='$name', gradetype='$gradetype' WHERE id='$gsid' ");
	for($i=0; $i<count($id); $i++) {
		$sql = "UPDATE gs_grades SET symbol='{$symbol[$i]}',low='{$low[$i]}',high='{$high[$i]}',val='{$val[$i]}',points='{$points[$i]}',ord='{$ord[$i]}' WHERE id='{$id[$i]}' ";
		$db->get_results("$sql");
	}
}

$gslist = $db->get_results("SELECT name, id from gs", ARRAY_A);
$gs = getOptionList($gslist, $gsid);

$newgs = "<a href='?cmd=editgs&gsid=$gsid&subcmd=newgs'>New Grade Schedule</a>";
$deletegs = "<a href='?cmd=editgs&gsid=$gsid&subcmd=deletegs' onclick=\"return confirmMsg('Should I delete this grade schedule?');\" >Delete Current Grade Schedule</a>";

$body .= <<<END
<table cellpadding="0" cellspacing="0" border="0" width="90%">
<tr>
	<td align="left" width="50%">
		<input type="button" value="Edit Grade Setup" onclick="javascript: window.location = '?cmd=editgs';" style="width: 100%;" />
	</td>
	<td align="left" width="50%">
		<input type="button" value="Edit Site Grades" onclick="javascript: window.location = '?cmd=editsite';" style="width: 100%;" />
</tr>
</table><br><br>

Select Grade Schedule: <select name=p2 onChange='window.location="?cmd=editgs&gsid="+this.value'>
	<option value=''></option>
	$gs
</select> $newgs | $deletegs<br>
END;

$gsinfo = $db->get_row("SELECT * from gs where id = '{$gsid}' ", ARRAY_A);
$gradetype = array(array("id"=>"1","name"=>"Old Standards"),array("id"=>"2","name"=>"New - Avg"));
$gtype = getOptionList($gradetype, $gsinfo['gradetype']);

$gsgrades = $db->get_results("SELECT * from gs_grades where gsid = '{$gsid}' ", ARRAY_A);
$new = "<a href='?cmd=editgs&gsid=$gsid&subcmd=newgrd'>New Symbol Entry</a>";
$grds .= "$new<br>
<table><tr><th>symbol</th><th>High</th><th>Low</th><th>Value</th><th>GPA Points</th><th>Order</th></tr>";
foreach($gsgrades as $g) {
	$d = "<a href='?cmd=editgs&gsid=$gsid&subcmd=deletegrd&id={$g['id']}' onclick=\"return confirmMsg('Should I delete this entry?');\" >D</a>";
	$grds .= "<tr><td><input type=hidden name=id[] value='{$g['id']}'>
					<input type=text name=symbol[] value='{$g['symbol']}' size=5>
				</td><td><input type=text name=high[] value='{$g['high']}' size=5></td>
				<td><input type=text name=low[] value='{$g['low']}' size=5></td>
				<td><input type=text name=val[] value='{$g['val']}' size=5></td>
				<td><input type=text name=points[] value='{$g['points']}' size=5></td>
				<td><input type=text name=ord[] value='{$g['ord']}' size=5></td>
				<td>$d</td></tr>";
}
$grds .= "</table>";

$body .= <<<END
<form action=?cmd=editgs&gsid=$gsid&subcmd=save method=post>
Name: <input type=text name=name value='{$gsinfo['name']}'>
Grading Type: <select name=gradetype><option value=''></option>$gtype</select><br>

<br>
$grds
<input type=submit value=submit name=submit>
</form>
END;
include ("template.inc");

?>
