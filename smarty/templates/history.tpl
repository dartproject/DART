{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
<script type="text/javascript" src="js/jquery.datepick.package/jquery.datepick.js"></script>
<script language="JavaScript" type="text/javascript" src="js/history.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/jquery.datepick.package/jquery.datepick.css" />
{/block}

{block name="body"}
Entire History<br />
<a href=index.php?cmd=history{foreach $searchParameters as $name => $value}{if $value neq ''}&{$name}={$value}{/if}{/foreach}>Page</a> |
<a href=index.php?cmd=count>Count Screen</a><br /><br />
{if $Display != 'none'}
<form action=index.php method=get>
	<input type=hidden name=cmd value=history />
	Start:
	<input id=startdate type=text name=startdate value='{$searchParameters.startdate}' />
	<input id=startOutput type=hidden name=startOutput value='{$searchParameters.startOutput}' />
	END:
	<input id=enddate type=text name=enddate value='{$searchParameters.enddate}' />
	<input id=endOutput type=hidden name=endOutput value='{$searchParameters.endOutput}' />
	Site:
	{html_options name="site" options=$siteMenu selected=$searchParameters.site}
	Toggle Type:
	{html_options name="toggle" options=$typeMenu selected=$searchParameters.toggle}
	<br />
	{html_options name="user" options=$userMenu selected=$searchParameters.user}
	{html_options name="student" options=$studentMenu selected=$searchParameters.student}
	{html_options name="subject" options=$subjectMenu selected=$searchParameters.subject}
	{html_options name="level" options=$levelMenu selected=$searchParameters.level}
	<input type=submit name=submit />
</form>
{/if}
<br />
<table border=1>
	<tr>
		<th>Timestamp</th>
		<th>Type</th>
		<th>User</th>
		<th>Subject</th>
		<th>Level</th>
		<th>Sth</th>
		<th>Value</th>
		<th>StudentID</th>
	</tr>
	{foreach $history as $h}
	<tr>
		<td>{$h.dt}</td>
		<td>{$h.type}</td>
		<td>{$h.user}</td>
		<td>{$h.subject}</td>
		<td>{$h.lvl}</td>
		<td>{$h.std}</td>
		<td>{$h.value}</td>
		<td nowrap>{$h.studentName}<br />({$h.studentID})</td>
	</tr>
	{/foreach}
</table>
{include 'comp/pagination.tpl'}
{/block}
