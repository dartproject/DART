{literal}<?xml version="1.0" encoding="iso-8859-1"?>{/literal}
<!doctype html> 
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
        <title>{block name=title}{/block}</title>
        <link rel="stylesheet" href="dart_test.css" type="text/css" media="screen">
        {literal}
        <!--        <link rel="stylesheet" href="menu.css" type="text/css" media="screen" />-->
        <!--[if IE 6]>
        <style>
        body {behavior: url("csshover3.htc");}
        #menu li .drop {background:url("img/drop.gif") no-repeat right 8px;
</style>
<![endif]-->{/literal}

{block name=head}{/block}
        {$head}

        <script type="text/javascript" >
    {$js}
        </script>
    </head>
    <body>

        <div id="header">
            <div id="banner" style="height:auto;">
                <div style="width:auto; display:inline; height: auto; float:left; margin-right: 10px ">
                    <img align="absmiddle" src="{$imageURL}bssd_logo.png" alt=""/>
                </div>
                <div style="display:inline;height:auto; vertical-align: middle">
                    <div style="font-size: 20pt; color:white;">
                        Bering Strait School District
                    </div>
                    <div style="color:white;">
                        Building bridges between tomorrow and today
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

                    {block name=body}{/block}
                    {$body}
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
        {block name=js}{/block}
        <script language="JavaScript" type="text/javascript" src="wz_tooltip.js"></script>
        <script language="JavaScript" type="text/javascript" src="js/timeout.js"></script>
    </body>
</html>



