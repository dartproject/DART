{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/extjs/bootstrap.js"></script>
<script language="JavaScript" type="text/javascript" src="js/view/Student.js"></script>
<script language="JavaScript" type="text/javascript" src="js/showScores.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/extjs/resources/css/ext-all.css" />
{/block}
{block name="body"}
<style>
    .hidden { display: none; }
    .unhidden { display: inline; }
</style>
<input type="hidden" name="listName" value="{$listName}" />
<input type="hidden" name="imageURL" value="{$imageURL}" />
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

<div id="tabhome" class="unhidden"></div>

{/block}
