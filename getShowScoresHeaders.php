<?php

include_once 'ListMembers.php';

$subjects = getCoreSubjects();
$results = array("totalCount" => count($subjects), "success" => true, "headers" => $subjects);

echo json_encode($results);

?>
