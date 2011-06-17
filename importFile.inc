<?php

$pnum = $_POST['colnum'];
$term = stripslashes($_POST['lineterminate']);
$fterm = stripslashes($_POST['fieldterminate']);
$enclose = $_POST['enclosed'];

for($i = 1; $i <= $pnum; $i++) {
	$params .= $params == ""? "param$i" : ",param$i";
}
//echo $params;
uploadFiles($params, $term, $fterm,$enclose);

printLoadTable($pnum, 3);

function printLoadTable($num, $linenum){
	global $db;
	echo "<br>PRINTING LOAD TABLE FOR FIRST $linenum ENTRIES<br>";
	$sql = "select * from loadtable limit 1, $linenum";
	$results = $db->get_results($sql, ARRAY_A);
	echo "<table border=1>";
	for($i = 1; $i <= $num; $i++) {
		$param = "param$i";
		echo "<th>" . $param . "</th>";
	}
	foreach($results as $line) {
		echo "<tr>";
		for($i = 1; $i <= $num; $i++) {
			$param = "param$i";
			echo "<td>" . $line[$param] . "</td>";
		}
		echo "</tr>";
	}
	echo "</table>";
}
function uploadFiles ($params, $terminated="\n", $fterminated="\t", $enclose=""){
    $tmpdir = $_FILES['upload_tmp_dir'];
    $tmpdir = '/tmp/';
    $tmpname = $_FILES['importfile']['tmp_name'];
    $uploadFile = $_FILES['importfile']['name']; 
    $NewFile = $tmpdir . $uploadFile;
    
    echo ("File Information => tmpdir: $tmpdir tmpname: $tmpname uploadFile: $uploadFile File: $NewFile<br>");
    
    @unlink($NewFile);
    
    if (move_uploaded_file($tmpname, $NewFile)) {
       echo ("Upload Successful<br>");
       printFile ($NewFile);
       importUploadLoadTable ($NewFile, $params, $terminated, $fterminated, $enclose);
       return (TRUE);
    } else {
       echo ("Upload Failured");
       return(FALSE);
    }
}

function printFile($filename) {
    $lines = file($filename);
    
    foreach ($lines as $line_num => $line) {
       debugPrint ("Line #<b>{$line_num}</b> : " . htmlspecialchars($line) . "<br />\n");
    }
}

function importUploadLoadTable ($file, $params, $terminated, $fterminated, $enclose) {
  global $db, $dbuser, $dbpassword, $dbname, $dbhose;
  
  $db->show_errors();
  $empty = "TRUNCATE TABLE `loadtable`";
  $db->query($empty);
  echo ("Load Table Emptied<br>");
  $load = "LOAD DATA LOCAL INFILE '$file'
            INTO TABLE loadtable
			FIELDS TERMINATED BY '$fterminated' ENCLOSED BY '$enclose'
            LINES TERMINATED BY '$terminated'
           ($params)";
  echo ("Load: $load<br>");
  $db->query($load);
  $select = "select * from loadtable";
  $db->query($select);
  $num = $db->num_rows;
  echo ("Load Table Loaded ($num) $test<br>");
}


/*
$id = $_POST['id'];

if($activity=="Upload") {
    $tmpname = $_FILES['pict_file']['tmp_name'];
    $uploadFile = $_FILES['pict_file']['name']; 
    
    debugPrint("tmpname: $tmpname uploadFile: $pictDIR$uploadFile<br>");
    
    $File = $pictDIR . $uploadFile;
    
    @unlink($File);
//    if(is_file($File)) { echo ("File Unlink Attempt " . unlink($File)); }

    if (move_uploaded_file($tmpname, $File)) {
       debugPrint ("Success");
       updateStudentField($id, 'picture', $uploadFile);
    //   alert("File is valid, and was successfully uploaded.");
    } else {
         debugPrint ("Failure");
    //   alert("Possible file upload attack!");
    }
    
} else {
    $student = getStudentInfo ($id);
    $File = $pictDIR . $student['picture'];
//    echo $File;
//    if(is_file($File)) { unlink($File); }
    updateStudentField($id, 'picture', "");
}



function uploadFiles ($params, $terminated="\n"){
    $tmpdir = $_FILES['upload_tmp_dir'];
    $tmpdir = '/tmp/';
    $tmpname = $_FILES['gradefile']['tmp_name'];
    $uploadFile = $_FILES['gradefile']['name']; 
    $NewFile = $tmpdir . $uploadFile;
    
    echo ("File Information => tmpdir: $tmpdir tmpname: $tmpname uploadFile: $uploadFile File: $NewFile<br>");
    
    @unlink($NewFile);
    
    if (move_uploaded_file($tmpname, $NewFile)) {
       echo ("Upload Successful<br>");
       printFile ($NewFile);
       importUploadLoadTable ($NewFile, $params, $terminated);
       return (TRUE);
    } else {
         echo ("Upload Failured");
         return(FALSE);
    }
}

function printFile($filename) {
    $lines = file($filename);
    
    foreach ($lines as $line_num => $line) {
       debugPrint ("Line #<b>{$line_num}</b> : " . htmlspecialchars($line) . "<br />\n");
    }
}

function importFileIntoTable ($file, $pnum, $terminated) {
  global $db, $dbuser, $dbpassword, $dbname, $dbhose;
  
  for($i = 1, $i <= $pnum; $i++) {
  	$params .= $params == ""? "param$i" : ", param$i";
  }
  echo $params;
  
  $db->show_errors();
  $empty = "TRUNCATE TABLE `loadtable`";
  $db->query($empty);
  echo ("Load Table Emptied<br>");
  $load = "LOAD DATA LOCAL INFILE '$file'
            INTO TABLE loadtable
            FIELDS TERMINATED BY '\t'
            LINES TERMINATED BY '$terminated'
           ($params)";
  debugPrint ("Load: $load<br>");
  $db->query($load);
  $select = "select * from loadtable";
  $db->query($select);
  $num = $db->num_rows;
  echo ("Load Table Loaded ($num) $test<br>");
}
*/
?>
