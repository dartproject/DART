<?php

global $db;

$testtype = $_GET['testtype'];
$importid = 'RJ';
$year = $_POST['year'];
$button = $_POST['button'];

/********************************* PPVT Testing Information ****************************/
$test['PPVT']['array'] = <<<END
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Testing date', '', '', [Pre Testing date], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'CA', '', '', [PreCA], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PreRS', '', '', [PreRS], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PreSS', '', '', [PreSS], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PreAE', '', '', [PreAE], '','','','', '', '', '$importid'--

	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PrePercentile', '', '', [PrePercentile], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PreNCE', '', '', [PreNCE], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PreGrowthScale', '', '', [PreGrowthScale], '','','','', '', '', '$importid'--

	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Diff', '', '', [Pre Diff], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Pre Range', '', '', [Pre Range], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Post Testing date', '', '', [Post Testing date], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Post CA', '', '', [Post CA], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PostRS', '', '', [PostRS], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PostSS', '', '', [PostSS], '','','','', '', '', '$importid'--

	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PostPercentile', '', '', [PostPercentile], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PostNCE', '', '', [PostNCE], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PostGrowScale', '', '', [PostGrowScale], '','','','', '', '', '$importid'--

	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'PostAE', '', '', [PostAE], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Post Diff', '', '', [Post Diff], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'PPVT', [Site], [Grade Level], 'Post Range', '', '', [Post Range], '','','','', '', '', '$importid'
END;
$test['PPVT']['match'] = array("Site", "Alaska ID", "Grade Level", "Pre Testing date", "PreCA", "PreRS", "PreSS", "PrePercentile", "PreNCE", "PreGrowthScale", "PreAE","Pre Diff","Pre Range", "Post Testing date","Post CA", "PostRS","PostSS", "PostPercentile", "PostNCE", "PostGrowScale", "PostAE", "Post Diff", "Post Range" );

//alaskaid, year, test, site, gradelevel, standard, status, needed, value, difference, raw_value, raw_needed, raw_difference, level, test_date, importgrp
/********************************* SBA Testing Information ****************************/
$test['SBA']['array'] = <<<END
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'Reading', '', [Reading Scale Needed], [Reading Scale], [Reading Scale Diff], [Reading Raw], [Reading Raw Needed], [Reading Raw Diff], [Reading Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'R-SC1', [R-SC1 Strand Name], [R-SC1 Scale Needed], [R-SC1 Scale], [R-SC1 Scale Diff], [R-SC1 Raw], [R-SC1 Raw Needed], [R-SC1 Raw Diff], [R-SC1 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'R-SC2', [R-SC2 Strand Name], [R-SC2 Scale Needed], [R-SC2 Scale], [R-SC2 Scale Diff], [R-SC2 Raw], [R-SC2 Raw Needed], [R-SC2 Raw Diff], [R-SC2 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'R-SC3', [R-SC3 Strand Name], [R-SC3 Scale Needed], [R-SC3 Scale], [R-SC3 Scale Diff], [R-SC3 Raw], [R-SC3 Raw Needed], [R-SC3 Raw Diff], [R-SC3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'Writing', '', [Writing Scale Needed], [Writing Scale], [Writing Scale Diff], [Writing Raw], [Writing Raw Needed], [Writing Raw Diff], [Writing Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'W-SC1', [W-SC1 Strand Name], [W-SC1 Scale Needed], [W-SC1 Scale], [W-SC1 Scale Diff], [W-SC1 Raw], [W-SC1 Raw Needed], [W-SC1 Raw Diff], [W-SC1 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'W-SC2', [W-SC2 Strand Name], [W-SC2 Scale Needed], [W-SC2 Scale], [W-SC2 Scale Diff], [W-SC2 Raw], [W-SC2 Raw Needed], [W-SC2 Raw Diff], [W-SC2 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'W-SC3', [W-SC3 Strand Name], [W-SC3 Scale Needed], [W-SC3 Scale], [W-SC3 Scale Diff], [W-SC3 Raw], [W-SC3 Raw Needed], [W-SC3 Raw Diff], [W-SC3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'Math', '', [Math Scale Needed], [Math Scale], [Math Scale Diff], [Math Raw], [Math Raw Needed], [Math Raw Diff], [Math Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'M-SC1', [M-SC1 Strand Name], [M-SC1 Scale Needed], [M-SC1 Scale], [M-SC1 Scale Diff], [M-SC1 Raw], [M-SC1 Raw Needed], [M-SC1 Raw Diff], [M-SC1 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'M-SC2', [M-SC2 Strand Name], [M-SC2 Scale Needed], [M-SC2 Scale], [M-SC2 Scale Diff], [M-SC2 Raw], [M-SC2 Raw Needed], [M-SC2 Raw Diff], [M-SC2 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'M-SC3', [M-SC3 Strand Name], [M-SC3 Scale Needed], [M-SC3 Scale], [M-SC3 Scale Diff], [M-SC3 Raw], [M-SC3 Raw Needed], [M-SC3 Raw Diff], [M-SC3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'M-SC4', [M-SC4 Strand Name], [M-SC4 Scale Needed], [M-SC4 Scale], [M-SC4 Scale Diff], [M-SC4 Raw], [M-SC4 Raw Needed], [M-SC4 Raw Diff], [M-SC4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'M-SC5', [M-SC5 Strand Name], [M-SC5 Scale Needed], [M-SC5 Scale], [M-SC5 Scale Diff], [M-SC5 Raw], [M-SC5 Raw Needed], [M-SC5 Raw Diff], [M-SC5 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'M-SC6', [M-SC6 Strand Name], [M-SC6 Scale Needed], [M-SC6 Scale], [M-SC6 Scale Diff], [M-SC6 Raw], [M-SC6 Raw Needed], [M-SC6 Raw Diff], [M-SC6 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'Science', '', [Science Scale Needed], [Science Scale], [Science Scale Diff], [Science Raw], [Science Raw Needed], [Science Raw Diff], [Science Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'S-SC1', [S-SC1 Strand Name], [S-SC1 Scale Needed], [S-SC1 Scale], [S-SC1 Scale Diff], [S-SC1 Raw], [S-SC1 Raw Needed], [S-SC1 Raw Diff], [S-SC1 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'S-SC2', [S-SC2 Strand Name], [S-SC2 Scale Needed], [S-SC2 Scale], [S-SC2 Scale Diff], [S-SC2 Raw], [S-SC2 Raw Needed], [S-SC2 Raw Diff], [S-SC2 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'S-SC3', [S-SC3 Strand Name], [S-SC3 Scale Needed], [S-SC3 Scale], [S-SC3 Scale Diff], [S-SC3 Raw], [S-SC3 Raw Needed], [S-SC3 Raw Diff], [S-SC3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'SBA', [Site], [Grade Level], 'S-SC4', [S-SC4 Strand Name], [S-SC4 Scale Needed], [S-SC4 Scale], [S-SC4 Scale Diff], [S-SC4 Raw], [S-SC4 Raw Needed], [S-SC4 Raw Diff], [S-SC4 Proficiency], '', '$importid'
END;

$test['SBA']['match'] = array("Alaska ID", "Site", "Grade Level", 
"Reading Raw","Reading Raw Needed","Reading Raw Diff",
   "Reading Proficiency","Reading Scale","Reading Scale Needed","Reading Scale Diff",
"R-SC1 Strand Name","R-SC1 Raw","R-SC1 Raw Needed","R-SC1 Raw Diff",
   "R-SC1 Proficiency","R-SC1 Scale","R-SC1 Scale Needed","R-SC1 Scale Diff",
"R-SC2 Strand Name","R-SC2 Raw","R-SC2 Raw Needed","R-SC2 Raw Diff",
   "R-SC2 Proficiency","R-SC2 Scale","R-SC2 Scale Needed","R-SC2 Scale Diff",
"R-SC3 Strand Name","R-SC3 Raw","R-SC3 Raw Needed","R-SC3 Raw Diff",
   "R-SC3 Proficiency","R-SC3 Scale","R-SC3 Scale Needed","R-SC3 Scale Diff",
"Writing Raw","Writing Raw Needed","Writing Raw Diff",
   "Writing Proficiency","Writing Scale","Writing Scale Needed","Writing Scale Diff",
"W-SC1 Strand Name","W-SC1 Raw","W-SC1 Raw Needed","W-SC1 Raw Diff",
   "W-SC1 Proficiency","W-SC1 Scale","W-SC1 Scale Needed","W-SC1 Scale Diff",
"W-SC2 Strand Name","W-SC2 Raw","W-SC2 Raw Needed","W-SC2 Raw Diff",
   "W-SC2 Proficiency","W-SC2 Scale","W-SC2 Scale Needed","W-SC2 Scale Diff",
"W-SC3 Strand Name","W-SC3 Raw","W-SC3 Raw Needed","W-SC3 Raw Diff",
   "W-SC3 Proficiency","W-SC3 Scale","W-SC3 Scale Needed","W-SC3 Scale Diff",
"Math Raw","Math Raw Needed","Math Raw Diff",
   "Math Proficiency","Math Scale","Math Scale Needed","Math Scale Diff",
"M-SC1 Strand Name","M-SC1 Raw","M-SC1 Raw Needed","M-SC1 Raw Diff",
   "M-SC1 Proficiency","M-SC1 Scale","M-SC1 Scale Needed","M-SC1 Scale Diff",
"M-SC2 Strand Name","M-SC2 Raw","M-SC2 Raw Needed","M-SC2 Raw Diff",
   "M-SC2 Proficiency","M-SC2 Scale","M-SC2 Scale Needed","M-SC2 Scale Diff",
"M-SC3 Strand Name","M-SC3 Raw","M-SC3 Raw Needed","M-SC3 Raw Diff",
   "M-SC3 Proficiency","M-SC3 Scale","M-SC3 Scale Needed","M-SC3 Scale Diff",
"M-SC4 Strand Name","M-SC4 Raw","M-SC4 Raw Needed","M-SC4 Raw Diff",
   "M-SC4 Proficiency","M-SC4 Scale","M-SC4 Scale Needed","M-SC4 Scale Diff",
"M-SC5 Strand Name","M-SC5 Raw","M-SC5 Raw Needed","M-SC5 Raw Diff",
   "M-SC5 Proficiency","M-SC5 Scale","M-SC5 Scale Needed","M-SC5 Scale Diff",
"M-SC6 Strand Name","M-SC6 Raw","M-SC6 Raw Needed","M-SC6 Raw Diff",
   "M-SC6 Proficiency","M-SC6 Scale","M-SC6 Scale Needed","M-SC6 Scale Diff",
"Science Raw","Science Raw Needed","Science Raw Diff",
   "Science Proficiency","Science Scale","Science Scale Needed","Science Scale Diff",
"S-SC1 Strand Name","S-SC1 Raw","S-SC1 Raw Needed","S-SC1 Raw Diff",
   "S-SC1 Proficiency","S-SC1 Scale","S-SC1 Scale Needed","S-SC1 Scale Diff",
"S-SC2 Strand Name","S-SC2 Raw","S-SC2 Raw Needed","S-SC2 Raw Diff",
   "S-SC2 Proficiency","S-SC2 Scale","S-SC2 Scale Needed","S-SC2 Scale Diff",
"S-SC3 Strand Name","S-SC3 Raw","S-SC3 Raw Needed","S-SC3 Raw Diff",
   "S-SC3 Proficiency","S-SC3 Scale","S-SC3 Scale Needed","S-SC3 Scale Diff",
"S-SC4 Strand Name","S-SC4 Raw","S-SC4 Raw Needed","S-SC4 Raw Diff",
   "S-SC4 Proficiency","S-SC4 Scale","S-SC4 Scale Needed","S-SC4 Scale Diff"
);
//$test['SBA']['match2'] = array("1", "3", "5","6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17" );

/********************************* HSGQE Testing Information ****************************/
$test['HSGQE']['array'] = <<<END
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'Reading', '', [Reading Scale Needed], [Reading Scale], [Reading Scale Diff], [Reading Raw], [Reading Raw Needed], [Reading Raw Diff], [Reading Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'R4.1', [R4.1 Strand Name], [R4.1 Scale Needed], [R4.1 Scale], [R4.1 Scale Diff], [R4.1 Raw], [R4.1 Raw Needed], [R4.1 Raw Diff], [R4.1 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'R4.2', [R4.2 Strand Name], [R4.2 Scale Needed], [R4.2 Scale], [R4.2 Scale Diff], [R4.2 Raw], [R4.2 Raw Needed], [R4.2 Raw Diff], [R4.2 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'R4.3', [R4.3 Strand Name], [R4.3 Scale Needed], [R4.3 Scale], [R4.3 Scale Diff], [R4.3 Raw], [R4.3 Raw Needed], [R4.3 Raw Diff], [R4.3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'R4.4', [R4.4 Strand Name], [R4.4 Scale Needed], [R4.4 Scale], [R4.4 Scale Diff], [R4.4 Raw], [R4.4 Raw Needed], [R4.4 Raw Diff], [R4.4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'R4.7', [R4.7 Strand Name], [R4.7 Scale Needed], [R4.7 Scale], [R4.7 Scale Diff], [R4.7 Raw], [R4.7 Raw Needed], [R4.7 Raw Diff], [R4.7 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'R4.8', [R4.8 Strand Name], [R4.8 Scale Needed], [R4.8 Scale], [R4.8 Scale Diff], [R4.8 Raw], [R4.8 Raw Needed], [R4.8 Raw Diff], [R4.8 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'Writing', '', [Writing Scale Needed], [Writing Scale], [Writing Scale Diff], [Writing Raw], [Writing Raw Needed], [Writing Raw Diff], [Writing Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'W4.1/4.2', [W4.1/4.2 Strand Name], [W4.1/4.2 Scale Needed], [W4.1/4.2 Scale], [W4.1/4.2 Scale Diff], [W4.1/4.2 Raw], [W4.1/4.2 Raw Needed], [W4.1/4.2 Raw Diff], [W4.1/4.2 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'W4.3', [W4.3 Strand Name], [W4.3 Scale Needed], [W4.3 Scale], [W4.3 Scale Diff], [W4.3 Raw], [W4.3 Raw Needed], [W4.3 Raw Diff], [W4.3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'W4.4', [W4.4 Strand Name], [W4.4 Scale Needed], [W4.4 Scale], [W4.4 Scale Diff], [W4.4 Raw], [W4.4 Raw Needed], [W4.4 Raw Diff], [W4.4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'Math', '', [Math Scale Needed], [Math Scale], [Math Scale Diff], [Math Raw], [Math Raw Needed], [Math Raw Diff], [Math Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'M1.4', [M1.4 Strand Name], [M1.4 Scale Needed], [M1.4 Scale], [M1.4 Scale Diff], [M1.4 Raw], [M1.4 Raw Needed], [M1.4 Raw Diff], [M1.4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'M2.4', [M2.4 Strand Name], [M2.4 Scale Needed], [M2.4 Scale], [M2.4 Scale Diff], [M2.4 Raw], [M2.4 Raw Needed], [M2.4 Raw Diff], [M2.4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'M3.4', [M3.4 Strand Name], [M3.4 Scale Needed], [M3.4 Scale], [M3.4 Scale Diff], [M3.4 Raw], [M3.4 Raw Needed], [M3.4 Raw Diff], [M3.4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'M4.4', [M4.4 Strand Name], [M4.4 Scale Needed], [M4.4 Scale], [M4.4 Scale Diff], [M4.4 Raw], [M4.4 Raw Needed], [M4.4 Raw Diff], [M4.4 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'M5.3', [M5.3 Strand Name], [M5.3 Scale Needed], [M5.3 Scale], [M5.3 Scale Diff], [M5.3 Raw], [M5.3 Raw Needed], [M5.3 Raw Diff], [M5.3 Proficiency], '', '$importid'--
[Alaska ID], '$year', 'HSGQE', [Site], [Grade Level], 'M6.3', [M6.3 Strand Name], [M6.3 Scale Needed], [M6.3 Scale], [M6.3 Scale Diff], [M6.3 Raw], [M6.3 Raw Needed], [M6.3 Raw Diff], [M6.3 Proficiency], '', '$importid'
END;
$test['HSGQE']['match'] = array("Site", "Alaska ID", "Grade Level", 
"Reading Raw","Reading Raw Needed","Reading Raw Diff",
   "Reading Proficiency","Reading Scale","Reading Scale Needed","Reading Scale Diff",
"R4.1 Strand Name","R4.1 Raw","R4.1 Raw Needed","R4.1 Raw Diff",
   "R4.1 Proficiency","R4.1 Scale","R4.1 Scale Needed","R4.1 Scale Diff",
"R4.2 Strand Name","R4.2 Raw","R4.2 Raw Needed","R4.2 Raw Diff",
   "R4.2 Proficiency","R4.2 Scale","R4.2 Scale Needed","R4.2 Scale Diff",
"R4.3 Strand Name","R4.3 Raw","R4.3 Raw Needed","R4.3 Raw Diff",
   "R4.3 Proficiency","R4.3 Scale","R4.3 Scale Needed","R4.3 Scale Diff",
"R4.4 Strand Name","R4.4 Raw","R4.4 Raw Needed","R4.4 Raw Diff",
   "R4.4 Proficiency","R4.4 Scale","R4.4 Scale Needed","R4.4 Scale Diff",
"R4.7 Strand Name","R4.7 Raw","R4.7 Raw Needed","R4.7 Raw Diff",
   "R4.7 Proficiency","R4.7 Scale","R4.7 Scale Needed","R4.7 Scale Diff",
"R4.8 Strand Name","R4.8 Raw","R4.8 Raw Needed","R4.8 Raw Diff",
   "R4.8 Proficiency","R4.8 Scale","R4.8 Scale Needed","R4.8 Scale Diff",
"Writing Raw","Writing Raw Needed","Writing Raw Diff",
   "Writing Proficiency","Writing Scale","Writing Scale Needed","Writing Scale Diff",
"W4.1/4.2 Strand Name","W4.1/4.2 Raw","W4.1/4.2 Raw Needed","W4.1/4.2 Raw Diff",
   "W4.1/4.2 Proficiency","W4.1/4.2 Scale","W4.1/4.2 Scale Needed","W4.1/4.2 Scale Diff",
"W4.3 Strand Name","W4.3 Raw","W4.3 Raw Needed","W4.3 Raw Diff",
   "W4.3 Proficiency","W4.3 Scale","W4.3 Scale Needed","W4.3 Scale Diff",
"W4.4 Strand Name","W4.4 Raw","W4.4 Raw Needed","W4.4 Raw Diff",
   "W4.4 Proficiency","W4.4 Scale","W4.4 Scale Needed","W4.4 Scale Diff",
"Math Raw","Math Raw Needed","Math Raw Diff",
   "Math Proficiency","Math Scale","Math Scale Needed","Math Scale Diff",
"M1.4 Strand Name","M1.4 Raw","M1.4 Raw Needed","M1.4 Raw Diff",
   "M1.4 Proficiency","M1.4 Scale","M1.4 Scale Needed","M1.4 Scale Diff",
"M2.4 Strand Name","M2.4 Raw","M2.4 Raw Needed","M2.4 Raw Diff",
   "M2.4 Proficiency","M2.4 Scale","M2.4 Scale Needed","M2.4 Scale Diff",
"M3.4 Strand Name","M3.4 Raw","M3.4 Raw Needed","M3.4 Raw Diff",
   "M3.4 Proficiency","M3.4 Scale","M3.4 Scale Needed","M3.4 Scale Diff",
"M4.4 Strand Name","M4.4 Raw","M4.4 Raw Needed","M4.4 Raw Diff",
   "M4.4 Proficiency","M4.4 Scale","M4.4 Scale Needed","M4.4 Scale Diff",
"M5.3 Strand Name","M5.3 Raw","M5.3 Raw Needed","M5.3 Raw Diff",
   "M5.3 Proficiency","M5.3 Scale","M5.3 Scale Needed","M5.3 Scale Diff",
"M6.3 Strand Name","M6.3 Raw","M6.3 Raw Needed","M6.3 Raw Diff",
   "M6.3 Proficiency","M6.3 Scale","M6.3 Scale Needed","M6.3 Scale Diff");


/********************************* ESP Testing Information ****************************/
$test['ESP']['array'] = <<<END
	[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Testing date', '', '', [Testing Date], '','','','', '', '', '$importid'--
	[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Chronological Age', '', '', [Chronological Age], '','','','', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Verbal Concepts', '', [Verbal Concepts National Percentile], [Verbal Concepts Standard Score], '', [Verbal Concepts Point Score], [Verbal Concepts Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Visual Discrimination', '', [Visual Discrimination National Percentile], [Visual Discrimination Standard Score], '', [Visual Discrimination Point Score], [Visual Discrimination Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Logical Relations', '', [Logical Relations National Percentile], [Logical Relations Standard Score], '', [Logical Relations Point Score], [Logical Relations Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Basic School Skills', '', [Basic School Skills National Percentile], [Basic School Skills Standard Score], '', [Basic School Skills Point Score], [Basic School Skills Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Expressive Language', '', [Expressive Language National Percentile], [Expressive Language Standard Score], '', [Expressive Language Point Score], [Expressive Language Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Receptive Language', '', [Receptive Language National Percentile], [Receptive Language Standard Score], '', [Receptive Language Point Score], [Receptive Language Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Gross Motor', '', '', '', '', [Gross Motor Point Score], [Gross Motor Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Fine Motor', '', '', '', '', [Fine Motor Point Score], [Fine Motor Screening Index], '', '', '', '$importid'--
[Alaska ID], '$year', 'ESP', [Site], [Grade Level], 'Articulation', '', '', '', '', [Articulation Raw Score], [Articulation Descriptive Category], '', '', '', '$importid'
END;
$test['ESP']['match'] = array("Site", "Alaska ID", "Grade Level", "Testing Date", "Chronological Age",
"Verbal Concepts Point Score","Verbal Concepts Screening Index","Verbal Concepts Standard Score", "Verbal Concepts National Percentile",
"Visual Discrimination Point Score","Visual Discrimination Screening Index","Visual Discrimination Standard Score", "Visual Discrimination National Percentile",
"Logical Relations Point Score","Logical Relations Screening Index","Logical Relations Standard Score", "Logical Relations National Percentile",
"Basic School Skills Point Score","Basic School Skills Screening Index","Basic School Skills Standard Score", "Basic School Skills National Percentile",
"Expressive Language Point Score","Expressive Language Screening Index","Expressive Language Standard Score", "Expressive Language National Percentile",
"Receptive Language Point Score","Receptive Language Screening Index","Receptive Language Standard Score", "Receptive Language National Percentile",
"Gross Motor Point Score","Gross Motor Screening Index",
"Fine Motor Point Score","Fine Motor Screening Index",
"Articulation Raw Score","Articulation Descriptive Category"
);
//$test['ESP']['match2'] = array("1", "3", "5","6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17" );

/********************************* ELP Testing Information ****************************/
$test['ELP']['array'] = <<<END
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'Listening Scale Score', '', '', [Listening Standard Score], '', '', '', '', [Listening Proficiency Level], '', '$importid'--
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'Speaking Scale Score', '', '', [Speaking Standard Score], '', '', '', '', [Speaking Proficiency Level], '', '$importid'--
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'Reading Scale Score', '', '', [Reading Standard Score], '', '', '', '', [Reading Proficiency Level], '', '$importid'--
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'Writing Scale Score', '', '', [Writing Standard Score], '', '', '', '', [Writing Proficiency Level], '', '$importid'--
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'Comprehension Scale Score', '', '', [Comprehension Standard Score], '', '', '', '', [Comprehension Proficiency Level], '', '$importid'--
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'Overall Scale Score', '', '', [Overall Standard Score], '', '', '', '', [Overall Proficiency Level], '', '$importid'--
[Alaska ID], '$year', 'ELP', [Site], [Grade Level], 'ELP Made Progress', '', '', [ELP Made Progress Scale], '', '', '', '', [ELP Made Progress Proficiency], '', '$importid'
END;
$test['ELP']['match'] = array("Site", "Alaska ID", "Grade Level", 
"Listening Standard Score",
"Speaking Standard Score",
"Reading Standard Score",
"Writing Standard Score",
"Comprehension Standard Score",
"Overall Standard Score",
"Listening Proficiency Level",
"Speaking Proficiency Level",
"Reading Proficiency Level",
"Writing Proficiency Level",
"Comprehension Proficiency Level",
"Overall Proficiency Level",
"ELP Made Progress Scale",
"ELP Made Progress Proficiency"
);
//$test['ELP']['match2'] = array("1", "3", "5","6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17" );

/********************************* TerraNova Testing Information ****************************/
$test['TerraNova']['array'] = <<<END
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Reading', '', [Reading NPR], [Reading Scale Score], '', [Reading NCE], '', '', if([Reading NCE] < 1, '', if([Reading NCE] <= 25, 'Q1', if([Reading NCE] <= 50, 'Q2', if([Reading NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Vocabulary', '', [Vocabulary NPR], [Vocabulary Scale Score], '', [Vocabulary NCE], '', '', if([Vocabulary NCE] < 1, '', if([Vocabulary NCE] <= 25, 'Q1', if([Vocabulary NCE] <= 50, 'Q2', if([Vocabulary NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Reading Composite', '', [Reading Composite NPR], [Reading Composite Scale Score], '', [Reading Composite NCE], '', '', if([Reading Composite NCE] < 1, '', if([Reading Composite NCE] <= 25, 'Q1', if([Reading Composite NCE] <= 50, 'Q2', if([Reading Composite NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Language', '', [Language NPR], [Language Scale Score], '', [Language NCE], '', '', if([Language NCE] < 1,'',if([Language NCE] <= 25, 'Q1', if([Language NCE] <= 50, 'Q2', if([Language NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Language Mechanics', '', [Language Mechanics NPR], [Language Mechanics Scale Score], '', [Language Mechanics NCE], '', '', if([Language Mechanics NCE] < 1,'', if([Language Mechanics NCE] <= 25, 'Q1', if([Language Mechanics NCE] <= 50, 'Q2', if([Language Mechanics NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Language Composite', '', [Language Composite NPR], [Language Composite Scale Score], '', [Language Composite NCE], '', '', if([Language Composite NCE] < 1, '', if([Language Composite NCE] <= 25, 'Q1', if([Language Composite NCE] <= 50, 'Q2', if([Language Composite NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Mathematics', '', [Mathematics NPR], [Mathematics Scale Score], '', [Mathematics NCE], '', '', if([Mathematics NCE] < 1,'', if([Mathematics NCE] <= 25, 'Q1', if([Mathematics NCE] <= 50, 'Q2', if([Mathematics NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Math Computation', '', [Math Computation NPR], [Math Computation Scale Score], '', [Math Computation NCE], '', '', if([Math Computation NCE] < 1,'', if([Math Computation NCE] <= 25, 'Q1', if([Math Computation NCE] <= 50, 'Q2', if([Math Computation NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Math Composite', '', [Math Composite NPR], [Math Composite Scale Score], '', [Math Composite NCE], '', '', if([Math Composite NCE] < 1,'', if([Math Composite NCE] <= 25, 'Q1', if([Math Composite NCE] <= 50, 'Q2', if([Math Composite NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Total Score', '', [Total Score NPR], [Total Score Scale Score], '', [Total Score NCE], '', '', if([Total Score NCE] < 1,'', if([Total Score NCE] <= 25, 'Q1', if([Total Score NCE] <= 50, 'Q2', if([Total Score NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Science', '', [Science NPR], [Science Scale Score], '', [Science NCE], '', '', if([Science NCE] < 1,'', if([Science NCE] <= 25, 'Q1', if([Science NCE] <= 50, 'Q2', if([Science NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Social Studies', '', [Social Studies NPR], [Social Studies Scale Score], '', [Social Studies NCE], '', '', if([Social Studies NCE] < 1,'', if([Social Studies NCE] <= 25, 'Q1', if([Social Studies NCE] <= 50, 'Q2', if([Social Studies NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Spelling', '', [Spelling NPR], [Spelling Scale Score], '', [Spelling NCE], '', '', if([Spelling NCE] < 1, '',if([Spelling NCE] <= 25,  'Q1', if([Spelling NCE] <= 50, 'Q2', if([Spelling NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'--
[Alaska ID], '$year', 'TerraNova', [Site], [Grade Level], 'Word Analysis', '', [Word Analysis NPR], [Word Analysis Scale Score], '', [Word Analysis NCE], '', '', if([Word Analysis NCE] < 1,'', if([Word Analysis NCE] <= 25, 'Q1', if([Word Analysis NCE] <= 50, 'Q2', if([Word Analysis NCE] <= 75, 'Q3', 'Q4')))), '', '$importid'	  	
END;
$test['TerraNova']['match'] = array("Site", "Alaska ID", "Grade Level", 
"Reading NCE",
"Vocabulary NCE",
"Reading Composite NCE",
"Language NCE",
"Language Mechanics NCE",
"Language Composite NCE", 
"Mathematics NCE",
"Math Computation NCE",	
"Math Composite NCE",
"Total Score NCE",
"Science NCE",
"Social Studies NCE",
"Spelling NCE",
"Word Analysis NCE",

"Reading NPR",
"Vocabulary NPR",
"Reading Composite NPR",
"Language NPR",
"Language Mechanics NPR",
"Language Composite NPR", 
"Mathematics NPR",
"Math Computation NPR",	
"Math Composite NPR",
"Total Score NPR",
"Science NPR",
"Social Studies NPR",
"Spelling NPR",
"Word Analysis NPR",

"Reading Scale Score",
"Vocabulary Scale Score",
"Reading Composite Scale Score",
"Language Scale Score",
"Language Mechanics Scale Score",
"Language Composite Scale Score", 
"Mathematics Scale Score",
"Math Computation Scale Score",	
"Math Composite Scale Score",
"Total Score Scale Score",
"Science Scale Score",
"Social Studies Scale Score",
"Spelling Scale Score",
"Word Analysis Scale Score"
);

$test[$testtype]['match2'] = unserialize($db->get_var("SELECT import from test_save_import_order where test = '$testtype'"));
if($button == "import") {
	$tmpname = $_FILES['importfile']['tmp_name'];
	$uploadFile = '/tmp/import.csv'; 

//	echo "--" . file_exists($tmpname) . "--";
	if(uploadFile($tmpname, $uploadFile)) {
		$body .= importFile($uploadFile);
	} else {
		$body .= "IMPORT ERROR NO DATA has been put into the database";
	}

} else if($button == 'Save') {
	$vals = $_POST['val'];
	$reps = $_POST['input'];
	foreach($reps as $row)	$rep[] = (trim($row) != '') ? 'p'.$row : "''";
	foreach($vals as $row)	$val[] = "[" . trim($row) . "]";
	
//	print_r($rep);
//	print_r($val);
	$newval = str_replace($val, $rep, $test[$testtype]['array']);
//	echo $newval;
	$a = "array($newval);";
//	echo $a;
	$selects = explode('--', $newval);
	$sql = "DELETE FROM testscores WHERE year = '$year' and test = '$testtype' and alaskaid in (select p2 from tmpimport) ";
	$db->get_results($sql);
	echo $sql;
	$db->get_results("DELETE FROM tmpimport LIMIT 1 ");
	foreach ($selects as $select) {
		$sql = "INSERT INTO 
							testscores (alaskaid, year, test, site, 
										gradelevel, standard, status, needed, 
										value, difference, raw_value, raw_needed, 
										raw_difference, level, test_date, importgrp) 
						   SELECT $select FROM tmpimport";
//		echo "$sql<br>";
		$db->get_results($sql);
	}
	$serial = serialize($reps);
	$sql = "INSERT INTO test_save_import_order SET import = '$serial', test='$testtype' ON DUPLICATE KEY UPDATE import = '$serial'";
//	echo $sql;
	$db->get_results($sql);
	$body = "<h1>Test scores for $year and test $testtype have been stored</h1>Back to <a href='index.php?module=testing&cmd=testingHome'>Test Home</a> | or <a href='index.php?module=testing&cmd=importData'>Import Test Scores</a>";
	include_once ("template.inc");
	exit();
}


$match = $test[$testtype]['match'];
$match2 = $test[$testtype]['match2'];
$results = $db->get_results("SELECT * from tmpimport LIMIT 0, 2", ARRAY_A);
//print_r($results);
$results0 = $results[0];
$results1 = $results[1];
//print_r($results1);
$i=0;
foreach( $results0 as $val1) {
	$val1a = $results1['p'.$i];
//	echo "---$val1a--<br>";
	$table2 .= "<tr><td>$i</td><td><div id=a$i>$val1 [$val1a]</div></td></tr>\n";
	$p[$i] = $val1;
	$i++;
}
$i=0;
reset($results);
foreach($match as $val2) {
	$index = $match2[$i];
	$value = $p[$index];
	$table .= "<tr ><td nowrap>$val2<input type=hidden name=val[$i] value=\"$val2\"></td><td><div id=p[$i]>$value</div></td><td><input type=text name='input[$i]' id='input[$i]' value='{$index}' size=3 onChange='javascript:update($i);'></td></tr>\n";
	$i++;
}

$body .= "<script>
function update(i) {
	var input = document.getElementById('input['+i+']');
//	alert(input.value);
	var a = document.getElementById('a'+input.value);
	var p = document.getElementById('p['+i+']');
//	alert(a.innerHTML);
//	var pval = document.getElementById('p'+a.innerHTML);
	p.innerHTML = a.innerHTML;
}
</script>
<style>
.selection tr {
	line-height: 22px;
}
</style>
<form action='index.php?module=testing&cmd=compare&testtype=$testtype' method=post>
<input type=submit name=button value=Save> | <button onClick=\"javascript:window.location='index.php?module=testing&cmd=importData'; return false;\">Cancel</button><br>
<input type=hidden name=year value='$year'>
Year: $year Test: $testtype
<table border=1>
	<tr valign=top>
		<td>
			<table border=1 class=selection>
				<tr bgcolor=lightgreen><th colspan=3>Data Put Into System</th></tr>
				<tr bgcolor=lightgreen><th>Values Needed</th><th>Match From Data</th><th>#</th></tr>
			$table
			</table>
		</td><td>
			<table border=1 class=selection>
				<tr bgcolor=lightgreen><th colspan=2>From Import File</th></tr>
				<tr bgcolor=lightgreen><th>#</th><th>Column Title [1st sample record data]</th></tr>
			$table2
			</table>
		</td>
	</tr>
</table>
<input type=submit name=button value=Save> | <button onClick=\"javascript:window.location='index.php?module=testing&cmd=importData'; return false;\">Cancel</button>
</form>
";

function uploadFile($tmpname, $uploadFile) {

    @unlink($uploadFile);    
    if (move_uploaded_file($tmpname, $uploadFile)) {
//       echo ("Upload Successful<br>");
       return (TRUE);
    } else {
       echo ("Upload Failured TMP: $tmpname - UPLOAD: $uploadFile");
       return(FALSE);
    }
}

function importFile($file) {
	global $db;
	
  for($i = 0; $i < 200; $i++) {
	$params .= $params == ""? "p$i" : ",p$i";
  }
  $db->show_errors();
  $empty = "TRUNCATE TABLE `tmpimport`";
  $db->query($empty);
//  echo ("Load Table Emptied<br>");
  $load = "LOAD DATA LOCAL INFILE '$file'
            INTO TABLE tmpimport
			FIELDS TERMINATED BY '\t' ENCLOSED BY '\"'
            LINES TERMINATED BY '\r'
           ($params)";
//  echo ("Load: $load<br>");
  $db->query($load);
  $select = "select * from tmpimport";
  $db->query($select);
  $num = $db->num_rows;
  return ("Students Loaded ($num) $test<br>");

}

/*
//$body .= "--$values--";
$url = "";
$body .= <<<END
<link rel="STYLESHEET" type="text/css" href="./testing/codebase/dhtmlxgrid.css">
<script src="./testing//codebase/dhtmlxcommon.js"></script>
<script src="./testing//codebase/dhtmlxgrid.js"></script>
<script src="./testing//codebase/dhtmlxgridcell.js"></script>
<script src="./testing//codebase/ext/dhtmlxgrid_drag.js"></script>
<script src="./testing//codebase/ext/dhtmlxgrid_form.js"></script>
<script src="./testing//codebase/ext/dhtmlxgrid_filter.js"></script>

<TABLE cellspacing=0 cellpadding=0>
<TR>
<TD><div id="mygrid_container1" style="width:150PX;height:150px;"></div></TD>
<TD><div id="mygrid_container2" style="width:200PX;height:150px;"></div></TD>
</TR>
</TABLE>
<script>

var data1=[
    ["AlaskaId"],
    ["Site"]
];
 var data2=[
    $values
];
    mygrid1 = new dhtmlXGridObject('mygrid_container1');
    mygrid1.setImagePath("codebase/imgs/");
    mygrid1.setHeader("Name");
    mygrid1.setInitWidths("150");
    mygrid1.setColAlign("right");
    mygrid1.setSkin("light");
    mygrid1.enableEditEvents(false,false,false);
    mygrid1.init();
    mygrid1.load("_data.js","jsarray");
    mygrid1.parse(data1,"jsarray");
    
 
    mygrid2 = new dhtmlXGridObject('mygrid_container2');
    mygrid2.setImagePath("codebase/imgs/");
    mygrid2.setHeader("Name, Slot");
    mygrid2.setInitWidths("150,50");
    mygrid2.setColAlign("left,right");
    mygrid2.setSkin("light");
    mygrid2.enableEditEvents(false,false,false);
  	mygrid2.enableDragAndDrop(true); 
    mygrid2.init();
    mygrid2.load("_data.js","jsarray");
    mygrid2.parse(data2,"jsarray");

</script>
END;
*/
include_once ("template.inc");
?>