<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
 
$js = "function changeValue(name,newval) {
        obj = document.getElementsByName(\"ch_\" + name)[0];
        obj.value = newval;
 }
  
  function handleSelection(value) {
     if (value == \"#save_changes\") {
        toggle.loc.value = location.href;
        toggle.submit();
     } else {
     window.location=value;
     }
 }";

echo $CurrentYear;

$cellwidth = 60;
$studentID = $_GET['p1'];
$studentInfo = getStudentInfo($studentID);
$site = $studentInfo['site'];

$siteEqual = $currentMySite == $site;
$idEqual = $currentAffiliatedID == $studentID;
//$idEqual = 0;
$A2Priv = Privilege(A2);
$A3Priv = Privilege(A3);

$Display = checkStudent($idEqual, $siteEqual, $A2Priv, $A3Priv);

if ($Display == 'no') {
   $type = "denied toggleStudent";
   $notes = "page=toggleStudent;site=$site;studentID=$studentID;currentSite=$currentMySite;idEqual=$idEqual;siteEqual=$siteEqual;A2Priv=$A2Priv;A3Priv=$A3Priv";
   echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=noPrivilege&type=$type&notes=$notes\"> ");
}

debugPrint ("DISPLAY: $Display [ $idEqual, $siteEqual, $A2Priv, $A3Priv]<br>");
$studentChanges = getStudentChanges($studentID);

$studentName = $studentInfo['fname'] . " " . $studentInfo['lname'];
$toggleColor = 2;

$body_pre .= "<font class=big>Individual View - All Content Areas - $studentName</font><br><br>

<form name=reports method=get action=''>
  <select  onChange='window.location=this.value'>
      <option value=''>None</option>";


$body_pre .= viewReport($idEqual, $siteEqual, Privilege(A4)) ? "<option value='index.php?cmd=studentInfo&id=$studentID'>Student Information</option>" : ""; 

$body_pre .= viewReport($idEqual, $siteEqual, Privilege(A4)) ? "<option value='index.php?cmd=StudentEdit&id=$studentID'>Edit Student Information</option>" : ""; 
			
$body_pre .=	viewReport($idEqual, $siteEqual, Privilege(A18)) ? "<option value='index.php?cmd=sreport&id=$studentID'>Report Cover - no QPI</option>
    <option value='index.php?cmd=sreport&id=$studentID&qpi=on'>Report Cover - with QPI</option>" : ""; 
			
$body_pre .=viewReport($idEqual, $siteEqual, Privilege(A20)) ? "<option value='index.php?cmd=progressReport&id=$studentID'>Progress Report</option>" : ""; 

$body_pre .=viewReport($idEqual, $siteEqual, Privilege(A22)) ? "<option value='index.php?cmd=pacingReport&id=$studentID'>Pacing Report</option>" : ""; 

$body_pre .="<option value='index.php?cmd=AttendanceCalendar&student=$studentID&year=$CurrentYear'>Attendance</option>"; 

$body_pre .=viewReport($idEqual, $siteEqual, Privilege(A21)) ? "<option value='index.php?cmd=disciplineList&studentid=$studentID&year=$CurrentYear'>Discipline List</option>" : ""; 
/*
$status = $studentInfo['status'];
$body_pre .=viewReport($idEqual, $siteEqual, Privilege(A23)) ? 

($active == 'Active' ? 
"<option value='index.php?cmd=StudentExit&id=$studentID'>Deactivate</option>" :
"<option value='index.php?cmd=StudentEnter&id=$studentID'>Activate</option>" ) : "";
*/

$body_pre .=viewReport($idEqual, $siteEqual, Privilege(A23)) ? "<option value='index.php?cmd=MovementView&studentid=$studentID'>View Student Movement</option>" : ""; 
			
$body_pre .= "
  </select> Go To Report
  </form>

          <br>";

$body_pre .= "<ul>
  						<li type='circle'><font size='2'><b>Note:</b>  Roll over each standard number to read its short name!</font>
  					</ul>
  					<p><font size=\"2\">The screen below shows the current status of these students in this content area.  Toggle the appropriate indicator, and enter comments as needed. Make sure you &quot;Save Changes&quot; for the entire page from either the pull down menu, or the button at the bottom of the page.  The time and date stamp of your entry for this student will be added.</font></p>
  						<br><font size=\"2\">Here is a &quot;weighted list&quot; of the common relative weaknesses of this student from <i>all of their content areas</i>. The student standard having no toggled status </font><font size=\"2\">, Emerging status, or Developing status, the larger the name of the standard is in the list respectively. This means that the largest short standard names are the most common relative weaknesses of the student.</font>

											<p><font size=\"4\" color=\"#cc0000\">Weighted List of Standards Needed</font><font size=\"2\">: </font></p>";

$body_post .="<div align=\"left\">
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
										


$body_post .= "<form name=toggle method=post action=index.php?cmd=saveStudentToggle>
          <input type=hidden name=studentid value=$studentID>
          <input type=hidden name=loc>";

$subjects = getStudentLevels($studentID);

$pulldownMenu = "<select  onChange='handleSelection(this.value)'>
													<option selected value=''>Choose One</option>
													<option value='#top_anchor'>Top of Page</option>";
													
foreach ($subjects as $rec) {
    $anchor = $rec['subject'];
    $pulldownMenu .= "<option value='#$anchor'>$anchor</option>
    ";
}

if($Display == 'edit') {				
    $pulldownMenu .= "<option value='#save_changes'>Save All Changes</option>";
}
    $pulldownMenu .= "</select>";		

$z = 0;
foreach ($subjects as $rec) {

    $sub = $rec['subject']; //$_GET['p2'];       // subject number
    $lvl = $rec['level']; //$_GET['p3'];      // level number
    $progress = $rec['progress']; //$_GET['p3'];      // level number
    
    $standards = getSubjectStandards ($sub, $lvl);
    $overall = getSubjectOverall ($sub, $lvl);
    $scores = getSutdentSubjectStandards($studentID, $sub, $lvl);
    $subInfo = getSubjectInfo ($sub);
    
    $subName =  $subInfo[0]['name'];
    $subTableName = $subInfo[0]['tablename'];
    $gradlvl = $subInfo[0]['gradLevel'];
    $ch_name = $studentChanges[$sub]['ch_name'];
    $ch_time = date($dateSettings, $studentChanges[$sub]['ch_time']);
    
    
    $body_post .= "<font size=2><b>$subName<a href=index.php?cmd=updateSingleLevelScore&id=$studentID&subject=$sub&level=$lvl onMouseOver=\"return escape('Update score for saved values. NOTE: THIS WILL RESET ANY TOGGLE/COMMENT CHANGES NOT SAVED.')\">.</a> - <font color=#cc0000>$progress</font></b></font><br><a name=\"$sub\"></a>$pulldownMenu<br>";
    $body_post .= "<b>Student:</b> $studentName <b>Last Change:</b> $ch_name ($ch_time) - <a href=index.php?cmd=history&student=$studentID&subject=$sub&lvl=$lvl>History</a>";
    $body_post .= "<table border=1>";
    $line0 = "<tr rowspan=2 bgcolor=$color1><th rowspan=2>$sub ($lvl)</th>";
    $line1 = "";
    $line2 = "";
    for ($i = 0; $i < count($standards); $i++) {
         $std = $standards[$i]['std'];
         $link = $standards[$i]['link'];
         $value= getStdValue($std, $scores);
         $num = getToggleValue($value);
         $shortname = $standards[$i]['shortname'];
         $des = htmlentities($standards[$i]['description']);
         $wlist2[$z]['subject'] = $sub;
         $wlist2[$z]['level'] = $lvl;
         $wlist2[$z]['std'] = $std;
         $wlist2[$z]['num'] = $num;
         $wlist2[$z]['link'] = $link;
         $stdw = strlen($std) == 1 ? "0" . $std : $std;
         $wlist2[$z]['sort'] = $sub . "_" . $lvl . "_" . $stdw;
         $wlist2[$z]['shortname'] = $shortname;
         $z++;
         if (!isset($value)) { $type = "i"; } else { $type = "u"; }
         // onmouseover=\"return escape('$des')\"
         // title=\"". $des ."\"
        $des = str_replace("'", "\'", $des );
        $line1 .= "<th width=$cellwidth onMouseOver=\"return escape('$des')\">&nbsp;&nbsp;" . $std . "&nbsp;&nbsp;</th>";
         $name = "gr" . $type . "_" . $studentID . "_" . $sub . "_" . $lvl . "_" .$standards[$i]['std'];
         if($Display == 'edit') {
           $line2 .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
           $line2 .= "<input type=hidden name=ch_" . $name . " value=empty>\n";
           $line2 .= "<select bgcolor=$color name=" . $name . " onChange='changeValue(\"$name\", this.value)'' >
                     <option value=\"\"" . selected("", $value) . "></option>
                     <option value=\"EMG\"" . selected("EMG", $value) . ">EMG</option>
                     <option value=\"DEV\"" . selected("DEV", $value) . ">DEV</option>
                     <option value=\"PRO\"" . selected("PRO", $value) . ">PRO</option>
                     <option value=\"ADV\"" . selected("ADV", $value) . ">ADV</option>
                     </select>&nbsp;
                     </td>\n";
         } else {
           $line2 .= "<td align=center>&nbsp;$value&nbsp;</td>";
         }
         if(fmod($i+1, $width) == 0) {
            $body_post .= "$line0 $line1 </tr><tr> $line2 </tr>";
            $line1 = "";
            $line2 = "";
         }
    }
    if(fmod($i, $width) <> 0) {
       $body_post .= "$line0 $line1 </tr><tr> $line2 </tr>";

    }
    $body_post .= "</table>";
/***** Overall Scores *****/
    $body_post .= "<table border= 1 bgcolor=$color1C>";
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
  
          $name = "gr" . $type . "_" . $studentID . "_" . $sub . "_" . $lvl . "_" .$std;
          if($Display=='edit') {
              $line4 .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
              $line4 .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
              $line4 .= "<select title = \"test_$studentID_over_$i\" bgcolor=$color name=" . $name . " onChange='changeValue(\"$name\",this.value )' >
                        <option value=\"\"" . selected("", $value) . "></option>
                        <option value=\"EMG\"" . selected("EMG", $value) . ">EMG</option>
                        <option value=\"DEV\"" . selected("DEV", $value) . ">DEV</option>
                        <option value=\"PRO\"" . selected("PRO", $value) . ">PRO</option>
                        <option value=\"ADV\"" . selected("ADV", $value) . ">ADV</option>
                        </select>&nbsp;
                        </td>\n";
                if(fmod($i+1, $width) == 0) {
                  $body_post .= "$line0 $line3 </tr><tr> $line4 </tr>";
                  $line3 = "";
                  $line4 = "";
                }
            } else {
           $line4 .= "<td align=center>&nbsp;$value&nbsp;</td>";
         }

    }

    $value = getStdValue('qpi', $scores);;
    if (!isset($value)) { $type = "i"; } else { $type = "u"; }
    $line3 .= "<th width=$cellwidth onMouseOver=\"return escape('Quarterly Performance Indicator')\">QPI</th>";

    $name = "gr" . $type . "_" . $studentID . "_" . $sub . "_" . $lvl . "_qpi";
    if($Display == 'edit') {
        $line4 .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
        $line4 .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
        $line4 .= "<select title = \"test_$studentID_qpi_$i\" bgcolor=$color name=" . $name . " onclick='changeValue(\"$name\",this.value )' >
                  <option value=\"\"" . selected("", $value) . "></option>
                  <option value=\"Disengaged\"" . selected("Disengaged", $value) . ">Disengaged</option>
                  <option value=\"Deficient\"" . selected("Deficient", $value) . ">Deficient</option>
                  <option value=\"Acceptable\"" . selected("Acceptable", $value) . ">Acceptable</option>
                  <option value=\"Exemplary\"" . selected("Exemplary", $value) . ">Exemplary</option>
                  </select>&nbsp;
                  </td>\n";
     } else {
           $line4 .= "<td align=center>&nbsp;$value&nbsp;</td>";
     }

//    if(fmod($i, $width) <> 0) {
       $body_post .= "$line0 $line3 </tr><tr> $line4 </tr>";
//    }
    $body_post .= "</table>";

/***** COMMENTS *****/    
   $value = getStdValue('comment', $scores);;
   if (!isset($value)) { $type = "i"; } else { $type = "u"; }
   $name = "gr" . $type . "_" . $studentID . "_" . $sub . "_" . $lvl . "_comment";
   $body_post .= "<input type=hidden name=old_" . $name . " value=" . $value . ">\n";
   $body_post .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
   $body_post .= "<font size=\"2\"><b>Teacher Comments:</b></font><br>";
   $body_post .= $Display == 'edit' ? "<textarea name=\"comment_$studentID_$i\" rows=\"8\" cols=\"80\" wrap=\"physical\" onChange='changeValue(\"$name\",this.value )'  >$value</textarea><br>" :
              "&nbsp;$value&nbsp;";
		$body_post .= "</font><br><br>";

}
if($Display == 'edit') {
$body_post .= "<input type=reset value=reset>
<input type=submit value=save>
</form><br>";
}

$body_post .= "* Placing mouse over standard number will display standards descriptions.";

$title = "Show Scores for Student";


// Weighted Standards for Student of users
//$wlist2 = getIndWeight ($studentID);
$wlist2 = array_sort($wlist2, 'num');
$wnum = min(30, count($wlist2));
$buckets = 5;
$t = $wlist2[0]['num'];
$b = $wlist2[$wnum-1]['num'];
$spread = ($t - $b)/$buckets;
//$wlist = $wlist2;
$wlist = array_slice($wlist2, 0, $wnum);
$wlist = array_sort($wlist, 'sort');
$weight = "<div class=\"notetarget\">";
for ($i = 0; $i < $wnum; $i++) {
   $val = $wlist[$i]['num'];
   $sid = $wlist[$i]['subject'] . $wlist[$i]['level'] . "." . $wlist[$i]['std'];
   if($spread==0) {
     $tmpnum = 0;
    } else { $tmpnum = floor(($val - $b)/$spread);}
   $loc = $buckets - min($buckets-1, $tmpnum);
   $weight .= "<a href=\"" . $wlist[$i]['link'] . "\" target=_blank><span class=t$loc>" . $sid . "-" . $wlist[$i]['shortname'] . "</span></a> :: ";
}
$weight .= "</div>";

$body .= $body_pre . $weight . $body_post;

include ("template.inc");

?>
