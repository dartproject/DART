<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

$site = $_GET['site'];
$priv = Privilege(A29);

if($priv == 'none') { NoPriv("denied Edit", "site=$site"); }

$snotes = getNotes($site);
$important = $snotes['important'];
$warning = $snotes['warning'];
$tip = $snotes['tip'];

$js = "function editSelection(value) {
     if (value == \"#save_changes\") {
        toggle.loc.value = location.href;
        toggle.submit();
     } else {
     window.location=\"index.php?cmd=editNotes&site=\" + value;
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


$body .= "<form name=toggle method=post action=index.php?cmd=saveNotes>
          <input type=hidden name=loc>";

$body .= $pulldownMenu;
$body .= "<input type=reset value=reset>
          <input type=submit value='save all changes'><br>";

$body .= "<font size=\"2\"><b>Important:</b></font><br>
					<textarea name=\"important\" rows=\"8\" cols=\"80\">$important</textarea><br>
          <font size=\"2\"><b>Warning:</b></font><br>
					<textarea name=\"warning\" rows=\"8\" cols=\"80\">$warning</textarea><br>
          <font size=\"2\"><b>Tip:</b></font><br>
					<textarea name=\"tip\" rows=\"8\" cols=\"80\">$tip</textarea><br>";

$body .= "</form>";


include ("template.inc");

?>
