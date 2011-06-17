<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
 debugPrint("Start");
 
$js = "function handleSelection(value) {
     if (value == \"#save_changes\") {
        toggle.loc.value = location.href;
        toggle.submit();
     } else {
     window.location=value;
     }
 }";
debugPrint("Here");
$cellwidth = 60;
$commentWidth = $cellwidth * ($width + 2);
$studentInfo = getStudentInfo($currentStudentID);
$site = $studentInfo['site'];


$studentChanges = getStudentChanges($currentStudentID);

$studentName = $studentInfo['fname'] . " " . $studentInfo['lname'];
$toggleColor = 2;

// Weighted Standards for Student of users
$wlist2 = getIndWeight ($currentStudentID);
$wnum = 30;
$buckets = 4;
$t = $wlist2[0]['num'];
$b = $wlist2[$wnum-1]['num'];
$spread = ($t - $b)/$buckets;
//$wlist = $wlist2;
$wlist = array_slice($wlist2, 0, $wnum);
$wlist = array_sort($wlist, 'subject');
$weight = "<div class=\"notetarget\">";
for ($i = 0; $i < $wnum; $i++) {
   $val = $wlist[$i]['num'];
   $sid = $wlist[$i]['subject'] . $wlist[$i]['level'] . "." . $wlist[$i]['std'];
   if($spread==0) {
     $tmpnum = 0;
    } else { $tmpnum = floor(($val - $b)/$spread);}
   $loc = $buckets - min($buckets-1, $tmpnum);
   $weight .= "<a href=\"" . $wlist[$i]['link'] . "\" target=_blank><span class=t$loc>" . $sid . "-" . $wlist[$i]['subject'] . "_" . $wlist[$i]['shortname'] . "</span></a> :: ";
}
$weight .= "</div>";


$header = "<ul>
  						<li type='circle'><font size='2'><b>Note:</b>  Roll over each standard number to read its short name!</font>
  					</ul>
  					<p><font size=\"2\">The screen below shows the current status of these students in this content area.  Toggle the appropriate indicator, and enter comments as needed. Make sure you &quot;Save Changes&quot; for the entire page from either the pull down menu, or the button at the bottom of the page.  The time and date stamp of your entry for this student will be added.</font></p>
  						<br><font size=\"2\">Here is a &quot;weighted list&quot; of the common relative weaknesses of this student from <i>all of their content areas</i>. The student standard having no toggled status </font><font size=\"2\">, Emerging status, or Developing status, the larger the name of the standard is in the list respectively. This means that the largest short standard names are the most common relative weaknesses of the student.</font>

											<p><font size=\"4\" color=\"#cc0000\">Weighted List of Standards Needed</font><font size=\"2\">: </font></p>
$weight

												<div align=\"left\">
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
												</div>";
										
$bodyReports .= "<form name=reports method=get action=''>
  <select  onChange='window.location=this.value'>
      <option value=''>None</option>
			<option value='index.php?cmd=sreport&id=$currentStudentID'>Report Cover - no QPI</option> 
      <option value='index.php?cmd=sreport&id=$currentStudentID&qpi=on'>Report Cover - with QPI</option> 
			<option value='index.php?cmd=progressReport&id=$currentStudentID'>Progress Report</option>
      <option value='index.php?cmd=pacingReport&id=$currentStudentID'>Pacing Report</option>
  </select> Go To Report
  </form>";

$body .= "<font class=big>Individual View - All Content Areas - $studentName</font><br><br>
$bodyReports<br>$header";

$subjects = getStudentLevels($currentStudentID);

$pulldownMenu = "<select  onChange='handleSelection(this.value)'>
													<option selected value=''>Choose One</option>
													<option value='#top_anchor'>Top of Page</option>";
													
foreach ($subjects as $rec) {
    $anchor = $rec['subject'];
    $pulldownMenu .= "<option value='#$anchor'>$anchor</option>";
}

    $pulldownMenu .= "</select>";		


foreach ($subjects as $rec) {

    $sub = $rec['subject'];        // subject number
    $lvl = $rec['level'];          // level number
    $progress = $rec['progress'];  // level number
    
    $standards = getSubjectStandards ($sub, $lvl);
    $overall = getSubjectOverall ($sub, $lvl);
    $scores = getSutdentSubjectStandards($currentStudentID, $sub, $lvl);
    $subInfo = getSubjectInfo ($sub);
    $subName =  $subInfo[0]['name'];
    $subTableName = $subInfo[0]['tablename'];
    $gradlvl = $subInfo[0]['gradLevel'];
    $ch_name = $studentChanges[$sub]['ch_name'];
    $ch_time = date($dateSettings, $studentChanges[$sub]['ch_time']);
       
    $body .= "<font size=2><b>$subName - <font color=#cc0000>$progress</font></b></font><br><a name=\"$sub\"></a>$pulldownMenu<br>";
    $body .= "<b>Student:</b> $studentName <b>Last Change:</b> $ch_name ($ch_time)";
    $body .= "<table border=1>";
    $line0 = "<tr rowspan=2 bgcolor=$color1><th rowspan=2>$sub ($lvl)</th>";
    $line1 = "";
    $line2 = "";
    for ($i = 0; $i < count($standards); $i++) {
         $std = $standards[$i]['std'];
         $value= getStdValue($std, $scores);
         $des = htmlentities($standards[$i]['description']);
         if (!isset($value)) { $type = "i"; } else { $type = "u"; }
        $des = str_replace("'", "\'", $des );
        $line1 .= "<th width=$cellwidth onMouseOver=\"return escape('$des')\">&nbsp;&nbsp;" . $std . "&nbsp;&nbsp;</th>";
        $name = "gr" . $type . "_" . $currentStudentID . "_" . $sub . "_" . $lvl . "_" .$standards[$i]['std'];
        $line2 .= "<td align=center>&nbsp;$value&nbsp;</td>";
        if(fmod($i+1, $width) == 0) {
            $body .= "$line0 $line1 </tr><tr> $line2 </tr>";
            $line1 = "";
            $line2 = "";
         }
    }
    if(fmod($i, $width) <> 0) {
       $body .= "$line0 $line1 </tr><tr> $line2 </tr>";
    }
    $body .= "</table>";

/***** Overall Scores *****/
    $body .= "<table border= 1>";
    $line3 = "";
    $line4 = "";
    for ($i = 0; $i < count($overall); $i++) {
  // name of cell = _id_subject_lvl
        $std = $overall[$i]['std'];
        $des = $overall[$i]['description'];
        $des = str_replace("'", "\'", $des );
        $value = getStdValue($std, $scores);
        if (!isset($value)) { $type = "i"; } else { $type = "u"; }
          $line3 .= "<th width=$cellwidth onMouseOver=\"return escape('$des')\">" . $std . "</th>";
  
          $name = "gr" . $type . "_" . $currentStudentID . "_" . $sub . "_" . $lvl . "_" .$std;
          $line4 .= "<td align=center>&nbsp;$value&nbsp;</td>";
    }

    $value = getStdValue('qpi', $scores);
    if (!isset($value)) { $type = "i"; } else { $type = "u"; }
    $line3 .= "<th width=$cellwidth onMouseOver=\"return escape('Quarterly Performance Indicator')\">QPI</th>";

    $name = "gr" . $type . "_" . $currentStudentID . "_" . $sub . "_" . $lvl . "_qpi";
    $line4 .= "<td align=center>&nbsp;$value&nbsp;</td>";

    $body .= "$line0 $line3 </tr><tr> $line4 </tr>";
    $body .= "</table>";

    
   $value = getStdValue('comment', $scores);;
   if (!isset($value)) { $type = "i"; } else { $type = "u"; }
   $name = "gr" . $type . "_" . $currentStudentID . "_" . $sub . "_" . $lvl . "_comment";
   $body .= "<input type=hidden name=old_" . $name . " value=" . $value . ">\n";
   $body .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
   $body .= "<font size=\"2\" ><b>Teacher Comments:</b></font><br>";
   $body .= "<table width=$commentWidth border=1><tr><td>&nbsp;$value&nbsp;</td></tr></table>";
	 $body .= "<br><br>";

}

$body .= "* Placing mouse over standard number will display standards descriptions.";

$title = "Show Scores for Student";


include ("template.inc");

?>
