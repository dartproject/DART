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
 * Description of DictType
 * Specifies types of dictionaries and their json file (stored in /config/dict)
 * 
 * @author Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 */
class DictType {
    CONST ETHNICITY             = "ethnicity.json";
    CONST TESTING_LEVELS        = "testingLevels.json";
    CONST GENDER                = "gender.json";
    CONST STATUS                = "status.json";
    CONST PARENT_WITH_STUDENT   = "parentwstudent.json";
}

?>