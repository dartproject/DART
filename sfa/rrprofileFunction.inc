<?php

function rrprofile($quarter, $name, $grade, $rr, $reading, $tardies, $absences) {


    $w = "width=60 align=center";
    $h = "height=48";
    
	$body = "<h2>Roots Reading Profile ($quarter Quarter)</h2>
			<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\">
				<tr>
					<td align=right><b>Name:</b></td>
					<td width=100>$name</td>
					<td width=100>&nbsp</td>
					<td align=right><b>Grade:</b></td>
					<td width=30>$grade</td>
					<td width=40></td>
					<td align=right><b>Homework:</b></td>
					<td width=30>$rr</td>
				</tr>
				<tr>
					<td align=right><b>Teacher:</b></td>
					<td>$reading</td>
					<td>&nbsp</td>
					<td align=right><b>Tardies</b></td>
					<td>$tardies</td>
					<td></td>
					<td align=right><b>Absences:</b></td>
					<td>$absences</td>
				</tr>
			</table>
			<table width=\"780\" border=\"1\" cellspacing=\"2\" cellpadding=\"0\">
				<tr>
					<td bgcolor=\"white\">Assessment</td>
					<td $w bgcolor=\"white\">Pre 1</td>
					<td $w bgcolor=\"white\">1-5</td>
					<td $w bgcolor=\"white\">6-10</td>
					<td $w bgcolor=\"white\">11-15</td>
					<td $w bgcolor=\"white\">16-20</td>
					<td $w bgcolor=\"white\">21-25</td>
					<td $w bgcolor=\"white\">26-31</td>
					<td $w bgcolor=\"white\">32-37</td>
					<td $w bgcolor=\"white\">38-42</td>
					<td $w bgcolor=\"white\">43-48</td>
				</tr>
				<tr $h>
					<td bgcolor=\"#ffbfd1\">Baseline</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
				</tr>
				<tr $h>
					<td bgcolor=\"#ffcf96\">1st 8 weeks</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
				</tr>
				<tr $h>
					<td bgcolor=\"#ffffb5\">2nd 8 weeks</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
				</tr>
				<tr $h>
					<td bgcolor=\"#aee67c\">3rd 8 weeks</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
				</tr>
				<tr $h>
					<td bgcolor=\"b5e0ff\">4th 8 weeks</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
				</tr>
			</table>";
		
		return ($body);

}

?>