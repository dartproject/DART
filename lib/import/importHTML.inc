
function trim(s)
{
   return s.replace(/(^\s+)|(\s+$)/g, "");
}

////////////////////////////////////////////////////////////////////////////
// function to get the instance of xmlHttp object 
var xm = cm();
function cm()
{
   var xt;
   try 
   {
      xt = new XMLHttpRequest();
   }
   catch(e) 
   {
      var XmlHttpVersions = new Array("MSXML2.XMLHTTP.6.0", "MSXML2.XMLHTTP.5.0", "MSXML2.XMLHTTP.4.0", "MSXML2.XMLHTTP.3.0", "MSXML2.XMLHTTP", "Microsoft.XMLHTTP");
      // pass through the whole array and get the result if match found
      for (var i=0; i<XmlHttpVersions.length && !xt; i++)
      { 
         try
         {
            xt = new ActiveXObject(XmlHttpVersions[i]); 
         } 
         catch (e) 
         {
         }
       }
     }
   if (!xt) 
   {
      alert("Some functions may not work properly. Try upgrading your browser.");
      return false;
   }
   else
   { 
      return xt;
   } 
}
/////////////////////////////////////////////////////////////////////////////////////

function callServer(XMM, URLL, Responsee, Params)
{
   if(XMM)
   {
      if (XMM.readyState == 4 || XMM.readyState == 0) 
      {
        XMM.open("POST", URLL, true);
        XMM.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        XMM.send(Params);
        XMM.onreadystatechange = Responsee;
     }
     else 
     {
        setTimeout("callServer(XMM, URLL, Responsee);", 500);
     } 
   } 
}

/////////////////////////////////////////////////////////////////////////////////////



function preview()
{
   var param = 'sqlcsvcombination=';
   
   // real field name array is also linked with whether to import data from
   // csv or not like fname#import and userid#1
   var allempty = true;
   for (var i = 0; i < mysqlRealFieldNamesArray.length; i++)
   {
      var mysqlRealFieldNamesArrayImportFree = mysqlRealFieldNamesArray[i].split('#');
	  // will determine whether to import or not
	  var importOrNot = mysqlRealFieldNamesArrayImportFree[1]; 
	  var mysqlRealFieldName = mysqlRealFieldNamesArrayImportFree[0];
      var mysqlRealFieldNameID = document.getElementById(mysqlRealFieldName);
      var trimmedValue = trim(mysqlRealFieldNameID.value);
      var replacedValue = trimmedValue.replace(/,/g, "|").replace(/&/g, "|");
	  if (replacedValue !== '')
	   allempty = false;
      param += mysqlRealFieldName + ':' + replacedValue + ':' + importOrNot;
      if (i != (mysqlRealFieldNamesArray.length - 1))
         param += ',';
   }
   if (allempty)
   {
      alert('All fields cannot be left blank.\nYou must provide atleast one Table-CSV combination.');
	  return false;
   }
   
   param += '&tablename=<?php echo $tablename; ?>' + '&tablefields=<?php echo $tablefields; ?>' + '&preview=show';
   document.getElementById('main#').innerHTML = '<h4>Loading, please wait...</h4>';
   callServer(xm, 'index.php?cmd=preview', previewRes, param);
}




function previewRes()
{
   if (xm.readyState == 4)
   {
      if (xm.status == 200)
      {
         var sendRes = xm.responseText;
        document.getElementById('main#').innerHTML = sendRes;
      }
   }
}

function insertData()
{
   var param = 'preview=insert';
   document.getElementById('main#').innerHTML = '<h4>Exporting data to database...</h4>';
   callServer(xm, 'index.php?cmd=preview', insertDataRes, param); 
}

function insertDataRes()
{
   if (xm.readyState == 4)
   {
      if (xm.status == 200)
      {
         var sendRes = xm.responseText;
        document.getElementById('main#').innerHTML = sendRes;
      }
   }
}
// ]]>
</script>
<style type="text/css">
<!--
.lft {
	text-align: right;
}
td, div {
	font-family: Verdana, Arial, Helvetica, sans-serif;
	font-size: 12px;
}
.error       { color: #FFFFFF; background-color: #FF6464 }
-->
</style>
</head>

<body>
<div id="main#">
<table width="100%" align="center" cellpadding="2" cellspacing="2">
  <tr>
    <td width="55%" class="lft"><b>Table to import into</b></td>
    <td width="10%"></td>
    <td width="35%"><b>CSV File</b></td>
  </tr>
  <tr>
    <td class="lft" valign="top"><table width="100%" cellspacing="2" cellpadding="2">
    
    <?php
    for ($i = 0; $i < count($easySqlFields); $i++)
    {
     $show = '';
	 $easySqlFieldsTemp = explode('#',$easySqlFields[$i]);
	 if ($easySqlFieldsTemp[1] !== 'import')
	    $show = 'none';
	 echo '<tr style="display:'.$show.'"><td width="53%" class="lft">'.$easySqlFieldsTemp[0].':</td>'
        .'<td width="47%"><input  type="text" id="'. $realSqlFields[$i] .'" onfocus="this.className = \'\';" /></td></tr>';
    } 
    ?> 
      </table></td>
    <td></td>
    <td valign="top"><table width="100%" cellspacing="2" cellpadding="6">
    <?php
    for ($i = 0; $i < count($csvHeadersArray); $i++)
    {
      echo "<tr><td>".$csvHeadersArray[$i]."</td></tr>";
     }
    ?>
      </table></td>
  </tr>
  <tr>
    <td class="lft" colspan="3">
	<p style="text-align: center"><input type="button" name="Button" value="Preview" id="preButton" onClick="preview();"/></td>
  </tr>
</table>
</div>
</body>
</html>