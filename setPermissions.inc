<?php

     $id = $_GET['id'];

     $privA = intval($_GET['privA']);
    $scopeA = intval($_GET['scopeA']);

$value = Privilege(A30);

if($value != 'district') { NoPriv("denied Edit", "priv=$value"); }
else {
    updatePremissions ($privA, $scopeA, $id);
}

 echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=permissions&user=$id\"> ");

?>
