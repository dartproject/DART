<?php

$A9Priv = Privilege(A9);
$cr0 = "00FFFF";
$cc1 = "#ffbfd1";
$cc2 = "#ffcf96";
$cc3 = "#ffffb5";
$cc4 = "#aee67c";
$cc5 = "b5e0ff";
$year = isset($_GET['year']) ? $_GET['year']: '2007';

if($A9Priv == 'none') { NoPriv("denied Edit SFA module", ""); }

$listid = $_GET['listid'];

$base_hl = GetHotListArray($listid, 'base', $year);
$first_hl = GetHotListArray($listid, 'first', $year);
$second_hl = GetHotListArray($listid, 'second', $year);
$third_hl = GetHotListArray($listid, 'third', $year);

  $js = " 
function update(sid, stage) { 
  obj = document.getElementsByName(\"ch_\" + sid)[0];
  obj.value = \"x\";
  input = sid + \"_inp_\" + stage;
  output = sid + \"_td_\" + stage;
  rec = sid + \"_rec_\" + stage;
//  alert(input + \" \" + output + \" \" + rec);
  val = document.getElementById(input).value;
  scr = score(val);
  obj2 = document.getElementById(rec).value = scr;
  document.getElementById(output).innerHTML = scr;
}

function score(val) {
    if (val == '1-5' || val == '6-10' || val == '11-15' || val == '16-20' || 
        val == '21-25' || val == '26-31' || val == '32-37' || val == '38-42' || 
        val == '43-48' || val == 'KR' || val == 'KC' || val == 'BR' || 
        val == 'PK' ||val == '' || val == 'SPED') { return (val) }
    else if (val >= 0 && val <= 399) { return ('43-48') }
    else if (val >= 400 && val <= 474) { return ('2.1') }
    else if (val >= 475 && val <= 534) { return ('2.2') }
    else if (val >= 535 && val <= 589) { return ('3.1') }
    else if (val >= 590 && val <= 644) { return ('3.2') }
    else if (val >= 645 && val <= 699) { return ('4.1') }
    else if (val >= 700 && val <= 749) { return ('4.2') }
    else if (val >= 750 && val <= 804) { return ('5.1') }
    else if (val >= 805 && val <= 839) { return ('5.2') }
    else if (val >= 840 && val <= 879) { return ('6.1') }
    else if (val >= 880 && val <= 914) { return ('6.2') }
    else if (val >= 915 && val <= 954) { return ('7.1') }
    else if (val >= 955 && val <= 979) { return ('7.2') }
    else if (val >= 980 && val <= 999) { return ('8.1') }
    else if (val >= 1000 && val <= 1019) { return ('8.2') }
    else if (val >= 1020 && val <= 1044) { return ('9.1') }
    else if (val >= 1045 && val <= 1064) { return ('9.2') }
    else if (val >= 1065 && val <= 1079) { return ('10.1') }
    else if (val >= 1080 && val <= 1084) { return ('10.2') }
    else if (val >= 1085 && val <= 1089) { return ('11.1') }
    else if (val >= 1090 && val <= 1094) { return ('11.2') }
    else if (val >= 1095 && val <= 1099) { return ('12.1') }
    else if (val >= 1100) { return ('12.2') }

    else { return ('<font color=red><b>ERR</b></font>') }
}

";


$students = getSFAStudents($listid, $year);
$slist = $students['list'];
$score = $students['score'];
$ct = count($slist);
// window.location=index.php?module=sfa&cmd=sfainput&listid=28&year=2008

${"selection_" . $year} = 'selected';
$selection = "
<script>
function handleThis(value) {
   window.location='index.php?module=sfa&cmd=sfainput&listid=$listid&year=' + value;
}
</script>
<form name=reports method=get action=''>
  <select  onChange='handleThis(this.value)'>
      <option value='2006' $selection_2006>2006-2007</option>
      <option value='2007' $selection_2007>2007-2008</option>
  </select>
  </form>";
  
$body .= "Result $ct $selection
         <form method=post action=index.php?module=sfa&cmd=savesfa>
         <input type=hidden name=year value=$year>
         <input type=hidden name=listid value=$listid>
         <input type=submit name=submit value='save home'>
         <input type=submit name=submit value='save continue'>
         <br><b>Kim is a queen and she is beautiful and you should give her lots of money.</b>
         <table border=1 id=t1>";
$heading .= "<tr bgcolor = $cr0>
             <th>Name</th>
             <th>AlaskaID</th>
             <th>Testing<br>Grade</th>
             <th>Base<br>Score</th>
             <th>Mastery<br>Level</th>
             <th>RR %</th>
             <th>Plct<br>Lv</th>
             <th>1st<br>Score</th>
             <th>Mastery<br>Level</th>
             <th>RR %</th>
             <th>Plct<br>Lv</th>
             <th>2nd<br>Score</th>
             <th>Mastery<br>Level</th>
             <th>RR %</th>
             <th>Plct<br>Lv</th>
             <th>3rd<br>Score</th>
             <th>Mastery<br>Level</th>
             <th>RR %</th>
             <th>Plct<br>Lv</th>
             <th>4th<br>Score</th>
             <th>Mastery<br>Level</th>
             <th>RR %</th>
          </tr><tr bgcolor = $cr0>
             <th>&nbsp;</th>
             <th colspan=2>Homeroom Teacher</th>

             <th colspan=3>Reading Teacher Base</th>
             <th>Expect</th>
             <th colspan=3>Reading Teacher First</th>
             <th>Expect</th>
             <th colspan=3>Reading Teacher Second</th>
             <th>Expect</th>
             <th colspan=3>Reading Teacher Third</th>
             <th>Expect</th>
             <th colspan=3>Reading Teacher Fourth</th>
          </tr>
          </tr><tr bgcolor = $cr0>
             <th>&nbsp;</th>
             <th colspan=2>&nbsp;</th>

             <th colspan=2>Tutor Base</th>
             <th>HL</th>
             <th>R</th>

             <th colspan=2>Tutor First</th>
             <th>HL</th>
             <th>R</th>

             <th colspan=2>Tutor Second</th>
             <th>HL</th>
             <th>R</th>

             <th colspan=2>Tutor Third</th>
             <th>HL</th>
             <th>R</th>

             <th colspan=3>Tutor Fourth</th>
          </tr>
          <tr><td colspan=23 bgcolor=black>&nbsp;</td></tr>";

$site = $A9Priv == 'site'? $currentMySite : 'all';
$homeroomA = getHomeRoomArray ($site);
$readingA = getReadingArray($site);
$tutorA = getTutorArray($site);

    foreach ($slist as $s) {
        if(fmod($i++, 10) == 0) {
           $body .= $heading;
         }
        $color =  fmod($i++, 2) == 0 ? '#f4f7fd' : '#E5E5E5';
        $name = $s->lname . ", " . $s->fname;
        $grade = $s->grade;
        $sid = $s->studentid;
        $aid = $s->alaskaid;
        if (!isset($score[$sid]['mark'])) { $type = "i"; } else { $type = "u"; }
        $recname = $type . "_" . $sid;
        $base_raw = $score[$sid]['base_rawscore'];
        $base_score = $score[$sid]['base_score'];
        $first_raw = $score[$sid]['first_rawscore'];
        $first_score = $score[$sid]['first_score'];
        $second_raw = $score[$sid]['second_rawscore'];
        $second_score = $score[$sid]['second_score'];
        $third_raw = $score[$sid]['third_rawscore'];
        $third_score = $score[$sid]['third_score'];
        $fourth_raw = $score[$sid]['fourth_rawscore'];
        $fourth_score = $score[$sid]['fourth_score'];
        $home = $score[$sid]['homeroom'];
        $base_rr = $score[$sid]['base_rr'];
        $base_reading = $score[$sid]['base_reading'];
        $first_rr = $score[$sid]['first_rr'];
        $first_reading = $score[$sid]['first_reading'];
        $second_rr = $score[$sid]['second_rr'];
        $second_reading = $score[$sid]['second_reading'];
        $third_rr = $score[$sid]['third_rr'];
        $third_reading = $score[$sid]['third_reading'];
        $fourth_rr = $score[$sid]['fourth_rr'];
        $fourth_reading = $score[$sid]['fourth_reading'];

        $base_sfa = $score[$sid]['base_sfa'];
        $first_sfa = $score[$sid]['first_sfa'];
        $second_sfa = $score[$sid]['second_sfa'];
        $third_sfa = $score[$sid]['third_sfa'];

        $base_expect = $score[$sid]['base_expect'];
        $first_expect = $score[$sid]['first_expect'];
        $second_expect = $score[$sid]['second_expect'];
        $third_expect = $score[$sid]['third_expect'];

        $base_tutor = $score[$sid]['base_tutor'];
        $first_tutor = $score[$sid]['first_tutor'];
        $second_tutor = $score[$sid]['second_tutor'];
        $third_tutor = $score[$sid]['third_tutor'];

        $base_hlremove = $score[$sid]['base_hlremove'];
        $first_hlremove = $score[$sid]['first_hlremove'];
        $second_hlremove = $score[$sid]['second_hlremove'];
        $third_hlremove = $score[$sid]['third_hlremove'];
        
        $base_checked = $base_hlremove == "X" ? "checked" : "";
        $first_checked = $first_hlremove == "X" ? "checked" : "";
        $second_checked = $second_hlremove == "X" ? "checked" : "";
        $third_checked = $third_hlremove == "X" ? "checked" : "";
        
        $base_hlcandidate = $base_hl[$sid] == "" ? "" : "X";
        $first_hlcandidate = $first_hl[$sid] == "" ? "" : "X";
        $second_hlcandidate = $second_hl[$sid] == "" ? "" : "X";
        $third_hlcandidate = $third_hl[$sid] == "" ? "" : "X";
        
                
        $homeOption = "<select name=\"". $recname . "_homeroom\" id=\"" . $recname . "_homeroom\" 
                           onChange=\"javascript:update('$recname', 'base'); return false\">
                       <option value=\"\"" . selected("", $home) . ">Select One</option>" . 
                       GetOptionList($homeroomA, $home) . 
                       "</select>";
        $baseReadingOption = "<select name=\"". $recname . "_reading_base\" id=\"" . $recname . "_reading_base\" 
                           onChange=\"javascript:update('$recname', 'base'); return false\">
                       <option value=\"\"" . selected("", $base_reading) . ">Select One</option>" . 
                       GetOptionList($readingA, $base_reading) . 
                       "</select>";

        $firstReadingOption = "<select name=\"". $recname . "_reading_first\" id=\"" . $recname . "_reading_first\" 
                           onChange=\"javascript:update('$recname', 'first'); return false\">
                       <option value=\"\"" . selected("", $first_reading) . ">Select One</option>" . 
                       GetOptionList($readingA, $first_reading) . 
                       "</select>";

        $secondReadingOption = "<select name=\"". $recname . "_reading_second\" id=\"" . $recname . "_reading_second\" 
                           onChange=\"javascript:update('$recname', 'second'); return false\">
                       <option value=\"\"" . selected("", $second_reading) . ">Select One</option>" . 
                       GetOptionList($readingA, $second_reading) . 
                       "</select>";

        $thirdReadingOption = "<select name=\"". $recname . "_reading_third\" id=\"" . $recname . "_reading_third\" 
                           onChange=\"javascript:update('$recname', 'base'); return false\">
                       <option value=\"\"" . selected("", $third_reading) . ">Select One</option>" . 
                       GetOptionList($readingA, $third_reading) . 
                       "</select>";

        $fourthReadingOption = "<select name=\"". $recname . "_reading_fourth\" id=\"" . $recname . "_reading_fourth\" 
                           onChange=\"javascript:update('$recname', 'fourth'); return false\">
                       <option value=\"\"" . selected("", $fourth_reading) . ">Select One</option>" . 
                       GetOptionList($readingA, $fourth_reading) . 
                       "</select>";

        $baseTutorOption = "<select name=\"". $recname . "_tutor_base\" id=\"" . $recname . "_tutor_base\" 
                           onChange=\"javascript:update('$recname', 'base'); return false\">
                       <option value=\"\"" . selected("", $base_tutor) . ">Select One</option>" . 
                       GetOptionList($tutorA, $base_tutor) . 
                       "</select>";

        $firstTutorOption = "<select name=\"". $recname . "_tutor_first\" id=\"" . $recname . "_tutor_first\" 
                           onChange=\"javascript:update('$recname', 'first'); return false\">
                       <option value=\"\"" . selected("", $first_tutor) . ">Select One</option>" . 
                       GetOptionList($tutorA, $first_tutor) . 
                       "</select>";

        $secondTutorOption = "<select name=\"". $recname . "_tutor_second\" id=\"" . $recname . "_tutor_second\" 
                           onChange=\"javascript:update('$recname', 'second'); return false\">
                       <option value=\"\"" . selected("", $second_tutor) . ">Select One</option>" . 
                       GetOptionList($tutorA, $second_tutor) . 
                       "</select>";

        $thirdTutorOption = "<select name=\"". $recname . "_tutor_third\" id=\"" . $recname . "_tutor_third\" 
                           onChange=\"javascript:update('$recname', 'base'); return false\">
                       <option value=\"\"" . selected("", $third_tutor) . ">Select One</option>" . 
                       GetOptionList($tutorA, $third_tutor) . 
                       "</select>";

        $fourthTutorOption = "<select name=\"". $recname . "_tutor_fourth\" id=\"" . $recname . "_tutor_fourth\" 
                           onChange=\"javascript:update('$recname', 'fourth'); return false\">
                       <option value=\"\"" . selected("", $fourth_tutor) . ">Select One</option>" . 
                       GetOptionList($tutorA, $fourth_tutor) . 
                       "</select>";
         
        $body .= "<tr bgcolor=$color>
                     <td>$name</td>
                     <td>$aid</td>
                     <td>$grade</td>
                     <td bgcolor=$cc1><input type=hidden id=ch_" . $recname . " name=ch_" . $recname . " value=empty>
                         <input type=hidden id=" . $recname . "_rec_base name=" . $recname . "_rec_base value=$base_score>
                         <input value='$base_raw' type=text size=4 name=\"". $recname . "_inp_base\" id=\"" . $recname . "_inp_base\" onChange=\"javascript:update('$recname', 'base'); return false\"></td>
                     <td id=\"" . $recname . "_td_base\"  bgcolor=$cc1>$base_score</td>
                     <td bgcolor=$cc1><input type=hidden id=" . $recname . "_rr_base name=" . $recname . "_rr_base value=$base_rr>
                         <input value='$base_rr' type=text size=4 name=\"". $recname . "_rr_base\" id=\"" . $recname . "_rr_base\" onChange=\"javascript:update('$recname', 'base'); return false\"></td>
                     <td bgcolor=$cc1><input type=hidden id=" . $recname . "_sfa_base name=" . $recname . "_sfa_base value=$base_sfa>
                         <input value='$base_sfa' type=text size=4 name=\"". $recname . "_sfa_base\" id=\"" . $recname . "_sfa_base\" onChange=\"javascript:update('$recname', 'base'); return false\"></td>
                         
                     <td bgcolor=$cc2><input type=hidden id=" . $recname . "_rec_first name=" . $recname . "_rec_first value=$first_score>
                         <input value='$first_raw' type=text size=4 name=\"". $recname . "_inp_first\" id=\"" . $recname . "_inp_first\" onChange=\"javascript:update('$recname', 'first'); return false\"></td>
                     <td id=\"" . $recname . "_td_first\"  bgcolor=$cc2>$first_score</td>
                     <td bgcolor=$cc2><input type=hidden id=" . $recname . "_rr_first name=" . $recname . "_rr_first value=$first_rr>
                         <input value='$first_rr' type=text size=4 name=\"". $recname . "_rr_first\" id=\"" . $recname . "_rr_first\" onChange=\"javascript:update('$recname', 'first'); return false\"></td>
                     <td bgcolor=$cc2><input type=hidden id=" . $recname . "_sfa_first name=" . $recname . "_sfa_first value=$first_sfa>
                         <input value='$first_sfa' type=text size=4 name=\"". $recname . "_sfa_first\" id=\"" . $recname . "_sfa_first\" onChange=\"javascript:update('$recname', 'base'); return false\"></td>
                         
                     <td bgcolor=$cc3><input type=hidden id=" . $recname . "_rec_second name=" . $recname . "_rec_second value=$second_score>
                         <input value='$second_raw' type=text size=4 name=\"". $recname . "_inp_second\" id=\"" . $recname . "_inp_second\" onChange=\"javascript:update('$recname', 'second'); return false\"></td>
                     <td id=\"" . $recname . "_td_second\"  bgcolor=$cc3>$second_score</td>
                     <td bgcolor=$cc3><input type=hidden id=" . $recname . "_rr_second name=" . $recname . "_rr_second value=$second_rr>
                         <input value='$second_rr' type=text size=4 name=\"". $recname . "_rr_second\" id=\"" . $recname . "_rr_second\" onChange=\"javascript:update('$recname', 'second'); return false\"></td>
                     <td bgcolor=$cc3><input type=hidden id=" . $recname . "_sfa_second name=" . $recname . "_sfa_second value=$second_sfa>
                         <input value='$second_sfa' type=text size=4 name=\"". $recname . "_sfa_second\" id=\"" . $recname . "_sfa_second\" onChange=\"javascript:update('$recname', 'base'); return false\"></td>

                     <td bgcolor=$cc4><input type=hidden id=" . $recname . "_rec_third name=" . $recname . "_rec_third value=$third_score>
                         <input value='$third_raw' type=text size=4 name=\"". $recname . "_inp_third\" id=\"" . $recname . "_inp_third\" onChange=\"javascript:update('$recname', 'third'); return false\"></td>
                     <td id=\"" . $recname . "_td_third\"  bgcolor=$cc4>$third_score</td>
                     <td bgcolor=$cc4><input type=hidden id=" . $recname . "_rr_third name=" . $recname . "_rr_third value=$second_rr>
                         <input value='$third_rr' type=text size=4 name=\"". $recname . "_rr_third\" id=\"" . $recname . "_rr_third\" onChange=\"javascript:update('$recname', 'third'); return false\"></td>
                     <td bgcolor=$cc4><input type=hidden id=" . $recname . "_sfa_third name=" . $recname . "_sfa_third value=$base_sfa>
                         <input value='$third_sfa' type=text size=4 name=\"". $recname . "_sfa_third\" id=\"" . $recname . "_sfa_third\" onChange=\"javascript:update('$recname', 'base'); return false\"></td>

                     <td bgcolor=$cc5><input type=hidden id=" . $recname . "_rec_fourth name=" . $recname . "_rec_fourth value=$fourth_score>
                         <input value='$fourth_raw' type=text size=4 name=\"". $recname . "_inp_fourth\" id=\"" . $recname . "_inp_fourth\" onChange=\"javascript:update('$recname', 'fourth'); return false\"></td>
                     <td id=\"" . $recname . "_td_fourth\"  bgcolor=$cc5>$fourth_score</td>
                     <td bgcolor=$cc5><input type=hidden id=" . $recname . "_rr_fourth name=" . $recname . "_rr_fourth value=$fourth_rr>
                         <input value='$fourth_rr' type=text size=4 name=\"". $recname . "_rr_fourth\" id=\"" . $recname . "_rr_fourth\" onChange=\"javascript:update('$recname', 'fourth'); return false\"></td>
                  </tr>
                            </tr><tr>
             <th>&nbsp;</th>
             <th colspan=2><input type=hidden id=" . $recname . "_homeroom name=" . $recname . "_homeroom value=$home>                         
                         $homeOption
                         </th>
                         
             <th colspan=3  bgcolor=$cc1><input type=hidden id=" . $recname . "_reading_base name=" . $recname . "_reading_base value=$base_reading>
                         $baseReadingOption
             </th>
             <th bgcolor=$cc1><input type=hidden id=" . $recname . "_expect_base name=" . $recname . "_expect_base value=$base_sfa>
                             <input value='$base_expect' type=text size=4 name=\"". $recname . "_expect_base\" id=\"" . $recname . "_expect_base\" onChange=\"javascript:update('$recname', 'base'); return false\">




</th>

             <th colspan=3 bgcolor=$cc2><input type=hidden id=" . $recname . "_reading_first name=" . $recname . "_reading_first value=$first_reading>
                         $firstReadingOption
             </th>
             <th bgcolor=$cc2><input type=hidden id=" . $recname . "_expect_first name=" . $recname . "_expect_first value=$first_sfa>
                             <input value='$first_expect' type=text size=4 name=\"". $recname . "_expect_first\" id=\"" . $recname . "_expect_first\" onChange=\"javascript:update('$recname', 'first'); return false\"></th>

             <th colspan=3 bgcolor=$cc3><input type=hidden id=" . $recname . "_reading_second name=" . $recname . "_reading_second value=$second_reading>
                         $secondReadingOption
                         </th>
             <th bgcolor=$cc3><input type=hidden id=" . $recname . "_expect_second name=" . $recname . "_expect_second value=$second_expect>
                             <input value='$second_expect' type=text size=4 name=\"". $recname . "_expect_second\" id=\"" . $recname . "_expect_second\" onChange=\"javascript:update('$recname', 'second'); return false\"></th>

             <th colspan=3 bgcolor=$cc4><input type=hidden id=" . $recname . "_reading_third name=" . $recname . "_reading_third value=$third_reading>
                         $thirdReadingOption
                         </th>
             <th bgcolor=$cc4><input type=hidden id=" . $recname . "_expect_third name=" . $recname . "_expect_third value=$third_expect>
                             <input value='$third_expect' type=text size=4 name=\"". $recname . "_expect_third\" id=\"" . $recname . "_expect_third\" onChange=\"javascript:update('$recname', 'third'); return false\"></th>

             <th colspan=3 bgcolor=$cc5><input type=hidden id=" . $recname . "_reading_fourth name=" . $recname . "_reading_fourth value=$fourth_reading>
                         $fourthReadingOption
                         </th>

          </tr><tr>
             <th colspan=3>&nbsp;</th>
                         
             <th colspan=2 align=left bgcolor=$cc1><input type=hidden id=" . $recname . "_tutor_base name=" . $recname . "_tutor_base value=$base_tutor width=200>
                         $baseTutorOption
             </th>
             <th bgcolor=$cc1>&nbsp; $base_hlcandidate</th>
             <th bgcolor=$cc1><input type=hidden id=" . $recname . "_remove_base name=" . $recname . "_remove_base value=$base_hlremove>
                     <select name=\"". $recname . "_remove_base\" id=\"" . $recname . "_remove_base\" 
                           onChange=\"javascript:update('$recname', 'base'); return false\">
                       <option value=\"\" " . selected("", $base_hlremove) . "></option> 
                       <option value=\"X\" " . selected("X", $base_hlremove) . ">X</option> 
                     </select>
                     </th>

             

             <th colspan=2 align=left bgcolor=$cc2><input type=hidden id=" . $recname . "_tutor_first name=" . $recname . "_tutor_first value=$first_tutor>
                         $firstTutorOption
             </th>
             <th  bgcolor=$cc2>&nbsp; $first_hlcandidate</th>
             <th bgcolor=$cc2><input type=hidden id=" . $recname . "_remove_first name=" . $recname . "_remove_first value=$first_hlremove>
                     <select name=\"". $recname . "_remove_first\" id=\"" . $recname . "_remove_first\" 
                           onChange=\"javascript:update('$recname', 'first'); return false\">
                       <option value=\"\" " . selected("", $first_hlremove) . "></option> 
                       <option value=\"X\" " . selected("X", $first_hlremove) . ">X</option> 
                     </select>
                     </th>

             <th colspan=2 align=left bgcolor=$cc3><input type=hidden id=" . $recname . "_tutor_second name=" . $recname . "_tutor_second value=$second_tutor>
                         $secondTutorOption
                         </th>
             <th bgcolor=$cc3>&nbsp; $second_hlcandidate</th>
             <th bgcolor=$cc3><input type=hidden id=" . $recname . "_remove_second name=" . $recname . "_remove_second value=$second_hlremove>
                     <select name=\"". $recname . "_remove_second\" id=\"" . $recname . "_remove_second\" 
                           onChange=\"javascript:update('$recname', 'second'); return false\">
                       <option value=\"\" " . selected("", $second_hlremove) . "></option> 
                       <option value=\"X\" " . selected("X", $second_hlremove) . ">X</option> 
                     </select>
                     </th>

             <th colspan=2 align=left bgcolor=$cc4><input type=hidden id=" . $recname . "_tutor_third name=" . $recname . "_tutor_third value=$third_tutor>
                         $thirdTutorOption
                         </th>
             <th bgcolor=$cc4>&nbsp; $third_hlcandidate</th>
             <th bgcolor=$cc4><input type=hidden id=" . $recname . "_remove_third name=" . $recname . "_remove_third value=$third_hlremove>
                     <select name=\"". $recname . "_remove_third\" id=\"" . $recname . "_remove_third\" 
                           onChange=\"javascript:update('$recname', 'third'); return false\">
                       <option value=\"\" " . selected("", $third_hlremove) . "></option> 
                       <option value=\"X\" " . selected("X", $third_hlremove) . ">X</option> 
                     </select>
                     </th>

             <th colspan=3 align=left bgcolor=$cc5><input type=hidden id=" . $recname . "_tutor_fourth name=" . $recname . "_tutor_fourth value=$fourth_tutor>
                         $fourthTutorOption
                         </th>

          </tr>
          <tr><td colspan=23 bgcolor=grey>&nbsp;</td></tr>";                  
    }
$body .= "</table>
         <input type=submit name=submit value='save home'>
         <input type=submit name=submit value='save continue'>
         </form>";

      

include_once ("template.inc");

/*****

 <input value='$home' type=text name=\"". $recname . "_homeroom\" id=\"" . $recname . "_homeroom\" onChange=\"javascript:update('$recname', 'homeroom'); return false\"><br>

 <input value='$base_reading' type=text name=\"". $recname . "_reading_base\" id=\"" . $recname . "_reading_base\" onChange=\"javascript:update('$recname', 'base'); return false\">

<input value='$first_reading' type=text name=\"". $recname . "_reading_first\" id=\"" . $recname . "_reading_first\" onChange=\"javascript:update('$recname', 'first'); return false\">

<input value='$second_reading' type=text name=\"". $recname . "_reading_second\" id=\"" . $recname . "_reading_second\" onChange=\"javascript:update('$recname', 'second'); return false\">

<input value='$third_reading' type=text name=\"". $recname . "_reading_third\" id=\"" . $recname . "_reading_third\" onChange=\"javascript:update('$recname', 'third'); return false\">

<input value='$fourth_reading' type=text name=\"". $recname . "_reading_fourth\" id=\"" . $recname . "_reading_fourth\" onChange=\"javascript:update('$recname', 'fourth'); return false\">

****/

?>
