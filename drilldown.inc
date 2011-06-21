<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$studentID = $_GET['studentID'];
$grade = $_GET['grade'];
$siteID = $_GET['siteID'];
$sub = $_GET['sub'];
$siteID = $_GET['siteID'];
$lvl = $_GET['lvl'];

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

$students = getPivotStudents($studentID, $grade, $siteID, $sub, $lvl);
$total = count($students);

$body = "<table witdh=90%><tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href=index.php?cmd=pivot&siteID=$siteID&studentID=$studentID&grade=$grade>Return To Pivot</a> [Results $total]<br>
<form name=\"fieldsForm\" action=\"index.php?cmd=handleGroup\" method=\"post\" >
		<input type=\"hidden\" name=\"action\" value=\"bulk_action\">

  <table width=100% border=0><tr><th></th><th>Name</th><th>Student<br>Number</th><th>AK Student ID</th><th>School</th><th>Content<br>Area</th><th>Level</th><th>Testing<br>Grade</th><th>Age</th><th>TIL</th><th>QPI<th>View</th></tr>";

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
    $lvl = $s->level;
    $age = age($s->bday);
    $link = "<a href=index.php?cmd=toggleStudent&p1=" . $sid . ">edit</a>";
    $body .= "<tr bgcolor=$color><td><input type=\"checkbox\" name=\"studentID[]\" value=\"$sid\" class=\"radio\"></td><td>$name</td><td>$sid</td><td>$akid</td><td>$school</td><td>$sub</td><td>$lvl</td><td>$grade</td><td>$age</td><td>$TIL</td><td>$QPI</td><td>$link</td></tr>";

//  $body .= "<tr><td>" . V($s->lname) . " " . V($s->fname) . "</td><td>" . V($s->grade) . "</td><td>" . V($s->subject) . "</td><td>" . V($s->numlevel) . "</td><td>" . V($s->site) . "</td></tr>";
}

$body .= "</table>";

$body .= "<div align=\"left\">
		&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', true); return false;\" class=\"action\">Check All</a>&nbsp;/&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', false); return false;\" class=\"action\">UnCheck All</a>
	<i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Group'> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Export'>
  </div></form>
  
  </td><td>&nbsp;</td></tr></table>";

include("template.inc");
?>
