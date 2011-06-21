<?php

$id = $_GET['id'];
$sub = $_GET['sub'];
$lvl = $_GET['lvl'];
$type = $_GET['type'];

debugPrint("HANDLE Level Param: $id, $sub, $lvl, $type<br>");

if($type =="add") {
   addLevel ($id, $sub);
} else if($type =="addall") {
   addLevel ($id, 'CA');
   addLevel ($id, 'CS');
   addLevel ($id, 'LS');
   addLevel ($id, 'MA');
   addLevel ($id, 'RE');
   addLevel ($id, 'SC');
   addLevel ($id, 'SS');
   addLevel ($id, 'TE');
   addLevel ($id, 'WR');
} else if ($type == "delete") {
   deleteLevel ($id, $sub, $lvl);
} else if ($type=="Active") {
    saveStudentValue($id, 'status', 'Active');   
} else if ($type=="Inactive") {
    saveStudentValue($id, 'status', 'Inactive');
}

echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=StudentEdit&id=$id\"> ");


?>
