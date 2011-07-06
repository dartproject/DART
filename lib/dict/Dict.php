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
 * Description of Dict
 *  Retieves dictionaries stored in JSON files in config/dict
 * 
 * 
 * @author Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 */
class Dict {
    
    CONST DICTIONARY_PATH = "/../../config/dict/";
    
    public static function getDict($dictType){
        
        $dictFile = dirname(__FILE__) . self::DICTIONARY_PATH .
                $dictType;
        
        if (!file_exists($dictFile))
            throw new Exception("Template " . $dictFile .
                    " not found");

        $json = file_get_contents($dictFile);

        return json_decode($json, true);
    }
}

?>
