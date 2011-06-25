<?php
$subcmd = $_GET['subcmd'];
$listid = $_GET['listid'];

if($subcmd == 'addtab') {
	addTab($listid);
} else if($subcmd == 'deltab') {
	delTab($_GET['tabid']);
} else if($subcmd == 'addinfo') {
	addInfo($_GET['tabid']);
} else if($subcmd == 'delinfo') {
	delInfo($_GET['infoid']);
} else if($subcmd=='reordertab') {
	reorderTab($_GET['tabid'], $_GET['ord']);
} else if($subcmd=='reorderinfo') {
	reorderInfo($_GET['infoid'], $_GET['ord']);
}

global $db;
$tabs = $db->get_results("SELECT * from grp_tab
							WHERE listid = '$listid'
							ORDER BY ord", ARRAY_A);

$n_tabs = count($tabs);
$output = range(0,$n_tabs);
$values = $output;
array_unshift($output,"top");
$data = array();

$kindMenu = array(
		"iframe" => "URL",
		"embed" => "Code"
);


foreach($tabs as $t) {
	$data[$t['tabid']] = array();
	$data[$t['tabid']]["tabname"] = $t['tabname'];
	$data[$t['tabid']]["selected"] = $t['ord'];
	$data[$t['tabid']]["info"] = array();

	$info = $db->get_results("SELECT * from grp_info
							WHERE tabid = '{$t['tabid']}'
							ORDER BY ord", ARRAY_A);
	$n_infos = count($info);
	$data[$t['tabid']]["info"] = array();
	foreach($info as $i) {
		$data[$t['tabid']]["info"][$i['infoid']] = array();
		$info_output = range(0,$n_infos);
		$info_values = $info_output;
		array_unshift($info_output,"top");
		$data[$t['tabid']]["info"][$i['infoid']]["output"] = $info_output;
		$data[$t['tabid']]["info"][$i['infoid']]["values"] = $info_values;
		$data[$t['tabid']]["info"][$i['infoid']]["selected"] = $i['ord'];
		$data[$t['tabid']]["info"][$i['infoid']]["value"] = $i['value'];
		$data[$t['tabid']]["info"][$i['infoid']]["width"] = $i['width'];
		$data[$t['tabid']]["info"][$i['infoid']]["height"] = $i['height'];
		$data[$t['tabid']]["info"][$i['infoid']]["kind"] = $i['kind'];

	}
}

$smarty->assign('listid',$listid);
$smarty->assign('output',$output);
$smarty->assign('values',$values);
$smarty->assign('kindMenu',$kindMenu);
$smarty->assign('data',$data);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('showscoresEditInfo.tpl');


function reorderInfo($infoid, $ord) {
	global $db;

	$db->get_results("UPDATE grp_info SET ord = '$ord'+.5 WHERE infoid = '$infoid' ", ARRAY_A);
	$tabid = $db->get_var("SELECT tabid from grp_info where infoid = '$infoid'");
	$items = $db->get_results("SELECT * from grp_info where tabid = '$tabid' ORDER BY ord", ARRAY_A);
	$i = 1;
	foreach($items as $item) {
		$db->get_results("UPDATE grp_info SET ord = '$i' WHERE infoid = '{$item['infoid']}' ", ARRAY_A);
		$i++;
	}
}
function reorderTab($tabid, $ord) {
	global $db;

	$db->get_results("UPDATE grp_tab SET ord = '$ord'+.5 WHERE tabid = '$tabid' ", ARRAY_A);
	$listid = $db->get_var("SELECT listid from grp_tab where tabid = '$tabid'");
	$items = $db->get_results("SELECT * from grp_tab where listid = '$listid' ORDER BY ord", ARRAY_A);
	$i = 1;
	foreach($items as $item) {
		$db->get_results("UPDATE grp_tab SET ord = '$i' WHERE tabid = '{$item['tabid']}' ", ARRAY_A);
		$i++;
	}
}

function addInfo($tabid) {
	global $db;

	$ordnum = $db->get_var("SELECT max(ord)+1 FROM grp_info WHERE tabid = '$tabid' ");
	$db->get_results("INSERT INTO grp_info SET tabid = '$tabid', kind='iframe', ord = '$ordnum' ", ARRAY_A);
}

function addTab($listid) {
	global $db;

	$ordnum = $db->get_var("SELECT max(ord)+1 FROM grp_tab WHERE listid = '$listid' ");
	$db->get_results("INSERT INTO grp_tab SET listid = '$listid', ord = '$ordnum' ", ARRAY_A);
}

function delTab($tabid) {
	global $db;

	$db->get_results("DELETE FROM grp_tab WHERE tabid='$tabid' ", ARRAY_A);
	$db->get_results("DELETE FROM grp_info WHERE tabid='$tabid' ", ARRAY_A);
}

function delInfo($infoid) {
	global $db;

	$db->get_results("DELETE FROM grp_info WHERE infoid='$infoid' ", ARRAY_A);
}

?>
