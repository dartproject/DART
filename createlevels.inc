<?php

$sel = $_GET['sel'];

$selectList .= "
<script>
function handleThis(value) {
//	alert('test');
   window.location='index.php?cmd=createlevels&sel=' + value;
}
</script>
";

$electives = $db->get_results("SELECT * from subjects ", ARRAY_A);

$selectList .= "<select name=listid onChange='javascritp:handleThis(this.value);'>
<option value=''>--</option>";

foreach($electives as $el) {
  $id = $el['id'];
  $select = ($id == $sel) ? "selected": "";
  $selectList .= "<option value=\"$id\" $select>$id</option>";
  }
$selectList .= "</select>";


$body .= selectEditStdMenu();

$body .= <<<END
$selectList
Create/Edit Level<br>
	<form action='' method=post>
		<table>
			<tr>
				<td>Level: <input type=text name=level size=2></td>
				<td>Name: <input type=text name=name></td>
				<td>Weight: <input type=text name=weight size=3></td>
				<td>
					<input type=submit name=button value=Create>
				</td>
			</tr>
		</table>
	</form>

END;

if($_POST['button'] == 'Create') {
	$db->get_results("INSERT INTO level set subject = '$sel', name = '{$_POST['name']}',weight = '{$_POST['weight']}', level = '{$_POST['level']}'  ");
} else if($_POST['button'] == 'Save') {
	$levels = $_POST['levels'];
	$names = $_POST['names'];
	$weights = $_POST['weights'];
	for($i = 0; $i < count($levels); $i++) {
		$sql = "UPDATE level set name = '{$names[$i]}', weight='{$weights[$i]}' WHERE subject = '{$sel}' and level = '{$levels[$i]}' ";
//		echo $sql;
		$db->get_results($sql);
	}
}
$electives = $db->get_results("SELECT * from level where subject = '$sel' ", ARRAY_A);
$body .= "<form action='' method=post><table border=1><tr><th>Level</th><th>Name</th><th>Weight</th></tr>";
foreach($electives as $el) {
	$body .= "<tr><td>{$el['level']}</td>
				<td>
					<input type=text name=names[] value='{$el['name']}'>
					<input type=hidden name=levels[] value='{$el['level']}'>
				</td>
				<td><input type=text name=weights[] value='{$el['weight']}' size=3></td>
				
			</tr>";
}
$body .= "</table><input type=submit name=button value=Save>";

include ("template.inc");

?>
