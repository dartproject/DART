{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="body"}

<div style="width:1024px; margin: auto; padding-bottom:30px;">
<h2>New Student Current Location: {$site}</h2>
<h3><span style="color:red">{$msg|default:'&nbsp;'}</span></h3>
			<form action=index.php?cmd=NewStudentMovement&site={$site} method=post>
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
							{html_options name="month" options=$monthMenu selected=$month}
							{html_options name="day" options=$dayMenu selected=$day}
							{html_options name="year" options=$yearMenu selected=$year}
							&nbsp;
						</td>
						<td>
							Site:
						</td>
						<td>
							{html_options name="site" id="id" options=$siteMenu selected=$site}
						</td>
					</tr>
					<tr>
						<td>
							Enter Code:
						</td>
						<td colspan=3>
							{html_options name="entryCode" options=$entryCodeMenu}
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
							<input type=button onClick="javascript:window.location='index.php?cmd=userAdmin&status=Active&site={$site}'" value=Cancel name=cancel>
						</td>
					</tr>
				</table>
			</form>
			<h2>Enter Code and Description</h2>
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
		{foreach $code_names as $id => $name}
		<tr>
			<td bgcolor="#339900" nowrap="nowrap" width="26">
				<div align="center">
					<b><font color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">{$id}</font></b></div>
			</td>
			<td nowrap="nowrap">{$name}</td>

			<td nowrap="nowrap">{$examples.{$id}}
		</tr>
		{/foreach}
	</tbody>
</table>
</div>
{/block}
