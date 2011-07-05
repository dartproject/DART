<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
include_once("lib/functions_gs.inc");

$listID = $_GET['p1'];    // list id
$sub = $_GET['p2'];       // subject number
$lvl = $_GET['p3'];      // level number
$width = 9;
$cellwidth = 60;

$standards = getSubjectStandardsArray ($sub, $lvl);
$overall = getSubjectOverallArray ($sub, $lvl);
$subInfo = getSubjectInfo ($sub);

$subName =  $subInfo[0]['name'];
$gradlvl = $subInfo[0]['gradLevel']; /* @todo: is this variable used? */
$listName = getListName($listID);

$A2Priv = Privilege(A2);
$A3Priv = Privilege(A3);
$TotalDisplay = 'view';
$menuData = array("" => "Choose One","#top_anchor" => "Top of Page");

$summary = getSummaryInfo();

$data = getSubjectLevelInfo(explode(",", getListStudents($listID)), $sub, $lvl);
$stdcount = count($data);
$total = $stdcount * count($standards);

for($i = 0; $i < count($data); $i++) {
	$student = $data[$i];
	$studentID = $student['studentID'];
	$ch_time = date($dateSettings, $student['change_timestamp']);
	$siteEqual = $currentMySite == $student['site'];
	$idEqual = isset($currentAffiliatedID) && $currentAffiliatedID == $studentID; /* is $currentAffiliatedID always null? */
	$Display =  checkStudent($idEqual, $siteEqual, $A2Priv, $A3Priv);
	$TotalDisplay = (($TotalDisplay == 'edit') or ($Display == 'edit')) ? 'edit':'view';

	$student['gradeSymbols'] = getGradeSymbols($student['gradetype']);
	$student['anchor'] = $student['fname'] ."_" . $student['lname'];
	$student['text'] = $student['lname'].", ".$student['fname']." (".$student['grade'].":".$student['site']." - ".$student['gradetypename'].")";
	$student['change'] = $student['change_username']." (".$ch_time.")";
	$student['display'] = $Display;

	$menuData["#".$student['fname']."_".$student['lname']] = $student['lname'].", ".$student['fname'];

	/* Standards */
	for($j = 0; $j < count($standards); $j++) {
		$std = $standards[$j]['std'];
		if(!isset($student['standards'][$std]))
			$student['standards'][$std] = array("value" => NULL);
		$student_std = $student['standards'][$std];

		// i: insert; u: update
		$type = isset($student_std['value'])? "u" : "i";
		$student['standards'][$std]['name'] =
					"gr".$type."_".$studentID."_".$sub."_".$lvl."_".$std;
		$student['standards'][$std]['selected'] = getEqGradeValue($student['gradetype'], $student_std['value']);
		$student['standards'][$std]['symbol'] = getGradeSymbol($student['gradetype'], $student_std['value']);

		if(!isset($wlist[$std]))
			$wlist[$std] = array("std" => $std, 'link' => '', 'shortname' => '', 'count' => 0, 'sum' => 0, 'comp' => 0);
		$wlist[$std]['std'] = $std;
		$wlist[$std]['link'] = $standards[$j]['link'];
		$wlist[$std]['shortname'] = $standards[$j]['shortname'];
		$wlist[$std]['count']++;
		$wlist[$std]['sum'] += getToggleValue($student_std['value']);
		$wlist[$std]['comp'] = $wlist[$std]['sum']/$stdcount;
	}
	/* Overall */
	for($j = 0; $j < count($overall); $j++) {
		$std = $overall[$j]['std'];
		if(!isset($student['overall'][$std]))
			$student['overall'][$std] = array("value" => NULL);
		
		$student_over = $student['overall'][$std];

		$type = isset($student_over['value'])? "u" : "i";
		$student['overall'][$std]['name'] =
			"gr".$type."_".$studentID."_".$sub."_".$lvl."_".$std;
		$student['overall'][$std]['selected'] = getEqGradeValue($student['gradetype'], $student_over['value']);
		$student['overall'][$std]['symbol'] = getGradeSymbol($student['gradetype'], $student_over['value']);
	}
	/* Summary */
	foreach($summary as $key => $val) {
		if(!isset($student['summary'][$key]))
			$student['summary'][$key] = array("value" => NULL);
		$student_sum = $student['summary'][$key];

		$type = isset($student_sum['value'])? "u" : "i";
		$student['summary'][$key]['name'] = "gr".$type."_".$studentID."_".$sub."_".$lvl."_".$key;
	}

	$student['comment'] = $student['comment']['comment'];
	$type = isset($student['comment']['value'])? "u" : "i";
	$student['comment']['comment_id'] = "gr".$type."_".$studentID."_".$sub."_".$lvl."_comment";
	$student['comment']['esc_comment'] = htmlspecialchars($student['comment']['value']);
	$data[$i] = $student;
}

$menuData["#save_changes"] = "Save All Changes";

$title = "Show Scores for List";

/* Weighted List of Standards & Assessments */
$wlist = array_unique2($wlist);
$wlist = array_sort($wlist, 'comp');
$wnum = min(10, count($wlist));
$buckets = 4;
$start = 0;
$end = $wnum-1+$start;
$t = $wlist[$start]['comp'];
$b = $wlist[$end]['comp'];
$spread = ($t - $b)/$buckets;
$weightedStd = array();
for ($i = $start; $i <= $end; $i++) {
	$val = $wlist[$i]['comp'];
	$sid = $sub.$lvl.".".$wlist[$i]['std'];
	if($spread == 0) {
		$tmpnum = 0;
	}
	else {
		$tmpnum = floor(($val - $b)/$spread);
	}
	$loc = $buckets - min($buckets-1, $tmpnum);
	$weightedStd[$i] = array();
	$weightedStd[$i]['link'] = $wlist[$i]['link'];
	$weightedStd[$i]['class'] = "t$loc";
	$weightedStd[$i]['span'] = $sid."-".$wlist[$i]['shortname'];
}

$smarty->assign('pageTitle',$title);
$smarty->assign('listID',$listID);
$smarty->assign('sub',$sub);
$smarty->assign('lvl',$lvl);
$smarty->assign('subName',$subName);
$smarty->assign('listName',$listName);
$smarty->assign('stdcount',$stdcount);
$smarty->assign('data',$data);
$smarty->assign('standards',$standards);
$smarty->assign('overall',$overall);
$smarty->assign('summary',$summary);
$smarty->assign('totalStd',count($standards));
$smarty->assign('totalOver',count($overall));
$smarty->assign('n_sum',count($summary));

$smarty->assign('cellwidth',$cellwidth);
$smarty->assign('width',$width);
$smarty->assign('totalDisplay',$TotalDisplay);

$smarty->assign('menuData',$menuData);

$smarty->assign('color1',$color1);
$smarty->assign('color2',$color2);
$smarty->assign('weightedStd',$weightedStd);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('toggleSubjectLevel.tpl');

?>
