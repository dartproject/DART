<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$body = "
<div class=\"notetip\">
Welcome to the BSSD Testing Module.
</div>

<table align=center border=1>
";
if(PDisplayB(B13)) {
	$body .= "
		<tr>
			<td>
				<a href=index.php?module=testing&cmd=showGroupTestScores>Show Group Test Scores</a>
			</td>		
		</tr>";
} 
if (PDisplayB(B14)) {
	$body .= "
		<tr>
			<td>
				<a href=index.php?module=testing&cmd=importData>Import Test Scores</a>
			</td>		
		</tr>	
		<tr>
			<td>
				<a href=index.php?module=testing&cmd=editTestScores>Edit Test Scores<a>
			</td>		
		</tr>
	";
}

$body .= "</table>";




include_once ("template.inc");

?>
