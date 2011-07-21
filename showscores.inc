<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once 'WeightedList.php';

$listID = $_GET['p1'];
$listinfo = getListInfo($listID);
$listName = $listinfo['listname'];

$grades = getGradesList($listID); 

$subjects = getCoreSubjects();
$electives = getElectiveSubjects();
$list = getStudentList($listID);
$stdcount = count($list);

$att_am = $listinfo['am'] == 1;
$att_pm = $listinfo['pm'] == 1;
$tabs = getListTabs($listID);

$student = getStudentScores ($listID);

$weightedList = new WeightedList($list, $student, $subjects, $grades);
$weightedStd = $weightedList->getList();

$title = "Show Scores for List";

if (Privilege(A6) == 'district')
	$showEdit = 1;
else
	$showEdit = 0;

for ($y = 0; $y < count($list); $y++) {
	$id = $list[$y]['studentid'];
	foreach ($subjects as $s) {
		$sub = $s['id'];
		$lvl = $student[$id][$sub];
		$sublvls = getSubjectStandards ($sub, $lvl);
		foreach ($sublvls as $sublvl) {
			$std = $sublvl['std'];
			$stdw = strlen($std) == 1 ? "0" . $std : $std;
			$key = $sub . "_" . $lvl . "_" . $std;
			$value = $grades[$id][$sub][$lvl][$std];
			$wlist2[$key]['std'] = $std;
			$wlist2[$key]['subject'] = $sub;
			$wlist2[$key]['level'] = $lvl;
			$wlist2[$key]['link'] = $sublvl['link'];
			$wlist2[$key]['shortname'] = $sublvl['shortname'];
			$wlist2[$key]['count']++;
			$wlist2[$key]['sum'] += getToggleValue($value);
			$wlist2[$key]['comp'] = $wlist2[$key]['sum']/$stdcount;
			$wlist2[$key]['sort'] = $sub . "_" . $lvl . "_" . $stdw;
		}
	}
}

$wlist = array_unique2($wlist2);
$wlist = array_sort($wlist, 'comp');
$wnum = min(30, count($wlist));
$buckets = 4;
$start = 0;
$end = $wnum-1+$start;
$t = $wlist[$start]['comp'];
$b = $wlist[$end]['comp'];
$spread = ($t - $b)/$buckets;
$wlist = array_slice($wlist, 0, $wnum);
$wlist = array_sort($wlist, 'sort');

for ($i = $start; $i <= $end; $i++) {
	$val = $wlist[$i]['comp'];
	$sid = $wlist[$i]['subject'] . $wlist[$i]['level'] . "." . $wlist[$i]['std'];
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
$smarty->assign('att_am',$att_am);
$smarty->assign('att_pm',$att_pm);
$smarty->assign('listID',$listID);
$smarty->assign('listName',$listName);
$smarty->assign('stdcount',$stdcount);
$smarty->assign('oldtabid',0);
$smarty->assign('tabs',$tabs);
$smarty->assign('weightedStd',$weightedStd);
$smarty->assign('imageURL',$imageURL);

//set flag to indicate that smarty template exists for this page
$isSmarty=true;
include ("template.inc");

$smarty->display('showscores.tpl');

?>
