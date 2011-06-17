<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

if(!isset($title)) { $title = "DART"; } 
// Times arein seconds
$warningtime = 2400; 
$timeout = 3600;
?>
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
<title><?php echo $title ?></title>
<link rel="stylesheet" href="dart_test.css" type="text/css">
<?php echo $head ?>
<script>
<!--
function popUp2(URL, x, y) {
  	self.name = "listings"; // names current window as "listings"
	newwindow = window.open(URL, 'name', 'toolbar=1,scrollbars=1,location=1,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
	if(window.focus) {newwindow.focus()}
  }

function confirmMsg(msg)
{
  inbox = confirm(msg);
  return(inbox);
}

function logout(skip){
	window.location = 'index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out."';
}

function go2(skip){
	if(skip == false) {
		alert ("You will be automatically logged out in 2 minutes if you don't save data or refresh screen");
		window.refresh();
	}
	window.setTimeout("go2(false)", <?php echo $warningtime ?> * 1000); // 1000 is for every min or 1 sec
	window.setTimeout("logout(false)", <?php echo $timeout ?> * 1000); // 1000 is for every min or 1 sec
}

go2(true);
-->
</script>
<script>
<?php echo $js ?>
</script>
<script>
var countDownInterval=<?php echo $timeout ?>;
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

</head>
	<body marginheight="0" topmargin="0" vspace="0"
	marginwidth="0" leftmargin="0" hspace="0" style="margin:0; padding:0">
	<table border=0 cellpadding=0 cellspacing=0>
	
	<tr><td colspan=3 valign=top nowrap><br><?php include("header.inc") ?></td></tr>
	<tr><td colspan=3 valign=top><img src="images/cleardot.gif" height="10"></td></tr>
	
	<tr><td width=10>
	<img src="images/cleardot.gif" height="1" width="10" border="0" alt="spacer">
	</td>
	<td valign=top width=90>
	<?php include("leftside.inc") ?><br>
	<img src="images/cleardot.gif" height="1" width="100" border="0" alt="spacer">
	</td>
	<td valign=top align=left width=600><br><?php echo $body ?></td></tr>
	
	<tr><td colspan=2></td><td><br><br><?php include("footer.inc") ?></td></tr>
	</table>
	<script language="JavaScript" type="text/javascript" src="wz_tooltip.js"></script>
	</body>
</html>
