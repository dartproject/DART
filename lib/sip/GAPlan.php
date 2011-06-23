<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of GAPlan
 *
 *
 *
 * @author Bolek
 */
class GAPlan {

    public $emphasisArea;
    public $districtMeasurableGoal;
    public $currentSBA;
    public $performanceTarget;
    public $researchSupport;
    public $actionPlans;

    public function __construct($emphasisArea) {
        $this->emphasisArea = $emphasisArea;
    }

}
?>
