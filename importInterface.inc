<?php

echo <<<END
This will allow the import of a csv file to the loadTable:<br>

<form enctype="multipart/form-data" name=upload method=post action=index.php?cmd=ImportFile>
<input  type="file" name="importfile" class="textfield" /><br>
Number Columns<input type="text" size=3 name=colnum><br>
Fields Terminated By <input  type="text" size = 3 name="fieldterminate" value = ','/> <br>
Fields Enclosed By <input  type="text" size = 3 name="enclosed" value='"'/> <br>
Lines Terminated By <input  type="text" size = 3 name="lineterminate" value='\\n' /> <br><br>


<input type=submit name=activity value=Upload/Submit></form><br><br>
END;

?>
