<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$nonweaponValues =  array(
		array("id"  => "", "name" => "Select One"),
		array("id"  => "1", "name" => "Assalt"),
		array("id"  => "2", "name" => "Alcohol"),
		array("id"  => "3", "name" => "Arson"),
		array("id"  => "4", "name" => "Cheating / Unethical Behavior"),
		array("id"  => "5", "name" => "Disorderly Conduct"),
		array("id"  => "6", "name" => "Drugs"),
		array("id"  => "7", "name" => "Embezzlement"),
		array("id"  => "8", "name" => "Extortion"),
		array("id"  => "9", "name" => "Fighting"),
		array("id"  => "10", "name" => "Bullying/Harassment/Intimidation"),
		array("id"  => "11", "name" => "Insubordination"),
		array("id"  => "12", "name" => "Other Non-Weapon Incident"),
		array("id"  => "13", "name" => "Theft"),
		array("id"  => "14", "name" => "Threat"),
		array("id"  => "15", "name" => "Tobacco"),
		array("id"  => "16", "name" => "Vandalism"),
		array("id"  => "17", "name" => "Profanity")
		);
		
function makeArr($values) {
	foreach($values as $val) {
		if($val['id'] != "") 
			$ret[$val['id']] = $val['name'];
	}
	return($ret);
}
$victimNoValues = array(
		array("id"  => "", "name" => "Select Number"),
		array("id"  => "1", "name" => "1"),
		array("id"  => "2", "name" => "2"),
		array("id"  => "3", "name" => "3"),
		array("id"  => "4", "name" => "4"),
		array("id"  => "5", "name" => "5"),
		array("id"  => "6", "name" => "6"),
		array("id"  => "7", "name" => "7"),
		array("id"  => "8", "name" => "8"),
		array("id"  => "9", "name" => "9"),
		array("id"  => "10", "name" => "10"),
		array("id"  => "11", "name" => "11"),
		array("id"  => "12", "name" => "12"),
		array("id"  => "13", "name" => "13"),
		array("id"  => "14", "name" => "14"),
		array("id"  => "15", "name" => "15"),
		array("id"  => "1+", "name" => "15+")
		);

$policeValues =  array(
		array("id"  => "", "name" => "Either Y or N"),
		array("id"  => "Y", "name" => "Yes"),
		array("id"  => "N", "name" => "No")
		);

$consequenceValues = array(
		array("id"  => "", "name" => "Select Consequence"),
		array("id"  => "none", "name" => "Verbal Warning"),
		array("id"  => "G", "name" => "Gym List"),
		array("id"  => "D", "name" => "Detention"),
		array("id"  => "I", "name" => "ISS"),
		array("id"  => "S", "name" => "Suspended"),
		array("id"  => "E", "name" => "Expelled"),
		array("id"  => "O", "name" => "Other")
		);

$lengthValues = array(
		array("id"  => "", "name" => "Select Number"),
		array("id"  => "N/A", "name" => "None"),
		array("id"  => "0", "name" => "Less Than 0.5 Day"),
		array("id"  => "1", "name" => "1 Day"),
		array("id"  => "2", "name" => "2 Days"),
		array("id"  => "3", "name" => "3 Days"),
		array("id"  => "4", "name" => "4 Days"),
		array("id"  => "5", "name" => "5 Days"),
		array("id"  => "6", "name" => "6 Days"),
		array("id"  => "7", "name" => "7 Days"),
		array("id"  => "8", "name" => "8 Days"),
		);
$dstatusValues = array(
		array("id"  => "", "name" => "Select Status"),
		array("id"  => "O", "name" => "Open"),
		array("id"  => "C", "name" => "Closed")
		);
$weaponValues = array(
		array("id"  => "", "name" => "Select One"),
		array("id"  => "3", "name" => "BB Gun / Pellet Gun"),
		array("id"  => "5", "name" => "Club / Stick"),
		array("id"  => "7", "name" => "Knife"),
		array("id"  => "8", "name" => "Martial Arts Weapon"),
		array("id"  => "9", "name" => "Paintball Gun"),
		array("id"  => "20", "name" => "Toy Gun"),
		array("id"  => "18", "name" => "Firecrackers"),		
		array("id"  => "21", "name" => "Cap Gun / Toy Gun"),		
		array("id"  => "22", "name" => "Handgun"),
		array("id"  => "23", "name" => "Rifle / Shotgun"),
		array("id"  => "14", "name" => "Other Firearm")
		);
		
$victimTypeValues = array(
		array("id"  => "", "name" => "Select Type"),
		array("id"  => "126", "name" => "Student"),
		array("id"  => "850", "name" => "Parent / Guardian"),
		array("id"  => "1232", "name" => "Substitute"),
		array("id"  => "3036", "name" => "Teacher"),
		array("id"  => "3038", "name" => "Counselor"),
		array("id"  => "3040", "name" => "Medical Staff"),
		array("id"  => "3041", "name" => "Administrator"),
		array("id"  => "3042", "name" => "Principal"),
		array("id"  => "3043", "name" => "Assistant Principal"),
		array("id"  => "3047", "name" => "Other School Staff"),
		array("id"  => "3048", "name" => "Transportation Staff"),
		array("id"  => "3050", "name" => "Custodial Staff"),
		array("id"  => "3052", "name" => "Paraprofessional / Aide"),
		array("id"  => "3054", "name" => "Law Enforcement Officer"),
		array("id"  => "3062", "name" => "Other Nonstudent Youth"),
		array("id"  => "3061", "name" => "Other Adult")

		);
            
$relatedDisabilitySelect =  array(
		array("id"  => "", "name" => "Either Y or N"),
		array("id"  => "Y", "name" => "Yes"),
		array("id"  => "N", "name" => "No")
		);
		
$IEPMeetSelect =  array(
		array("id"  => "", "name" => "Either Y or N"),
		array("id"  => "Y", "name" => "Yes"),
		array("id"  => "N", "name" => "No")
		);
		
$eduServicesSelect =  array(
		array("id"  => "", "name" => "Choose Status"),
		array("id"  => "NC", "name" => "No Change in Setting"),
		array("id"  => "ISS-Y", "name" => "ISS with Educational Services"),
		array("id"  => "ISS-N", "name" => "ISS without Services"),
		array("id"  => "S-Y", "name" => "Suspension with Services"),
		array("id"  => "ISS-N", "name" => "Suspension without Services"),
		array("id"  => "E-N", "name" => "Expulsion With Services"),
		array("id"  => "IAES-Y", "name" => "Interim Alternate Setting"),
		array("id"  => "UR", "name" => "Unilateral Removal")

		);
									
function getDisipline($studentid, $year) {
	global $db;
	
    $sql = "select * from discipline where studentid = '$studentid' and year = '$year' order by creation";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function createDisipline($studentid, $year, $kind, $site) {
	global $db;
	
    $sql = "insert into discipline 
    		set studentid = '$studentid',
    			year = '$year',
    			kind = '$kind',
    			site = '$site',
    			cuser = '$CurrentUserID'
    			";
    $db->get_results($sql);
    return ($db->insert_id);

}

function getDisciplineData ($dispID) {
	global $db;
	
    $sql = "select *, concat(fname, ' ', lname) as studentname from discipline, student where disciplineid = '$dispID' and discipline.studentid = student.studentid";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results[0]);

}

function saveDiscipline ($values) {
	global $db;

	while(list($var, $value) = each($values)) {
		if(substr($var, 0, 2) == "i_") {
			$setvalues .= $setvalues == "" ? "" : ",\n";
			$setvalues .= substr($var, 2, 100) . " = '$value'";
		}
	}
	$did = $values['disciplineid'];
	$sql = "UPDATE discipline SET $setvalues WHERE disciplineid = '$did'";
	echo $sql;
	$db->get_results($sql);
}

function varValue($list, $val) {
	foreach ($list as $value) {
	  if($value['id'] == $val) return ($value['name']);
	}
	return ("");
}
?>
