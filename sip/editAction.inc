<?php

$aid = $_GET['aid'];
$sid = $_GET['sid'];
$area = $_GET['area'];
 
$sql = "select * from sipaction where aid = '$aid' ";
$results = $db->get_results($sql, ARRAY_A);

while(list($name, $val) = each($results[0])) {
	${$name} = $val;
}

if($_POST['button'] == 'Save') {
	while(list($name, $val) = each($_POST)) {
		${$name} = $val;
	}
	
	if($aid != '') {
		$sql = "UPDATE sipaction SET action='$action', person='$person', ptype='$ptype', timeline = '$timeline', eval = '$eval', final = '$final' where aid = '$aid'";
	} else {
		$sql = "INSERT sipaction SET action='$action', person='$person', ptype='$ptype', timeline = '$timeline', eval = '$eval', final = '$final', area = '$area', sid = '$sid' ";
	}
	echo $sql;

	$db->get_results($sql);
  	echo "<script>
		  window.opener.location.reload(true);
		  window.close(); 
	 </script>";

}

${"ptype_" . str_replace (" ", "_", $ptype) } = "selected";

$options = <<<END
	<option value="" $ptype_></option>
	<option value="teacher" $ptype_teacher>Teacher</option>
	<option value="Parapro" $ptype_Parapro>Parapro</option>
	<option value="Administrator" $ptype_Administrator>Administrator</option>
	<option value="Facilitator" $ptype_Facilitator>Facilitator</option>
	<option value="Parent liaison" $ptype_Parent_liaison>Parent Liaison</option>
	<option value="Principal" $ptype_Principal>Principal</option>
	<option value="Other" $ptype_Other>Other</option>
	<option value="staff" $ptype_staff>Old Value [staff]</option>
	<option value="parent" $ptype_parent>Old Value [parent]</option></select>
END;

$r = 6;
$c = 40;
$s = 40;
$url = $_SERVER[PHP_SELF] . "?module=sip&cmd=editAction";

echo <<<END
	<form action=$url method=post>
	<input type=hidden name=aid value='$aid'>
	<input type=hidden name=area value='$area'>
	<input type=hidden name=sid value='$sid'>
	
	<table border=0 >
		<tr valign=top>
			<td>Smart Plan: </td><td><textarea rows=$r cols=$c name=action>$action</textarea></td>
		</tr>
		<tr valign=top>
			<td>Evaluation: </td><td><textarea  rows=$r cols=$c name=eval>$eval</textarea></td>
		</tr>
	</table>
	<input type=submit name=button value=Save><button onClick=javascript:window.close()>Cancel</button>
	</form>
END;

?>