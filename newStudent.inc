<?php

$A6Priv = Privilege(A6);

if($A6Priv != 'district') { NoPriv("denied newStudent", "You should not be trying to creating new student. Email sent to admin"); }

    $site = $_GET['site'];
    
    $id = createNewStudent($site);
    
    header("Location: ./index.php?cmd=NewStudentMovement&id=$id");

?>
