<?php

// ==================================================================

//  Author: Robert Joseph (dart@vizmotion.com)

//	 Web: http://wiki.bssd.org/index.php/DART_System

// ==================================================================



$id = $_GET['id'];



$url = $_SERVER['PHP_SELF'];

$close = $_GET['close'];

if($_POST['saveButton'] <> "") {

//	saveTable(spedSQL(), $HTTP_POST_VARS);

	saveSped($_POST);

    $body = "Information saved";

}

	$student = getStudentInfo($id);

	$body .= "<h1>" . $student['fname'] . " " . $student['lname'] . "</h1>";

	$sped = getSped($id);

	$table = editTable(spedArray(), $sped, 4);

	$exitreason = $sped['exitreason'];

	$spedcomments = $sped['spedcomments'];

	while(list($var, $val) = each($_GET) ) {
		$params .= $params != '' ? '&' : '?';
		if($var == 'close') $val = urlencode($val);
		$params .= "$var=$val";
	}
    $body .= "<form action=$url$params method=post>

    			<input type=submit name=saveButton value=Save>

    			<input type=button value=Close onClick=javascript:window.location=\"./index.php?{$_GET['close']}\">

				<input type=hidden name=close value='{$_GET['close']}'>
				<input type=hidden name=studentid value='$id'>
				
    				$table

<!--    			Exit Reason: <input type=text name=exitreason value='$exitreason' size=40></br> -->
				<table><tr><td valign=top>Comments: </td><td> <textarea name='spedcomments' cols='100' rows='20' onchange=markChange('spedcomments');>$spedcomments</textarea></td></tr></table>

    			<input type=submit name=saveButton value=Save>

    			<input type=button value=Close onClick=javascript:window.location=\"./index.php?{$_GET['close']}\">    		

    	  </form>";



function spedSQL() {

	$sql = "UPDATE speddata

			SET percent = '{percent}',

				dc = '{dc}',

				code = '{code}',

				entrysped = '{entrysped}',

				iepstart = '{iepstart}',

				iepend = '{iepend}',

				psyreeval = '{psyreeval}',

				splangreeval = '{splangreeval}',

				eser = '{eser}',

				exitdate = '{exitdate}',

				exitreason = '{exitreason}',
				
				spedcomment = '{spedcomment}',

				testac = '{testac}'

			WHERE studentid = '{studentid}'

			" ;

	return ($sql);

}

function spedArray () {

	$i=0; $table[$i]['name'] = "studentid"; $table[$i]['label'] = "studentid"; $table[$i]['type'] = "hidden";
	
//	$i++; $table[$i]['name'] = "sped"; $table[$i]['label'] = "SpEd"; $table[$i]['type'] = "yesno";

	$i++; $table[$i]['name'] = "Sped_Status"; $table[$i]['label'] = "SpEd Status"; $table[$i]['type'] = "select";
		$table[$i]['extra'] = statusOptionArray();

	$i++; $table[$i]['name'] = "percent"; $table[$i]['label'] = "Percentage"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "GoalViewID"; $table[$i]['label'] = "GoalViewID"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "dc"; $table[$i]['label'] = "DC"; $table[$i]['type'] = "select";
		$table[$i]['extra'] = array(
								array("","Select One"),
								array("01","01 - Gifted/Talented"),
								array("02","02 - Cognitive Impairment"),
								array("03","03 - Hearing Impairment"),
								array("04","04 - Speech / Language"),
								array("05","05 - Visual Impairment"),
								array("06","06 - Emotional Disturbance"),
								array("07","07 - Orthopedic Impairment"),
								array("08","08 - Other Health Impairment"),
								array("09","09 Specific Learning Disability"),
								array("10","10- Deaf-Blindness"),
								array("11","11- Multiple Disabilities"),
								array("14","12 - Autism"),
								array("13","13 - Traumatic Brain Injury"),
								array("14","14 - Developmental Delay"),
								array("RE","RE - Referral In Process"),
								array("TNP","TNP - Tested & Not Placed")
							);

	$i++; $table[$i]['name'] = "pcode"; $table[$i]['label'] = "Code"; $table[$i]['type'] = "select";
		$table[$i]['extra'] = array(
								array("","Select One"),
								array("01","01 - Early Childhood Setting"),
								array("02","02 - Early Childhood SpEd Setting"),
								array("03","03 - Home"),
								array("04","04 - Part-time ECE/EC SpEd Setting"),
								array("05","05 - Residential Facility"),
								array("06","06 - Separate School"),
								array("07","07 - In Regular Classroom 80% +"),
								array("08","08 - In Regular Classroom 40 - 79%"),
								array("09","09 - In Regular Classroom 1 - 39%"),
								array("10","10 - Separate Class with <50% non-disabled"),
								array("11","11 - Public Separate School Facility"),
								array("12","12 - Private Separate School Facility"),
								array("13","13 - Public Residential Facility"),
								array("14","14 - Private Residential Facility"),
								array("15","15 - Homebound/Hospital"),
								array("16","16 - Correctional Facility"),
								array("17","17 - Other")
							);

	$i++; $table[$i]['name'] = "entrysped"; $table[$i]['label'] = "Enter Sped"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "iepstart"; $table[$i]['label'] = "IEP Start"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "iepend"; $table[$i]['label'] = "IEP End"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "psyreeval"; $table[$i]['label'] = "Last Psy Eval"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "splangreeval"; $table[$i]['label'] = "Last Sp Lang Eval"; $table[$i]['type'] = "date";

//	$i++; $table[$i]['name'] = "eser"; $table[$i]['label'] = "ESER"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "exitdate"; $table[$i]['label'] = "SpEd Exit Date"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "testac"; $table[$i]['label'] = "Test AC"; $table[$i]['type'] = "yesno";

//		$table[$i]['extra'] = array( array(" ", "select Y/N"), array("Y", "Yes") , array("N", "No") );



	$i++; $table[$i]['name'] = "Last_OT_Eval"; $table[$i]['label'] = "Last_OT_Eval"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "Last_PT_Eval"; $table[$i]['label'] = "Last_PT_Eval"; $table[$i]['type'] = "date";



	$i++; $table[$i]['name'] = "Other_Eval"; $table[$i]['label'] = "Other_Eval"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "Other_Eval_Date"; $table[$i]['label'] = "Other_Eval_Date"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "Current_ESER"; $table[$i]['label'] = "Current_ESER"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "ESER_plus3"; $table[$i]['label'] = "ESER_plus3"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "Latest_Consent"; $table[$i]['label'] = "Latest_Consent"; $table[$i]['type'] = "date";

	$i++; $table[$i]['name'] = "45_Days"; $table[$i]['label'] = "45_Days"; $table[$i]['type'] = "select";
		$table[$i]['extra'] = array(
								array("","Select One"),
								array("0", "0 - completed within 45 school days"),
								array("1", "1 - completed within 45-50 school days"),
								array("2", "2 - completed within 51-60 school days"),
								array("3", "3 - completed within 61-70 school days"),
								array("4", "4 - took longer than 70 school days")
							);

	$i++; $table[$i]['name'] = "Reason_Code"; $table[$i]['label'] = "Reason_Code"; $table[$i]['type'] = "select";
		$table[$i]['extra'] = array(
								array("","Select One"),
								array("0", "0 - Completed within 45 school days"),
								array("1", "1 - Extended illness for child"),
								array("2", "2 - Moved after referral before eligibility"),
								array("3", "3 - Evaluator unable to test due to weather"),
								array("4", "4 - Consent withdrawn by parent"),
								array("5", "5 - Other"),
								array("6", "6 - Parent not produce child for evaluation")
							);
	$i++; $table[$i]['name'] = "SpEd_Exit_Date"; $table[$i]['label'] = "SpEd_Exit_Date"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "SpEd_Exit_Code"; $table[$i]['label'] = "SpEd_Exit_Code"; $table[$i]['type'] = "select";
		$table[$i]['extra'] = array(
								array("","Select One"),
								array("01","01 - Graduated with Diploma"),
								array("02","02 - Graduated with COA"),
								array("03","03 - Reached Maximum Age"),
								array("04","04 - Dropped Out"),
								array("51","51 - Decertified"),
								array("52","52 - Died"),
								array("53","53 - Moved, Continuing SpEd"),
								array("54","54 - Moved, Not Continuing SpEd"),
								array("00","00 - Other"),
							);

	$i++; $table[$i]['name'] = "IEPLessAge3"; $table[$i]['label'] = "IEPLessAge3"; $table[$i]['type'] = "textfield";
		$table[$i]['extra'] = array(
								array("","Select One"),
								array("0", "0 - completed by 3rd birthday"),
								array("1", "1 - Extended illness for child"),
								array("2", "2 - Late referral by ILP"),
								array("3", "3 - No 90 day transition meeting"),
								array("4", "4 - Parent refusal to provide consent"),
								array("5", "5 - Student moved or withdrawn after referral but before IEP implementation"),
								array("6", "6 - Not able to contact parents"),
								array("7", "7 - Other"),
								array("8", "8 - Parent repeatedly fails or refuses to produce the child for evaluation")
							);
	$i++; $table[$i]['name'] = "Trans_Plan"; $table[$i]['label'] = "Trans_Plan"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "ISS"; $table[$i]['label'] = "ISS"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "OSS"; $table[$i]['label'] = "OSS"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "MD_Held"; $table[$i]['label'] = "MD Held"; $table[$i]['type'] = "yesno";

	$i++; $table[$i]['name'] = "Mod_HSGQE"; $table[$i]['label'] = "Mod HSGQE"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "Alt_Assmt"; $table[$i]['label'] = "Alt Assmt"; $table[$i]['type'] = "textfield";



	$i++; $table[$i]['name'] = "Int_Needs"; $table[$i]['label'] = "Int Needs"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "RS_Sp"; $table[$i]['label'] = "RS Sp"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "RS_FM"; $table[$i]['label'] = "RS FM"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "RS_GM"; $table[$i]['label'] = "RS GM"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "RS_Coun"; $table[$i]['label'] = "RS Coun"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "RS_Tran"; $table[$i]['label'] = "RS Tran"; $table[$i]['type'] = "textfield";



	$i++; $table[$i]['name'] = "RS_Other"; $table[$i]['label'] = "RS Other"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "H_Aid"; $table[$i]['label'] = "H Aid"; $table[$i]['type'] = "textfield";

	$i++; $table[$i]['name'] = "LEP_Status"; $table[$i]['label'] = "LEP Status"; $table[$i]['type'] = "view";


	$i++; $table[$i]['name'] = "Add_45_Days"; $table[$i]['label'] = "Add 45 Days"; $table[$i]['type'] = "textfield";


//	$i++; $table[$i]['name'] = "spedcomments"; $table[$i]['label'] = "Comments"; $table[$i]['type'] = "textarea";
//			$table[$i]['width'] = 30; $table[$i]['height'] = 20; 


		
	return($table);

}



function getSped($studentid) {

	global $db;

	

	$sql = "select * from speddata, student 

								 where student.studentid = '$studentid' and 

								 	   speddata.studentid = student.studentid";

	$results = $db->get_results($sql, ARRAY_A);

	if($results[0] == "") {

		$db->get_results("insert speddata set studentid = '$studentid'");

		$results = $db->get_results($sql, ARRAY_A);

	}

	return ($results[0]);

}



include ("template.inc");



?>

