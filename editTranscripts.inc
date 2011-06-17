<?php
 $sid= $_GET['sid'];
 $subject = $_GET['subject'];
 $subject1 = "$subject._";
 $subject2 = "$subject.__";
 
 if($_GET['subcmd'] == 'delete') {
 	$sql = "DELETE FROM transcript WHERE studentid='$sid' and subjectid='{$_GET['subjectid']}' and year = '{$_GET['year']}' and quarter='{$_GET['quarter']}' LIMIT 1 ";
// 	echo $sql;
 	$db->get_results($sql);
 	logHistory("Transcript DELETE", addslashes($sql));
 } else if ($_GET['subcmd'] == 'add') {
 	$timeframe = "{$_GET['quarter']}:{$_GET['year']}-" . substr($_GET['year']+1, -2);
 	$schoolinfo = explode('-', $_GET['school']);
 	$subjectid = "$subject.{$_GET['subjectlevel']}";
 	$sql = "INSERT INTO transcript SET
 				studentid='$sid',
 				subjectname='{$_GET['subjectname']}',
 				subjectid='{$subjectid}',
				schoolid='{$schoolinfo[0]}',
 				schoolname='{$schoolinfo[1]}',
 				year='{$_GET['year']}',
 				quarter='{$_GET['quarter']}',
 				score='{$_GET['score']}',
 				gpa='{$_GET['gpa']}',
 				timeframe='$timeframe'
 				";
 	$db->get_results($sql);
 	logHistory("Transcript INSERT", addslashes($sql));
} else if ($_GET['subcmd'] == 'save') {
	for($i = 0; $i <= count($_POST['change']); $i++) {
		if($_POST['change'][$i] == 'yes') {
			$sql = "UPDATE transcript
					SET 
						subjectname='{$_POST['subjectname'][$i]}',
						subjectid='{$_POST['subjectid'][$i]}',
						schoolid='{$_POST['schoolid'][$i]}',
						schoolname='{$_POST['schoolname'][$i]}',
						score='{$_POST['score'][$i]}',
						gpa='{$_POST['gpa'][$i]}'				
					WHERE
						studentid ='$sid' and
 						subjectid='{$_POST['subjectid'][$i]}' and
 						timeframe='{$_POST['timeframe'][$i]}'
					";	
			$db->get_results($sql);
 			logHistory("Transcript UPDATE", addslashes($sql));
		}
	}
}
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

 $body .= "
 <script>
 function ModifyChange(p) {
 	item = document.getElementById('ch'+p);
 	item.value = 'yes';
 }
 </script> 
 <form name=std action='.?cmd=editTranscripts&subcmd=save&sid=$sid&subject=$subject' method = post>
<table border=1 width=600><tr><th></th><th>Subject Id</th><th>Timeframe</th><th>Subject Name</th><th>Score</th><th>School Id</th><th>School Name</th><th>GPA</th></tr>";
$s = 12;
$i=0;
foreach($ts as $row) {
    while(list($var, $val) = each($row)) ${$var} = $val;
	$button = "<a href='index.php?cmd=editQuarter&year=$year&quarter=$quarter&button=Delete'>Delete</a>";
	$body .= "<tr valign=top>
	<td><a href=?cmd=editTranscripts&subcmd=delete&sid=$sid&subject=$subject&subjectid=$subjectid&year=$year&quarter=$quarter onclick=\"return confirmMsg('Should I delete this entry?');\">Delete</a></td>
		<td>$subjectid<input type=hidden name=subjectid[$i] value='$subjectid'>
			<input type=hidden id=ch$i name=change[$i] value='no'>
		</td>
		<td>$timeframe<input type=hidden name=timeframe[$i] value='$timeframe'></td>
		<td><input type=text name=subjectname[$i] value='$subjectname' size=20 onchange=ModifyChange('$i');></td>
		<td><input type=text name=score[$i] value='$score' size=5 onchange=ModifyChange('$i');></td>
		<td><input type=text name=schoolid[$i] value='$schoolid' size=5 onchange=ModifyChange('$i');></td>
		<td><input type=text name=schoolname[$i] value='$schoolname' size=20 onchange=ModifyChange('$i');></td>
		<td><input type=text name=gpa[$i] value='$gpa' size=5 onchange=ModifyChange('$i');></td>
		</tr>";
	$i++;

}

$body .= "</table>
<input type=submit name=button value=Save> <input type=reset name=button value='Reset Values'>
</form><br><br>";

$schools = $db->get_results("SELECT concat(schoolnumber,'-',name) as id, name FROM site", ARRAY_A);
$schooloption = getOptionList($schools, $_GET['school']);
$qoptions = getOptionList(array(array('id'=>'Q1', 'name'=>'Q1'), array('id'=>'Q2', 'name'=>'Q2'), array('id'=>'Q3', 'name'=>'Q3'), array('id'=>'Q4', 'name'=>'Q4')), $_GET['quarter']);
$soptions = getOptionList(array(array('id'=>'EMG', 'name'=>'EMG'), array('id'=>'DEV','name'=>'DEV'), array('id'=>'PRO','name'=>'PRO'), array('id'=>'ADV', 'name'=>'ADV')), $_GET['score']); 
$goptions = getOptionList(array(array('id'=>'0', 'name'=>'0'), array('id'=>'1','name'=>'1'), array('id'=>'2','name'=>'2'), array('id'=>'3', 'name'=>'3'),array('id'=>'4', 'name'=>'4')), $_GET['gpa']); 
$body .= <<<END
Score - what the student got for the quarter<br>
GPA - The grading that was given for that particular year:quarter for the particular subject<br>
Year - base year that the grade happened<br>
	<form name=std method = get>
		<input type=hidden name=sid value='$sid'>
		<input type=hidden name=subject value='$subject'>
		<input type=hidden name=cmd value=editTranscripts>
		<input type=hidden name=subcmd value=add>
		Year: <input type=text name=year value='{$_GET['year']}'>
		Quarter: <select name=quarter>$qoptions
			</select><br>
		Level for ({$_GET['subject']}): <input type=text name=subjectlevel value='{$_GET['subjectlevel']}'>
		Subject Name: <input type=text name=subjectname value='{$_GET['subjectname']}' ><br>
		School: <select name=school>$schooloption</select><br>
		Score: <select name=score>$soptions
			</select><br>
		GPA: <select name=gpa>$goptions
			</select><br><br>
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
