<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

function dv($value, $type="") {
  $ans = $value=="" ? ($type == "num" ? 0 : "&nbsp;") : $value;
//    $ans = $value=="" ? "&nbsp;" : $value;
  $ans = $value=="0" ? "0" : $ans;

  return($ans);
}

function getYearOption ($year) {
	global $db, $CurrentYear;
	
	$years = $db->get_results("select distinct(year) as year from sfascores");
	$current = false;
  	foreach ($years as $yr) {
  		if ($yr->year != '') {
			$val = $yr->year;
			$nextval = $val + 1;
			$selected = $year == $val ? "selected": "";
			$str .= "<option value='$val' $selected>$val-$nextval</option>\n";
			$current = ($val == $CurrentYear) ? true : $current;
		}
  	}
  	$nextvalcurrent = $CurrentYear + 1;
  	$selected = $year == $CurrentYear ? "selected": "";
  	$str .= ($current == true) ? "" : "<option value='$CurrentYear' $selected>$CurrentYear-$nextvalcurrent</option>\n";
  	return ($str);	
}

function scorevalue ($score) {
//  $value = "$score-";
  switch($score) {
    case "sped": return("");
    case "Pre": return (0);
    case "1-5": return(1);
    case "6-10": return(2);
    case "11-15": return(3);
    case "16-20": return(4);
    case "21-25": return(5);
    case "26-31": return(6);
    case "32-37": return(7);
    case "38-42": return(8);
    case "43-48": return(9);
    default: return($score);
  }
}

function scoreR($val) {
    if ($val == "sped") { return(""); }
    elseif ($val == '1-5' || $val == '6-10' || $val == '11-15' || $val == '16-20' || 
        $val == '21-25' || $val == '26-31' || $val == '32-37' || $val == '38-42' || 
        $val == '43-48' || $val == 'KR' || $val == 'KC' || $val == 'BR' || 
        $val == 'PK' ||$val == '') { return ($val);  }   
    elseif ($val >= 0 && $val <= 399) { return ('43-48'); }
    elseif ($val >= 400 && $val <= 474) { return ('2.1'); }
    elseif ($val >= 475 && $val <= 534) { return ('2.2'); }
    elseif ($val >= 535 && $val <= 589) { return ('3.1'); }
    elseif ($val >= 590 && $val <= 644) { return ('3.2'); }
    elseif ($val >= 645 && $val <= 699) { return ('4.1'); }
    elseif ($val >= 700 && $val <= 749) { return ('4.2'); }
    elseif ($val >= 750 && $val <= 804) { return ('5.1'); }
    elseif ($val >= 805 && $val <= 839) { return ('5.2'); }
    elseif ($val >= 840 && $val <= 879) { return ('6.1'); }
    elseif ($val >= 880 && $val <= 914) { return ('6.2'); }
    elseif ($val >= 915 && $val <= 954) { return ('7.1'); }
    elseif ($val >= 955 && $val <= 979) { return ('7.2'); }
    elseif ($val >= 980 && $val <= 999) { return ('8.1') ;}
    elseif ($val >= 1000 && $val <= 1019) { return ('8.2'); }
    elseif ($val >= 1020 && $val <= 1044) { return ('9.1'); }
    elseif ($val >= 1045 && $val <= 1064) { return ('9.2'); }
    elseif ($val >= 1065 && $val <= 1079) { return ('10.1'); }
    elseif ($val >= 1080 && $val <= 1084) { return ('10.2'); }
    elseif ($val >= 1085 && $val <= 1089) { return ('11.1'); }
    elseif ($val >= 1090 && $val <= 1094) { return ('11.2') ;}
    elseif ($val >= 1095 && $val <= 1099) { return ('12.1') ;}
    elseif ($val >= 1100) { return ('12.2') ;}
    else { return ("ERR"); }
}

function GetAllGroupScores($listid, $year, $exclude='') {
  global $db;

  switch ($exclude) {
     case '1-13':
    	$clause = " and testinglevel.testinglevel != 'K' and testinglevel.testinglevel != 'sped'";
    	break;
     case 'K':
    	$clause = " and testinglevel.testinglevel = 'K'";
    	break;
     default:
     	$clause = "";
    }
    
  $studentlist = getListStudents($listid);
    
  $sql = "select * from sfascores, student, testinglevel where testinglevel.studentid = student.studentid and testinglevel.year = '$year' and sfascores.year = '$year' and student.studentid = sfascores.studentid and student.studentid in ($studentlist) and student.status='Active' $clause";
  debugPrint("GetAllGroupScores: " . $sql);
  $results = $db->get_results($sql);
  $cutoff = getCutOffs();

  foreach ($results as $res) {
  		$testlevel = $res->testinglevel;
        debugPrint($res->studentid . "=> " . $res->base_score . "-");
		if($res->base_rawscore != "") {
		   debugPrint("KC"); 
		   $score['base'][$testlevel]['count']['value']++;
		   $score['base'][$testlevel]['count']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
		   $score['base'][$testlevel]['count']['studentid'] .= $res->studentid . ", ";
		   if(scorevalue($res->base_rawscore) >= $cutoff[$res->testlevel]['base']) {
		   		$score['base'][$testlevel]['above']['value']++;
			    $score['base'][$testlevel]['above']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
			    $score['base'][$testlevel]['above']['studentid'] .= $res->studentid . ", ";
		   	}
		}
		if($res->first_rawscore != "") {
		   $score['first'][$testlevel]['count']['value']++;
		   $score['first'][$testlevel]['count']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
		   $score['first'][$testlevel]['count']['studentid'] .= $res->studentid . ", ";
		   if(scorevalue($res->first_rawscore) >= $cutoff[$res->testlevel]['first']) {
		   		$score['first'][$testlevel]['above']['value']++;
			    $score['first'][$testlevel]['above']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
			    $score['first'][$testlevel]['above']['studentid'] .= $res->studentid . ", ";
		   	}
		}
		if($res->second_rawscore != "") {
		   $score['second'][$testlevel]['count']['value']++;
		   $score['second'][$testlevel]['count']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
		   $score['second'][$testlevel]['count']['studentid'] .= $res->studentid . ", ";
		   if(scorevalue($res->second_rawscore) >= $cutoff[$res->testlevel]['second']) {
		   		$score['second'][$testlevel]['above']['value']++;
			    $score['second'][$testlevel]['above']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
			    $score['second'][$testlevel]['above']['studentid'] .= $res->studentid . ", ";
		   	}
		}
		if($res->third_rawscore != "") {
		   $score['third'][$testlevel]['count']['value']++;
		   $score['third'][$testlevel]['count']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
		   $score['third'][$testlevel]['count']['studentid'] .= $res->studentid . ", ";
		   if(scorevalue($res->third_rawscore) >= $cutoff[$res->testlevel]['third']) {
		   		$score['third'][$testlevel]['above']['value']++;
			    $score['third'][$testlevel]['above']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
			    $score['third'][$testlevel]['above']['studentid'] .= $res->studentid . ", ";
		   	}
		}
		if($res->fourth_rawscore != "") {
		   $score['fourth'][$testlevel]['count']['value']++;
		   $score['fourth'][$testlevel]['count']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
		   $score['fourth'][$testlevel]['count']['studentid'] .= $res->studentid . ", ";
		   if(scorevalue($res->fourth_rawscore) >= $cutoff[$res->testlevel]['fourth']) {
		   		$score['fourth'][$testlevel]['above']['value']++;
			    $score['base'][$testlevel]['above']['studentshow'] .= $res->fname . " " . $res->lname . ": ";
			    $score['base'][$testlevel]['above']['studentid'] .= $res->studentid . ", ";
		   	}
		}
    }
    debugPrint("Coming Out: " . print_r($score, true));
    return($score);
}
function GetGroupScores ($listid, $year) {
  global $db;

  $studentlist = getListStudents($listid);

  $sql = "select * from sfascores, student,testinglevel where testinglevel.studentid = student.studentid and testinglevel.year = '$year' and sfascores.year = '$year' and student.studentid = sfascores.studentid and student.studentid in ($studentlist) order by student.lname, student.fname";
//  $sql = "select * from listvalues, student left join on listvalues.studentid = sfascores.studentid where listvalues.listid = $listid and  listvalues.studentid = student.studentid order by student.lname, student.fname";
  debugPrint("GetGroupScores: " . $sql);
  $results = $db->get_results($sql);
//  $sqlt = "select studentid from listvalues where listvalues.listid = $listid";
//  debugPrint("Total Scores: " . $sqlt);
//  $result_t = $db->get_results($sqlt);
  $score['count'] = $db->num_rows;
  debugPrint("Array GroupScore: " . print_r($results, true));

  foreach ($results as $res) {
    debugPrint("Student: " . $res->studentid);
    if($res->base_score != "") {
       $testinglevel = $res->testinglevel;
       debugPrint("KC"); 
       $score[$testinglevel]['base'][$res->base_score]['value']++;
       $score['any']['base'][$res->base_score]['value']++;
       $score[$testinglevel]['base']['any']['value']++;
       $score['any']['base']['any']['value']++;
       
       $score[$testinglevel]['base'][$res->base_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['base'][$res->base_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score[$testinglevel]['base']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['base']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       
       $score[$testinglevel]['base'][$res->base_score]['ids'] .= $res->studentid . ', ';
       $score['any']['base'][$res->base_score]['ids'] .= $res->studentid . ', ';
       $score[$testinglevel]['base']['any']['ids'] .= $res->studentid . ', ';
       $score['any']['base']['any']['ids'] .= $res->studentid . ', ';
    }
    if($res->first_score != "") {
       $score[$testinglevel]['first'][$res->first_score]['value']++;
       $score['any']['first'][$res->first_score]['value']++;
       $score[$testinglevel]['first']['any']['value']++;
       $score['any']['first']['any']['value']++;
       
       $score[$testinglevel]['first'][$res->first_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['first'][$res->first_score]['student'] .= $res->fname . ' ' . $res->lname  .': ';
       $score[$testinglevel]['first']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['first']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       
       $score[$testinglevel]['first'][$res->first_score]['ids'] .= $res->studentid . ', ';
       $score['any']['first'][$res->first_score]['ids'] .= $res->studentid . ', ';
       $score[$testinglevel]['first']['any']['ids'] .= $res->studentid . ', ';
       $score['any']['first']['any']['ids'] .= $res->studentid . ', ';
    }
    if($res->second_score != "") {
       $score[$testinglevel]['second'][$res->second_score]['value']++;
       $score['any']['second'][$res->second_score]['value']++;
       $score[$testinglevel]['second']['any']['value']++;
       $score['any']['second']['any']['value']++;
       
       $score[$testinglevel]['second'][$res->second_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['second'][$res->second_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score[$testinglevel]['second']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['second']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       
       $score[$testinglevel]['second'][$res->second_score]['ids'] .= $res->studentid . ', ';
       $score['any']['second'][$res->second_score]['ids'] .= $res->studentid . ', ';
       $score[$testinglevel]['second']['any']['ids'] .= $res->studentid . ', ';
       $score['any']['second']['any']['ids'] .= $res->studentid . ', ';
    }
    if($res->third_score != "") {
       $score[$testinglevel]['third'][$res->third_score]['value']++;
       $score['any']['third'][$res->third_score]['value']++;
       $score[$testinglevel]['third']['any']['value']++;
       $score['any']['third']['any']['value']++;
       
       $score[$testinglevel]['third'][$res->third_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['third'][$res->third_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score[$testinglevel]['third']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['third']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       
       $score[$testinglevel]['third'][$res->third_score]['ids'] .= $res->studentid . ', ';
       $score['any']['third'][$res->third_score]['ids'] .= $res->studentid . ', ';
       $score[$testinglevel]['third']['any']['ids'] .= $res->studentid . ', ';
       $score['any']['third']['any']['ids'] .= $res->studentid . ', ';
    }
    if($res->fourth_score != "") {
       $score[$testinglevel]['fourth'][$res->fourth_score]['value']++;
       $score['any']['fourth'][$res->fourth_score]['value']++;
       $score[$testinglevel]['fourth']['any']['value']++;
       $score['any']['fourth']['any']['value']++;
       
       $score[$testinglevel]['fourth'][$res->fourth_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['fourth'][$res->fourth_score]['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score[$testinglevel]['fourth']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       $score['any']['fourth']['any']['student'] .= $res->fname . ' ' . $res->lname . ': ';
       
       $score[$testinglevel]['fourth'][$res->fourth_score]['ids'] .= $res->studentid . ', ';
       $score['any']['fourth'][$res->fourth_score]['ids'] .= $res->studentid . ', ';
       $score[$testinglevel]['fourth']['any']['ids'] .= $res->studentid . ', ';
       $score['any']['fourth']['any']['ids'] .= $res->studentid . ', ';
    }
  } 
debugPrint("Coming Out: " . print_r($score, true));

return ($score);

}


function getCutOffs () {
  global $db;
  
  $sql = "select * from hotlist";
  debugPrint ("getTeacherTutorHomeroom: $sql");
  $values = $db->get_results($sql);
  foreach ($values as $value) {
    $results[$value->grade][$value->stage]=$value->neededmin;
  } 
  return ($results);  
}


function getHotListValues () {
  global $db;
  
  $sql = "select * from hotlist";
  debugPrint ("getTeacherTutorHomeroom: $sql");
  $values = $db->get_results($sql);
  foreach ($values as $value) {
    $results[$value->grade][$value->stage]=$value->score;
  } 
  return ($results);  
}

function GetStudentGroup ($grade, $test, $score, $listid) {
  global $db;

  $studentlist = getListStudents($listid);

//  $sql = "select * from sfascores, student where student.grade = $grade and sfascores.test = $test and sfascores.$grade_score = $score and student.studentid = sfascores.studentid";
  if($grade != "any") { $where .= " student.grade = '$grade' and "; }
  if($test != "any") { $where .= "sfascores." . $test . "_score = '$score' and ";}
  else { $where .= " (sfascores.base_score = '$score' or sfascores.first_score = '$score' or sfascores.second_score = '$score' or sfascores.third_score = '$score' or sfascores.fourth_score = '$score') and "; }
  $sql = "select * from sfascores, student where $where student.studentid = sfascores.studentid and student.studentid in ($studentlist)";
  debugPrint ("GetStudentGroup: " . $sql);
  $results = $db->get_results($sql);
  return($results);
}

function getSFAStudents ($listid, $year) {
  global $db;
  
  $studentlist = getListStudents($listid);

  $sqlscores = "SELECT *, student.studentid as sid from student, sfascores 
	  WHERE  student.studentid in ($studentlist) 
	  		and sfascores.studentid = student.studentid 
	  		and sfascores.year = '$year'
";
//  echo  $sqlscores;
  debugPrint("getSFAStudents sfascores: " . $sqlscores);
  $scores = $db->get_results($sqlscores);
  $sqllist = "select *, student.studentid as sid from student
  		LEFT JOIN testinglevel ON testinglevel.studentid = student.studentid 
			and testinglevel.year = '$year'
		WHERE student.studentid in ($studentlist)
		ORDER BY student.lname, student.fname";
  debugPrint("getSFAStudents sfaslists: " . $sqllist);
  $list = $db->get_results($sqllist);
  foreach ($scores as $score) {
    $scr[$score->sid]['mark'] = "X";
    $scr[$score->sid]['base_score'] = $score->base_score;
    $scr[$score->sid]['base_rawscore'] = $score->base_rawscore;
    $scr[$score->sid]['first_score'] = $score->first_score;
    $scr[$score->sid]['first_rawscore'] = $score->first_rawscore;
    $scr[$score->sid]['second_score'] = $score->second_score;
    $scr[$score->sid]['second_rawscore'] = $score->second_rawscore;
    $scr[$score->sid]['third_score'] = $score->third_score;
    $scr[$score->sid]['third_rawscore'] = $score->third_rawscore;
    $scr[$score->sid]['fourth_score'] = $score->fourth_score;
    $scr[$score->sid]['fourth_rawscore'] = $score->fourth_rawscore;
    $scr[$score->sid]['homeroom'] = $score->homeroom;
    $scr[$score->sid]['base_rr'] = $score->base_rr;
    $scr[$score->sid]['first_rr'] = $score->first_rr;
    $scr[$score->sid]['second_rr'] = $score->second_rr;
    $scr[$score->sid]['third_rr'] = $score->third_rr;
    $scr[$score->sid]['fourth_rr'] = $score->fourth_rr;
    $scr[$score->sid]['base_reading'] = $score->base_reading;
    $scr[$score->sid]['first_reading'] = $score->first_reading;
    $scr[$score->sid]['second_reading'] = $score->second_reading;
    $scr[$score->sid]['third_reading'] = $score->third_reading;
    $scr[$score->sid]['fourth_reading'] = $score->fourth_reading;
    $scr[$score->sid]['base_sfa'] = $score->base_sfa;
    $scr[$score->sid]['first_sfa'] = $score->first_sfa;
    $scr[$score->sid]['second_sfa'] = $score->second_sfa;
    $scr[$score->sid]['third_sfa'] = $score->third_sfa;

    $scr[$score->sid]['base_expect'] = $score->base_expect;
    $scr[$score->sid]['first_expect'] = $score->first_expect;
    $scr[$score->sid]['second_expect'] = $score->second_expect;
    $scr[$score->sid]['third_expect'] = $score->third_expect;

    $scr[$score->sid]['base_tutor'] = $score->base_tutor;
    $scr[$score->sid]['first_tutor'] = $score->first_tutor;
    $scr[$score->sid]['second_tutor'] = $score->second_tutor;
    $scr[$score->sid]['third_tutor'] = $score->third_tutor;

    $scr[$score->sid]['base_hlremove'] = $score->base_hlremove;
    $scr[$score->sid]['first_hlremove'] = $score->first_hlremove;
    $scr[$score->sid]['second_hlremove'] = $score->second_hlremove;
    $scr[$score->sid]['third_hlremove'] = $score->third_hlremove;
    $scr[$score->sid]['sid'] = $score->sid;
  }
  $results['score'] = $scr;
  $results['list'] = $list;
  return($results);
}

        function saveSFAScores($values) {
         global $db;

 		 $year = $values['year']; 
// 		 print_r($values);
         while(list($var, $val) = each($values)) {
//               echo("var $var => $val <br>");
                if(substr($var, 0, 3) == "ch_" and $val != "empty") {
                 $type = substr($var, 3, 1);
                 $studentid = strtok(substr($var, 5, 100), "_");
                 $recname = $type . "_" . $studentid;
                 debugPrint ("TYPE: $type STUDENT: $studentid RECNAME: $recname<br>");
                 $base = $values[$recname . "_rec_base"];
                 $base_raw = $values[$recname . "_inp_base"];
                 $first = $values[$recname . "_rec_first"];
                 $first_raw = $values[$recname . "_inp_first"];
                 $second = $values[$recname . "_rec_second"];
                 $second_raw = $values[$recname . "_inp_second"];
                 $third = $values[$recname . "_rec_third"];
                 $third_raw = $values[$recname . "_inp_third"];
                 $fourth = $values[$recname . "_rec_fourth"];
                 $fourth_raw = $values[$recname . "_inp_fourth"];
                 $home = $values[$recname . "_homeroom"];
                 $base_rr = $values[$recname . "_rr_base"];
                 $base_reading = $values[$recname . "_reading_base"];
                 $first_rr = $values[$recname . "_rr_first"];
                 $first_reading = $values[$recname . "_reading_first"];
                 $second_rr = $values[$recname . "_rr_second"];
                 $second_reading = $values[$recname . "_reading_second"];
                 $third_rr = $values[$recname . "_rr_third"];
                 $third_reading = $values[$recname . "_reading_third"];
                 $fourth_rr = $values[$recname . "_rr_fourth"];
                 $fourth_reading = $values[$recname . "_reading_fourth"];
                 $logval = "base: $base_raw; first: $first_raw; second: $second_raw; third: $third_raw; fourth: $fourth_raw;";
                 $base_sfa = $values[$recname . "_sfa_base"];
                 $first_sfa = $values[$recname . "_sfa_first"];
                 $second_sfa = $values[$recname . "_sfa_second"];
                 $third_sfa = $values[$recname . "_sfa_third"];
                 $base_expect = $values[$recname . "_expect_base"];
                 $first_expect = $values[$recname . "_expect_first"];
                 $second_expect = $values[$recname . "_expect_second"];
                 $third_expect = $values[$recname . "_expect_third"];
                 $base_tutor = $values[$recname . "_tutor_base"];
                 $first_tutor = $values[$recname . "_tutor_first"];
                 $second_tutor = $values[$recname . "_tutor_second"];
                 $third_tutor = $values[$recname . "_tutor_third"];
                 $base_hlremove = $values[$recname . "_remove_base"];
                 $first_hlremove = $values[$recname . "_remove_first"];
                 $second_hlremove = $values[$recname . "_remove_second"];
                 $third_hlremove = $values[$recname . "_remove_third"];

                 $set = "SET base_score='$base',
						 base_rawscore = '$base_raw',
						 first_score='$first',
						 first_rawscore = '$first_raw',
						 second_score='$second',
						 second_rawscore = '$second_raw',
						 third_score='$third',
						 third_rawscore = '$third_raw',
						 fourth_score='$fourth',
						 fourth_rawscore = '$fourth_raw',
						 base_rr = '$base_rr',
						 base_reading = '$base_reading',
						 first_rr = '$first_rr',
						 first_reading = '$first_reading',
						 second_rr = '$second_rr',
						 second_reading = '$second_reading',
						 third_rr = '$third_rr',
						 third_reading = '$third_reading',
						 fourth_rr = '$fourth_rr',
						 fourth_reading = '$fourth_reading',
						 base_sfa = '$base_sfa',
						 first_sfa = '$first_sfa',
						 second_sfa = '$second_sfa',
						 third_sfa = '$third_sfa',
						 base_expect = '$base_expect',
						 first_expect = '$first_expect',
						 second_expect = '$second_expect',
						 third_expect = '$third_expect',
						 base_tutor = '$base_tutor',
						 first_tutor = '$first_tutor',
						 second_tutor = '$second_tutor',
						 third_tutor = '$third_tutor',
						 base_hlremove = '$base_hlremove',
						 first_hlremove = '$first_hlremove',
						 second_hlremove = '$second_hlremove',
						 third_hlremove = '$third_hlremove',
						 homeroom = '$home'";
                 if($type == "i" ) {
                  $sql = "INSERT into sfascores
                                 $set,
                                  studentid = '$studentid', year='$year'";
                } else {
                 $sql = "Update sfascores 
                               $set
                               WHERE
                                    studentid = '$studentid' and year='$year'";
                }
//			echo $sql;
//			exit();
//			$sql = "INSERT INTO sfascores set 
//						studentid = '$studentid', year='$year', $set 
//					  ON DUPLICATE KEY UPDATE $set";
//			
//           debugPrint($var . "<br>");
           debugPrint ("LOGVAL: $logval<br>");
           debugPrint("SQL=>$sql<br>");
           $db->get_results($sql);
           logEntry("score", $logval, $studentid, "SPI", "", "");
           }
          }
//          exit();
      }
      
      function saveTutorTime($values) {
         global $db;
         
         debugPrint("<br>******* TutotTime *********<br>");
         while(list($var, $val) = each($values)) {
                 debugPrint("var $var => $val <br>");
                 $type = substr($var, 0, 2);
					 if($type == "ch" and $val != 'empty') {
					 $studentid = strtok(substr($var, 2, 100), "_");
					 $stage = strtok("_");                
					 $recname = $studentid . "_" . $stage;
                	 debugPrint ("TYPE: $type STUDENT: $studentid RECNAME: $recname<br>");                 $base = $values[$recname . "_rec_base"];
                     $stime = $values[$recname . "_inp_stime"];
                     $etime = $values[$recname . "_inp_etime"];
                     $logval = "Stage: $stage STime: $stime ETime: $etime";

                     $set = "SET " . $stage . "_stime = '$stime', "
                                   . $stage . "_etime = '$etime'";

                     $sql = "Update sfascores 
                               $set
                               WHERE
                                 studentid = '$studentid'";
				     debugPrint("Update Tutor Time SQL=>$sql<br>");
		           $db->get_results($sql);
		           logEntry("tutortime", $logval, $studentid, "TutorTime", "", "");
        
                  }
         }
      }

function GetStudentNoScore($kind, $listid) {
  global $db;

  $studentlist = getListStudents($listid);

  $sql = "select * from student where student.studentid in ($studentlist) and NOT Exists (select student.studentid from  sfascores where student.studentid = sfascores.studentid and sfascores." . $kind . "_rawscore IS NOT NULL and sfascores." . $kind . "_rawscore  != '')";
  debugPrint("GetStudentNoScore: " . $sql);
  $results = $db->get_results($sql);
  return ($results);
}

function GetListWithScore($listid, $year, $exclude=false) {
  global $db;
  
  $clause = $exclude ? " and student.grade != 'K' and student.grade != 'sped'" : "";
  $studentlist = getListStudents($listid);

  $sql = "select *, student.studentid as sid, student.site as ste from student, sfascores where sfascores.year = '$year' and student.studentid = sfascores.studentid and student.status = 'Active' and student.studentid in ($studentlist) and (sfascores.base_rawscore != '' or sfascores.first_rawscore != '' or sfascores.second_rawscore != '' or sfascores.third_rawscore != '' or sfascores.fourth_rawscore != '') $clause";
  debugPrint("GetStudentWithScore: " . $sql);
  $results = $db->get_results($sql);
  return ($results);
}

function GetStudentWithScore($year) {
  global $db;

  $sql = "select *, student.studentid as sid, student.site as ste from student, sfascores,testinglevel where testinglevel.studentid = student.studentid and testinglevel.year = '$year' and sfascores.year = '$year' and student.studentid = sfascores.studentid and status = 'Active' and (sfascores.base_rawscore != '' or sfascores.first_rawscore != '' or sfascores.second_rawscore != '' or sfascores.third_rawscore != '' or sfascores.fourth_rawscore != '')"; //  limit 0,30
  debugPrint("GetStudentWithScore: " . $sql);
  $results = $db->get_results($sql);
  return ($results);
}

function GetNoScores ($listid, $year) {
  global $db;

  $studentlist = getListStudents($listid);

  $sqlb = "select distinct student.studentid from student where student.studentid in ($studentlist) and NOT Exists (select student.studentid from sfascores where sfascores.year = '$year' and student.studentid = sfascores.studentid and sfascores.base_rawscore IS NOT NULL and sfascores.base_rawscore  != '')";
  $sql1 = "select distinct student.studentid from student where student.studentid  in ($studentlist) and NOT Exists (select student.studentid from sfascores where sfascores.year = '$year' and student.studentid = sfascores.studentid and sfascores.first_rawscore IS NOT NULL and sfascores.first_rawscore  != '')";
    $sql2 = "select distinct student.studentid from student where student.studentid  in ($studentlist) and NOT Exists (select student.studentid from sfascores where sfascores.year = '$year' and student.studentid = sfascores.studentid and sfascores.second_rawscore IS NOT NULL and sfascores.second_rawscore  != '')";
  $sql3 = "select distinct student.studentid from student where student.studentid  in ($studentlist) and NOT Exists (select student.studentid from sfascores where sfascores.year = '$year' and student.studentid = sfascores.studentid and sfascores.third_rawscore IS NOT NULL and sfascores.third_rawscore  != '')";
    $sql4 = "select distinct student.studentid from student where student.studentid  in ($studentlist) and NOT Exists (select student.studentid from sfascores where sfascores.year = '$year' and student.studentid = sfascores.studentid and sfascores.fourth_rawscore IS NOT NULL and sfascores.fourth_rawscore  != '')";

  debugPrint("GetNoScores: " . $sqlb);
  $resultb = $db->get_results($sqlb, ARRAY_A);
  $value['base'] = $resultb;
  $value['bcount'] = count($resultb);
    
  $result1 = $db->get_results($sql1, ARRAY_A);
  $value['first'] = $result1;  
  $value['fcount'] = count($result1);
  
  $result2 = $db->get_results($sql2, ARRAY_A);
  $value['second'] = $result2;  
  $value['scount'] = count($result2);
  
  $result3 = $db->get_results($sql3, ARRAY_A);
  $value['third'] = $result3;  
  $value['tcount'] = count($result3);
  
  $result4 = $db->get_results($sql4, ARRAY_A);
  $value['fourth'] = $result4;
  $value['fourthcount'] = count($result4);
  
  return ($value);
}

/*** 
Determines what value will have you on the hotlist. 
Sometimes just above level and other times just below level. 
***/
function GetHotList ($list, $stage, $year, $site = '') {
  global $db;
  
  $clause = ($site == '') ? '' : " and student.village = '$site'";
//  $sql = "select student.*, sfascores.* from listvalues, student, sfascores, hotlist where listvalues.listid = '$list' and student.studentid = listvalues.studentid and student.studentid = sfascores.studentid and student.grade = hotlist.grade and sfascores." . $stage . "_score = hotlist.score and hotlist.stage = '$stage' and hotlist.score != '' and sfascores." . $stage . "_hlremove != 'X'";
  $sql = "select student.*, sfascores.* from student, sfascores, hotlist where sfascores.year = '$year' and student.studentid = sfascores.studentid and student.grade = hotlist.grade and sfascores." . $stage . "_score = hotlist.score and hotlist.stage = '$stage' and hotlist.score != '' and sfascores." . $stage . "_hlremove != 'X' $clause";
  debugPrint("Hotlist ($stage): " . $sql);
  $results = $db->get_results($sql);
  return ($results);
 
}

function GetHotListArray ($list, $stage, $year) {
   $hl = GetHotList($list, $stage, $year);
   
   foreach ($hl as $stu) {
      $results[$stu->studentid] = "X";
    }
    return($results);
}

function GetTutorHotList ($tutor, $stage, $year) {
  global $db;
  
  $sql = "select * from student, sfascores, hotlist where student.studentid = sfascores.studentid and student.grade = hotlist.grade and sfascores." . $stage . "_score = hotlist.score and hotlist.stage = '$stage' and sfascores." . $stage . "_tutor = '$tutor' and year = '$year'";
  debugPrint("TutorHotlist ($stage): " . $sql);
  $results = $db->get_results($sql);
  return ($results);
 
}
function GetTutorHotListArray ($tutor, $stage, $year) {
   $hl = GetTutorHotList($tutor, $stage, $year);
   
   foreach ($hl as $stu) {
      $results[$stu->studentid] = "X";
    }
    return($results);
}

function getHomeRoomArray ($site="all") {
  global $db;
  
  if($site == 'all') {
     $sql = "select userid as id, name from user where homeroom = 'X' and status = 'Active'";
  } else { 
     $sql = "select userid as id, name from user where homeroom = 'X' and site = '$site' and status = 'Active'";
  }
  debugPrint("getHomeRoomArray: " . $sql);
  $list = $db->get_results($sql, ARRAY_A);
  
  return ($list);
}

function getReadingArray ($site="all") {
  global $db;
  
  if($site == 'all') {
     $sql = "select userid as id, name from user where reading = 'X' and status = 'Active' order by name";
  } else { 
     $sql = "select userid as id, name from user where reading = 'X' and site = '$site'  and status = 'Active' order by name";
  }
  debugPrint("getReadingArray: " . $sql);
  $list = $db->get_results($sql, ARRAY_A);
  
  return ($list);
}

function getTutorArray ($site="all") {
  global $db;
  
  if($site == 'all') {
     $sql = "select userid as id, name from user where tutor = 'X' and status = 'Active' order by name";
  } else { 
     $sql = "select userid as id, name from user where tutor = 'X' and site = '$site' and status = 'Active' order by name";
  }
  debugPrint("getTutoeArray: " . $sql);
  $list = $db->get_results($sql, ARRAY_A);
  
  return ($list);
}
// LEFT JOIN testlevel ON student.studentid = testlevel.studentid and testlevel.year = '$year'
function getSFATeacherStudents ($teacher, $quarter, $year="2006") {
  global $db;
  
  $sql = "select * from student, sfascores, user, hotlist, testinglevel where testinglevel.studentid = student.studentid and testinglevel.year = '$year' and sfascores.year = '$year' and student.studentid = sfascores.studentid and student.status = 'Active' and " .  $quarter . "_reading='$teacher' and " . $quarter . "_reading=user.userid and student.grade = hotlist.grade and hotlist.stage = '$quarter' order by lname, fname";
  debugPrint ("getSFATeacherStudents: $sql");
  $students = $db->get_results($sql, ARRAY_A);
 
  return ($students);
  
}


function getContentReadingAreaStudents($teacher, $quarter, $year="2006") {
  global $db;
  
  $sql = "select level, studentlevel.studentid from sfascores, studentlevel where sfascores.year = '$year' and studentlevel.studentid = sfascores.studentid and " .  $quarter . "_reading='$teacher' and studentlevel.subject = 'RE' ";
  debugPrint ("getContentReadingAreaStudents: $sql");
  $students = $db->get_results($sql);
  foreach ($students as $stu) {
    $results[$stu->studentid]=$stu->level;
  } 
  return ($results);
  
}

function getListContentAreaStudents($listid, $quarter, $year="2006") {
  global $db;

  $studentlist = getListStudents($listid);
  
  $sql = "select level, studentlevel.studentid from sfascores, studentlevel where studentlevel.studentid in ($studentlist) and studentlevel.studentid = sfascores.studentid and studentlevel.subject = 'RE' ";
  debugPrint ("getContentReadingAreaStudents: $sql");
  $students = $db->get_results($sql);
  foreach ($students as $stu) {
    $results[$stu->studentid]=$stu->level;
  } 
  return ($results);
  
}

function getTutorStudents($tutor, $tutorQ, $year) {
  global $db;
  
  $sql = "select * from sfascores, student where sfascores.studentid = student.studentid and sfascores.$tutorQ = '$tutor' and sfascores.year = '$year'"; 
  debugPrint ("getSFATeacherStudents: $sql");
  $students = $db->get_results($sql, ARRAY_A); 
  return ($students);
}

function getTeacherTutorHomeroom () {
  global $db;

  $sql = "select user.userid, user.name from sfascores, user where sfascores.homeroom = user.userid
          or sfascores.base_reading = user.userid or sfascores.base_tutor = user.userid 
          or sfascores.first_reading = user.userid or sfascores.first_tutor = user.userid 
          or sfascores.second_reading = user.userid or sfascores.second_tutor = user.userid 
          or sfascores.third_reading = user.userid or sfascores.third_tutor = user.userid 
          group by user.userid";
  debugPrint ("getTeacherTutorHomeroom: $sql");
  $users = $db->get_results($sql);
  foreach ($users as $u) {
    $results[$u->userid]=$u->name;
  } 
  return ($results);
}

function getDates ($year) {
  global $db;
  
  $sql = "select * from sfainfo where year = '$year'"; 
  debugPrint ("sfainfo: $sql");
  $dt = $db->get_results($sql, ARRAY_A); 
  return ($dt[0]);

}

function setupHotList () {
  global $db;
  
  $sql = "select * from hotlist";
  debugPrint("setupHotlist: " . $sql);
  $hl = $db->get_results($sql);   
  foreach ($hl as $cell) {
      $results[$cell->grade][$cell->stage][$cell->score] = "X";
    }
    return($results);
}

function setupLines () {
  global $db;
  
  $sql = "select * from line";
  debugPrint("setupHotlist: " . $sql);
  $hl = $db->get_results($sql);   
  foreach ($hl as $cell) {
      $results[$cell->grade][$cell->stage][$cell->score] = $cell->value;
    }
    return($results);
}

function buildGroupUrl($ids, $show, $value, $num="") {
   $ids = str_replace("'", "\'", $ids);
   $str = "<form name=sl$num method=post action=index.php?cmd=sfadrilldown&module=sfa> <input type=hidden name=studentlist value=\"$ids\"> <a href=\"javascript:document.sl$num.submit();\" onMouseOver=\"return escape('Students: $show')\">$value</a></form>";
   return $str;
}

function getStudentsFromList($studentlists) {
         global $db;

         $sql = "SELECT * FROM student where student.studentID in ($studentlists -1) order by lname";
         debugPrint("getStudentsFromList: " . $sql);
         $results = $db->get_results($sql); 
         return ($results); 

}

function getTeachers() {
  global $db;
  
  $sql = "select * from user where homeroom != '' or reading != '' or tutor != ''";
  $users = $db->get_results($sql);   
  foreach ($users as $user) {
      $results[$user->userid]['name'] = $user->name;
    }
    return($results);
}


?>
