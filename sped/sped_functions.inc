<?php

// ==================================================================

//  Author: Robert Joseph (dart@vizmotion.com)

//	 Web: http://wiki.bssd.org/index.php/DART_System

// ==================================================================

function convert_date($str) {

list($date, $time) = explode(' ', $str);
list($year, $month, $day) = explode('-', $date);
//list($hour, $minute, $second) = explode(':', $time);

$timestamp = mktime(0, 0, 0, $month, $day, $year);

//echo "($date -- $year, $month, $day $time -- $hour, $minute, $second $str - $timestamp)";
return $timestamp;
}

function editTable($tableinfo, $savedinfo, $col = 1, $w=10) {

	

	$str = "
	<div id=id1></div>

<script type=\"text/javascript\" src=\"lib/jquery-min.js\"></script>
	<script>
	var list = new Array();
	function markChange(id) {
		var str='';
		list.push(id);
		for(var i=0;i<list.length;i++){
		    if(i>0) str = str + ','; 
			str = str + list[i];
		}
		$('#id1').html(str);
		$('#changed').val(str);
		
	}
	</script>
	<table border=0><tr>
	<input id=changed type=hidden name=changed value=''>
	";

	$i = 0;

	foreach ($tableinfo as $row) {

		$type = $row['type'];

		$name = $row['name'];

		$label = $row['label'];

		$value = $savedinfo[$name];

		$str .= (fmod($i, $col) == 0) ? "\n</tr><tr>" : "";

		if($type == 'textfield' or $type=='date') {

			$str .= "<td align=right>$label:</td>

					 <td><input type=text name='$name' value='$value' size=$w onchange=markChange('$name');></td>";

			$i++;

		} else if ($type == 'hidden') {

			$strBefore .= "<input type=hidden name='$name' value='$value'>";

		} else if ($type == 'view') {

			$str .= "<td align=right>$label:</td>

					 <td>$value</td>";

			$i++;

		} else if ($type == 'defaulthidden') {

			$default = $row['default'];

			$strBefore .= "<input type=hidden name='$name' value='$default'>";

		} else if ($type == 'select') {

			$extra = $row['extra'];

			$selectOptions = arrayOptions($extra, $value);

			$str .= "<td valign=top align=right>$label:</td>

								<td>

									<select name='$name' onchange=markChange('$name');>

										$selectOptions

						   			</select>

						   		</td>

						   	";

			$i++;

		} else if ($type == 'textarea') {
			$width = ($row['width']=='') ? '20' : $row['width'];
			$height = ($row['height']=='') ? '20' : $row['height'];
			$str .= "<td valign=top align=right>$label:</td>

					 <td><textarea name='$name' cols='$width' rows='$height' onchange=markChange('$name');>$value</textarea></td>";

			$i++;

		} else if ($type == 'yesno') {

			$extra = array( array(" ", "select Y/N"), array("Y", "Yes") , array("N", "No") );
			
			$selectOptions = arrayOptions($extra, $value);

			$str .= "<td valign=top align=right>$label:</td>

								<td>

									<select name='$name' onchange=markChange('$name');>

										$selectOptions

						   			</select>

						   		</td>

						   	";

			$i++;

		}

	}

	$j = ($col - fmod($i, $col) ) * 2;

	while ($j > 0 and fmod($i, $col) <> 0) { $str .= "<td>&nbsp;</td>"; $j--; }

	

	$str .= "</tr></table>";

	return($strBefore . $str);

}



function arrayOptions ($values, $sel = '') {

	global $db;

	

	foreach ($values as $row) {

		$selected = ($row[0] == $sel) ? "selected": "";

		$ret .= "<option value='$row[0]' $selected>$row[1]</option>";

	}

	return ($ret);



}



function editTable_old($tableinfo, $savedinfo, $col = 1) {

	

	$str = "<table border=0><tr>";

	$i = 0;

	foreach ($tableinfo as $row) {

		$type = $row['type'];

		$name = $row['name'];

		$label = $row['label'];

		$value = $savedinfo[$name];

		$str .= (fmod($i, $col) == 0) ? "\n</tr><tr>" : "";

		if($type == 'textfield') {

			$str .= "<td>$label</td>

					 <td><input type=text name='$name' value='$value'></td>";

			$i++;

		} else if ($type == 'hidden') {

			$strBefore .= "<input type=hidden name='$name' value='$value'>";

		} else if ($type == 'defaulthidden') {

			$default = $row['default'];

			$strBefore .= "<input type=hidden name='$name' value='$default'>";

		}



	}

	$j = ($col - fmod($i, $col) ) * 2;

	while ($j > 0 and fmod($i, $col) <> 0) { $str .= "<td>&nbsp;</td>"; $j--; }

	

	$str .= "</tr></table>";

	return($strBefore . $str);

}



function saveTable($sql, $savedinfo) {

	global $db;

	

	while(list($name, $val) = each($savedinfo)) {

		$vars[] = "{" . $name . "}";

		$values[] = $val;

	}

	$sql = str_replace($vars, $values, $sql);

	$results = $db->get_results("$sql");

}


function saveSped($v) {
	global $db;
	
	$fields = explode(",", $v['changed']);
	
	foreach($fields as $field) {
		$set .= $set != '' ? ',' : '';
		$set .= "$field='{$v[$field]}'";
		$rec .= "$field=>{$v[$field]} ";
	}
	$sql = "UPDATE speddata SET $set WHERE studentid = '{$v[studentid]}'";

//	echo "$sql .<br>";
	$db->get_results($sql);
	
	logHistory('spedupdate', $v['studentid'], $rec);
}
function getStudentListSep($listID, $other) {

	 global $debugLevel, $db;

//	 print_r($other);

	 $studentlist = getListStudents($listID);
	 
	 $clause .= ($other['spedstatus'] != '') ? " and Sped_Status = '{$other['spedstatus']}' ": '';
	 

	 $query = "select *, (CURDATE() - bday) as age, student.studentid, entrysped > exitdate as sped 
	 			from student 
	 			Left join speddata on speddata.studentid = student.studentid 
	 			where student.studentid in ($studentlist) 
	 				$clause
	 			order by {$other['sortval']} {$other['sortdir']} ";

// echo $query;

	 $list = $db->get_results($query, ARRAY_A);



	 return $list;

}

function statusOptionList($val) {
	$values = statusOptionArray();
	$str = arrayOptions ($values, $val);

	return($str);
}

function statusOptionArray($val) {
	$val = array( 
				  array("", "Select One"), 
				  array("BSSD_Default", "BSSD Default (IP/R/E)") , 
				  array("In_Program", "In Program") , 
				  array("Referred", "Referred") , 
				  array("Exited", "Exited") , 
				  array("TNP", "TNP") , 
				  array("Eligible", "Eligible") );
	return($val);
}

function getMyListSped($userID) {
	global $db, $currentMySite;
	
	$query = "select kind, listid as id, listname as name from lists where userid='$userID' order by listname ASC";
	$list = $db->get_results($query, ARRAY_A);
	for ($i = 0; $i < count($list); $i++) {
		$addtion = ($list[$i]['kind'] == 'search') ? "*": "";
		$list2[$i]['id'] = $list[$i]['id'] ;
		$list2[$i]['name'] = $list[$i]['name'] . $addtion ;
	}

	$list2[$j+$i]['id'] = "" ;
	$list2[$j+$i]['name'] = "-- Group --" ;
	$i++;
	
	$query = "select kind, listid as id, listname as name from lists where type = \"$currentMySite\" order by listname ASC";
//	echo "$query<br>";
	$list = $db->get_results($query, ARRAY_A);
	for ($j = 0; $j < count($list); $j++) {
		$addtion = ($list[$i]['kind'] == 'search') ? "*": "";
		$list2[$j+$i]['id'] = $list[$j]['id'] ;
		$list2[$j+$i]['name'] = $list[$j]['name'] . $addtion ;
	}
	$list2[$j+$i]['id'] = "" ;
	$list2[$j+$i]['name'] = "-- Private --" ;
	$i = $i+$j+1;
	
	$query = "select lists.listid as listid, lists.listname as listname, lists.kind as kind from lists 
				where lists.userid = '$userID' and type = 'Private'
			union
			  select lists.listid as listid, lists.listname as listname, lists.kind as kind from lists, listshare 
				where lists.listid = listshare.listid and listshare.userid = '$userID' and type='Private'";
//	echo "$query<br>";
	$list = $db->get_results($query, ARRAY_A);
	for ($j = 0; $j < count($list); $j++) {
		$addtion = ($list[$j]['kind'] == 'search') ? "*" : "";
		$list2[$j+$i]['id'] = $list[$j]['listid']  ;
		$list2[$j+$i]['name'] = $list[$j]['listname'] . $addtion ;
	}

return $list2;
}

?>