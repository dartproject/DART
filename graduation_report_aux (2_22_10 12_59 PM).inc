<?php

	function getStudentDataForGraduation ($id, $data, $debug=false, $testinglevel='') {
		global $db;
		$values2 = array("ca4", "ca5","ca6", "ca7", "ca8","ca9", "ca10",
						 "sc4", "sc5","sc6", "sc7", "sc8",
						 "cs4", "cs5","cs6", "cs7", "cs8",
						 "ss5","ss6", "ss7", "ss8", "ss9", "ss10",
						 "ls4", "ls5","ls6", "ls7", "ls8",
						 "te4", "te5","te6", "te7",
						 "ma7", "ma8","ma9", "ma10", "ma11","ma12",
						 "wr5","wr6", "wr7", "wr8", "wr9",
						 "re6", "re7", "re8", "re9"					 
						 );
		foreach($values2 as $val2) $gpa[$val2] = 1;
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
			$data["{$sid}.w"] = $w['weight'];
		}
		$results = $db->get_results("SELECT * FROM student where studentid = '$id'", ARRAY_A);
//		print_r($results[0]);
		$studentinfo = $results[0];
		getValuesStudent($id, &$data, $weight, $gpa, $debug, $testinglevel);
		getValuesStudentCurrentClasses($id, &$data, $weight, $gpa, $studentinfo, $debug, $testinglevel);
		getValuesStudentElectives($id, &$data, $weight, $gpa, $studentinfo, $debug, $testinglevel);
	}
	
	function getValuesStudent($id, $data, $weight, $gpa, $debug, $testinglevel) {
		global $db;
		$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
		$table = $testinglevel == '' ? '' : ', testinglevel';
		$clause = $testinglevel == '' ? '' : " and testinglevel.studentid = '$id' and year(studentlevel.final) = testinglevel.year and ($testinglevel) ";
		$sql = "SELECT * FROM studentlevel, subjects $table WHERE studentlevel.subject = subjects.id and studentlevel.studentid = '$id' and final <> '0000-00-00 00:00:00' $clause";
//		echo $sql . "<br><br>";
		$results = $db->get_results($sql, ARRAY_A);
//		echo count($results) . "<br>";
//		print_r($results);
		foreach($results as $row) {
			$sublvl = strtolower($row['subject']) . (int)$row['level'];
			$subject = strtolower($row['subject']);
			$data[$sublvl.".1"] = "$credit"; 
			$data[$sublvl.".2"] = "$credit"; 
			$data[$sublvl.".3"] = "$credit"; 
			$data[$sublvl.".4"] = "$credit"; 
			$data[$sublvl.".c"] = $gpa[$sublvl] * $weight[$subject]; // echo "$sublvl - {$gpa[$sublvl]} - {$weight[$subject]}<br>";
			$data[$sublvl.".c"] .= $debug ? "-".substr($row['progress'], 0, 1) : ""; 
			$data['credit'] += $gpa[$sublvl] * $weight[$subject];
			$p = $row['progress'] == 'ADV' ? 4 : ($row['progress'] == 'PRO' ? 3 : 0);
			if($p != 0) {
				$data['score'] += $gpa[$sublvl] * $weight[$subject] * $p;
				$data['scorecredit'] += $gpa[$sublvl] * $weight[$subject];
			}	
		}
//		print_r($data);
//		return($data);
	}

	function getValuesStudentCurrentClasses($id, $data, $weight, $gpa, $studentinfo, $debug, $testinglevel) {
		global $db, $CurrentYear, $CurrentQuarter;
		$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
		$table = $testinglevel == '' ? '' : ', testinglevel';
		$clause = $testinglevel == '' ? '' : " and testinglevel.studentid = '$id' and ($testinglevel) ";
		$show = $testinglevel == '' ? '' : ", testinglevel.*";
		$sql = "SELECT standards.subject as sub, standards.level as lvl, grades.*, studentlevel.studentid as sid, level.name as nm $show
			FROM (subjects, studentlevel, standards, level $table) 
			LEFT JOIN grades ON grades.subject = standards.subject and 
				grades.level=standards.level and 
				grades.std = standards.std and 
				grades.studentid = studentlevel.studentid
			WHERE 
				standards.level = level.level and 
				standards.subject = level.subject and
				subjects.id = studentlevel.subject and
				subjects.core = 'x' and
				standards.type = 'std' and
				studentlevel.subject = standards.subject and 
				studentlevel.level = standards.level and 
				studentlevel.final = '0000-00-00 00:00:00' and
				studentlevel.studentid = '$id' $clause
			ORDER BY standards.subject, standards.level, standards.std
		";
//		echo $sql . "<br><br>";
		$grades = $db->get_results($sql, ARRAY_A);
		foreach($grades as $grade) {
			$sub_lvl = strtolower($grade['sub']) . (int)$grade['lvl'];
			if($grade['value'] == 'PRO' or $grade['value'] == 'ADV') {
				if($grade['value'] == 'ADV') {
					$scores[$sub_lvl]['adv'] += 1;
				}
				$scores[$sub_lvl]['pass'] += 1;
			}
			$scores[$sub_lvl]['total'] += 1;
			$scores[$sub_lvl]['subject'] = $grade['sub'];
			$scores[$sub_lvl]['level'] = $grade['lvl'];
			$scores[$sub_lvl]['sub_lvl'] = $sub_lvl;
			$scores[$sub_lvl]['name'] = $grade['nm'];
			$scores[$sub_lvl]['testinglevel'] = $grade['testinglevel'];
		}
		$studentid = $id;
		$year = $CurrentYear."-".substr($CurrentYear+1, 2, 2);
		$quarter = "Q".$CurrentQuarter;
		foreach($scores as $score) {
			$subject = strtolower($score['subject']);
			$sublvl = $score['sub_lvl'];
			$subjectid = strtoupper($subject) . "." . $score['level'];
			$quad = floor(($score['pass']/$score['total'])/.25);
			for($i=0; $i < $quad; $i++) {
				$j = $i+1;
				$data[$sublvl.".$j"] = "$credit";
			}
			$p = 0;
			if($quad > 0) {
				$c = $gpa[$sublvl] * $weight[$subject]*$quad*.25;
				$p = ($score['adv'] / $score['pass']) > 0.75 ? 4 : 3;
				$data['score'] += $gpa[$sublvl] * $weight[$subject]*$quad*.25 * $p;
				$data['scorecredit'] += $c;
				$progress = $p == 4 ? "A" : "P";
				$data[$sublvl.".c"] = $debug ? $c."-$progress" : $c; 
				$data['credit'] += $c;
			} else {
				$data[$sublvl.".c"] = $debug ? "{$score['pass']}/{$score['total']}":"";
			}
			$c = fixnum($c);
			$g = $p==4 ? "A/$c" : (($p==3) ? "B/$c" : "---");
			$data['grades'][$studentid.$year.$subjectid]['schoolname'] = $studentinfo['site'];
			$data['grades'][$studentid.$year.$subjectid]['schoolid'] = $studentinfo['site'];
			$data['grades'][$studentid.$year.$subjectid]['sname'] = $studentinfo['fname'] . " " . $studentinfo['lname'];
			$data['grades'][$studentid.$year.$subjectid]['grade']  = $studentinfo['grade'];
			$data['grades'][$studentid.$year.$subjectid]['alaskaid']  = $studentinfo['alaskaid'];
			$data['grades'][$studentid.$year.$subjectid]['bday']  = $studentinfo['bday'];
			$data['grades'][$studentid.$year.$subjectid]['gender']  = $studentinfo['gender'];
			$data['grades'][$studentid.$year.$subjectid]['testinglevel'] = $score['testinglevel'];

			$data['grades'][$studentid.$year.$subjectid]['year'] = $year;
			$data['grades'][$studentid.$year.$subjectid]['sort'] = $studentid.$subjectid.$year.$quarter;
			$data['grades'][$studentid.$year.$subjectid]['studentid'] = $studentid;
			$data['grades'][$studentid.$year.$subjectid]['subjectid']  = $subjectid;
			$data['grades'][$studentid.$year.$subjectid]['subjectname']  = $score['name'];
			$data['grades'][$studentid.$year.$subjectid][$quarter] = $g;
			$data['grades'][$studentid.$year.$subjectid]['timeframe'] = $year;		
		}
	}
	
	function getValuesStudentElectives($id, $data, $weight, $gpa, $studentinfo, $debug, $testinglevel) {
		global $db, $CurrentYear, $CurrentQuarter;
		$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
		$table = $testinglevel == '' ? '' : ', testinglevel';
		$clause = $testinglevel == '' ? '' : " and testinglevel.studentid = '$id' and ($testinglevel) ";
		$show = $testinglevel == '' ? '' : ", testinglevel.*";
		$sql = "SELECT standards.subject as sub, standards.level as lvl, grades.*, level.name as nm $show
			FROM (subjects, studentlevel, standards, level $table) 
			LEFT JOIN grades ON grades.subject = standards.subject and 
				grades.level=standards.level and 
				grades.std = standards.std and 
				grades.studentid = studentlevel.studentid
			WHERE 
				standards.level = level.level and 
				standards.subject = level.subject and
				subjects.id = studentlevel.subject and
				subjects.core = '' and
				standards.type = 'std' and
				studentlevel.subject = standards.subject and 
				studentlevel.level = standards.level and
				studentlevel.studentid = '$id' $clause
			ORDER BY standards.subject, standards.level, standards.std
		";
//		echo $sql . "<br><br>";
		$grades = $db->get_results($sql, ARRAY_A);
//		print_r($grades);
		foreach($grades as $grade) {
			$sub_lvl = strtolower($grade['sub']) . (int)$grade['lvl'];
			if($grade['value'] == 'PRO' or $grade['value'] == 'ADV') {
				if($grade['value'] == 'ADV') {
					$scores[$sub_lvl]['adv'] += 1;
				}
				$scores[$sub_lvl]['pass'] += 1;
			}
			$scores[$sub_lvl]['total'] += 1;
			$scores[$sub_lvl]['subject'] = $grade['sub'];
			$scores[$sub_lvl]['level'] = $grade['lvl'];
			$scores[$sub_lvl]['sub_lvl'] = $sub_lvl;
			$scores[$sub_lvl]['name'] = $grade['nm'];
			$scores[$sub_lvl]['testinglevel'] = $grade['testinglevel'];
		}
		$studentid = $id;
		$year = $CurrentYear."-".substr($CurrentYear+1, 2, 2);
		$quarter = "Q".$CurrentQuarter;
//		print_r($scores);
		$k=1;
		foreach($scores as $score) {
			$subject = strtolower($score['subject']);
			$weight[$subject] = 0.5;
			$sublvl = $score['sub_lvl'];
			$subjectid = strtoupper($subject) . "." . $score['level'];
			$quad = floor(($score['pass']/$score['total'])/.25);
			$name = $score['name'] ;
			$name .= $debug ? " ({$weight[$subject]} Cr) => $sublvl {$score['pass']}/{$score['total']}+$quad": "";
			for($j=1; $j < 5; $j++) ${"flag".$j} = "$nocredit";
			for($i=0; $i < $quad; $i++) {
				$j = $i+1;
				${"flag".$j} = "$credit";
			}
			$c = ''; $p = 0;
			if($quad > 0) {
				$c = fixnum($weight[$subject]*$quad*.25);
				$p = (($score['adv'] / $score['pass']) > 0.75) ? 4 : 3;
				$data['score'] += $weight[$subject]*$quad*.25 * $p;
				$data['scorecredit'] += $weight[$subject]*$quad*.25;
				$progress = $p == 4 ? "A" : "P";
				$c .= $debug ? "-$progress {$score['adv']}/{$score['pass']}" : ""; 
				$data['credit'] += $c;
			} else {
//				$c .= $debug ? "{$score['pass']}/{$score['total']}":"";
			}
			$g = ($p==4) ? "A/$c" : (($p==3) ? "B/$c" : "");
			$data['grades'][$studentid.$year.$subjectid]['schoolname'] = $studentinfo['site'];
			$data['grades'][$studentid.$year.$subjectid]['schoolid'] = $studentinfo['site'];
			$data['grades'][$studentid.$year.$subjectid]['sname'] = $studentinfo['fname'] . " " . $studentinfo['lname'];
			$data['grades'][$studentid.$year.$subjectid]['grade']  = $studentinfo['grade'];
			$data['grades'][$studentid.$year.$subjectid]['alaskaid']  = $studentinfo['alaskaid'];
			$data['grades'][$studentid.$year.$subjectid]['bday']  = $studentinfo['bday'];
			$data['grades'][$studentid.$year.$subjectid]['gender']  = $studentinfo['gender'];
			$data['grades'][$studentid.$year.$subjectid]['testinglevel'] = $score['testinglevel'];

			$data['grades'][$studentid.$year.$subjectid]['year'] = $year;
			$data['grades'][$studentid.$year.$subjectid]['sort'] = $studentid.$subjectid.$year.$quarter;
			$data['grades'][$studentid.$year.$subjectid]['studentid'] = $studentid;
			$data['grades'][$studentid.$year.$subjectid]['subjectid']  = $subjectid;
			$data['grades'][$studentid.$year.$subjectid]['subjectname']  = $score['name'];
			$data['grades'][$studentid.$year.$subjectid]['timeframe'] = $year;		
			$data['grades'][$studentid.$year.$subjectid][$quarter] = $g;
			$data['elective'.$k] = <<<END
			<td valign="bottom" nowrap="nowrap" height="32" colspan="5">
			<div align="right"><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><font size="2"><b>$name</b></font></font></div>
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
		$rprof = str_replace(" ", "_", trim($test['Reading']['prof']));
		$wprof = str_replace(" ", "_", trim($test['Writing']['prof']));
		$mprof = str_replace(" ", "_", trim($test['Math']['prof']));
		$str .= "<tr>
			<td>{$test['alaskaid']}&nbsp;</td>
			<td>{$test['year']}&nbsp;</td>
			<td>{$test['grade']}&nbsp;</td>
			<td class='$rprof'>{$test['Reading']['prof']}&nbsp;</td>
			<td class='$wprof'>{$test['Writing']['prof']}&nbsp;</td>
			<td class='$mprof'>{$test['Math']['prof']}&nbsp;</td>
			<td>{$test['Reading']['ss']}&nbsp;</td>
			<td>{$test['Writing']['ss']}&nbsp;</td>
			<td>{$test['Math']['ss']}&nbsp;</td>
			</tr>";
		}
		$str .= "</table>";
		return($str);
	}

	function fixnum($num) {
		$outnum = number_format(round($num, 2), 2);
		return ($outnum);
	}
?>