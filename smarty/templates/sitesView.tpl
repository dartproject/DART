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
{block name="title"}District Schools{/block}

{block name=css}
{/block}

{block name="js"}
<script type="text/javascript" src="js/sitesView.js"></script>
{/block}

{block name="body"}

<div style="padding-bottom: 20px">
    <font size="4" color="#cc0000">District Schools</font><br>

    <div id="sites"> 
        <a href="index.php?cmd=sitesEdit">Add new school</a>
        {if $msg|default:''}
            <p style="color: tomato; font-size: 10pt">{$msg}</p>
         {/if}
        
        
        <table cellpadding=5 cellspacing=0>
            <tr style="height:40px; font-size: 10pt; font-weight: bold;">
                <td style="border-bottom: 1px solid; border-left: 1px solid; border-top: 1px solid;"></td>
                <td style="border-bottom: 1px solid; border-top: 1px solid;">Name</td>
                <td style="border-bottom: 1px solid; border-top: 1px solid;">Abbreviation</td>
                <td style="border-bottom: 1px solid; border-right: 1px solid; border-top: 1px solid;">Logo</td>
            </tr>
            {foreach $sites as $site}
                <tr style="font-size: 9pt;">
                <td style="border-bottom: 1px solid; border-left: 1px solid; border-top: 1px solid;">
                <a href="index.php?cmd=sitesEdit&siteid={$site.siteid}">
                    <img src="{$imageURL}icons/pencil_16.png" title="Edit Site" /></a>
                <a href="index.php?cmd=sitesDelete&siteid={$site.siteid}" onclick='javascript:return confirm_delete("You are about to delete the a school. Please act carefully. Click OK to continue")'>
                   <img src="{$imageURL}icons/bin_empty_16.png" title="Delete Site"/></a>
                </td>
                <td style="border-bottom: 1px solid; border-top: 1px solid;">{$site.name}</td>
                <td style="border-bottom: 1px solid; border-top: 1px solid;">{$site.siteid}</td>
                <td style="border-bottom: 1px solid; border-right: 1px solid; border-top: 1px solid;">
                    <img width="200" height="200" alt="" src="{$logoURL}{$site.logo}" />
                </td>
            </tr>
            {/foreach}
        </table>
    </div>
</div>

{/block}