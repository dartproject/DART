<?php

debugPrint ("Here");
/**
$stages[0]['stage'] = 'base';
$stages[0]['name'] = 'Baseline';
$stages[0]['color'] = "#ffbfd1";
 
$grades = ('K', '1', '2', '3', '4', '5');

//$scores = GetAllGroupScores();


debugPrint ("Here2");
foreach ($stages as $stage) {
    $name = $stage['name'];
    $line0 = '<td>$name</td>';    
    $line1 = '<td>Total# Kids</td>';
    $line2 = '<td>$#f of Kids on<br>Grade Level</td>';
    $line3 = '<td>% of Kids on<br>GradeLevel</td>';
    $totct = 0;
    $totadv = 0;

   foreach ($grades as $grade) {
      $ct = $scores[$stage][grade]['count'];
      $abv = $scores[$stage][grade]['above'];
      $per = $abv/$ct;
      $totct += $ct;
      $totabv += $per;
      
      $line0 .= "<td>$grade</td>";
      $line1 .= "<td>$ct</td>";
      $line2 .=  "<td>$abv</td>";
      $line3 .=  "<td>$per</td>";
      
   }
   
   $body .= "<tr bgcolor=$color>$line0</tr>
             <tr>$line1</tr>
             <tr>$line2</tr>";
}

include_once ("template.inc");
**/

?>