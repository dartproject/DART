<?php

//$sid = $_POST['sid'];
//$area = $_POST['area'];
//$aid = $_GET['aid'];

echo ("Please wait while your review of $repname is being recorded<br>");
echo ("CMD: $mcmd<br>");
switch($mcmd) {
  case "deleteAction":
	$sid = $_GET['sid'];
	$area = $_GET['area'];
	$aid = $_GET['aid'];
  	deleteAction($aid);
  	break;
  case "addAction":
	$sid = $_POST['sid'];
	$area = $_POST['area'];
  	saveAction($_POST);
	break;	
}

//echo ("Thank You<br>");

//echo ("<a href=\"index.php?module=sip&cmd=showaction&area=$area&id=$sid\">URL </a>");


echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?module=sip&cmd=showaction&area=$area&id=$sid\">");



?>