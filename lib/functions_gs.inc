<?php

/*
 * Get list of grade symbols for this grade system
 */
function getGradeSymbols($gsID) {
	global $db;
	$options = array("" => "");
	$results = $db->get_results("SELECT val, symbol FROM gs_grades where gsid = $gsID ORDER BY ord", ARRAY_A);
	foreach($results as $r) {
		$options[$r['val']] = $r['symbol'];
	} 
	return $options;
}

/*
 * Get equivalent grade value for a given grade $val (Eg: $val in [83,86] => $value = 86, B grade)
 */
function getEqGradeValue($gsID, $val) {
	global $db;
	$value = "";
	if($val != '') {
		$value = (int)($db->get_var("SELECT val FROM gs_grades WHERE gsid = $gsID AND low <= $val AND $val <= high"));
	} 
	return $value;
}

/*
 * Get grade symbol for a given grade $val (Eg: $val in [83,86] => $symbol = B)
 */
function getGradeSymbol($gsID, $val) {
	global $db;
	$symbol = "";
	if($val != '') {
		$symbol = $db->get_var("SELECT symbol FROM gs_grades WHERE gsid = $gsID AND low <= $val AND $val <= high");
	} 
	return $symbol;
}

function getSingleGradeSymbol($id, $sel) {
	global $db;
	
	$results = $db->get_results("SELECT * FROM gs_grades where gsid = '$id' ORDER BY ord", ARRAY_A);
	foreach($results as $r) {
		if(($sel <= $r['high']) and ($sel >= (int)($r['low'])) and $sel != '') return($r['symbol']);
	} 
	return('');
}
