<?php

  include_once ("./testing/testing_functions.inc");
  
  	$body .= getStyle();
	$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
	$nocredit = "<img src=\"http://dart.bssd.org/images/1pix.gif\" alt=\"\" border=\"0\">";

	$id = $_GET['student_id'];
//	$id = '530105'; // 530105'; //
//	$id = '10219';

	$values = array("ca","cs","sc", "ss", "ls", "te", "ma", "wr", "re");
	foreach($values as $val1) {
		for($j=1; $j<=15;$j++) {
			for($i=1; $i<5;$i++) {
				$data["$val1$j".".".$i] = "$nocredit";
			}
			$data["$val1$j".".c"] = "";
		}
	}
	for($i=1; $i <8;$i++) $data['elective'.$i] = '<td nowrap="nowrap" height="30" colspan="11"></td>';
	$sql = "SELECT * FROM scoreweight";
	$ws = $db->get_results($sql, ARRAY_A);
	foreach($ws as $w ) {
		$sid = strtolower($w['subjectid']);
		$weight[$sid] = $w['weight'];
		$var[] = "[{$sid}.w]"; $val[] = $w['weight'];
	}
	$student = getStudentInfo($id);
	getValuesStudent($id, &$data, $weight);
	getValuesStudentCurrentClasses($id, &$data, $weight);
	getValuesStudentElectives($id, &$data, $weight);
	$var[] = "[name]"; $val[] = $student['fname'] . " " . $student['lname'];
	$var[] = "[school]"; $val[] = $student['village'];
	$var[] = "[tests]"; $val[] = reportHSGQE($id);
//	print_r($data);
	while(list($var1, $val1) = each($data)  ) { $var[] = "[$var1]"; $val[] = $val1; }
	$filestr = file_get_contents("./graduation_report.html");
	$body .= str_replace($var, $val, $filestr);
		
	include("template.inc");;
	
	function getValuesStudent($id, $data, $weight) {
		global $db;
		$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
		$sql = "SELECT * FROM studentlevel, subjects WHERE studentlevel.subject = subjects.id and studentid = '$id' and final <> '0000-00-00 00:00:00'";
		$results = $db->get_results($sql, ARRAY_A);
//		print_r($results);
		foreach($results as $row) {
			if($row['core'] == 'x') {
				$sublvl = strtolower($row['subject']) . (int)$row['level'];
				$subject = strtolower($row['subject']);
				$data[$sublvl.".1"] = "$credit"; 
				$data[$sublvl.".2"] = "$credit"; 
				$data[$sublvl.".3"] = "$credit"; 
				$data[$sublvl.".4"] = "$credit"; 
				$data[$sublvl.".c"] = $weight[$subject]; 
			} else {
			
			}
			$data['credit'] += $weight[$subject];
		}
//		print_r($data);
//		return($data);
	}

	function getValuesStudentCurrentClasses($id, $data, $weight) {
		global $db;
		$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
		$sql = "SELECT standards.subject as sub, standards.level as lvl, grades.* 
			FROM (subjects, studentlevel, standards) 
			LEFT JOIN grades ON grades.subject = standards.subject and 
				grades.level=standards.level and 
				grades.std = standards.std and 
				grades.studentid = studentlevel.studentid
			WHERE 
				subjects.id = studentlevel.subject and
				subjects.core = 'x' and
				standards.type = 'std' and
				studentlevel.subject = standards.subject and 
				studentlevel.level = standards.level and 
				studentlevel.final = '0000-00-00 00:00:00' and
				studentlevel.studentid = '$id'
			ORDER BY standards.subject, standards.level, standards.std
		";
//		echo $sql;
		$grades = $db->get_results($sql, ARRAY_A);
		foreach($grades as $grade) {
			$sub_lvl = strtolower($grade['sub']) . (int)$grade['lvl'];
			if($grade['value'] == 'PRO' or $grade['value'] == 'ADV') {
				$scores[$sub_lvl]['pass'] += 1;
			}
			$scores[$sub_lvl]['total'] += 1;
			$scores[$sub_lvl]['subject'] = $grade['sub'];
			$scores[$sub_lvl]['level'] = $grade['lvl'];
			$scores[$sub_lvl]['sub_lvl'] = $sub_lvl;
		}
		foreach($scores as $score) {
			$subject = strtolower($score['subject']);
			$sublvl = $score['sub_lvl'];
			$quad = floor(($score['pass']/$score['total'])/.25);
			for($i=0; $i < $quad; $i++) {
				$j = $i+1;
				$data[$sublvl.".$j"] = "$credit";
			}
			if($quad > 0) {
				$c = $weight[$subject]*$quad*.25;
				$data[$sublvl.".c"] = $c; 
				$data['credit'] += $c;
			}
		}
	}
	
	function getValuesStudentElectives($id, $data, $weight) {
		global $db;
		$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
		$sql = "SELECT standards.subject as sub, standards.level as lvl, grades.*, standards.shortname
			FROM (subjects, studentlevel, standards) 
			LEFT JOIN grades ON grades.subject = standards.subject and 
				grades.level=standards.level and 
				grades.std = standards.std and 
				grades.studentid = studentlevel.studentid
			WHERE 
				subjects.id = studentlevel.subject and
				subjects.core = '' and
				standards.type = 'std' and
				studentlevel.subject = standards.subject and 
				studentlevel.level = standards.level and
				studentlevel.studentid = '$id'
			ORDER BY standards.subject, standards.level, standards.std
		";
//		echo $sql;
		$grades = $db->get_results($sql, ARRAY_A);
//		print_r($grades);
		foreach($grades as $grade) {
			$sub_lvl = strtolower($grade['sub']) . (int)$grade['lvl'];
			if($grade['value'] == 'PRO' or $grade['value'] == 'ADV') {
				$scores[$sub_lvl]['pass'] += 1;
			}
			$scores[$sub_lvl]['total'] += 1;
			$scores[$sub_lvl]['subject'] = $grade['sub'];
			$scores[$sub_lvl]['level'] = $grade['lvl'];
			$scores[$sub_lvl]['sub_lvl'] = $sub_lvl;
			$scores[$sub_lvl]['name'] = $grade['shortname'];
		}
		print_r($scores);
		$k=1;
		foreach($scores as $score) {
			$subject = strtolower($score['subject']);
			$sublvl = $score['sub_lvl'];
			$quad = floor(($score['pass']/$score['total'])/.25);
			for($i=1; $i < 5; $i++) ${"flag".$j} = "$nocredit";
			for($i=0; $i < $quad; $i++) {
				$j = $i+1;
				${"flag".$j} = "$credit";
			}
			$c = '';
			if($quad > 0) {
				$c = $weight[$subject]*$quad*.25;
			}
			echo "HERE";
			$data['elective'.$k] = <<<END
			<td valign="bottom" nowrap="nowrap" height="32" colspan="5">
			<div align="right"><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2"><b>College Prep Writing L9</b></font></font></div>
			</td>
			<td width="32" nowrap="nowrap" height="30">
			<div align="center">$flag1<img border="0" alt="" src="http://dart.bssd.org/images/1pix.gif" /></div>
			</td>
			<td width="32" nowrap="nowrap" height="30">
			<div align="center"><img border="0" alt="" src="http://dart.bssd.org/images/1pix.gif" />$flag2</div>
			</td>
			<td width="33" nowrap="nowrap" height="30">
			<div align="center">$flag3<img border="0" alt="" src="http://dart.bssd.org/images/1pix.gif" /></div>
			</td>
			<td width="32" nowrap="nowrap" height="30">
			<div align="center">$flag4<img border="0" alt="" src="http://dart.bssd.org/images/1pix.gif" /></div>
			</td>
			<td width="32" valign="bottom" nowrap="nowrap" height="30">
			<div align="center"><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2">$c</font></font><img border="0" alt="" src="http://dart.bssd.org/images/1pix.gif" /></div>
			</td>
END;
			$k++;	
		}
	}


	function reportHSGQE($sid) {
		global $db;
		
		$sql = "select testscores.* from testscores, student where studentid = '$sid' and testscores.alaskaid = student.alaskaid and test = 'HSGQE' and (standard ='READING' or standard = 'WRITING' or standard = 'MATH') ORDER BY year ASC";
		$testvalues = $db->get_results($sql, ARRAY_A);
		foreach($testvalues as $value) {
			$testlist[$value['year']][$value['standard']]['prof'] = $value['level'];
			$testlist[$value['year']][$value['standard']]['ss'] = $value['needed'];
			$testlist[$value['year']]['year'] = $value['year'];
			$testlist[$value['year']]['grade'] = $value['gradelevel'];
			$testlist[$value['year']]['alaskaid'] = $value['alaskaid'];
		}
		$str .= "<table border=0 cellpadding=3> <tr>
			<th>Legend:</th>
			<td class=Proficient>Proficient</td>
			<td class=Not_Proficient>Not Proficient</td>
			</tr></table>";
		$str .= "<table border=1 width=800px><tr>
			<th>Alaska ID</th>
			<th>Year</th>
			<th>Grade Level</th>
			<th>Reading Proficiency</th>
			<th>Writing Proficiency</th>
			<th>Math Proficiency</th>
			<th>Reading Scale Scores</th>
			<th>Writing Scale Scores</th>
			<th>Math Scale Scores</th>
			</tr>";
		foreach($testlist as $test ) {
		$str .= "<tr>
			<td>{$test['alaskaid']}&nbsp;</td>
			<td>{$test['year']}&nbsp;</td>
			<td>{$test['grade']}&nbsp;</td>
			<td class='{$test['Reading']['prof']}'>{$test['Reading']['prof']}&nbsp;</td>
			<td class='{$test['Writing']['prof']}'>{$test['Writing']['prof']}&nbsp;</td>
			<td class='{$test['Math']['prof']}'>{$test['Math']['prof']}&nbsp;</td>
			<td>{$test['Reading']['ss']}&nbsp;</td>
			<td>{$test['Writing']['ss']}&nbsp;</td>
			<td>{$test['Math']['ss']}&nbsp;</td>
			</tr>";
		}
		$str .= "</table>";
		return($str);
	}

?>