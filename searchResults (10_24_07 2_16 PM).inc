<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

global $db;

$defaultLimit = 50;  

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
//    alert ('length' + elts_cnt);
//    if(elts_cnt == 0) { return false; }
    for (var i = 0; i < elts_cnt; i++) {
        if(elts[i].checked == true) { return true; }
    } 
    alert ('There are no students checked.');
    return false;
}

function nextSubmit() { document.nextForm.submit(); }

function prevSubmit() { document.prevForm.submit(); }
";
if($_POST['continue'] == "yes") {
    $limit = $_POST['limit'];
    if ($limit < 1) { $limit = $defaultLimit; }
    $start = $_POST['start'];
    $limitstart = $start-1;
    $total = $_POST['total'];
    $sql = $_POST['sql'];
    $sql = URLdecode($sql);
    $sql1 = $sql . " order by lname LIMIT $limitstart, $limit";
    $students = $db->get_results($sql1, ARRAY_A); 

} else {
    $limit = $defaultLimit; 
    $start = 1; 
    //$sql = getSearchSQL($HTTP_POST_VARS);
//    $values = getStudentSearchResults($HTTP_GET_VARS, $start-1, $limit);
    $values = getStudentSearchResults($HTTP_POST_VARS, $start-1, $limit);
    $students = $values['list'];
    $total = $values['total'];
    $sql = $values['sql'];
}
    
    $end = min($total,$start+$limit-1);
    
    if($start+$limit > $total) {
      $nextstart = $start;
    } else {
      $nextstart = $start+$limit;
    }
    if($start-$limit > 0) {
      $prevstart = $start-$limit;
    } else {
      $prevstart = $start;
    }

$navigate = "&nbsp;";

$navigate1 = "<table border=0 valign=bottom>
             <tr valign=bottom><td valign=top>DART Search Results - (</td><td >
             <form method=\"POST\" action=\"index.php?cmd=searchResults\" name='prevForm'>
             <input type=hidden name=start value=$prevstart>
             <input type=hidden name=continue value=yes>
             <input type=hidden name=sql value=" . URLEncode($sql) . ">
             <input type=hidden name=total value=$total>
             <input type=hidden name=limit value=$limit>
             <a href=\"javascript:prevSubmit()\">Prev</a>
</form></td><td valign=bottom>
            <form method=\"POST\" action=\"index.php?cmd=searchResults\" name='nextForm'>
             <input type=hidden name=start value=$nextstart>
             <input type=hidden name=continue value=yes>
             <input type=hidden name=sql value=" . URLEncode($sql) . ">
             <input type=hidden name=total value=$total>
             <input type=hidden name=limit value=$limit>
             <a href=\"javascript:nextSubmit()\">Next</a>
             </form>
             </td><td valign=top>$start to $end from $total)</td></tr></table>";
//             <input type=button value=NEXT onclick='submit()'></form>

$checkall = "<div align=\"left\">
																			&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', true); return false;\" class=\"action\">Check All</a>&nbsp;/&nbsp;<a href=\"javascript: ;\" onclick=\"setCheckboxes('fieldsForm', false); return false;\" class=\"action\">UnCheck All</a>
																		<i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Group'> <input type=submit name=cmd2 onClick='javascript: return checkChecks();' value='Export'>
               </div>";
$checkall = $total == 0 ? "" : $checkall;

function computeStatus($status) {
  if($status=='Active') { return ("<font color=\"#009966\">$status</font>"); }
  else { return ("<font color=red>$status</font>");}
}
function computeActivation($status) {
  if($status=='Active') { 
   $str = "<a href=\"http://www.bssd.org/transfer_form.shtml\" target=_blank>Deactivate</a>"; }
  else {
   $str = "<a href=\"http://www.bssd.org/enrollment_form.shtml\" target=_blank>Enroll</a>";}
  return $str;
}
$advHeader = Privilege(A6) == 'district' ? "<td>Edit</td>" : "";
$i = 0; 
 foreach ($students as $student) {   
      $id = $student['studentid'];
      $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
      $adv = Privilege(A6) == 'district' ?
            "<td><a href=\"index.php?cmd=StudentEdit&id=" . $student['studentid'] . "\">>>Edit</a></td>" :
            "";
//       $adv = "<td>t</td>";
      $results .= "			<tr bgcolor=$color>
																	<td align=\"center\" nowrap><input type=\"checkbox\" name=\"studentID[]\" value=\"$id\" class=\"radio\"></td>
																	<td nowrap><a href=\"index.php?cmd=toggleStudent&p1=". $student['studentid'] . "\">". $student['fname'] . " " . $student['lname'] . "</a></td>
																	<td>
																		<div align=\"center\">
																			" . $student['studentid'] . "</div>
																	</td>
																	<td>
																		<div align=\"center\">
																			" . $student['alaskaid'] . "</div>
																	</td>
																	<td>
																		<div align=\"center\">
																		" .	$student['site'] ."</div>
																	</td>
																	<td>
																		<div align=\"center\">
																			2006-07:Q1</div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			" .	$student['grade'] ."</div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			" .	age($student['bday']) ."</div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			" .	computeStatus($student['status']) ."</div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			" .	$student['code'] ."</div>
																	</td>
																	<td align=\"center\" nowrap>
																		<div align=\"center\">
																			<a href=\"index.php?cmd=toggleStudent&p1=". $student['studentid'] . "\">Details</a> >> " . computeActivation($student['status']) . "</div>
																	</td>
																	$adv
																</tr>";
}

$body ="	<div align=\"center\">
						<form name=\"fieldsForm\" action=\"index.php?cmd=handleGroup\" method=\"post\" >
							<input type=\"hidden\" name=\"action\" value=\"bulk_action\">
							<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
								<tr>
									<td>
										<div align=\"left\">
											<br>
											<div align=\"left\">
												<font size=\"4\" color=\"#cc0000\">DART Search Results</font><br>
											</div>
											<div class=\"noteimportant\">These are the records in the system that match your search query.  By using the links below you can select individuals to form new groups based on these criteria, add a person to an existing group you have access to, view his or her acount details, print reports, or export their data. You can resort the results by clicking the top of each column, and use the controls at the bottom of the screen to perform actions or change how many records you view on a screen.  </div>
										</div>
									</td>
								</tr>
								<tr>
									<td>
										<div align=\"center\">
											<br>
											<font size=\"4\" color=\"#cc0000\">Here's What I Found... </font><br>
											<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">
												<tr>
													<td width=\"100%\">
															<table width=\"100%\" cellpadding=\"1\" cellspacing=\"1\" border=\"0\" class=\"listtable\">
																<tr>
																	<td colspan=\"9\" bgcolor=\"#FFFFFF\"><img src=\"http://dart.bssd.org/images/1pix.gif\" width=\"1\" height=\"5\" border=\"0\" alt=\"\"></td>
																</tr>
																<tr bgcolor=\"#FFFFFF\">
																	<td colspan=\"9\" align=\"right\" class=\"searchhead\" nowrap>$navigate</td>
																</tr>
																<tr>
																	<td colspan=\"9\" bgcolor=\"#FFFFFF\"><img src=\"http://dart.bssd.org/images/1pix.gif\" width=\"1\" height=\"5\" border=\"0\" alt=\"\"></td>
																</tr>
																<tr class=\"listhead\">
																	<td width=\"2%\"></td>
																	<td align=\"center\" nowrap><a href=\"(EmptyReference!)\">&nbsp;Name&nbsp;</a></td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">Student Number</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">AK Student ID</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">School Site</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">Time Frame</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">Testing<br>Grade</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">Age</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">Status&nbsp;</a></div>
																	</td>
																	<td align=\"center\">
																		<div align=\"center\">
																			<a href=\"(EmptyReference!)\">Code&nbsp;</a></div>
																	</td>
																	<td align=\"center\" nowrap>
																		<div align=\"center\">
																			&nbsp;Action&nbsp;</div>
																	</td>
																	$advHeader
																</tr>

$results

                            </table>
															<table align=\"center\" width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">
																<tr>
																	<td colspan=\"2\"><img src=\"http://dart.bssd.org/images/1pix.gif\" width=\"1\" height=\"5\" border=\"0\" alt=\"\"></td>
																</tr>
																<tr>
																	<td valign=\"middle\" nowrap>
																	$checkall
																	</td>
																	<td align=\"right\">$navigate</td>
																</tr>
															</table>
															<input type=\"hidden\" name=\"back_url\" value=\"\">

													</td>
												</tr>
											</table>
										  </form>
										  <div align=left>
										     <table width = 100% border=0 cellpadding = 0 cellspacing = 0 valign=bottom>
                         <tr><td colspan=2>&nbsp;</td></tr><tr><td>
                         <form method=\"POST\" action=\"index.php?cmd=searchResults\" name='displaylimit'>
                           <input type=hidden name=start value=1>
                           <input type=hidden name=continue value=yes>
                           <input type=hidden name=sql value='" . URLEncode($sql) . "''>
                           <input type=hidden name=total value=$total>
                           <input type=text size=3 name=limit value=$limit>
                           <input type=submit name=submit value=\"Display Results\">
                        </form></td><td align=right>$navigate1</td></tr></table>
										  </div>
											<br>
										</div>
									</td>
								</tr>
							</table>
						</div>";

include ("template.inc");

?>
