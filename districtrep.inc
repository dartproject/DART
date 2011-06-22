<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//  Modified:   Bolek Kurowski (bkurowsk@andrew.cmu.edu)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

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

/**
 * 
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

$timeframe = $CurrentYear . "-" . substr($CurrentYear + 1, 2, 2);

$smarty->assign('timeframe',$timeframe);

$sip = $db->get_row("select * from sip, sipaux where kind='district' 
        and year = '$CurrentYear' and id = sid ");

while (list($var, $val) = each($sip))
    ${$var} = $val;

//******************************************************************************
// Summary of District Improvement Plan ****************************************
//******************************************************************************

$smarty->assign('subjectsInOrderOfStrength', $subjectorder);
$smarty->assign('strongestWeakestGrades', $graderating);

//******************************************************************************
// Specific Areas of Emphasis **************************************************
//******************************************************************************

$smarty->assign('emphasisR', $emphasisR);
$smarty->assign('emphasisW', $emphasisW);
$smarty->assign('emphasisM', $emphasisM);

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

$notMetAYPs = array($languageArts, $math, $participation, $graduationRate);

$smarty->assign('notMetAYPs', $notMetAYPs);

//******************************************************************************
//          2. Why not met               
//******************************************************************************

$smarty->assign('stateQ2Response', $stateques);
$smarty->assign('stateQ2ResponseLinks', $link);

//******************************************************************************
//          3. Describe how notify parents         
//******************************************************************************

$smarty->assign('stateQ3Response', $ques3);
$smarty->assign('stateQ3ResponseLinks', $link3);

//******************************************************************************
//          4. Describe technical assistance       
//******************************************************************************

$smarty->assign('stateQ4Response', $ques4);
$smarty->assign('stateQ4ResponseLinks', $link4);

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

$readingPlan->actionPlans = $db->get_results("select * from sipaction where sid = '$sid' and area = 'r' ", ARRAY_A);
$writingPlan->actionPlans = $db->get_results("select * from sipaction where sid = '$sid' and area = 'w' ", ARRAY_A);
$mathPlan->actionPlans = $db->get_results("select * from sipaction where sid = '$sid' and area = 'm' ", ARRAY_A);
$interventionPlan->actionPlans = $db->get_results("select * from sipaction where sid = '$sid' and area = 'i' ", ARRAY_A);

$GAPlans = array($readingPlan, $writingPlan, $mathPlan, $interventionPlan);

$smarty->assign('GAPlans', $GAPlans);

//$actionReadings = $db->get_results("select * from sipaction where sid = '$sid' and area = 'r' ", ARRAY_A);
//foreach($actionReadings as $act1) {
//	while (list($var, $val) = each($act1) ) ${$var} = $val;
//	$actionR .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
//}
//$actionWriting = $db->get_results("select * from sipaction where sid = '$sid' and area = 'w' ", ARRAY_A);
//foreach($actionWriting as $act2) {
//	while (list($var, $val) = each($act2) ) ${$var} = $val;
//	$actionW .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
//}
//$actionMath = $db->get_results("select * from sipaction where sid = '$sid' and area = 'm' ", ARRAY_A);
//foreach($actionMath as $act3) {
//	while (list($var, $val) = each($act3) ) ${$var} = $val;
//	$actionM .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
//}
//$actionIntervention = $db->get_results("select * from sipaction where sid = '$sid' and area = 'i' ", ARRAY_A);
//foreach($actionIntervention as $act4) {
//	while (list($var, $val) = each($act4) ) ${$var} = $val;
//	$actionI .= "<tr><td>$action</td><td>$eval &nbsp;</td></tr>";
//}
//$filestr = file_get_contents('districtReportTemplate.html');
//$str = "\"" . addslashes($filestr) . "\"";
//$str2 = "return($str);";
//$body .= eval($str2);

$isSmarty = true;

include("template.inc");

$smarty->display("districtrep.tpl");
?>
