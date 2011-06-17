<?php

// ==================================================================

//  Author: Robert Joseph (dart@vizmotion.com)

//	 Web: http://wiki.bssd.org/index.php/DART_System

// ==================================================================



$mylists = getMyList($currentUserID, 'all');

$listid = ($_GET['listid'] == "") ? $mylists[0]['listid'] : $_GET['listid'];



$listInfo = getListInfo($listid);

$listname = $listInfo['listname'];



$listOptions = getOptionList($mylists, $listid);

while(list($var, $val) = each ($_GET) ) {
	$params .= $params != '' ? '&': '';
	$params .= "$var=$val";
}
$params = urlencode($params);
// echo $params;


$spedstatusoptions = statusOptionList($_GET['spedstatus']);

$updateList = "<form name=editList action=index.php method=get>

					<input type=hidden name=cmd value=spedlist>

					<input type=hidden name=module value=sped>
					
					<select name='listid' onChange='submit()'>

						$listOptions

					</select> Select to edit list</form>

				";




$_GET['sortval'] = ($_GET['sortval'] == '') ? 'lname' : $_GET['sortval'];
$_GET['sortdir'] = ($_GET['sortdir'] == '') ? 'ASC' : $_GET['sortdir'];

${'sortval_'.$_GET['sortval']} = 'selected';
${'sortdir_'.$_GET['sortdir']} = 'selected';


$students = getStudentListSep($listid, $_GET);

/*

$sepheader = "

<tr>

<td>Last Name</td>

<td>First Name</td>

<td>Middle Name</td>

<td>Birthday</td>

<td>Age</td>

<td>GR</td>

<td>DC</td>

<td>Code</td>

<td>Entry Sped</td>

<td>IEP Start</td>

<td>IEP End</td>

<td>%</td>

<td>Psy ReEval</td>

<td>Sp Lang ReEval</td>

<td>ESER</td>

<td>Exit Date</td>

<td>Test AC</td>

<td>Editing</td>

</tr>

";

$export = "Last Name\tFirst Name\tMiddle Name\tBirthday\tAge\tGR\tDC\tCode\tEntry Sped\tIEP Start\tIEP End\t%\tPsy ReEval\tSp Lang ReEval\tESER\tExit Date\tTest AC\tEditing\n";

foreach($students as $stu) {

	$fname = commentSpace($stu['fname']);

	$mname = commentSpace($stu['mname']);

	$lname = commentSpace($stu['lname']);

	$grade = commentSpace($stu['grade']);

	$sped = commentSpace($stu['sped']);

	$studentid = $stu['studentid'];

	$bday = commentSpace($stu['bday']);

	$age = commentSpace(age($bday));

	$dc = commentSpace($stu['dc']);

	$code = commentSpace($stu['code']);

	$entrysped = commentSpace($stu['entrysped']);

	$iepstart = commentSpace($stu['iepstart']);

	$iepend = commentSpace($stu['iepend']);

	$percent = commentSpace($stu['percent']);

	$psyreeval = commentSpace($stu['psyreeval']);

	$splangreeval = commentSpace($stu['splangreeval']);

	$eser = commentSpace($stu['eser']);

	$exitdate = commentSpace($stu['exitdate']);

	$testac = commentSpace($stu['testac']);

	$editsped = (($sped == 'Y') ? 

			"<a href='index.php?cmd=spededit&module=sped&id=$studentid&close=$params'>Edit Sped</a>" : 

				(($stu['entrysped'] == "") ?

					"Not Sped":

					"<a href='index.php?cmd=spededit&module=sped&id=$studentid'>Edit Previous Sped</a>"))

				;





$color = fmod($i++, 2) == 0 ? "lightgrey" : "white";

$sepbody .= "<tr bgcolor=$color >

<td nowrap>$lname</td>

<td nowrap>$fname</td>

<td nowrap>$mname</td>

<td nowrap>$bday</td>

<td nowrap>$age</td>

<td>$grade</td>

<td>$dc</td>

<td>$code</td>

<td>$entrysped</td>

<td>$iepstart</td>

<td>$iepend</td>

<td>$percent</td>

<td>$psyreeval</td>

<td>$splangreeval</td>

<td>$eser</td>

<td>$exitdate</td>

<td>$testac</td>

					<td nowrap>

						$editsped | 

						<a href='index.php?cmd=StudentEdit&id=$studentid'>Edit Student</a>

					</td>

			  	</tr>";

$export .= "$lname\t$fname\t$mname\t$bday\t$age\t$grade\t$dc\t$code\t$entrysped\t$iepstart\t$iepend\t$percent\t$psyreeval\t$splangreeval\t$eser\t$exitdate\t$testac\n";



}

$body = $updateList . "<H1>$listname</H1><br>

		<table border=1 width = 95%>

			$sepheader

			$sepbody

		</table><button onClick=javascript:window.location='index.php?cmd=spedlist&module=sped&listid=$listid&cmd2=export' >Export All</button>";



$export = str_replace("&nbsp;", "", $export);

if($_GET['cmd2'] == "export") {

	exportText($export);

}

*/



foreach($students as $stu) {

	
	$studentid = $stu['studentid'];
//	$editsped = "<a href='index.php?cmd=spededit&module=sped&id=$studentid&close=$params'>Edit SpEd</a>" ;
	

/*
$editsped = (($stu['sped'] == 'Y') ? 

			"<a href='index.php?cmd=spededit&module=sped&id=$studentid&close=$params'>Edit SpEd</a>" : 

				(($stu['entrysped'] == ) ?

					"Not SpEd":

					"<a href='index.php?cmd=spededit&module=sped&id=$studentid'>Edit Previous SpEd</a>"))

				;

*/
	$sped = ($stu['entrysped'] > $stu['exitdate'])? "Yes" : "No";
	
	$editspedurl = "index.php?cmd=spededit&module=sped&id=$studentid&close=$params";
	$editstudenturl = "index.php?cmd=StudentEdit&id=$studentid";
	
	$editsped = ($sped == 'Yes') ? 
			"<a href='index.php?cmd=spededit&module=sped&id=$studentid&close=$params'>Edit SpEd</a>&nbsp;&nbsp;&nbsp;" : 
			"Not SpEd | <a href='index.php?cmd=spededit&module=sped&id=$studentid&close=$params'>+</a>";

	$editstudent = "<a href='index.php?cmd=StudentEdit&id=$studentid'>Edit Student</a>";

	$color = fmod($i++, 2) == 0 ? "lightgrey" : "white";

	$spedstatus = $sped == 'Yes' ? ($stu['Sped_Status'] ==''?'No Value' : $stu['Sped_Status']) : 'No Value';
	
	$age = age($stu['bday']);
//	echo $stu['ESER_plus3'] ."==".$eser_diff . "||" . $stu['iepend'] . "-" . $iepend_diff ."<br>";
//	echo "<br>$timestamp ==> ".$stu['iepend'] . "==" . date("Y-m-d H:i:s", $timestamp);
	$IEPcolor = ''; $ESERcolor = '';
	if($sped == 'Yes') {
		$today = time();
		$iepend_diff = floor((convert_date($stu['iepend']) - $today)/60/60/24);
		$eser_diff = floor((convert_date($stu['ESER_plus3']) - $today)/60/60/24);
		$ESERcolor =( $eser_diff < 30)? "red" : ($eser_diff < 180 ? "yellow" : ""); // ESER_plus3 == *yellow = 6 months    *red = 1 month
		$IEPcolor = ($iepend_diff < 21) ? "red" : (($iepend_diff < 60) ? "yellow" : ""); // iepend == *yellow = 2 months      *red = 3 weeks
//		echo $sped . $stu['ESER_plus3'] ."==$eser_diff $ESERcolor ||" . $stu['iepend'] . "==$iepend_diff $IEPcolor<br>";
	}
/*	if($spedstatus == 'In_Program' or $spedstatus == 'No Value') {
		$statuscolor = '';
		$statustext = '#006633';
	} else {
		$statuscolor = 'red';
		$statustext = 'white';
	}
*/	$ct1array[$stu['status']] +=1;
	$ct2array[$spedstatus] +=1;
	$spedstatusdisplay = str_replace("_", " ", $spedstatus);
	$stulist .=<<<END

	<tr bgcolor="$color">

		<td nowrap="nowrap">



			<div align="center">

				<input name="studentID[]" value="{$stu['studentid']}" class="studentselect" type="checkbox"></div>

		</td>
		<td nowrap="nowrap">



			<div align="center">
				{$sped}
				
			</div>

		</td>

		<td nowrap="nowrap">

			<div align="center">

				<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><font size="2" color="#006633">{$stu['status']}</font></font></div>

		</td>

		<td nowrap="nowrap">



			<div align="center">

				<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><font size="2" color="#006633"><a href=$editspedurl>$spedstatusdisplay</a></font></font></div>

		</td>

		<td nowrap="nowrap">

			<div align="center">

				<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['site']}</font></font></div>

		</td>

		<td nowrap="nowrap">



			<div align="left">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><a href=$editstudenturl>{$stu['lname']}</a></font></div>

		</td>

		<td nowrap="nowrap">

			<div align="left">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['fname']}</font></div>

		</td>

		<td nowrap="nowrap">



			<div align="left">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['mname']}</font></div>

		</td>

		<td nowrap="nowrap">

			<div align="center">

				<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['gender']}</font></font></div>

		</td>

		<td nowrap="nowrap">



			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['bday']}</font></div>

		</td>

		<td nowrap="nowrap">

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">$age</font></div>

		</td>

		<td nowrap>



			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['grade']}</font></div>

		</td>

		<td nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['alaskaid']}</font></td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['GoalViewID']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['dc']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['pcode']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10"></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">60 <b>%</b></font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['entrysped']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['iepstart']}</font></div>



		</td>

		<td nowrap bgcolor="$IEPcolor">

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['iepend']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['psyreeval']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['splangreeval']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Last_OT_Eval']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Last_PT_Eval']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Other_Eval']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Other_Eval_Date']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Current_ESER']}</font></div>



		</td>

		<td nowrap bgcolor='$ESERcolor'>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['ESER_plus3']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Latest_Consent']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['45_Days']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['Reason_Code']}</div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['SpEd_Exit_Date']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['SpEd_Exit_Code']}</div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['IEPLessAge3']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Trans_Plan']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['ISS']}</font></div>

		</td>

		<td nowrap bgcolor="red">

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['OSS']}</font></div>



		</td>

		<td nowrap bgcolor="red">

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['MD_Held']}</div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Test_AC']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Mod_HSGQE']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Alt_Assmt']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['Int_Needs']}</font></div>

		</td>

		<td nowrap>

			<div align="center">

				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">{$stu['RS_Sp']}</font></div>



		</td>

		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['RS_FM']}</div>

		</td>

		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['RS_GM']}</div>

		</td>



		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['RS_Coun']}</div>

		</td>

		<td nowrap>

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['RS_Tran']}</div>

		</td>

		<td nowrap>



			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['RS_Other']}</div>

		</td>

		<td nowrap="nowrap">

			<div align="center">

				<img src="images/10_h.gif" alt="" border="0" height="2" width="10">{$stu['H_Aid']}</div>

		</td>

		<td nowrap="nowrap">

			<div align="left">



				<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><a href="https://dart.bssd.org/index.php?cmd=spededit&amp;module=sped&amp;id=620100">History</a> | $editstudent | $editsped </font></div>

		</td>

	</tr>

END;

}

$body = <<<END

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

			$('#startdate').datepick({
				onClose: function(dates) { 
//					document.editlist.submit();
					alert('test');
//					var selected = ''; 
//					for (var i = 0; i < dates.length; i++) { 
//						selected += ',' + $.datepick.formatDate(dates[i]); 
//					} 
//					alert('Selected dates are: ' + selected.substring(1)); 
//
				} 		
    		});

			$('#enddate').datepick();

		});
		
		function setSpEd(id, val) {
            if(val == 'Y') val = 'N';
            else val = 'Y';
//			alert(id + val);
			$.get("https://dartdemo.bssd.org/index.php", { studentid: id, sped: val, module: 'sped', cmd: 'setsped' },
			   function(data){
//				 alert("Data Loaded: " + data);
				 window.location.reload( true );
			   });
		}
		function setCheckboxes (class, value) {
			$("."+class).attr('checked', value);
		}
		function makeGroup(type) {
//			alert(type);
			if(type == '') return;
//			alert('here');
			var str = '';
			$(".studentselect").each(function(){ 
//				alert(this.value);
				if(this.checked) str = str + "&s[]="+this.value
			});
//			alert(str);
			if(str == '') {
				alert('No students selected');
			} else {
				window.location = 'index.php?cmd=handleSpedGroup&module=sped'+str+'&type='+type;
			}		
		}
	</script>
	
<table border="0" cellpadding="0" cellspacing="2" width="100%">



	<tr>

		<td width="406">

			<div align="left">

				<br>

				<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Special Education Data Overview </font><font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"> </font><font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><br>

				</font></div>

			<blockquote>

				<div align="left">



					<div class="noteimportant">

						<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">This data is here for ready reference by teachers and principals. It is <u>not</u> directly entered here . If you spot any errors, please <a title="Email Special Ed District Staff" href="mailto:sped_info@bssd.org" target="_blank">email us</a>. </font></div>

				</div>

			</blockquote>

		</td>

		<td>

			<form name=editList action=index.php method=get>

			<input type=hidden name=cmd value=spedlist>

			<input type=hidden name=module value=sped>

			<table width="608" border="0" cellspacing="2" cellpadding="0">

				<tr>

					<td nowrap>

						<div align="right">

							<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b><font size="2" color="#336666">Current Group:</font></b></font></div>

					</td>

					<td nowrap><font color="#000099" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"></font>

						<div align="center">

							<select name='listid' onChange='submit()'>

								$listOptions

							</select>
					</td>

					<td nowrap></td>

					<td nowrap>

						<div align="right">


					</td>

					<td nowrap>



						<div align="center">


						</div>

					</td>

					<td nowrap>

						<div align="center">

							

						</div>

					</td>

					<td rowspan="6" nowrap><img src="http://dart.bssd.org/images/gold_panning.gif" alt="" height="174" width="216" align="left" border="0"></td>

				</tr>

				<tr>



					<td nowrap>

						<div align="right">

							<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b><font size="2" color="#336666">SpEd Status View: </font></b></font></div>

					</td>

					<td nowrap>

						<div align="center">

							<select name="spedstatus" onchange="submit()">

								$spedstatusoptions



							</select></div>

					</td>

					<td nowrap></td>

					<td nowrap>

						<div align="right">

							

						</div>

					</td>

					<td nowrap></td>

					<td nowrap>



						<div align="center">

							

						</div>

					</td>

				</tr>

				<tr>

					<td nowrap>

						<div align="right">

							<b><font size="2" color="#336666" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">View Date - Begin:</font></b></div>



					</td>

					<td nowrap>
					
					<input id=startdate type=text name=startdate value='{$_GET['startdate']}' onChange=alert('here');>

					<input id=startOutput type=hidden name=startOutput  value='{$_GET['startOutput']}'>

					<td nowrap></td>

					<td nowrap>

						<div align="right">

							<b><font size="1" color="#336666" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">View Date - End:</font></b></div>

					</td>

					<td nowrap><font size="1"><input type="text" name="enddate" value="2008-10-17" size="24"></font></td>



					<td nowrap>

						<div align="center">

							

						</div>

					</td>

				</tr>

				<tr>

					<td nowrap>

						<div align="right">

							

						</div>



					</td>

					<td nowrap>

						<div align="center">

							<font size="1" color="#cc3300" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">Default = SY Start Date<br>

								<br>

							</font></div>

					</td>

					<td nowrap><input name="save" value="Define Range" type="submit"></td>



					<td nowrap>

						<div align="right">

							

						</div>

					</td>

					<td nowrap>

						<div align="center">

							<font size="1" color="#cc3300" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">Default = Today<br>

								<br>



							</font></div>

					</td>

					<td nowrap>

						<div align="center">

							

						</div>

					</td>

				</tr>

				<tr>

					<td nowrap>



						<div align="center">

							<font size="1" color="#cc3300" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">- OR - </font></div>

					</td>

					<td nowrap></td>

					<td nowrap></td>

					<td nowrap>

						<div align="right">

							

						</div>



					</td>

					<td nowrap></td>

					<td nowrap>

						<div align="center">

							

						</div>

					</td>

				</tr>

				<tr>

					<td nowrap>



						<div align="right">

							<b><font size="2" color="#336666" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">Switch to Prior Year:</font></b></div>

					</td>

					<td nowrap>

						<div align="center">

							<select name="schoolyear" onchange="submit()">

								<option value="self" selected="selected">School Year</option>

								<option value="999">2007-08 SY</option>



								<option value="999">2006-07 SY</option>

								<option value="999">2005-06 SY</option>

								<option value="NO DATA in DART">Look in FMP!</option>

							</select></div>

					</td>

					<td></td>

					<td>



						<div align="right">

							<font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b><font size="2" color="#336666">Sort Order:</font></b></font></div>

					</td>

					<td nowrap>

						<div align="center">

							<select name="sortval" onchange="submit()">

								<option value="lname" $sortval_lname >Last Name (Default)</option>

								<option value="fname" $sortval_fname >First Name</option>

								<option value="sped" $sortval_sped >SpEd</option>


								<option value="bday" $sortval_bday >Age </option>

								<option value="grade" $sortval_GR >Grade Level</option>
								
								<option value="site" $sortval_site >Site</option>

								<option value="iepend" $sortval_iepend >IEP End Date</option>

								<option value="IEPLessAge3" $sortval_IEPLessAge3 >ESER + 3 Years</option>

								<option value="45_Days" $sortval_45_Days >Eval -45 Days</option>

								<option value="ISS" $sortval_ISS >Number ISS</option>



								<option value="Int_Needs" $sortval_Int_Needs >Intensive Needs</option>

								<option value="OSS" $sortval_OSS >Number OSS</option>

								<option value="dc" $sortval_dc >Disabilty Code</option>

								<option value="pcode" $sortval_pcode >Placement Code</option>

								<option value="psyreeval" $sortval_psyreeval >Psych Eval Date</option>

								<option value="splangreeval" $sortval_splangreeval >Speech Eval Date</option>



								<option value="SpEd_Exit_Date" $sortval_SpEd_Exit_Date >Exit Date</option>

								<option value="SpEd_Exit_Code" $sortval_SpEd_Exit_Code >Exit Code</option>

							</select></div>

					</td>

					<td nowrap>

						<div align="center">

							<select name="sortdir" onchange="submit()">

								<option value="ASC" $sortdir_ASC >Ascending</option>



								<option value="DESC" $sortdir_DESC >Descending</option>

							</select></div>

					</td>

				</tr>

			</table>

			</form>

		</td>

	</tr>

	<tr>



		<td colspan="2">

			<div align="left">

				<br>
<form>
				<table border="0" cellpadding="2" cellspacing="2" width="100%">

					<tbody>

						<tr>

							<td colspan="2" bgcolor="#ccffff">

								<div align="left">

									<font class="big" size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Special Education Data Summaries </b>:: </font><font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><font size="2" color="#006633">Active Students</font><font size="2"> - {$ct1array['Active']}<b> :: </b></font><font size="2" color="red">Inactive Students</font><font size="2"> - {$ct1array['Inactive']}<b> :: </b></font><font size="2" color="#006633">In Program Students</font><font size="2"> - {$ct2array['In_Program']} <b> :: </b></font><font size="2" color="red">Eligible Students</font><font size="2"> - {$ct2array['Eligible']}<b> :: </b></font><font size="2" color="red">TNP Students</font><font size="2"> - {$ct2array['TNP']}</font></font></div>



							</td>

						</tr>

						<tr>

							<td colspan="2" valign="top">

								<div align="left">

									<table border="1" width="95%">

										<tbody>

											<tr>

												<td nowrap>
													<div align="center">
													</div>

												</td>

												<td nowrap>
													<div align="center">
													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>SpEd</b></font>
													</div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>DART Status</b></font></div>

												</td>

												<td nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>SpEd Status</b></font></td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Site</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Last Name</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>First Name</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Middle Name</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Gender</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Birthday</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Age</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>GR</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>AK ID </b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>GoalView ID</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>D-Code</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>P-Code</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>P-Code (Old)</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>% In Reg Ed</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Entry SpEd</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>IEP Start</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>IEP End</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Last Psy Eval</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Last SpL Eval</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Last OT Eval</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Last PT Eval</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Other Eval</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Other Eval Date</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Current ESER</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>ESER +3 yrs</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Latest Consent</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<b><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">45 Days?</font></b></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Reason Code</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>SpEd Exit</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>SpEd Exit Code</b></font></div>

												</td>



												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>IEP &lt;Age 3</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Trans Plan</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>ISS</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>OSS</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>MD Held?</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Test AC</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Mod HSGQE</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Alt Assmt</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Int Needs</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>RS Sp</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>RS FM</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>RS GM</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>RS Coun</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>RS Tran</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>RS Other</b></font></div>

												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>H Aid</b></font></div>



												</td>

												<td nowrap>

													<div align="center">

														<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Views</b></font></div>

												</td>

											</tr>



											$stulist



											<tr bgcolor="white">

												<td colspan="7" nowrap="nowrap">

													<div align="right">

														</div>

												</td>

												<td colspan="6" nowrap="nowrap">

													<div align="center">

											<!--			<input type=text size=3 name=limit value=50><input type=submit name=submit value="Display Results"></div>
											-->

												</td>



												<td colspan="6" nowrap="nowrap">
												&nbsp;
											<!--
												<font size="2"><font face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>DART Special Ed Records - (1 to 13 from 13)</b></font></font></td>
											-->
												<td colspan="31" nowrap="nowrap"></td>

											</tr>

										</tbody>

									</table>

									<table width="862" border="0" cellspacing="2" cellpadding="0">

										<tr>

											<td nowrap><img src="images/135pix_hz.gif" alt="" border="0" height="2" width="135"></td>



											<td nowrap><img src="images/135pix_hz.gif" alt="" border="0" height="2" width="135"></td>

											<td nowrap><img src="images/135pix_hz.gif" alt="" border="0" height="2" width="135"></td>

											<td nowrap></td>

											<td nowrap width="181"></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>



										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap width="181">

												<div align="right">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><a href="javascript: ;" onclick="setCheckboxes('studentselect', true); return false;" class="action">Check All</a>&nbsp;/&nbsp;<a href="javascript: ;" onclick="setCheckboxes('studentselect', false); return false;" class="action">UnCheck All</a></font></div>



											</td>

											<td nowrap>

												<div align="right">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><i>with selected students</i> &nbsp;&nbsp;</font></div>

											</td>

											<td colspan="3" nowrap>

												<div align="center">

													Export: <select name=cmd2 onClick="makeGroup(this.value);return(false);">



														<option value="">Select Action Here</option>

														<option value="ExportAll">Export All SpEd Data</option>

														<option value="ExportDiscipline">SpEd and Discipline Data</optoin></option>

														<option value="ExportAttendance">SpEd and Attendance</optoin></option>

														<option value="ExportEnterExit">SpEd and Entry/Exit</optoin></option>



														<option value="ExportFallOasis">SpEd and Fall Oasis</optoin></option>

														<option value="ExportSpringOasis">SpEd and Spring Oasis</option>

														<option value="ExportSummerOasis">SpEd and Summer Oasis</option>

														<option value="ExportAccommodations">SpEd and Accommodations</option>

													</select></div>



											</td>

											<td nowrap><!-- <input type=submit name=Go value=Go onclick="javascript: return makeGroup('group');"> --> </td>

										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>

											<td rowspan="4" colspan="2" nowrap>

												<div align="center">

													<a title="View Group Change HIstory" href="/index.php?module=sped&cmd=spedhistory" target="_blank"><img src="http://dart.bssd.org/images/check_history.gif" alt="View Group Change History" height="46" width="46" border="0"></a></div>



											</td>

											<td nowrap width="181"></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

										<tr>



											<td colspan="2" nowrap>

												<div align="right">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><i><b>View this group's change history here! ==&gt;</b></i></font></div>

											</td>

											<td nowrap width="181"></td>

											<td nowrap>

												<div align="center">

													<font size="1" color="#cc3300" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>- OR - </b></font></div>



											</td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>



											<td nowrap width="181">

												<div align="center"></div>

											</td>

											<td nowrap><b><font size="2" color="#336666" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><button onclick="makeGroup('group');return(false);">Save Checked As Group</button></font></b></td>

											<td nowrap><!-- <input type=text name=grpname size=10> --></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap width="181"></td>

											<td nowrap></td>



											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>



											<td nowrap></td>

											<td nowrap width="181"></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

										<tr>



											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap width="181"></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>



											<td nowrap></td>

										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap width="181"></td>

											<td nowrap></td>



											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

										<tr>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>



											<td nowrap></td>

											<td nowrap width="181"></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

											<td nowrap></td>

										</tr>

									</table>



									<table width="1335" border="1" cellspacing="2" cellpadding="0">

										<tr>

											<td nowrap bgcolor="#acabac">

												<div align="center">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Disability Code</b></font></div>

											</td>

											<td nowrap bgcolor="#acabac">

												<div align="center">



													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>SpEd Placement Code</b></font></div>

											</td>

											<td nowrap bgcolor="#acabac">

												<div align="center">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Placement Code_Time Out</b></font></div>

											</td>

											<td nowrap bgcolor="#acabac">

												<div align="center">



													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>SpEd Exit Code</b></font></div>

											</td>

											<td nowrap bgcolor="#acabac">

												<div align="center">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>IEP by 3rd Code</b></font></div>

											</td>

											<td nowrap bgcolor="#acabac">

												<div align="center">



													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Eval Within 45 Days Code (45 Days?)</b></font></div>

											</td>

											<td nowrap bgcolor="#acabac">

												<div align="center">

													<font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular"><b>Reason for Delay Code</b></font></div>

											</td>

										</tr>

										<tr>



											<td valign="top" nowrap>

												<p><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">01 - Gifted/Talented<br>02 - Cognitive Impairment<br>

														03 - Hearing Impairment<br>

														04 - Speech / Language<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">05 - Visual Impairment<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">06 - Emotional Disturbance<br>



													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">07 - Orthopedic Impairment<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">08 - Other Health Impairment<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">09 Specific Learning Disability<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">10- Deaf-Blindness<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">11- Multiple Disabilities<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">12 - Autism<br>



														13 - Traumatic Brain Injury<br>

													</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">14 - Developmental Delay<br>

														RE - Referral In Process<br>TNP - Tested &amp; Not Placed<br>

													</font></p>

											</td>

											<td valign="top" nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">01 - Early Childhood Setting<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">02 - Early Childhood SpEd Setting<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">03 - Home<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">04 - Part-time ECE/EC SpEd Setting<br>

													05 - Residential Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">06 - Separate School<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">07 - In Regular Classroom 80% +<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">08 - In Regular Classroom 40 - 79%<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">09 - In Regular Classroom 1 - 39%<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">10 - Separate Class with &lt;50% non-disabled<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">11 - Public Separate School Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">12 - Private Separate School Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">13 - Public Residential Facility<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">14 - Private Residential Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">15 - Homebound/Hospital<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">16 - Correctional Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">17 - </font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">Other<br>

												</font></td>

											<td valign="top" nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">01 - Early Childhood Setting<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">02 - Early Childhood SpEd Setting<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">03 - Home<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">04 - Part-time EC/EC SpEd Setting<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">05 - Residential Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">06 - Separate School<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">07 - Itinerant Service Outside Home (Opt)<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">08 - Reverse Mainstream Setting (Opt)<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">09 - SpEd Outside RC&lt;21%<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">10 - SpEd Outside RC&lt;21%&lt;60%<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">11 - SpEd Outside RC&gt;60%<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">12 - Public Separate School Facility<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">13 - Private Separate School Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">14 - Public Residential Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">15 - Private Residential Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">16 - Homebound/Hospital<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">17 - Correctional Facility<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">18 - Enroll in Private School<br>



												</font></td>

											<td valign="top" nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">01 - Graduated with Diploma<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">02 - Graduated with COA<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">03 - Reached Maximum Age<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">04 - Dropped Out<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">51 - Decertified<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">52 - Died<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">53 - Moved, Continuing SpEd<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">54 - Moved, Not Continuing SpEd<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">00 - Other<br>

												</font></td>

											<td valign="top" nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">0 - IEP in place by 3rd birthday or DNQ determination completed by 3rd birthday<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">1 - Extended illness for child<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">2 - Late referral by ILP<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">3 - No 90 day transition meeting<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">4 - Parent refusal to provide consent caused delayed evaluation or initial services<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">5 - Student moved or withdrawn after referral but before IEP implementation<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">6 - Not able to contact parents<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">7 - Other<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">8 - Parent repeatedly fails or refuses to produce the child for evaluation</font></td>

											<td valign="top" nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">0 - Eligibility determination completed within 45 school days<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">1 - Eligibility determination completed within 45-50 school days<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">2 - Eligibility determination completed within 51-60 school days<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">3 - Eligibility determination completed within 61-70 school days<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">4 - Eligibility determination took longer than 70 school days<br>

													<br>

												</font></td>

											<td valign="top" nowrap><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">0 - Determination completed within 45 school days<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">1 - Extended illness for child<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">2 - Student moved or withdrawn after referral, but before eligibility determination<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">3 - Evaluator unable to test due to weather<br>



												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">4 - Consent withdrawn by parent<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">5 - Other<br>

												</font><font size="2" face="Arial, Helvetica, Geneva, Swiss, SunSans-Regular">6 - Parent repeatedly fails or refuses to produce the child for evaluation<br>

												</font></td>

										</tr>

										<tr>

											<td></td>



											<td></td>

											<td></td>

											<td></td>

											<td></td>

											<td></td>

											<td></td>

										</tr>

									</table>
</form>
									<p></p>



								</div>

							</td>

						</tr>

					</tbody>

				</table>

			</div>

		</td>

	</tr>

</table>

END;

include ("template.inc");



?>

