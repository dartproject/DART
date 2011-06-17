<?php

$A6Priv = Privilege(A6);

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
$studentLevel = getStudentLevelTable($id);
$subjects = getSubjects();
$sublen = count($subjects);
$studentName = $student['fname'] . " " . $student['lname'];
$status = $student['status'];
$newstatus = $status == 'Active' ? 'Inactive' : 'Active';
$width=10;

$body .= "<font size=4>$studentName [$status] $id</font><br>
Make <a href=index.php?cmd=handleLevel&type=$newstatus&id=$id onClick='javascript:return confirm_delete(\"You are about to change status to $newstatus. Click OK to continue\")'>$newstatus</a><br>
<br>";

$fname_input = name_input("First Name", "fname", $student['fname']);
$mname_input = name_input("Middle Name", "mname", $student['mname']);
$lname_input =  name_input("Last Name", "lname", $student['lname']);
$site = $student['site'];
$siteOptions = "<option value=\"\"" . selected("", $site) . ">None</option>" . getSitesOptions($site);
$grade =  $student['grade'];
$alaskaid_input = name_input("AKStudentID", "alaskaid", $student['alaskaid']);
$psid_input = name_input("PowerSchool ID", "psid", $student['psid']);
$bday_input = name_input("Bday", "bday", $student['bday']);
$user_input = name_input("User", "user", $student['user']);
$pwd_input = name_input("Pwd", "pwd", $student['pwd']);
$email_input = name_input("Email", "email", $student['email']);
$addr_input = name_input("Address", "addr", $student['addr']);
$village_input = name_input("Village", "village", $student['village']);
$zip_input = name_input("Zip", "zip", $student['zip']);
$phone_input = name_input("Phone", "phone", $student['phone']);
$code = $student['code'];
$codeOptions = "<option value=\"\"" . selected("", $code) . "></option>
                <option value=\"01\"" . selected("01", $code) . ">01 (Transfer within District)</option>
                <option value=\"02\"" . selected("02", $code) . ">02 (Transfer within Alaska)</option>
                <option value=\"03\"" . selected("03", $code) . ">03 (Transfer another State or Country)</option>
                <option value=\"04\"" . selected("04", $code) . ">04 (Transfer from home schooling)</option>
                <option value=\"05\"" . selected("05", $code) . ">05 (Transfer from private school)</option>
                <option value=\"06\"" . selected("06", $code) . ">06 (Transfer from an institute w/Ed Prog)</option>
                <option value=\"07\"" . selected("07", $code) . ">07 (RE-Entry voluntary WD same School)</option>
                <option value=\"08\"" . selected("08", $code) . ">08 (Re-entry involuntary WD same school)</option>
                <option value=\"09\"" . selected("09", $code) . ">09 (Initial Entry (student new to school))</option>
                <option value=\"10\"" . selected("10", $code) . ">10 (Return Student Prior Year))</option>
                <option value=\"E\"" . selected("E", $code) . ">E (enrolled)</option>
                <option value=\"R\"" . selected("R", $code) . ">R (returned)</option>
                <option value=\"T\"" . selected("T", $code) . ">T (Transferred from in-district)</option>
";


function name_input($header, $name, $value) {
   $value = "<td>$header:</td>
            <td><input type=hidden name=new_$name value=empty><input type=hidden name=old_$name value=$value>
                  <input type=text name=$name value='$value' onChange='changeValue(\"$name\", this.value)'></td>
";
   return ($value);
}
$body .= "<form name=toggle method=post action=index.php?cmd=saveAdvEditStudentInfo>
          <input type=hidden name=id value=$id>
          <input type=hidden name=loc>
          
        <table border=1>
            <tr>
              <td>Code:</td>
              <td colspan=4><input type=hidden name=new_code value=empty><input type=hidden name=old_code value=$code>
                  <select name=code onChange='changeValue(\"code\", this.value)' >$codeOptions</select></td>
            </tr>
            <tr>
              $fname_input
              $mname_input
              $lname_input
              <td>Site:</td>
              <td><input type=hidden name=new_site value=empty><input type=hidden name=old_site value=$site>
                  <select name=site onChange='changeValue(\"site\", this.value)' >$siteOptions</select></td>
            </tr>
              $psid_input
              $alaskaid_input
              $bday_input
            </tr>
            <tr>
              $user_input
              $pwd_input
              $email_input
              <td>Testing Level:</td>
              <td><input type=hidden name=new_grade value=empty><input type=hidden name=old_grade value='$grade'>
                  <select name=grade onChange='changeValue(\"grade\", this.value)' >" . getGradesSelection($grade) . "</select></td>
            </tr>
            <tr>
              $addr_input
              $village_input
              $zip_input
              $phone_input
            </tr>
        </table><input type=submit name=submit value='Save Demographics Information'></form>";
          

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

   
/******************************************/    
    include ("template.inc");

?>
