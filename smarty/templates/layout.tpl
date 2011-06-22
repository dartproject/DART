<html>
    <head>
        <meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
        <title>{block name=title}{/block}</title>
        <link rel="stylesheet" href="dart_test.css" type="text/css">
	{block name=head}{/block}
        {$head}

        <script type="text/javascript" >
            {$js}
        </script>
    </head>
    <body>
        <div id="container">
            <!-- HEADER      ************************************* -->

            <div id="header">
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

            <!-- LEFT SIDE MENU *************************************-->
            <div id="leftMenu">
                {include file="leftSideMenu.tpl"}
            </div>

           <!-- Content ***********************************************-->
            <div id="content">
           
                    {block name=body}{/block}
                    {$body}
            </div>

            <div id="footer">
        {include file="footer.tpl"}
            </div>
        </div>



        {block name=js}{/block}
        <script language="JavaScript" type="text/javascript" src="wz_tooltip.js"></script>
        <script language="JavaScript" type="text/javascript" src="js/timeout.js"></script>
    </body>
</html>



