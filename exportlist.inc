<?php
        $listid = $_GET['listid'];
        $type = $_GET['type'];
        debugPrint ("Start exportlist");
        $fn = exportList($listid, $type);
        debugPrint ("Finished exportlist");
        if($debug <> "on") {  
           echo ("<html><body OnLoad=\"javascript: history.back();\" bgcolor=\"#F0F0F0\"></body></html>");
        }
?>
