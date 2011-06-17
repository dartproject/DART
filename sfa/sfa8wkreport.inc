<?php

include_once("lib/libchart/libchart.php");
$listid = $_GET['listid'];
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=sfa8wkreport&listid=$listid&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";

debugPrint ("Here");

$w = 30;

$stages = array(
            array("stage" => "base", "name" => "Baseline", "color" => "#ffbfd1"),
            array("stage" => "first", "name" => "First Assess", "color" => "#ffcf96"),
            array("stage" => "second", "name" => "Second Assess", "color" => "#ffffb5"),
            array("stage" => "third", "name" => "Third Assess", "color" => "#aee67c"),
            array("stage" => "fourth", "name" => "Fourth Assess", "color" => "#b5e0ff")
           );
$grades = array ("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13");

$scores = GetAllGroupScores($listid, $year, '1-13');
$Kscores = GetAllGroupScores($listid, $year, 'K');


debugPrint ("Here2");

$body = "$selection<br><table border=1>";

function countURL ($stage, $grade, $stg, $kind, $num) {
   return (buildGroupUrl($stg[$stage][$grade][$kind]['studentid'],  
                 $stg[$stage][$grade][$kind]['studentshow'], 
                 dv($stg[$stage][$grade][$kind]['value']), $num));
}

$i = 0;

foreach ($stages as $stage) {
    $name = $stage['name'];
    $color = $stage['color'];
    $st = $stage['stage'];
    $line0 = "<td>$name</td>";    
    $line1 = "<td>Total# Kids</td>";
    $line2 = "<td># of Kids on<br>Grade Level<br></td>";
    $line3 = "<td>% of Kids on<br>GradeLevel</td>";
    $totct = 0;
    $totabv = 0;
    $totid = '';
    $totshow ='';

   foreach ($grades as $grade) {
      $ct = $scores[$st][$grade]['count']['value'];
      $abv = $scores[$st][$grade]['above']['value'];
      $per = number_format(($abv/$ct)*100, 0);
      $totct += $ct;
      $totabv += $abv;
      $totid .= $scores[$st][$grade]['above']['studentid'];
      $totshow .= $scores[$st][$grade]['above']['studentshow'];
      
      $line0 .= "<td width=$w align=center>$grade</td>";
      $line1 .= "<td align=right>" . countURL($st, $grade, $scores, 'count', $i++) . " </td>";
      $line2 .=  "<td align=right>" . countURL($st, $grade, $scores, 'above', $i++) . " </td>";
      $line3 .=  "<td align=right>" . dv($per) . "% </td>";
      
   }
   $line0 .= "<td width=$w align=center bgcolor='FFFFFF'>K</td>";
   $line1 .= "<td align=right bgcolor='FFFFFF'>" . countURL($st, 'K', $Kscores, 'count', $i++) . " </td>";
   $line2 .=  "<td align=right bgcolor='FFFFFF'>&nbsp;</td>";
   $line3 .=  "<td align=right bgcolor='FFFFFF'>&nbsp;</td>";
   
   $totper = number_format(($totabv/$totct)*100, 0);

   $data[] = array($st, $totper);
   
   $span = count($grades);
   $span2 = $span+3;
   $line4 = "<td>Total % of Kids<br>on Grade Level<br>(1-13+)</td>
             <td align=right>$totper% </td>
             <td align=right>". buildGroupUrl($totid, $totshow, $totabv, $i++) . "</td>
             <td colspan=$span></td>";
             
   $body .= "<tr bgcolor=$color>$line0</tr>
             <tr bgcolor=$color>$line1</tr>
             <tr bgcolor=$color>$line2</tr>
             <tr bgcolor=$color>$line3</tr>
             <tr bgcolor=$color>$line4</tr>
             <tr><td colspan=$span2 bgcolor=black></td></tr>";
}

$body .= "</table>";

// -------------------- Graph ------------------------


$fn = "./exp/d$currentUserID";

require_once 'phplot.php';

$plot =& new PHPlot(600, 300);
$plot->SetImageBorderType('plain');

$plot->SetPlotType('bars');
$plot->SetDataType('text-data');
$plot->SetDataValues($data);

# Main plot title:
$plot->SetTitle('Percent of Students Reading 
On or Above Grade Level');

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


include_once ("template.inc");

?>