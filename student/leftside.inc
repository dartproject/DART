<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


/********* Build Complete Left Side *************/
$leftside .= "<div align=\"left\">
		<b><font color=\"#0066ff\">Logged In As:</font></b><br>
		<img src=\"http://www.bssd.org/images/dart1.gif\" alt=\"\" height=\"67\" width=\"77\" border=\"0\"><br>
		<b><font color=\"#0066ff\">$currentStudentName</font></b><br>";

/******** Dart Home Information *********/		
$leftside .= "<br><b><font color=\"#0066ff\">DART Info<br></font></b>
		  <img src=\"../images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=logout\">Log Out</a><br>
			<img src=\"../images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=home\">Dart Home</a><br>
			<img src=\"../images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"index.php?cmd=editProfile\">Edit Profile</a><br>
			<img src=\"../images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\"><a href=\"mailto:dart@bssd.org\" target=_blank>Feedback</a><br>";


echo $leftside;
?>
