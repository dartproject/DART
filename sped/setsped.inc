<?php

$id = $_GET['studentid'];
$val = $_GET['sped'];

$sql="UPDATE student set sped='$val' where studentid='$id'";
echo $sql;
$db->query($sql);

?>