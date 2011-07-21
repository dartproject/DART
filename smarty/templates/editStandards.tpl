{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="body"}

<div style="width:1024px; margin: auto; padding-bottom:30px;">
	<font color="red">{$msg|default:'&nbsp;'}</font>
	{include 'comp/editSubjectButtons.tpl'}
	<form action="index.php" method="get">
		<input type="hidden" name="cmd" value="editStandards" />
		{html_options name="subject" options=$subjectMenu selected=$subject}
		{html_options name="level" options=$levelMenu selected=$level}
		<input type="submit" value="Go To Standards">
	</form>
	<form name="std" action="?cmd=editStandards&subject={$subject}&level={$level}" method="post">
		<input name="change" type="hidden" />
		<table border="1" width="600px">
			<tr>
				<th>Ord</th>
				<th>Standard</th>
				<th>Type</th>
				<th>Shortname</th>
				<th>Description</th>
				<th>Link</th>
			</tr>
			{foreach $standards as $std}
			<tr valign="top">
				<td><input name="ord[]" value="{$std->order}" size="3></td">
				<td>{$subject}.{$level}.{$std->std}
					<input type="hidden" name="id[]" value="{$std->Identifier}">
					<input type="hidden" name="subject[]" value="{$std->subject}">
					<input type="hidden" name="level[]" value="{$std->level}">
					<input type="hidden" name="std[]" value="{$std->std}">
				</td>
				<td>
					{html_options name="type[]" options=$typeMenu selected={$std->type}}
				</td>
				<td><textarea cols={$c} rows={$r} name="shortname[]">{$std->shortname}</textarea></td>
				<td><textarea cols={$c} rows={$r} name="description[]">{$std->description}</textarea></td>
				<td><textarea cols={$c} rows={$r} name="link[]">{$std->link}</textarea></td>
			</tr>
			{/foreach}
		</table>
		<input type="submit" name="button" value="Save">
		<input type="reset" name="button" value="Reset Values" />
	</form>
</div>
{/block}
