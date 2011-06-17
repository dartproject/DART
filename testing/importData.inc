<?php

if(!PDisplayB(B14) ) {
	Header("Location: index.php?cmd=noPrivilege&type=Testing&notes=Can not see testing data");
}

// INSERT INTO testscores (col1, col2, col3) SELECT col1, col2, col3 FROM table2 WHERE col4='some value'

$action = $_POST['action'];
$button = $_POST['button'];

if($button == 'delete') {
	$scores = $_POST['scores'];
	$test = strtok($scores, "_");
	$year = strtok("_");
	$sql = "Delete from testscores where test='$test' and year = '$year'";
//	$body .= "$sql<br>";
	$db->query($sql);
	$body .= "DELETED $test-$year<br>";
}
$menu = topmenu();

$body .= "$menu<table><tr><td>
			TerraNova Test<br>
			<form action='index.php?module=testing&cmd=compare&testtype=TerraNova' method=post enctype=\"multipart/form-data\" >
				<input type=hidden name=action value=TerraNova>
				<input type=text name=year value='$CurrentYear' size=6>
				<input type=file name=importfile>
				<input type=submit name=button value=import>
			</form></td></tr>
		  <tr><td>
			PPVT Test<br>
			<form action='index.php?module=testing&cmd=compare&testtype=PPVT' method=post enctype=\"multipart/form-data\" >
				<input type=hidden name=action value=PPVT>
				<input type=text name=year value='$CurrentYear' size=6>
				<input type=file name=importfile>
				<input type=submit name=button value=import>
			</form></td></tr>
		  <tr><td>
			ELP Test<br>
			<form action='index.php?module=testing&cmd=compare&testtype=ELP' method=post enctype=\"multipart/form-data\" >
				<input type=hidden name=action value=ELP>
				<input type=text name=year value='$CurrentYear' size=6>
				<input type=file name=importfile>
				<input type=submit name=button value=import>
			</form></td></tr>
		  <tr><td>
			ESP Test<br>
			<form action='index.php?module=testing&cmd=compare&testtype=ESP' method=post enctype=\"multipart/form-data\" >
				<input type=hidden name=action value=ESP>
				<input type=text name=year value='$CurrentYear' size=6>
				<input type=file name=importfile>
				<input type=submit name=button value=import>
			</form></td></tr>
		  <tr><td>
			SBA Test<br>
			<form action='index.php?module=testing&cmd=compare&testtype=SBA' method=post enctype=\"multipart/form-data\" >
				<input type=hidden name=action value=SBA>
				<input type=text name=year value='$CurrentYear' size=6>
				<input type=file name=importfile>
				<input type=submit name=button value=import>
			</form></td></tr>
		  <tr><td>
			HSGQE Test<br>
			<form action='index.php?module=testing&cmd=compare&testtype=HSGQE' method=post enctype=\"multipart/form-data\" >
				<input type=hidden name=action value=HSGQE>
				<input type=text name=year value='$CurrentYear' size=6>
				<input type=file name=importfile>
				<input type=submit name=button value=import>
			</form></td></tr>
		  </table>";
		  
$tests = getTestOptions();

$body .= "<hr>
DELETE Test Scores
<form action='' method=post>
<select name=scores>
	<option value=''>- select test -</option>
	$tests
</select>
<input type=submit value=delete name=button onClick='javascript:return (confirmMsg(\"Do you really want to delete this years test\"));'>
</form>
";
function getTestOptions() {
	global $db;
	
	$sql = "SELECT DISTINCT (concat( test, \"_\", year)) as value, test, year FROM testscores ORDER BY test, year";
	$results = $db->get_results($sql, ARRAY_A);
//	print_r($results);
	foreach ($results as $row ) {
		$str .= "<option value='{$row['value']}'>{$row['test']} {$row['year']} </option>\n";
	}
	return($str);
}

/*
function uploadFile($tmpname, $uploadFile) {

    @unlink($uploadFile);    
    if (move_uploaded_file($tmpname, $uploadFile)) {
//       echo ("Upload Successful<br>");
       return (TRUE);
    } else {
       echo ("Upload Failured");
       return(FALSE);
    }
}

function importFile($file) {
	global $db;
	
  for($i = 1; $i <= 200; $i++) {
	$params .= $params == ""? "p$i" : ",p$i";
  }
  $db->show_errors();
  $empty = "TRUNCATE TABLE `tmpimport`";
  $db->query($empty);
//  echo ("Load Table Emptied<br>");
  $load = "LOAD DATA LOCAL INFILE '$file'
            INTO TABLE tmpimport
			FIELDS TERMINATED BY ',' ENCLOSED BY '\"'
            LINES TERMINATED BY '\n'
           ($params)";
//  echo ("Load: $load<br>");
  $db->query($load);
  $select = "select * from tmpimport";
  $db->query($select);
  $num = $db->num_rows;
  return ("Students Loaded ($num) $test<br>");

}
*/
include_once ("template.inc");
?>