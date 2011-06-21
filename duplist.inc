<?php
        $listid = $_GET['listid'];
        debugPrint ("Start duplist");
        $id = dupList($listid);
        debugPrint ("Finished duplist");
        header("Location: http://localhost/dartnew/index.php?cmd=editlist&p1=$id");
//        echo ("<html><body OnLoad=\"javascript: history.back();\" bgcolor=\"#F0F0F0\"></body></html>");
        
?>
