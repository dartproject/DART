{*******************************************************************************
    @ author:
    @ maintainer
*******************************************************************************}
{extends file="layout.tpl"}
{block name="title"}Site Improvement Plan{/block}


{block name="js"}
{/block}

{block name="body"}
<form action="index.php" method="GET">
    <input type="hidden" name="cmd" value="siterep">
    Select Site: <select name="site" id="site" onChange="submit()">
        <option value=''>-select-</option>
	{foreach $sites as $site}
        <option value ="{$site.siteid}"
                {if ($site.siteid == $selectedSiteId)}
                selected
                {/if}>
            {$site.name}
        </option>
        {/foreach}
    </select>
</form>
{if $report}
<table border="0" cellpadding="0" cellspacing="2">
    <tr>
        <td width="60%">
            <div align="left">
                <br/>
                <font color="#cc0000" size="4"
                      face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                    Site Improvement Plan: {$report->year|cat:"-"|cat: (($report->year+1)|substr:2:2)} School Year
                </font>
            </div>
            <blockquote>
                <div align="left">
                    <div class="noteimportant">
                        <font size="2"
                              face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                            All 15 schools in the Bering Strait are required to do
                            Site School Improvement Plans in DART, and adjust their goals each quarter.
                            Individual BSSD teachers also use the DART SIP Module to create classroom level plans.
                            <br/>
                            <br/>
                            The following Site Improvement Plan data has been entered by
                            BSSD Site Office Program managers and staff, and summarizes the Site's
                            efforts for this school year. This is meant to meet the
                            reporting requirements of the Alaska Department of Education and Early Development.
                        </font>
                    </div>
                </div>
            </blockquote>
        </td>
        <td width="40%">
            <div align="center">
                <img src="http://dart.bssd.org/images/eed_logo.gif" alt=""
                     height="168" width="182" border="0">
                <img src="http://dart.bssd.org/images/BSSD-logo_168.gif" alt=""
                     height="168" width="162" border="0">
            </div>
        </td>
    </tr>
    <tr>
        <td colspan="2">
            <div align="left">
                <table border="0" cellpadding="2" cellspacing="2" width="1000">
                    <tbody>
                        <tr>
                            <td colspan="2" bgcolor="#ccffff">
                                <div align="left">
                                    <font size="3" color="#336666" face="Arial">
                                        <b>Summary of Site Improvement Plan</b>
                                    </font>
                                </div>
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </td>
    </tr>
</table>
<div align="center">
    <table width="550" border="0" cellspacing="2" cellpadding="0">
        <tr>
            <td nowrap bgcolor="#ffff99" width="50%">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Subjects in Order of Strength</b>
                    </font>
                </div>
            </td>
            <td nowrap bgcolor="#ffff99" width="50%">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Strongest &amp; Weakest Grade Levels</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td width="50%">
                <font face="Arial" size="2">
                            {$report->subjectsInOrderOfStrength}
                </font>
            </td>

            <td width="50%">
                <font face="Arial" size="2">
                                {$report->strongestWeakestGrades}
                </font>
            </td>
        </tr>
    </table>
</div>
<div align="left">
    <p>
        <font size="3" color="#336666" face="Arial">
            <b>Specific Areas of Emphasis</b>
        </font><br/>
    </p>
</div>
{*******************************************************************************
                            Specific Areas of Emphasis
*******************************************************************************}
<div align="center">
    <table border=1>
        {foreach $report->emphasisAreas as $emphasisArea}
        <tr>
            <td class=sipsubheading bgcolor="#ffff99">
                <font size="2" face="Arial">
                    <b>{$emphasisArea->area}:</b>
                </font>
            </td>
            <td>
                <font size="3" face="Arial">
                    {$emphasisArea->value}
                </font>
            </td>
        </tr>
        {/foreach}
    </table>
</div>
{*******************************************************************************
                            State Questions & Responses
*******************************************************************************}

<div align="left">
    <p>
        <font size="3" color="#336666" face="Arial">
            <b>State Questions and Responses</b>
        </font>
    </p>

{*******************************************************************************
                            1) NOT MET AYPs
*******************************************************************************}
    <p>
        <font size="2" face="Arial">
            <b>1) Check each cell in the following table to identify
                the areas in which the site did NOT meet AYP:</b>
        </font>
    </p>
    <p>
        <font size="2" face="Arial">Each marked cell in the following
            table identifies the areas in which the site did
            <u>NOT</u> meet AYP:&nbsp;
        </font>
    </p>
    <div align="center">
        <table width="600" border="0" cellspacing="2" cellpadding="0">
            <tr>
                <td colspan="3" bgcolor="#ffff99">
                </td>
                <td bgcolor="#ffff99">
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>All Students</b>
                        </font>
                    </div>
                </td>
                <td bgcolor="#ffff99">
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>Ethnic Groups</b>
                        </font>
                    </div>
                </td>
                <td bgcolor="#ffff99">
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>SWD</b>
                        </font>
                    </div>
                </td>
                <td bgcolor="#ffff99">
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>LEP</b>
                        </font>
                    </div>
                </td>
                <td bgcolor="#ffff99">
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>Low-Income</b>
                        </font>
                    </div>
                </td>
            </tr>
                        {foreach $report->notMetAYPs as $notMetAYP}
            <tr>
                <td colspan="3">
                    <font size="2" face="Arial">
                        <b>{$notMetAYP->name}</b>
                    </font>
                </td>
                <td>
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>
                                            {$notMetAYP->allStudents}
                            </b>
                        </font>
                    </div>
                </td>
                <td>
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>{$notMetAYP->ethnicGroups}</b>
                        </font>
                    </div>
                </td>
                <td>
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>{$notMetAYP->SWD}</b>
                        </font>
                    </div>
                </td>
                <td>
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>{$notMetAYP->LEP}</b>
                        </font>
                    </div>
                </td>
                <td>
                    <div align="center">
                        <font size="2" face="Arial">
                            <b>{$notMetAYP->lowIncome}</b>
                        </font>
                    </div>
                </td>
            </tr>
                        {/foreach}
        </table>
    </div>
{*******************************************************************************
                            2. Describe the process used to notify parents
*******************************************************************************}
    <p>
        <font size="2" face="Arial">
            <b>2) Describe the process used to notify parents of the school
                improvement status and of their opportunities to be involved
                in addressing the academic issues that caused the school to be
                identified for improvement. Please include a copy of the notification
                sent to parents.</b>
        </font>
    </p>
</div>
<div align="center">
    <table width="750" border="1" cellspacing="2" cellpadding="0">
        <tr>
            <td bgcolor="#ffff99">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Site Response to Question 2</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div align="left">
                    <font size="2" face="Arial">
                                    {$report->stateQ2Reponse->response}
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td bgcolor="#ffff99">
                <div align="center">

                    <font size="2" face="Arial">
                        <b>Links to Supporting Evidence Online for Response</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <font size="2" face="Arial">
                                {$report->stateQ2Response->links}
                </font>
            </td>
        </tr>
    </table>
</div>
{*******************************************************************************
                            3. Describe the process to notify all the parents
*******************************************************************************}
<div align="left">
    <div align="left">
        <p><font size="2" face="Arial">
                <b>3) Describe the peer review process that the district used to
                    review and approve this School Improvement Plan</b>
            </font>
        </p>
    </div>
</div>
<div align="center">
    <table width="750" border="1" cellspacing="2" cellpadding="0">
        <tr>
            <td bgcolor="#ffff99">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Site Response to Question 3</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div align="left">
                    <font size="2" face="Arial">
                       {$report->stateQ3Response->response}
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td bgcolor="#ffff99">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Links to Supporting Evidence Online for Response</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <font size="2" face="Arial">
                                {$report->stateQ3Response->links}
                </font>
            </td>
        </tr>
    </table>
</div>
{*******************************************************************************
                            4. Describe technical assistance
*******************************************************************************}
<div align="left">
    <div align="left">
        <div align="left">
            <p><font size="2" face="Arial">
                    <b>4) Describe the responsibilities of the school and the
                        district in implementing this School Improvement Plan,
                        and any technical assistance the district will provide
                        to the school. (Please contact the department if technical
                        assistance is needed in developing or implementing the plan.)</b>
                </font>
            </p>
        </div>
    </div>
</div>
<div align="center">
    <table width="750" border="1" cellspacing="2" cellpadding="0">
        <tr>
            <td bgcolor="#ffff99">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Site Response to Question 4</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <div align="left">
                    <font size="2" face="Arial">
                                    {$report->stateQ4Response->response}
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td bgcolor="#ffff99">
                <div align="center">
                    <font size="2" face="Arial">
                        <b>Links to Supporting Evidence Online</b>
                    </font>
                </div>
            </td>
        </tr>
        <tr>
            <td>
                <font size="2" face="Arial">
                                {$report->stateQ4Response->links}
                </font>
            </td>
        </tr>
    </table>
</div>
{*******************************************************************************
        GOALS & ACTION PLANS
*******************************************************************************}

<div align="left">
    <p>
        <font size="3" color="#336666" face="Arial">
            <b>Goals and Action Plans</b>
        </font>
    </p>
            {foreach $report->GAPlans as $GAPlan}
    <table class="Table11" border="0" cellspacing="0" cellpadding="0">
        <colgroup>
            <col width="1059" />
        </colgroup>
        <tr class="Table111">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; ">
                <div align="right">
                    <font size="3" color="#336666" face="Arial">
                        <b>Emphasis Area ::</b>
                    </font><font size="3" color="red" face="Arial">
                        <b>{$GAPlan->emphasisArea}</b>
                    </font>
                </div>
            </td>
        </tr>
{*******************************************************************************
            Site Measurable Goal
*******************************************************************************}
        <tr class="Table111">
            <td class="Table11_A1" style="text-align:left;width:9.5368in;" bgcolor="#ffff99">
                <p class="P9">
                    <font size="2" face="Arial">
                        <b>Site Meaurable Goal</b>
                    </font>
                </p>
            </td>
        </tr>
        <tr class="Table112">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; ">
                <br/>
                <font size="2" face="Arial">
                                {$GAPlan->districtMeasurableGoal}
                </font>
            </td>
        </tr>
{*******************************************************************************
            Current Performance Level on SBA
*******************************************************************************}
        <tr class="Table112">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; " bgcolor="#ffff99">
                <p class="P7">
                    <b><font size="2" face="Arial">
                            <span class="T12">
                                Current Performance Level on SBAs
                            </span>
                        </font>
                    </b>
                </p>
            </td>
        </tr>
        <tr class="Table113">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; ">
                <br>
                <font size="2" face="Arial">
                                {$GAPlan->currentSBA}
                </font>
            </td>
        </tr>
{*******************************************************************************
            Performance Target
*******************************************************************************}
        <tr class="Table113">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; "
                bgcolor="#ffff99">
                <b><font size="2" face="Arial">
                        <span class="T12">
                            Performance Target
                        </span>
                    </font>
                </b>
            </td>
        </tr>
        <tr class="Table113">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; ">
                <br>
                <font size="2" face="Arial">
                                {$GAPlan->performanceTarget}
                </font>
            </td>
        </tr>
{*******************************************************************************
            Scientifical Support
*******************************************************************************}
        <tr class="Table113">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; "
                bgcolor="#ffff99">
                <p class="P10">
                    <font size="2" face="Arial">
                        <b>Scientifically based research to support each strategy listed below.
                            Can include references or summaries of relevant research:</b>
                    </font>
                </p>
            </td>
        </tr>
        <tr class="Table113">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; ">
                <br>
                <font size="2" face="Arial">
                                {$GAPlan->researchSupport}
                </font>
            </td>
        </tr>
        <tr class="Table113">
            <td class="Table11_A1" style="text-align:left;width:9.5368in; ">
                <div align="center">
                    <font size="3" color="#336666" face="Arial"><b>{$GAPlan->emphasisArea} Action Planning</b></font></div>
            </td>

        </tr>
    </table>
{*******************************************************************************
            Smart Plans & Evaluations
*******************************************************************************}
    <table class="Table12" width="100%" border="1" cellspacing="0" cellpadding="0">
        <tr class="Table121">
            <td class="Table12_A1" style="text-align:left;" bgcolor="#ffff99" width="50%">
                <div align="center">
                    <font size="2" face="Arial"><b>Smart Plans</b></font></div>
            </td>
            <td class="Table12_E1" style="text-align:left;" bgcolor="#ffff99" width="50%">
                <div align="center">
                    <font size="2"><font face="Arial"><b>Evaluation</b></font></font></div>
            </td>
        </tr>
                {foreach $GAPlan->actionPlans as $actionPlan}
        <tr>
            <td>{$actionPlan.action}</td>
            <td>{$actionPlan.eval}</td>
        </tr>
                {/foreach}

    </table><br>

            {/foreach}
</div>
{/if}
{/block}