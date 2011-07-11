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
 * Description of Privileges
 *
 * @author Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 */
class Privileges {
    CONST TOGGLE_INFO_VIEW = 'A2';                      //A2
    CONST TOGGLE_INFO_EDIT = 'A4';                      //A3
    CONST STUDENT_BASIC_INFO_VIEW = 'A8';               //A4
    CONST STUDENT_BASIC_INFO_EDIT = 'A16';              //A5
    CONST STUDENT_INFO_EDIT = 'A32';                    //A6
    CONST SFA_VIEW = 'A64';                             //A7
    CONST REPORT_CARD_NOTES = 'A128';                   //A8
    CONST SFA_EDIT = 'A256';                            //A9
    CONST HISTORY_VIEW = "A512";                        //A10
    CONST GROUPS = 'A1024';                             //A11
    CONST SITE_SHARED_GROUPS_VIEW = 'A2048';            //A12
    CONST PROMOTE_STUDENTS = 'A4096';                   //A13
    CONST SITE_SHARED_GROUPS_EDIT = 'A8192';            //A14
    CONST SIP_VIEW = 'A16384';                          //A15
    CONST SIP_EDIT = 'A32768';                          //A16
    CONST ATTENDANCE_LISTS = 'A65536';                  //A17
    CONST REPORT_CARD_BROWSER = 'A131072';              //A18
    CONST SCHOOL_CALENDAR = 'A262144';                  //A19
    CONST PROGRESS_REPORT = 'A524288';                  //A20
    CONST DISCIPLINE = 'A1048576';                      //A21
    CONST PACING_GUIDE = 'A2097152';                    //A22
    CONST MOVE_STUDENT = 'A4194304';                    //A23
    CONST REPORT_CARD = 'A8388608' ;                    //A24
    CONST LEVEL_INFORMATION_EDIT = 'A16777216';         //A25
    CONST PIVOT_TABLE_DATA_VIEW = 'A33554432';          //A26
    CONST STUDENT_SEARCH_VIEW_EXPORT = 'A67108864';//A27
    CONST SITE_NOTES_VIEW = 'A134217728';               //A28
    CONST SITE_NOTES_EDIT = 'A268435456';               //A29
    CONST USER_ACCESS_SETTINGS = 'A536870912';          //A30

    CONST SPED = 'B2';                                  //B2
    /**
     * Allow to view the dashboard
     */
    CONST DASHBOARD_VIEW = 'B4';                        //B3
    CONST DRILLDOWN_DASHBOARD_VIEW = 'B8';              //B4
    CONST DISCIPLINE_EXPORT = 'B16';                    //B5
    CONST ATTENDANCE_EXPORT = 'B32';                    //B6
    CONST ENTER_EXIT_EXPORT = 'B64';                    //B7
    CONST FALL_OASIS_EXPORT = 'B128';                   //B8
    CONST ADDITIONAL_TRANSCRIPT_INFO = 'B256';          //B9
    CONST BIG_RED_BUTTON = 'B512';                      //B10
    CONST STANDARD_INFORMATION_EDIT = 'B1024';          //B11
    CONST TRANSCRIPTS_MANAGE = 'B2048';                 //B12
    CONST VIEW_TESTING_MODULE = 'B4096';                //B13
    CONST EDIT_TESTING_MODULE = 'B8192';                //B14

    /**
     * Check whether the given User privileges ($uPrivilege) has a specific
     * privilege ($privilege)
     * 
     * @param type $uPrivilege
     * @param type $privilege
     * @return boolean
     */
    public static function check($uPrivileges, $privilege) {
        if (isset($uPrivileges[substr($privilege, 0, 1)]))
            return((int) $uPrivileges[substr($privilege, 0, 1)]->getValue() &
            (int) substr($privilege, 1, strlen($privilege)));
        else
            return false;
    }

    /**
     * Checks the user permissions by scope and privilege.
     * Return 'true' if user was granted the checked permission.
     * Return 'false' if user was not granted the checked permission
     * 
     * @param UPrivilege[] $uPrivilege - array of UPrivileges
     * @param int const $pScopeType - PScopeType (e.g. PScopeType::DISTRICT)
     * @param string $privilege  - privilege type (e.g. PRIVILEGES::TOGGLE_INFO_VIEW)
     * @return boolean
     */
    public static function checkScope($uPrivilege, $pScopeType, $privilege) {
        if (Privileges::check($uPrivilege, $privilege))
            return FALSE;
        else {
            return $pScopeType == ($uPrivilege[$privilege['type']]->getScope() & $privilege['value']);
        }
    }

}

?>
