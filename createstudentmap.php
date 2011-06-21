<?php

echo "start";


define('DB_HOST', 'localhost');
define('DB_USERNAME', 'dartdb_dartdb');
define('DB_PASSWORD', 'U8zrpJ4f');
define('DB_NAME', 'dartdb_dartdb');
define('WB_PATH', dirname(__FILE__));
define('WB_URL', 'https://dart.bssd.org');

$link = mysql_connect(DB_HOST, DB_USERNAME, DB_PASSWORD);
if (!$link) {
	error('Could not connect: ' . mysql_error());
}
mysql_select_db(DB_NAME);

$sql = "TRUNCATE TABLE studentmap";
mysql_query($sql);

$sql = "ALTER TABLE studentmap AUTO_INCREMENT = 1";
mysql_query($sql);

$sql = "select studentid, gender from student where status = 'Active'";
$records = mysql_query($sql);

echo "here";

$male = getArray('data/male.txt');
$female = getArray('data/female.txt');
$last = getArray('data/last.txt');

$i = 330000;
if($records != "") {
	while($rec = mysql_fetch_array($records, MYSQL_ASSOC)) {
    $id = $rec['studentid']; 
    $gender = $rec['gender'];
//    echo $gender;
    echo ".";
	  if($gender == 'Female') {
       $fname = $female[rand(0, count($female)-1)];
       $lname = $last[rand(0, count($last)-1)];
    } else {
       $fname = $male[rand(0, count($male)-1)];
       $lname = $last[rand(0, count($last)-1)];
    }
		$sql = "INSERT INTO `studentmap` SET 
          studentid = '$id',
          fakealaskaid = '$i',
          fname= '$fname',
          lname= '$lname'
          ";
 //   echo "$sql<br>";
    mysql_query($sql);
    $i++;
	}
}

function getArray($file) {
  $file_handle = fopen($file, "rb");

echo "$file";
//  $i = 0;
  while (!feof($file_handle) ) {
    $info[] = fgets($file_handle);
//    $i++;
//    if ($i == 10) break;
  }
  fclose($file_handle);
  return ($info);
}

?>
