<?php 

if(!PDisplayB(B13) ) {
	Header("Location: index.php?cmd=noPrivilege&type=Testing&notes=Can not see testing data");
}

if($_GET['go'] != '') {
cleartestreports();
$i=1;
	createStrandReport('Reading', $i++, "SBA", false);
	createStrandReport('R-SC1', $i++, "SBA");
	createStrandReport('R-SC2', $i++, "SBA");
	createStrandReport('R-SC3', $i++, "SBA");
	createStrandReport('Writing', $i++, "SBA", false);
	createStrandReport('W-SC1', $i++, "SBA");
	createStrandReport('W-SC2', $i++, "SBA");
	createStrandReport('W-SC3', $i++, "SBA");
	createStrandReport('Math', $i++, "SBA", false);
	createStrandReport('M-SC1', $i++, "SBA");
	createStrandReport('M-SC2', $i++, "SBA");
	createStrandReport('M-SC3', $i++, "SBA");
	createStrandReport('M-SC4', $i++, "SBA");
	createStrandReport('M-SC5', $i++, "SBA");
	createStrandReport('M-SC6', $i++, "SBA");
	createStrandReport('Science', $i++, "SBA", false);
	createStrandReport('S-SC1', $i++, "SBA");
	createStrandReport('S-SC2', $i++, "SBA");
	createStrandReport('S-SC3', $i++, "SBA");
	createStrandReport('S-SC4', $i++, "SBA");

$i=1;	
	createStrandReport('Reading', $i++, "HSGQE", false);
	createStrandReport('R4.1', $i++, "HSGQE");
	createStrandReport('R4.2', $i++, "HSGQE");
	createStrandReport('R4.3', $i++, "HSGQE");
	createStrandReport('R4.4', $i++, "HSGQE");
	createStrandReport('R4.7', $i++, "HSGQE");
	createStrandReport('R4.8', $i++, "HSGQE");
	createStrandReport('Writing', $i++, "HSGQE", false);
	createStrandReport('W4.1/4.2', $i++, "HSGQE");
	createStrandReport('W4.3', $i++, "HSGQE");
	createStrandReport('W4.4', $i++, "HSGQE");
	createStrandReport('Math', $i++, "HSGQE", false);
	createStrandReport('M1.4', $i++, "HSGQE");
	createStrandReport('M2.4', $i++, "HSGQE");
	createStrandReport('M3.4', $i++, "HSGQE");
	createStrandReport('M4.4', $i++, "HSGQE");
	createStrandReport('M5.3', $i++, "HSGQE");
	createStrandReport('M6.3', $i++, "HSGQE");
	
$i=1;
	createESPStrandReport('Verbal Concepts', $i++, "ESP");
	createESPStrandReport('Visual Discrimination', $i++, "ESP");
	createESPStrandReport('Logical Relations', $i++, "ESP");
	createESPStrandReport('Basic School Skills', $i++, "ESP");
	createESPStrandReport('Expressive Language', $i++, "ESP");
	createESPStrandReport('Receptive Language', $i++, "ESP");
	createESPStrandReport2('Gross Motor', $i++, "ESP");
	createESPStrandReport2('Fine Motor', $i++, "ESP");
	createESPStrandReport3('Articulation', $i++, "ESP");

	createTerraNovaStrandReport('Reading', 1, "TerraNova");
	createTerraNovaStrandReport('Vocabulary', 2, "TerraNova");
	createTerraNovaStrandReport('Reading Composite', 3, "TerraNova");
	createTerraNovaStrandReport('Language', 4, "TerraNova");
	createTerraNovaStrandReport('Language Mechanics', 5, "TerraNova");
	createTerraNovaStrandReport('Language Composite', 6, "TerraNova");
	createTerraNovaStrandReport('Mathematics', 7, "TerraNova");
	createTerraNovaStrandReport('Math Computation', 8, "TerraNova");
	createTerraNovaStrandReport('Math Composite', 9, "TerraNova");
	createTerraNovaStrandReport('Total Score', 10, "TerraNova");
	createTerraNovaStrandReport('Science', 11, "TerraNova");
	createTerraNovaStrandReport('Social Studies', 12, "TerraNova");
	createTerraNovaStrandReport('Spelling', 13, "TerraNova");
	createTerraNovaStrandReport('Word Analysis', 14, "TerraNova");

	createOverallTerraNova();
	createOverallELP();
	createOverallPPVT();
	createOverallESP();
	createOverallHSGQE();
	createOverallSBA();

}

$mylists = getMyList($currentUserID);
$grouplists =  getMyList($currentUserID, $currentMySite);
 
// print_r($mylists);
$listid = $_GET['listid'] == "" ? $mylists[0]['listid'] : $_GET['listid'];
$year = $_GET['year'];
$test = $_GET['test'];
$kind = $_GET['kind'];

$grpOptions = "<form action=index.php method=get>
			<input type=hidden name=cmd value=showGroupTestScores>
			<input type=hidden name=year value='$year'>
			<input type=hidden name=test value='$test'>
			<input type=hidden name=kind value='$kind'>
			<input type=hidden name=module value=testing>
			<select name=\"listid\" id=\"grp\" onChange='javascript:submit();'>" .
                       GetOptionList($mylists, $listid) . 
					"<option value=''>-- Group List --</option>" .
                       GetOptionList($grouplists, $listid) . 
             "</select>
            </form><br>";

$sql1 = "select year as id, year as name from testscores where test = '$test' group by year order by year";
$yearOptionList = makeSQLOptions($sql1, $year);
$sql2 = "select test as id, test as name from testscores, tests where test=id group by test order by ord";
$testOptionsList = makeSQLOptions($sql2, $test);
$sql3 = "select testtype as id, testtype as name from testreports where test = '$test' ORDER by ord";
$kindOptionList = makeSQLOptions($sql3, $kind);
$grpOptions .= "<form action=index.php method=get>
			<input type=hidden name=cmd value='showGroupTestScores'>
			<input type=hidden name=module value='testing'>
			<input type=hidden name=listid value='$listid'>
			<select name='test' onChange=\"submit()\">
				$testOptionsList
			</select>
			<select name='year' onChange=\"submit()\">
				$yearOptionList
			</select>
			<select name='kind' onChange=\"submit()\">
				$kindOptionList
			</select>
		</form>";

//$arrowtext = "^";
//$var = array('[url]', '[{$sort}dir]');
//$val = array($_SERVER[PHP_SELF], '');
$sql4 = "select * from testreports, tests where test=id and test = '$test' and testtype = '$kind'";
$results = $db->get_results($sql4, ARRAY_A);
$fields = $results[0]['fields'];


$url = $_SERVER['PHP_SELF'];
while(list($var, $val) = each($_GET) ) {
	if($var != 'sort' or $var != 'dir') {
		$param .= "$var=$val&";
	}
}
$url = "$url?$param&";
$sort = $_GET['sort'];
$currentdir = ($_GET['dir'] == 'asc') ? 'asc': 'desc';
$orderval = $_GET['orderval'];
$sorttype = $_GET['sorttype'];
$stdval = $_GET['stdval'];
${$sort . "dir"} = ($currentdir == 'asc') ? 'desc' : 'asc';
$arrow = ($currentdir == 'asc') ? 'V' : '^';
${$sort . "arrow"} = $arrow;
$h = $results[0]['heading'];
eval("\$heading = \"$h\";");


$row = $results[0]['row'];
$legend = $results[0]['legend'];
$setlist = explode(" ", $fields);
$menu = topmenu();
$style = getStyle();
$body .= "
$style
$menu
$grpOptions
$legend";

$studentlist = getListStudents($listid);

$sql1 = "select *, alaskaid as aid from student where studentid in ($studentlist) ORDER BY lname, fname ";

//$oval = ($orderval != '') ? "ORDER BY $orderval $currentdir " : "";
$oval = ($orderval != '') ? "ORDER BY v $currentdir " : "";
$oselect = ($orderval != '') ? "CONVERT ( $orderval, $sorttype) as v,  " : "";
$stdval = ($stdval != '') ? " and standard='$stdval' " : "";
$sql1 = "SELECT  student.*, $oselect 
			student.alaskaid as aid from student 
		 LEFT JOIN testscores ON testscores.alaskaid = student.alaskaid and 
		 		year = '$year' and test = '$test' $stdval
		 WHERE studentid in ($studentlist) 
		 GROUP BY student.alaskaid
         $oval 
		 ";

// echo $sql1;

$studentinfo = '';
$students = $db->get_results($sql1, ARRAY_A);

foreach ($students as $stu) { 
	$id = trim($stu['alaskaid']);
	while (list($var, $val) = each($stu) ) {
		$studentinfo[$id][trim($var)] = $val;
	}
//	echo "ID: $id, ";
}
$sql2 = "select testscores.* from testscores, student where studentid in ($studentlist) and testscores.alaskaid = student.alaskaid and year = '$year' and test = '$test' ";

// Start getting the testing scores

$testscores = $db->get_results($sql2, ARRAY_A);

foreach ($testscores as $test) { 
	$id = $test['alaskaid'];
	$std = str_replace("-", "_", $test['standard']);
	$std = str_replace(".", "_", $std);
	$std = str_replace("/", "_", $std);
	$std = str_replace(" ", "_", $std);
	$studentinfo[$id][$std] = $test['value'];
	$studentinfo[$id]['gradelevel'] = $test['gradelevel'];
	$studentinfo[$id][$std."_class"] = str_replace(" ", "_", $test['level']);
	$studentinfo[$id][$std."_level"] = $test['level'];
	$studentinfo[$id][$std."_value"] = $test['raw_value'];
	$studentinfo[$id][$std."_needed"] = $test['raw_needed'];
	$studentinfo[$id][$std."_diff"] = $test['raw_difference'];
	$studentinfo[$id][$std."_scale_value"] = $test['value'];
	$studentinfo[$id][$std."_scale_needed"] = $test['needed'];
	$studentinfo[$id][$std."_scale_diff"] = $test['difference'];
	$studentinfo[$id][$std."_test_date"] = $test['test_date'];
	$studentinfo[$id][$std."_status"] = $test['status'];
}


/*
$heading = "
<th>Alaskia ID</th>
<th>Name</th>
<th>Grade<br>Level</th>
<th>Strand</th>
<th>Raw Score</th>
<th>Raw Score<br>Difference</th>
<th>Scale Score</th>
<th>Proficinty<br>Level</th>
<th>Scale Score<br>Needed for<br>Proficiency</th>
<th>Scale Score<br>Difference</th>
<th>Gender</th>
<th>Ethnicity</th>
<th>Economically<br>Disadvantage</th>
<th>LEP</th>
<th>SPED</th>
<th>504</th>";
$row = '<tr>
<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
<td>$fname $lname</td>
<td>$gradelevel &nbsp;</td>
<td>R-SC1</td>
<td>$value &nbsp;</td>
<td>$difference &nbsp;</td>
<td class=\"$R-SC1_class\">$scale_score &nbsp;</td>
<td>$level &nbsp;</td>
<td>$needed_proficiency &nbsp;</td>
<td>$scale_score_diff &nbsp;</td>

</tr>\n';
$setlist = explode(" ", "aid fname lname gradelevel R-SC1 R-SC1_class  value difference scale_score level needed_proficiency scale_score_diff");



$heading = "
<th>Alaskia ID</th>
<th>Name</th>
<th>Grade<br>Level</th>
<th>Reading</th>
<th>Writing</th>
<th>Math</th>
<th>Gender</th>
<th>Ethnicity</th>
<th>Economically<br>Disadvantage</th>
<th>LEP</th>
<th>SPED</th>
<th>504</th>";
$row = '<tr>
<td><a href=index.php?cmd=showIndividualTestScores&module=testing&aid=$aid>$aid</a></td>
<td>$fname $lname</td>
<td>$gradelevel &nbsp;</td>
<td class=\"$Reading_class\">$Reading &nbsp;</td>
<td class=\"$Writing_class\">$Writing &nbsp;</td>
<td class=\"$Math_class\">$Math &nbsp;</td>
<td>$gender</td>
<td>$ethnicity &nbsp;</td>
<td>$NSLPEligible &nbsp;</td>
<td>$LEP &nbsp;</td>
<td>$sped &nbsp;</td>
<td>$sec504 &nbsp;</td>
</tr>\n';
$setlist = explode(" ", "aid fname lname gradelevel Reading_class Reading Writing_class Writing Math_class Math gender ethnicity NSLPEligible LEP sped sec504");

*/

//print_r($studentinfo);

$body .= "<table border=1><tr>$heading</tr>";

foreach($studentinfo as $stu) {
	foreach($setlist as $s) ${$s} = "";
	while (list($var, $val) = each($stu) ) ${$var} = $val;
//	$body .= "<tr><td>$studentid--</td><td>$fname $lname</td></tr>";
//	echo "$row<br>";
	eval("\$str = \"$row\";");
	$body .= $str;
}


$body .= "</table>";

include_once ("template.inc");
/*
// Test Scores Start
	$sql = "SELECT testscores.* FROM testscores, students
			WHERE testscores.alaskaid = '$aid' and
				testscores.year = '$year' and
				testscoresmap.test = testscores.test and			
				testscoresmap.standard = testscores.standard and				
				testscoresmap.subject = '$area'
			GROUP BY testscores.standard
			ORDER BY testscoresmap.order";
//	echo $sql;
	$testscores = $db->get_results($sql, ARRAY_A);

	
	if ($testscores != "") {
		$theader = "";
		$tvalue = "";
		foreach($testscores as $row) {
			$title = $row['standard'];
			$tval = $row['value'];
			$theader .= "<th width=30>$title</th>";
			$tvalue .= "<td>$tval &nbsp;</td>";
			$test = $row['test'];
		}
		$body .= "<table border=1><tr><th rowspan=2 align=top>$test</th>$theader</tr><tr>$tvalue </tr></table>";
	}
*/
/*
ELP
*/


?>