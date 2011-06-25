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

	{foreach $data as $studentID => $student}
		<a name="{$student.anchor}"></a>
		<b><font color='#cc0000' class=big>
			<a href=index.php?cmd=toggleStudent&p1={$studentID}>{$student.text}</a>
			<a href=index.php?cmd=updateSingleLevelScore&id={$studentI}&subject={$sub}&level={$lvl}
			   onMouseOver="return escape('Update score for saved values. NOTE: THIS WILL RESET ANY TOGGLE/COMMENT CHANGES NOT SAVED.')">.</a>
			- <font color=#cc0000>{$student.progress}</font>
		</font></b><br/>
		<b>{$subName} {$lvl} Students
		{html_options name=pullDownMenu options=$menuData selected='' onChange="handleSelection(this.value)"}
		</b><br />
		<b>Last Change:</b> {$student.change} -
		<a href=index.php?cmd=history&student={$studentID}&subject={$sub}&lvl={$lvl}>History</a>
		<table border= 1>

		<!-- Standards -->
		{$start = 0}{$end = $width-1}
		{while $start < $totalStd}
			<tr  bgcolor=#FFFFCC>
				<th rowspan=2>{$sub} ({$lvl})</th>
			{for $i=$start to $end max=$totalStd}
				{$std = $standards.{$i}}
				<th width={$cellwidth} onMouseOver="return escape('{$std.description}')"> <a href="{$std.link}">{$std.std}</a></th>
			{/for}
			</tr>
			<tr>
			{if $student.display eq 'edit'}
				{for $i=$start to $end max=$totalStd}
					{$std = $standards.{$i}}
					<td>
						<input type=hidden name="old_{$student.std.{$std.std}.name}" value="{$student.std.{$std.std}.value}" />
						<input type=hidden id="ch_{$student.std.{$std.std}.name}" name="ch_{$student.std.{$std.std}.name}" value=empty />
						{html_options name="{$student.std.{$std.std}.name}" options=$student.std.{$std.std}.options selected=$student.std.{$std.std}.selected title ="test_{$studentID}_{$i}" onChange="changeValue('{$student.std.{$std.std}.name}',this.value)"}
					</td>
				{/for}
			{else}
				{for $i=$start to $end max=$totalStd}
					{$std = $standards.{$i}}
					<td align=center>&nbsp;{$student.std.{$std.std}.value}&nbsp;</td>
				{/for}
			{/if}
			</tr>
			{$start = $end+1}{$end = $end+$width}{if $end > $totalStd}{$end = $totalStd-1}{/if}
		{/while}
		</table>
		<table border= 1>
		<!-- Overall -->
		{$start = 0}{$end = $width-1}
		{while $start < $totalOver+$n_ind}
			<tr  bgcolor=#FFFFCC>
				<th rowspan=2>{$sub} ({$lvl})</th>
			{for $i=$start to $end max=$totalOver}
				{$over = $overall.{$i}}
				<th width={$cellwidth} onMouseOver="return escape('{$over.description}')">{$over.std}</th>
			{/for}
			{if $end+1 >= $totalOver - 1} {* Last row *}
			<!-- Indicators -->
				{foreach $indicators as $indID => $ind}
					<th width={$cellwidth} onMouseOver="return escape('{$ind.description}')">{$ind.label}</th>
				{/foreach}
			{/if}
			</tr>
			<tr>
			{if $student.display eq 'edit'}
				<!-- Overall -->
				{for $i=$start to $end max=$totalOver}
					{$over = $overall.{$i}}
					<td>
						<input type=hidden name="old_{$student.over.{$over.std}.name}" value="{$student.over.{$over.std}.value}" />
						<input type=hidden id="ch_{$student.over.{$over.std}.name}" name="ch_{$student.over.{$over.std}.name}" value=empty />
						{html_options name="{$student.over.{$over.std}.name}" options=$student.over.{$over.std}.options selected={$student.over.{$over.std}.selected} title ="test_{$studentID}_{$i}" onChange="changeValue('{$student.over.{$over.std}.name}',this.value)"}
					</td>
				{/for}
				<!-- Indicators -->
				{foreach $indicators as $indID => $ind}
					<td>
						<input type=hidden name=old_{$student.ind.{$indID}.name} value={$student.ind.{$indID}.value}> <!-- This one should be missing for "prog"... @todo -->
						<input type=hidden id=ch_{$student.ind.{$indID}.name} name=ch_{$student.ind.{$indID}.name} value=empty>
						{html_options name={$student.ind.{$indID}.name} values=$ind.options output=$ind.options selected="{$student.ind.{$indID}.value}" onChange="changeValue('{$student.ind.{$indID}.name}', this.value)"}
 				 	</td>
				{/foreach}
			{else}
				<!-- Overall -->
				{for $i=$start to $end  max=$totalOver}
					{$over = $overall.{$i}}
					<td align=center>&nbsp;{$student.over.{$over.std}.value}&nbsp;</td>
				{/for}
				<!-- Indicators -->
				<td align=center>&nbsp;{$indicators.qpi.value}&nbsp;</td>
				<td align=center>&nbsp;{$indicators.ase.value}&nbsp;</td>
				<!-- Nothing for "prog", @todo -->
			{/if}
			{$start = $end+1}{$end = $end+$width}{if $end > $totalOver}{$end = $totalOver-1}{/if}
			{if $end+1 >= $totalOver - 1} {* Last row *}
			{/if}
			</tr>
		{/while}
		</table>
		<input type=hidden name="old_{$student.comment_id}" value="{$student.comment}" />
		<input type=hidden id="ch_{$student.comment_id}" name="ch_{$student.comment_id}" value=empty />
		<font size="2"><b>Teacher Comments:</b></font><br/>
		{if $student.display eq 'edit'}
		<textarea name="comment_{$studentID}" rows="8" cols="80" wrap="physical" onChange='changeValue("{$student.comment_id}",this.value )'>{$student.comment}</textarea><br/>
		{else}
		{$student.comment}&nbsp;<br/><br/>
		{/if}
		{/foreach}
		{if $totalDisplay eq 'edit'}
			<input type=reset value=reset>
			<input type=button onClick='handleSelection("#save_changes")' value='save all changes'>
		{/if}
	</form>
	<br/>* Placing mouse over standard number will display standards descriptions.
{/block}
