<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

function getSipYearOption ($year) {
	global $db, $CurrentYear;
	
  	for ($yr = 2005; $yr <= $CurrentYear+1; $yr++) {
		$nextval = $yr + 1;
		$selected = $year == $yr ? "selected": "";
		$str .= "<option value='$yr' $selected>$yr-$nextval</option>\n";
  	}
  	return ($str);	
}

function getStudentsFromList($studentlists) {
         global $db;

         $sql = "SELECT * FROM student where student.studentID in ($studentlists -1) order by lname";
         debugPrint("getStudentsFromList: " . $sql);
         $results = $db->get_results($sql); 
         return ($results); 

}

function saveField($sid, $field, $value) {
         global $db;

         $sql = "UPDATE sipaux SET $field = '$value' where sid = '$sid'";
         debugPrint("saveField: " . $sql);
         $results = $db->get_results($sql); 
         return ($results); 
}

function getField($sid, $field) {
         global $db;

         $sql = "SELECT $field as value FROM sipaux where sid = '$sid'";
         debugPrint("saveField: " . $sql);
         $results = $db->get_results($sql); 
         return ($results[0]->value); 
}

function buildGroupUrl($ids, $show, $value, $num="") {
	if(isset($value) and $value != "") {
	   $ids = str_replace("'", "\'", $ids);
	   $str = "<form name=sl$num method=post action=index.php?cmd=sipdrilldown&module=sip> <input type=hidden name=studentlist value=\"$ids\"> <a href=\"javascript:document.sl$num.submit();\" onMouseOver=\"return escape('Students: $show')\"><center>$value</center></a></form>";
	} else {
		$str = "<br>&nbsp;<br>";
	}
   return $str;
}

function produceListTable($top, $side, $data) {

	$body = "<table border=1 cellpadding=0 cellspacing=0>";
	$body .= "<tr bgcolor=yellow><th></th>";
	foreach ($top as $t) {
		$value = $t['name'];
		$tip = $t['tip'];
		$body .= "<th width=30 onMouseOver=\"return escape('$tip')\"><center>$value</center></th>";
	}
	$i = 0;
	foreach ($side as $s) {
		 $val1 = $s['value'];
		 $name1 = $s['name'];
		 $tip = $s['tip'];
		 $row1 = $s['row'];
		 $body .=  "<tr $row1><td>$name1&nbsp;</td>";
		foreach ($top as $t) {
			$val2 = $t['value'];
			$value = $data[$val2][$val1]['value'];
			$body .=  "<td valign=middle align=center>$value&nbsp;</td>";
			$i++;
		}
		 $body .=  "</tr>";
	 }
	 
	 $body .= "</table>";
	 
	 return ($body);

}

function produceTable($top, $side, $data) {

	$body = "<table border=1 cellpadding=0 cellspacing=0>";
	$body .= "<tr bgcolor=yellow><th></th>";
	foreach ($top as $t) {
		$value = $t['name'];
		$tip = $t['tip'];
		$body .= "<th width=30 onMouseOver=\"return escape('$tip')\"><center>$value</center></th>";
	}
	$body .= "</tr>";
	$i = 0;
	foreach ($side as $s) {
		 $val1 = $s['value'];
		 $name1 = $s['name'];
		 $row1 = $s['row'];
		 $body .=  "<tr $row1><td>$name1</td>";	 
		foreach ($top as $t) {
			$val2 = $t['value'];
			if($val2 == 'Reading' || $val2 == 'Writing' || $val2 == 'Math') { 
				$color = 'bgcolor=yellow'; 
			} else { $color = ""; }
			$value = $data[$val2][$val1]['value'];
			$ids = $data[$val2][$val1]['ids'];
			$names = $data[$val2][$val1]['names'];
			$ins = buildGroupUrl($ids, $names, $value, $i);
			$body .=  "<td valign=middle $color>$ins</td>";
			$i++;
		}
		 $body .=  "</tr>";
	 }
	 
	 $body .= "</table>";
	 
	 return ($body);

}
function testValueInfo($test, $year, $parameters = '') {
	global $db;

	$top = $db->get_results("select name, value, tip from siptestfields where test = '$test' order by ord", ARRAY_A);
	return($top);
}

function testInfo ($test, $year, $parameters = '') {
	global $db;

	$top = $db->get_results("select name, value, tip from siptestfields where test = '$test' order by ord", ARRAY_A);


	$j = 0;
	$side[$j]['name'] = "Adv";
	$side[$j++]['value'] = "Adv";
	$side[$j]['name'] = "Prof";
	$side[$j++]['value'] = "Prof";
	$side[$j]['name'] = "BP";
	$side[$j++]['value'] = "BP";
	$side[$j]['name'] = "FBP";
	$side[$j++]['value'] = "FBP";
	$side[$j]['name'] = "No Scores Recorded";
	$side[$j++]['value'] = "";
//	$side[4]['row'] = " bgcolor = red";

	$side[$j]['name'] = "";
	$side[$j]['value'] = "-";
	$side[$j++]['row'] = " bgcolor = black";

	$side[$j]['name'] = "Number Proficient";
	$side[$j++]['value'] = "NumberP";
	$side[$j]['name'] = "Percentage Proficient";
	$side[$j++]['value'] = "PercentP";

	$side[$j]['name'] = "";
	$side[$j++]['value'] = "-";

	$side[$j]['name'] = "Number Not Proficient";
	$side[$j++]['value'] = "NumberNP";
	$side[$j]['name'] = "Percentage Not Proficient";
	$side[$j++]['value'] = "PercentNP";
	
//	$serials = serialize($side);
//	echo $serials;
	
/*	a:10:
{
 i:0;a:2:{s:4:"name";s:3:"Adv";s:5:"value";s:3:"Adv";}
 i:1;a:2:{s:4:"name";s:4:"Prof";s:5:"value";s:4:"Prof";}
 i:2;a:2:{s:4:"name";s:2:"BP";s:5:"value";s:2:"BP";}
 i:3;a:2:{s:4:"name";s:3:"FBP";s:5:"value";s:3:"FBP";}
 i:4;a:2:{s:4:"name";s:0:"";s:5:"value";s:0:"";}
 i:5;a:2:{s:4:"name";s:3:"FBP";s:5:"value";s:3:"FBP";}
 i:6;a:2:{s:4:"name";s:3:"FBP";s:5:"value";s:3:"FBP";}
 i:7;a:2:{s:4:"name";s:3:"FBP";s:5:"value";s:3:"FBP";}
 i:8;a:2:{s:4:"name";s:3:"FBP";s:5:"value";s:3:"FBP";}
 i:9;a:2:{s:4:"name";s:0:"";s:5:"value";s:0:"";}
}
*/
	$j = 0;
	for ($i = -25; $i < 25; $i++) {
		$diff[$j]['name'] = "$i";
		$diff[$j]['value'] = "$i";
		switch($i) {
			case 0:
				$diff[$j]['row'] = "  bgcolor=lightgreen";
				break;
		}
		$j++;
	}

	$diff[$j]['name'] = "Number Proficient";
	$diff[$j++]['value'] = "NumberP";
	$diff[$j]['name'] = "Percentage Proficient";
	$diff[$j++]['value'] = "PercentP";

	$diff[$j]['name'] = "";
	$diff[$j++]['value'] = "";

	$diff[$j]['name'] = "Number Not Proficient";
	$diff[$j++]['value'] = "NumberNP";
	$diff[$j]['name'] = "Percentage Not Proficient";
	$diff[$j++]['value'] = "PercentNP";
	
	
	$ret['side'] = $side;
	$ret['top'] = $top;
	
	$ret['diffside'] = $diff;
	
	return ($ret);

}

function selectStudents ($test, $year, $parameters = '', $table='') {
	global $db;

	$sql = "select fname, lname, student.studentid, standard, level, difference
	        FROM student, testscores $table
	        WHERE
	        	student.alaskaid = testscores.alaskaid and
	        	testscores.test = '$test' and 
	        	year = '$year' $parameters
	        ";
// student.alaskaid = '819000' 
//	        echo ($sql);
    $results = $db->get_results($sql);
//    print_r($results);
//    print_r($results);
	$info = "";
	foreach ($results as $r) {
		$info[$r->standard][$r->level]['value']++;
		$info[$r->standard][$r->level]['names'] .= $r->fname . " " . $r->lname . ": ";
		$info[$r->standard][$r->level]['ids'] .= $r->studentid . ", ";
		$info['grandsum'][$r->level]['value']++;
//		echo "Standard: " . $r->standard . " Level: " . $r->level . "-";
//		echo  $info[$r->standard][$r->level]['value'] . "-<br>";
		$info['grandsum'][$r->level]['names'] .= $r->fname . " " . $r->lname . ": ";
		$info['grandsum'][$r->level]['ids'] .= $r->studentid . ", ";
		if($r->level == 'Prof' || $r->level == 'Adv') {
		  $info[$r->standard]['NumberP']['value']++;
		  $info[$r->standard]['NumberP']['names'] .= $r->fname . " " . $r->lname . ": ";
		  $info[$r->standard]['NumberP']['ids'] .= $r->studentid . ", ";
		  
		  $diff[$r->standard]['NumberP']['value'] = $info[$r->standard]['NumberP']['value'];
		  $diff[$r->standard]['NumberP']['names'] = $info[$r->standard]['NumberP']['names'];
		  $diff[$r->standard]['NumberP']['ids'] = $info[$r->standard]['NumberP']['ids'];
		} else {
		  $info[$r->standard]['NumberNP']['value']++;
		  $info[$r->standard]['NumberNP']['names'] .= $r->fname . " " . $r->lname . ": ";
		  $info[$r->standard]['NumberNP']['ids'] .= $r->studentid . ", ";
		  
		  $diff[$r->standard]['NumberNP']['value'] = $info[$r->standard]['NumberNP']['value'];
		  $diff[$r->standard]['NumberNP']['names'] = $info[$r->standard]['NumberNP']['names'];
		  $diff[$r->standard]['NumberNP']['ids'] = $info[$r->standard]['NumberNP']['ids'];
		}
		$total = $info[$r->standard]['NumberP']['value'] + $info[$r->standard]['NumberNP']['value'];
		$info[$r->standard]['PercentP']['value'] = makePercent($info[$r->standard]['NumberP']['value']/ $total);
		$info[$r->standard]['PercentNP']['value'] = makePercent($info[$r->standard]['NumberNP']['value']/ $total);
		$info[$r->standard]['PercentP']['names'] = $info[$r->standard]['NumberP']['names'];
		$info[$r->standard]['PercentP']['ids'] = $info[$r->standard]['NumberP']['ids'];
		$info[$r->standard]['PercentNP']['names'] = $info[$r->standard]['NumberNP']['names'];
		$info[$r->standard]['PercentNP']['ids'] = $info[$r->standard]['NumberNP']['ids'];

		$diff[$r->standard][$r->difference]['value']++;
		$diff[$r->standard][$r->difference]['names'] .= $r->fname . " " . $r->lname . ": ";
		$diff[$r->standard][$r->difference]['ids'] .= $r->studentid . ", ";
		$diff[$r->standard]['PercentP']['value'] = $info[$r->standard]['PercentP']['value'];
		$diff[$r->standard]['PercentNP']['value'] = $info[$r->standard]['PercentNP']['value'];
		$diff[$r->standard]['PercentP']['names'] = $info[$r->standard]['PercentP']['names'];
		$diff[$r->standard]['PercentP']['ids'] = $info[$r->standard]['PercentP']['ids'];
		$diff[$r->standard]['PercentNP']['names'] = $info[$r->standard]['PercentNP']['names'];
		$diff[$r->standard]['PercentNP']['ids'] = $info[$r->standard]['PercentNP']['ids'];
		
	}
	
	$student['chart'] = $info;
	$student['diff'] = $diff;
	return $student;
	
}

function makePercent ($num) {
	$ret = number_format($num*100, 0);
	$ret .= "%";
	return ($ret);
}

function getStudentArray ($site = "") {
    global $db;
    //CONCAT(name, ' is in ', region) 
    
    $clause = ($site != '') ? "Where village = '$site'" : "";
	$sql = "select studentid as id, CONCAT(fname, ' ', lname) as name
	        FROM student
	        $clause
	        Order by lname
	        ";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function getDistrictSip ($year) {
	global $db;
	
	$sql = "select *
	        FROM sip,sipaux
	        WHERE
	        	sip.id = sipaux.sid and
	        	sip.kind = 'district' and
	        	sip.year = '$year'
	        ";
//	echo $sql;
    $results = $db->get_results($sql, ARRAY_A);
//    print_r($results);
    echo $results['r1'];
    return ($results[0]);

}

function saveDistrictSiteSip ($data) {
	global $db;
	
//	showarray($data);
	
	$sid = $data['id'];
	$sql = "update sipaux
	        SET
	        	district = '" . $data['district'] . "',
	        	stateques = '" . $data['stateques'] . "',
	        	link = '" . $data['link'] . "',
	        	ques3 = '" . $data['ques3'] . "',
	        	link3 = '" . $data['link3'] . "',
	        	ques4 = '" . $data['ques4'] . "',
	        	link4 = '" . $data['link4'] . "',
	        	g11 = '" . $data['g11'] . "',
	        	g12 = '" . $data['g12'] . "',
	        	g13 = '" . $data['g13'] . "',
	        	g14 = '" . $data['g14'] . "',
	        	g15 = '" . $data['g15'] . "',
	        	g21 = '" . $data['g21'] . "',
	        	g22 = '" . $data['g22'] . "',
	        	g23 = '" . $data['g23'] . "',
	        	g24 = '" . $data['g24'] . "',
	        	g25 = '" . $data['g25'] . "',
	        	g31 = '" . $data['g31'] . "',
	        	g32 = '" . $data['g32'] . "',
	        	g33 = '" . $data['g33'] . "',
	        	g34 = '" . $data['g34'] . "',
	        	g35 = '" . $data['g35'] . "',
	        	g41 = '" . $data['g41'] . "',
	        	g42 = '" . $data['g42'] . "',
	        	g43 = '" . $data['g43'] . "',
	        	g44 = '" . $data['g44'] . "',
	        	g45 = '" . $data['g45'] . "',
	        	emphasisR = '" . $data['emphasisR'] . "',
	        	emphasisW = '" . $data['emphasisW'] . "',
	        	emphasisM = '" . $data['emphasisM'] . "',	        	
	        	r1 = '" . $data['r1'] . "',
	        	r2 = '" . $data['r2'] . "',
	        	r3 = '" . $data['r3'] . "',
	        	r4 = '" . $data['r4'] . "',
	        	w1 = '" . $data['w1'] . "',
	        	w2 = '" . $data['w2'] . "',
	        	w3 = '" . $data['w3'] . "',
	        	w4 = '" . $data['w4'] . "',
	        	m1 = '" . $data['m1'] . "',
	        	m2 = '" . $data['m2'] . "',
	        	m3 = '" . $data['m3'] . "',
	        	m4 = '" . $data['m4'] . "',
	        	i1 = '" . $data['i1'] . "',
	        	i2 = '" . $data['i2'] . "',
	        	i3 = '" . $data['i3'] . "',
	        	i4 = '" . $data['i4'] . "'
	        WHERE
	        	sid = '$sid'
	        ";
//	echo $sql;
    $results = $db->query($sql);
    saveactions($sid, "r", $data['reading_id'], $data['reading_action'], $data['reading_person'], $data['reading_kind'], $data['reading_timeline'], $data['reading_eval'], $data['reading_final']);
    saveactions($sid, "w", $data['writing_id'], $data['writing_action'], $data['writing_person'], $data['writing_kind'], $data['writing_timeline'], $data['writing_eval'], $data['writing_final']);
    saveactions($sid, "m", $data['math_id'], $data['math_action'], $data['math_person'], $data['math_kind'], $data['math_timeline'], $data['math_eval'], $data['math_final']);
//    print_r($results);

}

function saveTeacherSiteSip ($data) {
//print_r($data);
	$sid = $data['id'];
	$area = $data['area'];
	$areatype = $data['areatype'];
//print_r( $data['reading' . '_id']);
	
    saveactions($sid, $area, 
    				$data[$areatype . '_id'], 
    				$data[$areatype . '_action'], 
    				$data[$areatype . '_person'], 
    				$data[$areatype . '_kind'], 
    				$data[$areatype . '_timeline'], 
    				$data[$areatype . '_eval'], 
    				$data[$areatype . '_final']
    			);
}


function saveactions($sid, $area, $id, $action, $person, $kind, $timeline, $eval, $final) {
  global $db;
  
  for ($i = 0; $i < count($id); $i++) {
//  	echo ($id[$i] . $action[$i] . $person[$i] . $kind[$i] . $timeline[$i] . $eval[$i] . $final[$i] . "<br>");
	 if ($id[$i] != '' or $action[$i] != '' or $person[$i] != '' or $kind[$i] != '' or $timeline[$i] != '' or $eval[$i] != '' or $final[$i]) {
			$set = "area = '$area',
					sid = '$sid',
					action = '" . $action[$i] . "',
					person = '" . $person[$i] . "',
					ptype = '" . $kind[$i] . "',
					timeline = '" . $timeline[$i] . "',
					eval = '" . $eval[$i] . "',
					final = '" . $final[$i] . "'
					";
					
			if($id[$i] == '') {
				$sql = "INSERT into sipaction 
						SET
							$set
						";
			} else {
				$sql = "UPDATE sipaction
						SET
							$set
						WHERE
							aid = '" . $id[$i] . "'
						";
			}
//			echo $sql . "<br>";
			$results = $db->query($sql);
	  }
	}
}

function createTeacherSipNew($year, $test, $area, $grp, $name) {
	global $currentUserName, $currentUserID, $currentMySite, $db;
	
	$timestamp = date("Y-m-d H-i-s");
	$sql = "INSERT into sip
			SET
				kind = 'teacher',
				listid = '$grp',
				test = '$test',
				site = '$currentMySite',
				area = '$area',
				name = '$name',
				owner = '$currentUserID',
				year = '$year',
				status = 'open',
				datecreated = '$timestamp'
				";
//	echo $sql;
	$results = $db->query($sql);
	return($db->insert_id);
}

function createTeacherSip($year, $test, $area, $grp, $name) {
	global $currentUserName, $currentUserID, $currentMySite, $db;
	
	$timestamp = date("Y-m-d H-i-s");
	$sql = "INSERT into sip
			SET
				kind = 'teacher',
				test = '$test',
				listid = '$grp',
				site = '$currentMySite',
				area = '$area',
				name = '$name',
				owner = '$currentUserID',
				year = '$year',
				status = 'open',
				datecreated = '$timestamp'
				";
//	echo $sql;
	$results = $db->query($sql);
	return($db->insert_id);
}

function getSip($sipid) {
	global $db;
	
	$sql = "select *
	        FROM sip
	        Left join sipaux ON sip.id = sipaux.sid
	        WHERE
				id = $sipid
	        ";
//	echo($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results[0]);
 }
 
function getSipYearKind($year, $kind='district', $site='') {
	global $db;
	
	$clause = $site != '' ? "sip.site = '$site' and ": "";
	$sql = "select *
	        FROM sip
	        left join sipaux ON sip.id = sipaux.sid
	        WHERE
	        	$clause
	        	sip.kind = '$kind' and sip.year = '$year'
	        ";
    $results = $db->get_results($sql, ARRAY_A);
    if($results[0]['id'] == '') {
    	$sql2 = "INSERT INTO sip SET kind = '$kind', site = '$site', year = '$year', status = 'open', owner = '$currentUserID'";
    	$db->get_results($sql2);
    	$sid = $db->insert_id;
    	$sql3 = "INSERT INTO sipaux SET sid = '$sid'";
    	$db->get_results($sql3);    	
    	$results = $db->get_results($sql, ARRAY_A);
    }
    return ($results[0]);
}

function getSipStudents($sipid) {
	global $db;
	
	$sql = "select *
	        FROM sipstudents, students
	        left join test ON test.studentid = sipstudents.studentid
	        WHERE
	        	sipstudents.studentid = students.studentid
	        ";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function showarray($data) {
	while(list($var, $val) = each($data)) {
		if(is_array($val) ) {
			echo ("$var => " . print_r ($val, true));
		} else {
       		echo("var $var => $val <br>");
       	}
	}
}

function getTeacherSip ($where, $year='') {
	global $db;
	
	$clause = ($year == '' ) ? "": "and year = '$year'" ;
	$sql = "select *, user.name as uname, sip.name as sname
	        FROM sip, user
	        WHERE
	        	sip.kind = 'teacher' and
	        	sip.owner = user.userid
	        	$clause
	        	$where
	        ORDER BY
	        	user.site, user.name
	        ";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}	


function showSipGroups($type='', $value='', $year) {
	if($type == 'district') $sips = getTeacherSip ('', $year);
	else if ($type == 'site') $sips = getTeacherSip("and user.site = '$value'", $year);
	else if ($type == 'none') $sips = getTeacherSip("and user.userid = '$value'", $year);
	foreach ($sips as $sip) {
		$name = $sip['sname'];
		$sipdisplay[$sip['user']]['name'] = $sip['uname'];
		$sipdisplay[$sip['user']]['site'] = $sip['site'];
		$delete = "<a onClick='return confirmMsg(\"Delete $name\");' href=index.php?cmd=deletesip&module=sip&year=$year&sid=" . $sip['id'] . ">[x]</a>";
		$sipdisplay[$sip['user']]['link'] .= "<a href=index.php?cmd=teachersip&module=sip&sid=" . $sip['id'] . "> ". $name . "</a>$delete : ";
	}
	$site = '';
	foreach ($sipdisplay as $sipd) {
		if($site !== $sipd['site']) {
			$results .= "<b>" . $sipd['site'] . "</b><br>";
			$site = $sipd['site'];
		}
		$results .= $sipd['name'] . ": " . $sipd['link'] . "<br>";
	}
 	return ($results);
}

function getActionPlans ($site='', $year='', $type ='teacher') {
	global $db;
	
	$clause = $site == ''?'':" and sip.site = '$site' ";
	$clause .= ($type == 'teacher') ? " and sip.owner = user.userid":"";
	$clause .= ($year == '') ? "" : " and sip.year = '$year'";
	$select = ($type == 'teacher') ? ", user.name as uname": "";
	$from = ($type == 'teacher') ? "user, ": "";
	$order = ($type == 'teacher') ?
							"ORDER BY sip.site, sip.area, user.name, sipaction.sid":
							"ORDER BY sip.site, sip.area, sip.id";
	$sql = "select *, sip.name as sname, sip.area as sarea $select
	        FROM $from sip
	        LEFT join sipaction ON sip.id = sipaction.sid 
	        WHERE
	        	sip.kind = '$type'	        	
	        	$clause
	        $order
	        ";
//	echo("$type=>$sql<br>");
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}	

function produceSiteTable($siteshow, $year, $report=false) {
	$results .= "
	<style>
	.sip1
	{
		font-weight: bold;
		font-size: 18px;
	}
	.sip2
	{
		font-weight: bold;
		font-size: 14px;
	}
	.sip3
	{
		font-weight: bold;
		font-style: italic;
	}
	.siptopic
	{
	}
	</style>
	";
	$sips = getActionPlans ($siteshow, $year);
//	echo print_r($sips, true) . "<br><br>";
	foreach ($sips as $sip) {
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['site'] = $sip['site'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['uname'] = $sip['uname'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['sname'] = $sip['sname'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['action'] = $sip['action'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['timeline'] = $sip['timeline'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['ptype'] = $sip['ptype'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['eval'] = $sip['eval'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['person'] = $sip['person'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['sip'] = $sip['id'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['area'] = $sip['sarea'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['kind'] = $sip['kind'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['aid'] = $sip['aid'];
	}
	$site = '';
	$user = '';
	$id = '';
	if($sipdisplay == '') {
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['site'] = $siteshow;
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['area'] = 'NONE';
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['action'] = 'DUMMY';
	}
	
//	$results .= "ACTION PLANS<br><br>";
	$dist = getDistrictSip($year);
	$results .= $siteshow == ""? produceDistrictSip($year, $report) : "";
	foreach ($sipdisplay as $sipd0) {
		foreach ($sipd0 as $sipd1) {
			foreach ($sipd1 as $sipd2) {
				foreach ($sipd2 as $sipd) {
//					echo print_r($sipd, true) . "<br>";
					if($site !== $sipd['site']) {
						$site = $sipd['site'];
	//					echo  "Site: $site -- ";
						$results .= produceSiteSip($site, $year, $dist, $report);
					}
					if($user !== $sipd['uname'].$sipd['sip']) {
						$results .= "<div class=sip3>" . $sipd['uname'] . "</div>";
						$user = $sipd['uname'].$sipd['sip'];
					}
					if($id !== $sipd['sip']) {
						$id = $sipd['sip'];
						$kind = $sipd['kind'];
	//					$results .=  "ID: $id $kind -- ";
						$results .= "&nbsp;&nbsp;" . $sipd['sname'] . " (" . $sipd['area'] . ")<br>";
					}
	//				echo $sipd['site'] ."-" . $sipd['sip'] ."-" . $sipd['aid'] . "<br>";
					if($sipd['action'] != 'DUMMY') {
						$results .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Smart Plan:</b> " . $sipd['action'] . " <b>Evaluation:</b> " . $sipd['eval']. "<br>";
//						$results .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Action Plan:</b> " . $sipd['action'] . " <b>Person:</b> " . $sipd['person'];
//						if($report) {
//							$results .= " <b>Position:</b> " . $sipd['ptype'] ." <b>Timeline:</b> " . $sipd['timeline'] . " <b>Eval:</b> " . $sipd['eval'] .  "<br>";
//						} else {
//							$results .= "<br>";				
//						}
					}
				}
			}
		}
	}
 	return ($results);
}

function produceSiteTable_new($siteshow, $year, $report=false) {
	$results .= "
	<style>
	.sip1
	{
		font-weight: bold;
		font-size: 18px;
	}
	.sip2
	{
		font-weight: bold;
		font-size: 14px;
	}
	.sip3
	{
		font-weight: bold;
		font-style: italic;
	}
	.siptopic
	{
	}
	</style>
	";
	$sips = getActionPlans ($siteshow, $year);
//	echo print_r($sips, true) . "<br><br>";
	foreach ($sips as $sip) {
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['site'] = $sip['site'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['uname'] = $sip['uname'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['sname'] = $sip['sname'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['action'] = $sip['action'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['person'] = $sip['person'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['timeline'] = $sip['timeline'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['ptype'] = $sip['ptype'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['eval'] = $sip['eval'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['sip'] = $sip['id'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['area'] = $sip['sarea'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['kind'] = $sip['kind'];
		$sipdisplay[$sip['aid']][$sip['area']][$sip['id']]['aid'] = $sip['aid'];
/*
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['site'] = $sip['site'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['uname'] = $sip['uname'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['sname'] = $sip['sname'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['action'] = $sip['action'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['person'] = $sip['person'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['sip'] = $sip['id'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['area'] = $sip['sarea'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['kind'] = $sip['kind'];
		$sipdisplay[$sip['site']][$sip['aid']][$sip['area']][$sip['id']]['aid'] = $sip['aid'];
*/
}
	$site = '';
	$user = '';
	$id = '';
	
//	$results .= "ACTION PLANS<br><br>";
	$dist = getDistrictSip($year);
	$results .= $siteshow == ""? produceDistrictSip($year, $report) : "";
//	foreach ($sipdisplay as $sipd0) {
		foreach ($sip0 as $sipd1) {
			foreach ($sipd1 as $sipd2) {
				foreach ($sipd2 as $sipd) {
		//			echo print_r($sipd, true) . "<br>";
					if($site !== $sipd['site']) {
						$site = $sipd['site'];
	//					echo  "Site: $site -- ";
						$results .= produceSiteSip($site, $year, $dist, $report);
					}
					if($user !== $sipd['uname'].$sipd['sip']) {
						$results .= "<div class=sip3>" . $sipd['uname'] . "</div>";
						$user = $sipd['uname'].$sipd['sip'];
					}
					if($id !== $sipd['sip']) {
						$id = $sipd['sip'];
						$kind = $sipd['kind'];
	//					$results .=  "ID: $id $kind -- ";
						$results .= "&nbsp;&nbsp;" . $sipd['sname'] . " (" . $sipd['area'] . ")<br>";
					}
	//				echo $sipd['site'] ."-" . $sipd['sip'] ."-" . $sipd['aid'] . "<br>";
					$results .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Smart Plan:</b> " . $sipd['action'] . " <b>Evaluation:</b> " . $sipd['eval'] . "<br>";
//					$results .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Action Plan:</b> " . $sipd['action'] . " <b>Person:</b> " . $sipd['person'];
//					if($report) {
//						$results .= " <b>Position:</b> " . $sipd['ptype'] ." <b>Timeline:</b> " . $sipd['timeline'] . " <b>Eval:</b> " . $sipd['eval'] .  "<br>";
//					} else {
//						$results .= "<br>";				
//					}
				}
			}
		}
//	}
 	return ($results);
}

function produceSiteSip ($site, $year='', $dist='', $report=false) {
	$sips = getActionPlans ($site, $year, 'site');
	foreach ($sips as $sipd) {
		$actions[$sipd['area']] .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Smart Plan:</b> " . $sipd['action'] . " <b>Evaluation:</b> " . $sipd['eval'] . "<br>";
//		$actions[$sipd['area']] .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Action Plan:</b> " . $sipd['action'] . " <b>Person:</b> " . $sipd['person'];
//		if($report) {
//			$actions[$sipd['area']]  .= " <b>Position:</b> " . $sipd['ptype'] ." <b>Timeline:</b> " . $sipd['timeline'] . " <b>Eval:</b> " . $sipd['eval'] .  "<br>";
//		} else {
//			$actions[$sipd['area']]  .= "<br>";				
//		}
	}
	$sip = getSipYearKind($year, 'site', $site);
	$results .= "<br><br><div class=sip1>" . $site . "</div><br>";
	if($report) {
		$results .= "<div class=sip2>State Questions</div>";
		$results .= "<div class=siptopic>" . $dist['stateques'] . "</div><br>";
		$results .= "<span class=sip2>Subject Listed In Order Of Strength</span><br>"
				 . $sip['subjectorder'] . "<br><br> 
				<span class=sip2>Strongest And Weakest Grades for Each Subject</span><br />"
				 . $sip['graderating'] . "<br /><br />
				<span class=sip2>Areas of emphasis:</span><br />			
				<span class=sipsubheading>Reading:</span> 
				<span class=sipsubheading>" . $sip['emphasisR'] . "</span><br />
				<span class=sipsubheading>Writing:</span> 
				<span class=sipsubheading>" . $sip['emphasisW'] . "</span><br />
				<span class=sipsubheading>Math:</span> 
				<span class=sipsubheading>" . $sip['emphasisM'] . "</span><br /><br />
				";

	} else {
		$results .= "<div class=sip2>District Sip Message</div>";
		$results .= "<div class=siptopic>" . $dist['district'] . "</div><br>";	
	}

	$results .= "<div class=sip2>Reading</div>";
	$results .= "<div class=sip3>Objective (Area of need to be addressed)</div>";
	$results .= "<div class=siptopic>" . $sip['r1'] . "</div><br>";
	$results .= "<div class=sip3>Current Performance Level on SBAs:</div>";
	$results .= "<div class=siptopic>" . $sip['r2'] . "</div><br>";
	$results .= "<div class=sip3>Performance Target (Measurable Change)</div>";
	$results .= "<div class=siptopic>" . $sip['r3'] . "</div><br>";
	$results .= "<div class=sip3>Scientifically based research to support for each strategy or curriculum listed below:</div>";
	$results .= "<div class=siptopic>" . $dist['r4'] . "</div><br>";
	$results .= "<div class=sip3>Action Plan (Reading)</div>";
	$results .= $actions['r'] . "<br>";

	$results .= "<div class=sip2>Writing</div>";
	$results .= "<div class=sip3>Objective (Area of need to be addressed)</div>";
	$results .= "<div class=siptopic>" . $sip['w1'] . "</div><br>";
	$results .= "<div class=sip3>Current Performance Level on SBAs:</div>";
	$results .= "<div class=siptopic>" . $sip['w2'] . "</div><br>";
	$results .= "<div class=sip3>Performance Target (Measurable Change)</div>";
	$results .= "<div class=siptopic>" . $sip['w3'] . "</div><br>";
	$results .= "<div class=sip3>Scientifically based research to support for each strategy or curriculum listed below:</div>";
	$results .= "<div class=siptopic>" . $dist['w4'] . "</div><br>";
	$results .= "<div class=sip3>Action Plan (Writing)</div>";
	$results .= $actions['w'] . "<br>";

	$results .= "<div class=sip2>Math</div>";
	$results .= "<div class=sip3>Objective (Area of need to be addressed)</div>";
	$results .= "<div class=siptopic>" . $sip['m1'] . "</div><br>";
	$results .= "<div class=sip3>Current Performance Level on SBAs:</div>";
	$results .= "<div class=siptopic>" . $sip['m2'] . "</div><br>";
	$results .= "<div class=sip3>Performance Target (Measurable Change)</div>";
	$results .= "<div class=siptopic>" . $sip['m3'] . "</div><br>";
	$results .= "<div class=sip3>Scientifically based research to support for each strategy or curriculum listed below:</div>";
	$results .= "<div class=siptopic>" . $dist['m4'] . "</div>";
	$results .= "<div class=sip3>Action Plan (Math)</div>";
	$results .= $actions['m'] . "<br>";
	
	$results .= "<div class=sip2>Teachers Action Plan</div>";	
	$results .= "<div class=sip3>Site Plan</div>";	

	return($results);

}

function produceDistrictSip ($year='', $report=false) {
	$sips = getActionPlans ('', $year, 'district');
	foreach ($sips as $sipd) {
		$actions[$sipd['area']] .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Smart Plan:</b> " . $sipd['action'] . " <b>Evaluation</b> " . $sipd['eval'] . "<br>";
//		$actions[$sipd['area']] .= "&nbsp;&nbsp;&nbsp;&nbsp;+ <b>Action Plan:</b> " . $sipd['action'] . " <b>Person</b> " . $sipd['person'];
//		if($report) {
//			$actions[$sipd['area']]  .= " <b>Position:</b> " . $sipd['ptype'] ." <b>Timeline:</b> " . $sipd['timeline'] . " <b>Eval:</b> " . $sipd['eval'] .  "<br>";
//		} else {
//			$actions[$sipd['area']]  .= "<br>";				
//		}
	}
	$results .= "<br><br><hr><div class=sip1>District</div><br>";
	$sip = getSipYearKind($year);

	if($report) {
		$results .= "<div class=sip2>State Questions</div>";
		$results .= "<div class=siptopic>" . $sip['stateques'] . "</div><br>";
		$results .= "<span class=sip2>Subject Listed In Order Of Strength</span><br>"
				 . $sip['subjectorder'] . "<br><br> 
				<span class=sip2>Strongest And Weakest Grades for Each Subject</span><br />"
				 . $sip['graderating'] . "<br /><br />
				<span class=sip2>Areas of emphasis:</span><br />			
				<span class=sipsubheading>Reading:</span> 
				<span class=sipsubheading>" . $sip['emphasisR'] . "</span><br />
				<span class=sipsubheading>Writing:</span> 
				<span class=sipsubheading>" . $sip['emphasisW'] . "</span><br />
				<span class=sipsubheading>Math:</span> 
				<span class=sipsubheading>" . $sip['emphasisM'] . "</span><br /><br />
				";

	} else {
		$results .= "<div class=sip2>District Sip Message</div>";
		$results .= "<div class=siptopic>" . $sip['district'] . "</div><br>";	
	}
	$results .= "<div class=sip2>Overall Topic</div>";
	$results .= "<div class=siptopic>" . $sip['district'] . "</div><br>";
	$results .= "<div class=sip2>Reading</div>";
	$results .= "<div class=sip3>Objective (Area of need to be addressed)</div>";
	$results .= "<div class=siptopic>" . $sip['r1'] . "</div><br>";
	$results .= "<div class=sip3>Current Performance Level on SBAs:</div>";
	$results .= "<div class=siptopic>" . $sip['r2'] . "</div><br>";
	$results .= "<div class=sip3>Performance Target (Measurable Change)</div>";
	$results .= "<div class=siptopic>" . $sip['r3'] . "</div><br>";
	$results .= "<div class=sip3>Scientifically based research to support for each strategy or curriculum listed below:</div>";
	$results .= "<div class=siptopic>" . $sip['r4'] . "</div><br>";
	$results .= "<div class=sip3>Action Plan (Reading)</div>";
	$results .= $actions['r'] . "<br>";


	$results .= "<div class=sip2>Writing</div>";
	$results .= "<div class=sip3>Objective (Area of need to be addressed)</div>";
	$results .= "<div class=siptopic>" . $sip['w1'] . "</div><br>";
	$results .= "<div class=sip3>Current Performance Level on SBAs:</div>";
	$results .= "<div class=siptopic>" . $sip['w2'] . "</div><br>";
	$results .= "<div class=sip3>Performance Target (Measurable Change)</div>";
	$results .= "<div class=siptopic>" . $sip['w3'] . "</div><br>";
	$results .= "<div class=sip3>Scientifically based research to support for each strategy or curriculum listed below:</div>";
	$results .= "<div class=siptopic>" . $sip['w4'] . "</div><br>";
	$results .= "<div class=sip3>Action Plan (Writing)</div>";
	$results .= $actions['w'] . "<br>";

	$results .= "<div class=sip2>Math</div>";
	$results .= "<div class=sip3>Objective (Area of need to be addressed)</div>";
	$results .= "<div class=siptopic>" . $sip['m1'] . "</div><br>";
	$results .= "<div class=sip3>Current Performance Level on SBAs:</div>";
	$results .= "<div class=siptopic>" . $sip['m2'] . "</div><br>";
	$results .= "<div class=sip3>Performance Target (Measurable Change)</div>";
	$results .= "<div class=siptopic>" . $sip['m3'] . "</div><br>";
	$results .= "<div class=sip3>Scientifically based research to support for each strategy or curriculum listed below:</div>";
	$results .= "<div class=siptopic>" . $sip['m4'] . "</div>";
	$results .= "<div class=sip3>Action Plan (Math)</div>";
	$results .= $actions['m'];

	return($results);
}
function createInitialSip($kind, $year, $site='') {
	global $db;
	
	debugPrint ("createInitialSip: $kind, $year, $site<br>");
	$sip = getSipYearKind($year, $kind, $site);

   if($sip['id'] == '')  {
		$timestamp = date("Y-m-d H-i-s");
		$sql = "INSERT into sip
				SET
					kind = '$kind',
					site = '$site',
					owner = '$currentUserID',
					year = '$year',
					status = 'open',
					datecreated = '$timestamp'
					";
		echo $sql;
		$results = $db->query($sql);
		$sipid = $db->insert_id;
		$sql = "INSERT into sipaux
				SET
					sid = '$sipid'
					";
		echo $sql;
		$results = $db->query($sql);
   }
   echo ("End createInitialSip<br>");
}

function initializeYear () {
	global $db;
	
	createInitialSip('district', '15', '');
	$sql = "SELECT * FROM site";
	echo $sql;
	$sites = $db->get_results($sql, ARRAY_A);
	foreach ($sites as $site) {
		$sitename = $site['siteid']; 
		createInitialSip('site', '15', $sitename);
	}
	
}

function saveAction($value) {
	global $db;

//	print_r($value);
	$area = $value['area'];
	$sid = $value['sid'];
	for($i = 0; $i < count($value['id']) ; $i++) {
		$aid = $value['id'][$i];
		$action = $value['action'][$i];
		$person = $value['person'][$i];
		$kind = $value['kind'][$i];
		$timeline = $value['timeline'][$i];
		$eval = $value['eval'][$i];
		$final = $value['final'][$i];
//		$aid = $value['id'][$i];
		$something = $action or $person or $kind or $timeline or $eval or $final;
		if ($something) { echo "Something"; }
		$set = "area = '$area',
				sid = '$sid',
				action = '" . $action . "',
				person = '" . $person . "',
				ptype = '" . $kind . "',
				timeline = '" . $timeline . "',
				eval = '" . $eval . "',
				final = '" . $final . "'
				";
//		echo "$set<br>";

		echo ("AID: --$aid--<br>");
		if($aid != '') {
			$sql = "UPDATE sipaction
					SET
						$set
					WHERE
						aid = '" . $aid . "'
					";
			$results = $db->query($sql);
		} else if ($something) {
			$sql = "INSERT into sipaction 
					SET
						$set
					";
			$results = $db->query($sql);
		}
	}
//	$sql = "INSERT INTO sipaction area = '$area', sid = '$sid'";
//	echo $sql;
//	$results = $db->query($sql);
}

function deleteAction($aid) {
	global $db;
	
	$sql = "DELETE FROM sipaction where aid = '$aid'";
	echo $sql;
	$results = $db->query($sql);			

}

function deleteTeacherSip ($sid) {
	global $db;
	
	$sip = getSip($sid);
	
	if ($sip['kind'] == 'teacher') {
		// delete sipaux, sipaction, sip
		$db->get_results("delete from sipaux where sid = '$sid'");
		$db->get_results("delete from sipaction where sid = '$sid'");
		$db->get_results("delete from sip where id = '$sid'");
	}
}

function getYearOption ($year) {
	global $db, $CurrentYear;
	
	$years = $db->get_results("select distinct(year) as year from sip");
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


?>
