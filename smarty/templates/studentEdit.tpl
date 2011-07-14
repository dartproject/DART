a{*
*  Copyright (C) 2011 Bolek Kurowski (bkurowsk@andrew.cmu.edu)
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
{block name="title"}Edit Student Information{/block}

{block name=css}
{/block}

{block name="js"}
<script type="text/javascript" src="js/studentEdit.js"></script>
<script type="text/javascript" src="js/jquery/jquery.simplemodal.1.4.1.min.js"></script>
{/block}

{block name="body"}
<div style="margin:0 auto; width:900px;">
    <form name=toggle method=post action=index.php?cmd=saveAdvEditStudentInfo>
        <input type=hidden name=id value={$student.studentid}>
        <input type=hidden name=loc>
        <table border="0" cellpadding="0" cellspacing="2" width="100%">
            <tr>
                <td>
                    <div align="left">
                        <br />
                        <font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                        Add/Edit Student </font><font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- {$student.fname|cat:' '|cat:$student.lname} 
                        </font>
                        <br />
                        <a id="page_help" href="#" onclick="" style="font-size: 8pt; color: #006FEB">
                            <img alt="help" src="{$imageURL}icons/help_16.png" style="vertical-align: middle"/> About this page
                        </a>
                    </div>

                    <blockquote>

                        <div id="page_modal_help" style="display:none">
                            <font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">This screen adds a new student to DART.  You begin here for students who have not ever been in DART before.  If you are looking for a former BSSD student, always 
                            <a title="Search DART" href="index.php?cmd=search"><b>search</b></a> for them first in our database.<i> </i>If a student exists in the system, just activate them, and assign them to the correct school. Field names in red are required, and those in black are optional.</font>
                        </div>

                    </blockquote>
                </td>
            </tr>
            <tr>

                <td>
                    <div align="center">
                        <table border="0" cellpadding="2" cellspacing="2" >
                            <tbody>
                                <tr>
                                    <td colspan="6" bgcolor="#ccffff">
                                        <div align="right">
                                            <b><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Account Basics</font></b></div>

                                    </td>
                                </tr>
                                <tr>
                                    <td colspan="6" valign="bottom"><div class="notewarning"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i><b>Note:</b>  Student names in DART must match either birth certificate, or legal document showing change of name. Unofficial adoption, divorce, or temporary guardianship arrangements do not change the legal name of a student. Do <u>not</u> use nicknames.</i></font></div></td>
                                </tr>
                                <tr>

                                    <td valign="bottom" nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Last Name:</b></font></td>
                                    <td valign="bottom" width="182">
                                        <input type=hidden name=new_lname value=empty><input type=hidden name=old_lname value='{$student.lname}'>
                                        <input type=text name=lname value='{$student.lname}' onChange='changeValue("lname", this.value)' size=20>
                                    </td>
                                    <td colspan="4">
                                        <div align="left">
                                        </div>
                                        {if $student.status eq "Active"}
                                            <font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                            <b>Student Active: </b>
                                            </font>
                                            <a href='' onClick='popUp("./index.php?cmd=StudentExit&id={$student.studentid}", 800, 600);return(false);'>
                                                Make Inactive
                                            </a>
                                        {else}
                                            <font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                            <b>Student Inactive: </b>
                                            </font>
                                            <a href="" onClick="popUp('./index.php?cmd=StudentEnter&id={$student.studentid}', 800, 600);return(false);">
                                                Make Active</a>
                                            {/if}
					 | <a href='' onClick='popUp("./index.php?cmd=StudentShowDates&id={$student.studentid}", 400, 400);return(false);' >Show Dates</a>
                                    </td>
                                </tr>
                                <tr>

                                    <td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>First Name:</b></font></td>
                                    <td width="182">
                                        <input type=hidden name=new_fname value=empty /><input type=hidden name=old_fname value='{$student.fname}' />
                                        <input type=text name=fname value='{$student.fname}' onChange='changeValue("fname", this.value)' size=20 />

                                    </td>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Middle Name:</b></font></td>
                                    <td nowrap width="15%">
                                        <input type=hidden name=new_mname value=empty><input type=hidden name=old_mname value='{$student.mname}'>
                                        <input type=text name=mname value='{$student.mname}' onChange='changeValue("mname", this.value)' size=20>
                                    </td>
                                    <td nowrap width="45"></td>
                                    <td nowrap width="15%"></td>
                                </tr>
                                <tr>
                                    <td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Mailing Address:</b></font></td>
                                    <td width="182">
                                        <input type=hidden name=new_maddr value=empty><input type=hidden name=old_maddr value='{$student.maddr}'>
                                        <input type=text name=mmadr value='{$student.maddr}' onChange='changeValue("maddr", this.value)' size=20>
                                    </td>
                                    <td width="15%"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Physical Address:</b></font></td>
                                    <td width="15%">
                                        <input type=hidden name=new_addr value=empty><input type=hidden name=old_addr value='{$student.addr}'>
                                        <input type=text name=addr value='{$student.addr}' onChange='changeValue("addr", this.value)' size=20>                                    
                                    </td>
                                    <td colspan="2" nowrap bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Different</i></font></td>
                                </tr>
                                <tr>

                                    <td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Village / Town:</b></font></td>
                                    <td width="182">
                                        <input type=hidden name=new_village value=empty><input type=hidden name=old_village value='{$student.village}'>
                                        <input type=text name=village value='{$student.village}' onChange='changeValue("village", this.value)' size=20>
                                    </td>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Zip Code:</b></font></td>
                                    <td width="15%">
                                        <input type=hidden name=new_zip value=empty><input type=hidden name=old_zip value='{$student.zip}'>
                                        <input type=text name=zip value='{$student.zip}' onChange='changeValue("zip", this.value)' size=20>

                                    </td>
                                    <td nowrap width="45"></td>
                                    <td nowrap width="15%"></td>
                                </tr>
                                <tr>

                                    <td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Email Address:</b></font></td>
                                    <td width="250">
                                        <input type=hidden name=new_email value=empty><input type=hidden name=old_email value='{$student.email}'>
                                        <input type=text name=email value='{$student.email}' onChange='changeValue("email", this.value)' size=20>

                                        <font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== Only District</i></font></td>

                                    <td nowrap width="45"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Phone:</b></font></td>
                                    <td nowrap width="15%">
                                        <input type=hidden name=new_phone value=empty><input type=hidden name=old_phone value='{$student.phone}'>
                                        <input type=text name=phone value='{$student.phone}' onChange='changeValue("phone", this.value)' size=20>

                                    </td>
                                </tr>

                                <tr>
                                    <td nowrap="nowrap" width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Username:</b></font></td>
                                    <td>
                                        <input type=hidden name=new_user value=empty><input type=hidden name=old_user value='{$student.user}'>
                                        <input type=text name=user value='{$student.user}' onChange='changeValue("user", this.value)' size=20>           
                                    </td>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Password:</b></font></td>
                                    <td width="15%">
                                        ***********
                                    </td>
                                    <td nowrap width="45"></td>
                                    <td nowrap width="15%"></td>
                                </tr>

                                <tr>
                                    <td colspan="6" nowrap="nowrap" bgcolor="#ccffff">
                                        <div align="right">
                                            <b><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Student Data Required</font></b></div>
                                    </td>
                                </tr>
                                <tr>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>BSSD School Site:</b></font></td>
                                    <td width="182">
                                        {$student.site}
                                    </td>
                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Status:</b></font></td>
                                    <td width="15%">
                                        <input type=hidden name=new_status value=empty><input type=hidden name=old_status value='{$student.status}'>
                                        <select name=status onChange='changeValue("status", this.value)' >
                                            {html_options options=$statusOptions selected=$student.status}
                                        </select>
                                    </td>
                                </tr>
                                <tr>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Date of Birth:</b></font></td>
                                    <td nowrap width="182">
                                        <input type=hidden name=new_bday value=empty><input type=hidden name=old_bday value='{$student.bday}'>
                                        <input type=text name=bday value='{$student.bday}' onChange='changeValue("bday", this.value)' size=20>  

                                        <font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">YYYY-MM-DD</font></td>

                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Gender:</b></font></td>
                                    <td width="15%">
                                        <div align="left">
                                            <input type=hidden name=new_gender value=empty><input type=hidden name=old_gender value='{$student.gender}'>
                                            <select name=gender onChange='changeValue("gender", this.value)' >
                                                {html_options options=$genderOptions selected=$student.gender}
                                            </select>
                                        </div>
                                    </td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Alaska Student ID:</b></font></td>
                                    <td width="182">
                                        <input type=hidden name=new_alaskaid value=empty><input type=hidden name=old_alaskaid value='{$student.alaskaid}'>
                                        <input type=text name=alaskaid value='{$student.alaskaid}' onChange='changeValue("alaskaid", this.value)' size=20> 
                                    </td>

                                    <td nowrap width="15%">
                                        <div align="left">
                                            <font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>PowerSchool ID:</b></font></div>
                                    </td>
                                    <td width="15%">
                                        <input type=hidden name=new_psid value=empty><input type=hidden name=old_psid value='{$student.psid}'>
                                        <input type=text name=psid value='{$student.psid}' onChange='changeValue("psid", this.value)' size=20> 
                                    </td>
                                    <td colspan="2" bgcolor="#ffcccc">
                                        <div align="left">
                                            <font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Applicable</i></font></div>
                                    </td>
                                </tr>
                                <tr>
                                    <td nowrap width="15%">
                                        <font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                        <b>Testing Level:</b>
                                        </font>
                                    </td>
                                    <td width="182">
                                        <input type=hidden name=new_grade value=empty><input type=hidden name=old_grade value='{$student.grade}'>
                                        <select name=grade onChange='changeValue("grade", this.value)' >
                                            {html_options options=$testinglevelOptions selected=$student.grade}
                                        </select>
                                    </td>
                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Special Education?:</b></font></td>
                                    <td width="15%">
                                        {$student.sped}
                                    </td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Ethnicity:</b></font></td>
                                    <td width="182">
                                        <input type=hidden name=new_ethnicity value=empty><input type=hidden name=old_ethnicity value='{$student.ethnicity}'>
                                        <select name=ethnicity onChange='changeValue("ethnicity", this.value)' >
                                            {html_options options=$ethnicityOptions selected=$student.ethnicity}
                                        </select>
                                    </td>
                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"></font></td>
                                    <td width="15%">
                                        &nbsp;
                                    </td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td colspan="6" bgcolor="#ccffff">
                                        <div align="right">

                                            <b><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Guardian &amp; Family Information</font></b></div>
                                    </td>
                                </tr>
                                <tr>
                                    <td nowrap width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Siblings at School?</b></font></td>
                                    <td valign="top" width="182">
                                        <input type=hidden name=new_siblings value=empty><input type=hidden name=old_siblings value='{$student.siblings}'>
                                        <select name=siblings onChange='changeValue("siblings", this.value)' >
                                            {html_options options=$siblingOptions selected=$student.siblings}
                                        </select>
                                    </td>

                                    <td colspan="4" bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== Number of other students <u>in this school</u> this student lives with</i></font></td>
                                </tr>
                                <tr>
                                    <td width="15%"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Names of Others:</b></font></td>
                                    <td colspan="3" valign="top">
                                        <input type=hidden name=new_siblingsnames value=empty><input type=hidden name=old_siblingsnames value='{$student.siblingsnames}'>
                                        <input type=text name=siblingsnames value='{$student.siblingsnames}' onChange='changeValue("siblingsnames", this.value)' size=75>

                                    </td>
                                    <td colspan="2" bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Applicable</i></font></td>

                                </tr>
                                <tr>
                                    <td colspan="6">
                                        <div class="notewarning">
                                            <i><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                                <b>Note: </b>The full names of the parent(s) or guardian(s) must be recorded for each
                                                student, unless student is over 18 years old. If the student is living with a relative
                                                or in another home, the names and addresses of the responsible adult with whom the student
                                                is living must be recorded here.
                                                </font>
                                            </i>
                                        </div>
                                    </td>
                                </tr>
                                <tr>
                                    <td nowrap width="15%">
                                        <font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                        <b>Parent or Guardian:</b>
                                        </font>
                                    </td>
                                    <td valign="top" width="182">
                                        <input type=hidden name=new_parent value=empty><input type=hidden name=old_parent value='{$student.parent}'>
                                        <input type=text name=parent value='{$student.parent}' onChange='changeValue("parent", this.value)' size=20>                                     
                                    </td>

                                    <td nowrap>
                                        <div align="left">
                                            <font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Resides With Student:</b></font></div>
                                    </td>
                                    <td valign="top">
                                        <input type=hidden name=new_parentwstudent value=empty><input type=hidden name=old_parentwstudent value='{$student.parentwstudent}'>
                                        <select name=siblings onChange='changeValue("siblings", this.value)' >
                                            {html_options options=$parentwstudentOptions selected=$student.parentwstudent}
                                        </select>
                                    </td>
                                    <td width="45"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Phone:</b></font></td>
                                    <td width="15%">
                                        <input type=hidden name=new_parentphone value=empty><input type=hidden name=old_parentphone value='{$student.parentphone}'>
                                        <input type=text name=parentphone value='{$student.parentphone}' onChange='changeValue("parentphone", this.value)' size=20> 
                                    </td>
                                </tr>
                                <tr>
                                    <td width="15%">
                                        <div align="left">

                                            <font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Mailing Address:</b></font></div>
                                    </td>
                                    <td valign="top" width="182">
                                        <input type=hidden name=new_parentmaddr value=empty><input type=hidden name=old_parentmaddr value='{$student.parentmaddr}'>
                                        <input type=text name=parentmaddr value='{$student.parentmaddr}' onChange='changeValue("parentmaddr", this.value)' size=20> 
                                    </td>
                                    <td><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Physical Address:</b></font></td>
                                    <td>
                                        <input type=hidden name=new_parentaddr value=empty><input type=hidden name=old_parentaddr value='{$student.parentaddr}'>
                                        <input type=text name=parentaddr value='{$student.parentaddr}' onChange='changeValue("parentaddr", this.value)' size=20> 
                                    </td>
                                    <td colspan="2" bgcolor="#ffcccc"><font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><i>&lt;== If Different</i></font></td>
                                </tr>

                                <tr>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Village / Town:</b></font></td>
                                    <td valign="top" width="182">
                                        <input type=hidden name=new_parentvillage value=empty><input type=hidden name=old_parentvillage value='{$student.parentvillage}'>
                                        <input type=text name=parentvillage value='{$student.parentvillage}' onChange='changeValue("parentvillage", this.value)' size=20>
                                    </td>
                                    <td><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Zip Code:</b></font></td>
                                    <td valign="top">
                                        <input type=hidden name=new_parentzip value=empty><input type=hidden name=old_v value='{$student.parentzip}'>
                                        <input type=text name=parentzip value='{$student.parentzip}' onChange='changeValue("parentzip", this.value)' size=20>
                                    </td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>

                                <tr>
                                    <td width="15%"><font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular"><b>Comments / Notes:</b></font></td>
                                    <td rowspan="4" colspan="3" valign="top">
                                        <input type=hidden name=new_snotes value=empty><input type=hidden name=old_snotes value=$student.snotes>
                                        <textarea name=snotes onChange='changeValue("snotes", this.value)' rows=6 cols=75 >{$student.snotes}</textarea>

                                    </td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td width="15%">

                                        <div align="center">
                                        </div>
                                    </td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td width="15%"></td>
                                    <td width="45"></td>

                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td width="15%"></td>
                                    <td width="45"></td>
                                    <td width="15%"></td>
                                </tr>
                                <tr>
                                    <td colspan="5">
                                        <div align="center">
                                            <br>
                                            <input name="cmdSearch" value="Save &amp; Exit" type="submit" style="width:240px; height:50px">
                                            <input name="cmdSearch" value="Cancel" type="submit" style="width:120px; height:40px"></div>
                                    </td> 
                                </tr>
                            </tbody>
                        </table>
                    </div>
                </td>
            </tr>
        </table>
    </form>

    {if $showStudentLevelInfo}
        <hr>
        <form><input type=button value="Add All Levels" onClick="window.location='index.php?cmd=handleLevel&id={$student.studentid}&type=addall';"></form>
        <table border=1><tr>
                <td>Click To Add Subject</td>
                {foreach $subjects as $subject}
                    <td>
                        <a href=index.php?cmd=handleLevel&id={$student.studentid}&sub={$subject.id}&type=add>&nbsp; {$subject.id} &nbsp;</a>
                    </td>
                {/foreach}
            </tr>
        </table>
        <br>
        <form name="toggle" method="POST" action="index.php?cmd=saveLevels">
            <input type=hidden name=id value={$student.studentid}>
            <input type=hidden name=loc>
            Edit or Remove Levels
            <table border=1>
                {assign var=i value=1}
                <tr>
                    {foreach $studentLevels as $studentLevel}
                        {$name=$studentLevel.subject|cat:'_'|cat:$studentLevel.level}
                        <td>
                            <table>
                                <tr>
                                    <th>
                                        <a href=index.php?cmd=handleLevel&id={$student.studentid}&sub={$studentLevel.subject}&lvl={$studentLevel.level}&type=delete 
                                           onClick='javascript:return confirm_delete("You are about to delete the level. Click OK to continue")'>
                                            <img alt="delete" src="{$imageURL}icons/delete_16.png" style="vertical-align: middle" title="Remove level"/></a>
                                        {$studentLevel.subject} ({$studentLevel.level})
                                    </th>
                                </tr>
                                <tr>
                                    <td style="text-align: center">
                                        <input type=hidden name=new_{$name} value=empty>
                                        <select name="{$name}" onChange='changeValue("{$name}", this.value)' style="width:50px" >
                                            <option value=""></option>
                                            {html_options options=$studentLevel.subOptions selected= $studentLevel.level}
                                        </select>&nbsp;
                                    </td>
                                </tr>
                            </table>
                        </td>
                        {if $i % 10 == 0 && $i>0} 
                        </tr>
                    {/if}
                    {assign var=i value=$i+1}
                {/foreach}
                {if $i % 10 <> 0}
                    </tr>
                {/if}
            </table>
            <br>
            <input type=submit name=submit value='Save Level Information'>
        </form>

    {/if}

</div>

{/block}