<?php

function createRepCurRep($id, $start, $finish) {
	global $rootURL, $CurrentYear, $CurrentQuarter;
	
	$debug = $_GET['debug'];
	if($finish != '' ) {
		$filter .= " and studentlevel.start < '$finish' "; 
		$finishDisplay = $finish;
	}
	$startDisplay = "Beginning";
	if ($start != '') {
		$startDisplay = $start;
		if($finish == '') {
			$filter .= "  and (studentlevel.final > '$start' or studentlevel.final = '0000-00-00 00:00:00') ";
			$finishDisplay = "In Progress";
		} else {
			$filter .= " and studentlevel.final > '$start' "; 
		}
	} 
	
	if($finish == '' and $start == '') { // just current
		$filter .= " and studentlevel.final = '0000-00-00 00:00:00' ";
		$startDisplay = $CurrentYear . "-" . substr($CurrentYear + 1, 2, 2) . ":Q$CurrentQuarter";
		$finishDisplay = "In Progress";
	}
	
	$studentInfo = getStudentInfo($id);
	
	$sname = $studentInfo['fname'] . " " . $studentInfo['lname'];
	//  $picture = $rootURL . "/images/student/" . $studentInfo['picture'];
	$picture = $studentInfo['picture'] != "" ? $studentInfo['picture'] : "no_photo.jpg";
	$picture = $rootURL . "/images/student/" . $picture;
	if($unofficial=="Y") { $bkgnd = "background = '" . $rootURL . "/images/unofficial.gif'"; }
	else { $bkgnd = "";}
	$img = $rootURL . "/images/SchoolLogos/" . $studentInfo['logo'] ;
	$sitename = $studentInfo['name'];
	$attendance = getAttendance($id);
	$absent = $attendance[0];
	$present = $attendance[4];
	$rate = $attendance['rate'];
	$alaskaid = $studentInfo['alaskaid'];
	
	$site = $studentInfo['siteid'];
	$sn = getRepNotes($site);
	$content = stripslashes($sn['comment']);
	$content = preg_replace(array('/</', '/>/', '/"/', '/\n/'), array('&lt;', '&gt;', '&quot;', '<br>'), $content);
	// echo $sn;
	if($sn['comment'] != "" and $sn != NULL) {
	$snotes = "<div class=\"noteclassic\" align=\"left\">" .
							$content 
			   . "</div>";
	}
//	$sname="Test";

$enrolled = "TBD"; // 2001-02:Q1
$ans = overAllGPA($id); // 3.857
$overallgpa = $ans['gpa']."/".$ans['credit'];
$periodgpa = filterGPA($id, $filter); // 3.634
$dategen = date("Y-m-d");
$gradesetup = '<img src="http://dart.bssd.org/images/bssd_grading_scale.gif" alt="" height="178" width="249" align="middle" border="0">';
$core = " 'CA', 'CS', 'LS', 'MA', 'RE', 'SC', 'SS', 'TE', 'WR' ";
$core = " Select id from subjects where core = 'x' ";
$classfilter = $filter . " and studentlevel.subject in ($core) ";
$classScore = getStudentOverallScore($id, $classfilter, $start, $finish);
foreach ($classScore as $r) {
	$comment = commentSpace($r['comment']);
	$qpi = commentSpace($r['qpi']);
	$complete = commentSpace($r['complete']); 
	$prog = commentSpace($r['prog']); 
	$progcolor = ($prog == "Not On Track")? "#cc0000":"#228b22";
	if($debug!='') {
		$more = "<br>{$r['spoints']}/{$r['sweight']}";
	}
	$class .= <<<END
	<tr>
		<td><b>{$r['sname']}</b></td>
		<td nowrap width="3%">
			<div align="center">
				<b>{$r['subject']} {$r['level']}</b></div>
		</td>

		<td nowrap width="4%">
			<div align="center">
				<font color="#cc0000"><b>{$r['score']}$more</b></font></div>
		</td>
		<td nowrap width="6%">
			<div align="center">
				<b>$complete</b></div>
		</td>

		<td nowrap>
			<div align="center">
				<b>$qpi</b></div>
		</td>
		<td nowrap width="7%">
			<div align="center">
				<font color="$progcolor"><b>$prog</b></font></div>
		</td>

		<td>
			<div align="left">
				$comment
			</div>
		</td>
	</tr>
END;
}
$electivefilter = $filter . " and studentlevel.subject not in ($core) ";
$electiveScore = getStudentOverallScore($id, $electivefilter);
 foreach ($electiveScore as $r) {
	$comment = commentSpace($r['comment']);
	$qpi = commentSpace($r['qpi']);
	$complete = commentSpace($r['complete']); 
	$prog = commentSpace($r['prog']); 
	$progcolor = ($prog == "Not On Track")? "#cc0000":"#228b22";
	$electives .= <<<END
	<tr>
		<td><b>{$r['sname']}</b></td>
		<td nowrap width="3%">
			<div align="center">
				<b>{$r['subject']} {$r['level']}</b></div>
		</td>

		<td nowrap width="4%">
			<div align="center">
				<font color="#cc0000"><b>{$r['score']}</b></font></div>
		</td>
		<td nowrap width="6%">
			<div align="center">
				<b>$complete</b></div>
		</td>

		<td nowrap>
			<div align="center">
				<b>$qpi</b></div>
		</td>
		<td nowrap width="7%">
			<div align="center">
				<font color="$progcolor"><b>$prog</b></font></div>
		</td>

		<td>
			<div align="left">
				$comment
			</div>
		</td>
	</tr>
END;
}
	$filestr = file_get_contents('repcurrentcreatetemp.inc');
	$str = "\"" . addslashes($filestr) . "\"";
	$str2 = "return($str);";
	$body .= eval($str2);

	return($body);

}

function GetClasses($id) {
	
}
?>