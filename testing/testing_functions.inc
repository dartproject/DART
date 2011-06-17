<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

function topMenu() {
	if(PDisplayB(B13)) {
		$str .= "<a href=index.php?module=testing&cmd=showGroupTestScores>Show Group Test Scores</a> ";
	} 
	if (PDisplayB(B14)) {
		$str .= "|
		<a href=index.php?module=testing&cmd=importData>Import Test Scores</a> |
		<a href=index.php?module=testing&cmd=editTestScores>Edit Test Scores</a><br>
		";
	}
	return ($str);
}

function getStyle () {

$str = <<<END
<style>
.bp {
	background: yellow;
}
.fbp 
{
	background: pink;
}
.NP {
	background: pink;
}
.Prof {
	background: lightgreen;
}
.Adv {
	background: lightblue;
}
.Proficient {
	background: lightgreen;
}
.Not_Proficient {
	background: pink;
}
.Q1 {
	background: pink;
}
.Q2 {
	background: yellow;
}
.Q3 {
	background: lightgreen;
}
.Q4 {
	background: lightblue;
}
.PH {
	background: lightgreen;
}
.PR {
	background: lightgreen;
} 
.IH {
	background: yellow;
} 
.IL {
	background: yellow;
}
.BH {
	background: pink;
}
.BL {
	background: pink;
} 
/* ESP screening index */
.c1  {
	background: pink;
} 
.c2  {
	background: pink;
} 
.c3  {
	background: yellow;
} 
.c4  {
	background: lightgreen;
} 
.c5  {
	background: lightgreen;
} 
.c6  {
	background: lightgreen;
} 
/* atriculation - ESP */
.cFBA  {
	background: pink;
} 
.cBA  {
	background: yellow;
} 
.cAvg  {
	background: lightgreen;
} 
/* atriculation - ESP */
.FBA  {
	background: pink;
} 
.BA  {
	background: yellow;
} 
.Avg  {
	background: lightgreen;
} 
</style>
END;

	return ($str);
}
function makeSQLOptions($sql, $sid) {
	global $db;

	$results = $db->get_results($sql);
	 
	$pulldown = "<option value=\"\">-- Select One -- </option>";									
	foreach ($results as $res) {
		$sel = ($res->id == $sid) ? "selected": "";
		$pulldown .= "<option value='". $res->id . "' $sel>" . $res->name . "</option>";
	}
					
	return ($pulldown);
}
function sortMenu($name, $orderval, $stdval, $sorttype='CHAR') {
//		return('<a href=\'{$url}sort=level&dir=$leveldir&orderval=gradelevel\'>Grade<br>Level $levelarrow</a>');
	$id = $orderval . $stdval;
	$id = str_replace("-", "", $id);
	$id = str_replace(".", "", $id);
	$id = str_replace("/", "", $id);
	$id = str_replace(" ", "", $id);

		return ("<a href='{\$url}sort={$id}&dir=\${$id}dir&orderval={$orderval}&stdval={$stdval}&sorttype=$sorttype'>{$name} \${$id}arrow</a>");	

}

function createStrandReport($strand, $ord, $test, $name=true) { 
	global $db;
	
	$spe_strand = str_replace("-", "_", $strand);
	$spe_strand = str_replace(".", "_", $spe_strand);
	$spe_strand = str_replace("/", "_", $spe_strand);
	$strandname = $name ? "<th>Strand Name</th>" : "";
	$strandvalue = $name ? '<td>$' . $spe_strand . '_status &nbsp;</td>' : "";
//	echo sortMenu('Raw Score', 'raw_value', "$spe_strand") . "<br>";
	$heading = addslashes("
		<th>Alaska ID</th>
		<th>" . sortMenu('Name', 'fname', '') . "</th>
		<th>" . sortMenu('Grade<br>Level', 'gradelevel', '', 'SIGNED') . "</th>
		<th>Strand</th>
		$strandname
		<th>" . sortMenu('Raw Score', 'raw_value', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Raw Score<br>Needed', 'raw_needed', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Raw Score<br>Difference','raw_difference', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Proficiency<br>Level', 'value', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Scale Score', 'value', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Scale Score<br>Needed for<br>Proficiency', 'needed', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Scale Score<br>Difference','difference', $strand, 'SIGNED') . "</th>");
		
	$row = addslashes('<tr>
			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
			<td>' . $strand . '</td>' .
			$strandvalue .
			'<td>$' . $spe_strand . '_value &nbsp;</td>
			<td>$' . $spe_strand . '_needed &nbsp;</td>
			<td>$' . $spe_strand . '_diff &nbsp;</td>
			<td>$' . $spe_strand . '_level &nbsp;</td>
			<td class=\"$' . $spe_strand . '_class\">$' . $spe_strand . '_scale_value &nbsp;</td>
			<td>$' . $spe_strand . '_scale_needed &nbsp;</td>
			<td>$' . $spe_strand . '_scale_diff &nbsp;</td>
			</tr>\n
		');
	$fields = addslashes('aid fname lname gradelevel '. $strand . ' ' . $spe_strand . '_class ' . $spe_strand . '_status ' . $spe_strand . '_value ' . $spe_strand . '_diff ' . $spe_strand . '_needed ' . $spe_strand . '_scale_value ' . $spe_strand . '_scale_diff ' . $spe_strand . '_scale_needed ' . $spe_strand . '_level needed_proficiency scale_score_dif');

//		$row = "test";
//		$heading = "test";
//		$fields = "test";
	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='$test', testtype='$strand', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createTerraNovaStrandReport($strand, $ord, $test) { 
	global $db;
	
	$spe_strand = str_replace("-", "_", $strand);
	$spe_strand = str_replace(".", "_", $spe_strand);
	$spe_strand = str_replace("/", "_", $spe_strand);
	$spe_strand = str_replace(" ", "_", $spe_strand);
	$heading = addslashes("
		<th>Alaska ID</th>
		<th>" . sortMenu('Name', 'fname', '') . "</th>
		<th>" . sortMenu('Grade<br>Level', 'gradelevel', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Normal<br>Curve<br>Equivalent', 'raw_value', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('National<br>Percentile<br>Rank', 'needed', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Scale<br>Score</th>', 'value', $strand, 'SIGNED') . "");
	$row = addslashes('<tr>
			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
			<td class=\"$' . $spe_strand . '_class\">$' . $spe_strand . '_value &nbsp;</td>
			<td>$' . $spe_strand . '_scale_needed &nbsp;</td>
			<td>$' . $spe_strand . '_scale_value &nbsp;</td>
			</tr>\n
		');
	$fields = addslashes('aid fname lname gradelevel ' . $spe_strand . '_value ' . $spe_strand . '_scale_needed ' . $spe_strand . '_scale_value '. $spe_strand . '_class ');

//		$row = "test";
//		$heading = "test";
//		$fields = "test";
	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='$test', testtype='$strand', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createESPStrandReport($strand, $ord, $test) { 
	global $db;
	
	$spe_strand = str_replace("-", "_", $strand);
	$spe_strand = str_replace(".", "_", $spe_strand);
	$spe_strand = str_replace("/", "_", $spe_strand);
	$spe_strand = str_replace(" ", "_", $spe_strand);
	$heading = addslashes("
		<th>Alaska ID</th>
		<th>" . sortMenu('Name', 'fname', '') . "</th>
		<th>" . sortMenu('Grade<br>Level', 'gradelevel', '', 'SIGNED') . "</th>
		<th>" . sortMenu('Birthdate', 'bday', '') . "</th>
		<th>" . sortMenu('Test Date', 'value', 'Testing date') . "</th>
		<th>" . sortMenu('Chronological Age', 'value', 'Chronological Age', 'SIGNED') . "</th>
		<th>" . sortMenu('Point Score', 'raw_value', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Screening Index', 'raw_needed', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('Standard Score', 'value', $strand, 'SIGNED') . "</th>
		<th>" . sortMenu('National Percentile', 'needed', $strand, 'SIGNED') . "</th>
		");
	$row = addslashes('<tr>
			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
			<td>$bday &nbsp;</td>
			<td>$Testing_date_scale_value &nbsp;</td>
			<td>$Chronological_Age_scale_value &nbsp;</td>
			<td>$' . $spe_strand . '_value &nbsp;</td>
			<td class=c$' . $spe_strand . '_needed >$' . $spe_strand . '_needed &nbsp;</td>
			<td>$' . $spe_strand . '_scale_value &nbsp;</td>
			<td>$' . $spe_strand . '_scale_needed &nbsp;</td>
			</tr>\n
		');
	$fields = addslashes('aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value ' . $spe_strand . '_scale_diff ' . $spe_strand . '_scale_needed ' . $spe_strand . '_scale_value '. $spe_strand . '_value '. $spe_strand . '_needed '. $spe_strand . '_raw_diff '. $spe_strand . '_test_date '. $spe_strand . '_class ');

//		$row = "test";
//		$heading = "test";
//		$fields = "test";
	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='$test', testtype='$strand', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}
function createESPStrandReport2($strand, $ord, $test) { 
	global $db;
	
	$spe_strand = str_replace("-", "_", $strand);
	$spe_strand = str_replace(".", "_", $spe_strand);
	$spe_strand = str_replace("/", "_", $spe_strand);
	$spe_strand = str_replace(" ", "_", $spe_strand);
	$heading = addslashes("
		<th>Alaska ID</th>
		<th>" . sortMenu('Name', 'fname', '') . "</th>
		<th>" . sortMenu('Grade<br>Level', 'gradelevel','', 'SIGNED') . "</th>
		<th>" . sortMenu('Birthdate', 'bday', '') . "</th>
		<th>" . sortMenu('Test Date', 'raw_value', 'Testing date') . "</th>
		<th>" . sortMenu('Chronological Age', 'Chronological Age') . "</th>
		<th>" . sortMenu('Point Score', 'raw_value', $strand) . "</th>
		<th>" . sortMenu('Screening Index', 'raw_needed', $strand) . "</th>
		");
	$row = addslashes('<tr>
			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
			<td>$bday &nbsp;</td>
			<td>$Testing_date_scale_value &nbsp;</td>
			<td>$Chronological_Age_scale_value &nbsp;</td>
			<td>$' . $spe_strand . '_value &nbsp;</td>
			<td class=c$' . $spe_strand . '_needed >$' . $spe_strand . '_needed &nbsp;</td>
			</tr>\n
		');
	$fields = addslashes('aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value ' . $spe_strand . '_scale_diff ' . $spe_strand . '_scale_needed ' . $spe_strand . '_scale_value '. $spe_strand . '_value '. $spe_strand . '_needed '. $spe_strand . '_raw_diff '. $spe_strand . '_test_date '. $spe_strand . '_class ');

//		$row = "test";
//		$heading = "test";
//		$fields = "test";
	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='$test', testtype='$strand', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createESPStrandReport3($strand, $ord, $test) { 
	global $db;
	
	$spe_strand = str_replace("-", "_", $strand);
	$spe_strand = str_replace(".", "_", $spe_strand);
	$spe_strand = str_replace("/", "_", $spe_strand);
	$spe_strand = str_replace(" ", "_", $spe_strand);
	$heading = addslashes("
		<th>Alaska ID</th>
		<th>" . sortMenu('Name', 'fname', '') . "</th>
		<th>" . sortMenu('Grade<br>Level', 'gradelevel', '', 'SIGNED') . "</th>
		<th>" . sortMenu('Birthdate', 'bday', '') . "</th>
		<th>" . sortMenu('Test Date', 'value', 'Testing date') . "</th>
		<th>" . sortMenu('Chronological Age', 'value', 'Chronological Age') . "</th>
		<th>" . sortMenu('Raw Score', 'raw_value', $strand) . "</th>
		<th>" . sortMenu('Descriptive Category', 'raw_needed', $strand) . "</th>
		");
	$row = addslashes('<tr>
			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
			<td>$bday &nbsp;</td>
			<td>$Testing_date_scale_value &nbsp;</td>
			<td>$Chronological_Age_scale_value &nbsp;</td>
			<td>$' . $spe_strand . '_value &nbsp;</td>
			<td  class=$' . $spe_strand . '_needed >$' . $spe_strand . '_needed &nbsp;</td>
			</tr>\n
		');
	$fields = addslashes('aid fname lname gradelevel Testing_date_scale_value Chronological_Age_scale_value ' . $spe_strand . '_scale_diff ' . $spe_strand . '_scale_needed ' . $spe_strand . '_scale_value '. $spe_strand . '_value '. $spe_strand . '_needed '. $spe_strand . '_raw_diff '. $spe_strand . '_test_date '. $spe_strand . '_class ');

//		$row = "test";
//		$heading = "test";
//		$fields = "test";
	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='$test', testtype='$strand', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}
function createOverallELP () { 
	global $db;
	
	$heading = addslashes("
	
<th>Alaska ID</th>
<th>" . sortMenu('Name', 'fname', '') . "</th>
<th>" . sortMenu('Testing Grade', 'gradelevel', '','SIGNED') . "</th>
<th>" . sortMenu('Listening Standard Score', 'value', 'Listening Scale Score') . "</th>
<th>" . sortMenu('Speaking Standard Score', 'value', 'Speaking Scale Score') . "</th>
<th>" . sortMenu('Reading Standard Score', 'value', 'Reading Scale Score') . "</th>
<th>" . sortMenu('Writing Standard Score', 'value', 'Writing Scale Score') . "</th>
<th>" . sortMenu('Comprehension Standard Score', 'value', 'Comprehension Scale Score') . "</th>
<th>" . sortMenu('Overall Standard Score', 'value', 'Overall Scale Score') . "</th>
<th>" . sortMenu('ELP Listening Proficiency Level', 'value', 'Listening Scale Score') . "</th>
<th>" . sortMenu('ELP Speaking Proficiency Level', 'value', 'Speaking Scale Score') . "</th>
<th>" . sortMenu('ELP Reading Proficiency Level', 'value', 'Reading Scale Score') . "</th>
<th>" . sortMenu('ELP Writing Proficiency Level', 'value', 'Writing Scale Score') . "</th>
<th>" . sortMenu('ELP Comprehension Proficiency Level', 'value', 'Comprehension Scale Score') . "</th>
<th>" . sortMenu('ELP Overall Proficiency Level', 'value', 'Overall Scale Score') . "</th>
<th>" . sortMenu('ELP Made Progress', 'value', 'ELP Made Progress') . "</th>

");

	$row = addslashes('<tr>
			<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
<td class=\"$Listening_Scale_Score_level\">$Listening_Scale_Score_scale_value &nbsp;</td>
<td class=\"$Speaking_Scale_Score_level\">$Speaking_Scale_Score_scale_value &nbsp;</td>
<td class=\"$Reading_Scale_Score_level\">$Reading_Scale_Score_scale_value &nbsp;</td>
<td class=\"$Writing_Scale_Score_level\">$Writing_Scale_Score_scale_value &nbsp;</td>
<td class=\"$Comprehension_Scale_Score_level\">$Comprehension_Scale_Score_scale_value &nbsp;</td>
<td class=\"$Overall_Scale_Score_level\">$Overall_Scale_Score_scale_value &nbsp;</td>
<td>$Listening_Scale_Score_level &nbsp;</td>
<td>$Speaking_Scale_Score_level &nbsp;</td>
<td>$Reading_Scale_Score_level &nbsp;</td>
<td>$Writing_Scale_Score_level &nbsp;</td>
<td>$Comprehension_Scale_Score_level &nbsp;</td>
<td>$Overall_Scale_Score_level &nbsp;</td>
<td>$ELP_Made_Progress_scale_value &nbsp;</td></tr>\n');
	$fields = addslashes('aid fname lname gradelevel Listening_Scale_Score_scale_value Speaking_Scale_Score_scale_value Reading_Scale_Score_scale_value Writing_Scale_Score_scale_value Comprehension_Scale_Score_scale_value Overall_Scale_Score_scale_value Overall_Scale_Score_level Listening_Scale_Score_level Speaking_Scale_Score_level Reading_Scale_Score_level Writing_Scale_Score_level Comprehension_Scale_Score_level Overall_Scale_Score_level ELP_Made_Progress_scale_value');


	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='ELP', testtype='Overall', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}
function testscoremap($test, $standard, $heading, $order, $second='') {
	global $db;
	
	$sql = "INSERT INTO testscoresmap set heading = '$heading', testscoresmap.order = '$order', standard = '$standard', test='$test', second='$second'
			ON DUPLICATE KEY UPDATE  heading = '$heading', testscoresmap.order = '$order', second='$second' ";
			
//	echo $sql;
	$db->get_results($sql);	

}
function cleartestscoremap() {
	global $db;
	$db->get_results("TRUNCATE testscoresmap ");	
}
function cleartestreports() {
	global $db;
	$db->get_results("TRUNCATE testreports ");	
}

function createOverallPPVT () { 
	global $db;
	
	$heading = addslashes("
	

<th>Alaska ID</th>
<th>" . sortMenu('Name', 'fname', '') . "</th>
<th>" . sortMenu('Testing Grade', 'gradelevel', '', 'SIGNED') . "</th>
<th>" . sortMenu('Birthdate', 'bday', '') . "</th>
<th>" . sortMenu('Pre Testing Date', 'fname', '') . "</th>
<th>" . sortMenu('Pre CA years-months', 'value', 'CA') . "</th>
<th>" . sortMenu('Pre RS', 'value', 'PreRS', 'SIGNED') . "</th>
<th>" . sortMenu('Pre SS', 'value', 'PreSS', 'SIGNED') . "</th>
<th>" . sortMenu('Pre Percentile', 'value', 'PrePercentile', 'SIGNED') . "</th>
<th>" . sortMenu('Pre NCE', 'value', 'PreNCE', 'SIGNED') . "</th>
<th>" . sortMenu('Pre Growth Scale Value', 'value', 'PreGrowthScale', 'SIGNED') . "</th>
<th>" . sortMenu('Pre AE', 'value', 'PreAE') . "</th>
<th>" . sortMenu('Pre Difference between CA and AE in years-months', 'value', 'Diff') . "</th>
<th>" . sortMenu('Pre Range in Years', 'value', 'Pre Range') . "</th>
<th>" . sortMenu('Post Testing Date', 'value', 'Post Testing') . "</th>
<th>" . sortMenu('Post CA years-months', 'value', 'PostRS') . "</th>
<th>" . sortMenu('Post RS', 'value', 'PostSS', 'SIGNED') . "</th>
<th>" . sortMenu('Post SS', 'value', 'PostSS', 'SIGNED') . "</th>
<th>" . sortMenu('Post Percentile', 'value', 'PostPercentile', 'SIGNED') . "</th>
<th>" . sortMenu('Post NCE', 'value', 'PostNCE', 'SIGNED') . "</th>
<th>" . sortMenu('Post Growth Scale Value', 'value', 'PostGrowScale', 'SIGNED') . "</th>
<th>" . sortMenu('Post AE', 'value', 'PostAE') . "</th>
<th>" . sortMenu('Post Difference between CA and AE in years-months', 'value', 'Post Diff') . "</th>
<th>" . sortMenu('Post Range in Years', 'value', 'Post Range') . "</th>

");

	$row = addslashes('<tr>
			<td nowrap><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td nowrap>$fname $lname</td>
			<td nowrap>$gradelevel &nbsp;</td>
			<td nowrap>$bday &nbsp;</td>
<td nowrap>$Testing_date_scale_value &nbsp;</td>
<td nowrap>$CA_scale_value &nbsp;</td>
<td nowrap>$PreRS_scale_value &nbsp;</td>
<td nowrap>$PreSS_scale_value &nbsp;</td>
<td nowrap>$PrePercentile_scale_value &nbsp;</td>
<td nowrap>$PreNCE_scale_value &nbsp;</td>
<td nowrap>$PreGrowthScale_scale_value &nbsp;</td>
<td nowrap>$PreAE_scale_value &nbsp;</td>
<td nowrap>$Diff_scale_value &nbsp;</td>
<td nowrap>$Pre_Range_scale_value &nbsp;</td>
<td nowrap>$Post_Testing_date_scale_value &nbsp;</td>
<td nowrap>$Post_CA_scale_value &nbsp;</td>
<td nowrap>$PostRS_scale_value &nbsp;</td>
<td nowrap>$PostSS_scale_value &nbsp;</td>
<td nowrap>$PostPercentile_scale_value &nbsp;</td>
<td nowrap>$PostNCE_scale_value &nbsp;</td>
<td nowrap>$PostGrowScale_scale_value &nbsp;</td>
<td nowrap>$PostAE_scale_value &nbsp;</td>
<td nowrap>$Post_Diff_scale_value &nbsp;</td>
<td nowrap>$Post_Range_scale_value &nbsp;</td>
</tr>\n');
	$fields = addslashes('aid fname lname gradelevel bday Testing_date_scale_value CA_scale_value PreRS_scale_value PreSS_scale_value PreAE_scale_value Diff_scale_value Pre_Range_scale_value Post_Testing_date_scale_value Post_CA_scale_value PostRS_scale_value PostSS_scale_value PostAE_scale_value Post_Diff_scale_value Post_Range_date_scale_value PostPercentile_scale_value PostNCE_scale_value PostGrowScale_scale_value PrePercentile_scale_value PreNCE_scale_value PreGrowthScale_scale_value PrePercentile_scale_value PreGrowthScale_scale_value PreNCE_scale_value');


	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='PPVT', testtype='Overall', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createOverallESP () { 
	global $db;
	
	$heading = addslashes("
	

<th>Alaska ID</th>
<th>" . sortMenu('Name', 'fname', '') . "</th>
<th>" . sortMenu('Testing Grade', 'gradelevel', '', 'SIGNED') . "</th>
<th>" . sortMenu('Birthdate', 'bday', '') . "</th>
<th>" . sortMenu('Chronological Age', 'value', 'Chronological Age', 'SIGNED') . "</th>
<th>" . sortMenu('Testing Date', 'value', 'Testing date') . "</th>

<th>" . sortMenu('Verbal Concepts Standard Score', 'value', 'Verbal Concepts', 'SIGNED') . "</th>
<th>" . sortMenu('Visual Discrimination Standard Score', 'value', 'Visual Discrimination', 'SIGNED') . "</th>
<th>" . sortMenu('Logical Relations Standard Score', 'value', 'Logical Relations', 'SIGNED') . "</th>
<th>" . sortMenu('Basic School Skills Standard Score', 'value', 'Basic School Skills', 'SIGNED') . "</th>
<th>" . sortMenu('Expressive Language Standard Score', 'value', 'Expressive Language', 'SIGNED') . "</th>
<th>" . sortMenu('Receptive Language Standard Score', 'value', 'Receptive Language', 'SIGNED') . "</th>
<th>" . sortMenu('Gross Motor Point Score', 'raw_value', 'Gross Motor', 'SIGNED') . "</th>
<th>" . sortMenu('Fine Motor Point Score', 'raw_value', 'Fine Motor', 'SIGNED') . "</th>
<th>" . sortMenu('Articulation Category', 'raw_value', 'Articulation', 'SIGNED') . "</th>

<th>" . sortMenu('Verbal Concepts Screening Index', 'raw_needed', 'Verbal Concepts') . "</th>
<th>" . sortMenu('Visual Discrimination Screening Index', 'raw_needed', 'Visual Discrimination', 'SIGNED') . "</th>
<th>" . sortMenu('Logical Relations Screening Index', 'raw_needed', 'Logical Relations', 'SIGNED') . "</th>
<th>" . sortMenu('Basic School Skills Screening Index', 'raw_needed', 'Basic School Skills', 'SIGNED') . "</th>
<th>" . sortMenu('Expressive Language Screening Index', 'raw_needed', 'Expressive Language', 'SIGNED') . "</th>
<th>" . sortMenu('Receptive Language Screening Index', 'raw_needed', 'Receptive Language', 'SIGNED') . "</th>
<th>" . sortMenu('Gross Motor Screening Index', 'raw_needed', 'Gross Motor', 'SIGNED') . "</th>
<th>" . sortMenu('Fine Motor Screening Index', 'raw_needed', 'Fine Motor', 'SIGNED') . "</th>

");

$row = addslashes('<tr>
		<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
			<td>$fname $lname</td>
			<td>$gradelevel &nbsp;</td>
			<td>$bday &nbsp;</td>
			<td>$Chronological_Age_scale_value &nbsp;</td>
<td>$Testing_date_scale_value &nbsp;</td>
<td class=\"c$Verbal_Concepts_needed\">$Verbal_Concepts_scale_value &nbsp;</td>
<td class=\"c$Visual_Discrimination_needed\">$Visual_Discrimination_scale_value &nbsp;</td>
<td class=\"c$Logical_Relations_needed\">$Logical_Relations_scale_value &nbsp;</td>
<td class=\"c$Basic_School_Skills_needed\">$Basic_School_Skills_scale_value &nbsp;</td>
<td class=\"c$Expressive_Language_needed\">$Expressive_Language_scale_value &nbsp;</td>
<td class=\"c$Receptive_Language_needed\">$Receptive_Language_scale_value &nbsp;</td>
<td class=\"c$Gross_Motor_needed\">$Gross_Motor_value &nbsp;</td>
<td class=\"c$Fine_Motor_needed\">$Fine_Motor_value &nbsp;</td>
<td class=\"$Articulation_needed\">$Articulation_needed &nbsp;</td>

<td >$Verbal_Concepts_needed &nbsp;</td>
<td>$Visual_Discrimination_needed &nbsp;</td>
<td>$Logical_Relations_needed &nbsp;</td>
<td>$Basic_School_Skills_needed &nbsp;</td>
<td>$Expressive_Language_needed &nbsp;</td>
<td>$Receptive_Language_needed &nbsp;</td>
<td>$Gross_Motor_needed &nbsp;</td>
<td>$Fine_Motor_needed &nbsp;</td>

</tr>\n');
	$fields = addslashes('aid fname lname gradelevel bday Testing_date_scale_value Verbal_Concepts_scale_value Visual_Discrimination_scale_value Logical_Relations_scale_value Basic_School_Skills_scale_value Expressive_Language_scale_value Receptive_Language_scale_value Gross_Motor_scale_value Fine_Motor_scale_value Articulation_scale_value  Verbal_Concepts_needed Visual_Discrimination_needed Logical_Relations_needed Basic_School_Skills_needed Expressive_Language_needed Receptive_Language_needed Gross_Motor_needed Fine_Motor_needed Articulation_needed Fine_Motor_value Gross_Motor_value Articulation_value Chronological_Age_scale_value');


	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='ESP', testtype='Overall', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createOverallSBA () { 
	global $db;
	
	$heading = addslashes("
	
<th>Alaska ID</th>
<th>" . sortMenu('Name', 'fname', '') . "</th>
<th>" . sortMenu('Grade<br>Level', 'gradelevel', '', 'SIGNED') . "</th>
<th>" . sortMenu('Reading<br>Proficiency', 'value', 'Reading', 'SIGNED') . "</th>
<th>" . sortMenu('Writing<br>Proficiency', 'value', 'Writing', 'SIGNED') . "</th>
<th>" . sortMenu('Math<br>Proficiency', 'value', 'Math', 'SIGNED') . "</th>
<th>" . sortMenu('Science<br>Proficiency', 'value', 'Science', 'SIGNED') . "</th>

<th>" . sortMenu('Reading<br>Scale Scores', 'value', 'Reading', 'SIGNED') . "</th>
<th>" . sortMenu('Writing<br>Scale Scores', 'value', 'Writing', 'SIGNED') . "</th>
<th>" . sortMenu('Math<br>Scale Scores', 'value', 'Math', 'SIGNED') . "</th>
<th>" . sortMenu('Science<br>Scale Scores', 'value', 'Science', 'SIGNED') . "</th>

<th>" . sortMenu('Gender', 'gender', '') . "</th>
<th>" . sortMenu('Ethnicity', 'ethnicity', '') . "</th>
<th>" . sortMenu('Economically<br>Disadvantage', 'NSLPEligible', '') . "</th>
<th>" . sortMenu('LEP', 'LEP', '') . "</th>
<th>" . sortMenu('SPED', 'sped', '') . "</th>
<th>" . sortMenu('504', 'sec504', '') . "</th>

");

$row = addslashes('<tr>
<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
<td>$fname $lname</td><td>$gradelevel &nbsp;</td>
<td>$Reading_level &nbsp;</td>
<td>$Writing_level &nbsp;</td>
<td>$Math_level &nbsp;</td>
<td>$Science_level &nbsp;</td>

<td class=\"$Reading_class\">$Reading &nbsp;</td>
<td class=\"$Writing_class\">$Writing &nbsp;</td>
<td class=\"$Math_class\">$Math &nbsp;</td>
<td class=\"$Science_class\">$Science &nbsp;</td>

<td>$gender</td><td>$ethnicity &nbsp;</td>
<td>$NSLPEligible &nbsp;</td><td>$LEP &nbsp;</td>
<td>$sped &nbsp;</td>
<td>$sec504 &nbsp;</td></tr>\n');
	$fields = addslashes('aid fname lname gradelevel Reading_level Reading_class Reading Writing_level Writing_class Writing Math_level Math_class Math Science_level Science_class Science gender ethnicity NSLPEligible LEP sped sec504');


	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='SBA', testtype='Overall', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createOverallTerraNova () { 
	global $db;
	
	$heading = addslashes("
	
<th>Student ID</th>
<th>" . sortMenu('Name', 'value', '') . "Name</th>
<th>" . sortMenu('Grade<br>Level', 'value', '') . "</th>
<th>" . sortMenu('Score Type', 'value', '') . "</th>
<th>" . sortMenu('Reading', 'raw_value', 'Reading', 'SIGNED') . "</th>
<th>" . sortMenu('Vocabulary', 'raw_value', 'Vocabulary', 'SIGNED') . "</th>
<th>" . sortMenu('Reading Composite', 'raw_value', 'Reading Composite', 'SIGNED') . "</th>

<th>" . sortMenu('Language', 'raw_value', 'Language', 'SIGNED') . "</th>
<th>" . sortMenu('Language<br>Mechanics', 'raw_value', 'Language Mechanics', 'SIGNED') . "</th>
<th>" . sortMenu('Language<br>Composite', 'raw_value', 'Language Composite', 'SIGNED') . "</th>
<th>" . sortMenu('Mathematics', 'raw_value', 'Mathematics', 'SIGNED') . "</th>

<th>" . sortMenu('Mathematics<br>Computation', 'raw_value', 'Math Computation', 'SIGNED') . "</th>
<th>" . sortMenu('Mathematics<br>Composite', 'raw_value', 'Math Composite', 'SIGNED') . "</th>
<th>" . sortMenu('Total<br>Score', 'raw_value', 'Total Score', 'SIGNED') . "</th>
<th>" . sortMenu('Science', 'raw_value', 'Science', 'SIGNED') . "</th>
<th>" . sortMenu('Social Studies', 'raw_value', 'Social Studies', 'SIGNED') . "</th>
<th>" . sortMenu('Spelling', 'raw_value', 'Spelling', 'SIGNED') . "</th>
<th>" . sortMenu('Word<br>Analysis', 'raw_value', 'Word Analysis', 'SIGNED') . "</th>

");

$row = addslashes('<tr>
<td rowspan=3><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
<td rowspan=3>$fname $lname</td>
<td rowspan=3>$gradelevel &nbsp;</td>
<td>NP</td>

<td>$Reading_scale_needed &nbsp;</td>
<td>$Vocabulary_scale_needed &nbsp;</td>
<td>$Reading_Composite_scale_needed &nbsp;</td>
<td>$Language_scale_needed &nbsp;</td>
<td>$Language_Mechanics_scale_needed &nbsp;</td>
<td>$Language_Composite_scale_needed &nbsp;</td>
<td>$Mathematics_scale_needed &nbsp;</td>
<td>$Math_Computation_scale_needed &nbsp;</td>
<td>$Math_Composite_scale_needed &nbsp;</td>
<td>$Total_Score_scale_needed &nbsp;</td>
<td>$Science_scale_needed &nbsp;</td>
<td>$Social_Studies_scale_needed &nbsp;</td>
<td>$Spelling_scale_needed &nbsp;</td>
<td>$Word_Analysis_scale_needed &nbsp;</td>
</tr>

<tr>
<td>NCE</td>

<td class=\"$Reading_level\">$Reading_value &nbsp;</td>
<td class=\"$Vocabulary_level\">$Vocabulary_value &nbsp;</td>
<td class=\"$Reading_Composite_level\">$Reading_Composite_value &nbsp;</td>
<td class=\"$Language_level\">$Language_value &nbsp;</td>
<td class=\"$Language_Mechanics_level\">$Language_Mechanics_value &nbsp;</td>
<td class=\"$Language_Composite_level\">$Language_Composite_value &nbsp;</td>
<td class=\"$Mathematics_level\">$Mathematics_value &nbsp;</td>
<td class=\"$Math_Computation_level\">$Math_Computation_value &nbsp;</td>
<td class=\"$Math_Composite_level\">$Math_Composite_value &nbsp;</td>
<td class=\"$Total_Score_level\">$Total_Score_value &nbsp;</td>
<td class=\"$Science_level\">$Science_value &nbsp;</td>
<td class=\"$Social_Studies_level\">$Social_Studies_value &nbsp;</td>
<td class=\"$Spelling_level\">$Spelling_value &nbsp;</td>
<td class=\"$Word_Analysis_level\">$Word_Analysis_value &nbsp;</td>


</tr>

<tr>
<td>Scale Score</td>

<td>$Reading_scale_value &nbsp;</td>
<td>$Vocabulary_scale_value &nbsp;</td>
<td>$Reading_Composite_scale_value &nbsp;</td>
<td>$Language_scale_value &nbsp;</td>
<td>$Language_Mechanics_scale_value &nbsp;</td>
<td>$Language_Composite_scale_value &nbsp;</td>
<td>$Mathematics_scale_value &nbsp;</td>
<td>$Math_Computation_scale_value &nbsp;</td>
<td>$Math_Composite_scale_value &nbsp;</td>
<td>$Total_Score_scale_value &nbsp;</td>
<td>$Science_scale_value &nbsp;</td>
<td>$Social_Studies_scale_value &nbsp;</td>
<td>$Spelling_scale_value &nbsp;</td>
<td>$Word_Analysis_scale_value &nbsp;</td>
</tr>
');

/*
<td>$Reading_level &nbsp;</td>
<td>$Writing_level &nbsp;</td>
<td>$Math_level &nbsp;</td>
<td>$Science_level &nbsp;</td>

<td class=\"$Reading_class\">$Reading &nbsp;</td>
<td class=\"$Writing_class\">$Writing &nbsp;</td>
<td class=\"$Math_class\">$Math &nbsp;</td>
<td class=\"$Science_class\">$Science &nbsp;</td>

<td>$gender</td><td>$ethnicity &nbsp;</td>
<td>$NSLPEligible &nbsp;</td><td>$LEP &nbsp;</td>
<td>$sped &nbsp;</td>
<td>$sec504 &nbsp;</td></tr>\n'
*/
	$fields = addslashes('aid fname lname gradelevel Reading Reading_scale_needed Reading_scale_value Reading_raw_needed Reading_value Reading_level Vocabulary Vocabulary_scale_needed Vocabulary_scale_value Vocabulary_raw_needed Vocabulary_value Vocabulary_level Reading_Composite Reading_Composite_scale_needed Reading_Composite_scale_value Reading_Composite_raw_needed Reading_Composite_value Reading_Composite_level Language Language_scale_needed Language_scale_value Language_raw_needed Language_value Language_level Language_Mechanics Language_Mechanics_scale_needed Language_Mechanics_scale_value Language_Mechanics_raw_needed Language_Mechanics_value Language_Mechanics_level Language_Composite Language_Composite_scale_needed Language_Composite_scale_value Language_Composite_raw_needed Language_Composite_value Language_Composite_level Mathematics Mathematics_scale_needed Mathematics_scale_value Mathematics_raw_needed Mathematics_value Mathematics_level Math_Computation Math_Computation_scale_needed Math_Computation_scale_value Math_Computation_raw_needed Math_Computation_value Math_Computation_level Math_Composite Math_Composite_scale_needed Math_Composite_scale_value Math_Composite_raw_needed Math_Composite_value Math_Composite_level Total_Score Total_Score_scale_needed Total_Score_scale_value Total_Score_raw_needed Total_Score_value Total_Score_level Science Science_scale_needed Science_scale_value Science_raw_needed Science_value Science_level Social_Studies Social_Studies_scale_needed Social_Studies_scale_value Social_Studies_raw_needed Social_Studies_value Social_Studies_level Spelling Spelling_scale_needed Spelling_scale_value Spelling_raw_needed Spelling_value Spelling_level Word_Analysis Word_Analysis_scale_needed Word_Analysis_scale_value Word_Analysis_raw_needed Word_Analysis_value Word_Analysis_level gender ethnicity NSLPEligible LEP sped sec504');



	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='TerraNova', testtype='Overall', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function createOverallHSGQE () { 
	global $db;
	
//	<a href={$url}sort=fname&dir=$fnamedir&orderval=fname&stdval=>Name $fnamearrow</a>
	
//	echo sortMenu('Name', 'fname', '') . "<br><br>";
	$heading = addslashes('
	
<th>Alaska ID</th>
<th>' . sortMenu('Name', 'fname', '') . '</th>
<th>' . sortMenu('Grade Level', 'gradelevel', '', 'SIGNED') . '</th>
<th>' . sortMenu('Reading Proficiency', 'level', 'Reading') . '</th>
<th>' . sortMenu('Writing Proficiency', 'level', 'Writing') . '</th>
<th>' . sortMenu('Math Proficiency', 'level', 'Math') . '</th>

<th>' . sortMenu('Reading<br>Scale Scores', 'value', 'Reading') . '</th>
<th>' . sortMenu('Writing<br>Scale Scores', 'value', 'Writing') . '</th>
<th>' . sortMenu('Math<br>Scale Scores', 'value', 'Math') . '</th>

<th>' . sortMenu('Gender', 'gender', '') . '</th>
<th>' . sortMenu('Ethnicity', 'ethnicity', '') . '</th>
<th>' . sortMenu('Economically<br>Disadvantage', 'NSLPEligible', '') . '</th>
<th>' . sortMenu('LEP', 'lep', '') . '</th>
<th>' . sortMenu('SPED', 'sped', '') . '</th>
<th>' . sortMenu('SEC', 'sec504', '') . '</th>


');

$row = addslashes('<tr>
<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
<td>$fname $lname</td>
<td>$gradelevel &nbsp;</td>
<td>$Reading_level &nbsp;</td>
<td>$Writing_level &nbsp;</td>
<td>$Math_level &nbsp;</td>
<td class=\"$Reading_class\">$Reading &nbsp;</td>
<td class=\"$Writing_class\">$Writing &nbsp;</td>
<td class=\"$Math_class\">$Math &nbsp;</td>

<td>$gender</td><td>$ethnicity &nbsp;</td><td>$NSLPEligible &nbsp;</td><td>$LEP &nbsp;</td>
<td>$sped &nbsp;</td><td>$sec504 &nbsp;</td></tr>\n');

	$fields = addslashes('aid fname lname gradelevel Reading_class Reading_level Reading Writing_class Writing_level  Writing Math_class Math_level Math gender ethnicity NSLPEligible LEP sped sec504');


	$sql = "INSERT INTO testreports set heading = '$heading', row = '$row', testreports.fields = '$fields', test='HSGQE', testtype='Overall', ord='$ord'
			ON DUPLICATE KEY UPDATE  heading = '$heading', row = '$row', testreports.fields = '$fields', ord='$ord'";
			
//	echo $sql;
	$db->get_results($sql);	
}

function menusort($name) {
	return("<a href='\$url?sort=\$sort&direction=\$direction'><a imag='\$arrow'>[arrowtext]</a>");
}

?>
