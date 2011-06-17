<?php
debugPrint("U:" . $userID . "<br>", 1);
debugPrint("S:" . $siteID . "<br>", 1);
?>

<script language="JavaScript">

var sURL = unescape(window.location.pathname);

function refresh(value)
{
    alert(sURL);
    window.location.href = sURL+"&mytype="+value;
    window.location.reload( true );
}
</script>
<?php
/**************************
$mySite = $_POST['mytype'];
$myCurrentSite = (isset($mySite) and $mySite != "") ? $mySite : "UNK";

$siteSelection = $mySite;
$myCurrentSite = "SKK";
// action=\"javascript:refresh(mytype.value);\">
$siteSelection = "<form style=\"margin-bottom:0;\" name=updateSharedGroup method=get action=\"javascript:refresh( true );\">
      <select name=mytype onChange='submit()'>
            <option value=\"\"" . selected("", $mySite) . "></option>
            <option value=\"self\"" . selected("self", $mySite) . ">self</option>
            <option value=\"UNK\"" . selected("UNK", $mySite) . ">UNK</option>
       </select>&nbsp;

      </form>";
*************************/
$myCurrentSite = "UNK";
    
$sharedGroups =      
    "<font color=\"#0066ff\"><b>Shared Groups<br>$currentMySite</b></font><br>"
    . showMyList($currentUserID, '<img src="http://dart.bssd.org/images/10_h.gif" alt="" height="2" width="10" border="0">','<font color="#0066ff"><br>', $myCurrentSite) . "
      <br>";

?>
<div align="left">
		<b><font color="#0066ff">Logged In As:</font></b><br>
		<img src="http://www.bssd.org/images/dart1.gif" alt="" height="67" width="77" border="0"><br>
		<b><font color="#0066ff"><?php echo $currentUserName; ?></font></b><br>

		  <br><b><font color="#0066ff">DART Info<br></font></b>
		  <img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=logout">Log Out</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=home">Dart Home</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=feedback" target=_blank>Feedbak</a><br>			
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=search">Search</a><br>
			<br>
			<font color="#0066ff"><b>My Groups</b></font><br>		
      <?php echo showMyList($currentUserID, '<img src="http://dart.bssd.org/images/10_h.gif" alt="" height="2" width="10" border="0">','<font color="#0066ff"><br>'); ?>
      <br>

      <?php echo $sharedGroups ?>
      <font color="#0066ff"><b>Manage Groups</b></font><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=newlist">New Group</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=editlist">Edit Groups</a><br>
			<br>
      <font color="#0066ff"><b>Reports</b></font><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=reportsInd">Individual</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=pivot">Drill Down!</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=reportsHist">Historical</a><br>
			<br>
			<font color="#0066ff"><b>Admin Area</b></font><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=userAdmin&site=<?php echo $currentMySite ?>&status=Active">Users <?php echo $currentMySite ?></a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=editNotes">Edit Notes</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=history">History</a><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="(EmptyReference!)">Alerts</a><br>
			
			<br>
			<font color="#0066ff"><b>Testing Area</b></font><br>
			<img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href=http://192.168.25.8/dart/index.php?cmd=permissions&user=208">Permissions Robert</a><br>
		</p>
</div>




