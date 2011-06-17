<?php

echo ("Here");



function aboveLevel ($grade, $score, $stage) {
  return (1);
}


$sql = "select * from sfascores, student where sfascores.studentid = student.studentid and (base_rawscore != '' or first_rawscore != '' or second_rawscore != '' or third_rawscore != '' or fourth_rawscore != '')";
echo("SFASCORES: $sql");

$res = $db->get_results($sql);


foreach ($res as $scores) {
  $base = $scores->base_rawscore;
  $first = $scores->first_rawscore;
  $second = $scores->second_rawscore;
  $third = $scores->third_rawscore;
  $fourth = $scores->fourth_rawscore;
  $grade = $scores->grades;
  
  echo ("<br>B: $base F: $first S: $second T: $third F: $bfourth");
  
  $fullCount[$grade]['base']['count'] += $base == "" ? 0 : 1;
  $fullCount[$grade]['first']['count'] += $first == "" ? 0 : 1;
  $fullCount[$grade]['second']['count'] += $second == "" ? 0 : 1;
  $fullCount[$grade]['third']['count'] += $third == "" ? 0 : 1;
  $fullCount[$grade]['fourth']['count'] += $fourth == "" ? 0 : 1;
  
  $aboveCount[$grade]['base']['above'] += aboveLevel ($grade, $base, 'base') ? 0 : 1;
  $aboveCount[$grade]['base']['first'] += aboveLevel ($grade, $base, 'base') ? 0 : 1;
  $aboveCount[$grade]['base']['second'] += aboveLevel ($grade, $base, 'base') ? 0 : 1;
  $aboveCount[$grade]['base']['third'] += aboveLevel ($grade, $base, 'base') ? 0 : 1;
  $aboveCount[$grade]['base']['fourth'] += aboveLevel ($grade, $base, 'base') ? 0 : 1;

}

echo ("<br>FULLCOUNT ====> ");
print_r ($fullCount);

echo ("<br>ABOVECOUNT ====> ");
print_r ($aboveCount);


?>