{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
<script type="text/javascript" src="js/jquery.datepick.package/jquery.datepick.js"></script>
<script language="JavaScript" type="text/javascript" src="js/sped/spedhistory.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/jquery.datepick.package/jquery.datepick.css" />
{/block}

{block name="body"}
Entire History<br />
<a href=index.php?cmd=history>Page</a> |
<a href=index.php?cmd=count>Count Screen</a><br /><br />
{if $Display != 'none'}
<form action=index.php method=get>
	<input type=hidden name=module value=sped>
	<input type=hidden name=cmd value={$cmd} />
	Start:
	<input id=startdate type=text name=startdate value='{$searchParameters.startdate}' />
	<input id=startOutput type=hidden name=startOutput value='{$searchParameters.startOutput}' />
	End:
	<input id=enddate type=text name=enddate value='{$searchParameters.enddate}' />
	<input id=endOutput type=hidden name=endOutput value='{$searchParameters.endOutput}' />
	Site:
	{html_options name="site" options=$siteMenu selected=$searchParameters.site}
	{html_options name="user" options=$userMenu selected=$searchParameters.user}
	<br />
	{html_options name="student" options=$studentMenu selected=$searchParameters.student}
	<input type=submit name=submit />
</form>
{/if}
<br />
<table border=1>
	<tr>
		<th>Timestamp</th>
		<th>Type</th>
		<th>User</th>
		<th>Site</th>
		<th>Value</th>
		<th>StudentID</th>
	</tr>
	{foreach $history as $h}
	<tr>
		<td>{$h.timestamp}</td>
		<td>{$h.type}</td>
		<td>{$h.user}</td>
		<td>{$h.site}</td>
		<td>{$h.value}</td>
		<td nowrap>{$h.studentName}<br />({$h.studentID})</td>
	</tr>
	{/foreach}
</table>
{include 'comp/pagination.tpl'}
{/block}
