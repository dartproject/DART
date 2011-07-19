{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/jquery/jquery.simplemodal.1.4.1.min.js"></script>
<script language="JavaScript" type="text/javascript" src="js/toggle.js"></script>
<script language="JavaScript" type="text/javascript" src="js/wz_tooltip.js"></script>
{/block}
{block name="body"}

<div style="width:1024px; margin: auto; padding-bottom:30px;">
	<font class="big">Individual View - All Content Areas - {$studentName}</font>
	<br />
	<a id="page_help" href="#" onclick="" style="font-size: 8pt; color: #006FEB">
		<img alt="help" src="{$imageURL}icons/help_16.png" style="vertical-align: middle"/> About this page
	</a>

	<blockquote>
		<div id="page_modal_help" style="display:none">
			<p><font size="3"><b>Individual View - All Content Areas</b></font></p>
			<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
				<p>
				The screen below shows the current status of these students
				in this content area.  Toggle the appropriate indicator, and enter comments as
				needed. Make sure you &quot;Save Changes&quot; for the entire page from either
				the pull down menu, or the button at the bottom of the page.  The time and date
				stamp of your entry for this student will be added.
				</p>
				<ul>
					<li type='circle'>
						<font size='2'><b>Note:</b>  Roll over each standard number to read
						its short name!</font>
					</li>
				</ul>
			</font>
			<p><font size="3"><b>Weighted List of Standards Needed</b></font></p>
			<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
				<p>
				Here is a &quot;weighted list&quot; of the common relative
				weaknesses of this student from <i>all of their content areas</i>. The student
				standard having no toggled status </font><font size="2">, Emerging status, or
				Developing status, the larger the name of the standard is in the list
				respectively. This means that the largest short standard names are the most
				common relative weaknesses of the student.
				</p>
			</font>
		</div>
	</blockquote>
	<br/>
	<p>
		<font size="4" color="#cc0000">Weighted List of Standards Needed</font>
		<font size="2">: </font>
	</p>

	<div class="notetarget">
	{foreach $weightedStd as $w}
		<a href="{$w.link}" target="_blank"><span class="{$w.class}">{$w.span}</span></a> ::
	{/foreach}
	</div>

	<form name="toggle" method="post" action=index.php?cmd=saveStudentToggle>
		<input type="hidden" name="studentid" value={$studentID} />
		<input type="hidden" name="loc" />

		{foreach $data as $sub => $subject}

		<font size="2">
			<b>{$subject.subName}
				<a href=index.php?cmd=updateSingleLevelScore&id={$studentID}&subject={$sub}&level={$subject.lvl} onMouseOver="return escape('Update score for saved values. NOTE: THIS WILL RESET ANY TOGGLE/COMMENT CHANGES NOT SAVED.')">.</a>
				- <font color=#cc0000>{$subject.progress}</font>
			</b>
		</font>
		<br /><a name="{$sub}"></a>
		{html_options name="subjectMenu" options=$subjectMenu
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
		<input type="reset" value="reset">
		<input type="button" onClick='handleSelection("#save_changes")' value='save all changes'>
	{/if}
	</form>
	<br />* Placing mouse over standard number will display standards descriptions.
</div>
{/block}
