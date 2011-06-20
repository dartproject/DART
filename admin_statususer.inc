<?php
    $id = $_POST['id'];
    $status = $_POST['p1'];

    admin_statusUser ($id, $status);

   echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=adminListUsers\">");


?>
