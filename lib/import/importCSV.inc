<?php

// fieldname used within the file <input> of the HTML form 
$fieldname = 'file'; 


// posted values
// name of the mysql table to which data will be inserted
$tablename = $_POST['table']; 
// specific pattern to show the mysql table field names to the user
$tablefields = $_POST['tablefields'];


// PHP upload errors 
$errors = array(1 => 'php.ini Max. CSV file size exceeded.', 
                2 => 'Html form Max. CSV file size exceeded.', 
                3 => 'CSV file import was only partial.', 
                4 => 'No CSV file was attached.'); 


// PHP's built-in uploading errors 
($_FILES[$fieldname]['error'] == 0) 
    or error($errors[$_FILES[$fieldname]['error']]); 
	
// name of the file (CSV) uploaded temporarily for import process
$tempname = $_FILES[$fieldname]['tmp_name'];
     
// check that the file we are working on really was the subject of an HTTP upload 
@is_uploaded_file($tempname) 
    or error('Not an HTTP upload'); 
	
/*
// check if the file uploaded is in .csv format and check if it is valid csv file
$s = explode('.',$_FILES[$fieldname]['name']);
if ($s[count($s) - 1] !== 'csv' || ($_FILES[$fieldname]['type'] !=='application/octet-stream' && $_FILES[$fieldname]['type'] !=='application/ms-excel'))
error('Not a CSV file format');

*/

// upload error handler function
function error($error) 
{ 
    echo '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"'."\n". 
    '"http://www.w3.org/TR/html4/strict.dtd">'."\n\n". 
    '<html lang="en">'."\n". 
    '    <head>'."\n".
	'<style type="text/css">'.
    '<!--'.
    '.txt {'.
	'font-family: Verdana, Arial, Helvetica, sans-serif;'.
	'font-size: 12px;'.
    '}'.
    '-->'.
    '</style>'. 
    '        <meta http-equiv="content-type" content="text/html; charset=iso-8859-1">'."\n\n". 
    '    <title>CSV file Import Error</title>'."\n\n". 
    '    </head>'."\n\n". 
    '    <body>'."\n\n". 
    '    <div class="txt">'."\n\n". 
    '        <h1>CSV File Import Failure!</h1>'."\n\n". 
    '        <p>An error has occured:<br>'."\n\n". 
    '        <span class="red"><b>' . $error . '</b></span>'."\n\n". 
    '     </div>'."\n\n". 
    ''; 
	echo '<br /><a href="javascript:history.back(1);" >Click here to go back.</a>';
    exit; 
} // end upload error handler 


/////////////////////////////////////////////////////////////////////////////////////////////////
// File uploaded to temporary directory successfully. Lets start the process to allow the user
// to map headrs of the CSV file with that MySQL table


//open CSV file and save the lines in a array
$fh = fopen($tempname,r); // open the file in read-only mode
$csvfilelines = file($tempname); // store the lines in array
fclose($fh); // close the file


// get the csv file headers and store them in a string - they are comma (,) seperated
$csvHeaders = trim($csvfilelines[0]);




// get the csv file values under each header and store them in an keyword defined array
// so they can be accessed by the header name. The values corresponding to each header will
// be stored comma seperated

$csvValues = array(); // the array that will hold the csv values with the index, the name of the respective header

$csvHeadersArray = explode(',',$csvHeaders); // get the csv headers from the csv headers string
// run the loop for as many times as there are number of single headers in the headers array
for ($i = 0; $i < count($csvHeadersArray); $i++) 
{
   // run the loop as many times as there are number of lines in the csv files
   // minus 1 since the first line is of headers
   for ($j = 1; $j < count($csvfilelines); $j++)
   {
      // line of the csv values seperated by commas(,)
	  $csvvaluesline = explode(',',$csvfilelines[$j]);
	  // csv value corresponding to cuurent csv header
	  $csvvalue = trim($csvvaluesline[$i]);
	   // insert the csv values in the $csvValues array where index is the csv header and the
      // values are inserted for each header seperated by comma
	  $seperateCsvHeaders = trim($csvHeadersArray[$i]); // get single csv header
	  // set it as index of the $csvValues
	  // array and get the corresponding values from the $csvfilelines
	  $csvValues[$seperateCsvHeaders] .= $csvvalue;
	  // insert values comma seperatd but no comma after last value
	  if ($j != (count($csvfilelines) - 1))
	     $csvValues[$seperateCsvHeaders] .= ',';
   }
}




////////////////////////////////////////////////////////////////////////////////////////////////
// Now we have $csvValues array in which csv values (,) seperated are inserted with
// index as their header name and $csvHeadersArray array which contain the CSV file headers
// insert the array in the session to be used in preview and import process
$_SESSION['csvvalues'] = $csvValues;
$_SESSION['csvheaders'] = $csvHeadersArray;
// Lets start output the html to allow user to map values of CSV header to that of MySQL fields


echo <<< WAS1
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Import CSV Data to MySQL Database</title>
<script type="text/javascript" language="JavaScript">
// <![CDATA[
var mysqlRealFieldNamesArray = new Array();
WAS1;
// get the array of easy and real mysql field name seperted by colon(:)
$easyRealMysqlFieldsArray = explode(',',$tablefields);
for ($i = 0; $i < count($easyRealMysqlFieldsArray); $i++)
{
   // splitted values in order Easy value, Real Value, Import or not (value)
   $easyRealImport = explode(':', $easyRealMysqlFieldsArray[$i]);
   $easySqlFields[$i] = trim($easyRealImport[0]) . '#' . trim($easyRealImport[2]);
   $realSqlFields[$i] = trim($easyRealImport[1]);
   $importSqlFields[$i] = trim($easyRealImport[2]);
   
   // check if the alue is to be imported from csv file or not
   if ($importSqlFields[$i] == 'import')
   {
      echo "mysqlRealFieldNamesArray.push('".$realSqlFields[$i]."#import');";
   }
   else
   {
       $valueImportField = explode('value', $importSqlFields[$i]);
	   $valueNotImport = trim($valueImportField[1]);
	   echo "mysqlRealFieldNamesArray.push('".$realSqlFields[$i]."#".$valueNotImport."');";
   }
}
include_once $rootPATH . '/lib/import/importHTML.inc';
?>