<?php

$id = $_GET['id'];

if($_POST['submit'] <> "") {

	$exitCode = $_POST['exitCode'];
	$site = $_POST['site'];
	$comments = addslashes($_POST['comments']);
	$date = MySQLDate($_POST['month'], $_POST['day'], $_POST['year']);
	$id = $_POST['id'];
	echo $date;
	saveExit($id, $exitCode, $site, $date, $comments);

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

$exitCodeOptions = <<<END
					<select name=exitCode size=1>
						<option value="one">&lt; Available Codes &gt;</option>
						<option value="1">1 - Transfer to another school in BSSD</option>
						<option value="2">2 - Transfer to a public school in a different school district in Alaska</option>
						<option value="3">3 - Transfer to a public school in a different state or country </option>
	
						<option value="5">5 - Transfer to a private school</option>
						<option value="6">6 - Transfer from an institution with an educational program</option>
						<option value="7">7 - Graduated with regular diploma</option>
						<option value="8">8 - Graduated with regular diploma under an approved waiver </option>
						<option value="9">9 - COA (certificate of attendance or achivement) </option>
						<option value="10">10 - Death</option>
	
						<option value="11">11 - Maximum age and did not receive a diploma or COA</option>
						<option value="12">12 - Dropped Out / Discontinued School</option>
						<option value="13">13  - Finished year as 12th grader &amp; expected to return</option>
						<option value="14">14- Finished year as PK-11th grader &amp; returning</option>
					</select>               
END;

$exitChart = <<<END
<table border="1" cellpadding="2" cellspacing="2">
	<tbody>
		<tr>
			<td nowrap="nowrap" width="26">
				<div align="center">
					<b><font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">.</font></b></div>
			</td>
			<td nowrap="nowrap">

				<div align="center">
					<b><font color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">Exit Type Code</font></b></div>
			</td>
			<td nowrap="nowrap">
				<div align="center">
					<b><font color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">Examples</font></b></div>
			</td>
		</tr>

		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<b><font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">1</font></b></div>
			</td>
			<td nowrap="nowrap">Transfer to <u>another school in BSSD</u></td>
			<td nowrap="nowrap">Going to one of our other villages!</td>

		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>2</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer to a public school in a <u>different school district in Alaska</u></td>

			<td nowrap="nowrap">Nome, NWABSD, Anchorage, Mt. Edgecumbe</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>3</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer to a public school in a <u>different state </u>or country </td>

			<td nowrap="nowrap">Going to the Lower 48</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>5</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer to a <u>private school</u></td>

			<td nowrap="nowrap">Anchorage Christian, etc.</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>6</b></font></div>
			</td>
			<td nowrap="nowrap">Transfer from an <u>institution with an educational program</u></td>

			<td nowrap="nowrap">Anvil Mountain Youth Facility, Northstar, jail, etc.</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>7</b></font></div>
			</td>
			<td nowrap="nowrap">Graduated with <u>regular diploma</u></td>

			<td nowrap="nowrap">Passed <u>both</u> HSGQE &amp; BSSD Standards</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>8</b></font></div>

			</td>
			<td nowrap="nowrap">Graduated with regular diploma under an <u>approved waiver</u> </td>
			<td nowrap="nowrap">District must have written waiver (<a title="Alaska Graduation Waiver Details" href="http://www.touchngo.com/lglcntr/akstats/aac/title04/chapter006/section772.htm" target="_blank">4 AAC 06.772</a>) </td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">

				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>9</b></font></div>
			</td>
			<td nowrap="nowrap">COA (certificate of attendance or achievement)</td>
			<td nowrap="nowrap">Passed <u>only</u> BSSD Standards</td>
		</tr>

		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>10</b></font></div>
			</td>
			<td nowrap="nowrap">Death</td>
			<td nowrap="nowrap">Student suicide or accidental death</td>

		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>11</b></font></div>
			</td>
			<td nowrap="nowrap">Maximum age and did <u>not</u> receive a diploma or COA</td>

			<td nowrap="nowrap">Student reaches 21 years of age</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>12</b></font></div>
			</td>
			<td bgcolor="#ffcccc" nowrap="nowrap">Dropped Out / Discontinued School</td>

			<td rowspan="2" bgcolor="#ffcccc" nowrap="nowrap"><b>Alaska EED Says:</b> <u>Includes</u> 10+ Consecutive Absences, truancy, <br>administrative drop, failing, those pursuing GED, entering military,<br>
				employment, family problems, pregnancy, alcohol/drug dependency,<br>
				expulsion due to behavior, illness, <u>transfer to home schooling</u>, or left for<br>
				unknown reasons without a formal request for transfer of records. Also<br>

				<u>includes</u> kindergarteners who stop coming to school once enrolled, even<br>
				though they are not of required school age.</td>
		</tr>
		<tr>
			<td colspan="2" nowrap="nowrap">
				<div align="center">
					<b><i>This code is critical to AYP calculations. Please read! </i><font color="red" size="4"><tt>==&gt;</tt></font></b></div>

			</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>13</b></font></div>
			</td>
			<td nowrap="nowrap">Finished year as 12th grader &amp; expected to return</td>

			<td nowrap="nowrap">Students staying in school above 12th year to earn diploma or COA</td>
		</tr>
		<tr>
			<td bgcolor="yellow" nowrap="nowrap" width="26">
				<div align="center">
					<font color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1"><b>14</b></font></div>
			</td>
			<td nowrap="nowrap">Finished year as PK-11th grader &amp; returning</td>

			<td nowrap="nowrap">Most students <u>still enrolled</u> on last day of school year!</td>
		</tr>
	</tbody>
</table>

END;

$body .= <<<END
<h2>Current Student $studentname at location $site</h2>
			<form action=index.php?cmd=StudentExit method=post>
				<input type=hidden name=id value=$id>
				<input type=hidden name=site value=$site>
				<table>
					<tr>
						<td>
							Exit Date<br>(Month-Day-Year):
						</td>
						<td>
							 $calmonth $calday $calyear
						</td>
					</tr>
					<tr>
						<td>
							Exit Code:
						</td>
						<td>
							$exitCodeOptions
						</td>
					</tr>
					<tr>
						<td valign=top>
							Comments:
						</td>
						<td >
							<textarea name=comments cols=60 rows=5></textarea>
						</td>
					</tr>
					<tr>
						<td colspan=2 align=center>
							<input type=submit value=Submit name=submit>
							<input type=button value=Cancel onClick="window.close();" name=cancel>
						</td>
					</tr>
				</table>
			</form>
			<h2>Exit Code and Descriptions</h2>
			$exitChart
END;

echo $body;
//include('template.inc');
?>
