<?php

include_once ('lib/functions_gb.inc');

$gid = $_GET['gid'];
$subcmd = $_GET['subcmd'];
$sep= '--_';
if($subcmd == 'newgb') {
	$listid = $_GET['listid'];
	$gid = newgb($listid);
} else if ($subcmd == 'newassignment') {
	newassignment($gid);
} else if ($subcmd == 'delassignment') {
	delassignment($_GET['aid']);
}else if ($subcmd == 'newcatwt') {
	newcatwt($gid);
} else if ($subcmd == 'delcatwt') {
	delcatwt($_GET['cwid']);
}else if ($subcmd == 'newcat') {
	newcat($gid);
} else if ($subcmd == 'delcat') {
	delcat($_GET['cid']);
} else if ($subcmd == 'save') {
//	echo "{$_GET['val']}<br><br>";
	$sval = explode ("$sep", $_GET['val']);
	$table = $sval[0];
	$name = $sval[1];
	$field = $sval[2];
	$id = $sval[3];
	$value = $sval[4];
	
	$sql = "UPDATE $table set $name = '$value' where $field='$id' ";
	$db->get_results($sql);
//	echo "{$_GET['val']} -- $sql";
}

$gb = $db->get_row("SELECT * from gb_main where gid = '$gid'", ARRAY_A);
//print_r($gb);
//echo "--{$gb['name']}";

$options = selectGB($currentUserID, $gid);
$self = $_SERVER['PHP_SELF'];
$newassignment = "<a href='?cmd=gb_edit&subcmd=newassignment&gid=$gid'>New Assignment</a>";
$newweight = "<a href='?cmd=gb_edit&subcmd=newcatwt&gid=$gid'>New Category Weight</a>";
$newcategory = "<a href='?cmd=gb_edit&subcmd=newcat&gid=$gid'>New Category</a>";
$viewgb = "<a href='?cmd=gb&gid=$gid'>View Gradebook</a>";

$catlist = $db->get_results("SELECT cid as id, catname as name from gb_categories WHERE userid = '$currentUserID'", ARRAY_A);

$assignments = $db->get_results("SELECT gb_assignments.*, gb_categories.*,
									GROUP_CONCAT(st.subject,'.',st.level,'.',st.std) as std 
								FROM gb_assignments
								LEFT JOIN gb_categories ON gb_categories.cid = gb_assignments.category
								LEFT JOIN (gb_assignstand as gba, standards as st) ON 
									gba.subject = st.subject and gba.level = st.level and gba.std = st.std and gba.aid = gb_assignments.aid

								WHERE gb_assignments.gid = '$gid' 
								GROUP BY aid
								ORDER BY ord", ARRAY_A);
//print_r($assignments);								
$editassign = "<table border=1><tr><th>Name</th><th>Category</th><th>Order</th><th>Standards</th><th>Action</th></tr>";
foreach($assignments as $a) {
	$aoptions = getOptionList($catlist, $a['category']);
	$del = "<a href='?cmd=gb_edit&subcmd=delassignment&aid={$a['aid']}&gid=$gid'>D</a>";
	$name1 = "gb_assignments{$sep}name{$sep}aid{$sep}{$a['aid']}";
	$name2 = "gb_assignments{$sep}category{$sep}aid{$sep}{$a['aid']}";
	$name3 = "gb_assignments{$sep}ord{$sep}aid{$sep}{$a['aid']}";
	$std = $a['std'];
	$stdedit = <<<END
	<a href="?cmd=gb_assignstd&aid={$a['aid']}" onclick="var newin = window.open(this.href,'','resizable=yes,location=no,menubar=no,scrollbars=yes,status=no,toolbar=no,fullscreen=no,dependent=no,width=400,height=400,left=20,top=20,status'); newin.focus(); return false">+</a>
END;
	$editassign .= "<tr>
						<td><input type=text id='$name1' value='{$a['name']}' onChange=\"saveEditChanges('$name1');\" ></td>
						<td>
							<select id='$name2' onChange=\"saveEditChanges('$name2');\" >
							<option value=''></option>$aoptions</select>
						</td>
						<td><input type=text id='$name3' value='{$a['ord']}' onChange=\"saveUpdateChanges('$name3');\" size=2></td><td>$stdedit $std</td><td>$del</td></tr>";
}
$editassign .= "</table>";

$name8="gb_main{$sep}weighted{$sep}gid{$sep}{$gid}";
//echo "Weight: {$gb['weighted']}";
if($gb['weighted'] == 1) {
	$sel = 'checked'; $v = 0; 
} else {
	$v = 1;
}
$weighted = "<input id='$name8' type=checkbox value='$v' $sel onChange=\"saveUpdateChanges('$name8');\">Weight<br><br>";
if($gb['weighted'] == 1) {
	$catwt = $db->get_results("SELECT * from gb_catwt WHERE gb_catwt.gid = '$gid'", ARRAY_A);
	$editcatwt = "Category Weight $newweight<br>
					<table border=1><tr><th>Name</th><th>Weight</th><th>Action</th></tr>";
	foreach($catwt as $c) {
		$coptions = getOptionList($catlist, $c['cid']);
		$del = "<a href='?cmd=gb_edit&subcmd=delcatwt&cwid={$c['cwid']}&gid=$gid'>D</a>";
		$name4 = "gb_catwt{$sep}cid{$sep}cwid{$sep}{$c['cwid']}";
		$name5 = "gb_catwt{$sep}weight{$sep}cwid{$sep}{$c['cwid']}";
		$editcatwt .= "<tr><td>
						<select id='$name4' onChange=\"saveEditChanges('$name4');\">
							<option value=''></option>
							$coptions
						</select>
						</td><td><input type=text id='$name5' value='{$c['weight']}' onChange=\"saveEditChanges('$name5');\" size=2></td><td>$del</td></tr>";
	}
	$editcatwt .= "</table><br><br>";
}
//echo $currentUserID;
$cat = $db->get_results("SELECT * from gb_categories WHERE userid = '$currentUserID'", ARRAY_A);
$editcat = "<table border=1><tr><th>Name</th><th>Action</th></tr>";
foreach($cat as $ca) {
	$del = "<a href='?cmd=gb_edit&subcmd=delcat&cid={$ca['cid']}&gid=$gid'>D</a>";
	$name6 = "gb_categories{$sep}catname{$sep}cid{$sep}{$ca['cid']}";
	$editcat .= "<tr><td><input type=text id='$name6' value='{$ca['catname']}' 
					onChange=\"saveUpdateChanges('$name6');\"></td><td>$del</td></tr>";
}
$editcat .= "</table>";


$body .= <<<END
<script type="text/javascript" src="lib/jquery-min.js"></script>
<script>
function saveEditChanges(name) {
	val = $('#'+name).val();
	$.get("/?cmd=gb_save_edit", { val: name+'$sep'+val, sep: '$sep' },
   		function(data){
//     		alert("Data Loaded: " + data);
   	});
//	alert(name+'_'+val);
}
function computeTotal (field) {
	alert(field);
}
function saveUpdateChanges(name) {
	val = $('#'+name).val();
	window.location = "?cmd=gb_edit&val="+name+'{$sep}'+val+"&subcmd=save&gid=$gid";
	
//	alert(name+'_'+val);

}
</script>
<style>
.novalue { background-color: pink;  }
</style>
<select name=gb onChange=window.location='$self?cmd=gb_edit&gid='+this.value>
<option value=''></option>
$options
</select> $viewgb
<br><br>
Name: <input type=text value='{$gb['name']}' id='gb_main{$sep}name{$sep}gid{$sep}{$gid}' onChange="saveUpdateChanges('gb_main{$sep}name{$sep}gid{$sep}{$gid}');"><br>
Assignments $newassignment<br>
$editassign
<br>
$weighted

$editcatwt

Categories $newcategory<br>
$editcat
<br><br><br>


END;


include ("template.inc");
?>
