<?php

echo "Importing grades file: <form enctype=\"multipart/form-data\" name=upload method=post action=index.php?cmd=uploadUpdate>
<input type=hidden name=id value=$id>
<input type=hidden name=type value=grades>
<input  type=\"file\" name=\"gradefile\" class=\"textfield\" />
<input type=submit name=activity value=Upload></form><br><br>";

echo "Importing studentlevel file: <form enctype=\"multipart/form-data\" name=upload method=post action=index.php?cmd=uploadUpdate>
<input type=hidden name=id value=$id>
<input type=hidden name=type value=studentlevel>
<input  type=\"file\" name=\"gradefile\" class=\"textfield\" />
<input type=submit name=activity value=Upload></form><br><br>";

echo "Importing student attendance: <form enctype=\"multipart/form-data\" name=upload method=post action=index.php?cmd=uploadUpdate>
<input type=hidden name=id value=$id>
<input type=hidden name=type value=attendance>
<input  type=\"file\" name=\"gradefile\" class=\"textfield\" />
<input type=submit name=activity value=Upload></form>";

?>
