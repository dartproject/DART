<?php

debugPrint ("HOPE THIS IS HERE");

$A9Priv = Privilege(A9);

$listid = $_GET['listid'];
$showmissing = $_GET['showmissing'];
$print = $_GET['print'];
$final = "";
$year = isset($_GET['year']) ? $_GET['year']: $CurrentYear;
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=gs&listid=$listid&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
		$optionYear
  </select>
  </form>";
  
debugPrint("<br>ListID: " . $listid);

$scores = GetGroupScores($listid, $year);
$hotlist = setupHotlist();
$linelist = setupLines();
$totalCount = $scores['count'];
$c1 = "#ffbfd1";
$c2 = "#ffcf96";
$c3 = "#ffffb5";
$c4 = "#aee67c";
$c5 = "b5e0ff";
$c1b = "#ffbfd1";
$c2b = "ffcf96";
$c3b = "#ffffb5";
$c4b = "#aee67c";
$c5b = "b5e0ff";

if ($print != "t") { 
	$body .= "<a href=index.php?module=sfa&cmd=gs&showmissing=$showmissing&listid=$listid&year=$year&print=t target=_blnk>Printer Friendly Page</a>$selection<p>";
}

if($A9Priv != 'none') {

$scs = array ("sped", "PK", "KC", "KR", "1-5", "6-10", "11-15", "16-20", "21-25", "26-31", "32-37", "38-42", "43-48", "BR", "2.1", "2.2", "3.1", "3.2", "4.1", "4.2", "5.1", "5.2", "6.1", "6.2", "7.1", "7.2", "8.1", "8.2", "9.1", "9.2", "10.1", "10.2", "11.1", "11.2", "12.1", "12.2", "any") ;

$noscores = GetNoScores($listid, $year);
$nob = $noscores['bcount'];
$no1 = $noscores['fcount'];
$no2 = $noscores['scount'];
$no3 = $noscores['tcount'];
$no4 = $noscores['fourthcount'];

$body .= "Total in List: $totalCount 
No BASE score: <a href=index.php?module=sfa&cmd=drilldown&drillcmd=base&listid=$listid><b> $nob</b></a>  No 1st score: <a href=index.php?module=sfa&cmd=drilldown&drillcmd=first&listid=$listid><b> $no1</b></a>  No 2nd score: <a href=index.php?module=sfa&cmd=drilldown&drillcmd=second&listid=$listid><b> $no2</b></a>  No 3rd score: <a href=index.php?module=sfa&cmd=drilldown&drillcmd=third&listid=$listid><b> $no3</b></a>  No 4th score: <a href=index.php?module=sfa&cmd=drilldown&drillcmd=fourth&listid=$listid><b> $no4</b></a>  <br><br>";
//debugPrint("<br>Score Array: " . print_r($scores, false));

$site = ($A9Priv == 'site') ? $currentMySite : '';
//echo $site;
$hotlistb = GetHotlist($listid, 'base', $year, $site);
$hob = count($hotlistb);
$hotlist1 = GetHotlist($listid, 'first', $year, $site);
$ho1 = count($hotlist1);
$hotlist2 = GetHotlist($listid, 'second', $year, $site);
$ho2 = count($hotlist2);
$hotlist3 = GetHotlist($listid, 'third', $year, $site);
$ho3 = count($hotlist3);
$hotlist4 = GetHotlist($listid, 'fourth', $year, $site);
$ho4 = count($hotlist4);

$body .= "Hot List: 
BASE: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=base&listid=$listid><b> $hob</b></a>  >> 1st: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=first&listid=$listid><b> $ho1</b></a>  >> 2nd: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=second&listid=$listid><b> $ho2</b></a>  >> 3rd: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=third&listid=$listid><b> $ho3</b></a>  >> 4th: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=fourth&listid=$listid><b> $ho4</b></a>  <br><br>";


$spb = dv($scores['any']['base']['sped']['value'], "num");
$sp1 = dv($scores['any']['first']['sped']['value'], "num");
$sp2 = dv($scores['any']['second']['sped']['value'], "num");
$sp3 = dv($scores['any']['third']['sped']['value'], "num");
$sp4 = dv($scores['any']['fourth']['sped']['value'], "num");

$body .= "Sped: 
BASE: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=base&listid=$listid><b> $spb</b></a>  >> 1st: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=first&listid=$listid><b> $sp1</b></a>  >> 2nd: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=second&listid=$listid><b> $sp2</b></a>  >> 3rd: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=third&listid=$listid><b> $sp3</b></a> >> 4th: <a href=index.php?module=sfa&cmd=drilldown&hotcmd=fourth&listid=$listid><b> $sp4</b></a>  <br><br>";

} else {
$scs = array ("PK", "KC", "KR", "1-5", "6-10", "11-15", "16-20", "21-25", "26-31", "32-37", "38-42", "43-48", "BR", "2.1", "2.2", "3.1", "3.2", "4.1", "4.2", "5.1", "5.2", "6.1", "6.2", "7.1", "7.2", "8.1", "8.2", "9.1", "9.2", "10.1", "10.2", "11.1", "11.2", "12.1", "12.2", "any") ;

}
$hi = 0;
function H($grade, $test, $score) {
  global $scores, $listid, $hotlist, $final, $hi;

  $value = $scores[$grade][$test][$score]['value'];
  $students = str_replace("'", "\'", $scores[$grade][$test][$score]['student']);
  debugPrint("<br>Value:$grade$test$score-$value");
  if($value == "") {
    $results = "-";
  } else {
     $results = "<a href=index.php?module=sfa&cmd=drilldown&grade=$grade&test=$test&score=$score&listid=$listid onMouseOver=\"this.T_WIDTH=900;return escape('$students')\">$value</a>";
//       $results = buildGroupUrl($scores[$grade][$test][$score]['ids'], 
//      							$students,
//      							$scores[$grade][$test][$score]['value'],
//      							$hi++);
  }
//  $results = "--";
  return($results);
}

$w = 20;

$grds = array ("PreK", "K", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"); 
$periods = array("base", "first", "second", "third", "fourth");
$colors = array ("$c1","$c2","$c3","$c4","$c5"); 
//$scs = array ("sped", "PK", "KC", "KR", "1-5", "6-10", "11-15", "16-20", "21-25", "26-31", "32-37", "38-42", "43-48", "BR", "2.1", "2.2", "3.1", "3.2", "4.1", "4.2", "5.1", "5.2", "6.1", "6.2", "7.1", "7.2", "8.1", "8.2", "9.1", "9.2", "10.1", "10.2", "11.1", "11.2", "12.1", "12.2", "any") ;

$body .= "<table border=1 cellpadding=0 cellspacing=0 width=2000>";
	 $body .= "<tr><th></th>";
     foreach ($scs as $sc) {
	  	 $body .= "<th><center>$sc</center></th>";
     }
	$body .= "</tr>";
	foreach ($grds as $grd) {
		  $i = 0;
		  foreach ($periods as $period) {
		  	 $color = $colors[$i];
			 $body .= "<tr bgcolor=$color><th align=right>$grd-$period</th>";
			 $i++;
			 foreach ($scs as $sc) {
			    $class = $linelist[$grd][$period][$sc] ? $linelist[$grd][$period][$sc] : "plain";
			 	if($hotlist[$grd][$period][$sc] == "X") {
				   $body .= "<td class=$class><center><font color=red>" .  H($grd, $period, $sc) . "*<font></center></td>";
			 	} else {
				   $body .= "<td class=$class><center>" .  H($grd, $period, $sc) . "</center></td>";
				}
			 }
			 $body .= "</tr>";
		  }
	}	
	$i = 0;
	foreach ($periods as $period) {
		 $color = $colors[$i];
		 $body .= "<tr bgcolor=$color><th align=right>Total-$period</th>";
		 $i++;
		 foreach ($scs as $sc) {
				 $body .= "<td><center>" .  H('any', $period, $sc) . "</center></td>";
		 }
 $body .= "</tr>";
  }

$body .= "</table>";



//debugPrint("BODY:  $body");

if ($print != "t") { 
	include_once ("template.inc");
} else {

echo "<html>
	<head>
	<title>$title </title>
	<link rel=\"stylesheet\" href=\"css/dart.css\" type=\"text/css\">
	<script>
	$js
	</script>
	</head>
	<body>
	$body
	</body>
	</html>";
}

?>

