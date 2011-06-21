<?php

    $listid = $_POST['listid'];
    $submit = $_POST['submit'];
    $year = $_POST['year'];
    saveSFAScores ($_POST);
    
    if($debug <> "on") {
        if($submit == 'save home') {
           echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?module=sfa&cmd=sfahome\">");
        } else {
           echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL='index.php?module=sfa&cmd=sfainput&listid=$listid&year=$year'\">");
        }
    } else {
        echo ("<a href=index.php?module=sfa&cmd=tutor&tutor=$tutor>Go To Page</a><br>");
    }


?>
