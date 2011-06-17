<?php

if($_POST['button'] != '') {
	foreach($_POST['checkbox'] as $c) {
		deleteList($c);
	}
}

$mylists = getMyList($currentUserID);
$grouplists =  getMyList($currentUserID, $currentMySite);
$totallist = array_merge($mylists, $grouplists);

$body .= "<form method=post>";
foreach($mylists as $list) {
	$body .= <<<END
		<input name="checkbox[]" type="checkbox" value='{$list['listid']}'>{$list['listname']}<br>
END;
}
$body .= "_________________________<br>";
foreach($grouplists as $list) {
	$body .= <<<END
		<input name="checkbox[]" type="checkbox" value='{$list['listid']}'>{$list['listname']}<br>
END;
}
$body .= "<input type=submit value=Delete name=button onclick=\"javascript:confirmMsg('do you really want to delete the checked lists');\"></form>";
include("template.inc");

?>