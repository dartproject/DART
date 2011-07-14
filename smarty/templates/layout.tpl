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
<!--        <script type="text/javascript"
        src="http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js"></script>-->
        <script type="text/javascript"
        src="js/jquery/jquery-1.6.2.min.js"></script>
        <link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.8.14/themes/base/jquery-ui.css" type="text/css" media="all">
            <link rel="stylesheet" type="text/css"
                  href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/themes/ui-lightness/jquery-ui.css" />

            <link rel="stylesheet" href="css/dart.css" type="text/css" media="screen" />
            {***********************************************************************
                        CSS files
            *********************************************c**************************}
            {block name=css}{/block}


            {literal}
            <!--        <link rel="stylesheet" href="menu.css" type="text/css" media="screen" />-->
            <!--[if IE 6]>
            <link type='text/css' href='css/dart_ie.css' rel='stylesheet' media='screen' />
    <![endif]-->{/literal}

                {block name=head}{/block}
                {$head|default:''}

                <script type="text/javascript" >
            

                    {$js|default:''}
                </script>
        </head>
        <body>
            <div id="wrapper">
                {*******************************************************************
                Header
                ******************************************************************}

                {include file="header.tpl"}

                {*******************************************************************
                Top Menu
                *******************************************************************}

                {include file="menu.tpl"}

                <div id="container">
                    {******************************************************************************
                        Left Side Menu
                    *******************************************************************************}

                    {*<div id="leftMenu">
                    {include file="leftSideMenu.tpl"}  
                    </div>*}
                    {*{if $isSmarty}
                    <img alt="smarty template" src="{$imageURL}smarty_logo.png" align="right" />
                    {/if}*}
                    {******************************************************************************
                        Content
                    *******************************************************************************}
                    <div id="content">
                        <script type="text/javascript" >
                            document.getElementById("content").style.display = "none";
                        </script>



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
                </div>
                    <div class="clearfooter"></div>
            </div>
            {******************************************************************************
                        Footer
            *******************************************************************************}

            <div id="footer">
                {include file="footer.tpl"}
            </div>

            {******************************************************************************
            `   Dialog Window Markup
            ********************************************************************************}
            <div id="dialog" title="Your session is about to expire!" style="display:none">
                <p>You will be logged off in <span id="dialog-countdown"></span> seconds.</p>
                <p>Do you want to continue your session?</p>
            </div


            {******************************************************************************
                        Javascript files
            *******************************************************************************}
            <script type="text/javascript" src="js/wz_tooltip.js"></script>


            <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.8.13/jquery-ui.min.js"></script>
<!--            <script type="text/javascript" src="js/timeout.js"></script>-->
            <script type="text/javascript" src="js/jquery/jquery.idletimeout.js"></script>
            <script type="text/javascript" src="js/jquery/jquery.idletimer.js"></script>
            <script type="text/javascript" src="js/main.js"></script>
            {block name=js}{/block}
        </body>


    </html>



