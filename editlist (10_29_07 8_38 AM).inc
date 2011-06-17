<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$A11Priv = Privilege(A11);
$A14Priv = Privilege(A14);
$A7Priv = Privilege(A7);
$A17Priv = Privilege(A17);

if($A11Priv == 'none') { NoPriv("denied Ad Hoc List", ""); }

/*
$head = "<SCRIPT LANGUAGE=\"JavaScript\" SRC=\"lib/multiselect.js\"></SCRIPT>
	<SCRIPT LANGUAGE=\"JavaScript\">
";
*/
$mylists = getMyList($currentUserID, 'all');
if($p1 == "") {
  $p1 = $mylists[0]['listid'];
  if($p1 == "") {
      $p1 = newList($userID);;
  }
}
$list = getListItems($p1);
$listInfo = getListInfo($p1);
$listname = $listInfo['listname'];
$listType = $listInfo['type'];
debugPrint("LIST TYPE: " . $listType);

$sfaexport .= $A7Priv == 'none' ? '' : "<td>
			<form name=\"exportlist\" id=\"exportlist\" method=\"post\" action=\"index.php?cmd=exportlist&listid=$p1&type=sfa\">
			<input name=\"export\" type=\"submit\" id=\"export\" value=\"SFA Export\">
			</form>
		</td>";

function getShared($listid) {
	global $db;

	$sql = "select user.userid, name from user, listshare where listid=$listid and user.userid = listshare.userid";
//	echo $sql;
	$results = $db->get_results ($sql, ARRAY_A);
	return($results);
}
if ($A17Priv <> 'none' and $listType == 'Private') {
	if($_GET['attSubmit'] <> "") {
		$am = $_GET['am'];
		$pm = $_GET['pm'];
		$db->get_results ("Update lists set am = '$am', pm = '$pm' where listid = '$p1'");
		$db->get_results ("Delete from listshare where listid = '$p1'");
		foreach ($_GET['test'] as $selection) {
//			echo $selection , "<br>";
			$db->get_results ("Insert into listshare set listid = '$p1', userid = $selection");
		}
	}
	${"am_" . $listInfo['am']} = "checked";
	${"pm_" . $listInfo['pm']} = "checked";
	$selected = getShared($p1);
	foreach ($selected as $user) {
		$names .= $user['name'] . "<br>";
		$show[$user['userid']] = 'selected';
	}
	$users = getAllUsers();
	$select = "<select name=\"test[]\" id=\"test\" size=10 MULTIPLE>" . 
                       GetMultipleOptionList($users, $show) . 
                       "</select>";
	$makeampm = "<hr><form name=\"myform\" action=\"index.php\" method=\"GET\">
			<div align=\"center\">
			<input type=hidden name=cmd value=editlist>
			<input type=hidden name=p1 value=$p1>
			<b>Attendance Period</b><br>
			<input type=\"checkbox\" name=\"am\" value=\"1\" $am_1> am
			<input type=\"checkbox\" name=\"pm\" value=\"1\" $pm_1> pm<br>
			<b>Users With Access</b><br>
			$select<br>
			<input type=submit value=\"Make Official Attendance List\" name=attSubmit>
			<br><br><b>Curent Users Who Share The List</b><br>
			$names
			</div>
			</form>";

}


$student = getPotentialListItems($userID, Privilege(A11));
//$student = $student2;

if($list != "") {
   $showlist = showListOptional($list);
   $showcount = count($list);
} else {
 $showlist = '<option value = "">{Empty Group}</option>';
 $showcount = 0;
}
function arr_diff($a1,$a2){
  foreach($a1 as $k=>$v){
   unset($dv);
   if(is_int($k)){
     // Compare values
     if(array_search($v,$a2)===false) $dv=$v;
     else if(is_array($v)) $dv=arr_diff($v,$a2[$k]);
     if($dv) $diff[]=$dv;
   }else{
     // Compare noninteger keys
     if(!$a2[$k]) $dv=$v;
     else if(is_array($v)) $dv=arr_diff($v,$a2[$k]);
     if($dv) $diff[$k]=$dv;
   }   
  }
  return $diff;
}
/********* array difference code that could be improved but works *********/
function my_serialize(&$arr,$pos){
  $arr = serialize($arr);
}

function my_unserialize(&$arr,$pos){
  $arr = unserialize($arr);
}
if(count($list) != 0) {
     //make a copy
    $first_array_s = $student;
    $second_array_s = $list;
    
    // serialize all sub-arrays
    array_walk($first_array_s,'my_serialize');
    array_walk($second_array_s,'my_serialize');
    
    // array_diff the serialized versions
    $diff = array_diff($first_array_s,$second_array_s);
    
    // unserialize the result
    array_walk($diff,'my_unserialize');
} else {
    $diff = $student;
}
/********* array difference code that could be improved but works *********/
debugPrint("<p>Potential: " . print_r($student, TRUE) . "<br><br>");
debugPrint("List: " . print_r($list, TRUE) . "<br><br>");
debugPrint("Diff: " . print_r($diff, TRUE) . "<br><br>");

$showpotential = showListOptional($diff);
$potentialCount = count($diff);

$body .= "<script>
<!--
function confirm_delete(id)
{
  input_box=confirm(\"Click OK to delete or Cancel\");
  if (input_box==true)
  { 
     window.location=\"index.php?cmd=deletelist&p1=\" + id;
     return false;
  } else {
     return false;
  }
}
-->
 </script>";

/*************** UPDATE LIST ******************/

$updateList = "<form name=editList action=index.php method=get>
<input type=hidden name=cmd value=editlist>
<select name=\"p1\" onChange=\"submit()\">";

foreach($mylists as $my) {
  $lid = $my['listid'];
  $lname = $my['listname'];
  $updateList .= "<option value=\"$lid\" " . selected ($lid, $p1) . ">$lname</option>";
  }

$updateList .= "</select> Select to edit list</form>";

/*************** UPDATE LIST ******************/
$sites = getSitesOptions($listType, $A14Priv);

$typeBody = "<form style=\"margin-bottom:0;\" name=updateType method=post action=\"index.php?cmd=updateListType\">
<input type=\"hidden\" name=\"p1\" value=$p1>
<input type=hidden name=userid value=$currentUserID>
<select name=p2 onChange='submit()'>
                   <option value=\"self\"" . selected("self", $listType) . ">Mine!</option>
                   $sites
                   </select>&nbsp;
                   </td>
</form>";

$body .= '<table border=0 ><tr><td colspan=4>' . $updateList . '</td></tr><tr><td>Group Name:</td><td>
<form style="margin-bottom:0;" name="updateName" method="post" action="index.php?cmd=updateListName">
<input type="hidden" name="p1" value="' . $p1 . '" />
<input type="text" name="p2" maxlength=12 size=11 value="' . $listname . '" />
<input name="save" type="submit" value="Rename Group" />
<button type=submit onClick="return confirm_delete(' . $p1. ');">Delete Group</Button>
</form></td><td nowrap>&nbsp;&nbsp;Type: </td><td>' . $typeBody . '</td></tr></table>';


$body .= '<table width=80% align="left" border="0" cellpadding="5" cellspacing="0"><tr><td>
<form name="studentform" id="studentform" method="post" action="index.php?cmd=updatelist">
<input type="hidden" name="previoussearch" value="0" />
<input type="hidden" name="id" value="'. $p1 . '" />
  <table align="center" border="0" cellpadding="5" cellspacing="0">
    <tr>
      <td valign="top">' .
          $showcount . ' Current Group Members      </td>
      <td></td>
      <td valign="top">' .
          $potentialCount . ' Potential Group Members      </td>
    </tr>
    <tr>
      <td valign="top">
          <select name="removeselect[]" size="20" id="removeselect" multiple
                  onFocus="document.studentform.add.disabled=true;
                           document.studentform.remove.disabled=false;
                           document.studentform.addselect.selectedIndex=-1;" />';
$body .= $showlist;

$body .= '
          </select></td>
      <td valign="top">
        <br />
        <input name="add" type="submit" id="add" value="&larr;" />
        <br />
        <input name="remove" type="submit" id="remove" value="&rarr;" />
        <br />
      </td>
      <td valign="top">
          <select name="addselect[]" size="20" id="addselect" multiple
                  onFocus="document.studentform.add.disabled=false;
                           document.studentform.remove.disabled=true;
                           document.studentform.removeselect.selectedIndex=-1;">' .
$showpotential .
         '</select>
         <br />
 <!---
         <input type="text" name="searchtext" size="30" value="" 
                  onFocus ="document.studentform.add.disabled=true;
                            document.studentform.remove.disabled=true;
                            document.studentform.removeselect.selectedIndex=-1;
                            document.studentform.addselect.selectedIndex=-1;"
                  onkeydown = "var keyCode = event.which ? event.which : event.keyCode;
                               if (keyCode == 13) {
                                    document.studentform.previoussearch.value=1;
                                    document.studentform.submit();
                               } " />
         <input name="search" id="search" type="submit" value="Search" />
 --->
                </td>
    </tr>
  </table>
</form>
</td></tr>
<tr><td align=center>
	<table border=0>
		<tr>' . $sfaexport .
		'<td>
		&nbsp;&nbsp;&nbsp;
		</td><td>
			<form name="exportlist" id="exportlist" method="post" action="index.php?cmd=exportlist&listid=' . $p1 . '">
			<input name="export" type="submit" id="export" value="Export">
			</form>
		</td><td>
		&nbsp;&nbsp;&nbsp;
		</td><td>
			<form name="duplist" id="duplist" method="post" action="index.php?cmd=duplist&listid=' . $p1 . '">
			<input name="dup" type="submit" id="dup" value="Duplicate">
			</form>
		</td></tr>
	</table>' . $makeampm . '
</td></tr></table>';


include ("template.inc");

?>
