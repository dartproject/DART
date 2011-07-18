{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/extjs/bootstrap.js"></script>
<script language="JavaScript" type="text/javascript" src="js/view/Discipline.js"></script>
<script language="JavaScript" type="text/javascript" src="js/disciplineList.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/extjs/resources/css/ext-all.css" />
{/block}
{block name="body"}
<div style="width:1024px;">
	<input type="hidden" name="imageURL" value="{$imageURL}" />
	<h3>Discipline Incidents during school year {$year}: {$name}</h3>
	<br />
	<div id="disciplineList"></div>
	<a href="?cmd=disciplineCreate&studentid={$studentid}">Create Discipline</a>
</div>
{/block}
