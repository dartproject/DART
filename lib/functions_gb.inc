<?php

function selectGB ($userID, $sel) {
	global $db;
    
    $query = "select gid as id, name from lists, gb_main where userid='$userID' and listid=lid ";
    $list = $db->get_results($query, ARRAY_A);
	$options = getOptionList($list, $sel);
	return($options);

}

function newgb($listid) {
	global $db, $currentUserID;
	
	$db->get_results("INSERT INTO gb_main set lid = '$listid',name='New Gradebook' ");
	return(mysql_insert_id() );
}

function newcat($gid) {
	global $db,$currentUserID;
	
	$db->get_results("INSERT INTO gb_categories set userid = '$currentUserID', catname='New Cat' ");
}
function delcat($cid) {
	global $db,$currentUserID;
	
	$db->get_results("DELETE FROM gb_categories WHERE cid = '$cid' and userid = '$currentUserID' ");
}
function newassignment($gid) {
	global $db;
	$ord = $db->get_var("SELECT max(ord)+1 FROM gb_assignments where gid = '$gid' ");
	$db->get_results("INSERT INTO gb_assignments set gid = '$gid', name='New Assignment', ord='$ord'  ");
}
function delassignment($aid) {
	global $db;
	$db->get_results("DELETE FROM gb_assignments WHERE aid = '$aid'  ");
	$db->get_results("DELETE FROM gb_assignstand WHERE aid = '$aid'  ");
}
function newcatwt($gid) {
	global $db;
	
	$db->get_results("INSERT INTO gb_catwt set gid = '$gid' ");
}
function delcatwt($cwid) {
	global $db;
	
	$db->get_results("DELETE FROM gb_catwt where cwid = '$cwid' ");
}
	

?>
