<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

/*
$handle = @fopen("/tmp/inputfile.txt", "r");
if ($handle) {
    while (!feof($handle)) {
        $buffer = fgets($handle, 4096);
        echo $buffer;
    }
    fclose($handle);
}
*/
/*

top array
  name
  value
  
side array
  name
  value
  
data
  [top->value][side->value]['data'] ==> value
  [top->value][side->value]['kind'] ==> display just number or match
  [top->value][side->value]['ids'] ==> student ids
  [top->value][side->value]['names'] ==> student names
  

*/

  
$test = $_GET['test'];
$year = $_GET['year'];
$optionYears = getSipYearOption ($year);

$site = $_GET['site'];
$grade = $_GET['grade'];
$level = $_GET['level'];
$student = $_GET['student'];
$grp = $_GET['grp'];
$siteRestriction = "";
$testList = array(
		array("id"  => "", "name" => "-select score-"),
		array("id"  => "SBA", "name" => "SBA"),
		array("id"  => "HSGQE", "name" => "HSGQE"),
		array("id"  => "TerraNova", "name" => "TerraNova")
	);	

$yearList = array(
		array("id"  => "", "name" => "-select year-"),
		array("id"  => "2005", "name" => "2005-2006"),
		array("id"  => "2006", "name" => "2006-2007"),
		array("id"  => "2007", "name" => "2007-2008")
		 );
		 
$gradeList =  array(
		array("id"  => "", "name" => ""),
		array("id"  => "1", "name" => "1"),
		array("id"  => "2", "name" => "2"),
		array("id"  => "3", "name" => "3"),
		array("id"  => "4", "name" => "4"),
		array("id"  => "5", "name" => "5"),
		array("id"  => "6", "name" => "6"),
		array("id"  => "7", "name" => "7"),
		array("id"  => "8", "name" => "8"),
		array("id"  => "9", "name" => "9"),
		array("id"  => "10", "name" => "10"),
		array("id"  => "11", "name" => "11"),
		array("id"  => "12", "name" => "12"),
		array("id"  => "12+", "name" => "12+")
		);
$levelList =  array(
		array("id"  => "", "name" => ""),
		array("id"  => "Adv", "name" => "Adv"),
		array("id"  => "Prof", "name" => "Prof"),
		array("id"  => "BP", "name" => "BP"),
		array("id"  => "FBP", "name" => "FBP")
		);
		
$studentList = getStudentArray($siteRestriction);

$grpList = $mylists = getMyList($currentUserID);

$siteOptions = getSitesOptions($site);

$testOptions = "<select name=\"test\" id=\"test\">" . 
                       GetOptionList($testList, $test) . 
                       "</select>";
                       
$yearOptions = "<select name=\"year\" id=\"year\">
					<option value=\"\">-select score-</option>
                     $optionYears
                 </select>";
                       
$siteOptions = "<select name=\"site\" id=\"site\">
                <option value=\"\" ></option>" . 
				$siteOptions . 
                "</select>";
                       
                       
$gradeOptions = "<select name=\"grade\" id=\"grade\">" . 
                       GetOptionList($gradeList, $grade) . 
                       "</select>";
                       
$levelOptions = "<select name=\"level\" id=\"level\">" . 
                       GetOptionList($levelList, $level) . 
                       "</select>";
                       
$studentOptions = "<select name=\"student\" id=\"student\">
                      <option value=\"\" ></option>" . 
                      GetOptionList($studentList, $student) . 
                       "</select>";
                       
$grpOptions = "<select name=\"grp\" id=\"grp\">
                       <option value=\"\" ></option>" . 
                       GetOptionList($grpList, $grp) . 
                       "</select>";
                       
function andClause($field, $value, $quote="'") {
	if($value <> "" ) {
		$ret = "and $field = $quote$value$quote";
	} else {
		$ret = "";
	}
	return $ret;
}
$clause = "";
$table = "";

$studentlist = getListStudents($grp);

$clause .= andClause("testscores.site", $site);
$clause .= andClause("testscores.gradelevel", $grade);
$clause .= andClause("testscores.level", $level);
$clause .= andClause("student.studentid", $student);
//$grpclause .= andClause("student.studentid in ($studentlist)", $grp);

if($grp <> "") {
//  $table = ", listvalues";
  $clause .= " and student.studentid in ($studentlist)";
}                      

$testdata = testInfo($test, $year);
$top = $testdata['top'];
$side = $testdata['side'];
$diffside = $testdata['diffside'];

$student = selectStudents($test, $year, $clause, $table);
$data = $student['chart'];
$diffdata = $student['diff'];


$body .= "<form action=index.php method=get>
			<input type=hidden name=cmd value=scores>
			<input type=hidden name=module value=sip>
		    <table>
		    	<tr>
		    		<td>
		    		</td>
					<td>
					</td>
		    		<td>Test: $testOptions
		    		</td>
					<td>Year: $yearOptions
					</td>
		    		<td>
		    		</td>
				</tr>
		    	<tr>
		    		<td>Site: $siteOptions
		    		</td>
					<td>Grade: $gradeOptions
					</td>
		    		<td>Proficiency: $levelOptions
		    		</td>
					<td>Student: $studentOptions
					</td>
		    		<td>Group: $grpOptions
		    		</td>
				</tr>
		    	<tr>
		    	<tr>
					<td>
					</td>
		    		<td>
		    		</td>
					<td><input type=submit>
					</td>
		    		<td><input type=reset>
		    		</td>
		    		<td>
		    		</td>
			</table>
		</form>";
				
$body .= produceTable($top, $side, $data);

$body .= "<br><br>";

$body .= produceTable($top, $diffside, $diffdata);


include_once ("template.inc");
?>