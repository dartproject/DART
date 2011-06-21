<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Import CSV data to MySQL Database</title>
<style type="text/css">
<!--
h3 {
	color: #666666;
	text-align: center;
	font-family: Arial, Helvetica, sans-serif;
}
.txt {
	font-family: Verdana, Arial, Helvetica, sans-serif;
	font-size: 12px;
}
-->
</style>
</head>

<body>
<form action="index.php?cmd=importCSV" method="post" enctype="multipart/form-data" name="form1" id="form1">
  <h3>Import CSV Data to MySQL Database </h3>
  <p>&nbsp;</p>
  <p class="txt" align="center">Please specify  the CSV file:
    <input type="file" name="file" />
	<input type="hidden" name="table" value="<?php echo $_GET['table']; ?>" />
	<input type="hidden" name="tablefields" value="<?php echo $_GET['tablefields']; ?>" />
  </p>
  <p class="txt">&nbsp;</p>
  <p align="center">
    <input type="submit" name="submit" value="Start Importing" /></p>
</form>
</body>
</html>
