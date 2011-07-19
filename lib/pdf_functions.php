<?php
/*
KOIVI HTML Form to FDF Parser for PHP (C) 2004 Justin Koivisto
Version 2.1.2
Last Modified: 9/12/2005

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or (at
    your option) any later version.

    This library is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this library; if not, write to the Free Software Foundation,
    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 

    Full license agreement notice can be found in the LICENSE file contained
    within this distribution package.

    Justin Koivisto
    justin.koivisto@gmail.com
    http://koivi.com
*/

/*
*   createFDF
*
*   Takes values submitted via an HTML form and fills in the corresponding
*   fields into an FDF file for use with a PDF file with form fields.
*
*   @param  $file   The pdf file that this form is meant for. Can be either
*                   a url or a file path.
*   @param  $info   The submitted values in key/value pairs. (eg. $_POST)
*   @result Returns the FDF file contents for further processing.
*/



function createFDF($file,$info){
    echo "HELLO";
    $data="%FDF-1.2\n%����\n1 0 obj\n<< \n/FDF << /Fields [ ";
    foreach($info as $field => $val){
    	if(is_array($val)){
        	$data.='<</T('.$field.')/V[';
        	foreach($val as $opt)
        		$data.='('.trim($opt).')';
        	$data.=']>>';
    	}else{
        	$data.='<</T('.$field.')/V('.trim($val).')>>';
    	}
    }
    $data.="] \n/F (".$file.") /ID [ <".md5(time()).">\n] >>".
        " \n>> \nendobj\ntrailer\n".
        "<<\n/Root 1 0 R \n\n>>\n%%EOF\n";
    echo "HELLO";
    writeNewFile($file, $data);
    return $data;
}

function writeNewFile ($file, $fdf) {
        if($fp=fopen($file,'w')){
            fwrite($fp,$fdf,strlen($fdf));
            $CREATED=TRUE;
        }else{
            echo 'Unable to create file: '.$fdf_file.'<br><br>';
            $CREATED=FALSE;
        }
        fclose($fp);
}

function copyFile ($file, $tmp) {
/*	if($fp=fopen($file,'w')){
		echo "Open File<br>";
		$CREATED=TRUE;
	}else{
		echo 'Unable to create file: '.$fdf_file.'<br><br>';
		$CREATED=FALSE;
	}
	fclose($fp);
	echo "Close File<br>";

	if (touch($file)) {
echo "$FileName created";
} else {
echo "Sorry, could not create $FileName";
}
*/
  $cmd = "cp $file $tmp";
//  echo $cmd;
  passthru($cmd);

}

function createPDFFile ($template, $pdfFile, $fdfFile) {
  global $pdftk;
  
  $cmd = "$pdftk $template fill_form $fdfFile output $pdfFile flatten";
//  echo "$cmd<br>";
  passthru( $cmd);
}

function mergePDFFile ($template, $pdfFile, $tmpfile) {
  global $pdftk;
  //  pdftk 1.pdf 2.pdf 3.pdf cat output 123.pdf
  $cmd = "cp $pdfFile $tmpfile";
  passthru($cmd);
//  echo "$cmd<br>";
  
  $cmd = "$pdftk $tmpfile $template cat output $pdfFile";
//  echo "$cmd<br>";
  passthru( $cmd);
}

function exportPDFFile($file) {

  header( 'Content-type: application/pdf' );
  header( 'Content-disposition: attachment; filename=test.pdf' ); // prompt to save to disk
  readfile($file);
}
?>
