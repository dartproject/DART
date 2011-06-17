<?php

  include_once ("./testing/testing_functions.inc");
  include_once ("./graduation_report_aux.inc");
  
  	$body .= getStyle();
	$credit = "<img src=\"http://sparklines.bitworking.info/spark.cgi?type=impulse&d=2,2,2,2,2,2&height=30&limits=0,2&upper=0&above-color=MediumSeaGreen&below-color=red&width=6\" alt=\"\" border=\"0\">";
	$nocredit = "<img src=\"http://dart.bssd.org/images/1pix.gif\" alt=\"\" border=\"0\">";

	$id = $_GET['student_id'];
	$debug = $_GET['debug'] != '' ? true : false;
//	$id = '530105'; // 530105'; //
//	$id = '10219';

	$student = getStudentInfo($id);
	$var[] = "[name]"; $val[] = $student['fname'] . " " . $student['lname'];
	$var[] = "[school]"; $val[] = $student['village'];
	$var[] = "[tests]"; $val[] = reportHSGQE($id);
	getStudentDataForGraduation($id, &$data, $debug);
	$ans = overAllGPA($id); // 3.857
	$data['gpadisplay'] = $ans['gpa'];
	$data['credit'] = $ans['credit'];
// echo  $ans['gpa'] . $ans['credit'];
//	$data['gpadisplay'] = number_format($data['score']/ $data['scorecredit'] , 2);
	$data['gpa'] = $debug ? "GPA Computed differently no more debug" : "";
//	$data['gpa'] = $debug ? $data['credit'] . "Credits for Score: " . $data['scorecredit'] . " Score:" . $data['score'] . " GPA: " . $data['score']/ $data['scorecredit'] : "";
//	if($debug) print_r($data);
	while(list($var1, $val1) = each($data)  ) { $var[] = "[$var1]"; $val[] = $val1; }
	$filestr = file_get_contents("./graduation_report.html");
	$body .= str_replace($var, $val, $filestr);
		
	include("template.inc");
	

?>