<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
 
$id = $_POST['id'];

$tmpname = $_FILES['pict_file']['tmp_name'];
$uploadFile = $_FILES['pict_file']['name']; //"uploads/" . 

//debugPrint("tmpname: $tmpname uploadFile: $pictDIR$uploadFile<br>");

$File = $pictDIR . $uploadFile;

if(is_file($File)) { unlink($File); }

if (move_uploaded_file($tmpname, $File)) {
//   debugPrint("Success");
   updateUserField($id, 'picture', $uploadFile);
//   alert("File is valid, and was successfully uploaded.");
} else {
//   debugPrint("Failure");
//   alert("Possible file upload attack!");
}

    echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=studentInfo&id=$id\"> ");


?>
