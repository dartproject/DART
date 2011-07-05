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
{block name="title"}Teacher SIP Report{/block}


{block name="js"}
{/block}

{block name="body"}

{*
    ****************************************************************************
    Summary of passed Smarty Variables:
    ****************************************************************************
    $sitelist           - array of all sites
    $selectedSite       - Site ID of site viewed

    $teacherActionPlans                             - array of teacher action plans
        $teacherActionPlan.teacher                  - teacher's name
        $teacherActionPlan.actionPlans              - array of teacher's action plans
            $teacherActionPlan.actionPlan.action    - description of smart action
            $teacherActionPlan.actionPlan.eval      - evaluation of the action plan

*}

<div align="left">
    <br/>
    <font color="#cc0000" size="4"
          face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
        Teacher Improvement Plan
    </font>
</div>
<br/>

<form action=index.php method=get>
    <input type=hidden name=cmd value=teacherrep>
    Select Site:
    <select name="site" id="site" onChange="submit()">
        <option value=''>-select-</option>
            {html_options options=$sitelist selected=$selectedSite}
    </select>
</form>
<br/><br/>

    {foreach $teacherActionPlans as $teacherActionPlan}
<strong>{$teacherActionPlan.teacher}</strong><br>
<table cellpadding="5px" cellspacing="0px" border=1>
    <tr><th>Smart Plan</th>
        <th>Evaluation</th>
    </tr>
        {foreach $teacherActionPlan.actionPlans as $actionPlan}
    <tr>
        <td width=50%>{$actionPlan.action}</td>
        <td>{$actionPlan.eval}</td>
    </tr>
        {/foreach}

</table><br/>
    {/foreach}
{/block}