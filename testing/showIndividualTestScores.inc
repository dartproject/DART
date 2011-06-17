<?php 

if(!PDisplayB(B13) ) {
	Header("Location: index.php?cmd=noPrivilege&type=Testing&notes=Can not see testing data");
}

if($_GET['go'] != '') {
cleartestscoremap();
$i=0;
testscoremap('SBA','Reading', 'Reading Scale Scores', $i++);
testscoremap('SBA','R-SC1', '', $i++);
testscoremap('SBA','R-SC2', '', $i++);
testscoremap('SBA','R-SC3', '', $i++);
testscoremap('SBA','Writing', 'Writing Scale Scores', $i++);
testscoremap('SBA','W-SC1', '', $i++);
testscoremap('SBA','W-SC2', '', $i++);
testscoremap('SBA','W-SC3', '', $i++);
testscoremap('SBA','Math', 'Math Scale Scores', $i++);
testscoremap('SBA','M-SC1', '', $i++);
testscoremap('SBA','M-SC2', '', $i++);
testscoremap('SBA','M-SC3', '', $i++);
testscoremap('SBA','M-SC4', '', $i++);
testscoremap('SBA','M-SC5', '', $i++);
testscoremap('SBA','M-SC6', '', $i++);
testscoremap('SBA','Science', 'Science Scale Scores', $i++);
testscoremap('SBA','S-SC1', '', $i++);
testscoremap('SBA','S-SC2', '', $i++);
testscoremap('SBA','S-SC3', '', $i++);
testscoremap('SBA','S-SC4', '', $i++);
	
testscoremap('HSGQE','Reading', '', $i++);
testscoremap('HSGQE','R4.1', '', $i++);
testscoremap('HSGQE','R4.2', '', $i++);
testscoremap('HSGQE','R4.3', '', $i++);
testscoremap('HSGQE','R4.4', '', $i++);
testscoremap('HSGQE','R4.7', '', $i++);
testscoremap('HSGQE','R4.8', '', $i++);
testscoremap('HSGQE','Writing', '', $i++);
testscoremap('HSGQE','W4.1/4.2', '', $i++);
testscoremap('HSGQE','W4.3', '', $i++);
testscoremap('HSGQE','W4.4', '', $i++);
testscoremap('HSGQE','Math', '', $i++);
testscoremap('HSGQE','M1.4', '', $i++);
testscoremap('HSGQE','M2.4', '', $i++);
testscoremap('HSGQE','M3.4', '', $i++);
testscoremap('HSGQE','M4.4', '', $i++);
testscoremap('HSGQE','M5.3', '', $i++);
testscoremap('HSGQE','M6.3', '', $i++);

testscoremap('PPVT', 'Testing date', 'Pre Testing Date', $i++);
testscoremap('PPVT', 'CA', 'Pre CA years-months', $i++);
testscoremap('PPVT', 'PreRS', 'Pre RS', $i++);
testscoremap('PPVT', 'PreSS', 'Pre SS', $i++);

testscoremap('PPVT', 'PrePercentile', 'Pre Percentile', $i++);
testscoremap('PPVT', 'PreNCE', 'Pre NCE', $i++);
testscoremap('PPVT', 'PreGrowthScale', 'Pre Growth', $i++);

testscoremap('PPVT', 'PreAE', 'Pre AE', $i++);
testscoremap('PPVT', 'Diff', 'Pre Difference between CA and AE in years-months', $i++);
testscoremap('PPVT', 'Pre Range', 'Pre Range in Years', $i++);
testscoremap('PPVT', 'Post Testing date', 'Post Testing date', $i++);
testscoremap('PPVT', 'Post CA', 'Post CA years-months', $i++);
testscoremap('PPVT', 'PostRS', 'Post RS', $i++);
testscoremap('PPVT', 'PostSS', 'Post SS', $i++);

testscoremap('PPVT', 'PostPercentile', 'Post Percentile', $i++);
testscoremap('PPVT', 'PostNCE', 'Post NCE', $i++);
testscoremap('PPVT', 'PostGrowScale', 'Post Growth', $i++);

testscoremap('PPVT', 'PostAE', 'Post AE',$i++);
testscoremap('PPVT', 'Post Diff', 'Post Difference between CA and AE in years-months', $i++);
testscoremap('PPVT', 'Post Range', 'Post Range in Years', $i++);

testscoremap('ESP', 'Testing date', 'Testing Date', $i++);
testscoremap('ESP', 'Chronological Age', 'Chronological Age', $i++);
testscoremap('ESP', 'Verbal Concepts', 'Verbal Concepts Standard Score', $i++,'Verbal Concepts Screening Index');
testscoremap('ESP', 'Visual Discrimination', 'Visual Discrimination Standard Score', $i++,'Visual Discrimination Screening Index');
testscoremap('ESP', 'Logical Relations', 'Logical Relations Standard Score', $i++,'Logical Relations Screening Index');
testscoremap('ESP', 'Basic School Skills', 'Basic School Skills Standard Score', $i++,'Basic School Skills Screening Index');
testscoremap('ESP', 'Expressive Language', 'Expressive Language Standard Score', $i++,'Expressive Language Screening Index');
testscoremap('ESP', 'Receptive Language', 'Receptive Language Standard Score', $i++,'Receptive Language Screening Index');
testscoremap('ESP', 'Gross Motor', 'Gross Motor Point Score', $i++, 'Gross MotorPoint Screening Index');
testscoremap('ESP', 'Fine Motor', 'Fine Motor Point Score', $i++, 'Fine Motor Screening Index');
testscoremap('ESP', 'Articulation', 'Articulation Category', $i++, 'second');

testscoremap('ELP', 'Listening Scale Score', 'Listening Standard Score', $i++, 'ELP Listening Proficiency Level');
testscoremap('ELP', 'Speaking Scale Score', 'Speaking Standard Score', $i++, 'ELP Speaking Proficiency Level');
testscoremap('ELP', 'Reading Scale Score', 'Reading Standard Score', $i++, 'ELP Reading Proficiency Level');
testscoremap('ELP', 'Writing Scale Score', 'Writing Standard Score', $i++, 'ELP Writing Proficiency Level');
testscoremap('ELP', 'Comprehension Scale Score', 'Comprehension Standard Score', $i++, 'ELP Comprehension Proficiency Level');
testscoremap('ELP', 'Overall Scale Score', 'Overall Scale Score', $i++, 'ELP Overall Proficiency Level');
testscoremap('ELP', 'ELP Made Progress', 'ELP Made Progress', $i++,'third');

//testscoremap('ELP', 'ELP Made Progress', 'ELP Made Progress', $i++);

testscoremap('TerraNova', 'Reading', 'Reading', 1);
testscoremap('TerraNova', 'Vocabulary', 'Vocabulary', 2);
testscoremap('TerraNova', 'Reading Composite', 'Reading Composite', 3);
testscoremap('TerraNova', 'Language', 'Language', 4);
testscoremap('TerraNova', 'Language Mechanics', 'Language Mechanics', 5);
testscoremap('TerraNova', 'Language Composite', 'Language Composite', 6);
testscoremap('TerraNova', 'Mathematics', 'Mathematics', 7);
testscoremap('TerraNova', 'Math Computation','Math Computation', 8);
testscoremap('TerraNova', 'Math Composite','Math Composite', 9);
testscoremap('TerraNova', 'Total Score', 'Total Score', 10);
testscoremap('TerraNova', 'Science', 'Science', 11);
testscoremap('TerraNova', 'Social Studies', 'Social Studies', 12);
testscoremap('TerraNova', 'Spelling', 'Spelling', 13);
testscoremap('TerraNova', 'Word Analysis', 'Word Analysis', 14);

}

$aid = $_GET['aid'];
$style = getStyle();
$body .= "
$style
$grpOptions<br>";

$sql1 = "Select * from student where alaskaid = '$aid' ";
$studentInfo = $db->get_results($sql1, ARRAY_A);
$studentInfo = $studentInfo[0];
while(list($var, $val) = each ($studentInfo)) ${$var} = $val;
$name = "$fname $lname";
$menu = topmenu();

$body .= "$menu<h1>$name</h1>
<table border=1>
<tr><th>Student Name</td><td>$name </td><th>Gender</th><td>$gender</td><th>LEP</th><td>$LEPStatus</td></tr>
<tr><th>AK ID#</th><td>$alaskaid</td><th>Ethnicity</th><td>$ethnicity &nbsp;</td><th>SPED</th><td>$sped</td></tr>
<tr><th>Current site</td><td>$site</td><th>Birthdate</th><td>$bday</td><th>504</th><td>$sec504</td></tr>
<tr><th>Current grade	</td><td>$grade</td></tr>
</table><br><br>
";

$sql = "SELECT * FROM testscoresmap, tests where id=test ORDER BY testscoresmap.order";
$testheading = $db->get_results($sql, ARRAY_A);	
foreach($testheading as $t) {
	$theading[$t['test']]['heading'][] = ($t['heading'] == '') ? $t['standard'] : $t['heading'] ;
	$theading[$t['test']]['second'][] = $t['second'] ;
	$theading[$t['test']]['standard'][] = $t['standard'];
	$theading[$t['test']]['legend'] = $t['legend'];
}

$sql = "SELECT testscores.*, heading FROM testscores, testscoresmap, tests
			WHERE testscores.alaskaid = '$aid' and
				testscoresmap.test = testscores.test and			
				testscoresmap.standard = testscores.standard and
				testscores.test = tests.id
			ORDER BY ord, testscoresmap.order, testscoresmap.test, testscores.year ASC, testscoresmap.subject ";
// echo $sql;
$testscores = $db->get_results($sql, ARRAY_A);
//print_r($testscores);
//echo $sql;
//print_r($testscores);
foreach($testscores as $t) {
//	$tests[$t['test']][$t['year']]['scores'][$t['standard']] = $t['value'];
	$tests[$t['test']][$t['year']]['scores'][$t['standard']]['value'] = $t['value'];
	$tests[$t['test']][$t['year']]['scores'][$t['standard']]['level'] = str_replace(' ', '_', $t['level']);
	$tests[$t['test']][$t['year']]['scores'][$t['standard']]['needed'] = $t['raw_needed'];
	$tests[$t['test']][$t['year']]['scores'][$t['standard']]['raw_value'] = $t['raw_value'];
	$tests[$t['test']][$t['year']]['scores'][$t['standard']]['scale_needed'] = $t['needed'];
//	$tests[$t['test']][$t['year']]['scores']['heading'][] = ($t['heading'] == '') ? $t['standard'] : $t['heading'] ;
	$tests[$t['test']][$t['year']]['test'] = $t['test'];
	$tests[$t['test']][$t['year']]['year'] = $t['year'];
	$tests[$t['test']][$t['year']]['site'] = $t['site'];
	$tests[$t['test']][$t['year']]['grade'] = $t['gradelevel'];
}
//print_r($tests['SBA']);
//print_r($theading);
foreach($tests as $setoftests) {
//	print_r($setoftests);
	$tval = '';
	foreach($setoftests as $test) {
		$title = $test['test'];
		$year = $test['year'];
		$grade = $test['grade'];
		$site = $test['site'];
		$grade = $test['grade'];
		$theader = "";
		$theader2 = "";
		$add = "";
		$theader3 = "";
		$add3 = "";
//		$theader2 = "";
$addtitle = '';
		if($title == 'TerraNova') $addtitle = "<td>NP</td>";
		$tvalues[$year] = "<tr><td>$title</td><td>$year</td><td>$grade</td> $addtitle";
//		$tvalues2[$year] = "<tr><td>$title</td><td>$year</td><td>$grade</td>";
/*		while(list($var, $val) = each($test['scores'])) {
			$theader .= "<th width=30>$var</th>";
			$tvalues[$year] .= "<td>$val &nbsp;</td>";
		}
*/		$i = 0;
		$here = $test['scores'];
//		echo "<br>$title-$year<br>";
//		print_r($theading[$title]);
//		echo "<br><br>--";
//		print_r($here);
//		echo "--<br><br>";

		$legend = $theading[$title]['legend'];;
		foreach($theading[$title]['standard'] as $row) {
			$name = $theading[$title]['heading'][$i];
			$var = $row;
			$val = $here[$var]['value'];
			$lvl = '';
//			$val2 = $here[$var]['needed'];
			if(($title == 'SBA') or ($title == 'HSGQE') or ($title == 'ELP') or ($title=='TerraNova')) $lvl = "class=" . $here[$var]['level'];
			if($title == 'ESP') $lvl = "class=c" . $here[$var]['needed'];
			$theader .= ($theading[$title]['second'][$i] != 'third') ? "<th width=30>$name</th>" : "";
//			$theader2 .= "<th width=30>$name<br>Screening Index</th>";
			if($title == 'ESP') {
				$second = trim($theading[$title]['second'][$i]);
				if(trim($second) != "" and $second != 'second') { 
					$theader2 .= "<th width=30>$second</th>";
					$add .= "<td>{$here[$var]['needed']}</td>"; 
				}
				if(substr($name, 0, 4) == 'Fine') $val = $here[$var]['raw_value'];
				else if(substr($name, 0, 5) == 'Gross') $val = $here[$var]['raw_value'];
				else if($second == 'second') $val = $here[$var]['needed'];
				$tvalues[$year] .= "<td $lvl>$val &nbsp;</td>";
			} else if($title == 'ELP') {
				$second = $theading[$title]['second'][$i];
				if($second == 'third') {
						$theader3 .= "<th width=30>$name</th>";
						$add3 .= "<td $lvl>$val &nbsp;</td>"; 
				} else {
					if(trim($second) != "" and $second != 'second') { 
						$theader2 .= "<th width=30>$second</th>";
						$add .= "<td> {$here[$var]['level']} &nbsp;</td>"; 
					}
					$tvalues[$year] .= "<td $lvl>$val &nbsp;</td>";
				}
			} else if($title == 'TerraNova') {
				$tvalues[$year] .= "<td>{$here[$var]['scale_needed']} &nbsp;</td>";			
				$middlevalue[$year] .= "<td $lvl>{$here[$var]['raw_value']} &nbsp;</td>";
				$bottomvalue[$year] .= "<td>$val &nbsp;</td>";
			} else if($title == 'PPVT') {
				$tvalues[$year] .= "<td $lvl nowrap>$val &nbsp;</td>";			
			} else {
				$tvalues[$year] .= "<td $lvl>$val &nbsp;</td>";			
			}
//			$tvalues2[$year] .= "<td>$val2 &nbsp;</td>";
			$i++;
			$lvl = '';
		}
		if($title == 'TerraNova') {
			$tval .= $tvalues[$year] . "</tr><tr><td colspan=3><td>NCE</td>" . $middlevalue[$year] . "</tr><tr><td colspan=3><td>Scale Scores</td>" . $bottomvalue[$year] .  "</tr>";
			$theader = '<th>TYPE</th>'.$theader;
//			$tval .= $tvalues[$year] . "</tr>";
		 
//		} else if($title == 'ESP') {
//			$tval .= $tvalues[$year] . $tvalues2[$year] . "</tr>";
		} else {
			$tval .= $tvalues[$year] . " $add$add3</tr>";
		}
		$tvalues[$year] = "";
		$middlevalue[$year] = "";
		$bottomvalue[$year] = "";
//		$tvalues2[$year] = "";
	}
//	if($title == 'ESP') { $theader .= $theader2; }
	$body .= "$legend<table border=1><tr><th>Test</th><th>Year</th><th>Grade</th>$theader$theader2$theader3</tr>$tval</table><br><br>";
	$tvalues[$year] = "";
	$middlevalue[$year] = "";
	$bottomvalue[$year] = "";
}

include_once ("template.inc");
/*
// Test Scores Start
	$sql = "SELECT testscores.* FROM testscores, students
			WHERE testscores.alaskaid = '$aid' and
				testscores.year = '$year' and
				testscoresmap.test = testscores.test and			
				testscoresmap.standard = testscores.standard and				
				testscoresmap.subject = '$area'
			GROUP BY testscores.standard
			ORDER BY testscoresmap.order";
//	echo $sql;
	$testscores = $db->get_results($sql, ARRAY_A);

	
	if ($testscores != "") {
		$theader = "";
		$tvalue = "";
		foreach($testscores as $row) {
			$title = $row['standard'];
			$tval = $row['value'];
			$theader .= "<th width=30>$title</th>";
			$tvalue .= "<td>$tval &nbsp;</td>";
			$test = $row['test'];
		}
		$body .= "<table border=1><tr><th rowspan=2 align=top>$test</th>$theader</tr><tr>$tvalue </tr></table>";
	}
*/

?>