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
{block name="title"}District Schools Edit{/block}

{block name=css}
{/block}

{block name="js"}

{/block}

{block name="body"}


<div style="padding-bottom: 20px">
    {if $site|default:''}
        <font size="4" color="#cc0000">Edit {$site.name} information</font><br>
    {else}
        <font size="4" color="#cc0000">Add new school</font><br>
    {/if}
    <a href="index.php?cmd=sitesView">View sites</a>
    <br/>
    <br/>
    <form action="index.php?cmd=sitesUpdate" method=POST enctype="multipart/form-data">
        <input type="hidden" value="{$site.siteid}" name="origSiteId" />
        <table cellpadding=5 cellspacing=0>
            <tr>
                <td style="font-weight:bold">Name:</td>
                <td><input value="{if $site}{$site.name}{/if}" name="name" style="width:250px;" /></td>
            </tr>
            <tr>
                <td style="font-weight:bold">Abbreviation</td>

                <td>{if $site}
                    {$site.siteid}
                    {else}
                        <input value="" name="siteid" maxlength="3" min="3" style="width:50px"/>
                        3 letters
                        {/if}
                        </td>    
                    </tr>
                    <tr>
                        <td style="font-weight:bold">Logo:</td>
                        <td>
                            {if $site && $site.logo}
                                <img alt="" src="{$imageURL}SchoolLogos/{$site.logo}" /><br/>
                            {/if}
                            <input type="file" name="file" id="file" /> Images should be 200px x 200px and not larger than 300kB
                        </td>
                    </tr>
                    <tr>
                        <td colspan=2>
                            {if $site}
                            <input type="submit" name="submit" value="Update" />
                            {else}
                                <input type="submit" name="submit" value="Create" />
                                {/if}
                            <a href="index.php?cmd=sitesView"><input type="button" value="Cancel" /></a>
                        </td>
                    </tr>
                </table>
                <br/>
                <ul>
                    {if $errors|default:''}
                        {foreach $errors as $error}

                            <li>{$error}</li>
                        {/foreach}
                    {/if}
                </ul>
            </form>
        </div>

        {/block}