<?php
  $id = $_GET['id'];
  $area = $_GET['area'];
  $oldarea = strtolower(substr($area, 0, 1));
//  $ptypeList = array("" => "", "teacher" => "teacher", "parent" => "parent", "staff" => "staff");
//  $value = "Test";
  $ptypeList = array(
		array("id"  => "", "name" => ""),
		array("id"  => "teacher", "name" => "Teacher"),
		array("id"  => "Parapro", "name" => "Parapro"),
		array("id"  => "Administrator", "name" => "Administrator"),
		array("id"  => "Facilitator", "name" => "Facilitator"),
		array("id"  => "Parent liaison", "name" => "Parent Liaison"),
		array("id"  => "Principal", "name" => "Principal"),
		array("id"  => "Other", "name" => "Other"),
		array("id"  => "staff", "name" => "Old Value [staff]"),
		array("id"  => "parent", "name" => "Old Value [parent]")
	);	
  $sql = "select * from sipaction where sid = '$id' and (area='$area' or area ='$oldarea')";
  $results = $db->get_results ($sql);
  $i = 0;
  foreach ($results as $res) {
    $aid = $res->aid;
	$ptypeOptions = "<select name=\"kind[]\">" . 
                       GetOptionList($ptypeList, $res->ptype) . 
                       "</select>";
/*
	$row .= "<tr>
		<td><input size = 2 type=hidden name=id[] value=\"" . $res->aid . "\" />
		<a href=\"index.php?module=sip&cmd=deleteAction&area=$area&sid=$id&aid=" . $res->aid . "\">D</a>
		</td>
		<td><input size = 10 type=text name=action[] value=\"" . $res->action . "\" /></td>
		<td><input  size = 7 type=text name=person[] value=\"" . $res->person . "\" /></td>
		<td>
			$ptypeOptions
		</td>
		<td><input  size = 7 type=text name=timeline[] value=\"" . $res->timeline . "\" /></td>
		<td><input  size = 12 type=text name=eval[] value=\"" . $res->eval . "\" /></td>
		<td><input  size = 12 type=text name=final[] value=\"" . $res->final . "\" /></td>		
	</tr>";
*/
    $row .= "<tr valign=top style=\"font-size: 12px;\">
		<td width=40px>
		<a onClick='javascript:return confirmMsg(\"Delete this entry?\");' href=\"index.php?module=sip&cmd=deleteAction&area=$area&sid=$id&aid=" . $res->aid . "\">Delete</a> 
<a href=\"javascript:popUp('index.php?module=sip&cmd=editAction&aid=" . $res->aid . "', 550, 480);\">Edit</a>
		</td>
		<td>" . $res->action . " &nbsp;</td>
		<td>" . $res->eval . " &nbsp;</td>
	</tr>"; 
  }
$ptypeOptionsBlank = "<select name=\"kind[]\">" . 
				   GetOptionList($ptypeList) . 
				   "</select>";
/*
$row .= "<tr>
		<td><input size = 2 type=hidden name=id[] value=\"\" />
		<a href=\"#\" onclick=\"javascript:removeRowClone('1');\">D</a>
		</td>
		<td><input size = 10 type=text name=action[] value=\"\" /></td>
		<td><input  size = 7 type=text name=person[] value=\"\" /></td>
		<td>
			$ptypeOptionsBlank
		</td>
		<td><input  size = 7 type=text name=timeline[] value=\"\" /></td>
		<td><input  size = 12 type=text name=eval[] value=\"\" /></td>
		<td><input  size = 12 type=text name=final[] value=\"\" /></td>		
	</tr>"; 
*/
$button = "<a href=\"javascript:popUp('index.php?module=sip&cmd=editAction&area=$area&sid=$id', 550, 480 );\">Add Item</a>";
//$button = "<input type=submit name=btn value=\"Add Item\">";
		
?>

<html>
<head>
<script>
  function popUp(URL, x, y) {
  	self.name = 'listings'; 
	newwindow = window.open(URL, 'name', 'toolbar=1,scrollbars=1,location=1,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
	if(window.focus) {newwindow.focus()}
  }

  function confirmMsg(msg)
  {
		return(input_box=confirm(msg));
  }
</script>
<?php
/*
	<script src="http://localhost/dart/lib/utility.txt"></script>
	<script type="text/javascript" src="http://localhost/dart/lib/myScript.js"></script>
	*/
?>
</head>
<body>
<!-- <form action=sip/showinfo.php method=post > -->
<?php echo $button ?>
<table id="phoneClone" class="graybg" border=1 width=600>
	<thead>
	<tr class="bluebarsub"><td width=50px>Edit/Delete</td><td>Smart Plan</td><td>Evaluation</td></tr>
	</thead>
	<?php echo $row ?>
</table>
</body>
</html>
