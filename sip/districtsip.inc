<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

// window.maintframe.document.forms(0).submit();
//window.maintframe.doVerify();
// gets value information of frame => window.frames['maintframe1'].document.forms[0].value.value; 

$A16Priv = Privilege(A16);

if($A16Priv <> 'district') { NoPriv("denied Ad Hoc List", ""); }

if($_POST['action'] == 'save') {
	saveDistrictSiteSip ($_POST);
	$body = "Information successfully saved<br>";
}

$year = $_GET['year'] == '' ? $CurrentYear : $_GET['year'];
$optionYears = getSipYearOption ($year);
$url = $_SERVER[PHP_SELF];

while(list($name, $val) = each($_GET)) {
	if($name != 'year') { $get .= "&$name=$val"; }
}

$body .= <<<END
<form>
	Select Year: <select name=year onchange="window.location='$url?year='+this.value+'$get'">
		$optionYears
	  </select>
</form>
END;
	  
debugprint("Current Year: " . $year);

$dd = getSipYearKind($year, 'district');

$i = 1;
$j = 1;
for($i = 1; $i <=4; $i++) {
	for($j = 1; $j <=5; $j++) {
		$var = "g$i$j" . "_checked";
		${$var} = $dd["g$i$j"] == 'X' ? 'checked' : '';
	}
}
$head = "<script>

  function popUp(URL, x, y) {
  	self.name = 'listings'; 
	newwindow = window.open(URL, 'name', 'toolbar=1,scrollbars=1,location=1,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
	if(window.focus) {newwindow.focus()}
  }

  function confirmMsg(msg)
  {
		return(input_box=confirm(msg));
  }

function elmName(){
   var ni = document.getElementById('myDiv');
   for(i=0; i<window.frames['maintframe1'].document.forms[0].elements.length; i++){
		var newinput = document.createElement('input');
		newinput.setAttribute(\"type\",\"hidden\");
		newinput.setAttribute(\"name\", \"reading_\" + window.frames['maintframe1'].document.forms[0].elements[i].name);
		newinput.value = window.frames['maintframe1'].document.forms[0].elements[i].value;
		ni.appendChild(newinput);
   }
   for(i=0; i<window.frames['maintframe2'].document.forms[0].elements.length; i++){
		var newinput = document.createElement('input');
		newinput.setAttribute(\"type\",\"hidden\");
		newinput.setAttribute(\"name\", \"writing_\" + window.frames['maintframe2'].document.forms[0].elements[i].name);
		newinput.value = window.frames['maintframe2'].document.forms[0].elements[i].value;
		ni.appendChild(newinput);
   }
   for(i=0; i<window.frames['maintframe3'].document.forms[0].elements.length; i++){
		var newinput = document.createElement('input');
		newinput.setAttribute(\"type\",\"hidden\");
		newinput.setAttribute(\"name\", \"math_\" + window.frames['maintframe3'].document.forms[0].elements[i].name);
		newinput.value = window.frames['maintframe3'].document.forms[0].elements[i].value;
		ni.appendChild(newinput);
   }
 }

function doSaveClick() {
//alert(\"test\");
//elmName();
document.sip.submit();
}
</script>

<style type=\"text/css\">
/*
body{
		margin:10px;
		font-size:0.9em;
	}
	a{
		color:#F00;
	}
*/
.sipheading {
	font-style:bold;
	font-size:14px;
}
.sipsubheading {
}
	</style>
	<link rel=\"stylesheet\" href=\"lib/tab-view.css\" type=\"text/css\" media=\"screen\">
	<script type=\"text/javascript\" src=\"js/ajax.js\"></script>
	<script type=\"text/javascript\" src=\"lib/tab-view.js\"></script>
	<script src=\"lib/utility.txt\"></script>
	<script type=\"text/javascript\" src=\"lib/myScript.js\"></script>
	";

$body .= "<table border=0><tr><td>&nbsp;</td><td>";

$url = $_SERVER['PHP_SELF'];
$sid = $dd['id'];	
$body .= "


<form name=sip action=index.php?module=sip&cmd=districtsip&year=$year method=post>
<input type=hidden name=action value=save>
<input type=hidden name=id value=$sid>
<input type=\"hidden\" value=\"0\" id=\"theValue\" />

	
<input type=button id=\"save\" name=\"save\" value=\"save\" onclick=\"javascript:doSaveClick();\">
 <div id=\"myDiv\"> </div>

<span class=sipheading>Subject Listed In Order Of Strength</span>
<a href='#' onClick='javascript:popUp(\"$url/index.php?module=sip&cmd=sipedit&sid=$sid&field=subjectorder&title=Edit Subject Order\", 550, 220);'>Edit</a> 
<br>"
 . $dd['subjectorder'] . "<br><br>
 
<span class=sipheading>Strongest And Weakest Grades for Each Subject</span>
<a href='#' onClick='javascript:popUp(\"$url/index.php?module=sip&cmd=sipedit&sid=$sid&field=graderating&title=Edit Strongest and Weakest Grades\", 550, 220);'>Edit</a> 
<br>"
 . $dd['graderating'] . "<br><br>
 
<span class=sipheading>Areas of emphasis:</span><br>
<table border=1>
	<tr>
		<td class=sipsubheading>Reading:</td>
		<td><input type=text name=emphasisR value='" . $dd['emphasisR'] . "'></td>
	</tr>
	<tr>
		<td class=sipsubheading>Writing:</td>
		<td><input type=text name=emphasisW value='" . $dd['emphasisW'] . "'></td>
	</tr>
	<tr>
		<td class=sipsubheading>Math:</td>
		<td><input type=text name=emphasisM value='" . $dd['emphasisM'] . "'></td>
	</tr>
	
</table><br>
<table>
<tr>
	<td colspan='3' bgcolor='#ffff99'>
		<div align='center'></div>
	</td>
	<td bgcolor='#ffff99'>
		<div align='center'>
			<font size='2' face='Arial'><b>All Students</b></font></div>

	</td>
	<td bgcolor='#ffff99'>
		<div align='center'>
			<font size='2' face='Arial'><b>Ethnic Groups</b></font></div>
	</td>
	<td bgcolor='#ffff99'>
		<div align='center'>
			<font size='2' face='Arial'><b>SWD</b></font></div>

	</td>
	<td bgcolor='#ffff99'>
		<div align='center'>
			<font size='2' face='Arial'><b>LEP</b></font></div>
	</td>
	<td bgcolor='#ffff99'>
		<div align='center'>
			<font size='2' face='Arial'><b>Low-Income</b></font></div>

	</td>
</tr>
<tr>
	<td colspan='3'><font size='2' face='Arial'><b>Language Arts</b></font></td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g11 $g11_checked></font></div>
	</td>

	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g12 $g12_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g13 $g13_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g14 $g14_checked></font></div>

	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g15 $g15_checked></font></div>
	</td>
</tr>
<tr>
	<td colspan='3'><font size='2' face='Arial'><b>Math</b></font></td>

	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g21 $g21_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g22 $g22_checked></font></div>
	</td>
	<td>

		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g23 $g23_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g24 $g24_checked></font></div>
	</td>
	<td>
		<div align='center'>

			<font size='2' face='Arial'><input type=checkbox value=X name=g25 $g25_checked></font></div>
	</td>
</tr>
<tr>
	<td colspan='3'><font size='2' face='Arial'><b>Participation</b></font></td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g31 $g31_checked></font></div>
	</td>

	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g32 $g32_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g33 $g33_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g34 $g34_checked></font></div>
	</td>

	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g35 $g35_checked></font></div>
	</td>
</tr>
<tr>
	<td colspan='3'><font size='2' face='Arial'><b>Graduation Rate</b></font></td>
	<td>
		<div align='center'>

			<font size='2' face='Arial'><input type=checkbox value=X name=g41 $g41_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g42 $g42_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g43 $g43_checked></font></div>
	</td>

	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g44 $g44_checked></font></div>
	</td>
	<td>
		<div align='center'>
			<font size='2' face='Arial'><input type=checkbox value=X name=g45 $g45_checked></font></div>
	</td>
</tr>
</table><br>
<span class=sipheading>District SIP Message:</span><br>
<textarea rows = 8 cols=60 name=district>". $dd['district'] . "</textarea><br>

<span class=sipheading>Questions 2:</span><br>
<textarea rows = 8 cols=60 name=stateques>". $dd['stateques'] . "</textarea><br>
<span class=sipheading>Link 2:</span><br>
<textarea rows = 8 cols=60 name=link>". $dd['link'] . "</textarea><br>

<span class=sipheading>Questions 3:</span><br>
<textarea rows = 8 cols=60 name=ques3>". $dd['ques3'] . "</textarea><br>
<span class=sipheading>Link 3:</span><br>
<textarea rows = 8 cols=60 name=link3>". $dd['link3'] . "</textarea><br>

<span class=sipheading>Questions 4:</span><br>
<textarea rows = 8 cols=60 name=ques4>". $dd['ques4'] . "</textarea><br>
<span class=sipheading>Link 4:</span><br>
<textarea rows = 8 cols=60 name=link4>". $dd['link4'] . "</textarea><br>

<span class=sipheading>Area Action Plans:</span><br>
 <div id=dhtmlgoodies_tabView1>
	<div class=dhtmlgoodies_aTab>
	    Reading Section<br><br>
		Objective (Area of need to be addressed):<br>
		<textarea rows = 3 cols=60 name=r1>". $dd['r1'] . "</textarea><br>
		
		Current Performance Level on SBAs:<br>
		<textarea rows = 3 cols=60 name=r2>". $dd['r2'] . "</textarea><br>
		
		Performance Target (Measurable Change):<br>
		<textarea rows = 3 cols=60 name=r3>". $dd['r3'] . "</textarea><br>
		
		Scientifically based research to support for each strategy or curriculum listed below:<br>
		<textarea rows = 3 cols=60 name=r4>". $dd['r4'] . "</textarea><br>
		
		<iframe id=maintframe1 name=maintframe1
			frameborder=1
			src =\"index.php?module=sip&cmd=showaction&area=r&id=". $dd['sid'] . "\"
			width=\"100%\">
		</iframe>
		
	</div>
	<div class=\"dhtmlgoodies_aTab\">
	    Writing Section<br><br>
		Objective (Area of need to be addressed):<br>
		<textarea rows = 3 cols=60 name=w1>". $dd['w1'] . "</textarea><br>
		
		Current Performance Level on SBAs:<br>
		<textarea rows = 3 cols=60 name=w2>". $dd['w2'] . "</textarea><br>
		
		Performance Target (Measurable Change):<br>
		<textarea rows = 3 cols=60 name=w3>". $dd['w3'] . "</textarea><br>
		
		Scientifically based research to support for each strategy or curriculum listed below:<br>
		<textarea rows = 3 cols=60 name=w4>". $dd['w4'] . "</textarea><br>

		<iframe id=maintframe2 name=maintframe2
			frameborder=0
			src =\"index.php?module=sip&cmd=showaction&area=w&id=". $dd['sid'] . "\"
			width=\"100%\">
		</iframe>

	</div>
	<div class=\"dhtmlgoodies_aTab\">
	    Math Section<br><br>
		Objective (Area of need to be addressed):<br>
		<textarea rows = 3 cols=60 name=m1>". $dd['m1'] . "</textarea><br>
		
		Current Performance Level on SBAs:<br>
		<textarea rows = 3 cols=60 name=m2>". $dd['m2'] . "</textarea><br>
		
		Performance Target (Measurable Change):<br>
		<textarea rows = 3 cols=60 name=m3>". $dd['m3'] . "</textarea><br>
		
		Scientifically based research to support for each strategy or curriculum listed below:<br>
		<textarea rows = 3 cols=60 name=m4>". $dd['m4'] . "</textarea><br>
		
		<iframe id=maintframe3 name=maintframe3
			frameborder=0
			src =\"index.php?module=sip&cmd=showaction&area=m&id=". $dd['sid'] . "\"
			width=\"100%\">
		</iframe>
	</div>
	<div class=\"dhtmlgoodies_aTab\">
	    Intervention Section<br><br>
		Objective (Area of need to be addressed):<br>
		<textarea rows = 3 cols=60 name=i1>". $dd['i1'] . "</textarea><br>
		
		Current Performance Level on SBAs:<br>
		<textarea rows = 3 cols=60 name=i2>". $dd['i2'] . "</textarea><br>
		
		Performance Target (Measurable Change):<br>
		<textarea rows = 3 cols=60 name=i3>". $dd['i3'] . "</textarea><br>
		
		Scientifically based research to support for each strategy or curriculum listed below:<br>
		<textarea rows = 3 cols=60 name=i4>". $dd['i4'] . "</textarea><br>
		
		<iframe id=maintframe3 name=maintframe3
			frameborder=0
			src =\"index.php?module=sip&cmd=showaction&area=i&id=". $dd['sid'] . "\"
			width=\"100%\">
		</iframe>
	</div>
</div>
<script type=\"text/javascript\">
initTabs('dhtmlgoodies_tabView1',Array('&nbsp;&nbsp;&nbsp;&nbsp;Reading&nbsp;&nbsp;&nbsp;&nbsp;','&nbsp;&nbsp;&nbsp;&nbsp;Writing&nbsp;&nbsp;&nbsp;&nbsp;','&nbsp;&nbsp;&nbsp;&nbsp;Math&nbsp;&nbsp;&nbsp;&nbsp;','&nbsp;&nbsp;&nbsp;&nbsp;Intervention&nbsp;&nbsp;&nbsp;&nbsp;'),0,650,500,Array(false,false,false, false));
</script>
<br>
<br>
<br>
<div class=clear></div>

<input type=button id=\"save\" name=\"save\" value=\"save\" onclick=\"javascript:doSaveClick();\">
</form>
";

$body .= "</td></tr></table>";

include_once ("template.inc");


?>