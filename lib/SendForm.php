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

/**
 * Description of SendForm
 *
 * @author Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 */
require_once('swift/swift_required.php');

class SendForm {

    public $subject;
    public $fromEmail;
    public $fromName;
    public $body;

    public function send($config) {
        
        $toEmail = $config['SEF_Recipient_Email'];
        $toName = $config['SEF_Recipient_Name'];
        //create message
        $message = Swift_Message::newInstance()
                ->setSubject($this->subject)
                ->setTo(array($toEmail => $toName))
                ->setFrom(array($this->fromEmail => $this->fromName))
                ->setBody($this->subject, 'text/html')
                ->addPart($this->body, 'text/plain');

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

        return $result;
    }

}

?>
