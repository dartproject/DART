{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script language="JavaScript" type="text/javascript" src="js/jquery-min.js"></script>
<script language="JavaScript" type="text/javascript" src="js/showScores.js"></script>
{/block}
{block name="body"}
<style>
	.hidden { display: none; }
	.unhidden { display: inline; }
</style>
<div align="left">
	<br/>
	<font size="4">Overview - All Content Areas - {$listName} Group<br/><br/></font>
	<font size="2">Here is a &quot;weighted list&quot; of the common relative
		weaknesses of this group of students from <i>all of their content areas</i>.
		The more students is this group that show any standard as having no toggled
		status, Emerging status, or Developing status, the larger the name
		of the standard is in the list. This means that the largest short standard
		names are the most common relative weaknesses of the group.</font>
	<p><font size="4" color="#cc0000">Weighted List of Standards Needed</font>
		<font size="2">: </font></p>
	
	<!-- Weighted List of Standards -->
	<div class="notetarget">
	{foreach $weightedStd as $w}
		<a href="{$w.link}" target="_blank"><span class="{$w.class}">{$w.span}</span></a> ::
	{/foreach}
	</div>

	<div align="left">
		<ul>
			<li type="circle"><font size="2">Roll over each content area code to read it!</font></li>
			<li type="circle"><font size="2">Click on the Level Number in any Content Area to view the <i>students in this group at that level</i>.</font></li>
			<li type="circle"><font size="2" color="black">Click on the name of the student to see<i> his or her standards progress in all content areas</i>. </font><font size="2"></font></li>
			<li type="circle"><font size="2">Click on any Content Area to <i>re-sort the view by Content Area &amp; Level Number</i>.</font></li>
		</ul>
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

<div id="tabhome" class="unhidden">
	<font size="4">
		<table width="100%" border= 1 class=big>
			<tr>
				<th colspan=11 bgcolor=#ccccff><b>{$listName} Group Profile</b></th>
			</tr>
			<tr>
				<th>Name</th>
				{foreach $subjects as $s}
					<th onMouseOver="return escape('{$s.name}')">{$s.id}</th>
				{/foreach}
				<td>EL</td>
			</tr>
			{foreach $list as $l}
			<tr bgcolor="{cycle values="$color1,$color2"}">
				<td nowrap><a href=index.php?cmd=toggleStudent&p1={$l.studentid}>{$l.fname} {$l.lname}</a></td>
				{foreach $subjects as $s}
					<td><a href="index.php?cmd=toggle&p1={$listID}&p2={$s.id}&p3={$student.{$l.studentid}.{$s.id}}">{$student.{$l.studentid}.{$s.id}}</a></td>
				{/foreach}
				<td>
				{foreach $electives as $e}
					{if $student.{$l.studentid}.{$e.id} != ''}
						<a href="index.php?cmd=toggle&p1={$listID}&p2={$e.id}&p3={$student.{$l.studentid}.{$e.id}}">{$e.id}.{$student.{$l.studentid}.{$e.id}}</a>
					{/if}
				{/foreach}
				</td>
			</tr>
			{/foreach}
		</table>
	</font>
</div>
{/block}