<?php

$body .= selectEditStdMenu();

$body .= <<<END
Create/Edit Subject<br>
	<form action='' method=post>
		<table>
			<tr>
				<td>ID: <input type=text name=id size="2" maxlength="2" ></td>
				<td>Name: <input type=text name=name></td>
				<td>
					<input type=submit name=button value=Create>
				</td>
			</tr>
		</table>
	</form>

END;

if($_POST['button'] == 'Create') {
	$db->get_results("INSERT INTO subjects set id = '{$_POST['id']}', name = '{$_POST['name']}' ");
} else if($_POST['button'] == 'Save') {
	$ids = $_POST['ids'];
	$names = $_POST['names'];
	for($i = 0; $i < count($ids); $i++) {
		$sql = "UPDATE subjects set name = '{$names[$i]}' WHERE id = '{$ids[$i]}' ";
//		echo $sql;
		$db->get_results($sql);
	}
}
$electives = $db->get_results("SELECT * from subjects where core <>'x'", ARRAY_A);
$body .= "<form action='' method=post><table border=1><tr><th>ID</th><th>Name</th></tr>";
foreach($electives as $el) {
	$body .= "<tr><td>{$el['id']}</td>
				<td>
					<input type=text name=names[] value='{$el['name']}'>
					<input type=hidden name=ids[] value='{$el['id']}'>
				</td></tr>";
}
$body .= "</table><input type=submit name=button value=Save>";
include_once("template.inc");
?>
