{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script language="JavaScript" type="text/javascript" src="js/editlist.js">
</script>
{/block}

{block name="body"}
<div style="width:1024px; margin: 0 auto">
	<table width=80%  border="0" cellpadding="5" cellspacing="0">
		<tr>
			<td colspan="5">
				<form name="editList" action="index.php" method="get">
					<input type="hidden" name="cmd" value="editlist" />
					{html_options name="p1" options=$listMenu selected=$listID onChange="submit()"}
					Select to edit list
				</form>
			</td>
		</tr>
		<tr>
			<td>Group Name:</td>
			<td>
				<form style="margin-bottom:0;" name="updateName" method="post" action="index.php?cmd=updateListName">
					<input type="hidden" name="p1" value="{$listID}" />
					<input type="text" name="p2" maxlength="16" size="18" value="{$listname}" />
					<input name="save" type="submit" value="Rename Group" />
					<input type="submit" onClick="return confirm_delete('{$listID}');" value="Delete Group" />
				</form>
			</td>
			<td nowrap>&nbsp;&nbsp;Type: </td>
			<td>
				<form style="margin-bottom:0;" name="updateType" method="post" action="index.php?cmd=updateListType">
					<input type="hidden" name="p1" value="{$listID}" />
					<input type="hidden" name="userid" value="{$currentUserID}" />
					{html_options name="p2" options=$typeMenu selected=$type onChange="submit()"}
				</form>
			</td>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
		</tr>

		{if $listKind neq "search"}
		<tr>
			<td colspan="5">
				<form name="studentform" id="studentform" method="post" action="index.php?cmd=updatelist">
					<input type="hidden" name="previoussearch" value="0" />
					<input type="hidden" name="id" value="{$listID}" />
					<table align="center" border="0" cellpadding="5" cellspacing="0">
						<tr>
							<td valign="top">
								{$showcount}  Current Group Members
							</td>
							<td>&nbsp;</td>
							<td valign="top">
								{$potentialCount} Potential Group Members
							</td>
						</tr>
						<tr>
							<td valign="top">
								{html_options name="removeselect[]" size="20" id="removeselect" multiple="multiple" onFocus="studentSelected('removeselect')" options=$membersMenu}
							</td>
							<td valign="top">
								<br />
								<input name="add" type="submit" id="add" value="&larr;" />
								<br />
								<input name="remove" type="submit" id="remove" value="&rarr;" />
								<br />
							</td>
							<td valign="top">
								{html_options name="addselect[]" size="20" id="addselect" multiple="multiple" onFocus="studentSelected('addselect')" options=$potentialMenu}
								<br />
							</td>
						</tr>
					</table>
				</form>
			</td>
		</tr>
		{else}
		<tr>
			<td colspan="5">
				<h2>Search List</h2>
			</td>
		</tr>
		{/if}
		<tr>
			<td align="center" colspan="5">
				<table border="0">
					<tr>
						<td>
						{if $showSFA}
							<form name="exportlist" id="exportlist" method="post" action="index.php?cmd=exportlist&listid={$listID}&type=sfa">
								<input name="export" type="submit" id="export" value="SFA Export" />
							</form>
						{else}&nbsp;{/if}
						</td>
						<td>
							<form name="exportlist" id="exportlist" method="post" action="index.php?cmd=exportlist&listid={$listID}">
								<input name="export" type="submit" id="export" value="Export" />
							</form>
						</td>
						<td>
							<form name="duplist" id="duplist" method="post" action="index.php?cmd=duplist&listid={$listID}">
								<input name="dup" type="submit" id="dup" value="Duplicate" />
							</form>
						</td>
					</tr>
					<tr>
						<td colspan="3">
						{if $showExport}
							<br />
							<b>Export Presets</b>
							<br />
							<form action="index.php?cmd=handleGroup" method="post">
								<input type="hidden" name="cmd" value="handleGroup">
								<input type="hidden" name="listid" value="{$listID}">
								<table>
									<tr>
										<td>
											<input type="text" name="startdate" size="10" value="{$qstart}">
										</td>
										<td>
											<input type="text" name="enddate"  size="10" value="{$qend}">
										</td>
										<td>
											{html_options name="cmd2" options=$exportMenu}
										</td>
										<td>
											<input type="submit" name="Go" value="Go" />
										</td>
									</tr>
								</table>
							</form>
						{else}&nbsp;{/if}
						</td>
					</tr>
				</table>
				{if $showAttendance}
				<hr />
				<form name="myform" action="index.php" method="GET">
					<div align="center">
						<input type="hidden" name="cmd" value="editlist" />
						<input type="hidden" name="p1" value="{$listID}" />
						<b>Attendance Period</b>
						<br />
						<input type="checkbox" name="am" value="1" {if $am}checked="checked"{/if} /> am
							   <input type="checkbox" name="pm" value="1" {if $pm}checked="checked"{/if} /> pm
							   <br />
						<b>Users With Access</b>
						<br />
							{html_options name="test[]" size="10" id="test" multiple="multiple" options=$userMenu selected=$currentUserIDs}
						<br />
						<input type="submit" value="Make Official Attendance List" name="attSubmit" />
						<br />
						<br />
						<b>Curent Users Who Share The List</b>
						<br />
						{foreach $currentUserNames as $name}
							{$name}<br />
						{/foreach}
					</div>
				</form>
				{/if}
			</td>
		</tr>
		<tr>
			<td>
				<br />
				<a href="?cmd=gb_edit&subcmd=newgb&listid={$listID}">New Gradebook</a>
				<br />
				<br />
				GradeBooks
				<br />
				{foreach $gradebooks as $gid => $name}
					{$name}
					<a href=?cmd=gb&gid={$gid}>View</a>
					<a href=?cmd=gb_edit&gid={$gid}>Edit</a>
					<br />
				{/foreach}
			</td>
		</tr>
	</table>
</div>

{/block}