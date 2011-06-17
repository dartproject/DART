<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
$type = $_GET['type'];
$js .= "function SubmitType(value) {
     doreports.action = \"index.php?cmd=reportsInd&type=\" + value;
//     alert(value + \"---\" + doreports.action);
     doreports.submit();
     }
     
     function AddList () {
     var val = doreports.selectGroup.value;
     doreports.action = \"index.php?cmd=reportsInd&type=add&listid=\" + val;
//     alert(\"Here\" + val);
     doreports.submit();
     }
     
          
";
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
$studentnumber = count($reportstudents);
$studentlist = showListOptional($reportstudents);
$list1 = getMyList($currentUserID);
$ct = count($list1);
$list1[$ct]['listid'] = "";
$list1[$ct]['listname'] = "------ Server ------";
$list2 = getMyList($currentUserID, $currentMySite);
$lists = array_merge((array)$list1, (array)$list2);
$listoptions = showListNameOptional($lists);

$body ="<div align=\"center\">
             <form name=doreports method=post action=\"index.php?cmd=reports\">
							<table width=\"100%\" border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
								<tr>
									<td bgcolor=\"white\">
										<div align=\"left\">
											<br>
											<div align=\"left\">
												<font size=\"4\" color=\"#cc0000\">DART Current Report Center</font><br>
												<br>
											</div>
											<div class=\"noteimportant\">This is the area for adminstrators or their designees to print reports for the current quarter. You first select the site or district group, or individual you would print reports for and use the &quot;Print&quot; button. The result is a PDF file and download of the report which you can view and print locally. The system automatically knows which group each user has rights to see, and fills out the fields below with the groups and users which can be printed.  </div>
										</div>
									</td>
								</tr>
								<tr>
									<td><br>
										<br>
										<font size=\"4\" color=\"#cc0000\">Select Current Groups &amp; Users </font><br>
										<br>You can use this interface to select either an entire group, or any idividual within a group to print reports for, and then select the time frame of the report. <br>
										<br>
										
										
										If you do not see the group or user listed here, you can use the Student Search screen to locate specific individuals.<br>
										<br>
										<table width=\"75%\" border=\"1\">
											<tbody>
												<tr>
													<td nowrap bgcolor=\"#ccccff\">
														<div align=\"center\">
															<font size=\"2\"><b>Groups</b></font></div>
													</td>
													<td nowrap bgcolor=\"#ccccff\">
														<div align=\"center\">
															<font size=\"2\"><b>Users</b></font></div>
													</td>
												</tr>
												<tr height=\"100\">
													<td nowrap height=\"100\">
														<div align=\"center\">
															<select name=\"selectGroup\" size=\"15\" onClick=\"javascript:AddList();\" style=\"width: 50mm\">
                              $listoptions
                              </select></div>
													</td>
													<td nowrap height=\"100\">
														<div align=\"center\">
                               <input type=button name=delete value=delete onClick=\"javascript:SubmitType('delete');\">
                              <input type=button name=clear onClick=\"javascript:SubmitType('clear')\" value='Clear List'><br>Student Number [$studentnumber]<br>
                              <select name=\"selectNames[]\" size=\"13\" multiple style=\"width: 50mm\">
                              $studentlist
                              </select></div>

													</td>
												</tr>
											</tbody>
										</table>
										<br>
										<table width=\"75%\" border=\"1\" cellspacing=\"2\" cellpadding=\"0\">
											<tr>
												<td width=\"50%\"><font size=\"4\" color=\"#cc0000\">Select Report</font><br>
												</td>
											</tr>
											<tr>
												<td width=\"50%\">
												<table>
                          <tr>
                              <td><input type=\"checkbox\" name=rcard value=X>Report Card</td>
                              <td><input type=\"checkbox\" name=rcardwo value=X>Report Card - No QPI</td>
                          </tr>
                          <tr>
                              <td><input type=\"checkbox\" name=progrep value=X>Progress Report</td>
                              <td><input type=\"checkbox\" name=paceguide value=X>Pacing Guide</td>
                          </tr>
                        </table>
												
<br>
													<br>
													<br>
													<font size=\"4\" color=\"#cc0000\">Print Reports</font><br>
													<br>
													When you click the print button below you the system creates the reports you have requested in PDF format, and downloads them to your machine.
													<p></p>
													<div align=\"center\">
														<p><button name=\"buttonName\" value=\"Print!\" type=\"button\" onClick=\"submit();\">Print Reports!</button></p>
													</div>
												</td>
											</tr>
										</table>
										<br>
										<br>
										<br>
									</td>
								</tr>
							</table>
						</form>
           </div>";
           
include ("template.inc");
?>
<!------------
<csobj data=\"{ 0 = { label = &quot;Select Report Type&quot;; selected = &quot;YES&quot;; }; 1 = { label = &quot;Report Card &quot;; url = &quot;http://www.adobe.com&quot;; }; 2 = { label = &quot;Report Card - No QPI&quot;; url = &quot;http://www.adobe.com&quot;; }; 3 = { label = &quot;Progress Report&quot;; url = &quot;http://www.adobe.com&quot;; }; 4 = { label = &quot;Pacing Guide&quot;; url = &quot;http://www.adobe.com&quot;; }; 5 = { label = &quot;Report Card / Progress Report&quot;; url = &quot;http://www.adobe.com&quot;; }; 6 = { label = &quot;Report Card / Progress Report - No QPI&quot;; url = &quot;http://www.adobe.com&quot;; }; 7 = { label = &quot;Report Card / Pacing Guide&quot;; url = &quot;http://www.adobe.com&quot;; }; 8 = { label = &quot;Quarterly Reports - All Three!&quot;; url = &quot;http://www.adobe.com&quot;; }; }\" h=\"23\" t=\"URLPopup\" target=\"_top\" w=\"229\">
															<select name=\"cs_popup_name_1\" onchange=\"CSURLPopupShow(/*CMP*/'cs_form_name_1', /*CMP*/'cs_popup_name_1', '_top');\">
																<option value=\"#\" selected>Select Report Type</option>
																<option value=\"http://www.adobe.com\">Report Card</option>
																<option value=\"http://www.adobe.com\">Report Card - No QPI</option>
																<option value=\"http://www.adobe.com\">Progress Report</option>
																<option value=\"http://www.adobe.com\">Pacing Guide</option>
																<option value=\"http://www.adobe.com\">Report Card / Progress Report</option>
																<option value=\"http://www.adobe.com\">Report Card / Progress Report - No QPI</option>
																<option value=\"http://www.adobe.com\">Report Card / Pacing Guide</option>
																<option value=\"http://www.adobe.com\">Quarterly Reports - All Three!</option>
															</select>
													</csobj>
		
<input type=button name=select value='Select All' onClick=\"javascript:selectAllItems();\"><br>
                               											
		function selectAllItems() {
     alert(\"Here\");
     len = 2;
//document.myForm.mySelect.selectedIndex
//     doreports.selectNames.options.length=0;
//     alert(len);
     
     for (i=0;i < len;i++) {
         alert(i);
//        	document.doreports.selectNames.selectedIndex = i;
            document.doreports.selectNames.options[i].selected = true;
       }
       
     }

----------->
