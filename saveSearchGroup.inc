<?php

     $listsql = URLdecode($_POST['sql']);
     $name = $_POST['name'];
     $type = $_POST['type'];

//	$body .= "$name<br>$listsql";
	
	
	$listsql = addslashes ($listsql);

	$sql = "INSERT INTO lists set lists.sql = '$listsql', lists.kind='search', type='$type', userid = '$currentUserID', listname = '$name' ";

//	echo $sql;
	$db->get_results($sql);

/*	echo getListStudents('7306') ."<br>";
	echo getListStudents('7309') ."<br>";
	echo getListStudents($db->insert_id) ."<br>";
*/
	$body .= "<h1>Search Saved: $name</h1>";
	include("template.inc");
?>
