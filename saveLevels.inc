<?php

    $id = $_POST['id'];

    saveLevels ($_POST);
if($debug <> "on") {    
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=StudentEdit&id=$id\"> ");
}
?>
