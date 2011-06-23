<?php

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
