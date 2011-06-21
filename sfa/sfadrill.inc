<?php

$grade = $_GET['grade'];
$test = $_GET['test'];
$score = $_GET['score'];
$listid = $_GET['listid'];
$drillcmd = $_GET['drillcmd'];
$hotcmd = $_GET['hotcmd'];

if ($drillcmd == 'base' or $drillcmd == 'first' or 
    $drillcmd == 'second' or $drillcmd == 'third' or 
    $drillcmd == 'fourth') {
   $students = GetStudentNoScore($drillcmd, $listid);
} else if ($hotcmd == 'base' or $hotcmd == 'first' or 
    $hotcmd == 'second' or $hotcmd == 'third' or 
    $hotcmd == 'fourth') {
   $students = GetHotList($listid, $hotcmd);
} else {
   $students = GetStudentGroup($grade, $test, $score, $listid);
}

$js = "function setCheckboxes(the_form, do_check)
{
 
    var elts      = (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
                  ? document.forms[the_form].elements['studentID[]']
                  : (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
          ? document.forms[the_form].elements['studentID[]']
          : document.forms[the_form].elements['studentID[]'];
    var elts_cnt  = (typeof(elts.length) != 'undefined')
                  ? elts.length
                  : 0;

    if (elts_cnt) {
        for (var i = 0; i < elts_cnt; i++) {
            elts[i].checked = do_check;
        } // end for
    } else {
        elts.checked        = do_check;
    } // end if... else

    return true;
} // end of the 'setCheckboxes()' function

function checkChecks () {
    var elts = document.forms['fieldsForm'].elements['studentID[]'];
    var elts_cnt = elts.length;
    for (var i = 0; i < elts_cnt; i++) {
        if(elts[i].checked == true) { return true; }
    } 
    alert ('There are no students checked.');
    return false;
}

function nextSubmit() { document.nextForm.submit(); }

function prevSubmit() { document.prevForm.submit(); }
";

function V($val) { 
  if ($val == "") {$val = "&nbsp;"; } 
  return ($val); 
}

//$students = GetStudentGroup($grade, $test, $score, $listid);

$total = count($students);

$body = "<table witdh=90%><tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href=index.php?module=sfa&cmd=gs&listid=$listid>Return To SFA</a> [Results $total]<br>
<form name=\"fieldsForm\" action=\"index.php?cmd=handleGroup\" method=\"post\" >
		<input type=\"hidden\" name=\"action\" value=\"bulk_action\">

  <table width=100% border=0><tr><th></th><th>Name</th><th>Student<br>Number</th><th>AK Student ID</th><th>School</th><th>Testing Grade</th><th>TIL</th><th>QPI<th>View</th></tr>";

$i = 0;
foreach ($students as $s) {
    $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
    $name = $s->lname . ", " . $s->fname;
    $akid = V($s->alaskaid);
    $school = $s->site;
    $grade = $s->grade;
    $TIL = $s->TIL;
    $QPI = $s->QPI;
    $sid = $s->studentid;
    $link = "<a href=index.php?cmd=toggleStudent&p1=" . $sid . ">edit</a>";
    $body .= "<tr bgcolor=$color><td><input type=\"checkbox\" name=\"studentID[]\" value=\"$sid\" class=\"radio\"></td><td>$name</td><td>$sid</td><td>$akid</td><td>$school</td><td>$grade</td><td>$TIL</td><td>$QPI</td><td>$link</td></tr>";

//  $body .= "<tr><td>" . V($s->lname) . " " . V($s->fname) . "</td><td>" . V($s->grade) . "</td><td>" . V($s->subject) . "</td><td>" . V($s->numlevel) . "</td><td>" . V($s->site) . "</td></tr>";
}

$body .= "</table>";

$body .= "<div align=\"left\">
		&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', true); return false;\" class=\"action\">Check All</a>&nbsp;/&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', false); return false;\" class=\"action\">UnCheck All</a>
	<i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Group'> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Export'>
  </div></form>
  
  </td><td>&nbsp;</td></tr></table>";

include_once("template.inc");

?>
