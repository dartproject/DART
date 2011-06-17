<?php

$url = $_SERVER['PHP_SELF'];

$name = $_POST['name'];

if($name == "save") {
	$field = $_POST['field'];
	$sid = $_POST['sid'];
	$body = $_POST['body'];
	
	saveField($sid, $field, $body);
	// Add Saving things here
	echo <<<END
	<script>
	  window.opener.location.reload(true);
	  self.close();
	</script>
END;

} else {

	// Add getting things here
	$field = $_GET['field'];
	$sid = $_GET['sid'];
	$title = $_GET['title'];
	
	$value = getField($sid, $field);
	
	echo <<<END
		   $title
		   <form  name="editform" method="post" action=$url?module=sip&cmd=sipedit>
				<input type=hidden name="sid" value="$sid">
				<input type=hidden name="module" value="sip">
				<input type=hidden name="cmd" value="sipedit">
				<input type=hidden name="field" value="$field">
				<textarea name=body cols=60 rows=10>$value</textarea><br>
				<input type=submit name="name" value='save'> 
				<input name="reset" type="reset" value="Reset">
				<input name="cancel" type=button value='Cancel' onClick="javascript:window.close()">
			</form>
END;
}


/**********
<script>
<!-- Begin
  function popUp(URL, x, y) {
  	self.name = "listings"; // names current window as "listings"
	newwindow = window.open(URL, 'name', 'toolbar=1,scrollbars=1,location=1,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
	if(window.focus) {newwindow.focus()}
  }

  function confirmMsg(msg)
  {
		return(input_box=confirm(msg));
  }

// End -->
</script>

echo <<<END
	<a href='#' onClick='javascript:popUp("http://localhost/dart_current/index.php?module=sip&cmd=sipedit", 550, 450);'>Popup</a> 
END;

********/
?>