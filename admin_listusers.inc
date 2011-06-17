<?php

$list = admin_getUsers();

$body = "<br><br><br><table border=1><tr><td>name</td><td>User</td><td>Password</td><td>status</td><td colspan=3>operations</td></tr>";

foreach ($list as $user) {
    $body .=  "<tr><td>" . $user['name'] . "</td><td>" .  $user['user'] . "</td><td>" .  $user['pwd'] . "</td><td>" .  $user['status'] . "</td><td align=center>" .admin_statusForm ($user['userid'], 'active') . "</td><td>" . admin_statusForm ($user['userid'], 'inactive') . "</td><td>" . admin_formPwd($user['userid']) . "</td></tr>";
}

$body .= "</table><br><br>";

$body .= "<form name=addUser method=post action=index.php?cmd=adminAddUser>
          Name: <input type=text name=name>
          User Name: <input type=text name=user>
          Password: <input type=password name=password>
          <input type=submit value=add></form>" ;


include ("template.inc");

?>