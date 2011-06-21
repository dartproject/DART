<?php

// session_start(); // start session
if ($_POST['preview'] == 'show')
{

$csvValues = $_SESSION['csvvalues']; // csv values array with the index the name of the csv header
$csvHeadersArray = $_SESSION['csvheaders']; // csv file headers array


$sqlcsvcombination = $_POST['sqlcsvcombination']; // posted sql csv combination
// this combination was choosen by the user
$tablename = $_POST['tablename']; // name of the mysql table to whixh data will be inserted
$tablefields = $_POST['tablefields'];


// build the query
// Note: $sqlcsvcombination is in this format fname:FirstName:import,userid::1
$insertSets = '';
$csvOutput = '<tr>';
$sqlcsvcombinationArray = explode(',',$sqlcsvcombination);
for ($i = 0; $i < count($sqlcsvcombinationArray); $i++)
{
   $sqlcsvcombinationNew = $sqlcsvcombinationArray[$i];
   $sqlcsvcombinationNew = explode(':',$sqlcsvcombinationNew);
   $insertSets .= $sqlcsvcombinationNew[0] . "='";
   if ($sqlcsvcombinationNew[2] == 'import')
   {
      $sqlcsvValueNew = trim($sqlcsvcombinationNew[1]);
	  $sqlcsvValueNew = str_replace('|',',',$sqlcsvValueNew);
	  $insertSets .= $sqlcsvValueNew . "'";
	  if ($sqlcsvValueNew !== '')
	     $csvOutput .= '<td>' . $sqlcsvValueNew . '</td>';
	  else
	     $csvOutput .= '<td><i>empty</i></td>';
   }
   else
   {
      $insertSets .= $sqlcsvcombinationNew[2] . "'";
   }
   if ($i != (count($sqlcsvcombinationArray) - 1))
      $insertSets .= ',';   
}
$csvOutput .= '<tr>';
$sql = "INSERT INTO ". $tablename ." SET " . $insertSets;


$SQL = array(); // array containing the sql queries
$CSV = array(); // csv output for preview purpose

$anycsvvalue = $csvValues[trim($csvHeadersArray[0])];
$anycsvvalue = explode(',',$anycsvvalue);

for ($i = 0; $i < count($anycsvvalue); $i++)
{
   $csvValuesArray = array();
   for ($j = 0; $j < count($csvHeadersArray); $j++)
   {
      $csvheader = trim($csvHeadersArray[$j]);
	  $csvvalues = explode(',',$csvValues[$csvheader]);
      $csvValuesArray[] = $csvvalues[$i];
   }
   $SQL[] = str_replace($csvHeadersArray, $csvValuesArray, $sql);
   $CSV[] = str_replace($csvHeadersArray, $csvValuesArray, $csvOutput);
}

$_SESSION['SQL'] = $SQL;


showPreview($sqlcsvcombination, $tablefields, $csvValues, $csvHeadersArray, $CSV);

}
else if ($_POST['preview'] == 'insert')
{
   @mysql_connect($dbhose, $dbuser, $dbpassword) or die("Couldn't connect to MySQL Host!");
	
	# try to select the defined database else output an error message
   @mysql_select_db($dbname) or die("Couldn't select the MySQL Database!");

   $SQL = $_SESSION['SQL'];
   for ($i = 0; $i < count($SQL); $i++)
   {
      $ok = mysql_query($SQL[$i]);
   }
   if ($ok)
   {
      echo '<br /><br /><h2>CSV file imported successfully into MySQL database!</h2><hr>';
   }
   else
   {
      echo '<br /><br /><h2>CSV data couldn\'t be inserted into the database possibly due to following errors:</h2>';
	  echo '<h4> - The tablefields definition contain field names which are not present in the database being used.</h4>'
	  .'<h4> - You donot have sufficient privileges to insert data into the database.</h4>'
	  .'<h4> - The server is too busy at the moment to handle the request.</h4>';
   }
   echo '<div align="center" style="margin-top:25px">'
       .'<input type="button" value="Close Window" onclick="window.close();" />'
       .'</div>';
}



function showPreview($sqlcsvcombination, $tablefields, $csvValues, $csvHeadersArray, $CSV)
{
   $sqlfields = array();
   $realsqlfields = array();
   $tablefieldsArray = explode(',',$tablefields);
   for ($i = 0; $i < count($tablefieldsArray); $i++)
   {
      $singlefields = explode(':', $tablefieldsArray[$i]);
	  if (trim($singlefields[2]) == 'import')
	  {
	     $sqlfields[] = trim($singlefields[0]);
		 $realsqlfields[] = trim($singlefields[1]);
	  }
   }
   $width = 100 / count($sqlfields);
   echo '<table width="100%" align="center" cellpadding="2" cellspacing="2">'
       .'<tr style="font-weight:bold">';
   
   for ($i = 0; $i < count($sqlfields); $i++)
   {
	  echo '<td width="'.$width.'%">'.$sqlfields[$i].'</td>';
   }
	 	 
   echo '</tr>';
   
   for ($i = 0; $i < count($CSV); $i++)
   {
      echo $CSV[$i];
   }
   	 
echo '</table><div align="center" style="margin-top:15px">'
     .'<input type="button" value="Accept" onclick="insertData();" />' 
     .'&nbsp;<input type="button" value="Cancel" onclick="window.close();" />'
     .'</div>';
}

?>