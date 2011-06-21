<?php

$A6Priv = Privilege(A6);

if($A6Priv != 'district') { NoPriv("denied newStudent", "You should not be trying to creating new student. Email sent to admin"); }

    $site = $_GET['site'];

// Site created by newStudent.inc.
if($_POST['submit'] <> "") {

	$enterCode = $_POST['enterCode'];
	$alaskaid = $_POST['alaskaid'];

	if($alaskaid != "" and $enterCode != "") {
		$date = MySQLDate($_POST['month'], $_POST['day'], $_POST['year']);
		$site = $_POST['site'];
		$comments = addslashes($_POST['comments']);
		$id = createNewStudent($site);
		saveEntry($id, $enterCode, $site, $date, $alaskaid, $comments);
//		echo "$id $date $site $alaskaid $enterCode";		
		header("Location: ./index.php?cmd=StudentEdit&id=$id");
	} else {
		$body =  "<h1>Need to have alaskaid or entry code entered</h1>";
	}
}


$calday = getDay('day', date('j'));
$calmonth = getMonth('month', date('n'));
$calyear = getYear('year', date('Y'));

$siteOptions = "<select name=\"site\" id=\"site\" >
				<option value=\"\"></option>" . 
				getSitesOptions($site) . 
                "</select>";

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
<h2>New Student Current Location: $site</h2>
			<form action=index.php?cmd=NewStudentMovement&site=$site method=post>
				<table>
					<tr>
						<td>
							Alaska ID:
						</td>
						<td  colspan=3>
							<input type=text name=alaskaid>
						</td>
					</tr>
					<tr>
						<td>
							Enter Date (M-D-Y):
						</td>
						<td>
							 $calmonth $calday $calyear
						</td>
						<td>
							Site:
						</td>
						<td>
							 $siteOptions
						</td>
					</tr>
					<tr>
						<td>
							Enter Code:
						</td>
						<td colspan=3>
							$enterCodeOptions
						</td>
					</tr>
					<tr>
						<td valign=top>
							Comments:
						</td>
						<td colspan=3>
							<textarea name=comments cols=40 rows=5></textarea>
						</td>
					</tr>
					<tr>
						<td colspan=3 align=center>
							<input type=submit value=Submit name=submit>
							<input type=button onClick="javascript:window.location='index.php?cmd=userAdmin&status=Active&site=$site'" value=Cancel name=cancel>
						</td>
					</tr>
				</table>
			</form>
			<h2>Enter Code and Description</h2>
			$enterChart
END;

include('template.inc');
?>
