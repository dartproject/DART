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
 * Description of AYP - Annual Year Progress
 * Used in District/Site Improvement Plan Report districtrep.inc/siterep.inc
 * for storing values for not met AYPs
 *
 * @author Bolek Kurowski
 */
class AYP {

    public $name;
    public $allStudents;
    public $ethnicGroups;
    public $SWD;
    public $LEP;
    public $lowIncome;

    public function __construct($name, $allStudents, $ethnicGroups, $SWD, $LEP, $lowIncome) {
        $this->name = $name;
        $this->allStudents = $allStudents;
        $this->ethnicGroups = $ethnicGroups;
        $this->SWD = $SWD;
        $this->LEP = $LEP;
        $this->lowIncome = $lowIncome;
    }
}

?>
