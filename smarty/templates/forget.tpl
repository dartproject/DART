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
			<form method="get" action="index.php">
				<input type=hidden name="cmd" value="getPwd">
				<div align="left">
					<br />
					<div align="left">
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
				<div align="center">
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
		<div id="footer">
			{include file="footer.tpl"}
		</div>
	</body>
</html>