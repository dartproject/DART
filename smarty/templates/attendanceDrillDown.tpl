{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script language="JavaScript" type="text/javascript" src="js/attendanceDrillDown.js"></script>
{/block}
{block name="body"}
{$view}<br />
<form name="selectionForm" action="index.php?cmd=AttendanceDrillDown&type={$type}&site={$site}&year={$year}&month={$month}&cdate={$cdate}" method="post" >
	<table border=1>
		<tr>
			<th></th>
			<th>Name</th>
			<th>Student ID</th>
			<th>Site</th>
			<th>Absent</th>
			<th>Late</th>
			<th>ISS</th>
			<th>Suspended</th>
			<th>Present</th>
		</tr>
	{foreach $table as $ind}
		<tr>
			<td>
				<input type="checkbox" name="studentID[]" value="{$ind.id}" class="radio">
			</td>
			<td>{$ind.name}</td>
			<td>{$ind.id}</td>
			<td>{$ind.site}</td>
			<td>{$ind.g_0|default:'&nbsp;'}</td>
			<td>{$ind.g_1|default:'&nbsp;'}</td>
			<td>{$ind.g_2|default:'&nbsp;'}</td>
			<td>{$ind.g_3|default:'&nbsp;'}</td>
			<td>{$ind.g_4|default:'&nbsp;'}</td>
		</tr>
	{/foreach}
	</table>
	<div align="left">
		&nbsp;
		<a href="javascript: ;" onclick="setCheckboxes('selectionForm', true); return false;" class="action">
			Check All
		</a>
		&nbsp;/&nbsp;
		<a href="javascript: ;" onclick="setCheckboxes('selectionForm', false); return false;" class="action">
			UnCheck All
		</a>
		<i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i>
		<input type="submit" name="cmd2" onClick='javascript: return checkChecks();' value='Group' />
		<br />
		<input type="submit" name="cmd2" value='Export All' />
	</div>
</form>

{/block}
