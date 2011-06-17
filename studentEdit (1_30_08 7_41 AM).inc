<?php

$A6Priv = Privilege(A6);
$A25Priv = Privilege(A25);

$flag = $A25Priv == 'none'? false : true;

if($A6Priv != 'district') { NoPriv("denied advEdit", "You should not be trying to do advance editing. Email sent to admin"); }

$id = $_GET['id'];

$js = "function changeValue(name,newval) {
        obj = document.getElementsByName(\"new_\" + name)[0];
        obj.value = newval;
 }
 
function changeToggle(name,newval) {
        obj = document.getElementsByName(\"ch_\" + name)[0];
        obj.value = newval;
 }
function confirm_delete(prompt)
{
  input_box=confirm(prompt);
  if (input_box==true)
  { 
     return true;
  } else {
     return false;
  }
}
 ";
//      window.location=\"index.php?cmd=handleLevel&type=delete&sub=\" + sub + \"&lvl=\" + lvl + \"&id=\" + id;

$student = getStudentInfo($id);
$showDates = " | <a href='' onClick='popUp(\"./index.php?cmd=StudentShowDates&id=$id\", 400, 400);return(false);' >Show Dates</a>";
$activeButton = $student['status'] == 'Active' ? 
	"<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Student Active: </b></font> <a href='' onClick='popUp(\"./index.php?cmd=StudentExit&id=$id\", 800, 600);return(false);' >Make Inactive</a>" :
	"<font size=\"2\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><b>Student Inactive: </b></font> <a href='' onClick='popUp(\"./index.php?cmd=StudentEnter&id=$id\", 800, 600);return(false);'>Make Active</a>" ;
	
$studentLevel = getStudentLevelTable($id);
$subjects = getSubjects();
$sublen = count($subjects);
$studentName = $student['fname'] . " " . $student['lname'];
$entrylist = array("fname", "lname");
while(list($var, $value) = each($student)) {
//	${$var} = $value;
	${$var . "_input"} = name_input2($var, $value);
//	echo $var . "_input" . "=>" . htmlspecialchars(name_input2($var, $value)) . "<br>" ;
}
$studentsite = $student['site'];
//$site = "<a href='index.php?cmd=Movement&studentid=$id'><b>$studentsite</b></a> <= Click to change";
// name_selection('grade', $student['grade'], $statusOptions);"

$siblingsnamesChoice = name_input2('siblingsnames', $student['siblingsnames'], 75);

$notesArea = name_textarea('snotes', $student['snotes'], 6, 75);

$testinglevelOptions = arrayOptions(array (array("", "none"), array("PK", "PK"), array("K", "K"), array("1", "1"), array("2", "2"), array("3", "3"), array("4", "4"), array("5", "5"), array("6", "6"), array("7", "7"), array("8", "8"), array("9", "9"), array("10", "10"), array("11", "11"), array("12", "12"), array("13", "13")), $student['grade']);
$testinglevel = name_selection('grade', $student['grade'], $testinglevelOptions);

$statusOptions = arrayOptions(array (array("Active", "Active"), array("Inactive", "Inactive")), $student['status']);
$statusChoice = name_selection('status', $student['status'], $statusOptions);

$genderOptions = arrayOptions(array (array("", ""), array("F", "Female"), array("M", "Male")), $student['gender']);
$genderChoice = name_selection('gender', $student['gender'], $genderOptions);

$spedOptions = arrayOptions(array (array("N", "No"), array("Y", "Yes")), $student['sped']);
$spedChoice = name_selection('sped', $student['sped'], $spedOptions);

$siblingsOptions = arrayOptions(array (array("", "Choose One"), array("none", "none"), array("1", "1"), array("2", "2"), array("3", "3"), array("4", "4"), array("5", "5"), array("6", "6"), array("7", "7"), array("8", "8"), array("9", "9"), array("10", "10"), array("11", "11")), $student['siblings']);
$siblingsChoice = name_selection('siblings', $student['siblings'], $siblingsOptions);

$parentwstudentOptions = arrayOptions(array (array("", "Either Y or N"),array("Y", "Yes"), array("N", "No")), $student['parentwstudent']);
$parentwstudentChoice = name_selection('parentwstudent', $student['parentwstudent'], $parentwstudentOptions);


$width=10;

function arrayOptions ($values, $sel = '') {
	global $database;
	
	if($values <> "") {
		
		foreach ($values as $row) {
			$selected = ($row[0] == $sel) ? "selected": "";
			$ret .= "<option value=$row[0] $selected>$row[1]</option>";
		}
	}
	return ($ret);
}

function name_input2($name, $value, $size=20) {
   $ret = "<input type=hidden name=new_$name value=empty><input type=hidden name=old_$name value='$value'>
                  <input type=text name=$name value='$value' onChange='changeValue(\"$name\", this.value)' size=$size>
";
   return ($ret);
}

function name_textarea($name, $value, $row=20, $cols=20) {
   $ret = "<input type=hidden name=new_$name value=empty><input type=hidden name=old_$name value=$value>
                  <textarea name=$name onChange='changeValue(\"$name\", this.value)' rows=$row cols=$cols >$value</textarea>
";
   return ($ret);
}

function name_selection($name, $value, $options) {
	$ret = "<input type=hidden name=new_$name value=empty><input type=hidden name=old_$name value='$value'>
                  <select name=$name onChange='changeValue(\"$name\", this.value)' >" . $options . "</select>";
	return($ret);
}

$body .= <<<END
<form name=toggle method=post action=index.php?cmd=saveAdvEditStudentInfo>
          <input type=hidden name=id value=$id>
          <input type=hidden name=loc>
<table border="0" cellpadding="0" cellspacing="2" width="100%">
	<tr>
		<td>
			<div align="left">

				<br>
				<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Add/Edit Student </font><font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- $studentName </font><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><br>
				</font></div>
			<div align="right">
				
			</div>
			<blockquote>
				<div align="left">
					<div class="noteimportant">

						<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">This screen adds a new student to DART.  You begin here for students who have not ever been in DART before.  If you are looking for a former BSSD student, always <a title="Search DART" href="https://dart.bssd.org/index.php?cmd=search"><b>search</b></a> for them first in our database.<i> </i>If a student exists in the system, just activate them, and assign them to the correct school. Field names in red are required, and those in black are optional.</font></div>
				</div>
			</blockquote>
		</td>
	</tr>
	<tr>

		<td>
			<div align="center">
				<table border="0" cellpadding="2" cellspacing="2" width="749">
					<tbody>
						<tr>
							<td colspan="6" bgcolor="#ccffff">
								<div align="right">
									<b><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Account Basics</font></b></div>

							</td>
						</tr>
						<tr>
							<td colspan="6" valign="bottom"><div class="notewarning"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i><b>Note:</b>  Student names in DART must match either birth certificate, or legal document showing change of name. Unofficial adoption, divorce, or temporary guardianship arrangements do not change the legal name of a student. Do <u>not</u> use nicknames.</i></font></div></td>
						</tr>
						<tr>

							<td valign="bottom" nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Last Name:</b></font></td>
							<td valign="bottom" width="182">
							$lname_input
							</td>
							<td colspan="4">
								<div align="left">
									</div>
							$activeButton $showDates
							</td>
						</tr>
						<tr>

							<td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>First Name:</b></font></td>
							<td width="182">
							$fname_input
							</td>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Middle Name:</b></font></td>
							<td nowrap width="15%">
							$mname_input
							</td>
							<td nowrap width="45"></td>
							<td nowrap width="15%"></td>
						</tr>
						<tr>

							<td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Mailing Address:</b></font></td>
							<td width="182">
							$maddr_input
							</td>
							<td width="15%"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Physical Address:</b></font></td>
							<td width="15%">
							$addr_input
							</td>
							<td colspan="2" nowrap bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Different</i></font></td>
						</tr>
						<tr>

							<td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Village / Town:</b></font></td>
							<td width="182">
							$village_input
							</td>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Zip Code:</b></font></td>
							<td width="15%">
							$zip_input
							</td>
							<td nowrap width="45"></td>
							<td nowrap width="15%"></td>
						</tr>
						<tr>

							<td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Email Address:</b></font></td>
							<td width="182">
							$email_input
							<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== Only District</i></font></td>
							
							<td nowrap width="45"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Phone:</b></font></td>
							<td nowrap width="15%">
							$phone_input
							</td>
						</tr>

						<tr>
							<td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Username:</b></font></td>
							<td width="182">
							$user_input
							</td>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Password:</b></font></td>
							<td width="15%">
							$pwd_input
							</td>
							<td nowrap width="45"></td>
							<td nowrap width="15%"></td>
						</tr>

						<tr>
							<td colspan="6" nowrap="nowrap" bgcolor="#ccffff">
								<div align="right">
									<b><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Student Data Required</font></b></div>
							</td>
						</tr>
						<tr>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>BSSD School Site:</b></font></td>
							<td width="182">
							$studentsite
							</td>
							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Status:</b></font></td>
							<td width="15%">
							$statusChoice
							</td>
						</tr>
						<tr>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Date of Birth:</b></font></td>
							<td nowrap width="182">
							
							$bday_input
							<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">YYYY-MM-DD</font></td>

							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gender:</b></font></td>
							<td width="15%">
								<div align="left">
								$genderChoice
								</div>
							</td>
							<td width="45"></td>
							<td width="15%"></td>
						</tr>
						<tr>
							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Alaska Student ID:</b></font></td>
							<td width="182">
							$alaskaid_input
							</td>

							<td nowrap width="15%">
								<div align="left">
									<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>PowerSchool ID:</b></font></div>
							</td>
							<td width="15%">
							$psid_input
							</td>
							<td colspan="2" bgcolor="#ffcccc">
								<div align="left">
									<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Applicable</i></font></div>

							</td>
						</tr>
						<tr>
							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Testing Level:</b></font></td>
							<td width="182">
							$testinglevel
							</td>
							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Special Education?:</b></font></td>
							<td width="15%">
							$spedChoice
							</td>
							<td width="45"></td>
							<td width="15%"></td>
						</tr>
						<tr>
							<td colspan="6" bgcolor="#ccffff">
								<div align="right">

									<b><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Guardian &amp; Family Information</font></b></div>
							</td>
						</tr>
						<tr>
							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Siblings at School?</b></font></td>
							<td valign="top" width="182">
							$siblingsChoice
							</td>

							<td colspan="4" bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== Number of other students <u>in this school</u> this student lives with</i></font></td>
						</tr>
						<tr>
							<td width="15%"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Names of Others:</b></font></td>
							<td colspan="3" valign="top">
							$siblingsnamesChoice
							</td>
							<td colspan="2" bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Applicable</i></font></td>

						</tr>
						<tr>
							<td colspan="6"><div class="notewarning"><i><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Note: </b>The full names of the parent(s) or guardian(s) must be recorded for each student, unless student is over 18 years old. If the student is living with a relative or in another home, the names and addresses of the responsible adult with whom the student is living must be recorded here.</font></i></td>
						</tr>
						<tr>
							<td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Parent or Guardian:</b></font></td>
							<td valign="top" width="182">
							$parent_input
							</td>

							<td nowrap>
								<div align="left">
									<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Resides With Student:</b></font></div>
							</td>
							<td valign="top">
							$parentwstudentChoice							
							</td>
							<td width="45"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Phone:</b></font></td>
							<td width="15%">
							$parentphone_input
							</td>
						</tr>
						<tr>
							<td width="15%">
								<div align="left">

									<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Mailing Address:</b></font></div>
							</td>
							<td valign="top" width="182">
							$parentmaddr_input
							</td>
							<td><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Physical Address:</b></font></td>
							<td>
							$parentaddr_input
							</td>
							<td colspan="2" bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Different</i></font></td>
						</tr>

						<tr>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Village / Town:</b></font></td>
							<td valign="top" width="182">
							$parentvillage_input
							</td>
							<td><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Zip Code:</b></font></td>
							<td valign="top">
							$parentzip_input
							</td>
							<td width="45"></td>
							<td width="15%"></td>
						</tr>

						<tr>
							<td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Comments / Notes:</b></font></td>
							<td rowspan="4" colspan="3" valign="top">
							$notesArea
							</td>
							<td width="45"></td>
							<td width="15%"></td>
						</tr>
						<tr>
							<td width="15%">

								<div align="center">
									</div>
							</td>
							<td width="45"></td>
							<td width="15%"></td>
						</tr>
						<tr>
							<td width="15%"></td>
							<td width="45"></td>

							<td width="15%"></td>
						</tr>
						<tr>
							<td width="15%"></td>
							<td width="45"></td>
							<td width="15%"></td>
						</tr>
						<tr>
							<td width="15%"></td>

							<td colspan="2">
								<div align="center">
									<br>
									<input name="cmdSearch" value="Save &amp; Exit" type="submit"></div>
							</td>
							<td colspan="2"><br>
								<input name="cmdSearch" value="Cancel" type="submit"></td>
							<td width="15%"></td>
						</tr>

					</tbody>
				</table>
			</div>
		</td>
	</tr>
</table>
</form>
END;

if($flag == true) {
/************** Student Level Information ************************/
$addAllLevels = "<form><input type=button value=\"Add All Levels\" onClick=\"window.location='index.php?cmd=handleLevel&&id=$id&type=addall';\"></form>";

$subjectAdd = "$addAllLevels<table border=1><tr><td>Click To Add Subject</td>";
debugPrint("<br>sublen: $sublen<br>");
for ($i = 0; $i < $sublen; $i++) {
  $sub = $subjects[$i]['id'];
  $subjectAdd .= "<td><a href=index.php?cmd=handleLevel&id=$id&sub=$sub&type=add>&nbsp; $sub &nbsp;</a></td>";
}

$subjectAdd .= "</tr></table>";

$body .= "<hr>
$subjectAdd<br>
<form name=toggle method=post action=index.php?cmd=saveLevels>
          <input type=hidden name=id value=$id>
          <input type=hidden name=loc>";

    $body .= "Edit or Remove Levels (click on minus sign to remove)<table border=1>";
    $line0 = "";
    $line1 = "";
  
$len = count($studentLevel);
 
for ($i = 0; $i < $len; $i++) {
     $sub = $studentLevel[$i]['subject'];        // subject number
     $lvl = $studentLevel[$i]['level'];          // level number
     $subOptions = getSubLvlOptions ($sub, $lvl);
        
     $line0 .= "<th><a href=index.php?cmd=handleLevel&id=$id&sub=$sub&lvl=$lvl&type=delete onClick='javascript:return confirm_delete(\"You are about to delete the level. Click OK to continue\")'> - </a>$sub ($lvl)</th>";
     $name = $sub . "_" . $lvl;
     $line1 .= "<td><input type=hidden name=new_" . $name . " value=empty>\n";
     $line1 .= "<select bgcolor=$color name=" . $name . " onChange='changeValue(\"$name\", this.value)' >
               <option value=\"\"" . selected("", $value) . "></option>
               $subOptions
               </select>&nbsp;
               </td>\n";
     if(fmod($i+1, $width) == 0) {
        $body .= "<tr> $line0 </tr><tr> $line1 </tr>";
        $line0 = "";
        $line1 = "";
     }
   }
   if(fmod($i, $width) <> 0) {
        $body .= "<tr> $line0 </tr><tr> $line1 </tr>";  
   }
    $body .= "</table><br>
    <input type=submit name=submit value='Save Level Information'></form>";
    $body .= "<hr>";
    
/*************  Student Levels ****************************/

$stdLevels = allStudentLevels($id);
$studentGrades = allStudentGrades($id);

$body .= "<form name=toggle method=post action=index.php?cmd=saveAdvToggle>
          <input type=hidden name=id value=$id>
          <input type=hidden name=loc>";


    $line0 = "";
    $line1 = "";
  
$len = count($stdLevels);
for ($j = 0; $j < $len; $j++) {
    $sub = $stdLevels[$j]['subject'];
    $lvl = $stdLevels[$j]['level'];
//foreach ($stdLevels as $level) {
//    $sub = $level['subject'];
//    $lvl = $level['level'];
    $standards = getStandards($sub, $lvl );
    $jlen = count($standards);
    $body .= "$sub ($lvl) ";
    $line0 = "<table border=1><tr rowspan=2 bgcolor=$color1><th rowspan=2>$sub ($lvl)</th>";
    $line1 = "";
    $line2 = "";

    for ($i = 0; $i < $jlen; $i++) {
         $std = $standards[$i]['std'];        
         $value  = $studentGrades[$sub][$lvl][$std]; 
         $des = htmlentities($standards[$i]['description']);
         $des = str_replace("'", "\'", $des );
         if (!isset($value)) { $type = "i"; } else { $type = "u"; }
         $name = "gr" . $type . "_" . $id . "_" . $sub . "_" . $lvl . "_" .$std;
//         debugPrint("<br>=> $sub: $lvl: $std: $value<br>");
         $line1 .= "<th width=$width onMouseOver=\"return escape('$des')\">&nbsp;&nbsp;" . $std . "&nbsp;&nbsp;</th>";
         $line2 .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
         $line2 .= "<input type=hidden name=ch_" . $name . " value=empty>\n";
         $line2 .= "<select bgcolor=$color name=" . $name . " onChange='changeToggle(\"$name\", this.value)'' >
                     <option value=\"\"" . selected("", $value) . "></option>
                     <option value=\"EMG\"" . selected("EMG", $value) . ">EMG</option>
                     <option value=\"DEV\"" . selected("DEV", $value) . ">DEV</option>
                     <option value=\"PRO\"" . selected("PRO", $value) . ">PRO</option>
                     <option value=\"ADV\"" . selected("ADV", $value) . ">ADV</option>
                     </select>&nbsp;
                     </td>\n";
         if(fmod($i+1, $width) == 0) {
            $body .= "$line0 $line1 </tr><tr> $line2 </tr>";
            $line1 = "";
            $line2 = "";
         }
    }
    if(fmod($i, $width) <> 0 or $i == 0) {
       $body .= "$line0 $line1 </tr><tr> $line2 </tr>";

    }

    $body .= "</table><input type=submit name=submit value='Save Toggles'><br><br>";
}
}
   
/******************************************/    
    include ("template.inc");

?>
