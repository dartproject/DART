<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


if(PrivilegeB(B11) == 'none') { NoPriv("denied access to Test Level Information"); }

$listid = $_GET['listid'];
$button = $_GET['button'];
if($button == 'Delete') {
	$id = $_GET['id'];
	$year = $_GET['year'];
	$sql = "DELETE FROM testinglevel where studentid = '$id' and year='$year'";
	$db->query($sql);
} else if ($button == 'Save') {
	$sid = $_GET['studentid'];
	$years = $_GET[$sid . "_year"];
	$level =  $_GET[$sid . "_level"];
	$sql = "DELETE FROM testinglevel where studentid = '$sid' ";
	$db->query($sql);
	for($i=0; $i < count($years); $i++) {
		if($years[$i] != '') {
			$sql = "INSERT INTO testinglevel set studentid = '$sid', year='{$years[$i]}', testinglevel='{$level[$i]}' ";
			$db->query($sql);
		}
	}
}

$self = $_SERVER['PHP_SELF'] . "?cmd=edittestlevel&listid=$listid";

$mylists = getMyList($currentUserID);
$grouplists =  getMyList($currentUserID, $currentMySite);

$selectList .= "
<script>
function handleThis(value) {
//	alert('test');
   window.location='index.php?cmd=edittestlevel&listid=' + value;
}
</script>
";

$selectList .= "<select name=listid onChange='javascritp:handleThis(this.value);'>
<option value=''>--</option>";

foreach($mylists as $my) {
  $lid = $my['listid'];
  $lname = $my['listname'];
  $select = ($listid == $lid) ? "selected": "";
  $selectList .= "<option value=\"$lid\" $select>$lname</option>";
  }

$selectList .= "<option value=\"\">---- Shared List ---</option>";

foreach($grouplists as $my) {
  $lid = $my['listid'];
  $lname = $my['listname'];
  $selectList .= "<option value=\"$lid\">$lname</option>";
  }

$selectList .= "</select>";

$body = $selectList;

if($listid != '') {
	$students = getListStudents($listid);
	
	$results = $db->get_results("select testinglevel.studentid, year, testinglevel, fname, lname FROM testinglevel, student where student.studentid = testinglevel.studentid and testinglevel.studentid in ($students) ORDER BY studentid ASC, year ASC", ARRAY_A);
	
	foreach($results as $testlevel) {
		$levels[$testlevel['studentid']][$testlevel['year']] = $testlevel['testinglevel'];
		$studentname[$testlevel['studentid']] = $testlevel['fname'] . " " . $testlevel['lname'];
	}
	
	while(list($var, $val) = each($levels)) {
		$name = $studentname[$var];
		$col1 = "<form method=get action=$self>
			<input type=hidden name=cmd value=edittestlevel>
			<input type=hidden name=listid value='$listid'>
			<input type=hidden name=studentid value='$var'>
			<table border=1><tr><td rowspan=2 nowrap>$name [$var]<br><input type=submit value=Save name=button></td>";
		
		while(list($var2, $val2) = each($val) ) {
			$col1 .= "<td nowrap>$var2<input type=hidden name={$var}_year[] value=$var2> <a href='$self&button=Delete&year=$var2&id=$var'>D</a></td>";
			$col2 .= "<td><input type=text name='{$var}_level[]' value='$val2' size=2></td>";
		}
		$col1 .= "<td nowrap><input type=text name={$var}_year[] value='' size=4></td>";
		$col2 .= "<td><input type=text name='{$var}_level[]' value='' size=2></td>";
		$body .= "$col1</tr><tr> $col2 </tr><table></form><br>";
		$col2 = '';
		$col1 = '';
	}
}

include ("template.inc");

?>
