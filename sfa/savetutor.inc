<?php

    $tutor = $_POST['tutor'];
    $submit = $_POST['submit'];
    $quarter = $_POST['quarter'];
    $year = $_POST['year'];
    saveTutorTime ($HTTP_POST_VARS);
    
    if($debug <> "on") {
        if($submit == 'save home') {
           echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?module=sfa&cmd=sfahome\">");
        } else {
           echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL='index.php?module=sfa&cmd=tutor&tutor=$tutor&quarter=$quarter&year=$year'\">");
        }
    } else {
        echo ("<a href=index.php?module=sfa&cmd=tutor&tutor=$tutor&quarter=$quarter&year=$year>Go To Page</a><br>");
    }


?>
