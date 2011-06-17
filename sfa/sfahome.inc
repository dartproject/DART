<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$A9Priv = Privilege(A9);
$A7Priv = Privilege(A7);

$mylists = getMyList($currentUserID);
$grouplists =  getMyList($currentUserID, $currentMySite);

$year = isset($_GET['year']) ? $_GET['year']: $CurrentYear;
$optionYear = getYearOption($year);
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=sfahome&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      $optionYear
  </select>
  </form>";

$selectList .= "<select name=\"listid\">";

foreach($mylists as $my) {
  $lid = $my['listid'];
  $lname = $my['listname'];
  $selectList .= "<option value=\"$lid\">$lname</option>";
  }

$selectList .= "<option value=\"\">---- Shared List ---</option>";

foreach($grouplists as $my) {
  $lid = $my['listid'];
  $lname = $my['listname'];
  $selectList .= "<option value=\"$lid\">$lname</option>";
  }

$selectList .= "</select>";

$site = $A7Priv == 'site'? $currentMySite : 'all' ;
$readingA = getReadingArray($site);

$readingOption = "<select name=\"teacher\" id=\"teacher\">" . 
                       GetOptionList($readingA, "") . 
                       "</select>";
                       
$tutorA = getTutorArray($site);

$tutorOption = "<select name=\"tutor\" id=\"tutor\">" . 
                       GetOptionList($tutorA, "") . 
                       "</select>";
                       
$quarterOptions = "<select name=\"quarter\">
                     <option value=first>First</option>
                     <option value=second>Second</option>
                     <option value=third>Third</option>
                     <option value=fourth>Fourth</option>
                   </select>";
$quarterOptionsWBase = "<select name=\"quarter\">
                     <option value=base>Base</option>
                     <option value=first>First</option>
                     <option value=second>Second</option>
                     <option value=third>Third</option>
                     <option value=fourth>Fourth</option>
                   </select>";
if($A9Priv != 'none') {
  $input ="<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=sfainput>
  <input type=hidden name=year value=$year>
    <td>Data Entry Screen</td><td>$selectList</td><td colspan=2><input type=submit name=submit></td>
  </form>
</tr>";
 $gradesumall = "<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=gs>
  <input type=hidden name=showmissing value=yes>  
  <input type=hidden name=year value=$year>
    <td>GRADE Summary Form with<br>Missing Data and Hot List</td><td>$selectList</td><td colspan=2><input type=submit name=submit></td>
  </form>
</tr>";
}
 
$body .= "
<div class=\"notetip\">
Welcome to the BSSD Reading Module. Our reading program for all of 
the students in reading levels 1-8 is Success for All. Students that 
are in reading levels 9-12 are instructed in reading in either stand 
alone reading classes or through their content area classes.<p>

The beauty of this module, is that at a glance you can see which of 
the students in a grade(s), school or district are reading on or 
above grade level.<p>

The assessments used to pace students on the Grade Summary Form has 
been aligned to the state mandated assessments, so we can also use 
this form to predict student proficiency on those state assessments.<p>

Only facilitators are able to enter/edit reading data, however we 
welcome all users to view the grade summary forms!
</div>
<center>$selection</center><table align=center border=1>
$input
<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=gs>
  <input type=hidden name=year value=$year>
    <td>GRADE Summary Form</td><td>$selectList</td><td colspan=2><input type=submit name=submit></td>
  </form>
</tr>
$gradesumall
<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=wing>
  <input type=hidden name=year value=$year>
    <td>Class Progress-Wings-RE</td><td>$readingOption</td><td>$quarterOptions</td><td><input type=submit name=submit></td>
  </form>
</tr>

<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=root>
  <input type=hidden name=year value=$year>
    <td>Class Progress-Roots</td><td>$readingOption</td><td>$quarterOptions</td><td><input type=submit name=submit></td>
  </form>
</tr>

<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=tutor>
  <input type=hidden name=year value=$year>
    <td>Tutor Profile</td><td>$tutorOption</td><td>$quarterOptions</td><td><input type=submit name=submit></td>
  </form>
</tr>

<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=rrprofile>
  <input type=hidden name=year value=$year>
    <td>Roots Reading Profile Report</td><td>$selectList</td><td>$quarterOptions</td><td><input type=submit name=submit></td>
  </form>
</tr>

<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=stgreport>
  <input type=hidden name=year value=$year>
    <td>Short Term Goals</td><td>$selectList</td><td colspan=2><input type=submit name=submit></td>
  </form>
</tr>

<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=sfa8wkreport>
  <input type=hidden name=year value=$year>
    <td>8 Week Assessment</td><td>$selectList</td><td colspan=2><input type=submit name=submit></td>
  </form>
</tr>
<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=sfahotlist>
  <input type=hidden name=year value=$year>
    <td>HotList Report</td> <td>$selectList</td><td>$quarterOptionsWBase</td><td><input type=submit name=submit></td>
  </form>
</tr>

<tr>
  <form action=index.php>
  <input type=hidden name=module value=sfa>
  <input type=hidden name=cmd value=stsreport>
  <input type=hidden name=year value=$year>
    <td>Site by Site</td><td colspan=3><input type=submit name=submit></td>
  </form>
</tr>

</table>";

include_once("template.inc");

?>
