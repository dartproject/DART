<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$listID = $_GET['p1'];    // list id
$sub = $_GET['p2'];       // subject number
$lvl = $_GET['p3'];      // level number
$width = 9;
$cellwidth = 60;

$subject = getSubjectStandards ($sub, $lvl);
$overall = getSubjectOverall ($sub, $lvl);
$list = getSutdentToggleList($listID, $sub, $lvl);
$student = getStudentStdScores ($listID, $sub, $lvl);
$stdcount = count($list);
$subInfo = getSubjectInfo ($sub);
$total = $stdcount * count($subject);

$subName =  $subInfo[0]['name'];
$gradlvl = $subInfo[0]['gradLevel'];
$listName = getListName($listID);

// print_r ($subInfo);
debugPrint("<br>ID: " . $subInfo[0]['id']);

$js = "function changeValue(name,newval) {
//        alert(newval);
        obj = document.getElementsByName(\"ch_\" + name)[0];
        obj.value = newval;
//        toggle.document.getElementByID(\"ch_\" + name);
//        val =toggle.document.getElementsByName(\"ch_\" + name)[0].value;
//        val = obj.value;
//        alert(val);
// toggle image
//        document.getElementById(name + \"_img\").src = 'images\\\dot.gif';
//        document.gri_2_CA_3_3_img.src = 'images\\\dot.gif';
//alert(name + \"_img \" + 'images\\\dot.gif');
 }
 ";
 
 $js .= "function handleSelection(value) {
     if (value == \"#save_changes\") {
        toggle.loc.value = location.href;
        toggle.submit();
     } else {
     window.location=value;
     }
 }";

$pulldownMenu = "<select  onChange='handleSelection(this.value)'>
													<option selected value=''>Choose One</option>
													<option value='#top_anchor'>Top of Page</option>";
$z = 0;													
for ($y = 0; $y < count($list); $y++) {
    $fname = $list[$y]['fname'];
    $lname = $list[$y]['lname'];
    $anchor = $fname ."_" . $lname;
    $pulldownMenu .= "<option value='#$anchor'>$lname, $fname</option>
    ";

}
				
$pulldownMenu .= "<option value='#save_changes'>Save All Changes</option>
                  </select>";		
												
$toggleHeader_pre = "     <div align='left'>
											<br>
											<font size='4'>$stdcount Student(s) - $subName $lvl - $listName Group
												<br>
											</font>
                      <font size='2'>$pulldownMenu
											</font>
											<ul>
												<li type='circle'><font size='2'><b>Note:</b> Roll over each standard number to read its short name!</font>
											</ul>
											<p>The screen below shows the current status of these students in this content area.  Toggle the appropriate indicator, and enter comments as needed. Make sure you &quot;Save Changes&quot; for the entire page from either the pull down menu, or the button at the bottom of the page.  The time and date stamp of your entry for this student will be added.</p>
												<br>
												<font size='4'>Shared Standard Needs - $subName $lvl - $listName<br>
													<br>
												</font><font size='2'>Here is a &quot;weighted list&quot; of the common relative weaknesses of this group of students. The more students is this group that show any standard as having no toggled status </font><font size='2'>, Emerging status, or Developing status, the larger the name of the standard is in the list. This means that the largest short standard names are the most common relative weaknesses of the group.</font></p>
                        <p><font size='4' color='#cc0000'>Weighted List of Standards &amp; Assessments Needed</font><font size='2'>: </font></p>";
$toggleHeader_post ="</div>";

$body_pre .= "<form name=toggle method=post action=index.php?cmd=saveToggle>
          <input type=hidden name=loc>
          <input type=hidden name=listID value=$listID>
          <input type=hidden name=sub value=$sub>
          <input type=hidden name=lvl value=$lvl>$toggleHeader_pre";

$body .= $toggleHeader;
//$body .= "<b>$subName ($sub): [Graduation Level - $gradlvl] Current Level $lvl - Student Count $stdcount</b><br>";
/**************
for ($i = 0; $i < count($subject); $i++) {
   $body_post .= "<th title=\"". $subject[$i]['description'] ."\">" . $subject[$i]['std'] . "*</th>";
}
$body_post .= "$toggleHeader_post</tr>";

$toggleColor = 2;
*****************/
$A2Priv = Privilege(A2);
$A3Priv = Privilege(A3);
$TotalDisplay = 'view';

for ($y = 0; $y < count($list); $y++) {
//    if ($toggleColor == 1) { $toggleColor = 2; $color = $color2; }
//    else { $toggleColor = 1; $color = $color1; }
    $id = $list[$y]['studentid'];
    $fname = $list[$y]['fname'];
    $lname = $list[$y]['lname'];
    $site = $list[$y]['site'];
    $progress = $list[$y]['progress'];
    $ch_name = $list[$y]['change_username'];
    $ch_time = date($dateSettings, $list[$y]['change_timestamp']);    
    $anchor = $fname ."_" . $lname;
    $siteEqual = $currentMySite == $site;
    $idEqual = $currentAffiliatedID == $id;
    $Display =  checkStudent($idEqual, $siteEqual, $A2Priv, $A3Priv);
    $TotalDisplay = (($TotalDisplay == 'edit') or ($Display == 'edit')) ? 'edit':'view';
    $updateDot = "<a href=index.php?cmd=updateSingleLevelScore&id=$id&subject=$sub&level=$lvl onMouseOver=\"return escape('Update score for saved values. NOTE: THIS WILL RESET ANY TOGGLE/COMMENT CHANGES NOT SAVED.')\">.</a>";
    $body_post .= "<a name=\"$anchor\"></a><b><font color='#cc0000' class=big><a href=index.php?cmd=toggleStudent&p1=$id>$lname, $fname</a>$updateDot - <font color=#cc0000>$progress</font></font></b><br>";
    $body_post .= "<b>$subName $lvl Students $pulldownMenu</b><br>";
    $body_post .= "<b>Last Change:</b> $ch_name ($ch_time) - <a href=index.php?cmd=history&student=$id&subject=$sub&lvl=$lvl>History</a>";
    $body_post .= "<table border= 1>";
    $line0 = "<tr  bgcolor=#FFFFCC><th rowspan=2>$sub ($lvl)</th>";

     $line1 = "";
     $line2 = "";
     for ($i = 0; $i < count($subject); $i++) {
// name of cell = _id_subject_lvl
        $std = $subject[$i]['std'];
        $value = $student[$id][$std];
        debugPrint ("STD: $std $value<br>");
        $wlist[$std]['std'] = $std;
        $wlist[$std]['link'] = $subject[$i]['link'];
        $wlist[$std]['shortname'] = $subject[$i]['shortname'];
        $wlist[$std]['count']++;
        $wlist[$std]['sum'] += getToggleValue($value);
        $wlist[$std]['comp'] = $wlist[$std]['sum']/$stdcount;
        $des = htmlentities($subject[$i]['description']);
        $des = str_replace("'", "\'", $des );
        if (!isset($value)) { $type = "i"; } else { $type = "u"; }
         $line1 .= "<th width=$cellwidth onMouseOver=\"return escape('$des')\"> <a href=" . $subject[$i]['link'] . ">" . $subject[$i]['std'] . "</a> </th>";

        $name = "gr" . $type . "_" . $id . "_" . $sub . "_" . $lvl . "_" .$subject[$i]['std'];
        if($Display == 'edit') {
        $line2 .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
        $line2 .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
        $line2 .= "<select title = \"test_$id_$i\" bgcolor=$color name=" . $name . " onclick='changeValue(\"$name\",this.value )' >
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
//    echo "I: $i Width $width FMod: " , fmod($i+1, $width) . "<br>";
    if(fmod($i, $width) <> 0) {
       $body_post .= "$line0 $line1 </tr><tr> $line2 </tr>";
    }
   $body_post .= "</table><table border= 1 >";
     $line3 = "";
     $line4 = "";
     for ($i = 0; $i < count($overall); $i++) {
// name of cell = _id_subject_lvl
        $des = str_replace("'", "\'", $overall[$i]['description']);
        $value = $student[$id][$overall[$i]['std']];
        if (!isset($value)) { $type = "i"; } else { $type = "u"; }
         $line3 .= "<th width=$cellwidth onMouseOver=\"return escape('$des')\">" . $overall[$i]['std'] . "</th>";

        $name = "gr" . $type . "_" . $id . "_" . $sub . "_" . $lvl . "_" .$overall[$i]['std'];
        if($Display == 'edit') {
        $line4 .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
        $line4 .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
        $line4 .= "<select title = \"test_$id_$i\" bgcolor=$color name=" . $name . " onclick='changeValue(\"$name\",this.value )' >
                  <option value=\"\"" . selected("", $value) . "></option>
                  <option value=\"EMG\"" . selected("EMG", $value) . ">EMG</option>
                  <option value=\"DEV\"" . selected("DEV", $value) . ">DEV</option>
                  <option value=\"PRO\"" . selected("PRO", $value) . ">PRO</option>
                  <option value=\"ADV\"" . selected("ADV", $value) . ">ADV</option>
                  </select>&nbsp;
                  </td>\n";
          } else {
             $line4 .= "<td align=center>&nbsp;$value&nbsp;</td>";
          }
          if(fmod($i+1, $width) == 0) {
            $body_post .= "$line0 $line3 </tr><tr> $line4 </tr>";
            $line3 = "";
            $line4 = "";
            }
    }
    
/********************************************/
//    $value = getStdValue('qpi', $scores);
    $value = $student[$id]['qpi'];
    if (!isset($value)) { $type = "i"; } else { $type = "u"; }
    $value2 = $student[$id]['ase'];
    if (!isset($value2)) { $type2 = "i"; } else { $type2 = "u"; }
    $line3 .= "<th width=$cellwidth onMouseOver=\"return escape('Quarterly Performance Indicator')\">QPI</th>
    <th width=$cellwidth onMouseOver=\"return escape('ASE')\">ASE</th>";

    $name = "gr" . $type . "_" . $id . "_" . $sub . "_" . $lvl . "_qpi";
    $name2 = "gr" . $type2 . "_" . $id . "_" . $sub . "_" . $lvl . "_ase";
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
        $line4 .= "<td><input type=hidden name=old_" . $name2 . " value='" . $value2 . "'>\n";
        $line4 .= "<input type=hidden id=ch_" . $name2 . " name=ch_" . $name2 . " value=empty>\n";
        $line4 .= "<select title = \"test_$studentID_ase_$i\" bgcolor=$color name=" . $name2 . " onclick='changeValue(\"$name2\",this.value )' >
                  <option value=\"\"" . selected("", $value2) . "></option>
                  <option value=\"Eligible\"" . selected("Eligible", $value2) . ">Eligible</option>
                  <option value=\"Not_Eligible\"" . selected("Not_Eligible", $value2) . ">Not Eligible</option>
                  </select>&nbsp;
                  </td>\n";
    } else {
           $line4 .= "<td align=center>&nbsp;$value&nbsp;</td><td align=center>&nbsp;$value2&nbsp;</td>";
    }
/**************************************************************************/

//    if(fmod($i, $width) <> 0) {
       $body_post .= "$line0 $line3 </tr><tr> $line4 </tr>";
//    }

   $body_post .= "</table>";
   
   $value = $student[$id]['comment'];
   if (!isset($value)) { $type = "i"; } else { $type = "u"; }
   $name = "gr" . $type . "_" . $id . "_" . $sub . "_" . $lvl . "_comment";
   $body_post .= "<input type=hidden name=old_" . $name . " value=" . $value . ">\n";
   $body_post .= "<input type=hidden id=ch_" . $name . " name=ch_" . $name . " value=empty>\n";
   $body_post .= "<font size=\"2\"><b>Teacher Comments:</b></font><br>";
   $body_post .= $Display == 'edit' ? "</b></font><textarea name=\"comment_$id_$i\" rows=\"8\" cols=\"80\" wrap=\"physical\" onChange='changeValue(\"$name\",this.value )'  >$value</textarea><br>" :
              "$value&nbsp;<br><br>";
		   $body_post .= "</font>";
	
}

if($TotalDisplay == 'edit') {
$body_post .= "
    <input type=reset value=reset>
    <input type=button onClick='handleSelection(\"#save_changes\")' value='save all changes'>
    </form>";
}
    
$body_post .= "<br>* Placing mouse over standard number will display standards descriptions.";

$title = "Show Scores for List";

// $body = "This is the body";

//$wlist = getListSubjectLevelWeight ($listID, $sub, $lvl);
$wlist = array_unique2($wlist);
debugPrint ("<br>***P1: " . print_r ($wlist, true) . "<br><br>");
$wlist = array_sort($wlist, 'comp');
debugPrint ("***P2: " . print_r ($wlist, true) . "<br><br>");
$wnum = min(10, count($wlist));
$buckets = 4;
$start = 0;
$end = $wnum-1+$start;
debugPrint ("***START : $start END: $end<br><br>");
$t = $wlist[$start]['comp'];
$b = $wlist[$end]['comp'];
$spread = ($t - $b)/$buckets;

$weightedStd = "<div class=\"notetarget\">";
for ($i = $start; $i <= $end; $i++) {
   $val = $wlist[$i]['comp'];
  $sid = $sub . $lvl . "." . $wlist[$i]['std'];
   if($spread == 0) { $tmpnum = 0; } 
   else { $tmpnum = floor(($val - $b)/$spread); }
   $loc = $buckets - min($buckets-1, $tmpnum);
   $weightedStd .= "<a href=\"" . $wlist[$i]['link'] . "\" target=_blank><span class=t$loc>" . $sid .  "-" . $wlist[$i]['shortname'] . "</span></a> :: ";
}
$weightedStd .= "</div>";

$body = $body_pre . $weightedStd . $body_post;

include ("template.inc");

?>
