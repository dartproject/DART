{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="body"}
Entire History<br />
<a href=index.php?cmd=history{foreach $searchParameters as $name => $value}{if $value neq ''}&{$name}={$value}{/if}{/foreach}>Page</a><br />
<form action=index.php method=get>
	<input type=hidden name=cmd value={$cmd} />
	{html_options name="user" options=$userMenu selected=$searchParameters.user}
	<input type=submit name=submit />
</form>
<br />
<table border=1>
	<tr>
		<th>Timestamp</th>
		<th>User</th>
		<th>Type</th>
		<th>Username</th>
	</tr>
	{foreach $history as $h}
	<tr>
		<td>{$h.timestamp}</td>
		<td>{$h.user}</td>
		<td>{$h.type}</td>
		<td>{$h.p1}</td>
	</tr>
	{/foreach}
</table>
{include 'comp/pagination.tpl'}
{/block}
