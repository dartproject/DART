<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
include_once("lib/functions_gs.inc");
include_once 'WeightedList.php';

$listID = $_GET['p1'];    // list id
$sub = $_GET['p2'];       // subject number
$lvl = $_GET['p3'];      // level number
$width = 9;
$cellwidth = 60;

$standards = getSubjectStandards ($sub, $lvl);
$overall = getSubjectOverall ($sub, $lvl);
$list = getStudentToggleList($listID, $sub, $lvl);
$student = getStudentStdScores ($listID, $sub, $lvl);
$stdcount = count($list);
$subInfo = getSubjectInfo ($sub);
$total = $stdcount * count($standards);

$subName =  $subInfo[0]['name'];
$gradlvl = $subInfo[0]['gradLevel']; /* @todo: is this variable used? */
$listName = getListName($listID);

$A2Priv = Privilege(A2);
$A3Priv = Privilege(A3);
$TotalDisplay = 'view';
$menuData = array("" => "Choose One","#top_anchor" => "Top of Page");

$indicators = getIndicatorInfo();

$data = array();
for ($y = 0; $y < count($list); $y++) {
	$studentID = $list[$y]['studentid'];
	$fname = $list[$y]['fname'];
	$lname = $list[$y]['lname'];
	$site = $list[$y]['site'];
	$grade = $list[$y]['grade'];
	$grdtype = $list[$y]['gradetype'];
	$grdtypename = $list[$y]['gradetypename'];
	$ch_name = $list[$y]['change_username'];
	$ch_time = date($dateSettings, $list[$y]['change_timestamp']);
	$siteEqual = $currentMySite == $site;
	$idEqual = isset($currentAffiliatedID) && $currentAffiliatedID == $studentID; /* is $currentAffiliatedID always null? */
	$Display =  checkStudent($idEqual, $siteEqual, $A2Priv, $A3Priv);
	$TotalDisplay = (($TotalDisplay == 'edit') or ($Display == 'edit')) ? 'edit':'view';
	$gradeSymbols = getGradeSymbols($grdtype);

	$data[$studentID]['anchor'] = $fname ."_" . $lname;
	$data[$studentID]['progress'] = $list[$y]['progress'];
	$data[$studentID]['text'] = "$lname, $fname ($grade:$site - $grdtypename)";
	$data[$studentID]['change'] = "$ch_name ($ch_time)"; /* pullDownMenu */
	$data[$studentID]['display'] = $Display;

	$menuData["#".$fname."_".$lname] = "$lname, $fname";

	$data[$studentID]['std'] = array();
	/* Standards */
	for ($i = 0; $i < count($standards); $i++) {
		$std = $standards[$i]['std'];
		$value = $student[$studentID][$std];

		$des = htmlentities($standards[$i]['description']);
		$des = str_replace("'", "\'", $des );
		$standards[$i]['description'] = $des;

		$type = isset($value)? "u" : "i";

		$data[$studentID]['std'][$std]['name'] =
				"gr".$type."_".$studentID."_".$sub."_".$lvl."_".$standards[$i]['std'];
		$data[$studentID]['std'][$std]['value'] = $value;
		$data[$studentID]['std'][$std]['options'] = $gradeSymbols;
		$data[$studentID]['std'][$std]['selected'] = getEqGradeValue($grdtype, $value);

		$wlist[$std]['std'] = $std;
		$wlist[$std]['link'] = $standards[$i]['link'];
		$wlist[$std]['shortname'] = $standards[$i]['shortname'];
		$wlist[$std]['count']++;
		$wlist[$std]['sum'] += getToggleValue($value);
		$wlist[$std]['comp'] = $wlist[$std]['sum']/$stdcount;
	}
	/* Overall */
	for ($i = 0; $i < count($overall); $i++) {
		$std = $overall[$i]['std'];
		$des = str_replace("'", "\'", $overall[$i]['description']);
		$overall[$i]['description'] = $des;
		$value = $student[$studentID][$std];

		$type = isset($value)? "u" : "i";

		$data[$studentID]['over'][$std]['name'] =
			"gr".$type."_".$studentID."_".$sub."_".$lvl."_".$std;

		$data[$studentID]['over'][$std]['value'] = $student[$studentID][$std];
		$data[$studentID]['over'][$std]['options'] = $gradeSymbols;
		$data[$studentID]['over'][$std]['selected'] = getEqGradeValue($grdtype, $value);
	}
	/* Indicators */
	foreach($indicators as $key => $val) {
    	$value = $student[$studentID][$key];
		$type = isset($value)? "u" : "i";
		$data[$studentID]['ind'][$key]["name"] = "gr".$type."_".$studentID."_".$sub."_".$lvl."_".$key;
		$data[$studentID]['ind'][$key]["value"] = $value;
	}

	$value = $student[$studentID]['comment'];
	$type = isset($value)? "u" : "i";
	$data[$studentID]['comment_id'] = "gr".$type."_".$studentID."_".$sub."_".$lvl."_comment";
	$data[$studentID]['comment'] = $value;
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
$smarty->assign('list',$list);
$smarty->assign('data',$data);
$smarty->assign('standards',$standards);
$smarty->assign('overall',$overall);
$smarty->assign('totalStd',count($standards));
$smarty->assign('totalOver',count($overall));

$smarty->assign('cellwidth',$cellwidth);
$smarty->assign('width',$width);
$smarty->assign('totalDisplay',$TotalDisplay);

$smarty->assign('menuData',$menuData);
$smarty->assign('indicators',$indicators);
$smarty->assign('n_ind',count($indicators));

$smarty->assign('color1',$color1);
$smarty->assign('color2',$color2);
$smarty->assign('weightedStd',$weightedStd);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('toggleSubjectLevel.tpl');

?>
