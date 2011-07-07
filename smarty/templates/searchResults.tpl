{*
 *  Copyright (C) 2011 author (email)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*}

{extends file="layout.tpl"}
{block name="title"}Search Results{/block}

{block name=css}
{/block}

{block name="js"}
<script type="text/javascript" src="js/searchResults.js"></script>
{/block}

{block name="body"}
<div align="center">
    <form name="fieldsForm" action="index.php?cmd=handleGroup" method="post" >
        <input type="hidden" name="action" value="bulk_action">
        <table width="100%" border="0" cellspacing="2" cellpadding="0">
            <tr>
                <td>
                    <div align="left">
                        <br>
                        <div align="left">
                            <font size="4" color="#cc0000">DART Search Results - here is what we found</font><br>
                            <a href="index.php?cmd=search"><button style="width:300px">New Search</button></a>
                        </div>
                        {*<div class="noteimportant">These are the records in the system that match your search query.  By using the links below you can select individuals to form new groups based on these criteria, add a person to an existing group you have access to, view his or her acount details, print reports, or export their data. You can resort the results by clicking the top of each column, and use the controls at the bottom of the screen to perform actions or change how many records you view on a screen.
                        </div> *}
                    </div>
                </td>
            </tr>
            <tr>
                <td>
                    <div align="center">
                        <br>
                                          
                        <table border="0" cellspacing="0" cellpadding="0" width="100%">
                            <tr>
                                <td width="100%">
                                    <table width="100%" cellpadding="1" cellspacing="1" border="0" class="listtable">
                                        
                                        <tr class="listhead">
                                            <td width="2%"></td>                                            
                                            <td></td>                          
                                            <td align="center" nowrap><a href="(EmptyReference!)">&nbsp;Name&nbsp;</a></td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">Student Number</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">AK Student ID</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">School Site</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">Time Frame</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">Testing<br>Grade</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">Age</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">Status&nbsp;</a></div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                    <a href="(EmptyReference!)">Code&nbsp;</a></div>
                                            </td>
                                            <td align="center" nowrap>
                                                <div align="center">
                                                    &nbsp;Action&nbsp;
                                                </div>
                                            </td>
                                            
                                        </tr>
{* results*}
                                        {foreach $students as $student}
                                            {if $student@iteration is div by 2}
                                        <tr bgcolor=#f4f7fd>
                                            {else}
                                        <tr bgcolor=#E5E5E5>
                                            {/if}
                                            <td align="center" nowrap><input type="checkbox" name="studentID[]" value="{$student.studentid}" class="radio"></td>
                                            {if $showEdit}
                                            <td style="text-align:center">
                                                <a href="index.php?cmd=StudentEdit&id={$student.studentid}">
                                                    <img alt="EditStudent" src="{$imageURL}icons/user_edit_16.png" title="Edit student's information" style="padding:2px; vertical-align: middle" />
                                                </a>
                                            </td>
                                            {/if}
                                            <td nowrap>
                                                <a href="index.php?cmd=toggleStudent&p1={$student.studentid}">
                                                    {$student.fname} {$student.lname}
                                                </a>
                                            </td>
                                            <td>
                                                <div align="center">
                                                {$student.studentid}
                                                </div>
                                            </td>
                                            <td>
                                                <div align="center">
						{$student.alaskaid}
                                                </div>
                                            </td>
                                            <td>
                                                <div align="center">
                                                {$student.site}
                                                </div>
                                            </td>
                                            <td>
                                                <div align="center">
                                                {$yearDisplay}
                                                </div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                {$student.grade}
                                                </div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
						{$student.bday|age}
                                                </div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
                                                {if $showStudentStatusLink}
                                                    {if $student.status eq "Active"}
                                                    <a href='' onClick="popUp('./index.php?cmd=StudentExit&id={$student.studentid}', 800, 600);return(false);">
                                                        <font color="#009966">Active</font>
                                                    </a>
                                                     {else}
                                                    <a href="" onClick="popUp('./index.php?cmd=StudentEnter&id={$student.studentid}', 800, 600);return(false);" >
                                                        <font color=red>Inactive</font>
                                                    </a>
                                                    {/if}
                                                {else}
                                                    {if $student.status eq "Active"}
                                                    <font color="#009966">Active</font>
                                                     {else}
                                                    <font color=red>Inactive</font>
                                                    {/if}
                                                {/if}
                                                </div>
                                            </td>
                                            <td align="center">
                                                <div align="center">
						{$student.code}
                                                </div>
                                            </td>
                                            <td align="center" nowrap>
                                                <div align="center">
                                                     {if $student.status eq "Active"}
                                                    <a href="http://www.bssd.org/transfer_form.shtml" target=_blank>Deactivate</a>
                                                    {else}
                                                    <a href="http://www.bssd.org/enrollment_form.shtml" target=_blank>Enroll</a>
                                                     {/if}
                                                </div>
                                            </td>                                            
                                        </tr>
                                        {/foreach}
{* results --end*}
                                    </table>
                                    <table align="center" width="100%" border="0" cellspacing="0" cellpadding="0">
                                        <tr>
                                            <td valign="middle" nowrap>
                                                <div align="left">
                                                    <table>
                                                        <tr>
                                                            <td>
                                                                &nbsp;<a href="javascript: ;" onclick="setCheckboxes('fieldsForm', true); return false;" class="action">Check All</a>&nbsp;/&nbsp;<a href="javascript: ;" onclick="setCheckboxes('fieldsForm', false); return false;" class="action">UnCheck All</a>
                                                                <i> &nbsp;&nbsp; with selected &nbsp;&nbsp;</i>
                                                            </td>
                                                            <td>
                                                                <input type=submit name=Go value=Go onClick='javascript: return checkChecks();'>
                                                            </td>
                                                            <td>
                                                                <select name=cmd2>
                                                                    <option value=Export>Export</option>
                                                                    <option value=Group>Group</option>
                                                                     {html_options options=$showExportOptions}
                                                                </select>
                                                            </td>
                                                            <td>
                                                                Start Date
                                                                <input type=text name=startdate size=10 value={$qstart}>
                                                            </td>
                                                            <td>
                                                                End Date
                                                                <input type=text name=enddate  size=10 value={$qend}>
                                                            </td>
                                                        </tr>
                                                    </table>
                                                </div>

                                            </td>
                                            <td align="right"></td>
                                        </tr>
                                    </table>
                                    <input type="hidden" name="back_url" value="">
                                </td>
                            </tr>
                        </table>
                    </div>
                </td>
            </tr>
        </table>
    </form>

    <div align=left>
        <table width = 100% border=0 cellpadding = 0 cellspacing = 0 valign=bottom>
            <tr><td colspan=2></td></tr><tr><td>
                    <form method="POST" action="index.php?cmd=searchResults" name='displaylimit'>
                        <input type=hidden name=start value=1 />
                        <input type=hidden name=continue value=yes />
                        <input type=hidden name=sql value="{$urlSQL}" />
                        <input type=hidden name=total value={$total} />
                        <input type=text size=3 name=limit value={$limit} style="width:30px" />
                        <input type=submit name=submit value="Display Results" />
                    </form>
                </td> 
                <td>Name:</td>
                <td>
                    <form action=index.php?cmd=saveSearchGroup method=post>
                        <input type=text name=name size=10>
                        <select name=type><option value=self>Self</option></select>
                        <input type=hidden name=sql value="{$urlSQL}">
                        <input type=submit name=button value='Save Smart Group'>
                    </form>
                </td>
                <td align=right>
                    <table border=0>
                        <tr>
                            <td>DART Search Results: (</td><td>
                                <form method="POST" action="index.php?cmd=searchResults" name='prevForm'>
                                    <input type=hidden name=start value={$prevstart}>
                                    <input type=hidden name=continue value=yes>
                                    <input type=hidden name=sql value="{$urlSQL}">
                                    <input type=hidden name=total value={$total}>
                                    <input type=hidden name=limit value={$limit}>
                                    <a href="javascript:prevSubmit()">Prev</a>
                                </form>
                            </td>
                            <td>
                                <form method="POST" action="index.php?cmd=searchResults" name='nextForm'>
                                    <input type=hidden name=start value={$nextstart}>
                                    <input type=hidden name=continue value=yes>
                                    <input type=hidden name=sql value="{$urlSQL}">
                                    <input type=hidden name=total value={$total}>
                                    <input type=hidden name=limit value={$limit}>
                                    <a href="javascript:nextSubmit()">Next</a>
                                </form>
                            </td>
                            <td>
                                {$start} to {$end} from {$total})
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
        </table>
    </div>
    <br>
</div>


{/block}