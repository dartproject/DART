<html>
    <head>
        <meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
        <title>{$pageTitle}</title>
        <link rel="stylesheet" href="dart_test.css" type="text/css">
	{block name=head}{/block}
        {$head}

        <script type="text/javascript" >
            {$js}</script>
        {literal}<script type="text/javascript">
var countDownInterval=3600;
var countDownTime=countDownInterval+1;
function countDown(){
countDownTime--;
if (countDownTime <=0){
countDownTime=countDownInterval;
clearTimeout(counter)
//window.location="index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.";
return
}
if (document.all) //if IE 4+
document.all.countDownText.innerText = countDownTime+" ";
else if (document.getElementById) //else if NS6+
document.getElementById("countDownText").innerHTML=countDownTime+" "
else if (document.layers){ //CHANGE TEXT BELOW TO YOUR OWN
document.c_reload.document.c_reload2.document.write('Timing out in <b id="countDownText">'+countDownTime+' </b> seconds')
document.c_reload.document.c_reload2.document.close()
}
counter=setTimeout("countDown()", 1000);
}

function startit(){
if (document.all||document.getElementById) //CHANGE TEXT BELOW TO YOUR OWN
document.write('Timing out in <b id="countDownText">'+countDownTime+' </b> seconds')
countDown()
}

if (document.all||document.getElementById)
startit()
else
window.onload=startit
//setTimeout("location.href='index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.'" , t)
</script>
{/literal}
    </head>
    <body marginheight="0" topmargin="0" vspace="0"
          marginwidth="0" leftmargin="0" hspace="0" style="margin:0; padding:0">
        <table border=0 cellpadding=0 cellspacing=0>
            <tr>
                <td colspan=3 valign=top nowrap>
                    <br/>

                    <!--    HEADER      *************************************-->

                    <a name='top_anchor'>
                        <img src="{$imageURL}frontlogo.gif" alt="" />
                    </a>
                    <a href="http://wiki.bssd.org/index.php/DART_System" target="_blank">
                        DART Project Info</a> ::
                    <a title="DART Support Information"
                       href="http://wiki.bssd.org/index.php/DART_System#DART_Technical_Support">
                        Support</a> ::
                    <a title="DART Contact Information"
                       href="http://wiki.bssd.org/index.php/DART_System#DART_Contacts"
                       target="_blank">Contact
                    </a>

                    <!--    HEADER      *************************************-->

                </td>
            </tr>
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
        <script language="JavaScript" type="text/javascript" src="wz_tooltip.js"></script>
    </body>
</html>



