<?php
 $sid= $_GET['sid'];
 $subject = $_GET['subject'];
 $subject1 = "$subject._";
 $subject2 = "$subject.__";
 
 $sql1 = "select studentid as id, concat(fname, ' ', lname) as name from student order by lname";
 $studentOptionList = makeSQLOptions($sql1, $sid);
 $sql2 = "select id, id as name from subjects";
 $subjectOptionsList = makeSQLOptions($sql2, $subject);
 $body .= "<form action=index.php method=get>
 				<input type=hidden name=cmd value='editTranscripts'>
 				<select name='sid' onChange=\"submit()\">
 					$studentOptionList
 				</select>
				<select name='subject' onChange=\"submit()\">
 					$subjectOptionsList
 				</select>
 			</form>";
 			
 $ts = $db->get_results("select * from transcript where studentid = '$sid' and (subjectid LIKE '$subject1' or subjectid LIKE '$subject2') order by year, quarter, subjectid ", ARRAY_A);

 $body .= "<form name=std action='.?cmd=editTranscripts' method = post>
<table border=1 width=600><tr><th>Subject Id</th><th>Timeframe</th><th>Subject.Level name</th><th>Score</th><th>School Id</th><th>School Name</th><th>GPA</th></tr>";
$s = 12;
foreach($ts as $row) {
    while(list($var, $val) = each($row)) ${$var} = $val;
	$button = "<a href='index.php?cmd=editQuarter&year=$year&quarter=$quarter&button=Delete'>Delete</a>";
	
	$body .= "<tr valign=top>
		<td>$subjectid<input type=hidden name=timefram[] value='$subjectid'></td>
		<td>$timeframe<input type=hidden name=timefram[] value='$timeframe'></td>
		<td><input type=text name=subjectname[] value='$subjectname' size=20></td>
		<td><input type=text name=score[] value='$score' size=5></td>
		<td><input type=text name=schoolid[] value='$schoolid' size=5></td>
		<td><input type=text name=schoolname[] value='$schoolname' size=20></td>
		<td><input type=text name=gpa[] value='$gpa' size=5></td>
		</tr>";

}

$body .= "</table>
<input type=submit name=button value=Save> <input type=reset name=button value='Reset Values'>
</form><br><br>";

$body .= <<<END
	<form name=std action='.?cmd=editQuarter' method = post>
		Year: <input type=text name=year >
		Quarter: <input type=text name=quarter ><br>
		Start: <input type=text name=start >
		Finish: <input type=text name=finish ><br>
		<input type=submit name=button value='Add Entry'>
	</form>
END;

include ("template.inc");

function makeSQLOptions($sql, $sid) {
	global $db;

	$results = $db->get_results($sql);
	 
	$pulldown = "<option value=\"\">-- Select One -- </option>";									
	foreach ($results as $res) {
		$sel = ($res->id == $sid) ? "selected": "";
		$pulldown .= "<option value=". $res->id . " $sel>" . $res->name . "</option>";
	}
					
	return ($pulldown);
}


?>
