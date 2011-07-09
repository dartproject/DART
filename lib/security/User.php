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
 * Description of User
 *
 * @author Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 */
class User {
    private $_name;
    private $_login;
    private $_id;
    private $_siteID;
    private $_status;
    private $_email;
    private $_role;
    
    private $_db;
    
    // <editor-fold defaultstate="collapsed" desc="Getters">
    public function getName(){
        return $this->_name;
    }
    
    public function getID(){
        return $this->_id;
    }
    
    public function getLogin(){
        return $this->_login;
    }
    // </editor-fold>
    
    public function __construct($UserID, $db) {
        $this->_id = $UserID;
        $this->_db = $db;
        
        getUser($UserID);
        
    }
    
    private function getUser($UserID){
        $query = 'SELECT user, name, status, site,email, type 
            FROM user WHERE userID="' . mysql_real_escape_string($UserID) . '";';
        
        $result = $db->get_results($query);
        
        if(count($result)==1){
            $this->_name    = $result[0]->name;
            $this->_login   = $result[0]->user;
            $this->_siteID  = $result[0]->site;
            $this->_status  = $result[0]->status;
            $this->_email   = $result[0]->email;
            $this->_role    = $result[0]->role;
        }else{
            throw new Exception('User not found.');
        }
    }
    
    
    
    
    
}

?>
