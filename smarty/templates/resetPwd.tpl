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
			<![endif]-->
		{/literal}
	</head>
	<body>
		<div id="wrapper">
			{include file="header.tpl"}
			<div id="container" style="width: 1024px; margin: auto; padding-bottom:30px;">
				<div  style="text-align:left">
					<br />
					<div style="text-align:left">
						<font size="4" color="#cc0000">Reset DART Password</font>
						<br />
						<br />
					</div>
				</div>
				<div align=center>
					<br />
					<br />
					<font size="4" color="#cc0000">
					Change Password :: {$username|default:'&nbsp;'}
					</font>
					<br />
					<form name="resetPwd" action="#" method ="POST">
						<table border="1" cellspacing="2" cellpadding="3">
							<tr>
								<td colspan=2 bgcolor=lightpink>
									<font size="2" color="#cc0000"><b>{$msg}</b></font>
								</td>
							</tr>
							<tr>
								<td>
									<font size="2"><b>New Password:</b></font>
								</td>
								<td>
									<input type="password" name="pwd1" size="40" maxlength="20"/>
								</td>
							</tr>
							<tr>
								<td>
									<font size="2"><b>New Password Retype:</b>
									</font>
								</td>
								<td>
									<input type="password" name="pwd2" size="40" maxlength="20"/>
								</td>
							</tr>
							<tr>
								<td colspan="2">
									<input type="submit" name="Update" value="Update" />
								</td>
							</tr>
						</table>
					</form>
				</div>
			</div>
			<div class="clearfooter"></div>
		</div>
		<div id="footer">
			{include file="footer.tpl"}
		</div>
	</body>
</html>
