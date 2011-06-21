<?php

$A15Priv = Privilege(A15);

$moduleleft .= $A15Priv != 'none' ? "<b>SIP</b><br>
  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">
  <a href=index.php?module=sip&cmd=siphome>Home</a><br>" : "";
  
//$moduleleft = "-$A7Priv- SFA<br>";
?>
