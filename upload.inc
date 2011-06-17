<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
 
$id = $_POST['id'];
$activity = $_POST['activity'];

if($activity=="Upload") {
    $tmpname = $_FILES['pict_file']['tmp_name'];
    $uploadFile = $_FILES['pict_file']['name']; 
    
    debugPrint("tmpname: $tmpname uploadFile: $pictDIR$uploadFile<br>");
    
    $File = $pictDIR . $uploadFile;
    
    @unlink($File);
//    if(is_file($File)) { echo ("File Unlink Attempt " . unlink($File)); }

    if (move_uploaded_file($tmpname, $File)) {
       debugPrint ("Success");
       updateStudentField($id, 'picture', $uploadFile);
    //   alert("File is valid, and was successfully uploaded.");
    } else {
         debugPrint ("Failure");
    //   alert("Possible file upload attack!");
    }
    
} else {
    $student = getStudentInfo ($id);
    $File = $pictDIR . $student['picture'];
//    echo $File;
//    if(is_file($File)) { unlink($File); }
    updateStudentField($id, 'picture', "");
}

 echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=studentInfo&id=$id\"> ");

?>
