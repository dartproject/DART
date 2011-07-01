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

/*
 * Smarty plugin
 * -------------------------------------------------------------
 * File:     modifier.age.php
 * Type:     modifier
 * Name:     age
 * Purpose:  Converts a person's birthday to age in the following
 * format [years]y [months]m [days]d
 * -------------------------------------------------------------
 */
function smarty_modifier_age($date_of_birth)
{
    if ($date_of_birth != 0) {
        $dayinseconds = 24 * 60 * 60;
        $dayinYear = 0.00273972602739726;

        $dif = time() - strtotime($date_of_birth);

        $age_in_days = $dif / $dayinseconds;

        $flt_year = $age_in_days * $dayinYear;
        $year = floor($flt_year);

        $flt_month = ($flt_year - $year) * 12;
        $month = floor($flt_month);

        $flt_day = ($flt_month - $month) * 30.58;
        $day = floor($flt_day);

        return $year . "y " . $month . "m " . $day . "d";
    } else {
        return("unk");
    }
}
?>
