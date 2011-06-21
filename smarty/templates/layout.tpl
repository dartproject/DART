<html>
    <head>
        <meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
        <title>{block name=title}{/block}</title>
        <link rel="stylesheet" href="dart_test.css" type="text/css">
	{block name=head}{/block}
        {$head}

        <script type="text/javascript" >
            {$js}</script>
    </head>
    <body marginheight="0" topmargin="0" vspace="0"
          marginwidth="0" leftmargin="0" hspace="0" style="margin:0; padding:0">
        <div id="header" style="margin:10px">
            <a name='top_anchor'>
                <img src="{$imageURL}frontlogo.gif" alt="" />
            </a>
            <div id="top_menu" style="margin:0px;padding:0px;">
                <div id="countDownText" style="float:left; margin:0px; padding:0px;width:180px;"></div>
                <div>
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

        <table border=0 cellpadding=0 cellspacing=0>
<!--            <tr>
                <td colspan=3 valign=top nowrap>
                    <br/>

                        HEADER      *************************************




                        HEADER      *************************************

                </td>
            </tr>-->
            <tr>
                <td colspan=3 valign=top>
                    <img src="images/cleardot.gif" height="10" alt="" />
                </td>
            </tr>
            <tr>
                <td width=10>
                    <img src="images/cleardot.gif" height="1"
                         width="10" border="0" alt="spacer" />
                </td>
                <td valign=top width=90>

                    <!-- LEFT SIDE MENU *************************************-->
                    {include file="leftSideMenu.tpl"}

                    <br/>

                    <img src="images/cleardot.gif" height="1" width="100"
                         border="0" alt="spacer"/>
                </td>

                <td valign=top align=left width=600>
                    <br/>
                    <!-- BODY ***********************************************-->
                    {block name=body}{/block}
                    {$body}
                </td>
            </tr>
            <tr>
                <td colspan=2></td>
                <td>
                    <br/><br/>
                    {include file="footer.tpl"}
                </td>
            </tr>
        </table>
        {block name=js}{/block}
        <script language="JavaScript" type="text/javascript" src="wz_tooltip.js"></script>
        <script language="JavaScript" type="text/javascript" src="js/timeout.js"></script>
    </body>
</html>



