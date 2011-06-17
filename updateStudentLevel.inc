<?php

set_time_limit(0);

include_once("lib/stopwatch.inc");


// *************** LOAD DATA FILES ********************
$BOTTOM = 0;
$TOP = 100000;
$COUNT = 500;

$stopwatch = new stopwatch;
echo "Start stopwatch<br>";
flush();

$sql = "SELECT * FROM studentlevel WHERE final = '0000-00-00' LIMIT $BOTTOM, $TOP"; //  AND studentid = '7000331'

$results = $db->get_results($sql);

$stopwatch->lap("After SQL $sql", true);	

$num = count($results);

$stopwatch->lap("After NUM: $num", true);	
flush();
$i=0;
foreach ($results as $sl) {
	$id = $sl->studentid;
	$subject = $sl->subject;
	$level = $sl->level;
	$oldscore = $sl->progress;
	
	$score = updateSingleLevelScore($id, $subject, $level);
//	echo "$id - $subject - $level - OLD: $oldscore NEW: $score<br>";
	if(fmod($i++, $COUNT) == 0) { 
		$stopwatch->lap("Currently $i out of $num", true);
		flush();
	}
}
$stopwatch->lap("THE END $i out of $num", true);	

?>