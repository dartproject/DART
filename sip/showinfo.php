<?php

$data = $HTTP_POST_VARS;


saveactions($data['rid'], $data['raction'], $data['rperson'], $data['rkind'], $data['rtimeline'], $data['reval'], $data['rfinal']);


function saveactions($id, $action, $person, $kind, $timeline, $eval, $final) {
  for ($i = 0; $i < count($id); $i++) {
  	echo ($id[$i] . $action[$i] . $person[$i] . $kind[$i] . $timeline[$i] . $eval[$i] . $final[$i] . "<br>");
  }
}

	while(list($var, $val) = each($HTTP_POST_VARS)) {
		if(is_array($val) ) {
			echo ("$var => " . print_r ($val, true));
		} else {
       		echo("var $var => $val <br>");
       	}
	}
?>