{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/extjs/bootstrap.js"></script>
<script language="JavaScript" type="text/javascript" src="js/view/Student.js"></script>
<script language="JavaScript" type="text/javascript" src="js/attendanceDrillDown.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/extjs/resources/css/ext-all.css" />
{/block}
{block name="body"}
<h3>{$view}</h3><br />
<form name="selectionForm" action="index.php?cmd=AttendanceDrillDown&type={$type}&site={$site}&year={$year}&month={$month}&cdate={$cdate}" method="post" >
	<div id="attendanceDrillDown"></div>
	<div align="left">
		<i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i>
		<input type="submit" name="cmd2" onClick='javascript: return checkChecks();' value='Group' />
		<br />
		<br />
		<input type="submit" name="cmd2" value='Export All' />
	</div>
</form>

{/block}
