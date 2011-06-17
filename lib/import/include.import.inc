<?php

// function definition stat here
function DefineImportButton($title, $table, $tablefields)
{

$titl = trim($title); 
$tabl = trim($table);
$tablefield = trim($tablefields);

// output the required javascript for opening new window
$str .= <<< JAVASCRIPT
<script type="text/javascript" language="JavaScript">
// <![CDATA[
function newImport()
{
   var url = 'index.php?cmd=importWin&table=$tabl&tablefields=$tablefield';
   var name = 'importCSVWin';
   var windowProperties =  'toolbar=no,location=no,status=yes,menubar=no,scrollbars=yes,resizable=yes,width=600,height=450';
   window.open(url,name,windowProperties);
}
// ]]>
</script>
JAVASCRIPT;



// output the button code
$str .= '<input type="button" value="'. $titl .'" onclick="newImport();" />';

return($str);

}

?>