<?php

$A7Priv = Privilege(A7);

$moduleleft .= $A7Priv != 'none' ? "<b>SFA</b><br>
  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">
  <a href=index.php?module=sfa&cmd=sfahome>Home</a><br>
  <img src=\"images/10_h.gif\" alt=\"\" height=\"2\" width=\"10\" border=\"0\">
  <a href='javascript:void(0);' ONCLICK=\"popUp('sfa/sri.html', 550, 650);\">SRI Sheet</a><br><br>
  <script>
<!-- Begin
  function popUp(URL, x, y) {
	newwindow = window.open(URL, 'name', 'toolbar=0,scrollbars=1,location=0,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
	if(window.focus) {newwindow.focus();return false;}
	return false
  }
// End -->
</script>


" : "";
  


  
//$moduleleft = "-$A7Priv- SFA<br>";
?>
