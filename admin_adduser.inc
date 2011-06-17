<?php
    $name = $_POST['name'];
    $user = $_POST['user'];
    $password = $_POST['password'];

    if (admin_addUser ($name, $user, $password)) {

    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=adminListUsers\">");
     } else {
       $body = "Error in inputing user please input again<br>";
       $body .= "<form name=addUser method=post action=index.php?cmd=adminAddUser>
          Name: <input type=text name=name>
          User Name: <input type=text name=user>
          Password: <input type=password name=password>
          <input type=submit value=add></form>" ;
       $body .= "<a href=index.php?cmd=adminListUsers>Go To Users</a>";

          include ("template.inc");
     }



?>