<html>
	<head>
		<meta http-equiv="Content-Language" content="en-us">
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
		<title>
			Password Recovery
		</title>
		<link rel="stylesheet" href="css/dart.css" type="text/css">
		<link rel="shortcut icon" type="image/ico" href="{$imageURL}favicon.ico" />
	</head>
	<body marginheight="0" topmargin="0" vspace="0"
		  marginwidth="0" leftmargin="0" hspace="0" style="margin:0; padding:0">
		{include file="header.tpl"}
		<div id="container">
			<div align="left">
				<br />
				<div align="left">
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
			<div id="footer">
			{include file="footer.tpl"}
			</div>
		</div>
	</body>
</html>
