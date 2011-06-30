{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
<script type="text/javascript" src="js/jquery.datepick.package/jquery.datepick.js"></script>
<script language="JavaScript" type="text/javascript" src="js/count.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/jquery.datepick.package/jquery.datepick.css" />
{/block}

{block name="body"}
{if $Display eq 'none'}{$msg}
{else}
	<form method=get action="index.php?cmd=count">
		<input type=hidden name=cmd value=count />
		Start:
		<input id=start type=text name=start value='{$start}' />
		<input id=startOutput type=hidden name=startOutput  value='{$startOutput}'>
		End:
		<input id=end type=text name=end value='{$end}'>
		<input id=endOutput type=hidden name=endOutput  value='{$endOutput}'>
		Site:
		{html_options name="site" options=$siteMenu selected=$site}
		Type:
		{html_options name="toggle" options=$toggleMenu selected=$toggle}
		<input type=submit name=button value=go />
	</form>
	{if $isGET}
	<p>Show data from {$start} - {$end} for {$get_site}</p>
	<table border=1>
	<tr>
		<th>Name</th>
		<th>Site</th>
		<th>Toggles</th>
		<th>Comments</th>
	</tr>
	{foreach $data as $person}
		<tr>
			<td>{$person.name}</td>
			<td>{$person.site}</td>
			<td>
				<a href=index.php?cmd=history&toggletype=std&{$person.filter}&startdate={$start}&startOutput={$startOutput}&enddate={$end}&endOutput={$endOutput}&site={$site}>{$person.toggle}</a>
			</td>
			<td>
				<a href=index.php?cmd=history&toggletype=comment&{$person.filter}&startdate={$start}&startOutput={$startOutput}&enddate={$end}&endOutput={$endOutput}&site={$site}>{$person.comments}</a>
			</td>
		</tr>
	{/foreach}
	</table>
	{/if}
{/if}
{/block}
