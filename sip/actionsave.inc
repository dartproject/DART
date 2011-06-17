<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


$value = $_POST['value'];
$id = $_POST['id'];

$sql = "update action set value = '$value' where id = '$id'";

echo $sql;

$db->get_results($sql);

?>