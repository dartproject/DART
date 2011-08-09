<?php
// Empty table => TRUNCATE TABLE `loadtable` 

$type = $_POST['type'];

echo ("Type: $type<br>");

if($type == 'grades') {
  if(uploadFiles('param1,param2,param3,param4,param5'))
    { updateUploadedGrades(); }
} else if ($type == 'studentlevel') {
  if(uploadFiles('param1,param2,param3,param4,param5'))
    { updateUploadedLevels(); }
} else if ($type == 'attendance') {
  if(uploadFiles('param1,param2,param3'))
    { updateAttendance(); }
}
function uploadFiles ($params) {
    $tmpdir = $_FILES['upload_tmp_dir'];
    $tmpdir = '/tmp/';
    $tmpname = $_FILES['gradefile']['tmp_name'];
    $uploadFile = $_FILES['gradefile']['name']; 
    $NewFile = $tmpdir . $uploadFile;
    
    echo ("File Information => tmpdir: $tmpdir tmpname: $tmpname uploadFile: $uploadFile File: $NewFile<br>");
    
    @unlink($NewFile);
    
    if (move_uploaded_file($tmpname, $NewFile)) {
        echo ("Upload Successful<br>");

        $terminated="\r";
        $fd = fopen($NewFile,'r');
        while ($fd && !feof($fd)) {
            $line = fgets($fd, 64);
            if(preg_match('/\r\n/', $line)) { // Windows
    			$terminated = "\r\n";
    			break;
    		} else if(preg_match('/\r/', $line)) { // Old Mac OS
    			$terminated = "\r";
    			break;
    		} else if(preg_match('/\n/', $line)) { // Linux, Mac OS X
    			$terminated = "\n";
    			break;
    		}
    	}
       //printFile($NewFile);
       importUploadLoadTable ($NewFile, $params, $terminated);
       return (TRUE);
    } else {
         echo ("Upload Failured");
         return(FALSE);
    }
}

function printFile($filename) {
    ini_set('auto_detect_line_endings', true);
    $lines = file($filename);
    
    foreach ($lines as $line_num => $line) {
       debugPrint ("Line #<b>{$line_num}</b> : " . htmlspecialchars($line) . "<br />\n");
    }
}

function importUploadLoadTable ($file, $params, $terminated) {
  global $db, $dbuser, $dbpassword, $dbname, $dbhose;
  
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


function updateUploadedGrades () {
   global $db, $currentUserID;
// Once grades have been uploaded to loadtable
// mark grades
   $grpsql = "insert importgrp set userid = '$currentUserID', type='grades'";
   debugPrint("GRP sql: $grpsql<grp>");
   $db->get_results($grpsql);
   $igrp = $db->insert_id;
   $marksql = "update loadtable,grades set mark = 'X' where studentid = param1 and subject = param2 and level = param3 and std = param4";
   $db->get_results($marksql);
   $num1 = $db->rows_affected; //$db->rows_affected 
   $gradessql = "select * from loadtable where mark != 'X'"; 
   $newgrades = $db->get_results($gradessql);
   $num2 = $db->num_rows;
   echo ("Group number: $igrp<br>Number already in database: $num1<br>Number of new update: $num2<br>");
   foreach ($newgrades as $grade) {
      $studentid = $grade->param1;
      $subject = $grade->param2;
      $level = $grade->param3;
      $std = $grade->param4;
      $value = $grade->param5;
      $instertsql = "insert grades
                      SET studentid ='$studentid',
                          subject = '$subject',
                          level = '$level',
                          std = '$std',
                          value = '$value',
                          igrp = '$igrp'";
//       echo ($instertsql . "<br>");
      $db->get_results($instertsql);
     echo (".");
     if(fmod($i++,70) == 0) { echo ("<br>"); }
   }
}

function updateUploadedLevels () {
   global $db, $currentUserID;
// Once grades have been uploaded to loadtable
// mark grades
   $grpsql = "insert importgrp set userid = '$currentUserID', type='studentlevel'";
   debugPrint("GRP sql: $grpsql<grp>");
   $db->get_results($grpsql);
   $igrp = $db->insert_id;
   $marksql = "update loadtable,studentlevel set mark = 'X' where studentid = param1 and subject = param2 and level = param3";
   $db->get_results($marksql);
   $num1 = $db->rows_affected; //$db->rows_affected 
   $slsql = "select * from loadtable where mark != 'X'"; 
   $sls = $db->get_results($slsql);
   $num2 = $db->num_rows;
   echo ("Group number: $igrp<br>Number already in database: $num1<br>Number of new update: $num2<br>");
   foreach ($sls as $sl) {
      $studentid = $sl->param1;
      $subject = $sl->param2;
      $level = $sl->param3;
      $start = $sl->param4;
      $final = $sl->param5;
      $instertsql = "insert studentlevel
                      SET studentid ='$studentid',
                          subject = '$subject',
                          level = '$level',
                          start = '$start',
                          final = '$final',
                          igrp = '$igrp'";
      debugPrint($instertsql . "<br>");
      $db->get_results($instertsql);
     echo (".");
     if(fmod($i++,70) == 0) { echo ("<br>"); }
   }
}

function updateAttendance () {
   global $db, $currentUserID;

   $sql = "update loadtable,student set present = param2, absent = param3 where studentid = param1";
   debugPrint($sql);
   $db->get_results($sql);
   $num = $db->rows_affected; //$db->rows_affected 
   echo ("<br>Attendance update for $num");
}

/**************************************************
function importUploadGrades ($dir) {
  global $db, $dbuser, $dbpassword, $dbname, $dbhose;
  
  $db->show_errors();
  $empty = "TRUNCATE TABLE `loadtable`";
  $db->get_results($empty);
  echo ("Load Table Emptied<br>");
  $load = "LOAD DATA LOCAL INFILE '". $dir . "grades_upload.tab'
            INTO TABLE loadtable
            FIELDS TERMINATED BY '\t'
            LINES TERMINATED BY '\n'
           (param1,param2,param3,param4,param5,param6,param7,param8)";
  $db->query($load);
  $select = "select * from loadtable";
  $db->query($select);
  $num = $db->num_rows;
  echo ("Load Table Loaded ($num) $test<br>");
}
**************************************************/

?>
