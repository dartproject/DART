<?php

set_time_limit(0);

include_once("lib/machine.config.php");
include_once("lib/stopwatch.inc");


$flag = false;

echo "Start stopwatch<br>";
flush();

executeDBFile("./transbackward.inc", $dbname);

function executeDBFile($file, $dbnm) {
	global $dbhost, $dbuser, $dbpassword, $flag;

	$stopwatch = new stopwatch;
	
	echo "FILE: $file DB: $dbnm<br>";
	$db = mysql_connect ($dbhost, $dbuser, $dbpassword);
	echo "Here2<br>";
	mysql_select_db( $dbnm, $db );
	echo "Here3<br>";
	
	$FP = fopen ( $file, 'r' );
	$READ = fread ( $FP, filesize ( $file) );
	
	$READ = explode ( ";\n", $READ );
	echo "At Read Location<br>";
	
	foreach ( $READ AS $RED )
	{
		echo "<br>Start: $RED<br>";
		flush();
		mysql_query ( $RED);
		$stopwatch->lap("End: ", true);
//		exit ();
	}

	echo 'Done';
}

?>