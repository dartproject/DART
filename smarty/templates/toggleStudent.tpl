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

	<table border=1>

	<!-- Standards -->
		{$start = 0}{$end = $width-1}
		{while $start < $subject.totalStd}
			{$max = $subject.totalStd - $start} 
			<tr rowspan=2 bgcolor={$color1}>
				<th rowspan=2>{$sub} ({$subject.lvl})<br />{$subject.levelName}</th>
			{for $i=$start to $end max=$max}
				{$standard = $subject.std.{$i}}
				<th width={$cellwidth} onMouseOver="return escape('{$standard.description}')">&nbsp;&nbsp;
					<a href={$standard.link}>{$standard.std}</a>&nbsp;&nbsp;
				</th>
			{/for}
			</tr>
			<tr>
			{if $Display eq 'edit'}
				{for $i=$start to $end max=$max}
					{$standard = $subject.std.{$i}}
					<td>
						<input type=hidden name="old_{$standard.name}" value="{$standard.value}" />
						<input type=hidden name="ch_{$standard.name}" value=empty />
						{html_options name="{$standard.name}" options=$gradeSymbols selected={$standard.selected} onChange="changeValue('{$standard.name}',this.value)"}
					</td>
				{/for}
			{else}
				{for $i=$start to $end max=$max}
					{$standard = $subject.std.{$i}}
					<td align=center>&nbsp;{$standard.symbol}&nbsp;</td>
				{/for}
			{/if}
			</tr>
			{$start = $end+1}{$end = $end+$width}{if $end > $subject.totalStd}{$end = $subject.totalStd-1}{/if}
		{/while}
		</table>
		<table border= 1>

		<!-- Overall -->
		{$start = 0}{$end = $width-1}
		{while $start < $subject.totalOver+$n_ind}
			{$max = $subject.totalOver - $start} 
			<tr rowspan=2 bgcolor={$color1}>
				<th rowspan=2>{$sub} ({$subject.lvl})<br />{$subject.levelName}</th>
			{for $i=$start to $end max=$max}
				{$over = $subject.over.{$i}}
				<th width={$cellwidth} onMouseOver="return escape('{$over.description}')">{$over.std}</th>
			{/for}
			{if $end >= $subject.totalOver - 1} {* Last row *}
				<!-- Summary -->
				{foreach $summary as $indID => $ind}
					<th width={$cellwidth} onMouseOver="return escape('{$ind.description}')">{$ind.label}</th>
				{/foreach}
			{/if}
			</tr>
			<tr>
			{if $Display eq 'edit'}
				<!-- Overall -->
				{for $i=$start to $end max=$max}
					{$over = $subject.over.{$i}}
					<td>
						<input type=hidden name="old_{$over.name}" value="{$over.value}" />
						<input type=hidden id="ch_{$over.name}" name="ch_{$over.name}" value=empty />
						{html_options name="{$over.name}" options=$gradeSymbols selected={$over.selected} title ="test_{$studentID}_over_{$i}" onChange="changeValue('{$over.name}',this.value)"}
					</td>
				{/for}

				{if $end >= $subject.totalOver - 1} {* Last row *}
					<!-- Summary -->
					{foreach $summary as $indID => $val}
						{$ind = $subject.ind.{$indID}}
						<td>
							<input type=hidden name=old_{$ind.name} value={$ind.value}> <!-- This one should be missing for "prog"... @todo -->
							<input type=hidden id=ch_{$ind.name} name=ch_{$ind.name} value=empty>
							{html_options name={$ind.name} values=$val.options output=$val.options selected="{$ind.value}" onChange="changeValue('{$ind.name}', this.value)"}
						</td>
					{/foreach}
				{/if}
			{else}
				<!-- Overall -->
				{for $i=$start to $end  max=$max}
					{$over = $subject.over.{$i}}
					<td align=center>&nbsp;{$over.symbol}&nbsp;</td>
				{/for}
				{if $end >= $subject.totalOver - 1} {* Last row *}
					<!-- Summary -->
					<td align=center>&nbsp;{$summary.qpi.value}&nbsp;</td>
					<td align=center>&nbsp;{$summary.ase.value}&nbsp;</td>
					<!-- Nothing for "prog", @todo -->
				{/if}
			{/if}
			{$start = $end+1}{$end = $end+$width}
			{if $end >= $subject.totalOver - 1} {* Last row *}
				{$end = $subject.totalOver+$n_ind}
			{/if}
			</tr>
		{/while}
		</table>
		<input type=hidden name="old_{$subject.comment_id}" value="{$subject.esc_comment}">
		<input type=hidden id="ch_{$subject.comment_id}" name="ch_{$subject.comment_id}" value=empty>
		<font size="2"><b>Teacher Comments:</b></font><br/>
		{if $Display eq 'edit'}
		<textarea name="comment_{$studentID}" rows="8" cols="80" wrap="physical" onChange='changeValue("{$subject.comment_id}",this.value )'>{$subject.comment}</textarea><br/>
		{else}
		&nbsp;{$subject.comment}&nbsp;
		{/if}
		<br /><br />
		{/foreach}
		{if $Display eq 'edit'}
			<input type=reset value=reset>
			<input type=button onClick='handleSelection("#save_changes")' value='save all changes'>
		{/if}
	</form>
	<br/>* Placing mouse over standard number will display standards descriptions.
{/block}
