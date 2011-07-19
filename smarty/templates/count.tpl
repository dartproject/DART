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
<div style="width:1024px; margin: auto; padding-bottom:30px;">
	{if $Display eq 'none'}{$msg}
	{else}
		<form method=get action="index.php?cmd=count">
			<input type=hidden name=cmd value=count />
			Start:
			<input id=startdate type=text name=startdate value='{$searchParameters.startdate}' />
			<input id=startOutput type=hidden name=startOutput  value='{$searchParameters.startOutput}'>
			End:
			<input id=enddate type=text name=enddate value='{$searchParameters.enddate}'>
			<input id=endOutput type=hidden name=endOutput  value='{$searchParameters.endOutput}'>
			Site:
			{html_options name="site" options=$siteMenu selected=$searchParameters.site}
			Type:
			{html_options name="toggle" options=$toggleMenu selected=$searchParameters.toggle}
			<input type=submit name=button value=go />
		</form>
		{if $isGET}
		<p>Show data from {$searchParameters.startdate} - {$searchParameters.enddate} for {$get_site}</p>
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
				<td>{if $person.toggle}
					<a href=index.php?cmd=history&toggle=std&{$person.filter}&startdate={$startdate}&startOutput={$startOutput}&enddate={$enddate}&endOutput={$endOutput}&site={$site}>{$person.toggle}</a>
					{else}0{/if}
				</td>
				<td>{if $person.comments}
					<a href=index.php?cmd=history&toggle=comment&{$person.filter}&startdate={$startdate}&startOutput={$startOutput}&enddate={$enddate}&endOutput={$endOutput}&site={$site}>{$person.comments}</a>
					{else}0{/if}
				</td>
			</tr>
		{/foreach}
		</table>
		{include 'comp/pagination.tpl'}
		{/if}
	{/if}
</div>
{/block}
