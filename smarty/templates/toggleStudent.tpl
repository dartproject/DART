{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script language="JavaScript" type="text/javascript" src="js/toggle.js"></script>
{/block}
{block name="body"}

<font class=big>Individual View - All Content Areas - {$studentName}</font>
<br /><br />
<form name=reports method=get action=''>
	{html_options name=reportMenu values=$reportLinks output=$reportNames
	onChange='window.location=this.value'}
	Go To Report
</form>
<br />
<ul>
	<li type='circle'>
		<font size='2'><b>Note:</b>  Roll over each standard number to read
its short name!</font>
	</li>
</ul>
<p>
	<font size="2">The screen below shows the current status of these students
in this content area.  Toggle the appropriate indicator, and enter comments as
needed. Make sure you &quot;Save Changes&quot; for the entire page from either
the pull down menu, or the button at the bottom of the page.  The time and date
stamp of your entry for this student will be added.</font>
</p>
<br/>
<font size="2">Here is a &quot;weighted list&quot; of the common relative
weaknesses of this student from <i>all of their content areas</i>. The student
standard having no toggled status </font><font size="2">, Emerging status, or
Developing status, the larger the name of the standard is in the list
respectively. This means that the largest short standard names are the most
common relative weaknesses of the student.</font>

<p>
	<font size="4" color="#cc0000">Weighted List of Standards Needed</font>
	<font size="2">: </font>
</p>

<div class="notetarget">
{foreach $weightedStd as $w}
	<a href="{$w.link}" target=_blank><span class="{$w.class}">{$w.span}</span></a> ::
{/foreach}
</div>

<div align="left">
	<ul>
		<li type="circle">
			<font size="2">
				Roll over each content area code to read it!
			</font>
		</li>
		<li type="circle">
			<font size="2">
				Click on the Level Number in any Content Area to view the
				<i>students in this group at that level</i>.
			</font>
		</li>
		<li type="circle">
			<font size="2" color="black">
				Click on the name of the student to see
				<i> his or her standards progress in all content areas</i>.
			</font>
		</li>
		<li type="circle">
			<font size="2">
				Click on any Content Area to
				<i>re-sort the view by Content Area &amp; Level Number</i>.
			</font>
		</li>
	</ul>
</div>

<form name=toggle method=post action=index.php?cmd=saveStudentToggle>
	<input type=hidden name=studentid value={$studentID}>
	<input type=hidden name=loc>

{foreach $data as $sub => $subject}

	<font size=2>
		<b>{$subject.subName}
			<a href=index.php?cmd=updateSingleLevelScore&id={$studentID}&subject={$sub}&level={$subject.lvl} onMouseOver="return escape('Update score for saved values. NOTE: THIS WILL RESET ANY TOGGLE/COMMENT CHANGES NOT SAVED.')">.</a>
			- <font color=#cc0000>{$subject.progress}</font>
		</b>
	</font>
	<br /><a name="{$sub}"></a>
	{html_options name=subjectMenu options=$subjectMenu
	selected={$subjectSelected} onChange='handleSelection(this.value)'}
	<br />
	<b>Student:</b>{$subject.studentText}
	<b>Last Change:</b> {$subject.changeText} -
	<a href=index.php?cmd=history&student={$studentID}&subject={$sub}&lvl={$subject.lvl}>History</a>
	{$totalStd = $subject.totalStd}
	{$totalOver = $subject.totalOver}
	{$lvl = $subject.lvl}
	{$levelName = $subject.levelName}
	{$standards = $subject.std}
	{$overall = $subject.over}
	{$student = $subject}
	{include 'comp/toggle.tpl'}
{/foreach}
{if $Display eq 'edit'}
	<input type=reset value=reset>
	<input type=button onClick='handleSelection("#save_changes")' value='save all changes'>
{/if}
</form>
<br/>* Placing mouse over standard number will display standards descriptions.
{/block}
