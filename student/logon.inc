<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$bgcolor = "#EAE0D3"; // #ffcc99
// $bgcolor = "#ffcc99";
?>
<html>

<head>
<meta http-equiv="Content-Language" content="en-us">
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
		<title>Login to DART</title>
		<style>
<!--
 INPUT.button { background-color:#eeeeee;font:verdana;font-weight:bold;color:#000080;font-size:10pt; }
-->
</style>

</head>

<body>

<?php 
$msg = $_GET['msg'];
if(isset($msg) and $msg != "") {
   $msg = "<tr><td colspan=3 bgcolor=pink>$msg</td></tr>";
} else { $msg = "";}
?>

<form method="POST" action="index.php?cmd=processLogon" name='login'>
<input type=hidden name=command value="manage">
<div align="center">
  <center>
  <table width=100% height="100%" ><tr><td valign="middle" align="center">
  <table border="1" cellpadding="5" cellspacing="0" bordercolorlight="#000000" bordercolordark="#FFFFFF" bgcolor="#C0C0C0">
  <?php echo $msg; ?>
     <tr>
      <td bgcolor="#006666">
        <div align="center">
                 <table border="0" cellpadding="3" cellspacing="0">

                    <tr>
                      <td nowrap>
                        <table border="1" cellpadding="5" cellspacing="0" bordercolorlight="#000000" bordercolordark="#FFFFFF" bgcolor="#C0C0C0" width="100%">
                          <tr >
                            <td bgcolor=<?php echo $bgcolor ?> width="100%">
																		<div align="center">
																			<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Bering Strait School District<br>
																			</font><img src="../images/bssd_logo_logon.gif" alt="BSSD Logo" width="85" height="88"><br>

																			<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">DART: Data Analysis &amp; Reporting Toolkit<br>Student/Parent Login</font></div>
																	</td>
                          </tr>
                        </table>
                      </td>
                    </tr>
                    <tr>

                      <td>
                        <table border="1" cellpadding="5" cellspacing="0" bordercolorlight="#000000" bordercolordark="#FFFFFF" bgcolor="#C0C0C0" width="100%">
                          <tr>
                            <td bgcolor=<?php echo $bgcolor ?> width="100%">
                              <table border="0" width="100%" cellspacing="0" cellpadding="2">
                                <tr>
                                  <td width="50%" align="right"><font size="2" face="verdana,arial,helvetica"><b>Username</b></font><font face="verdana,arial,helvetica"><b><font size="2">:
                        </font></b></font></td>
                                  <td width="50%"><input type="text" name="user" size="30"></td>

                                </tr>
                                <tr>
                                  <td width="50%" align="right"><font face="verdana,arial,helvetica"><b><font size="2">Password:
                        </font></b></font></td>
                                  <td width="50%"><input type="password" name="password" size="30"></td>
                                </tr>
                                <tr>
                                  <td width="100%" colspan="2">
																					<div align="center">

																						<font size="-2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Support: <a title="Email DART Tech Support" href="mailto:dart@bssd.org">DART Support</a><br><br><a href=index.php?cmd=forget>Forget your password?</a></font></div>
																				</td>
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
                            <td bgcolor=<?php echo $bgcolor ?> width="100%" valign="middle" align="center"><input CLASS="button" type="submit" value="Login" name="B1"><img border="0" src="http://dart.bssd.org/images//cleardot.gif" width="1" height="1"></td>
                          </tr>
                        </table>
                      </td>

                    </tr>
                  </table>

      </div>
    </td>
  </tr>
  </table></td></tr>
  </table>
</div>
</form>

</body>
</html>
