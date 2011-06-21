<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
include_once ("extraPacingReportFunction.inc");

$mylists = getMyList($currentUserID, 'all');
$ListId = ($_GET['id'] == '') ? $mylists[0]['listid'] : $_GET['id'];

$updateList = "<form name=editList action=index.php method=get>
<input type=hidden name=cmd value=extraPacingReport>
<select name=\"id\" onChange=\"submit()\"><option value=''>-select a list-</option>";

foreach($mylists as $my) {
  $lid = $my['listid'];
  $lname = $my['listname'];
  $updateList .= "<option value=\"$lid\" " . selected ($lid, $ListId) . ">$lname</option>";
  }

$updateList .= "</select> Select to edit list</form>";

$studentList = getListStudents($ListId);


$title = "Pacing Analysis & Scheduling Screen";
$rows = createExtraPacingReport($studentList);

$body .= $updateList . $rows;	

// while ($row['display']
include ("template.inc");
?>
