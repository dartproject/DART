<?php

$sub = $_GET['sub'];
$lvl = $_GET['lvl'];
$aid = $_GET['aid'];

if($_GET['subcmd'] == 'save') {
	$s1 = $_GET['sub'];
	$l1 = $_GET['lvl'];
	$std1 = $_GET['std'];
	$v = $_GET['value'];
	if($v == 'true') {
		$sql = "INSERT INTO gb_assignstand set subject='$s1', level = '$l1', std = '$std1', aid = '$aid' ";
	} else {
		$sql = "DELETE FROM gb_assignstand WHERE subject='$s1' and level = '$l1' and std = '$std1' and aid = '$aid' ";
	}
	$db->get_results($sql);
//	echo "$sql - $v<br";
}
$a = $db->get_row("SELECT gb_assignments.*,
						GROUP_CONCAT(' ',st.subject,'.',st.level,'.',st.std) as std 
						FROM gb_assignments
						LEFT JOIN (gb_assignstand as gba, standards as st) ON 
								gba.subject = st.subject and gba.level = st.level and gba.std = st.std and gba.aid = gb_assignments.aid
						WHERE gb_assignments.aid = '$aid'  ", ARRAY_A);

$subs = $db->get_results("select id, concat(id,'-',name) as name from subjects ORDER BY core DESC, id  ", ARRAY_A);
$soptions = getOptionList($subs, $sub);

$lvls = $db->get_results("select level as id, concat(level,' - ',name) as name from level where subject='$sub' ORDER BY convert(level, unsigned) ASC ", ARRAY_A);
$loptions = getOptionList($lvls, $lvl);

$stds = $db->get_results("select st.*, g.subject as checked
							FROM standards as st
							LEFT JOIN  gb_assignstand as g ON g.subject = st.subject and g.level = st.level and g.std = st.std and g.aid = '$aid'
							WHERE st.subject='$sub' and st.level = '$lvl' and st.type = 'std' 
							ORDER BY convert(st.std, unsigned) ASC ", ARRAY_A);

$str = <<<END
<script type="text/javascript" src="lib/jquery-min.js"></script>
<script>
function submitStd(std, value) {
//	value = $('#$sub.$lvl.'+std+':checked').val();
//	value = $('#CA.3.3:checked').val();
//	value = $('#CA.3.3').is(':checked');
//	alert(value);
//	alert('$sub.$lvl.'+std+'-'+value)
	window.location="?cmd=gb_assignstd&aid=$aid&sub=$sub&lvl=$lvl&std="+std+"&subcmd=save&value="+value;
}
</script>
<table>
END;
foreach ($stds as $s) {
	$val = "{$s['subject']}.{$s['level']}.{$s['std']}";
	$checked = $s['checked'] != '' ? 'checked' : '';
	$str .= "<tr><td><input type=checkbox value=$val id=$val $checked onChange=\"submitStd('{$s['std']}', this.checked);\"></td><td>{$s['std']} - {$s['shortname']}</td></tr>";
}
$str .= "</table>";
echo <<<END
<script>
function closeThis() {
	window.opener.location.reload(true);
	window.close(); 
}
</script>
Assignment: {$a['name']}<br>
{$a['std']}<br>

<form>
<input type=hidden name=cmd value=gb_assignstd>
<input type=hidden name=aid value=$aid>

<select name=sub onchange=form.submit();>
<option vlaue=''></option>
$soptions
</select>

<select name=lvl onchange=form.submit();>
<option vlaue=''></option>
$loptions
</select>
</form>

$str

<button onClick=closeThis(); >Close</button>
END;


?>