<?php

include_once ('lib/functions_gb.inc');

$gid = $_GET['gid'];

$gb = $db->get_results("SELECT * from gb_main where gid = '$gid'", ARRAY_A);
$listid = $gb[0]['lid'];
$slist = getListStudents($listid);
$weighted = $gb[0]['weighted'];
$students = $db->get_results ("select * from student where studentid in ($slist)", ARRAY_A);
$editgb = "<a href='?cmd=gb_edit&gid=$gid'>Edit Gradebook</a>";

$assignments = getGBAssignments($gid);

$grades = getGBGrades($gid);


if ($weighted == '1') {
	$cat = getCategories($gid);
	$catlegend .= "<b>Category and Weight</b><br>";
	foreach($cat as $c) {
		$catlegend .= "{$c['catname']} -> {$c['weight']}%<br>";
	}
}

function getCategories($gid) {
	global $db;
	
	$cat = $db->get_results("SELECT * from gb_categories, gb_catwt where  gb_categories.cid = gb_catwt.cid and gb_catwt.gid = '$gid'", ARRAY_A);
	return($cat);
}
$options = selectGB($currentUserID, $gid);
$self = $_SERVER['PHP_SELF'];
$body .= <<<END
<script type="text/javascript" src="lib/jquery-min.js"></script>
<script>
function saveChange(name, field) {
	val = $('#'+name).val();
	$.get("/?cmd=gb_save", { val: name+'_'+val, field: field, weighted: '$weighted' },
   		function(data){
   			$("#"+field).val(data);
   			$("#"+name).removeClass('novalue');
//     		alert("Data Loaded: " + data);
   	});
//	alert(name+'_'+val);
}
function computeTotal (field) {
	alert(field);
}
</script>
<style>
.novalue { background-color: pink;  }
</style>
<select name=gb onChange=window.location='$self?cmd=gb&gid='+this.value>
<option value=''></option>
$options
</select> $editgb<br>
$catlegend
<table border=1><tr><td></td><td>Overall</td>
END;

foreach($assignments as $a) {
	$body .= "<td>{$a['name']}<br>{$a['catname']}<br>[{$a['std']}]</td>";
}
$body .= "</tr>";
foreach($students as $stu) {
	$body .= "<tr><td nowrap>{$stu['fname']} {$stu['lname']} ({$stu['studentid']})</td>";
	$totalid = "{$stu['studentid']}_{$gid}_total";
	$body .= "<td><input type=text id=$totalid name=$totalid value='' size=6  readonly\"> </td>";
	foreach($assignments as $a) {
		$fieldid = "{$stu['studentid']}_{$a['aid']}";
		$val = $grades[$stu['studentid']][$a['aid']];
		$class = ($val == '') ? "class=novalue": '';
		$body .= "<td><input  $class type=text id=$fieldid name=$fieldid value='$val' size=3 onchange=\"javascript:saveChange('$fieldid', '$totalid');\"></td>";
	}
	$body .="</tr>";
}
$body .="</table>";
//echo $studentlist;
function getGBGrades ($gid) {
	global $db;
	
	$scores = $db->get_results("SELECT * from gb_scores, gb_assignments 
		WHERE gb_assignments.gid = '$gid' and gb_scores.aid = gb_assignments.aid", ARRAY_A);
	foreach($scores as $s) {
		$arr[$s['sid']][$s['aid']] = $s['score'];
	}
//	$arr[670452][1] = '56';
	return($arr);
}

function getGBAssignments ($gid) {
	global $db;
	
	$assignments = $db->get_results("SELECT * from gb_assignments
									LEFT JOIN gb_categories ON gb_categories.cid = gb_assignments.category
									WHERE gb_assignments.gid = '$gid' 
									ORDER BY ord", ARRAY_A);
// 	$link = "'<a href=',st.link,' onMouseOver=\"return escape('test');\">',st.subject,'</a> '";

	$link = "'<a href=',st.link,' onMouseOver=\"return escape(\'',st.description,'\');\">',st.subject,'.',st.level,'.',st.std,'</a>'";
	$assignments = $db->get_results("SELECT gb_assignments.*, cat.*, GROUP_CONCAT($link) as std from gb_assignments
									LEFT JOIN gb_categories as cat ON cat.cid = gb_assignments.category
									LEFT JOIN (gb_assignstand as gba, standards as st) ON 
										gba.subject = st.subject and gba.level = st.level and gba.std = st.std and gba.aid = gb_assignments.aid
									WHERE gb_assignments.gid = '$gid' 
									GROUP BY gb_assignments.aid
									ORDER BY ord", ARRAY_A);
//	print_r($assignments);
	return($assignments);
}



include ("template.inc");
?>
