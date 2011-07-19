{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/extjs/bootstrap.js"></script>
<script type="text/javascript" src="js/jquery/jquery.simplemodal.1.4.1.min.js"></script>
<script language="JavaScript" type="text/javascript" src="js/view/Student.js"></script>
<script language="JavaScript" type="text/javascript" src="js/wz_tooltip.js"></script>
<script language="JavaScript" type="text/javascript" src="js/showScores.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/extjs/resources/css/ext-all.css" />
{/block}
{block name="body"}
<style>
    .hidden { display: none; }
    .unhidden { display: inline; }
</style>
<input type="hidden" name="listName" value="{$listName}" />
<input type="hidden" name="imageURL" value="{$imageURL}" />
<div style="width:1024px;">
	<div align="left">
		<br/>
		<font size="4">Overview - All Content Areas - {$listName} Group</font>
		<br />
		<a id="page_help" href="#" onclick="" style="font-size: 8pt; color: #006FEB">
			<img alt="help" src="{$imageURL}icons/help_16.png" style="vertical-align: middle"/> About this page
		</a>

		<blockquote>
			<div id="page_modal_help" style="display:none">
				<p><font size="3"><b>Weighted List of Standards Needed</b></font></p>
				<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><p>
					Here is a &quot;weighted list&quot; of the common relative
					weaknesses of this group of students from <i>all of their content areas</i>.
					The more students is this group that show any standard as having no toggled
					status, Emerging status, or Developing status, the larger the name
					of the standard is in the list. This means that the largest short standard
					names are the most common relative weaknesses of the group.</p>
				</font>
				<br />
				<p><font size="3"><b>Overview - All Content Areas</b></font></p>
				<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
					<!--- Roll over each content area code to read it!</font><br />-->
					- Click on the Level Number in any Content Area to view the <i>students in this group at that level</i>.<br />
					- Click on the name of the student to see<i> his or her standards progress in all content areas</i>.<br />
					- Click on any Content Area to <i>re-sort the view by Content Area &amp; Level Number</i>.<br />
				</font>
			</div>
		</blockquote>
		<br/><br/>
		<p><font size="4" color="#cc0000">Weighted List of Standards Needed</font>
			<font size="2">: </font></p>

		<!-- Weighted List of Standards -->
		<div class="notetarget">
	        {foreach $weightedStd as $w}
			<a href="{$w.link}" target="_blank"><span class="{$w.class}">{$w.span}</span></a> ::
	        {/foreach}
		</div>

	</div>
	<b>Student count - {$stdcount}</b><br/>
	<a href='index.php?cmd=editlist&p1={$listID}'>Edit Group</a> |
	<a href='index.php?cmd=showscoresEditInfo&listid={$listID}'>Edit Tab</a>
	{if $att_am || $att_pm} Take attendance:
	{if $att_am}<a href=index.php?cmd=AttendanceList&listid={$listID}&period=0>AM</a>{/if}
	{if $att_am && $att_pm}|{/if}
	{if $att_pm}<a href=index.php?cmd=AttendanceList&listid={$listID}&period=1>PM</a>{/if}
	{/if}
	<br/>
	<a href="javascript:turnOn('home');">Home</a>

	<!-- Custom tabs -->
	{foreach $tabs as $id=>$t}
		| <a href=javascript:turnOn('{$id}');>{$t.name}</a>
	{/foreach}
	<br/>
	{foreach $tabs as $id=>$t}
	<div id="tab{$id}" class="hidden">
		{foreach $t.subtabs as $s}
			{if $s.kind == 'iframe'}
			<iframe width='{$s.width}' height='{$s.height}' src='{$s.value}'></iframe>
			{else}
				{$s.value}
			{/if}
		<br />
		{/foreach}
	</div>
	{/foreach}
</div>
<div style="margin-bottom:30px;">
	<div id="tabhome" class="unhidden"></div>
</div>
{/block}
