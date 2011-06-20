<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include_once ("lib/chart.inc");

$priv = Privilege(A26);
$studentID = $_GET['studentID'];
$grade = $_GET['grade'];
$siteID = $_GET['siteID'];

if($priv == 'none') { NoPriv("denied DrillDown", ""); }
else if($priv == 'district') {
  $siteList = getSitesOptions($siteID);

   $pulldownsites = "<select name=\"siteID\" onChange=\"submit()\">
  <option value=\"\" " . selected ($siteID, "") . ">All Locations</option>
  $siteList </select>";
} else {
   $siteID = $currentMySite;
   $pulldownsites = "<select name=\"siteID\" >
  <option value=\"$currentMySite\" selected>$currentMySite</option> 
  </select>";
}

$w=200;
$pval = getPivotValues($studentID, $grade, $siteID);
$c1 = "lightpink";
$c2 = "yellow";
$c3 = "#99ff99"; //"green";
$c4 = "#ccffff"; // "blue";

$values = $pval['values'];
debugPrint ("<br>RETURN VALUE: $values <br>");
$subjects = getSubjects();

$jumpmenu = "<select  onChange='javascript:window.location=value;'>
													<option selected value=''>Choose One</option>
													<option value='#top_anchor'>Top of Page</option>";
																	
for ($i=0; $i<count($subjects); $i++) {
    $subid = $subjects[$i]['id'];
    $subname = $subjects[$i]['name'];
    $jumpmenu .= "<option value='#$subid'>$subname</option>";
}
$jumpmenu .= "</select>";	


function V($sub, $lvl="") {
    global $values, $studentID, $grade, $siteID;
    
    $val = $values[$sub][$lvl];
    if ($val=="") {$val = "&nbsp;";}
    else { $val = "<center><a href=index.php?cmd=drilldown&sub=$sub&lvl=$lvl&$studentID=$studentid&grade=$grade&siteID=$siteID>$val</a></center>"; }
    return ($val);
}
/* computing the totals for each area */
function T($sub) {
    global $values, $studentID, $grade, $siteID;
    $sum = 0;
    
    for ($i = 0; $i <= 12; $i++) {
        $sum = $sum + $values[$sub][$i];
    }
    $str = "<center><a href=index.php?cmd=drilldown&sub=$sub&studentID=$studentID&grade=$grade&siteID=$siteID>$sum</a></center>";
    
    return ($str);
}


$pStudent = pulldownPivotStudents($studentID, $grade, $siteID);
$pulldownStudent = $pStudent['options'];
$totalStudents = $pStudent['count'];

$body = "<a name=$subid></a>$jumpmenu Jump... <br><br>
<form name=ptime method=get action=\"index.php\">
<input type=hidden name=cmd value=pivot>
$pulldownStudent

<select name=\"grade\" onChange=\"submit()\">
  <option value\"\" " . selected ($grade, "") . ">All Grades</option>
	<option value=\"K\" " . selected ($grade, "K") . ">K</option>
	<option value=\"1\" " . selected ($grade, "1") . ">1</option>
	<option value=\"2\" " . selected ($grade, "2") . ">2</option>
	<option value=\"3\" " . selected ($grade, "3") . ">3</option>
	<option value=\"4\" " . selected ($grade, "4") . ">4</option>
	<option value=\"5\" " . selected ($grade, "5") . ">5</option>
	<option value=\"6\" " . selected ($grade, "6") . ">6</option>
	<option value=\"7\" " . selected ($grade, "7") . ">7</option>
	<option value=\"8\" " . selected ($grade, "8") . ">8</option>
	<option value=\"9\" " . selected ($grade, "9") . ">9</option>
	<option value=\"10\" " . selected ($grade, "10") . ">10</option>
	<option value=\"11\" " . selected ($grade, "11") . ">11</option>
	<option value=\"12\" " . selected ($grade, "12") . ">12</option>
	<option value=\"13\" " . selected ($grade, "13") . ">13</option>
</select>

$pulldownsites

</form>Total Student [$totalStudents]

<table border=1>
<tr><th width=$w> </th><th width=$w>CS</th><th width=$w>CA</th width=$w><th width=$w>LS</th><th width=$w>MA</th><th width=$w>RE</th><th width=$w>SC</th><th width=$w>SS</th><th width=$w>TE</th><th width=$w>WR</th></tr>

<tr><th>0</th><td >" . V("CS", "0") . "</td><td  >" . V("CA", "0") . "</td><td >" . V("LS", "0") . "</td><td >" . V("MA", "0") . "</td><td >" . V("RE", "0") . "</td><td >" . V("SC", "0") . "</td><td >" . V("SS", "0") . "</td><td >" . V("TE", "0") . "</td><td >" . V("WR", "0") . "</td></tr>

<tr><th>1</th><td >" . V("CS", "1") . "</td><td  >" . V("CA", "1") . "</td><td >" . V("LS", "1") . "</td><td >" . V("MA", "1") . "</td><td >" . V("RE", "1") . "</td><td >" . V("SC", "1") . "</td><td >" . V("SS", "1") . "</td><td >" . V("TE", "1") . "</td><td >" . V("WR", "1") . "</td></tr>

<tr><th>2</th><td >" . V("CS", "2") . "</td><td  bgcolor=$c1>" . V("CA", "2") . "</td><td bgcolor=$c1>" . V("LS", "2") . "</td><td >" . V("MA", "2") . "</td><td >" . V("RE", "2") . "</td><td bgcolor=$c1>" . V("SC", "2") . "</td><td bgcolor=$c1>" . V("SS", "2") . "</td><td >" . V("TE", "2") . "</td><td >" . V("WR", "2") . "</td></tr>

<tr><th>3</th><td bgcolor=$c1>" . V("CS", "3") . "</td><td  >" . V("CA", "3") . "</td><td >" . V("LS", "3") . "</td><td bgcolor=$c1>" . V("MA", "3") . "</td><td >" . V("RE", "3") . "</td><td bgcolor=$c2>" . V("SC", "3") . "</td><td >" . V("SS", "3") . "</td><td bgcolor=$c1>" . V("TE", "3") . "</td><td bgcolor=$c1>" . V("WR", "3") . "</td></tr>

<tr><th>4</th><td >" . V("CS", "4") . "</td><td  bgcolor=$c2>" . V("CA", "4") . "</td><td bgcolor=$c2>" . V("LS", "4") . "</td><td >" . V("MA", "4") . "</td><td bgcolor=$c1>" . V("RE", "4") . "</td><td bgcolor=$c3>" . V("SC", "4") . "</td><td bgcolor=$c2>" . V("SS", "4") . "</td><td bgcolor=$c2>" . V("TE", "4") . "</td><td >" . V("WR", "4") . "</td></tr>

<tr><th>5</th><td bgcolor=$c2>" . V("CS", "5") . "</td><td  >" . V("CA", "5") . "</td><td >" . V("LS", "5") . "</td><td >" . V("MA", "5") . "</td><td bgcolor=$c2>" . V("RE", "5") . "</td><td >" . V("SC", "5") . "</td><td >" . V("SS", "5") . "</td><td bgcolor=$c3>" . V("TE", "5") . "</td><td bgcolor=$c2>" . V("WR", "5") . "</td></tr>

<tr><th>6</th><td bgcolor=$c3>" . V("CS", "6") . "</td><td  bgcolor=$c3>" . V("CA", "6") . "</td><td bgcolor=$c3>" . V("LS", "6") . "</td><td >" . V("MA", "6") . "</td><td bgcolor=$c3>" . V("RE", "6") . "</td><td bgcolor=$c4>" . V("SC", "6") . "</td><td bgcolor=$c3>" . V("SS", "6") . "</td><td bgcolor=$c4>" . V("TE", "6") . "</td><td bgcolor=$c3>" . V("WR", "6") . "</td></tr>

<tr><th>7</th><td bgcolor=$c4>" . V("CS", "7") . "</td><td  bgcolor=$c4>" . V("CA", "7") . "</td><td bgcolor=$c4>" . V("LS", "7") . "</td><td bgcolor=$c2>" . V("MA", "7") . "</td><td bgcolor=$c4>" . V("RE", "7") . "</td><td >" . V("SC", "7") . "</td><td >" . V("SS", "7") . "</td><td >" . V("TE", "7") . "</td><td bgcolor=$c4>" . V("WR", "7") . "</td></tr>

<tr><th>8</th><td >" . V("CS", "8") . "</td><td  >" . V("CA", "8") . "</td><td >" . V("LS", "8") . "</td><td >" . V("MA", "8") . "</td><td >" . V("RE", "8") . "</td><td >" . V("SC", "8") . "</td><td bgcolor=$c4>" . V("SS", "8") . "</td><td >" . V("TE", "8") . "</td><td >" . V("WR", "8") . "</td></tr>

<tr><th>9</th><td >" . V("CS", "9") . "</td><td  >" . V("CA", "9") . "</td><td >" . V("LS", "9") . "</td><td bgcolor=$c3>" . V("MA", "9") . "</td><td >" . V("RE", "9") . "</td><td >" . V("SC", "9") . "</td><td >" . V("SS", "9") . "</td><td >" . V("TE", "9") . "</td><td >" . V("WR", "9") . "</td></tr>

<tr><th>10</th><td >" . V("CS", "10") . "</td><td  >" . V("CA", "10") . "</td><td >" . V("LS", "10") . "</td><td bgcolor=$c4>" . V("MA", "10") . "</td><td >" . V("RE", "10") . "</td><td >" . V("SC", "10") . "</td><td >" . V("SS", "10") . "</td><td >" . V("TE", "10") . "</td><td >" . V("WR", "10") . "</td></tr>

<tr><th>11</th><td >" . V("CS", "11") . "</td><td  >" . V("CA", "11") . "</td><td >" . V("LS", "11") . "</td><td >" . V("MA", "11") . "</td><td >" . V("RE", "11") . "</td><td >" . V("SC", "11") . "</td><td >" . V("SS", "11") . "</td><td >" . V("TE", "11") . "</td><td >" . V("WR", "11") . "</td></tr>

<tr><th>12</th><td >" . V("CS", "12") . "</td><td  >" . V("CA", "12") . "</td><td >" . V("LS", "12") . "</td><td >" . V("MA", "12") . "</td><td >" . V("RE", "12") . "</td><td >" . V("SC", "12") . "</td><td >" . V("SS", "12") . "</td><td >" . V("TE", "12") . "</td><td >" . V("WR", "12") . "</td></tr>



<tr><th>Total</th><th >" . T("CS") . "</th><th  >" . T("CA") . "</th><th >" . T("LS") . "</th><th >" . T("MA") . "</th><th >" . T("RE") . "</th><th >" . T("SC") . "</th><th >" . T("SS") . "</th><th >" . T("TE") . "</th><th >" . T("WR") . "</th></tr>


</table>
<br>
<br>
<table border=1>
<tr><td bgcolor=$c1><b>PINK</b></td><td> 3rd Grade Testing</td></tr>
<tr><td bgcolor=$c2><b>YELLOW</b></td><td> 6th Grade Testing</td></tr>
<tr><td bgcolor=$c3><b>GREEN</b></td><td> 8th Grade Testing</td></tr>
<tr><td bgcolor=$c4><b>BLUE</b></td><td> 10th Grade Testing</td></tr>
</table>
";


for ($i=0; $i<count($subjects); $i++) {
    $subid = $subjects[$i]['id'];
    $subname = $subjects[$i]['name'];
    $val = &$values[$subid];
    $other['subject']=$subid;
    $other['$studentID']=$studentID;
    $other['$grade']=$grade;
    $other['$siteID']=$siteID;

    debugPrint ("SubID: " . $subid . " Subject Name: " . $subname . "<br>");
    $body .= "<br><br><br><a name=$subid></a>$jumpmenu<br>";
    $body .= graphArea ($val, $subname, $other);
//    break;
}

$body = "<center>$body</center>";


include ("template.inc");
?>
