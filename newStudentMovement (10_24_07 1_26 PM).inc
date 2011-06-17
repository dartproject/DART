<?php

if($_POST['submit'] <> "") {

	$enterCode = $_POST['enterCode'];
	$enterSite = $_POST['site'];
	$id = $_POST['id'];
	$alaskaid = $_POST['alaskaid'];
	saveEntry($id, $enterCode, $enterSite, $alaskaid);
	
	header("Location: ./index.php?cmd=StudentEdit&id=$id");
}

$id = $_GET['id'];
$studentInfo = getStudentInfo($id);
$site = $studentInfo['site'];
$studentname = $studentInfo['fname'] .  " " . $studentInfo['lname'];

$enterCodeOptions = <<<END
			<select name=enterCode>
				<option value="one">&lt; Available Codes &gt;</option>
                <option value="01">01 (Transfer within District)</option>
                <option value="02">02 (Transfer within Alaska)</option>
                <option value="03">03 (Transfer another State or Country)</option>
                <option value="04">04 (Transfer from home schooling)</option>
                <option value="05">05 (Transfer from private school)</option>
                <option value="06">06 (Transfer from an institute w/Ed Prog)</option>
                <option value="07">07 (RE-Entry voluntary WD same School)</option>
                <option value="08">08 (Re-entry involuntary WD same school)</option>
                <option value="09">09 (Initial Entry (student new to school))</option>
                <option value="10">10 (Return Student Prior Year))</option>
                <option value="E">E (enrolled)</option>
                <option value="R">R (returned)</option>
                <option value="T">T (Transferred from in-district)</option>
              </select>
END;

$enterChart = <<<END
<table border="1" cellpadding="2" cellspacing="2">
	<tbody>
		<tr>
			<td nowrap="nowrap" width="26">
				<div align="center">
					<b><font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">.</font></b></div>

			</td>
			<td nowrap="nowrap">
				<div align="center">
					<b><font color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">Entry Type Code List</font></b></div>
			</td>
			<td nowrap="nowrap">
				<div align="center">
					<b><font color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">Examples</font></b></div>

			</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<b><font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">1</font></b></div>
			</td>
			<td nowrap="nowrap">Transfer from <u>another BSSD school</u></td>

			<td nowrap="nowrap">One of our other villages!</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>2</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer from a public school in a <u>different school district in Alaska</u></td>

			<td nowrap="nowrap">Nome, NWABSD, Anchorage, Mt. Edgecumbe</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>3</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer from a <u>public school in a different state</u> or country</td>

			<td nowrap="nowrap">Lower 48</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>4</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer from <u>home schooling</u> </td>

			<td nowrap="nowrap">Does not include students just kept home ;-)</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>5</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer from a <u>private school</u></td>

			<td nowrap="nowrap">Anchorage Christian, etc.</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>6</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer from an <u>institution with an educational program</u></td>

			<td nowrap="nowrap">Anvil Mountain Youth Facility, Northstar, jail, etc.</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>7</b></font></div>
			</td>
			<td nowrap="nowrap">Re-Entry after a <u>voluntary withdrawal from same school</u></td>

			<td nowrap="nowrap">Former drop out</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>8</b></font></div>
			</td>
			<td nowrap="nowrap">Re-Entry after a <u>explusion from same school</u></td>

			<td nowrap="nowrap">Expelled last year</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>9</b></font></div>
			</td>
			<td nowrap="nowrap">Student is <u>new</u> to the school</td>

			<td nowrap="nowrap">New Kindergarten or pre-school students</td>
		</tr>
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>10</b></font></div>
			</td>
			<td nowrap="nowrap">Student <u>continuing</u> from last year without break in attendance</td>

			<td nowrap="nowrap">Was still an <u>active student</u> on last day of last year!</td>
		</tr>
	</tbody>
</table>

END;

$body .= <<<END
<h2>Current Student $studentname at location $site</h2>
			<form action=index.php?cmd=NewStudentMovement method=post>
				<input type=hidden name=id value=$id>
				<input type=hidden name=site value=$site>
				<table>
					<tr>
						<td>
							Alaska ID:
						</td>
						<td>
							<input type=text name=alaskaid>
						</td>
					</tr>
					<tr>
						<td>
							Enter Code:
						</td>
						<td>
							$enterCodeOptions
						</td>
					</tr>
					<tr>
						<td colspan=2 align=center>
							<input type=submit value=Submit name=submit>
							<input type=button value=Cancel name=cancel>
						</td>
					</tr>
				</table>
			</form>
			<h2>Enter Code and Description</h2>
			$enterChart
END;

include('template.inc');
?>