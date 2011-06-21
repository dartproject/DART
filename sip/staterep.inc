<?php
// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================

set_time_limit(0);

$site = $_GET['site'];
$year = $CurrentYear;
$year = $_GET['year'] == '' ? $CurrentYear : $_GET['year'];
$optionYears = getSipYearOption ($year);
$url = $_SERVER[PHP_SELF];
while(list($name, $val) = each($_GET)) {
	if($name != 'year') { $get .= "&$name=$val"; }
}

$yearSelections .= <<<END
<form>
	Select Year: <select name=year onchange="window.location='$url?year='+this.value+'$get'">
		$optionYears
	  </select>
</form>
END;


$siteList = "<option value=\"\" >All</option>" . getSitesOptions($site);

$siteOptions = "<form action=index.php method=get>
				<input type=hidden name=module value = sip>
				<input type=hidden name=year value = '$year'>
				<input type=hidden name=cmd value = staterep>
				<select name=\"site\" id=\"site\" onChange=\"submit();\">" . 
				$siteList . 
                "</select>
                </form>";

$sips = produceSiteTable($site, $year, true);

$body .= <<<END
<table><tr><td>&nbsp;</td><td>
$siteOptions $yearSelections
$sips
</td></tr>
</table>
END;


include_once ("template.inc");
?>