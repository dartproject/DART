<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$site = $_GET['site'];
$test = $_GET['test'] == '' ? 'Q1' : $_GET['test'];
${"siterep_" . $site} = "selected";
${"test_" . $test} = "selected";
$body .= "<form action=index.php method=get>
					<input type=hidden name=cmd value=teacherrep>
					<select name=\"site\" id=\"site\" onChange=\"submit()\">
						<option value=''>-select-</option> 
						<option value='SMK' $siterep_SMK>Anthony A. Andrews</option> 
						<option value='WBB' $siterep_WBB>Tukurngailnguq School</option> 
						<option value='SHH' $siterep_SHH>Shishmaref School</option> 
						<option value='ELI' $siterep_ELI>Aniguiin School</option> 
						<option value='KKA' $siterep_KKA>Koyuk-Malemute School</option> 
						<option value='SVA' $siterep_SVA>Hogarth Kingeekuk Memorial School</option> 
						<option value='GAM' $siterep_GAM>Gambell School</option>
						<option value='DIO' $siterep_DIO>Diomede School</option>
					</select>
					
					<select name=test onChange=\"submit()\">
						<option value=Q1 $test_Q1>Q1</option>
						<option value=Q2 $test_Q2>Q2</option>
						<option value=Q3 $test_Q3>Q3</option>
						<option value=Q4 $test_Q4>Q4</option>
						<option value=Semester1 $test_Semester1>Semester1</option>
						<option value=Semester2 $test_Semester2>Semester2</option>
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
		$body .= "<strong>$teacher</strong><br><table border=1><tr><th>Area</th><th>Action</th><th>Person</th><th>PType</th><th>Timeline</th><th>Eval</th><th>Final</th></tr>";
		$oldteacher = $teacher;
	}
	$body .= "<tr>
				<td>$area</td>
				<td>$action</td>
				<td>$person</td>
				<td>$ptype</td>
				<td>$timeline</td>
				<td>$eval</td>
				<td>$final</td>
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
	        	and sip.test = '$test'
	        ORDER BY sip.site, sip.area, user.name, sipaction.sid
	        ";
//	echo("$type=>$sql<br>");
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}
?>
