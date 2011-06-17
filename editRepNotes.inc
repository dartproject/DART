<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$site = $_GET['site'];
$priv = Privilege(A8);

if($priv == 'none') { NoPriv("denied Edit", "site=$site"); }

$rnotes = getRepNotes($site);
$notes = stripslashes($rnotes['comment']);

$js = "function editSelection(value) {
     if (value == \"#save_changes\") {
        toggle.loc.value = location.href;
        toggle.submit();
     } else {
     window.location=\"index.php?cmd=editRepNotes&site=\" + value;
     }
 }";

$pulldownMenu = "<select name=selectedSite onChange='editSelection(this.value)'>
													<option value=''>Choose One</option>";

$sites = getSites($priv);													
foreach ($sites as $siteRec) {
    $value = $siteRec['siteid'];
    $pulldownMenu .= "<option value='$value' " . selected($site, $value) . ">$value</option>
    ";
}
				
$pulldownMenu .= "</select>";		


$body .= "<form name=toggle method=post action=index.php?cmd=saveRepNotes>
          <input type=hidden name=loc>
          $pulldownMenu
          <input type=reset value=reset>
          <input type=submit value='save all changes'><br>
          <font size=\"2\"><b>Report Card:</b></font><br>
					<textarea name=\"notes\" rows=\"8\" cols=\"80\">$notes</textarea><br>
          </form>";


include ("template.inc");

?>
