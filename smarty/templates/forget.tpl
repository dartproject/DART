{*{literal}<?xml version="1.0" encoding="iso-8859-1"?>{/literal}*}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
	<head>
		<meta http-equiv="Content-Language" content="en-us" />
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1252" />
		<title>
			Password Recovery
		</title>
		<link rel="shortcut icon" type="image/ico" href="{$imageURL}favicon.ico" />
		<link rel="stylesheet" href="css/dart.css" type="text/css" />
		{literal}
		<!--        <link rel="stylesheet" href="menu.css" type="text/css" media="screen" />-->
		<!--[if IE 6]>
		<link type='text/css' href='css/dart_ie.css' rel='stylesheet' media='screen' />
		<![endif]-->{/literal}
	</head>
	<body>
		<div id="wrapper">
			{include file="header.tpl"}
			<div id="container" style="width: 1024px; margin: auto; padding-bottom:30px;">
				<form method="get" action="index.php">
					<div style="text-align:left">
						<input type=hidden name="cmd" value="getPwd" />
						<br />
						<div style="text-align:left">
							<font size="4" color="#cc0000">DART Password Recovery</font>
							<br />
							<br />
						</div>
						<div class="noteimportant">
						Enter your username below, and your password will be sent to the email address
						associated with your account.  If you do not remember your username, please
							<a title="DART Support" href="mailto:dart@bssd.org">email us</a> for
						instructions.  All password recovery attempts are logged with IP and
						timestamp. You should receive your password within a few minutes.
						</div>
					</div>
					<div style="text-align:center">
						<br />
						<table border="1">
							<tr>
								<th bgcolor="pink" colspan="3">
								{$msg|default: '&nbsp;'}
								</th>
							</tr>
							<tr>
								<td nowrap bgcolor="#ccccff">
									&nbsp;
								</td>
								<th nowrap bgcolor="#ccccff">
									<font size="2">
									Example
									</font>

								</th>
								<th bgcolor="#ccccff">
									<font size="2">
									Your Username
									</font>
								</th>
							</tr>
							<tr>
								<td nowrap>
									<font size="3" color="#cc0000">
										<b>DART Username:</b>
									</font>
								</td>
								<td nowrap align="center">
									<font size="2">tommyteacher</font>
								</td>
								<td nowrap align="center">
									<input name="username" type="text" size="40" />
								</td>
							</tr>
						</table>
						<br />
						<input type="submit" name="buttonName" value="Request Password" />
						<br />
					</div>
				</form>
			</div>
			<div class="clearfooter"></div>
		</div>
		<div id="footer">
			{include file="footer.tpl"}
		</div>
	</body>
</html>
