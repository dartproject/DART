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

{*{literal}<?xml version="1.0" encoding="iso-8859-1"?>{/literal}*}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">


<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
    <head>
        <link rel="shortcut icon" type="image/ico" href="{$imageURL}favicon.ico" />
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
        <title>DSD DART: {block name=title}{/block}</title>
        <script type="text/javascript"
        src="http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js"></script>
        <link rel="stylesheet" type="text/css"
              href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/themes/ui-lightness/jquery-ui.css" />
        <link rel="stylesheet" href="dart_test.css" type="text/css" media="screen" />
       {***********************************************************************
                        CSS files
        ***********************************************************************}
        {block name=css}{/block}


        {literal}
        <!--        <link rel="stylesheet" href="menu.css" type="text/css" media="screen" />-->
        <!--[if IE 6]>
        <style>
        body {behavior: url("csshover3.htc");}
        #menu li .drop {background:url("img/drop.gif") no-repeat right 8px;
</style>
<![endif]-->{/literal}

{block name=head}{/block}
        {$head|default:''}

        <script type="text/javascript" >
            

            {$js|default:''}
        </script>
    </head>
    <body>

        <div id="header">
            <div id="banner" style="height:auto;">
                <div style="width:auto; display:inline; height: auto; float:left; margin-right: 10px ">
                    <img align="absmiddle" src="{$imageURL}delta_logo_small.gif" alt=""/>
                </div>
                <div style="display:inline;height:auto; vertical-align: middle">
                    <div style="font-size: 20pt; color:white;">
                        Delta School District
                    </div>
                    <div style="color:white;">
                        Inspired Learning
                    </div>
                </div>



            </div>

            {include file="menu.tpl"}
        </div>
        <div id="container">
{******************************************************************************
                        HEADER
*******************************************************************************}
{*            <div id="banner">
                <a name='top_anchor'>
<!--                    <img src="{$imageURL}frontlogo.gif" alt="" />-->
                </a>
                <div id="top_menu" style="margin:0px;padding:0px;">
                    <div id="countDownText" style="float:left; margin:0px; padding:0px;width:180px;"></div>
{*                    <div>
                        <a href="http://wiki.bssd.org/index.php/DART_System" target="_blank">
                            DART Project Info</a> ::
                        <a title="DART Support Information"
                           href="http://wiki.bssd.org/index.php/DART_System#DART_Technical_Support">
                            Support</a> ::
                        <a title="DART Contact Information"
                           href="http://wiki.bssd.org/index.php/DART_System#DART_Contacts"
                           target="_blank">Contact
                        </a>
                    </div>

                </div>
            </div>

*}
{******************************************************************************
                        Left Side Menu
*******************************************************************************}

            <div id="leftMenu">
               {include file="leftSideMenu.tpl"}  
            </div>

{******************************************************************************
                        Content
*******************************************************************************}
            <div id="content">
                <script type="text/javascript" >
                    document.getElementById("content").style.display = "none";
                </script>

                {if $isSmarty}
                <img alt="smarty template" src="{$imageURL}smarty_logo.png" align="right" />
                {/if}

                {block name=body}{/block}
                {$body|default:""}

                {literal}
                <script type="text/javascript" >
                    $(document).ready(function(){
                        document.getElementById("content").style.display = "block";
                    });
                </script>
                {/literal}
            </div>

{******************************************************************************
                        Footer
*******************************************************************************}
            <div id="footer">
        {include file="footer.tpl"}
            </div>
        </div>

{******************************************************************************
                        Javascript files
*******************************************************************************}
        <script type="text/javascript" src="js/wz_tooltip.js"></script>
        <script type="text/javascript" src="js/timeout.js"></script>
        <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.8.13/jquery-ui.min.js"></script>
        {block name=js}{/block}
    </body>


</html>



