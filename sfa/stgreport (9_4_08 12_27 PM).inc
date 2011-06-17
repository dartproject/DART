<?php

//echo ("Here");

$listid = $_GET['listid'];
$cuttoff = getCutOffs();
$hotlist = getHotlistValues();
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=stgreport&listid=$listid&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";

function abovelevel ($grade, $score, $stage) {
  global $cuttoff;
  
  $score = scorevalue($score);
  $neededmin =  $cuttoff[$grade][$stage];
  
  $answer = ($score >= $neededmin and $score != "") ? true : false;
  debugPrint("Score: $score Grade: $grade Stage: $stage NeededMin: $neededmin Answer: $answer");
  return ($answer);
}
/*** n = not on hotlist, u = on hotlist and above, d = on hotlist and below ***/
function hotlocation ($grade, $score, $stage, $remove) {
  global $cuttoff, $hotlist;
  
  $hl = $hotlist[$grade][$stage];
  $ct = $cuttoff[$grade][$stage];
  
  if(scoreR($score) == $hl and $remove == "" and $score != "") {
     $dir = scorevalue($score) >= $ct ? "u": "d";
  } else {
    $dir = 'n';
  }
//  if($stage == 'base') {
//      echo("RawScore: $score Score: " . scoreR($score) . " Grade: $grade Stage: $stage Hotlist: $hl Cutoff: $ct Dir: $dir<br>");
//  }
  return ($dir);
}

$w = "width=40 align=center";
$students = GetListWithScore($listid, $year, true);
$ct = count($students);
echo "Count: $ct";

$stg[][][] = "";



foreach ($students as $stu) {
  $id = $stu->studentid;
  $name = $stu->fname . " " . $stu->lname;
  $base = $stu->base_rawscore;
  $first = $stu->first_rawscore;
  $second = $stu->second_rawscore;
  $third = $stu->third_rawscore;
  $fourth = $stu->fourth_rawscore;
  
  $removeb = $stu->base_hlremove;
  $remove1 = $stu->first_hlremove;
  $remove2 = $stu->second_hlremove;
  $remove3 = $stu->third_hlremove;
  $remove4 = $stu->fourth_hlremove;

  $grade = $stu->gradelevel;
  $site = $stu->site;
  debugPrint ("<br>$id) Site: $site B: $base- F: $first S: $second T: $third F: $fourth");
// Total Count  
  $stg['base']['count']['value'] += (scorevalue($base) == "" ? 0 : 1);
  $stg['base']['count']['studentid'] .= (scorevalue($base) == "" ? "" : "$id, ");
  $stg['base']['count']['studentshow'] .= (scorevalue($base) == "" ? "" : "$name: ");
  
  $stg['first']['count']['value'] += (scorevalue($first) == "" ? 0 : 1);
  $stg['first']['count']['studentid'] .= (scorevalue($first) == "" ? "" : "$id, ");
  $stg['first']['count']['studentshow'] .= (scorevalue($first) == "" ? "" : "$name: ");
  
  $stg['second']['count']['value'] += (scorevalue($second) == "" ? 0 : 1);
  $stg['second']['count']['studentid'] .= (scorevalue($second) == "" ? "" : "$id, ");
  $stg['second']['count']['studentshow'] .= (scorevalue($second) == "" ? "" : "$name: ");
  
  $stg['third']['count']['value'] += (scorevalue($third) == "" ? 0 : 1);
  $stg['third']['count']['studentid'] .= (scorevalue($third) == "" ? "" : "$id, ");
  $stg['third']['count']['studentshow'] .= (scorevalue($third) == "" ? "" : "$name: ");
  
  $stg['fourth']['count']['value'] += (scorevalue($fourth) == "" ? 0 : 1);
  $stg['fourth']['count']['studentid'] .= (scorevalue($fourth) == "" ? "" : "$id, ");
  $stg['fourth']['count']['studentshow'] .= (scorevalue($fourth) == "" ? "" : "$name: ");
  debugPrint("Count: " .   $stg['base']['count']['value']);
  
// ON Level Count  
  $stg['base']['on']['value'] += (aboveLevel ($grade, $base, 'base') ? 1 : 0);
  $stg['base']['on']['studentid'] .= (aboveLevel ($grade, $base, 'base') ?  "$id, " : "");
  $stg['base']['on']['studentshow'] .= (aboveLevel ($grade, $base, 'base') ?  "$name: " : "");

  $stg['first']['on']['value'] += (aboveLevel ($grade, $first, 'first') ? 1 : 0);
  $stg['first']['on']['studentid'] .= (aboveLevel ($grade, $first, 'first') ?  "$id, " : "");
  $stg['first']['on']['studentshow'] .= (aboveLevel ($grade, $first, 'first') ?  "$name: " : "");

  $stg['second']['on']['value'] += (aboveLevel ($grade, $second, 'second') ? 1 : 0);
  $stg['second']['on']['studentid'] .= (aboveLevel ($grade, $second, 'second') ?  "$id, " : "");
  $stg['second']['on']['studentshow'] .= (aboveLevel ($grade, $second, 'second') ?  "$name: " : "");

  $stg['third']['on']['value'] += (aboveLevel ($grade, $third, 'third') ? 1 : 0);
  $stg['third']['on']['studentid'] .= (aboveLevel ($grade, $third, 'third') ?  "$id, " : "");
  $stg['third']['on']['studentshow'] .= (aboveLevel ($grade, $third, 'third') ?  "$name: " : "");

  $stg['fourth']['on']['value'] += (aboveLevel ($grade, $fourth, 'fourth') ? 1 : 0);
  $stg['fourth']['on']['studentid'] .= (aboveLevel ($grade, $fourth, 'fourth') ?  "$id, " : "");
  $stg['fourth']['on']['studentshow'] .= (aboveLevel ($grade, $fourth, 'fourth') ?  "$name: " : "");

  debugPrint("Here3");  

  $baseh = hotlocation ($grade, $base, 'base', $removeb);
  $firsth = hotlocation ($grade, $first, 'first', $remove1);
  $secondh = hotlocation ($grade, $second, 'second', $remove2);
  $thirdh = hotlocation ($grade, $third, 'third', $remove3);
  $fourth = hotlocation ($grade, $fourth, 'fourth', $remove4);
  debugPrint("Here4");

// Hotabove    
  $stg['base']['hotabove']['value'] += $baseh == 'u' ? 1 : 0;
  $stg['base']['hotabove']['studentid'] .= $baseh == 'u' ?  "$id, " : "";
  $stg['base']['hotabove']['studentshow'] .= $baseh == 'u' ?  "$name: " : "";
  
  $stg['first']['hotabove']['value'] +=  $firsth == 'u' ? 1 : 0;
  $stg['first']['hotabove']['studentid'] .= $firsth == 'u' ?  "$id, " : "";
  $stg['first']['hotabove']['studentshow'] .= $firsth == 'u' ?  "$name: " : "";

  $stg['second']['hotabove']['value'] +=  $secondh == 'u' ? 1 : 0;
  $stg['second']['hotabove']['studentid'] .= $secondh == 'u' ?  "$id, " : "";
  $stg['second']['hotabove']['studentshow'] .= $secondh == 'u' ?  "$name: " : "";

  $stg['third']['hotabove']['value'] += $thirdh == 'u' ? 1 : 0;
  $stg['third']['hotabove']['studentid'] .= $thirdh == 'u' ?  "$id, " : "";
  $stg['third']['hotabove']['studentshow'] .= $thirdh == 'u' ?  "$name: " : "";

  $stg['fourth']['hotabove']['value'] += $fourth == 'u' ? 1 : 0;
  $stg['fourth']['hotabove']['studentid'] .= $fourth == 'u' ?  "$id, " : "";
  $stg['fourth']['hotabove']['studentshow'] .= $fourth == 'u' ?  "$name: " : "";
  debugPrint("Here5");

// hot Below 
  $stg['base']['hotbelow']['value'] += $baseh == 'd' ? 1 : 0;
  $stg['base']['hotbelow']['studentid'] .= $baseh == 'd' ?  "$id, " : "";
  $stg['base']['hotbelow']['studentshow'] .= $baseh == 'd' ?  "$name: " : "";

  $stg['first']['hotbelow']['value'] +=  $firsth == 'd' ? 1 : 0;
  $stg['first']['hotbelow']['studentid'] .= $firsth == 'd' ?  "$id, " : "";
  $stg['first']['hotbelow']['studentshow'] .= $firsth == 'd' ?  "$name: " : "";

  $stg['second']['hotbelow']['value'] +=  $secondh == 'd' ? 1 : 0;
  $stg['second']['hotbelow']['studentid'] .= $secondh == 'd' ?  "$id, " : "";
  $stg['second']['hotbelow']['studentshow'] .= $secondh == 'd' ?  "$name: " : "";

  $stg['third']['hotbelow']['value'] += $thirdh == 'd' ? 1 : 0;
  $stg['third']['hotbelow']['studentid'] .= $thirdh == 'd' ?  "$id, " : "";
  $stg['third']['hotbelow']['studentshow'] .= $thirdh == 'd' ?  "$name: " : "";

  $stg['fourth']['hotbelow']['value'] += $fourth == 'd' ? 1 : 0;
  $stg['fourth']['hotbelow']['studentid'] .= $fourth == 'd' ?  "$id, " : "";
  $stg['fourth']['hotbelow']['studentshow'] .= $fourth == 'd' ?  "$name: " : "";

  debugPrint("Here6");
  

}

$report['base']['perabove'] = round($stg['base']['on']['value']/$stg['base']['count']['value'], 2) * 100;
$report['first']['perabove'] = round($stg['first']['on']['value']/$stg['first']['count']['value'], 2) * 100;
$report['second']['perabove'] = round($stg['second']['on']['value']/$stg['second']['count']['value'], 2) * 100;
$report['third']['perabove'] = round($stg['third']['on']['value']/$stg['third']['count']['value'], 2) * 100;
$report['fourth']['perabove'] = round($stg['fourth']['on']['value']/$stg['fourth']['count']['value'], 2) * 100;

$report['first']['goal'] = round(($stg['base']['hotbelow']['value']+$stg['base']['on']['value'])/$stg['base']['count']['value'], 2) * 100;
$report['second']['goal'] = round(($stg['first']['hotbelow']['value']+$stg['first']['on']['value'])/$stg['first']['count']['value'], 2) * 100;
$report['third']['goal'] = round(($stg['second']['hotbelow']['value']+$stg['second']['on']['value'])/$stg['second']['count']['value'], 2) * 100;
$report['fourth']['goal'] = round(($stg['third']['hotbelow']['value']+$stg['third']['on']['value'])/$stg['third']['count']['value'], 2) * 100;

//echo ("<br>Short Term Goal Array ====> ");
//print_r ($stg);

//echo ("<br>ABOVECOUNT ====> ");
//print_r ($aboveCount);

$w = "width=50 align=center";
$body .= "<h2>Short Term Goal</h2>$selection
          <table border=1>
            <tr>
              <td align=center><b>Titles</b></td>
              <td $w><b>Baseline</b></td>
              <td $w><b>1st</b></td>
              <td $w><b>2nd</b></td>
              <td $w><b>3rd</b></td>
              <td $w><b>4th</b></td>
            </tr>";

$adt = getDates($year);
$alignment = "align=right";

function countURL ($stg, $stage, $kind, $num) {
   return (buildGroupUrl($stg[$stage][$kind]['studentid'],  
                 $stg[$stage][$kind]['studentshow'], 
                 dv($stg[$stage][$kind]['value']),
                 $num));
}

$total[][][] = "";
$total['base']['hotlist']['value'] = $stg['base']['hotabove']['value'] + $stg['base']['hotbelow']['value'];
$total['first']['hotlist']['value'] = $stg['first']['hotabove']['value'] + $stg['first']['hotbelow']['value'];
$total['second']['hotlist']['value'] = $stg['second']['hotabove']['value'] + $stg['second']['hotbelow']['value'];
$total['third']['hotlist']['value'] = $stg['third']['hotabove']['value'] + $stg['third']['hotbelow']['value'];
$total['fourth']['hotlist']['value'] = $stg['fourth']['hotabove']['value'] + $stg['fourth']['hotbelow']['value'];

$total['base']['hotlist']['studentshow'] = $stg['base']['hotabove']['studentshow'] . $stg['base']['hotbelow']['studentshow'];
$total['first']['hotlist']['studentshow'] = $stg['first']['hotabove']['studentshow'] . $stg['first']['hotbelow']['studentshow'];
$total['second']['hotlist']['studentshow'] = $stg['second']['hotabove']['studentshow'] . $stg['second']['hotbelow']['studentshow'];
$total['third']['hotlist']['studentshow'] = $stg['third']['hotabove']['studentshow'] .  $stg['third']['hotbelow']['studentshow'];
$total['fourth']['hotlist']['studentshow'] = $stg['fourth']['hotabove']['studentshow'] . $stg['fourth']['hotbelow']['studentshow'];

$total['base']['hotlist']['studentid'] = $stg['base']['hotabove']['studentid'] . $stg['base']['hotbelow']['studentid'];
$total['first']['hotlist']['studentid'] = $stg['first']['hotabove']['studentid'] . $stg['first']['hotbelow']['studentid'];
$total['second']['hotlist']['studentid'] = $stg['second']['hotabove']['studentid'] . $stg['second']['hotbelow']['studentid'];
$total['third']['hotlist']['studentid'] = $stg['third']['hotabove']['studentid'] .  $stg['third']['hotbelow']['studentid'];
$total['fourth']['hotlist']['studentid'] = $stg['fourth']['hotabove']['studentid'] . $stg['fourth']['hotbelow']['studentid'];

$total['base']['hotgoal']['value'] = $stg['base']['hotbelow']['value'] + $stg['base']['on']['value'];
$total['first']['hotgoal']['value'] = $stg['first']['hotbelow']['value'] + $stg['first']['on']['value'];
$total['second']['hotgoal']['value'] = $stg['second']['hotbelow']['value'] + $stg['second']['on']['value'];
$total['third']['hotgoal']['value'] = $stg['third']['hotbelow']['value'] + $stg['third']['on']['value'];
$total['fourth']['hotgoal']['value'] = $stg['fourth']['hotbelow']['value'] + $stg['fourth']['on']['value'];

$total['base']['hotgoal']['studentshow'] = $stg['base']['hotbelow']['studentshow'] . $stg['base']['on']['studentshow'];
$total['first']['hotgoal']['studentshow'] = $stg['first']['hotbelow']['studentshow'] . $stg['first']['on']['studentshow'];
$total['second']['hotgoal']['studentshow'] = $stg['second']['hotbelow']['studentshow'] . $stg['second']['on']['studentshow'];
$total['third']['hotgoal']['studentshow'] = $stg['third']['hotbelow']['studentshow'] . $stg['third']['on']['studentshow'];
$total['fourth']['hotgoal']['studentshow'] = $stg['fourth']['hotbelow']['studentshow'] . $stg['fourth']['on']['studentshow'];

$total['base']['hotgoal']['studentid'] = $stg['base']['hotbelow']['studentid'] . $stg['base']['on']['studentid'];
$total['first']['hotgoal']['studentid'] = $stg['first']['hotbelow']['studentid'] . $stg['first']['on']['studentid'];
$total['second']['hotgoal']['studentid'] = $stg['second']['hotbelow']['studentid'] . $stg['second']['on']['studentid'];
$total['third']['hotgoal']['studentid'] = $stg['third']['hotbelow']['studentid'] . $stg['third']['on']['studentid'];
$total['fourth']['hotgoal']['studentid'] = $stg['fourth']['hotbelow']['studentid'] . $stg['fourth']['on']['studentid'];

//print_r($total);

$i = 0;
$body .= "<tr>
			  <td><b>Date of Assessment</b></td>
			  <td>" . dv($adt['base_date']) . "</td>
			  <td>" . dv($adt['first_date']) . "</td>
			  <td>" . dv($adt['second_date']) . "</td>
			  <td>" . dv($adt['third_date']) . "</td>
			  <td>" . dv($adt['fourth_date']) . "</td>
          </tr><tr>
			  <td><b>Current SFA Enrollment (1 - 13+)</b></td>
			  <td align=right>" . countURL ($stg, 'base','count', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'first','count', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'second','count', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'third','count', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'fourth','count', $i++) . "</td>
          </tr><tr>
			  <td><b>Number of students at or above level</b></td>
			  <td $alignment>" . countURL ($stg, 'base', 'on', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'first', 'on', $i++). "</td>
			  <td $alignment>" . countURL ($stg, 'second', 'on', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'third', 'on', $i++) . "</td>
			  <td $alignment>" . countURL ($stg, 'fourth', 'on', $i++) . "</td>
          </tr><tr>
			  <td><b>Current Percentage of students at or above level</b></td>
			  <td $alignment>" . dv($report['base']['perabove']) . "% </td>
			  <td $alignment>" . dv($report['first']['perabove']) . "% </td>
			  <td $alignment>" . dv($report['second']['perabove']) . "% </td>
			  <td $alignment>" . dv($report['third']['perabove']) . "% </td>
			  <td $alignment>" . dv($report['fourth']['perabove']) . "% </td>
          </tr><tr>
              <td colspan = 6>&nbsp;</td>
          </tr><tr>
			  <td><b>Number of Hot List student BELOW Level</b></td>
			  <td $alignment>" . countURL ($stg,'base','hotbelow', $i++) . "</td>
			  <td $alignment>" . countURL ($stg,'first','hotbelow', $i++) . "</td>
			  <td $alignment>" . countURL ($stg,'second','hotbelow', $i++) . "</td>
			  <td $alignment>" . countURL ($stg,'third','hotbelow', $i++) . "</td>
			  <td $alignment>" . countURL ($stg,'fourth','hotbelow', $i++) . "</td>
          </tr><tr>
			  <td><b>Number of Hot List students at or above level</b></td>
			  <td $alignment>" . countURL($stg,'base','hotabove', $i++) . "</td>
			  <td $alignment>" . countURL($stg,'first','hotabove', $i++) . "</td>
			  <td $alignment>" . countURL($stg,'second','hotabove', $i++)  . "</td>
			  <td $alignment>" . countURL($stg,'third','hotabove', $i++)  . "</td>
			  <td $alignment>" . countURL($stg,'fourth','hotabove', $i++)  . "</td>
          </tr><tr>
			  <td><b>Total Number of Hot List students</b></td>
			  <td $alignment>" . countURL($total, 'base', 'hotlist', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'first', 'hotlist', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'second', 'hotlist', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'third', 'hotlist', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'fourth', 'hotlist', $i++) . "</td>
          </tr><tr>
              <td colspan = 6>&nbsp;</td>
          </tr><tr>
			  <td><b>GOAL of students at or above level at<br>the end of current 8 weeks</b></td>
			  <td>&nbsp;</td>
			  <td $alignment>" . countURL($total, 'base', 'hotgoal', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'first', 'hotgoal', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'second', 'hotgoal', $i++) . "</td>
			  <td $alignment>" . countURL($total, 'third', 'hotgoal', $i++). "</td>
          </tr><tr>
			  <td><b>GOAL % of students at or above level at<br> the end of current 8 weeks</b></td>
			  <td>&nbsp;</td>
			  <td $alignment>" . dv($report['first']['goal']) . "% </td>
			  <td $alignment>" . dv($report['second']['goal']) . "% </td>
			  <td $alignment>" . dv($report['third']['goal']) . "% </td>
			  <td $alignment>" . dv($report['fourth']['goal']) . "% </td>
          </tr>
          ";  
          
/**************************************
$sites = getSites('district');
$phases = array('base', 'first', 'second', 'third', 'fourth');

$i=0;
foreach ($sites as $site) {
  $s = $site['siteid'];
//  $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
    $color =  fmod($i++, 2) == 0 ? 'white' : '#E5E5E5';
  
  $body .= "<tr bgcolor=$color><td>$s</td>";

   foreach ($phases as $phase) {
     $full = $fullCount[$s][$phase]['count'];
     $on = $fullCount[$s][$phase]['on'];
     $per = round($on/$full, 2)*100;
  
     $body .= "<td $w>$on</td>
               <td $w>$full</td>
               <td $w>$per%</td>";
  }
  $body .= "</tr>";
}
***********************************/

$body .= "</table>";



$fn = "./exp/d2$currentUserID";

include_once ("phplot.php");

//$report['base']['perabove'] = 20;

$data = array(
  array('Base', $report['base']['perabove']), 
  array('1st', $report['first']['perabove'], $report['first']['goal']), 
  array('2nd', $report['second']['perabove'], $report['second']['goal']),
  array('3rd', $report['third']['perabove'], $report['third']['goal']), 
  array('4th', $report['fourth']['perabove'], $report['fourth']['goal'])
);

$plot =& new PHPlot(600, 300);
$plot->SetImageBorderType('plain');

$plot->SetPlotType('bars');
$plot->SetDataType('text-data');
$plot->SetDataValues($data);

# Main plot title:
$plot->SetTitle('Short Term Goal 
Based on the current Hot List');

# Turn off X tick labels and ticks because they don't apply here:
$plot->SetXTickLabelPos('none');
$plot->SetXTickPos('none');

# Turn labels on for Y plot
$plot->SetYDataLabelPos('plotin');

$plot->SetIsInline(True);
$plot->SetOutputFile("$fn.png");
$plot->DrawGraph();
  
$body .= "<br><br><img alt='Vertical bars chart' src='$fn.png' style='border: 1px solid gray;'>
";

include_once("template.inc");

?>