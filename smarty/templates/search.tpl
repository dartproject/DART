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
{block name="title"}{/block}

{block name="css"}
<link rel="stylesheet" href="js/jquery/jquery.multiselect.css" type="text/css" media="screen" >
<link rel="stylesheet" type="text/css" href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/themes/ui-lightness/jquery-ui.css">
{/block}

{block name="js"}

<script language="JavaScript" type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.13/jquery-ui.min.js"></script>
<script language="JavaScript" type="text/javascript" src="js/jquery/jquery.multiselect.min.js"></script>
<script language="JavaScript" type="text/javascript" src="js/search.js"></script>
{/block}

{block name="body"}
<style type="text/css">
    select.singleSelect {
        width:155px;
    }

    input.text {
        width:155px;
    }

</style>

<div align="center">
    <div align="left">
        <font size="4" color="#cc0000">DART System Search</font><br>
    </div>
    <form method="POST" action="index.php?cmd=searchResults" name='search'>
        <table width="100%" border="0" cellspacing="2" cellpadding="0" >
            {*<tr>
                <td>
                    <div align="left">
                        <br>
                        
                        <div class="noteimportant">Looking for someone? This is the area you use to find him or her. After entering information in any of the spaces below, press "Search" to look at all current and historical records that you have access to in the DART system, form new groups based on these criteria, or proceed to an export area for data exporting.  </div>
                    </div>
                </td>
            </tr>*}
            <tr>
                <td>
                    <div style="text-align: center">
                        <input type="submit" name="cmdSearch" value="Search" style="width:300px">
                    </div>
                </td>
            </tr>
            <tr>
                <td>
                    <div align="left">
                        {*<br>
                        <font size="4" color="#cc0000">Looking for Someone? </font><br>
                        <br>*}

                        <table width="100%" border="0" cellspacing="2" cellpadding="0">
                            {*<tr>
                                <td colspan="6">
                                    <div align="center">
                                        <font face="Arial,Helvetica" color="#000000"><b>* Specify your record search criteria below, and click the "Search" button to see the results.<br>
                                                <br>

																* The more criteria you enter, the narrower your search results will be..so use caution!<br>
                                                <br>
                                            </b>
                                        </font>
                                    </div>
                                </td>
                            </tr>*}
                            <tr>
                                <td colspan="6" bgcolor="#ccffff">
                                    <div align="right" style="float:right;">
                                        <b>Specify User Variables</b>
                                    </div>
                                </td>
                            </tr>
                            <tr>
                                <td nowrap width="15%">
                                    <font size="2"><b>Time Frame:</b></font>
                                </td>
                                <td width="12%">
                                    <select class="singleSelect" name="tframe" style="width:155px">
                                        <option value="#" selected>Current Quarter</option>
                                        <option value="all">All Time Frames</option>
                                    </select>
                                </td>
                                <td width="15%"><font size="2"><b>Status:</b></font></td>
                                <td width="15%">
                                    <select class="singleSelect" name="status" style="width:155px">
                                        <option value="Active" selected>Active</option>
                                        <option value="Inactive">Inactive</option>
                                        <option value="">Both</option>
                                    </select>
                                </td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%">
                                    <font size="2" color="#cc0000"><b>Last Name:</b></font>
                                </td>
                                <td width="12%">
                                    <input type="text" name="lname" class="text">
                                </td>
                                <td colspan="3">Students who are currently in school are "Active". All others are considered "Inactive".  </td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%"><font size="2"><b>First Name:</b></font></td>
                                <td width="12%"><input type="text" name="fname"  class="text"></td>
                                <td width="15%"><font size="2" color="#cc0000"><b>Gender:</b></font></td>
                                <td width="15%">
                                    <select class="singleSelect" name="gender">
                                        <option value="" selected>Male or Female</option>
                                        <option value="Male">Male</option>
                                        <option value="Female">Female</option>
                                    </select>
                                </td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%"><font size="2" color="#cc0000"><b>Student Number:</b></font></td>
                                <td width="12%"><input type="text" name="studentnumber"  class="text"></td>
                                <td width="15%"><font size="2" color="#cc0000"><b>Suspensions:</b></font></td>
                                <td width="15%">
                                    <select name="suspension" class="singleSelect" >
                                        {html_options options=$suspensionList}
                                    </select>
                                </td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%"><font size="2" color="#cc0000"><b>AK Student ID:</b></font></td>
                                <td width="12%"><input type="text" name="aid" class="text"></td>
                                <td width="15%" valign = top rowspan = 4>
                                    <font size="2" color="#cc0000"><b>Testing Level:</b></font><br>
                                </td>
                                <td width="15%" valign = top rowspan = 4>
                                    <select class="multipleSelect" name="grade[]" multiple="multiple" size="5">
                                        <option value="" selected>All Testing Levels</option>
                                        <option value="PK">PK</option>
                                        <option value="K">K</option>
                                        <option value="1">1</option>
                                        <option value="2">2</option>
                                        <option value="3">3</option>
                                        <option value="4">4</option>
                                        <option value="5">5</option>
                                        <option value="6">6</option>
                                        <option value="7">7</option>
                                        <option value="8">8</option>
                                        <option value="9">9</option>
                                        <option value="10">10</option>
                                        <option value="11">11</option>
                                        <option value="12">12</option>
                                        <option value="13">13</option>
                                    </select>
                                </td>													<td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td nowrap width="15%"><font size="2" color="#cc0000"><b>PowerSchool ID:</b></font></td>
                                <td width="12%"><input type="text" name="psid" class="text"></td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%"><font size="2" color="#cc0000"><b>Age:</b></font></td>
                                <td width="12%">
                                    <select name="age" class="singleSelect">
                                        <option value="" selected>All Ages</option>
                                        <option value="18">18+</option>
                                        <option value="17">17</option>
                                        <option value="16">16</option>
                                        <option value="15">15</option>
                                        <option value="14">14</option>
                                        <option value="13">13</option>
                                        <option value="12">12</option>
                                        <option value="11">11</option>
                                        <option value="10">10</option>
                                        <option value="9">09</option>
                                        <option value="8">08</option>
                                        <option value="7">07</option>
                                        <option value="6">06</option>
                                        <option value="5">05</option>
                                        <option value="4">04</option>
                                        <option value="3">03</option>
                                    </select>
                                </td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%"><font size="2" color="#cc0000"><b>Attendance </b></font></td>
                                <td width="12%">
                                    <select name="attendance" class="singleSelect">
                                        <option value="" selected>All Rates</option>
                                        <option value="100">100%</option>
                                        <option value="95-99">95% - 99%</option>
                                        <option value="90-94">90% - 94%</option>
                                        <option value="85-89">85% - 89%</option>
                                        <option value="80-84">80%- 84%</option>
                                        <option value="other">Other</option>
                                    </select>
                                </td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td width="15%"><font size="2" color="#cc0000"><b>Eligibility:</b></font></td>
                                <td width="12%">
                                    <select name="Eligibility" class="singleSelect">
                                        <option value="" selected>Select Eligibility</option>
                                        <option value="Eligible">Eligible</option>
                                        <option value="Not Eligible - Academic">Not Eligible - Academic</option>
                                        <option value="Not Eligible - Attendance">Not Eligible - Attendance</option>
                                        <option value="Not Eligible - Behavior">Not Eligible - Behavior</option>
                                        <option value="Not Eligible - Transfer">Not Eligible - Transfer</option>
                                    </select>
                                    <br>
                                </td>
                                <td width="15%" valign = top><font size="2" color="#cc0000"><b>Special Ed Status:</b></font></td>

                                <td width="15%">
                                    <select name="sped" class="singleSelect">
                                        <option value="" selected>All</option>
                                        <option value="Y">Yes</option>
                                        <option value="N">No</option>
                                    </select>
                                </td><td>
                                    <font size="2" color="#cc0000" ><b>LEP Status</b></font>
                                </td><td>
                                    <select name="LEPstatus" class="singleSelect">
                                        <option value="" selected>All</option>
                                        <option value="Y">Yes</option>
                                        <option value="N">No</option>
                                    </select>

                                </td>
                            </tr>
                            <tr>
                                <td colspan="6" bgcolor="#ccffff">
                                    <div align="right">
                                        <b>Specify Learning Variables</b></div>
                                </td>
                            </tr>
                            <tr>
                                <td valign="top" width="15%"><font size="2" color="#cc0000"><b>Location:</b></font><font face="Arial,Helvetica" size="2" color="#000000"><strong><br>
                                        </strong></font>
                                </td>
                                <td valign="top" width="12%">
                                    <select name="locationids[]" multiple="multiple" class="multipleSelect">
                                        {html_options options=$sitelist}
                                    </select>
                                </td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                                <td width="15%"></td>
                            </tr>
                            <tr>
                                <td valign="top" width="15%">
                                    <font size="2" color="#cc0000"><b>Content Area:</b></font><br>
                                </td>
                                <td valign="top" width="12%"><select name="areas[]" multiple="multiple" class="multipleSelect">
                                        {html_options options=$coreSubjectList}
                                    </select></td>
                                <td valign="top" width="15%">
                                    <font size="2" color="#cc0000"><b>Level:</b></font><br>
                                </td>
                                <td valign="top" width="15%">
                                    <select name="level[]" multiple="multiple" class="multipleSelect">
                                        <option value="" selected >All Levels</option>
                                        <option value="0">0</option>
                                        <option value="1">1</option>
                                        <option value="2">2</option>
                                        <option value="3">3</option>
                                        <option value="3A">3A</option>
                                        <option value="3G">3G</option>
                                        <option value="3U">3U</option>
                                        <option value="4">4</option>
                                        <option value="4A">4A</option>
                                        <option value="4G">4G</option>
                                        <option value="4U">4U</option>
                                        <option value="5">5</option>
                                        <option value="5A">5A</option>
                                        <option value="5G">5G</option>
                                        <option value="5U">5U</option>
                                        <option value="5E">5E</option>
                                        <option value="5L">5L</option>
                                        <option value="5P">5P</option>
                                        <option value="6">6</option>
                                        <option value="6A">6A</option>
                                        <option value="6G">6G</option>
                                        <option value="6U">6U</option>
                                        <option value="6E">6E</option>
                                        <option value="6L">6L</option>
                                        <option value="6P">6P</option>
                                        <option value="7">7</option>
                                        <option value="7A">7A</option>
                                        <option value="7G">7G</option>
                                        <option value="7U">7U</option>
                                        <option value="7E">7E</option>
                                        <option value="7L">7L</option>
                                        <option value="7P">7P</option>
                                        <option value="8">8</option>
                                        <option value="8A">8A</option>
                                        <option value="8G">8G</option>
                                        <option value="8U">8U</option>
                                        <option value="9">9</option>
                                        <option value="10">10</option>
                                        <option value="11">11</option>
                                        <option value="12">12</option>
                                    </select>
                                </td>
                                <td valign="top" width="15%">
                                    <font size="2" color="#cc0000"><b>Overall:</b></font><br>
                                </td>
                                <td valign="top" width="15%"><select name="overall[]" multiple="multiple" class="multipleSelect">
                                        <option selected value="">All Toggles</option>
                                        <option value="EMG">EMG</option>
                                        <option value="DEV">DEV</option>
                                        <option value="PRO">PRO</option>
                                        <option value="ADV">ADV</option>
                                        <option value="blank">None</option>
                                    </select></td>
                            </tr>
                            <tr>
                                <td colspan="4"><b>After selecting your variables, please push the &quot"Search" button below. You results will load on another page that will allow you to create groups, view individual user files, or select that group for exporting data.</b></td>
                                <td valign="top" width="15%">
                                    <font size="2" color="#cc0000"><b>QPI:</b></font><br>
                                </td>
                                <td valign="top" width="15%"><select name="QPIs[]" multiple="multiple" class="multipleSelect">
                                        <option selected value="">All QPIs</option>
                                        <option value="Exemplary">Exemplary</option>
                                        <option value="Acceptable">Acceptable</option>
                                        <option value="Disengaged">Disengaged</option>
                                        <option value="Not Instructed">Not Instructed</option>
                                        <option value="Deficient">Deficient</option>
                                    </select><br>
                                    <br>
                                </td>
                            </tr>
                            <tr>
                                <td nowrap width="15%"><font size="2" color="#cc0000"><b>HSGQE Reading:</b></font></td>
                                <td width="12%">
                                    <select name="HSGQEReading" class="singleSelect">
                                        <option value="" selected>Either Y or N</option>
                                        <option value="Y">Yes</option>
                                        <option value="N">No</option>
                                    </select>
                                </td>
                                <td nowrap width="15%"><font size="2" color="#cc0000"><b>HSGQE  Math:</b></font></td>
                                <td width="15%">
                                    <select name="HSGQEMath" class="singleSelect">
                                        <option value="" selected>Either Y or N</option>
                                        <option value="Y">Yes</option>
                                        <option value="N">No</option>
                                    </select>
                                </td>
                                <td nowrap width="15%"><font size="2" color="#cc0000"><b>HSGQE Writing</b></font></td>
                                <td width="15%">
                                    <select name="HSGQEWriting" class="singleSelect">
                                        <option value="" selected>Either Y or N</option>
                                        <option value="Y">Yes</option>
                                        <option value="N">No</option>
                                    </select>
                                </td>
                            </tr>
                            <tr>
                                <td width="15%"></td>
                                <td colspan="4">

                                </td>
                                <td width="15%"></td>
                            </tr>
                        </table>
                        <div style="float:left">
                            <input type="submit" name="cmdSearch" value="Search" style="width:250px">
                        </div>
                    </div>
                </td>
            </tr>
        </table>
    </form>
</div>
{/block}

