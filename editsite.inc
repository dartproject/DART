<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

if(PrivilegeB(B10) == 'none')  { NoPriv("denied privledge to edit grades", ""); }

$site = $_GET['site'];
$sites = getSitesOptions($site);

if($_GET['subcmd'] == 'new') {
	$db->get_results("INSERT INTO gs_select set siteid = '$site', lowgrade='-3', highgrade='-3' ");
} else if ($_GET['subcmd'] == 'delete') {
	$db->get_results("DELETE FROM gs_select where id = '{$_GET['id']}' ");
} else if ($_GET['subcmd'] == 'save') {
	$body .= 'Save<br>';
	$g = $_POST['gsid']; $l = $_POST['low']; $h = $_POST['high']; $id = $_POST['gid'];
	for($i=0; $i<count($id); $i++) {
		$sql = "UPDATE gs_select SET gsid='{$g[$i]}',lowgrade='{$l[$i]}',highgrade='{$h[$i]}' WHERE id='{$id[$i]}' ";
		$db->get_results("$sql");
	}
}

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

Select Site: <select name=p2 onChange='window.location="?cmd=editsite&site="+this.value'>
	<option value=''></option>
	$sites
</select>
END;
 
$select = $db->get_results("SELECT * FROM gs_select where siteid = '$site' ", ARRAY_A);
$grades = array(array("id"=>"-2","name"=>"PPK"),array("id"=>"-1","name"=>"PK"),array("id"=>"0","name"=>"K"),array("id"=>"1","name"=>"1"),array("id"=>"2","name"=>"2"),array("id"=>"3","name"=>"3"),array("id"=>"4","name"=>"4"),array("id"=>"5","name"=>"5"),array("id"=>"6","name"=>"6"),array("id"=>"7","name"=>"7"),array("id"=>"8","name"=>"8"),array("id"=>"9","name"=>"9"),array("id"=>"10","name"=>"10"),array("id"=>"11","name"=>"11"),array("id"=>"12","name"=>"12"),array("id"=>"13","name"=>"12+"));
$new = "<a href='?cmd=editsite&site=$site&subcmd=new'>New Grade Schedule For Site</a>";
$body .= " $new<br><br>
<form action=?cmd=editsite&site=$site&subcmd=save method=post>
<table>";
$gslist = $db->get_results("SELECT name, id from gs", ARRAY_A);
foreach($select as $s) {
	$gs =  getOptionList($gslist, $s['gsid']);
	$low = getOptionList($grades, $s['lowgrade']);
	$high = getOptionList($grades, $s['highgrade']);
	$d = "<a href='?cmd=editsite&site=$site&subcmd=delete&id={$s['id']}' onclick=\"return confirmMsg('Should I delete this entry?');\" >D</a>";
	$body .= "<tr><td><input type=hidden name=gid[] value='{$s['id']}'><select name=gsid[]><option value=''></option>$gs</select>
				</td><td><select name=low[]><option value='-3'></option>$low</select></td>
				<td><select name=high[]><option value='-3'></option>$high</select></td>
				<td>$d</td></tr>";
}


$body.="</table><br><input type=submit name=submit value=submit></form>";

include ("template.inc");

?>
