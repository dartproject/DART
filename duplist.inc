<?php
        $listid = $_GET['listid'];
        debugPrint ("Start duplist");
        $id = dupList($listid);
        debugPrint ("Finished duplist");
        header("Location: index.php?cmd=editlist&p1=$id");
?>
