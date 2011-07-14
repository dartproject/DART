{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}

{block name="body"}
<div align="center">
    <form name=ptime method=get action="index.php">
        <input type=hidden name=cmd value=Dashboard>
        <input type=hidden name=year value={$year}>
        <input type=hidden name=quarter value={$quarter}>
        <table>
            <tr>
                {foreach $menus as $key => $value}
                    <td>
                        {html_options name="{$key}" options=$value.menu selected=$value.selected onChange="submit()"}
                    </td>
                {/foreach}
            </tr>
        </table>
    </form>
    <table width="90%" border="0" cellspacing="0" cellpadding="2">
        <tr>
            <td colspan="2">&nbsp;</td>
            <td style="white-space: nowrap" align="center">
                <b>
                    <font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2" color="#0000cc">
                    {$menus.year.menu.$year} {$menus.quarter.menu.$quarter}
                    </font>
                </b>
            </td>
            <td>&nbsp;</td>
            <td colspan="2" style="white-space: nowrap" align="right">
                <font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">
                <b>Today is: </b>{$currdatedisplay}
                </font>
            </td>
        </tr>
        <!-- ATTENDANCE -->
        {$section = $sections.Attendance}
            <tr>
                <td colspan="6" style="white-space: nowrap" bgcolor="#ffffcc"  align="left">
                    <font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
                    <b>Attendance</b>
                    </font>
                </td>
            </tr>
            {foreach $section as $row}
                <tr>
                    {foreach $row as $key => $value}
                        {if $key != ""}
                            <td style="white-space: nowrapp" align="right">
                                <font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                <b>{$value.label}:</b>
                                </font>
                            </td>
                            <td style="white-space: nowrap">
                                <font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                <a href=index.php?cmd=AttendanceDrillDown&type={$key}&site={$site}&{$value.param}>
                                    {$value.value}
                                </a>
                                </font>
                            </td>
                    {else}<td colspan="2">&nbsp;</td>{/if}
                {/foreach}
            </tr>
        {/foreach}
        <!-- DISCIPLINE -->
        {$section = $sections.Discipline}
            <tr>
                <td colspan="6" style="white-space: nowrap" bgcolor="#ffffcc"  align="left">
                    <font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
                    <b>Discipline</b>
                    </font>
                </td>
            </tr>
            {foreach $disciplineLabels as $type => $label}
                <tr>
                    {foreach $section as $period => $data}
                        <td style="white-space: nowrapp" align="right">
                            <font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                            <b>{$label} - {$data.label}:</b>
                            </font>
                        </td>
                        <td style="white-space: nowrap">
                            <font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                            {$data.value.{$type}}
                            </font>
                        </td>
                    {/foreach}
                </tr>
            {/foreach}
        </table>
    </div>

    {/block}
