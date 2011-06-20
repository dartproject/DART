<?php

$id = $_GET['id'];

if($_POST['submit'] <> "") {

	$enterCode = $_POST['enterCode'];
	$site = $_POST['site'];
	$comments = addslashes($_POST['comments']);
	$date = MySQLDate($_POST['month'], $_POST['day'], $_POST['year']);
	$id = $_POST['id'];
	echo $date;
	saveEnter($id, $enterCode, $site, $date, $comments);

    echo "<script>
			  window.opener.location.reload(true);
			  window.close(); 
		  </script>";
}


$studentInfo = getStudentInfo($id);
$site = $studentInfo['site'];
$studentname = $studentInfo['fname'] .  " " . $studentInfo['lname'];

$calday = getDay('day', date('j'));
$calmonth = getMonth('month', date('n'));
$calyear = getYear('year', date('Y'));

$siteOptions = "<select name=\"site\" id=\"site\" >
				<option value=\"\"></option>" . 
				getSitesOptions("") . 
                "</select>";
                
$enterCodeOptions = <<<END
			<select name=enterCode>
				<option value="">&lt; Available Codes &gt;</option>
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

$url = $_SERVER['PHP_SELF'];
$body .= <<<END
<h2>Inactive Student $studentname</h2>
			<form action=index.php?cmd=StudentEnter method=post>
				<input type=hidden name=id value=$id>
				<table>
					<tr>
						<td>
							Site:
						</td>
						<td>
							$siteOptions
						</td>
						<td>
							Enter Date (Month-Day-Year):
						</td>
						<td>
							 $calmonth $calday $calyear
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
							<textarea name=comments cols=60 rows=5></textarea>
						</td>
					</tr>
					<tr>
						<td colspan=4 align=center>
							<input type=submit value=Submit name=submit>
							<input type=button value=Cancel onClick="window.close();" name=cancel>
						</td>
					</tr>
				</table>
			</form>
			<h2>Enter Code and Description</h2>
			$enterChart
END;

echo $body;
//include('template.inc');
?>
