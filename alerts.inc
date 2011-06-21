<?php

global $db;

emptyAlertTable();

/************** Collect Area Levels to Progress ***************/

$alertProgress = alertAreaLevels();

echo ("<br>Area Levels Alerts: " . count($alertProgress) );

foreach ($alertProgress as $alert) {
  $id = $alert->studentid;
  $subject = $alert->subject;
  $level = $alert->level;
  $progress = $alert->progress;
  $userid = $alert->userid;
  $uname = $alert->uname;
  $uemail = $alert->uemail;
  $sname = $alert->lname . ", " . $alert->fname;
  $note = "      $sname ($id) $subject.$level = $progress";
  
  $alert1[$userid]['name'] = $uname;
  $alert1[$userid]['uemail'] = $uemail;
  $alert1[$userid]['note1'] .= "$note\n";
 
  $sql = "insert alerts 
                SET type = 'Level Progress',
                    studentid = '$id',
                    subject = '$sbject',
                    level = '$level',
                    userid = '$userid',
                    username = '$uname',
                    useremail = '$uemail',
                    note = '$note' ";
                    
   debugPrint ("<br>$sql");
                   
   $db->get_results($sql);
//   return($db->insert_id )
}

/************** Collect Toggle Not Changed ***************/

$tm = time();

$alertToggle = alertToggles($tm);
echo ("<br>Toggle Not Changing Alerts: " . count($alertToggle) );
foreach ($alertToggle as $alert) {
  $id = $alert->studentid;
  $subject = $alert->subject;
  $level = $alert->level;
  $progress = $alert->progress;
  $userid = $alert->userid;
  $uname = $alert->uname;
  $uemail = $alert->uemail;
  $sname = $alert->lname . ", " . $alert->fname;
  $ch_name = $alert->change_username;
  $ch_time = date($dateSettings, $alert->change_timestamp);
  $note = "      $sname ($id) $subject.$level = $progress : Last Change ($ch_name [$ch_time])";

  $alert1[$userid]['name'] = $uname;
  $alert1[$userid]['uemail'] = $uemail;
  $alert1[$userid]['note2'] .= "$note\n";

 
  $sql = "insert alerts 
                SET type = 'Toggle Change',
                    studentid = '$id',
                    subject = '$sbject',
                    level = '$level',
                    userid = '$userid',
                    username = '$uname',
                    useremail = '$uemail',
                    note = '$sname ($id) $subject.$level = $progress : Last Change ($ch_name [$ch_time])' ";
                    
   debugPrint ("<br>$sql");
                   
   $db->get_results($sql);
//   return($db->insert_id )
}

/*************** Send Out Toggle Email **********************/

echo ("<br><br>");

foreach ($alert1 as $alert) {
  $name = $alert['name'];
  $email = $alert['uemail'];
  $note1 = $alert['note1'];
  $note2 = $alert['note2'];

  $mailmessage = "Dear $name\n
  Students that need to be progressed:\n$note1\n
  Students that have not been toggled in a certain time frame:\n$note2\nSincerely,\nDART ALERT SYSTEM";
  
  $header = "To: $name <$uemail>\nFrom: automated@bssd.org\nSubject: Current Warnings\n\n";
  
  
 echo ( "<hr>" . str_replace(" ", " &nbsp; ", str_replace("\n", "<br>\n", htmlspecialchars($header. $mailmessage))));
}

?>
