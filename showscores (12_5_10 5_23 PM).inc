<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$listID = $_GET['p1'];
$listinfo = getListInfo($listID);
$listName = $listinfo['listname'];
$att_am = $listinfo['am'] == 1 ?
			"<a href=index.php?cmd=AttendanceList&listid=$listID&period=0>AM</a>" :
			"";
$att_pm = $listinfo['pm'] == 1 ?
			"<a href=index.php?cmd=AttendanceList&listid=$listID&period=1>PM</a>" :
			"";
$grades = getGradesList($listID);
$stdCount = getGradesListTotal($listID);
debugPrint ("StdCount: $stdCount");

$subject = getSubjects ();
$list = getStudentList($listID);
$student = getStudentScores ($listID);
$stdcount = count($list);
$toggleColor = 2;

$sep = ($att_pm <> "" and $att_am <> "") ? " | " : "";
$attendance = ($att_pm <> "" or $att_am <> "") ?
    "Take attendance: $att_am$sep$att_pm" :
    "";

$body_pre = "
<div align=\"left\">
											<br>
											<font size=\"4\">Overview - All Content Areas - $listName Group<br>
												<br>
											</font><font size=\"2\">Here is a &quot;weighted list&quot; of the common relative weaknesses of this group of students from <i>all of their content areas</i>. The more students is this group that show any standard as having no toggled status </font><font size=\"2\">, Emerging status, or Developing status, the larger the name of the standard is in the list. This means that the largest short standard names are the most common relative weaknesses of the group.</font>

											<p><font size=\"4\" color=\"#cc0000\">Weighted List of Standards Needed</font><font size=\"2\">: </font></p>";

$body_post = "<div align=\"left\">
													<ul>
														<li type=\"circle\"><font size=\"2\">Roll over each content area code to read it!<br>
															</font>
														<li type=\"circle\"><font size=\"2\">Click on the Level Number in any Content Area to view the <i>students in this group at that level</i>.<br>
															</font>

														<li type=\"circle\"><font size=\"2\" color=\"black\">Click on the name of the student to see<i> his or her standards progress in all content areas</i>. </font><font size=\"2\"><br>
															</font>
														<li type=\"circle\"><font size=\"2\">Click on any Content Area to <i>re-sort the view by Content Area &amp; Level Number</i>.<br>
															</font>

													</ul>
												</div>
										</div>
									";

$body_post .= "<b>Student count - $stdcount</b><br>";

$body_post .= "<a href=index.php?cmd=editlist&p1=" . $listID . ">Edit Group</a>$attendance<br>"; 

$body_post .= "<font size=4><table width=\"100%\" border= 1 class=big>";

$body_post .= "<tr><th colspan=11 bgcolor=#ccccff><b>$listName Group Profile</b></th></tr>";

$body_header .= "<tr><th>Name</th>";

for ($i = 0; $i < count($subject); $i++) {
	if($subject[$i]['core'] == 'x') {
	   $subname = $subject[$i]['name'];
	   $subid = $subject[$i]['id'];
	   $body_header .= "<th onMouseOver=\"return escape('$subname')\">$subid</th>";
	}
}
 $body_header .= "<td>EL</td></tr>";

for ($y = 0; $y < count($list); $y++) {
    if ($toggleColor == 1) { $toggleColor = 2; $color = $color2; }
    else { $toggleColor = 1; $color = $color1; }
   $id = $list[$y]['studentid'];
   $body_post1 .= "<tr bgcolor=$color><td nowrap><a href=index.php?cmd=toggleStudent&p1=$id>" . $list[$y]['fname'] . " " . $list[$y]['lname'] . "</a> </td>";
   for ($i = 0; $i < count($subject); $i++) {
	if($subject[$i]['core'] == 'x') {
   
        $sub = $subject[$i]['id'];
        $lvl = $student[$id][$sub];
        $link = "index.php?cmd=toggle&p1=$listID&p2=$sub&p3=$lvl";
        $body_post1 .= "<td><a href=$link>" . $student[$id][$subject[$i]['id']] . "</a></td>";
        
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
            debugPrint ("Key: $key Value: $value Comp: " . $wlist2[$key]['comp'] . "<br>");
        }
     } else if ($student[$id][$subject[$i]['id']] != '') {
        $sub = $subject[$i]['id'];
        $lvl = $student[$id][$sub];
        $link = "index.php?cmd=toggle&p1=$listID&p2=$sub&p3=$lvl";
        $student[$id]['elective'] .= " <a href=$link>" . $sub . "." . $student[$id][$subject[$i]['id']] . "</a> ";   
        $student[$id]['el']++;
        $maxel = max($student[$id]['el'], $maxel);
     }

   }
   $body_post1 .= "<td> " . $student[$id]['elective'] . "</td></tr><tr>";
}

$body_post .= "$body_header $body_post1 </table></font>";

$title = "Show Scores for List";

/*************************
// Weighted Standards for List of users
$wlist2 = getListWeight ($listID);
$wnum = 20;
$buckets = 4;
$t = $wlist2[0]['comp'];
$b = $wlist2[$wnum-1]['comp'];
$spread = ($t - $b)/$buckets;
$wlist = array_slice($wlist2, 0, $wnum);
$wlist = array_sort($wlist, 'subject');
$weight = "<div class=\"notetarget\">";
for ($i = 0; $i < $wnum; $i++) {
   $val = $wlist[$i]['comp'];
   if($spread==0) {
     $tmpnum = 0;
    } else { $tmpnum = floor(($val - $b)/$spread);}
   $loc = $buckets - min($buckets-1, $tmpnum);
   $weight .= "<a href=\"" . $wlist[$i]['link'] . "\" target=_blank><span class=t$loc>" . $wlist[$i]['subject'] . "_" . $wlist[$i]['shortname'] . "</span></a> :: ";
}
$weight .= "</div>";
**************/

debugPrint ("<br>Wlist2: " . print_r ($wlist2, true) . "<br><br>");
//$wlist = getListSubjectLevelWeight ($listID, $sub, $lvl);
$wlist = array_unique2($wlist2);
debugPrint ("<br>***P1: " . print_r ($wlist, true) . "<br><br>");
$wlist = array_sort($wlist, 'comp');
debugPrint ("***P2: " . print_r ($wlist, true) . "<br><br>");
debugPrint ("COUNT: " . count($wlist));
$wnum = min(30, count($wlist));
$buckets = 4;
$start = 0;
$end = $wnum-1+$start;
debugPrint ("***START : $start END: $end<br><br>");
$t = $wlist[$start]['comp'];
$b = $wlist[$end]['comp'];
$spread = ($t - $b)/$buckets;
$wlist = array_slice($wlist, 0, $wnum);
$wlist = array_sort($wlist, 'sort');

$weightedStd = "<div class=\"notetarget\">";
for ($i = $start; $i <= $end; $i++) {
   $val = $wlist[$i]['comp'];
  $sid = $wlist[$i]['subject'] . $wlist[$i]['level'] . "." . $wlist[$i]['std'];
   if($spread == 0) { $tmpnum = 0; } 
   else { $tmpnum = floor(($val - $b)/$spread); }
   $loc = $buckets - min($buckets-1, $tmpnum);
   $weightedStd .= "<a href=\"" . $wlist[$i]['link'] . "\" target=_blank><span class=t$loc>" . $sid .  "-" . $wlist[$i]['shortname'] . "</span></a> :: ";
}
$weightedStd .= "</div>";


$body = $body_pre . $weightedStd . $body_post;
// $body = "This is the body";

include ("template.inc");

?>
