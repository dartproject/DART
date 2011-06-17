<?php

function getGradeSymbol($id, $sel) {
	global $db;
	
	$results = $db->get_results("SELECT * FROM gs_grades where gsid = '$id' ORDER BY ord", ARRAY_A);
	$str .= "<option value=''></option>";
	foreach($results as $r) {
		$selected = (($sel <= $r['high']) and ($sel >= (int)($r['low'])) and $sel != '') ? "selected" : ''; 
//	echo "$id=>$sel: {$r['high']} {$r['low']} $selected<br>";
		$str .= "<option value={$r['val']} $selected>{$r['symbol']}</option>";
	} 
	return($str);
}
function getSingleGradeSymbol($id, $sel) {
	global $db;
	
	$results = $db->get_results("SELECT * FROM gs_grades where gsid = '$id' ORDER BY ord", ARRAY_A);
	foreach($results as $r) {
		if(($sel <= $r['high']) and ($sel >= (int)($r['low'])) and $sel != '') return($r['symbol']);
	} 
	return('');
}

?>
