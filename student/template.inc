<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
?>

<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
<meta http-equiv="Refresh" content="<?php echo $expireTime ?>;URL=index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.">
<title><?php echo $title ?></title>
<link rel="stylesheet" href="../dart_test.css" type="text/css">
<script>
<?php echo $js ?>
</script>
</head>
<body marginheight="0" topmargin="0" vspace="0"
marginwidth="0" leftmargin="0" hspace="0" style="margin:0; padding:0" bgcolor="<?php echo $dart_bkgnd ?>">
<table border=0 cellpadding=0 cellspacing=0>

<tr><td colspan=3 valign=top nowrap><br><?php include("../header.inc") ?></td></tr>
<tr><td colspan=3 valign=top><img src="../images/cleardot.gif" height="10"></td></tr>

<tr><td width=10>
<img src="../images/cleardot.gif" height="1" width="10" border="0" alt="spacer">
</td>
<td valign=top width=90>
<?php include("leftside.inc") ?><br>
<img src="../images/cleardot.gif" height="1" width="100" border="0" alt="spacer">
</td>
<td valign=top align=left width=600><br><?php echo $body ?></td></tr>

<tr><td colspan=2></td><td><br><br><?php include("../footer.inc") ?></td></tr>
</table>
<script language="JavaScript" type="text/javascript" src="../wz_tooltip.js"></script>
</body>
</html>
