<?php

//echo ("Here");
$year = isset($_GET['year']) ? $_GET['year']: '2007';
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=stsreport&listid=$listid&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";

$w = "width=40 align=center";
$res = GetStudentWithScore($year);
$fullCount[][][] = "";
$cutoff = getCutOffs();

debugPrint("<table border=1>", "no");
debugPrint("<tr><td>id</td><td>grade</td><td>base</td><td>first</td><td>second</td><td>third</td><td>fourth</td><td><tr>", "no");
foreach ($res as $scores) {
  $id = $scores->sid;
  $base = scorevalue($scores->base_rawscore);
  $first = scorevalue($scores->first_rawscore);
  $second = scorevalue($scores->second_rawscore);
  $third = scorevalue($scores->third_rawscore);
  $fourth = scorevalue($scores->fourth_rawscore);
  $site = $scores->ste;
  $grade = $scores->testinglevel;
  $compbase = $cutoff[$grade]['base'];
  $compfirst = $cutoff[$grade]['first'];
  $compsecond = $cutoff[$grade]['second'];
  $compthird = $cutoff[$grade]['third'];
  $compfourth = $cutoff[$grade]['fourth'];
  
  debugPrint ("<tr><td>$id) Site: $site </td><td>$grade</td><td>$base ? $compbase </td><td>$first ? $compfirst</td><td>$second</td><td>$third</td><td>$fourth</td></tr>", "no");
  if($grade != 'sped' and  $grade != 'K' ) { 
	  $fullCount[$site]['base']['count']['value'] += $base == "" ? 0 : 1;
	  $fullCount[$site]['first']['count']['value'] += $first == "" ? 0 : 1;
	  $fullCount[$site]['second']['count']['value'] += $second == "" ? 0 : 1;
	  $fullCount[$site]['third']['count']['value'] += $third == "" ? 0 : 1;
	  $fullCount[$site]['fourth']['count']['value'] += $fourth == "" ? 0 : 1;
	
	  $fullCount[$site]['base']['count']['studentid'] .= $base == "" ? "" : $scores->studentid . ', ';
	  $fullCount[$site]['first']['count']['studentid'] .= $first == "" ? "" : $scores->studentid . ', ';
	  $fullCount[$site]['second']['count']['studentid'] .= $second == "" ? "" : $scores->studentid . ', ';
	  $fullCount[$site]['third']['count']['studentid'] .= $third == "" ? "" : $scores->studentid . ', ';
	  $fullCount[$site]['fourth']['count']['studentid'] .= $fourth == "" ? "" : $scores->studentid . ', ';
	  
	  $fullCount[$site]['base']['count']['studentshow'] .= $base == "" ? "" : $scores->fname . ' ' . $scores->lname . ': ';
	  $fullCount[$site]['first']['count']['studentshow'] .= $first == "" ? "" : $scores->fname . ' ' . $scores->lname . ': ';
	  $fullCount[$site]['second']['count']['studentshow'] .= $second == "" ? "" : $scores->fname . ' ' . $scores->lname . ': ';
	  $fullCount[$site]['third']['count']['studentshow'] .= $third == "" ? "" : $scores->fname . ' ' . $scores->lname . ': ';
	  $fullCount[$site]['fourth']['count']['studentshow'] .= $fourth == "" ? "" : $scores->fname . ' ' . $scores->lname . ': ';
	  
	  $fullCount[$site]['base']['on']['value'] += $base >= $compbase and $base != ""? 1 : 0;
	  $fullCount[$site]['first']['on']['value'] += $first >= $compfirst & $first != "" ? 1 : 0;
	  $fullCount[$site]['second']['on']['value'] += $second >= $compsecond & $second != "" ? 1 : 0;
	  $fullCount[$site]['third']['on']['value'] += $third >= $compthird & $third != "" ? 1 : 0;
	  $fullCount[$site]['fourth']['on']['value'] += $fourth >= $compfourth & $fourth != "" ? 1 : 0;
	
	  $fullCount[$site]['base']['on']['studentid'] .= ($base >= $compbase and $base != "") ?  $scores->studentid . ', ' : "";
	  $fullCount[$site]['first']['on']['studentid'] .= ($first >= $compfirst and $first != "") ?  $scores->studentid . ', ' : "";
	  $fullCount[$site]['second']['on']['studentid'] .= ($second >= $compsecond and $second != "") ?  $scores->studentid . ', ' : "";
	  $fullCount[$site]['third']['on']['studentid'] .= ($third >= $compthird and $third != "") ?  $scores->studentid . ', ' : "";
	  $fullCount[$site]['fourth']['on']['studentid'] .= ($fourth >= $compfourth and $fourth != "") ?  $scores->studentid . ', ' : "";
	
	  $fullCount[$site]['base']['on']['studentshow'] .= ($base >= $compbase and $base != "") ?  $scores->fname . ' ' . $scores->lname . ': ' : "";
	  $fullCount[$site]['first']['on']['studentshow'] .= ($first >= $compfirst and $first != "") ?  $scores->fname . ' ' . $scores->lname . ': ' : "";
	  $fullCount[$site]['second']['on']['studentshow'] .= ($second >= $compsecond and $second != "") ?  $scores->fname . ' ' . $scores->lname . ': ' : "";
	  $fullCount[$site]['third']['on']['studentshow'] .= ($third >= $compthird and $third != "") ?  $scores->fname . ' ' . $scores->lname . ': ' : "";
	  $fullCount[$site]['fourth']['on']['studentshow'] .= ($fourth >= $compfourth and $fourth != "") ?  $scores->fname . ' ' . $scores->lname . ': ' : "";
	}
}

function countURL ($site, $phase, $stg, $kind, $num) {
   return (buildGroupUrl($stg[$site][$phase][$kind]['studentid'],  
                 $stg[$site][$phase][$kind]['studentshow'], 
                 dv($stg[$site][$phase][$kind]['value'], "num"), $num));
}

debugPrint("</table>", "no");

//echo ("<br>FULLCOUNT ====> ");
//print_r ($fullCount);

//echo ("<br>ABOVECOUNT ====> ");
//print_r ($aboveCount);

$body .= "$selection<h2>Site To Site (numbers based on current enrollment 1 - 13+)</h2>
          <table border=1>
            <tr>
              <td><b>Site</b></td>
              <td colspan = 3 align=center><b>Baseline</b></td>
              <td colspan = 3 align=center><b>1st</b></td>
              <td colspan = 3 align=center><b>2nd</b></td>
              <td colspan = 3 align=center><b>3rd</b></td>
              <td colspan = 3 align=center><b>EOY</b></td>
            </tr>
            <tr>
              <td>&nbsp;</td>
              
              <td $w><b>On</b></td>
              <td $w><b>Total</b></td>
              <td $w><b>%</b></td>

              <td $w><b>On</b></td>
              <td $w><b>Total</b></td>
              <td $w><b>%</b></td>

              <td $w><b>On</b></td>
              <td $w><b>Total</b></td>
              <td $w><b>%</b></td>

              <td $w><b>On</b></td>
              <td $w><b>Total</b></td>
              <td $w><b>%</b></td>
              
              <td $w><b>On</b></td>
              <td $w><b>Total</b></td>
              <td $w><b>%</b></td>

            </tr>";
            
$sites = getSites('district', false);
$phases = array('base', 'first', 'second', 'third', 'fourth');

$i=0;
$j=0;
foreach ($sites as $site) {
  $s = $site['siteid'];
//  $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
    $color =  fmod($i++, 2) == 0 ? 'white' : '#E5E5E5';
  
  $body .= "<tr bgcolor=$color><td>$s</td>";

   foreach ($phases as $phase) {
     $full = countURL($s, $phase, $fullCount, 'count', $j++);
     $on = countURL($s, $phase, $fullCount, 'on', $j++);

     $fullnum = dv($fullCount[$s][$phase]['count']['value'], "num");
     $onnum = dv($fullCount[$s][$phase]['on']['value'], "num");

     $per = dv(round($onnum/$fullnum, 2)*100, "num");
  
     $body .= "<td $w>$on</td>
               <td $w>$full</td>
               <td $w>$per%</td>";
  }
  $body .= "</tr>";
}

$body .= "</table>";
  
include_once("template.inc");

?>