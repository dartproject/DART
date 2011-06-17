<?php

include_once ("../lib/machine.config.inc");
include_once ("../lib/ez_sql.inc");
include_once ("../lib/warning.inc");
include_once ("../lib/function.inc");

//include XML Header (as response will be in xml format)
if ( stristr($_SERVER["HTTP_ACCEPT"],"application/xhtml+xml") ) {
 		header("Content-type: application/xhtml+xml"); } else {
 		header("Content-type: text/xml");
}
echo("<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"); 
$m = $_GET['m'];
$l = $_GET['l'];
$s = $_GET['s'];

$sql = "select body from segments where module='$m' and lesson='$l' and session='$s'";
$results = $db->get_var($sql);

echo XML_Segment($results);

function XML_Segment($results)  {

	$body .= "<rows  id=\"0\">\n";

	$i = 0;
	foreach (explode("\r\n", $results) as $seg) {
		$step = explode(";", trim($seg));
		$id = trim($step[0]);
		if($id != '') {
			$swffile = trim($step[1]);
			$swf_fadein = trim($step[2]);
			$swf_fadeout = trim($step[3]);
			$flvfile = trim($step[4]);
			$flv_fadein = trim($step[5]);
			$flv_fadeout = trim($step[6]);
			$replay = trim($step[7]);
			$x = trim($step[8]);
			$y = trim($step[9]);
			$width = trim($step[10]);
			$height = trim($step[11]);
			$q = trim($step[12]);
			
			$body .= "<row id='r$i'><cell>$id </cell><cell>$swffile </cell><cell>$swf_fadein </cell><cell>$swf_fadeout </cell><cell>$flvfile </cell><cell>$flv_fadein </cell><cell>$flv_fadeout </cell><cell>$replay </cell><cell>$x </cell><cell>$y </cell><cell>$width </cell><cell>$height </cell><cell>$q </cell><cell>$a </cell></row>";
			$i++;
			
		}
//		reset ($seg);
	}
	
	$body .= "</rows>\n";
	$body2 = <<<END
	<rows  id="0">
		<row id='r1'><cell><?php echo $h ?> - 1</cell><cell>V<?php echo $h ?></cell></row>
		<row id='r2'><cell><?php echo $h ?> - 2</cell><cell>V<?php echo $h ?></cell></row>
		<row id='r3'><cell><?php echo $h ?> - 3</cell><cell>V<?php echo $h ?></cell></row>
		<row id='r4'><cell><?php echo $h ?> - 4</cell><cell>V<?php echo $h ?></cell></row>
	</rows>
END;
//	echo (htmlspecialchar($body));
	return($body);
}
/*
<rows  id="0">
	<row id='r1'><cell><?php echo $h ?> - 1</cell><cell>V<?php echo $h ?></cell></row>
	<row id='r2'><cell><?php echo $h ?> - 2</cell><cell>V<?php echo $h ?></cell></row>
	<row id='r3'><cell><?php echo $h ?> - 3</cell><cell>V<?php echo $h ?></cell></row>
	<row id='r4'><cell><?php echo $h ?> - 4</cell><cell>V<?php echo $h ?></cell></row>

</rows>
*/
?>
