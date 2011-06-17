<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

if(Privilege(A28) == 'district') {
   $district = getNotes('Admin');
}

if(($currentMySite != "Admin") and (Privilege(A28) != 'none')) {
  $snotes = getNotes($currentMySite);
}

if($district['important'] <> "" or $district['warning'] <> "" or $district['tip'] <> "") {
    $body .= '<font size="4" color="#cc0000">DART System Status &amp; Reminders</font>';
    }

if($district['important'] <> "") {
   $body .= "<div class=\"noteimportant\">" . $district['important'] . "</div>";
}

if($district['warning'] <> "") {
   $body .= "<div class=\"notewarning\">" . $district['warning'] . "</div>";
}

if($district['tip'] <> "") {
   $body .= "<div class=\"notetip\">" . $district['tip'] . "</div>";
}

if($snotes['important'] <> "" or $snotes['warning'] <> "" or $snotes['tip'] <> "") {
    $body .= "<font size=\"4\" color=\"#cc0000\">DART Site $currentMySite System Status &amp; Reminders</font>";
    }

if($snotes['important'] <> "") {
   $body .= "<div class=\"noteimportant\">" . $snotes['important'] . "</div>";
}

if($snotes['warning'] <> "") {
   $body .= "<div class=\"notewarning\">" . $snotes['warning'] . "</div>";
}

if($snotes['tip'] <> "") {
   $body .= "<div class=\"notetip\">" . $snotes['tip'] . "</div>";
}

$title = "Home Page";

$body .="<font size=\"4\">DART: System Introduction<br></font>
				<div align=\"left\">
					<font size=\"2\">Welcome to the BSSD Data Analysis and Reporting Toolkit system - or DART.<br>
						<br>
						DART is a database system which allows the tracking and reporting of learner progress on a series of goal areas. It is unique for four reasons:</font>
					<ul>
						<li type=\"circle\"><font size=\"2\">DART is totally learner-centered! - DART does not rely on teacher and student schedules.</font>
						<li type=\"circle\"><font size=\"2\">DART is flexible enough to track any standards or outcomes for an organization, and give useful analysis of needs.</font>
						<li type=\"circle\"><font size=\"2\">DART is Open Source - This means is free, and that development and support takes place by users themselves.</font>
						<li type=\"circle\"><font size=\"2\">DART is Modular - Rather than telling users what data modules they need, users contribute modules that solve problems.</font>
					</ul>
					<p><font size=\"2\">For BSSD, DART tracks student progress through our 9 Content Areas, and the various levels within each Content Area. For a list, and detailed information about this BSSD Model, please see our explanation on the <a title=\"BSSD Standards Information\" href=\"http://wiki.bssd.org/index.php/Standards_Information\" target=\"_blank\">BSSD OpenContent website</a>.<br>
							<br>
							Each standard and assessment task which makes up a level is tracked, and each user gets customized information about group and individual progress. All reports and level changes are done at the school building level, and the District Office maintains current student enrollment data to be synchronized with the PowerSchool SIS.</font></p>
					<p><font size=\"2\">Instructional needs and weaknesses are highlighted using ideas similar to &quot;tag clouding&quot; to produce weighted lists of potential areas of focus. These are keyed directly, and hot-linked to </font></p>
					<p><font size=\"2\">Alerts go automatically out to teachers, students, parents and administrators when key events occur.</font></p>
					<p><font size=\"2\">For detailed information about the DART project, or to find staff development resources for system users, see the <a title=\"DART Project Information\" href=\"http://wiki.bssd.org/index.php/DART_System\">DART wiki</a>.</font></p>
					
        </div>";

include ("template.inc");

?>
