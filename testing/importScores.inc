<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================


include_once ( $rootPATH . '/lib/import/include.import.inc');

if(!PDisplayB(B14) ) {
	Header("Location: index.php?cmd=noPrivilege&type=Testing&notes=Can not see testing data");
}

$value= $currentUser . date("_Y-m-d_H-i-s");
//echo $value;

$title = 'Import File';

$table = 'testscores';

// $tablefields = 'AlaskaID:  alaskaid  : import, Year: year: import';

$tablefields = "
AlaskaID:  alaskaid  : import, 
Year: year: import, 
Test: test: import, 
Site: site: import, 
Grade Level: gradelevel: import, 
Standard: standard: import, 
Status (Scored): status: import,

Scale Value: value: import, 
Scale Needed: needed: import, 
Scale Difference: difference: import,
Proficiency: level: import, 

Raw Value: raw_value: import, 
Raw Needed: raw_needed: import, 
Raw Difference: raw_difference: import,

ImportGrp: importgrp: value $value ";

$tablefields = str_replace("\r\n", "", $tablefields);

$body .= DefineImportButton($title, $table, $tablefields);

include_once ("template.inc");

?>
