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
 * Description of SIPReport
 *
 * @author Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 */
require_once("EmphasisArea.php");
require_once("GAPlan.php");
require_once("AYP.php");
require_once("StateQuestionResponse.php");

class IPReport {

    public $year;

    public $intro;
    //String
    public $subjectsInOrderOfStrength;
    //String
    public $strongestWeakestGrades;
    //Array of EmphasisArea
    public $emphasisAreas;
    //Array of AYP
    public $notMetAYPs;
    public $stateQ2Response;
    public $stateQ3Response;
    public $stateQ4Response;
    //Array of GAPlan
    public $GAPlans;

    public function __construct($year, $db, $site=null) {
        $this->year = $year;

        $sip = $this->getData($year, $db, $site);


        while (list($var, $val) = each($sip))
            ${$var} = $val;


        $this->intro = $district;
        $this->subjectsInOrderOfStrength = $subjectorder;
        $this->strongestWeakestGrades = $graderating;

//******************************************************************************
// Specific Areas of Emphasis **************************************************
//******************************************************************************
        $this->emphasisAreas = array();
        array_push($this->emphasisAreas, new EmphasisArea("Reading", $emphasisR));
        array_push($this->emphasisAreas, new EmphasisArea("Writing", $emphasisW));
        array_push($this->emphasisAreas, new EmphasisArea("Math", $emphasisM));

//******************************************************************************
// State Questions and Responses ***********************************************
//******************************************************************************
//******************************************************************************
//          1. Not Met AYPs
//******************************************************************************
        $languageArts = new AYP("Language Arts", $g11, $g12, $g13, $g14, $g15);
        $math = new AYP("Math", $g21, $g22, $g23, $g24, $g25);
        $participation = new AYP("Participation", $g31, $g32, $g33, $g34, $g35);
        $graduationRate = new AYP("Graduation Rate", $g41, $g42, $g43, $g44, $g45);

        $this->notMetAYPs = array($languageArts, $math, $participation, $graduationRate);

//******************************************************************************
//          2. Why not met
//******************************************************************************

        $this->stateQ2Response = new StateQuestionResponse($stateques, $link);

//******************************************************************************
//          3. Describe how notify parents
//******************************************************************************

        $this->stateQ3Response = new StateQuestionResponse($ques3, $link3);

//******************************************************************************
//          4. Describe technical assistance
//******************************************************************************

        $this->stateQ4Response = new StateQuestionResponse($ques4, $link4);

//******************************************************************************
//   GOALS & ACTION PLANS ******************************************************
//******************************************************************************
        $readingPlan = new GAPlan("Reading");
        $writingPlan = new GAPlan("Writing");
        $mathPlan = new GAPlan("Math");
        $interventionPlan = new GAPlan("Intervention");

//******************************************************************************
//          1. District Measurable Goal
//******************************************************************************

        $readingPlan->districtMeasurableGoal = $r1;
        $writingPlan->districtMeasurableGoal = $w1;
        $mathPlan->districtMeasurableGoal = $m1;
        $interventionPlan->districtMeasurableGoal = $i1;

//******************************************************************************
//          2.  Current Performance Level on SBA
//******************************************************************************

        $readingPlan->currentSBA = $r2;
        $writingPlan->currentSBA = $w2;
        $mathPlan->currentSBA = $m2;
        $interventionPlan->currentSBA = $i2;

//******************************************************************************
//          3. Performance Target
//******************************************************************************

        $readingPlan->performanceTarget = $r3;
        $writingPlan->performanceTarget = $w3;
        $mathPlan->performanceTarget = $m2;
        $interventionPlan->performanceTarget = $i3;

//******************************************************************************
//          3. Research Support
//******************************************************************************

        $readingPlan->researchSupport = $r4;
        $writingPlan->researchSupport = $w4;
        $mathPlan->researchSupport = $m4;
        $interventionPlan->researchSupport = $i4;

//******************************************************************************
//      Action Plans & Evaluations
//******************************************************************************
        $readingPlan->actionPlans = $this->getActionPlan($db, $sid, 'r');
        $writingPlan->actionPlans = $this->getActionPlan($db, $sid, 'w');
        $mathPlan->actionPlans = $this->getActionPlan($db, $sid, 'm');
        $interventionPlan->actionPlans = $this->getActionPlan($db, $sid, 'i');

        $this->GAPlans = array($readingPlan, $writingPlan, $mathPlan, $interventionPlan);
    }

    private function getData($year, $db, $site=null) {
        if ($site == null)
            return $db->get_row("select * from sip, sipaux where kind='district'
                                and year = '$year' and id = sid ");
        else
            return $db->get_row("select * from sip, sipaux where kind='site' and
                    year = '$year' and id = sid and sip.site = '$site' ");
    }

    private function getActionPlan($db, $sid, $area) {
        return $db->get_results("select * from sipaction where sid = '$sid' and area = '$area' ", ARRAY_A);
    }

}

?>
