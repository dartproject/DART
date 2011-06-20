<?php
// Empty table => TRUNCATE TABLE `loadtable` 

$type = $_POST['type'];

echo ("Type: $type<br>");

if($type == 'grades') {
  if(uploadFiles('param1,param2,param3,param4,param5,param6,param7,param8'))
    { updateUploadedGrades(); }
} else if ($type == 'studentlevel') {
  if(uploadFiles('param1,param2,param3,param4,param5,param6'))
    { updateUploadedLevels(); }
} else if ($type == 'attendance') {
  if(uploadFiles('param1,param2,param3,param4', "\r"))
    { updateAttendance(); }
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
   $marksql = "update loadtable,grades set mark = 'X' where studentid = param1 and subject = param3 and level = param4 and std = param5";
   $db->get_results($marksql);
   $num1 = $db->rows_affected; //$db->rows_affected 
   $gradessql = "select * from loadtable where mark != 'X'"; 
   $newgrades = $db->get_results($gradessql);
   $num2 = $db->num_rows;
   echo ("Group number: $igrp<br>Number already in database: $num1<br>Number of new update: $num2<br>");
   foreach ($newgrades as $grade) {
      $studentid = $grade->param1;
      $type = $grade->param2;
      $subject = $grade->param3;
      $level = $grade->param4;
      $std = $grade->param5;
      $value = $grade->param6;
      $num = $grade->param7;
      $storecode = $grade->param8;      
      $instertsql = "insert grades
                      SET studentid ='$studentid',
                          subject = '$subject',
                          level = '$level',
                          std = '$std',
                          value = '$value',
                          num = '$num',
                          storecode = '$storecode',
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
      $til = $grade->param6;
      $instertsql = "insert studentlevel
                      SET studentid ='$studentid',
                          subject = '$subject',
                          level = '$level',
                          start = '$start',
                          final = '$final',
                          til = '$til',
                          igrp = '$igrp'";
//       echo ($instertsql . "<br>");
      $db->get_results($instertsql);
     echo (".");
     if(fmod($i++,70) == 0) { echo ("<br>"); }
   }
}

function updateAttendance () {
   global $db, $currentUserID;

   $sql = "update loadtable,student set present = param3, absent = param4 where studentid = param2";
   echo $sql;
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
