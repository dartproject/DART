<?php

include_once("lib/pdf_functions.php");

$file_path = "exp/$currentUserID.pdf";
$file_name = getValue($_GET, "file", $currentUserID);

exportPDFFile($file_path, $file_name);

?>
