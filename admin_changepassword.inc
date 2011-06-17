<?php
    $id = $_POST['id'];
    $password = $_POST['p1'];

    admin_changepassword ($id, $password);

    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=adminListUsers\">");


?>