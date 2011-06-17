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
    	$clause = " and student.grade != 'K' and student.grade != 'sped'";
    	break;
     case 'K':
    	$clause = " and student.grade = 'K'";
    	break;
     default:
     	$clause = "";
    }
    
  $studentlist = getListStudents($listid);
    
  $sql = "select * from sfascores, student where sfascores.year = '$year' and student.studentid = sfascores.studentid and student.studentid in ($studentlist) and student.status='Active' $clause";
  debugPrint("GetAllGroupScores: " . $sql);
  $results = $db->get_results($sql);
  $cutoff = getCutOffs();

  foreach ($results as $res) {
        debugPrint($res->studentid . "=> " . $res->base_score . "-");
		if($res->base_rawscore != "") {
		   debugPrint("KC"); 
		   $score['base'][$res->gradelvel]['count']['value']+