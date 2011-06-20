<?php
$subcmd = $_GET['subcmd'];
$listid = $_GET['listid'];

$body .= <<<END
	<script language="JavaScript" type="text/javascript" src="/lib/jquery-min.js"></script>
	<script>

	function onChangeValue (id, val) {
//		alert(id+val);
		$.get("/index.php", { cmd: 'saveDB', spec: id, val: val },
			function(data){
//				alert(data);
		});	
	}
	function onChangeOrder (id, val) {
//	alert(id+val);
		var page = 'index.php?cmd=showscoresEditInfo&listid=$listid&subcmd=reordertab&tabid='+id+'&ord='+val;
//		alert(page);
		window.location= page;
	}
	function onChangeInfoOrder (id, val) {
//	alert(id+val);
		var page = 'index.php?cmd=showscoresEditInfo&listid=$listid&subcmd=reorderinfo&infoid='+id+'&ord='+val;
//		alert(page);
		window.location= page;
	}
	</script>
END;



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

$body .= editTabInfo($listid);

include_once("template.inc");

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
function getOrdOptions($ct, $val) {
	for($i=1;$i<=$ct;$i++) {
		$select = $i == $val? "selected" : "";
		$str .= "<option value=$i $select>$i</option>\n";
	}
	return($str);
}
function editTabInfo($listid) {
	global $db;
	$tabs = $db->get_results("SELECT * from grp_tab
							WHERE listid = '$listid'
							ORDER BY ord
							", ARRAY_A);
							
	$str .= "<a href=index.php?cmd=showscores&p1=$listid>Back to Group</a> | 
			<a href=index.php?cmd=showscoresEditInfo&listid=$listid&subcmd=addtab>Add New Tab</a><br><br>";
	$ct = count($tabs);
	foreach($tabs as $t) {
		$options=getOrdOptions($ct, $t['ord']);
		$add = "<a href=index.php?cmd=showscoresEditInfo&listid=$listid&subcmd=addinfo&tabid={$t['tabid']}>Add New Info To Tab</a> |
				<a href=index.php?cmd=showscoresEditInfo&listid=$listid&subcmd=deltab&tabid={$t['tabid']}
					onclick=\"return(confirmMsg('Really Delete This Tab'));\">Delete Tab</a>";
		$str .= "
		
				<select onChange=javascript:onChangeOrder('{$t['tabid']}',this.value); >
					<option value=0>top</option>
					$options 
				</select>
				<input type=text name=grp_tab-tabid-{$t['tabid']}-tabname value='{$t['tabname']}'
					onChange=javascript:onChangeValue('grp_tab-tabid-{$t['tabid']}-tabname',this.value);> $add <br>";
		$info = $db->get_results("SELECT * from grp_info
							WHERE tabid = '{$t['tabid']}'
							ORDER BY ord
							", ARRAY_A);
		$str .= "<table ><tr style='background-color: lightgrey; border: 0px;'><th>Kind</th><th>Order</th><th>Value</th><th>Width</th><th>Height</th><th></th></tr>";
		$ct2 = count($info);
		foreach($info as $i) {
			$options=getOrdOptions($ct2, $i['ord']);
			$del2 = "<a href=index.php?cmd=showscoresEditInfo&listid=$listid&subcmd=delinfo&infoid={$i['infoid']}
					onclick=\"return(confirmMsg('Really Delete This Info'));\">Delete</a>";
			${"kind_".$i['kind']} = "selected";
			$str .= "<tr><td><select name='grp_info-infoid-{$i['infoid']}-kind'
							onChange=javascript:onChangeValue('grp_info-infoid-{$i['infoid']}-kind',this.value);>
						<option value=iframe $kind_iframe>URL</option>
						<option value=embed $kind_embed>Code</option>
					</select>
					</td><td>
					<select onChange=javascript:onChangeInfoOrder('{$i['infoid']}',this.value); >
						<option value=0>top</option>
						$options 
					</select>
					
					</td><td>
					<input type=text name=grp_info-infoid-{$i['infoid']}-value value='{$i['value']}'
						onChange=javascript:onChangeValue('grp_info-infoid-{$i['infoid']}-value',this.value);>
					</td><td>
					<input type=text name=grp_info-infoid-{$i['infoid']}-width value='{$i['width']}'
						onChange=javascript:onChangeValue('grp_info-infoid-{$i['infoid']}-width',this.value); size=5>
					</td><td>
					<input type=text name=grp_info-infoid-{$i['infoid']}-height value='{$i['height']}' 
						onChange=javascript:onChangeValue('grp_info-infoid-{$i['infoid']}-height',this.value); size=5>
					</td><td>
						$del2
					</td></tr>
					
					";
			${"kind_".$i['kind']} = "";
		}
		$str .= "</table><br><br>";
	}
	return($str);

}



?>
