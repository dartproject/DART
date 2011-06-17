<?php

$listID = $_GET['p1'];    // list id
$sub = $_GET['p2'];       // subject number
$lvl = $_GET['p3'];      // level number

$subject = getSubjectStandards ($sub, $lvl);
$list = getSutdentToggleList($listID, $sub, $lvl);
$student = getStudentStdScores ($listID, $sub, $lvl);
$stdcount = count($list);
$subInfo = getSubjectInfo ($sub);
// print_r ($subInfo);
debugPrint("<br>ID: " . $subInfo[0]['id']);

$js = "function changeValue(name) {
val = document.getElementById(name).value;
alert (val);
        document.getElementById(\"ch_\" + name).value = document.getElementById(name).value;
// toggle image
//        document.getElementById(name + \"_img\").src = 'images\\\dot.gif';
//        document.gri_2_CA_3_3_img.src = 'images\\\dot.gif';
//alert(name + \"_img \" + 'images\\\dot.gif');
 }";

$subName =  $subInfo[0]['name'];
$gradlvl = $subInfo[0]['gradLevel'];

$body .= "<b>$subName ($sub): [Graduation Level - $gradlvl] Current Level $lvl - Student Count $stdcount</b><br>";
$body .= "<form name=toggle method=post action=index.php?cmd=saveToggle>
          <input type=hidden name=listID value=$listID>
          <input type=hidden name=sub value=$sub>
          <input type=hidden name=lvl value=$lvl>
          <table border= 1><tr><th>Name</th>";
for ($i = 0; $i < count($subject); $i++) {
   $body .= "<th title=\"". $subject[$i]['description'] ."\">" . $subject[$i]['std'] . "*</th>";
}
$body .= "</tr>";

$toggleColor = 2;

for ($y = 0; $y < count($list); $y++) {
    if ($toggleColor == 1) { $toggleColor = 2; $color = $color2; }
    else { $toggleColor = 1; $color = $color1; }
    $id = $list[$y]['studentid'];
   $body .= "<tr bgcolor=$color><td>" . $list[$y]['fname'] . " " . $list[$y]['lname'] . " </td>";
   for ($i = 0; $i < count($subject); $i++) {
// name of cell = _id_subject_lvl
        $value = $student[$id][$subject[$i]['std']];
        if (!isset($value)) { $type = "i"; } else { $type = "u"; }
        $name = "gr" . $type . "_" . $id . "_" . $sub . "_" . $lvl . "_" .$subject[$i]['std'];
        $body .= "<td><input type=hidden name=old_" . $name . " value=" . $value . ">\n";
        $body .= "<input type=hidden name=ch_" . $name . " value=empty>\n";
        $body .= "<select title = \"test\" bgcolor=$color name=" . $name . " onclick=changeValue(\"" . $name . "\") >
                  <option value=\"\"" . selected("", $value) . "></option>
                  <option value=\"EMG\"" . selected("EMG", $value) . ">EMG</option>
                  <option value=\"PRO\"" . selected("PRO", $value) . ">PRO</option>
                  <option value=\"DEV\"" . selected("DEV", $value) . ">DEV</option>
                  <option value=\"ADV\"" . selected("ADV", $value) . ">ADV</option>
                  </select>&nbsp;
                  </td>\n";
//                  <img src=\"images\\dot_rev.gif\" name=" . $name . "_img>\n
    }
   $body .= "</tr><tr>";
}



$body .= "</table>
<input type=reset value=reset>
<input type=submit value=save>
</form><br>
* Placing mouse over standard number will display standards descriptions.";

$title = "Show Scores for List";

// $body = "This is the body";

include ("template.inc");

?>
