
<?php



$B2Priv = PrivilegeB(B2);



$moduleleft .= $B2Priv != 'none' ? "<br><b>Special Ed</b><br>

  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">
	 <a href=index.php?module=sped&cmd=spedlist>List</a><br>
  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">
  	<a href=index.php?module=sped&cmd=spedhistory>History</a><br>
  
  
  
  " : "";

  

//$moduleleft = "-$A7Priv- SFA<br>";

?>