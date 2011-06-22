<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
$type = $_GET['type'];

//******************************************************************************
// Moved to js/transcriptsDefined.js********************************************
// *****************************************************************************
//$js .= "function SubmitType(value) {
//     doreports.action = \"index.php?cmd=transcriptsDefine&type=\" + value;
////     alert(value + \"---\" + doreports.action);
//     doreports.submit();
//     }
//
//     function AddList () {
//     var val = doreports.selectGroup.value;
//     doreports.action = \"index.php?cmd=transcriptsDefine&type=add&listid=\" + val;
////     alert(\"Here\" + val);
//     doreports.submit();
//     }
//";


if($type == 'delete') {
  $ids = $_POST['selectNames'];
  removeStudentFromReport ($ids, $currentUserID);
} else if ($type == 'clear') {
  removeAllfromReport ($currentUserID);
} else if ($type == 'add') {
  $listid = $_GET['listid'];
  addListtoReport($listid, $currentUserID);
}

$reportstudents = getReportListItems($currentUserID);

$smarty->assign('studentList',$reportstudents);

//$studentnumber = count($reportstudents);
//$studentlist = showListOptional($reportstudents);
$list1 = getMyList($currentUserID);
$ct = count($list1);
$list1[$ct]['listid'] = "";
$list1[$ct]['listname'] = "------ Server ------";
$list2 = getMyList($currentUserID, $currentMySite);
$lists = array_merge((array)$list1, (array)$list2);
//$listoptions = showListNameOptional($lists);

$smarty->assign('listOptions',$lists);
$isSmarty = true;

//$body =<<<END
//<div align="center">
//             <form name=doreports method=post action="index.php?cmd=transcriptsProduce">
//             <input type=hidden name=foo value=bar>
//							<table width="100%" border="0" cellspacing="2" cellpadding="0">
//								<tr>
//									<td bgcolor="white">
//										<div align="left">
//											<br>
//											<div align="left">
//												<font size="4" color="#cc0000">DART Transcripts</font><br>
//												<br>
//											</div>
//											<div class="noteimportant">
//											</div>
//										</div>
//									</td>
//								</tr>
//								<tr>
//									<td><br>
//										<br>
//										<font size="4" color="#cc0000">Select Current Groups &amp; Users </font><br>
//										<br>You can use this interface to select either an entire group, or any idividual within a group to print reports for, and then select the time frame of the report. <br>
//										<br>
//
//
//										If you do not see the group or user listed here, you can use the Student Search screen to locate specific individuals.<br>
//										<br>
//										<table width="75%" border="1">
//											<tbody>
//												<tr>
//													<td nowrap bgcolor="#ccccff">
//														<div align="center">
//															<font size="2"><b>Groups</b></font></div>
//													</td>
//													<td nowrap bgcolor="#ccccff">
//														<div align="center">
//															<font size="2"><b>Users</b></font></div>
//													</td>
//												</tr>
//												<tr height="100">
//													<td nowrap height="100">
//														<div align="center">
//															<select name="selectGroup" size="15" onClick="javascript:AddList();" style="width: 50mm">
//                              $listoptions
//                              </select></div>
//													</td>
//													<td nowrap height="100">
//														<div align="center">
//                               <input type=button name=delete value=delete onClick="javascript:SubmitType('delete');">
//                              <input type=button name=clear onClick="javascript:SubmitType('clear')" value='Clear List'><br>Student Number [$studentnumber]<br>
//                              <select name="selectNames[]" size="13" multiple style="width: 50mm">
//                              $studentlist
//                              </select></div>
//
//													</td>
//												</tr>
//											</tbody>
//										</table>
//										<br>
//										<table width="75%" border="1" cellspacing="2" cellpadding="0">
//											<tr>
//												<td width="50%">
//												<table>
//                        </table>
//<font size="4" color="#cc0000">Print Reports</font><br>
//<br>Once you have selected the students to print the transcripts from you must select the type and the level for the transcripts. After this when you click the print button below you the system creates the reports you have requested in PDF format, and downloads them to your machine.
//													<p></p><table>
//  <tr>
//    <td>Type Of Transcript: <select name="transcriptType" size="1">
//		    <option value="">Choose One</option>
//<!--			<option value="Exit  - Standards Based">Exit  - Standards Based</option> -->
//			<option value="Exit - GPA & Credits Earned">Exit - GPA & Credits Earned</option>
//<!--			<option value="Permanent File - Standards Based">Permanent File - Standards Based</option> -->
//			<option value="Permanent File  - GPA & Credits Earned">Permanent File  - GPA & Credits Earned</option>
//<!--			<option value="COA - Standards Based">COA - Standards Based</option> -->
//			<option value="COA - GPA & Credits Earned">COA - GPA & Credits Earned</option>
//<!--			<option value="Graduation - Standards Based">Graduation - Standards Based</option> -->
//			<option value="Graduation - GPA & Credits Earned">Graduation - GPA & Credits Earned</option>
//		</select>
//	</td><td>
//		Date Issued: <input type=text name=dateIssued size=10>
//	</td><td>
//		Start Testing Level: <select name="start" size="1">
//		    <option value="">Choose One</option>
//			<option value="-2">PK2</option>
//			<option value="-1">PK</option>
//			<option value="0">K</option>
//			<option value="1">1</option>
//			<option value="2">2</option>
//			<option value="3">3</option>
//			<option value="4">4</option>
//			<option value="5">5</option>
//			<option value="6">6</option>
//			<option value="7">7</option>
//			<option value="8">8</option>
//			<option value="9">9</option>
//			<option value="10">10</option>
//			<option value="11">11</option>
//			<option value="12">12</option>
//			<option value="13">12+</option>
//		</select>
//	</td><td>
//		Final Testing Level: <select name="final" size="1">
//		    <option value="">Choose One</option>
//			<option value="-2">PK2</option>
//			<option value="-1">PK</option>
//			<option value="0">K</option>
//			<option value="1">1</option>
//			<option value="2">2</option>
//			<option value="3">3</option>
//			<option value="4">4</option>
//			<option value="5">5</option>
//			<option value="6">6</option>
//			<option value="7">7</option>
//			<option value="8">8</option>
//			<option value="9">9</option>
//			<option value="10">10</option>
//			<option value="11">11</option>
//			<option value="12">12</option>
//			<option value="13">12+</option>
//		</select>
//	</td></tr>
//</table>
//
//
//													<div align="center">
//														<p><button name="buttonName" value="Print!" type="button" onClick="submit();">Print Reports!</button></p>
//													</div>
//												</td>
//											</tr>
//										</table>
//										<br>
//										<br>
//										<br>
//									</td>
//								</tr>
//							</table>
//						</form>
//           </div>
//END;
           
include ("template.inc");

$smarty->display('transcriptsDefine.tpl');
?>

