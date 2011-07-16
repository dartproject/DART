<?php

/*
 *  Copyright (C) 2011 Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 * 
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

include_once ("lib/machine.config.php");
include_once ("lib/config.inc");
include_once ("lib/ez_sql.php");
include_once ("lib/function.inc");
include_once ("lib/PasswordHash.php");

require_once('lib/swift/swift_required.php');

session_start();

$config = parse_ini_file('config/config.ini');

//check is user logged in
if (isset($_SESSION['sessionUserID'])) {
    $loggedInUser = new User($_SESSION['sessionUserID'], $db);

    $toEmail = $config['SEF_Recipient_Email'];
    $toName = $config['SEF_Recipient_Name'];

    //create message body
    $body = "";

    foreach ($_POST as $key => $value) {
        $body .= "<b>$key:</b> $value <br/>";
    }

    $body .="<br/><br/>";
    $body .="<b>Sent by <br/> Name: </b>" . $loggedInUser->getName() . " <br/>
            <b>Login: </b>" . $loggedInUser->getLogin() . "<br/>
            <b>Email: </b>" . $loggedInUser->getEmail();
    
    //create message
    $message = Swift_Message::newInstance()
            ->setSubject("New Student Enrollment")
            ->setTo(array($toEmail => $toName))
            ->setFrom(array($loggedInUser->getEmail() => $loggedInUser->getName()))
            ->setBody($body, 'text/html')
            ->addPart('$body', 'text/plain');

    //check whether SSL connection
    if ($config['SMTP_SSL'] == 'Y')
        $transport = Swift_SmtpTransport::newInstance($config['SMTP_SERVER'], $config['SMTP_PORT'], 'ssl');
    else
        $transport = Swift_SmtpTransport::newInstance($config['SMTP_SERVER'], $config['SMTP_PORT']);

    //set credentials
    $transport->setUsername($config['SMTP_USERNAME']);
    $transport->setPassword($config['SMTP_PASSWORD']);

    $mailer = Swift_Mailer::newInstance($transport);

    //send message
    $result = $mailer->send($message);

    $response = array();
    $response['success'] = $result == 1 ? true : false;
    $response['msg'] = $response['success'] ? 'Form successfully sent' :
            'Unable to send form. Please contact administrator';
    $response['title'] = $response['success'] ? 'Form sent.' : 'Form not sent';
} else {
    $response = array();
    $response['success'] = false;
    $response['title'] = 'Unable to send form';
    $response['msg'] = "Please login to send the form";
}
echo json_encode($response);
?>