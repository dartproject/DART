<?php

if(!PDisplayB(B14) ) {
	Header("Location: index.php?cmd=noPrivilege&type=Testing&notes=Can not edit testing data");
}

 $year = $_GET['year'];
 $test = $_GET['test'];
 $menu = topmenu();

 $sql1 = "select year as id, year as name from testscores where test = '$test' group by year order by year";
 $yearOptionList = makeSQLOptions($sql1, $year);
 $sql2 = "select test as id, test as name from testscores group by test";
 $testOptionsList = makeSQLOptions($sql2, $test);
 $body .= "$menu<form action=index.php method=get>
 				<input type=hidden name=cmd value='editTestScores'>
 				<input type=hidden name=module value='testing'>
				<select name='test' onChange=\"submit()\">
 					$testOptionsList
 				</select>
 				<select name='year' onChange=\"submit()\">
 					$yearOptionList
 				</select>
 			</form>";
 			
 $ts = $db->get_results("select * from testscores   
 		LEFT JOIN student ON student.alaskaid = testscores.alaskaid 
 		WHERE year = '$year' and test = '$test' order by fname, lname", ARRAY_A);

 $body .= "<form name=std action='.?cmd=editTestScores&module=testing' method = post>
 
 <input type=hidden name=year value='$year'>
 <input type=hidden name=test value='$test'>
<table border=1 ><tr><th>Student Id</th><th>Site</th><th>Grade</th><th>Standard</th><th>Value</th><th>Difference</th><th>Level</th><th>Action</th></tr>";
$s = 12;
foreach($ts as $row) {
    while(list($var, $val) = each($row)) ${$var} = $val;
	$button = "<a href='index.php?module=testing&cmd=editTestScores&tid=$tid&year=$year&test=$test&button=Delete' onClick=\"javascript:confirmMsg('DELETE');\">Delete</a>";
	
	$body .= "<tr valign=top>
		<td>$fname $lname ($alaskaid) <input type=hidden name=alaskid[] value='$alaskaid' size=300></td>
		<td><input type=text name=site[] value='$site' size=5></td>
		<td><input type=text name=grade[] value='$gradelevel' size=5></td>
		<td><input type=text name=standard[] value='$standard' size=20></td>
		<td><input type=text name=value[] value='$value' size=5></td>
		<td><input type=text name=difference[] value='$difference' size=5></td>
		<td><input type=text name=level[] value='$level' size=5></td>
		<td>$button <input type=hidden name=tid[] value='$tid'></td>
		</tr>";

}

$body .= "</table>
<input type=submit name=button value=Save> <input type=reset name=button value='Reset Values'>
</form><br><br>";
/*
$body .= <<<END
	<form name=std action='.?cmd=editQuarter' method = post>
		Year: <input type=text name=year >
		Quarter: <input type=text name=quarter ><br>
		Start: <input type=text name=start >
		Finish: <input type=text name=finish ><br>
		<input type=submit name=button value='Add Entry'>
	</form>
END;
*/
include ("template.inc");


?>
