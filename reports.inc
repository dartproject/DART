<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

include ("sreportFunction.inc");
include("progressReportFunction.inc");
include ("pacingReportFunction.inc");

debugPrint("here");

//$names = $_POST['selectNames'];
$names = getReportListItems($currentUserID);
debugPrint("Names: " . print_r($names, true));

$body = "<html>
<head>
<title>Multiple Reports Page</title>
<link rel=\"stylesheet\" href=\"css/dart.css\" type=\"text/css\">
<body>";

foreach ($names as $stu) {
   $id = $stu['studentid'];
   if($_POST['rcard'] == 'X') {
       $body .= "<DIV style=\"page-break-after:always\">";
       $body .= createSReport($id, "on", "official");  
       $body .= "</DIV>";
   }
   
   if($_POST['rcardwo'] == 'X') {
       $body .= "<DIV style=\"page-break-after:always\">";
       $body .= createSReport($id, "off", "official");  
       $body .= "</DIV>";
   }
   
   if($_POST['paceguide'] == 'X') {
      $body .= "<DIV style=\"page-break-after:always\">";
      $body .= createPacingReport($id, "official");  
      $body .= "</DIV>";
   }
   
  if($_POST['progrep'] == 'X') {
       $body .= "<DIV style=\"page-break-after:always\">";
       $body .= createProgressReport($id, "official");  
       $body .= "</DIV>";
   }

}

$body .= "</body></html>";

echo "<html><body>$body</body></html>";

?>
