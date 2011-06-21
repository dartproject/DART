<?php
    $listID = $_GET['p1'];

    deleteList($listID);

    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=home\">");


?>
