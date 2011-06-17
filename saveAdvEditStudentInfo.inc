<?php

    $id = $_POST['id'];


    saveAdvEditStudentInfo ($_POST);

    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=toggleStudent&p1=$id\"> ");


?>
