<html>
    <head>
        <meta http-equiv="Content-Language" content="en-us">
        <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
        <link rel="shortcut icon" type="image/ico" href="{$imageURL}favicon.ico" />
        <title>Login to DART</title>
    </head>
    <body>
        <form method="POST" action="index.php?cmd=processLogon" name='login'>
            <input type=hidden name=command value="manage">
            <div align="center">
                <table width=100% height="100%">
                    <tr>
                        <td valign="middle" align="center">
                            <table border="1" cellpadding="5" cellspacing="0"
                                   bordercolorlight="#000000" bordercolordark="#FFFFFF"
                                   bgcolor="#C0C0C0">
                            
                            
                            {if $msg|default:'' != ''}
                                <tr>
                                    <td colspan=3 bgcolor=pink>
                            {$msg}
                                    </td>
                                </tr>
                            {/if}
                                <tr>
                                    <td bgcolor="#006666">
                                        <div align="center">
                                            <table border="0" cellpadding="3" cellspacing="0">
                                                <tr>
                                                    <td nowrap>
                                                        <table border="1" cellpadding="5" cellspacing="0" 
                                                               bordercolorlight="#000000" bordercolordark="#FFFFFF"
                                                               bgcolor="#C0C0C0" width="100%">
                                                            <tr>
                                                                <td bgcolor="white" width="100%">
                                                                    <div align="center">
                                                                        <font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Delta School District</font><br>
                                                                        <img src="{$imageURL}delta_logo.gif" alt="Delta Logo"><br>
                                                                        <font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">DART: Data Analysis &amp; Reporting Toolkit</font>
                                                                    </div>
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </td>
                                                </tr>
                                                <tr>
                                                    <td>
                                                        <table border="1" cellpadding="5" cellspacing="0" 
                                                               bordercolorlight="#000000" bordercolordark="#FFFFFF"
                                                               bgcolor="#C0C0C0" width="100%">
                                                            <tr>
                                                                <td bgcolor="white" width="100%">
                                                                    <table border="0" width="100%" cellspacing="0" cellpadding="2">
                                                                        <tr>
                                                                            <td width="50%" align="right"><font size="2" face="verdana,arial,helvetica">
                                                                                    <b>Username:</b></font></td>
                                                                            <td width="50%"><input type="text" name="user" size="30"></td>
                                                                        </tr>
                                                                        <tr>
                                                                            <td width="50%" align="right">
                                                                                <font face="verdana,arial,helvetica"><b><font size="2">Password:
                                                                                        </font></b></font></td>
                                                                            <td width="50%"><input type="password" name="password" size="30"></td>
                                                                        </tr>
                                                                        <tr>
                                                                            <td width="100%" colspan="2">
                                                                                <div align="center">
                                                                                    <font size="-2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
                                                                                        Support:
                                                                                        <a title="Email DART Tech Support" href="mailto:dart@bssd.org">DART Support</a>
                                                                                        <br><br>
                                                                                        <a href=index.php?cmd=forget>Forget your password?</a></font>
                                                                                </div>
                                                                            </td>
                                                                        </tr>
                                                                        <tr>
                                                                            <td colspan="2">Optional Demo credentials: <br/>Username: demo Password: demo</td>
                                                                        </tr>
                                                                    </table>
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </td>
                                                </tr>
                                                <tr>
                                                    <td align="right">
                                                        <table border="1" cellpadding="5" cellspacing="0" bordercolorlight="#000000" bordercolordark="#FFFFFF" bgcolor="#C0C0C0" width="100%">
                                                            <tr>
                                                                <td bgcolor="white" width="100%" valign="middle" align="center">
                                                                    <input type="submit" value="Login" name="B1" style="background-color:#eeeeee;font-family: verdana;font-weight:bold;color:#000080;font-size:10pt;" />
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </td>
                                                </tr>
                                            </table>
                                        </div>
                                    </td>
                                </tr>
                            </table>
                        </td>
                    </tr>
                </table>
            </div>
        </form>
    </body>
</html>
