<table>
	<tr>
		<td>
			Total: {$total}
			Viewing {$searchParameters.start+1} -
			{$final}
			{$searchParameters.start = $prevstart}
			<a href=index.php?cmd={$cmd}{foreach $searchParameters as $name => $value}{if $value neq ''}&{$name}={$value}{/if}{/foreach}>Prev</a>
			{$searchParameters.start = $nextstart}
			<a href=index.php?cmd={$cmd}{foreach $searchParameters as $name => $value}{if $value neq ''}&{$name}={$value}{/if}{/foreach}>Next</a>
		</td>
		<td>
			<form method=get action=index.php>
				<input type=hidden name='cmd' value='{$cmd}' />
				{$searchParameters.start = 0}
				{foreach $searchParameters as $name => $value}
					{if $name eq 'limit'}
						<input type=text name={$name} size=4 value='{$value}' />
					{else}
						<input type=hidden name={$name} value='{$value}' />
					{/if}
				{/foreach}
				<input type=submit value='Display Limit' />
			</form>
		</td>
	</tr>
</table>

