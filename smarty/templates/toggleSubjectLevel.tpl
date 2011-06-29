{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script language="JavaScript" type="text/javascript" src="js/toggle.js"></script>
{/block}
{block name="body"}
<form name=toggle method=post action=index.php?cmd=saveToggle>
	<input type=hidden name=loc />
	<input type=hidden name=listID value={$listID} />
	<input type=hidden name=sub value={$sub} />
	<input type=hidden name=lvl value={$lvl} />
	<div align='left'>
		<br/>
		<font size='4'>{$stdcount} Student(s) - {$subName} {$lvl} - {$listName} Group<br/></font>
		<font size='2'>
			{html_options name=pullDownMenu options=$menuData selected='' onChange="handleSelection(this.value)"}
		</font>
		<ul>
			<li type='circle'><font size='2'><b>Note:</b> Roll over each standard number to read its short name!</font></li>
		</ul>
		<p>
		The screen below shows the current status of these students in this
		content area.  Toggle the appropriate indicator, and enter comments as
		needed. Make sure you &quot;Save Changes&quot; for the entire page from
		either the pull down menu, or the button at the bottom of the page.  The
		time and date stamp of your entry for this student will be added.
		</p>
		<br/>
		<font size='4'>Shared Standard Needs - {$subName} {$lvl} - {$listName}<br/><br/></font>
		<p>
		<font size='2'>Here is a &quot;weighted list&quot; of the common relative
		weaknesses of this group of students. The more students is this group that
		show any standard as having no toggled status, Emerging status, or Developing
		status, the larger the name of the standard is in the list. This means that
		the largest short standard names are the most common relative weaknesses of
		the group.</font>
		</p>
		<p><font size='4' color='#cc0000'>Weighted List of Standards &amp; Assessments Needed</font><font size='2'>: </font></p>
	</div>
	<div class="notetarget">
	{foreach $weightedStd as $w}
		<a href="{$w.link}" target=_blank><span class="{$w.class}">{$w.span}</span></a> ::
	{/foreach}
	</div>

	{foreach $data as $student}
		<a name="{$student.anchor}"></a>
		<b><font color='#cc0000' class=big>
			<a href=index.php?cmd=toggleStudent&p1={$student.studentID}>{$student.text}</a>
			<a href=index.php?cmd=updateSingleLevelScore&id={$student.studentID}&subject={$sub}&level={$lvl}
			   onMouseOver="return escape('Update score for saved values. NOTE: THIS WILL RESET ANY TOGGLE/COMMENT CHANGES NOT SAVED.')">.</a>
			- <font color=#cc0000>{$student.progress}</font>
		</font></b><br/>
		<b>{$subName} {$lvl} Students
		{html_options name=pullDownMenu options=$menuData selected='' onChange="handleSelection(this.value)"}
		</b><br />
		<b>Last Change:</b> {$student.change} -
		<a href=index.php?cmd=history&student={$student.studentID}&subject={$sub}&lvl={$lvl}>History</a>

		{$Display = $student.display}
		{$gradeSymbols = $student.gradeSymbols}
		{$studentID = $student.studentID}
		{include 'comp/toggle.tpl'}
		{/foreach}
		{if $totalDisplay eq 'edit'}
			<input type=reset value=reset>
			<input type=button onClick='handleSelection("#save_changes")' value='save all changes'>
		{/if}
	</form>
	<br/>* Placing mouse over standard number will display standards descriptions.
{/block}
