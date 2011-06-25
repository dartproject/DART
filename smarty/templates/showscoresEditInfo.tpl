{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script language="JavaScript" type="text/javascript" src="js/showscoresEditInfo.js"></script>
<script language="JavaScript" type="text/javascript" src="lib/jquery-min.js"></script>
{/block}
{block name="body"}

<a href=index.php?cmd=showscores&p1={$listid}>Back to Group</a> |
<a href=index.php?cmd=showscoresEditInfo&listid={$listid}&subcmd=addtab>Add New Tab</a>
<br /><br />

{foreach $data as $tabid=>$tab}

	{html_options name=foo values=$values output=$output selected=$tab.selected onChange="javascript:onChangeOrder('{$tabid}',this.value,'{$listid}');"}
	<input type=text name=grp_tab-tabid-{$tabid}-tabname value='{$tab.tabname}'
				onChange=javascript:onChangeValue('grp_tab-tabid-{$tabid}-tabname',this.value);>
	<a href=index.php?cmd=showscoresEditInfo&listid={$listid}&subcmd=addinfo&tabid={$tabid}>
		Add New Info To Tab
	</a> |
	<a href=index.php?cmd=showscoresEditInfo&listid={$listid}&subcmd=deltab&tabid={$tabid} onclick="return(confirmMsg('Really Delete This Tab'));">
		Delete Tab
	</a>
	<br />

	<table >
		<tr style='background-color:lightgrey; border:0px;'>
			<th>Kind</th>
			<th>Order</th>
			<th>Value</th>
			<th>Width</th>
			<th>Height</th>
			<th></th>
		</tr>
	{foreach $tab.info as $infoid => $info}
		<tr>
			<td><!-- Kind -->
				{html_options name=foo options=$kindMenu selected=$info.kind onChange="javascript:onChangeValue('grp_info-infoid-{$infoid}-kind',this.value);"}
			</td>
			<td><!-- Order -->
				{html_options name=foo values=$info.values output=$info.output selected=$info.selected onChange="javascript:onChangeInfoOrder('{$infoid}',this.value,'{$listid}');"}
			</td>
			<td><!-- Value -->
				<input type=text name=grp_info-infoid-{$infoid}-value value='{$info.value}'
					onChange="javascript:onChangeValue('grp_info-infoid-{$infoid}-value',this.value);">
			</td>
			<td><!-- Width -->
				<input type=text name=grp_info-infoid-{$infoid}-width value='{$info.width}'
					onChange="javascript:onChangeValue('grp_info-infoid-{$infoid}-width',this.value);" size=5>
			</td>
			<td><!-- Height -->
				<input type=text name=grp_info-infoid-{$infoid}-height value='{$info.height}'
					onChange="javascript:onChangeValue('grp_info-infoid-{$infoid}-height',this.value);" size=5>
			</td>
			<td><!-- Delete -->
				<a href=index.php?cmd=showscoresEditInfo&listid={$listid}&subcmd=delinfo&infoid={$infoid}
				onclick="return(confirmMsg('Really Delete This Info'));">
					Delete
				</a>
			</td>
		</tr>		
	{/foreach}
	</table>
	<br /><br />
{/foreach}

{/block}