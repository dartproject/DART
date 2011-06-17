<?php

//$pval = getPivotValues("","","");

//$values = $pval['values'];

//$body = graphArea ($values['CD'], "CD Graph");

function C($i, $arr, $mval, $size, $other="") {

       $o = ($arr[$i]/$mval)*$size;
       if ($other != "") {
          $sub = $other['subject'];
//          $lvl = $other['level'];
          $studentID = $other['$studentID'];
          $grade = $other['$grade'];
          $siteID = $other['$siteID'];

          $linkpre = "<a href=index.php?cmd=drilldown&sub=$sub&lvl=$i&$studentID=$studentid&grade=$grade&siteID=$siteID ";
          $linkpost = "<a>";
         }
      $str = $arr[$i] . "<br>$linkpre<img valign=bottom align=center src = \"red.gif\" width = 12 height = $o border=0>$linkpost";
        return ($str);
}

function graphArea($cval , $title, $aux="") {
      $glen = 200;
      $boxsize = $glen;
      $side = $glen/4;
      $maxval = max($cval);
      $v1 = $maxval;
      $v2 = $maxval * .75;
      $v3 = $maxval * .5;
      $v4 = $maxval * .25;
      $tick = 10;
      $widthx = 30;
      
      $chart = "<table border=4><tr><td align=center>$title<br><br><table border = 0 cellspacing=0 cellpadding = 0 valign=bottom>
      
      <tr valign=bottom align=center><td valign=top align=right>&nbsp;<td rowspan=5>" . C("1", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("2", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("3", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("4", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("5", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("6", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("7", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("8", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("9", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("10", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("11", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>" . C("12", $cval, $maxval, $boxsize, $aux) . "</td><td rowspan=5>&nbsp;</td></tr>
            
      <tr><td valign=top align=right><div><img src = \"red.gif\" width = $tick height = 1 align = top></div><div>$v1 <img src = \"red.gif\" width = 1 height = $side align=top></div></td></tr>
      
      <tr><td valign=top align=right><div><img src = \"red.gif\" width = $tick height = 1 align = top></div><div>$v2 <img src = \"red.gif\" width = 1 height = $side align=top></div></td></tr>

      <tr><td valign=top align=right><div><img src = \"red.gif\" width = $tick height = 1></div><div>$v3 <img src = \"red.gif\" width = 1 height = $side align = top></div></td></tr>

      <tr><td valign=top align=right><div><img src = \"red.gif\" width = $tick height = 1></div><div>$v4 <img src = \"red.gif\" width = 1 height = $side align = top></div></td></tr>
                        
      <tr align=center ><td width = $widthx></td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>1</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>2</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>3</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>4</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>5</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>6</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>7</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>8</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>9</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>10</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>11</td><td width = $widthx><img src = \"red.gif\" width = $widthx height = 1 align = top>12</td></tr>
      </table></td></tr></table>";
      

      return $chart;
}

// include ("template.inc");

?>
