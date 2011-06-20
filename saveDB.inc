<?php


$value = $_GET['val'];
$spec = $_GET['spec'];

$def = explode("-", $spec);

$table = $def[0];
$fieldid = $def[1];
$id = $def[2];
$field = $def[3];
$cid = $def[4];

$sql = "UPDATE $table SET $field = '$value' WHERE $fieldid = '$id' ";
$db->get_results($sql);

echo $sql;


?>
