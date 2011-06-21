<?php

include_once('lib/functions.inc');

$Display = Privilege(A10);


if($Display != 'none') {
	$site = ($Display == 'site') ? $currentMySite : $_GET['site'];

	$end = $_GET['endOutput'];
	$start = $_GET['startOutput'];
	$toggle = $_GET['toggle'];
	
	$display ="Show data from {$_GET['start']} - {$_GET['end']} for {$_GET['site']}<br>";
	
	if($_GET['button'] != '') {
		$body = queryToggle($start, $end, $site, $toggle);
		$body .= showToggleNum($start, $end, $display, $site, $toggle);
	} else {
		$body = queryToggle($start, $end, $site, $toggle);
	}
} else {
	echo "You do not have the correct privledges";
}
function queryToggle($start, $end, $site, $toggle) {

	${"toggle_".$_GET['toggle']} = 'selected';
	$base = "https://dart.bssd.org/";
	$options = getSitesOptions($site);

	$str = <<<END
	<style type="text/css">
		@import "$base/jquery.datepick.package/jquery.datepick.css";
	</style>
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
	<script type="text/javascript" src="$base/jquery.datepick.package/js/jquery.datepick.js"></script>
	<style type="text/css">
		@import "http://keith-wood.name/css/jquery.datepick.css";
	</style>
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
	<script type="text/javascript" src="http://keith-wood.name/js/jquery.datepick.js"></script>	<script>
	$(function() {
		$('#start').datepick();
		$('#end').datepick();
	});
// format spec => sepcification, format Date live input, format output


	</script>
	<form method=get>
		<input type=hidden name=cmd value=count>
		Start: <input id=start type=text name=start value='{$_GET['start']}'>
				<input id=startOutput type=hidden name=startOutput  value='{$_GET['startOutput']}'> 
		END: <input id=end type=text name=end value='{$_GET['end']}'> 
				<input id=endOutput type=hidden name=endOutput  value='{$_GET['endOutput']}'> 
		Site: <select name=site>
		<option value=''>District Wide</option>
		$options
		</select>
		Type: <select name=toggle>
			<option value='teacher'>Teacher</option>
			<option value='student' $toggle_student >Student</option>
		</select>
		<input type=submit name=button value=go>
	</form>
	<script>
	$('#start').datepick({onSelect: reformatDate}); 
     
	function reformatDate() { 
		$('#startOutput').val($.datepick.formatDate( 
			"@", $('#start').datepick('getDate')[0])); 
	}

	$('#end').datepick({onSelect: reformatDateEnd}); 
	function reformatDateEnd() { 
		$('#endOutput').val($.datepick.formatDate( 
			"@", $('#end').datepick('getDate')[0])); 
	}

</script>
END;

	return($str);
}
function showToggleNum($start, $end, $display, $site='', $toggle='') {
	global $db;
	
	if($toggle == 'student') {
		$query = ($site == '' )? '' : " and student.site = '$site'";
		$sql = "SELECT fname,lname, count(history2.studentid) as c, student.studentid as sid, site from history2, student 
				WHERE
					history2.type = 'toggle' and
					history2.timestamp > '$start' and 
					history2.timestamp < '$end' and 
					student.studentid = history2.studentid and
					history2.std != 'comment'
					$query
				GROUP BY history2.studentid
				ORDER BY site, student.lname, student.fname
					";
//		echo $sql ."<br>";
		
		
		$r1 = $db->get_results($sql, ARRAY_A);
		foreach($r1 as $row) {
			$persons[$row['sid']]['toggle'] = $row['c'];
			$persons[$row['sid']]['name'] = "{$row['fname']} {$row['lname']} ({$row['studentid']})";
			$persons[$row['sid']]['site'] = $row['site'];
			$persons[$row['sid']]['studentid'] = $row['sid'];
			$persons[$row['sid']]['comments'] = 0;
		}
		$sql = "SELECT fname,lname, count(history2.studentid) as c, student.studentid as sid, site from history2, student 
				WHERE
					history2.type = 'toggle' and
					history2.timestamp > '$start' and 
					history2.timestamp < '$end' and 
					student.studentid = history2.studentid and
					history2.std = 'comment'
					$query
				GROUP BY history2.studentid
				ORDER BY site, student.lname, student.fname
					";
//		echo $sql;
		
		$r2 = $db->get_results($sql, ARRAY_A);
		foreach($r2 as $row) {
			$persons[$row['sid']]['comments'] = $row['c'];
		}
	} else {
		$query = ($site == '' )? '' : " and user.site = '$site'";
		$sql = "SELECT name, count(history2.type) as c, user.userid, site from history2, user 
				WHERE
					history2.type = 'toggle' and
					history2.timestamp > '$start' and 
					history2.timestamp < '$end' and 
					user.userid = history2.userid and
					history2.std != 'comment'
					$query
				GROUP BY userid
				ORDER BY site, user.name
					";
	//	echo $sql ."<br>";	
		$r1 = $db->get_results($sql, ARRAY_A);
		foreach($r1 as $row) {
			$persons[$row['userid']]['toggle'] = $row['c'];
			$persons[$row['userid']]['name'] = $row['name'];
			$persons[$row['userid']]['site'] = $row['site'];
			$persons[$row['userid']]['userid'] = $row['userid'];
			$persons[$row['userid']]['comments'] = 0;
		}
		$sql = "SELECT count(*) as c, user.userid from history2, user 
				WHERE
					history2.type = 'toggle' and
					history2.timestamp > '$start' and 
					history2.timestamp < '$end' and 
					user.userid = history2.userid and 
					history2.std = 'comment'
					$query
				GROUP BY userid
				ORDER BY site, user.name
					";
	//	echo $sql;
		
		$r2 = $db->get_results($sql, ARRAY_A);
		foreach($r2 as $row) {
			$persons[$row['userid']]['comments'] = $row['c'];
		}
	}
	$body .= "$display<table border=1>";
	foreach($persons as $p) {
		$filter = ($toggle == 'student') ? "student={$p['studentid']}" : "user={$p['userid']}";
		$link1 = "<a href=/?cmd=history&toggletype=std&$filter&startdate={$_GET['start']}&startOutput={$_GET['startOutput']}&enddate={$_GET['end']}&endOutput={$_GET['endOutput']}&site=$site>{$p['toggle']}</a>";
		$linkcomments = "<a href=/?cmd=history&toggletype=comment&$filter&startdate={$_GET['start']}&startOutput={$_GET['startOutput']}&enddate={$_GET['end']}&endOutput={$_GET['endOutput']}&site=$site>{$p['comments']}</a>";
		$body .= "<tr><td>{$p['name']}</td><td>({$p['site']})</td><td>$link1</td><td>$linkcomments</td></tr>";
	}
	$body .= "</table>";
	return($body);
}
			
include ("template.inc");

?>
