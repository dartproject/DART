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
    
    CONST QPIs                  = "qpi.json";
    
    //SEARCH Dictionaries
    CONST SEARCH_SUSPENSIONS    = "search_suspensions.json";
    CONST SEARCH_ATTENDANCE     = "search_attendanceRates.json";

    //DISCIPLINE Dictionaries
    CONST DISCIPLINE_NON_WEAPON  = "discipline_non_weapon.json";
    CONST DISCIPLINE_POLICE      = "discipline_police.json";
    CONST DISCIPLINE_CONSEQUENCE = "discipline_consequence.json";
    CONST DISCIPLINE_LENGTH      = "discipline_length.json";
    CONST DISCIPLINE_STATUS      = "discipline_status.json";
    CONST DISCIPLINE_WEAPON      = "discipline_weapon.json";
    CONST DISCIPLINE_VICTIM      = "discipline_victim.json";
    CONST DISCIPLINE_VICTIM_NO   = "discipline_victim_no.json";
    CONST DISCIPLINE_DISABILITY  = "discipline_disability.json";
    CONST DISCIPLINE_IEP         = "discipline_iep.json";
    CONST DISCIPLINE_SERVICE     = "discipline_service.json";

	//MOVEMENT Dictionaries
    CONST MOVEMENT_ENTRY_TYPES    = "entryTypes.json";
}

?>
