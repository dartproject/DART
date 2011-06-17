<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$js .= "
function checkBlank()
{
  if(document.SipCreator.area.value == '') {
  	alert ('Must select type');
 	return (false);
  }
  if(document.SipCreator.name.value == '') {
  	alert ('Must fill in Name');
 	return (false);
  } else {
	return(true);
  }
}
";

$yearOptions = "<select name=year >" .
			getSipYearOption($CurrentYear) .
			"</select>";

//$areaOptions = "<select name=\"area\" id=\"area\">" . 
//                       getSubjectOption() . 
//                       "</select>";
 		 

$mylists = getMyList($currentUserID);
$grouplists =  getMyList($currentUserID, $currentMySite);
$entireList = array_merge($mylists, $grouplists);
		 
                      
$grpOptions = "<select name=\"grp\" id=\"grp\">" .
                       GetOptionList($mylists) . 
					"<option value=''>-- Group List --</option>" .
                       GetOptionList($grouplists) . 
                       "</select>";

$typeOptions = "<select name=test>
					<option></option>
					<option value=Q1>Q1</option>
					<option value=Q2>Q2</option>
					<option value=Q3>Q3</option>
					<option value=Q4>Q4</option>
					<option value=Semester1>Semester1</option>
					<option value=Semester2>Semester2</option>
				</select>";
$rwmOptions = "<select name=area id=area>
					<option></option>
					<option value=r>RE</option>
					<option value=w>WR</option>
					<option value=m>MA</option>
				</select>";
					
$body .= "
<form name=SipCreator action=index.php?cmd=createTeacherSip&module=sip method=post>
	<table>
		<tr>
			<td>Year: $yearOptions</td>
			<td>Type: $rwmOptions</td>
			<td>
				Name: <input type=text name=name value=\"\">
			</td>
		</tr>
		</tr>
			<td colspan=4 align=center>
				<input type=submit name=save onClick='javascript:return checkBlank();' value='Create Teacher SIP'>
			</td>
		</tr>
	</table>

";

include_once ("template.inc");
?>