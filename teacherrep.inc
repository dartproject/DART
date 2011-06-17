<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$site = $_GET['site'];
$test = $_GET['test'] == '' ? 'Q1' : $_GET['test'];
${"test_" . $test} = "selected";
$sites = getSites('');   
foreach ($sites as $s) {
	$id = $s['siteid']; $name=$s['name'];
	$siteList .= "<option value =\"$id\" " . selected($id, $site) . ">$name</option>\n";    
}
$body .= "<form action=index.php method=get>
					<input type=hidden name=cmd value=teacherrep>
					<select name=\"site\" id=\"site\" onChange=\"submit()\">
						<option value=''>-select-</option> 
						$siteList
					</select>
					
				 </form>";
				 
$s = getTeacherActionPlans ($site, $CurrentYear, 'teacher', $test);			

// echo count($s) . "-";
for($i = 0; $i < count($s) ; $i++) {
	$area = $s[$i]['area'];
	$action = $s[$i]['action'];
	$person = $s[$i]['person'];
	$ptype = $s[$i]['ptype'];
	$timeline = $s[$i]['timeline'];
	$eval = $s[$i]['eval'];
	$final = $s[$i]['final'];
	$teacher = $s[$i]['user_name'];
//	echo $teacher;
	if ($teacher != $oldteacher) {
		$body .= "<strong>$teacher</strong><br><table border=1>
		<tr><th>Smart Plan</th><th>Evaluation</th></tr>";
		$oldteacher = $teacher;
	}
	$body .= "<tr>
				<td width=50%>$action</td>
				<td>$eval &nbsp;</td>
			</tr>
			";
	if($s[$i]['user_name'] != $s[$i+1]['user_name'] and $s[$i+1]['user_name'] != '') {
		$body .= "</table><br>";
	}
}
	$body .= "</table><br>";


include("template.inc");

function getTeacherActionPlans ($site='', $year='', $type ='teacher', $test='') {
	global $db;
	
	$sql = "select *, sip.name as sname, sip.area as sarea, user.name as user_name $select
	        FROM user, sip
	        LEFT join sipaction ON sip.id = sipaction.sid 
	        WHERE
	        	sip.kind = '$type'	        	
	        	and sip.site = '$site' 
	        	and sip.owner = user.userid 
	        	and sip.year = '$year' 

	        ORDER BY sip.site, sip.area, user.name, sipaction.sid
	        ";
//	echo("$type=>$sql<br>");
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}
?>
