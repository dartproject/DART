{*
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
{block name="title"}User Management{/block}

{block name=css}
{/block}

{block name="js"}
<script type="text/javascript" src="js/studentInfo.js"></script>
{/block}

{block name="body"}
<table width="100%" border="0" cellspacing="2" cellpadding="0">
    <tr>
        <td bgcolor="white">
            <div align="left">
                <br>
                <div align="left">
                    <a name='toppage'></a>
                    <font size="4" color="#cc0000">
                        Individual Student Profile - Active Account
                    </font><br>
                    <br>

                    {include file="comp/studentInfo.pulldown.tpl"}

                </div>
                <div class="noteimportant">
                    This is the page that School Admins or District Admins would use to modify
                    this user's account information, or to make level individual level changes.
                    Multiple user level changes need to be handled through a different screen.
                    Note that most of the fields below &quot;Account Information&quot; can't be
                    directly modified by School Level Administrators. Only District Office users
                    should be able to enter that data, and some of is auto-calculated from other
                    screens. School Level Administrators can view this data, however.  										</div>
                <table width="75%" border="0" cellspacing="2" cellpadding="0">
                    <tr>
                        <td width="25%">
                            <div align="center">
                                <img src="{$student.schoolLogoURL}" alt="" border="0">
                            </div>
                        </td>
                        <td nowrap width="50%">
                            <div align="center">
                                <font size="4">{$student.name} School: {$student.fname|cat:' '|cat:$student.lname}<br>
                                    <br>
                                </font>
                                <!--                                <b><font size="2">Last Access: </font></b>
                                                                <font size="2">05/21/2006 at 3:21 p.m.</font>-->
                                <br>
                                <font size="2">
                                    <a href="index.php?cmd=history&student={$student.studentid}">Account History</a>
                                </font>
                            </div>
                        </td>
                        <td nowrap width="25%">
                            <div align="center">
                                <img src="{$student.profilePic}" alt="{$student.lname}, {$student.fname} - SKK" height="105" width="95" border="0" />
                                <br>
                                <form enctype="multipart/form-data" name=upload method=post action=index.php?cmd=upload>
                                    <input type=hidden name=id value={$student.studentid} />
                                    <input size=10 type="file" name="pict_file" class="textfield" />
                                    <input type=submit name=activity value=Upload />
                                    <input type=submit name=activity value=Delete />
                                </form>
                            </div>
                        </td>
                    </tr>
                </table>
                <br>
                <a name='account'></a>
                <font size="4">{$student.fname|cat:' '|cat:$student.lname} - Account Information </font>
                <br>

                {include file="comp/studentInfo.pulldown.tpl"}

                <br>
                <table width="100%" border="0" cellspacing="2" cellpadding="0">
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>First Name: </b></font></td>
                        <td width="35%"><font size="2">{$student.fname}</font></td>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Student ID: </b></font></td>
                        <td width="35%">{$student.studentid}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%">
                            <font size="2"><b>Middle Name: </b></font>
                        </td>
                        <td width="35%">{$student.mname}</td>
                        <td nowrap bgcolor="#ccccff" width="15%">
                            <font size="2"><b>
                                    <a href="javascript:editValue('Username:','user','{$student.user}');">Username: </a>
                                </b></font>
                        </td>
                        <td width="35%">{$student.user}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Last Name: </b></font></td>
                        <td width="35%">{$student.lname}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Password: </b></font></td>
                        <td width="35%">{$student.pwd}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">Mailing Address:</font></b></td>
                        <td width="35%">{$student.addr}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Alaska Student ID:</b></font></td>
                        <td width="35%">{$student.alaskaid}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">Village:</font></b></td>
                        <td width="35%">{$student.village}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>PowerSchool ID:</b></font></td>
                        <td width="35%">{$student.psid}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">State: </font></b></td>
                        <td width="35%">{$student.state}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Testing Grade Level: </b></font></td>
                        <td width="35%">{$student.grade}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">Zip Code: </font></b></td>
                        <td width="35%">{$student.zip}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">Birthdate:</font></b></td>
                        <td width="35%">{$student.bday}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">Phone: </font></b></td>
                        <td width="35%">{$student.phone}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">Chronological Age: </font></b></td>
                        <td width="35%">{$student.bday|age}</td>
                    </tr>
                    <tr>
                        <td nowrap bgcolor="#ccccff" width="15%"><b><font size="2">
                                    <a href="javascript:editValue('Email_Address:','email','{$student.email}');">email: </a>
                                </font></b>
                        </td>
                        <td width="35%">{$student.email}</td>
                        <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Latest Enrollment: </b></font></td>
                        <td width="35%">{$student.latestenroll}</td>
                    </tr>
                </table>
                <div align="left">
                    <br>
                    <a name='demo'></a><font size="4">{$student.fname|cat:' '|cat:$student.lname} - Demographics </font><font size="4"></font><br>
                    {include file="comp/studentInfo.pulldown.tpl"}
                    <br>
                    <table width="100%" border="0" cellspacing="2" cellpadding="0">
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Gender: </b></font></td>
                            <td width="35%"><font size="2">{$student.gender}</font></td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Ethnicity: </b></font></td>
                            <td width="35%">{$student.ethnicity}</td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%">
                                <font size="2"><b>
                                        <a href="javascript:editValue('NSLP_Eligible:','NSLP_Eligible','{$student.NSLPEligible}');">NSLPEligible: </a>
                                    </b></font>
                            </td>
                            <td width="35%">{$student.NSLPEligible}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Migrant:','migrant','{$student.migrant}');">Migrant: </a>
                                    </b></font></td>
                            <td width="35%">{$student.migrant}</td>
                        </tr>
                    </table>
                    <br>
                    <a name='profile'></a><font size="4">{$student.fname|cat:' '|cat:$student.lname} - Learning Profile </font><br>
			{include file="comp/studentInfo.pulldown.tpl"}
                    <br>
                    <br>
                    <table width="100%" border="0" cellspacing="2" cellpadding="0">
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Attendance Y1: </b></font></td>
                            <td width="35%">{$student.attendance}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Last Updated: </b></font></td>
                            <td width="35%">{$student.lastUpdate}</td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>Suspensions Y1:</b></font></td>
                            <td width="35%">{$student.suspensions}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Activities_Eligible:','eligibility','{$student.eligibility}');">Activities Eligible: </a>
                                    </b></font>
                            </td>
                            <td width="35%">{$student.eligibility}</td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('LEP:','LEP','{$student.LEP}');">LEP: </a>
                                    </b></font>
                            </td>
                            <td width="35%"><font size="2">{$student.LEP}</font></td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('LEP_Status:','LEPStatus','{$student.LEPStatus}');">LEP Status: </a>
                                    </b></font></td>
                            <td width="35%">{$student.LEPStatus}</td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Indian_Education:','nativeEd','{$student.nativeEd}');">Indian Education: </a>
                                    </b></font></td>
                            <td width="35%">{$student.nativeEd}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Title_I:','titleI','{$student.titleI}');">Title I: </a>
                                    </b></font></td>
                            <td width="35%">{$student.titleI}</td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Section_504:','sec504','{$student.sec504}');">Section 504: </a>
                                    </b></font></td>
                            <td width="35%">{$student.sec504}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('SpEd_IEP:','Sp_ED_IEP','{$student.SpED_IEP}');">SpED_IEP: </a>
                                    </b></font></td>
                            <td width="35%">{$student.SpED_IEP}</td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Related_Services:','relatedServices','{$student.relatedServices}');">Related Services: </a>
                                    </b></font>
                            </td>
                            <td width="35%">{$student.relatedServices}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>State &amp; District Testing: </b></font></td>
                            <td width="35%"><select name="selectName" size="1">
                                    <option value="one">No Testing Accommodations</option>
                                    <option value="two">Accommodations</option>
                                    <option value="three">Modified HSGQE / EOLs</option>
                                    <option value="four">Alternate Assessment</option>
                                    <option value="five">No Statewide / District Testing</option>
                                </select></td>
                        </tr>
                        <tr>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('Behavior_Plan:','behaviorPlan','{$student.behaviorPlan}');">Behavior Plan: </a>
                                    </b></font>
                            </td>
                            <td width="35%">{$student.behaviorPlan}</td>
                            <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                        <a href="javascript:editValue('G/T_Plan:','GTPlan','{$student.GTPlan}');">G/T Plan: </a>
                                    </b></font>
                            </td>
                            <td width="35%">{$student.GTPlan}</td>
                        </tr>
                    </table>
                    <br>
                    <a name='levels'></a><font size="4">{$student.fname|cat:' '|cat:$student.lname} - Levels Information<br>
                    </font>
                    {include file="comp/studentInfo.pulldown.tpl"}
                    <br>
                    <br>
                </div>
		{************ Score Table *************************************}
                <table width="100%" border="1">
                    <tbody>
                        <tr>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <font size="2"><b>Content Area</b></font></div>
                            </td>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <font size="2"><b>Level</b></font></div>
                            </td>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <font size="2"><b>Overall</b></font></div>
                            </td>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <font size="2"><b>QPI</b></font></div>
                            </td>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <font size="2"><b>Entered</b></font></div>
                            </td>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <b>TIL</b></div>
                            </td>
                            <td nowrap bgcolor="#ccccff">
                                <div align="center">
                                    <font size="2"><b>Status</b></font></div>
                            </td>
                        </tr>
                        {foreach $student.studentScores as $studentScore}
                        <tr>
                            <td nowrap><font size="2">{$studentScore.sname}</font></td>
                            <td nowrap>
                                <div align="center">
                                    <font size="2">{$studentScore.subject} {$studentScore.level}</font></div>
                            </td>
                            <td nowrap>
                                <div align="center">
                                    {$studentScore.score}
                                </div>
                            </td>
                            <td nowrap>
                                <div align="center">
                                    <font size="2">{$studentScore.qpi} </font>
                                </div>
                            </td>
                            <td nowrap>
                                <div align="center">
                                    {$studentScore.entered}
                                </div>
                            </td>
                            <td nowrap>
                                <div align="center">
                                    {$studentScore.til}
                                </div>
                            </td>
                            <td nowrap>
                                <div align="center">

                                    <form action="#" method="post" name="cs_form_name_5">
                                        <select name="cs_popup_name_5" onchange="CSURLPopupShow(/*CMP*/'cs_form_name_5', /*CMP*/'cs_popup_name_5', '_top');">
                                            <option value="#" selected>Active</option>
                                            <option value="http://www.adobe.com">Exit - Next Level</option>
                                            <option value="http://www.adobe.com">Exit - Adjustment</option>
                                        </select>
                                    </form>

                                </div>
                            </td>
                        </tr>

                        {/foreach}

                    </tbody>
                </table>



            </div>
        </td>
    </tr>
    <tr>
        <td bgcolor="white">
        </td>
    </tr>
    <tr>
        <td bgcolor="white">
            <div align="center">
                <table width="100%" border="0" cellspacing="2" cellpadding="0">
                    <tr>
                        <td colspan="3"><br>
                            <a name="testing"></a><font size="4">{$student.fname|cat:' '|cat:$student.lname} - Testing Summary - </font><font size="2"><a href="(EmptyReference!)">Detailed Testing Data</a></font><font size="4"> </font><br>
														$pulldown
                            <br>
                            <br>
                            <table width="100%" border="0" cellspacing="2" cellpadding="0">
                                <tr>
                                    <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b
                                                <a href="javascript:editValue('HSGQE_Reading:','HSGQEReading','{$student.HSGQEReading}');">HSGQE Reading: </a>
                                            </b></font></td>
                                    <td width="35%">{$student.HSGQEReading}</td>
                                    <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                                <a href="javascript:editValue('Latest_SRI:','SRI','{$student.SRI}');">SRI: </a>
                                            </b></font></td>
                                    <td width="35%">{$student.SRI}</td>
                                </tr>
                                <tr>
                                    <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                                <a href="javascript:editValue('HSGQE_Writing:','HSGQEWriting','{$student.HSGQEWriting}');">HSGQE Writing: </a>
                                            </b></font></td>
                                    <td width="35%">{$student.HSGQEWriting}</td>
                                    <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                                <a href="javascript:editValue('STAR_Math:','STAR','{$student.STAR}');">STAR Math: </a>
                                            </b></font></td>
                                    <td width="35%">{$student.STAR}</td>
                                </tr>
                                <tr>
                                    <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                                <a href="javascript:editValue('HSGQE_Math:','HSGQEMath','{$student.HSGQEMath}');">HSGQE Math: </a>
                                            </b></font></td>
                                    <td width="35%"><font size="2">{$student.HSGQEMath}</font></td>
                                    <td nowrap bgcolor="#ccccff" width="15%"><font size="2"><b>
                                                <a href="javascript:editValue('SAT_ACT_ASVAB:','scores','{$student.scores}');">SAT_ACT_ASVAB: </a>
                                            </b></font></td>
                                    <td width="35%">{$student.scores}</td>
                                </tr>
                            </table>
                            <br>
                            <br>
                        </td>
                    </tr>
                </table>
            </div>
        </td>
    </tr>
</table>
{/block}