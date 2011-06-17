<HTML><HEAD><TITLE>Popup Window Demo</TITLE>

<script>

/*******Popup Window Definition*********************/

var htmlOpener = "<html><head><title>Popup Window Demo</title>"+
			"</head><body bgcolor='navyblue'><p>"
var htmlCloser = "</body></html>"

 demo = "<center><b>Popup Window</b></center><p>Here you can put any legal"+
        " html string. For example, you can put a graph here. <center>"+
        " <p><img src="corr.gif"></center>"

 body = "<html><body>
<form method=post name=feedback action=index.php>
<input type=hidden name=cmd value=sendFeedback>
<table><tr><td>Please send any comment you have.<br>
<textarea rows=10 cols=30 name=feedback></textarea><br>
<center><input type=submit name=sendButton value=Send></center>
</td></tr></table>
</form></body></html>"

/****END OF STRING DEFINITION*****/


 var popupWin
 var wholeWin
  function popup(term)  // write corresponding content to the popup window
  {
   popupWin = window.open("", "puWin",  "width=480,height=200,scrollbars,dependent,resizable");
   popupWin.document.open("text/html", "replace"); 
   popupWin.document.write(htmlOpener);
   popupWin.document.write(term);
   popupWin.document.write(htmlCloser);
   popupWin.document.close();  // close layout stream
   popupWin.focus();  // bring the popup window to the front
  }
 
  function closeDep() {
  if (popupWin && popupWin.open && !popupWin.closed) popupWin.close();
  if (wholeWin && wholeWin.open && !wholeWin.closed) wholeWin.close();

 }
</script>

</HEAD>
<BODY onUnload="closeDep()">
<H3>Popup Window Demo</H3>
<center>Click <a href="javascript:popup(body)">here</a> to see a body popup window. </center>
<center>Click <a href="javascript:popup(demo)">here</a> to see a demo popup window. </center>
</BODY>
</HTML>


<?php
/****
$body = "<html><body>
<form method=post name=feedback action=index.php>
<input type=hidden name=cmd value=sendFeedback>
<table><tr><td>Please send any comment you have.<br>
<textarea rows=10 cols=30 name=feedback></textarea><br>
<center><input type=submit name=sendButton value=Send></center>
</td></tr></table>
</form></body></html>";

echo $body;
****/
?>
