<?php

$type = $_GET['type'];
$notes = $_GET['notes'];


$msg = "Type: $type
Notes: $notes";

sendMailDart ("DART - no privilege error", $msg);

$body .= "<br><br><font size=4>Sorry you have attempted to go to a page you do not have sufficient privileges to visit.</font><br><br>TYPE: $type<br>NOTES: $notes<br>";

include ('template.inc');

?>
