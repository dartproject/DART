<?php

    $id = $_POST['id'];


    saveLevels ($HTTP_POST_VARS);
if($debug <> "on") {    
    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=StudentEdit&id=$id\"> ");
}
?>
