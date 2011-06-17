<?php

    $id = $_POST['id'];
    
    saveGrades ($HTTP_POST_VARS);


    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=StudentEdit&id=$id\">");


?>
