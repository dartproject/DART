{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/jquery.datepick.package/jquery.datepick.js"></script>
<script type="text/javascript" src="js/extjs/bootstrap.js"></script>
<script language="JavaScript" type="text/javascript" src="js/attendanceList.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/jquery.datepick.package/jquery.datepick.css" />
<link rel="stylesheet" type="text/css" href="js/extjs/resources/css/ext-all.css" />
{/block}

{block name="body"}
<table border="0" width="100%">
	<tr>
		<td align="left">
			<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Group Attendance Entry </font>
			<font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- {$listName}</font>
		</td>
	</tr>
	<!--
	<tr>
		<td align="left">
			<blockquote>
				<div class="noteimportant">
					<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">To take attendance, select a group of students and then select
						the correct code at the bottom of the screen.
					</font>
				</div>
			</blockquote>
		</td>
	</tr>
	-->
	<tr>
		<td>
			<div align="right" style="background-color:#ccffff; width:800px;">
				<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
					<form id="selectDateForm" action=index.php method="get">
						<input type="hidden" name="cmd" value="AttendanceList" />
						<input type="hidden" name="listid" value="{$listID}" />
						<input type="hidden" name="period" value="{$period}" />
							{html_options name="month" id="month" options=$monthMenu selected=$month}
							{html_options name="day" id="day" options=$dayMenu selected=$day}
						<input name="year" id="year" value="{$year}" size="5" type="text" />
						<input type="hidden" name="date" id="date" value="{$year}-{$month}-{$day}"/>
						<div style="display: none;">
							<a id="calImg" style="cursor: pointer;" class="trigger">Select Date</a>
						</div>
						<input type="submit" />
					</form>
				</font>
			</div>
			<br />
			<div align="center">
				<font size="4" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Keeping a List &amp; Checking it Twice...</font>
			</div>
			<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
				<b>Absent:</b> {$absent|default:0} ::
				<b>Present:</b> {$present} ::
				<b>Today's Rate:</b> {$rate}%
			</font>
			<br />
			<form name="fieldsForm" action="index.php?cmd=AttendanceListRecord" method="post" >
				<input type="hidden" name="listid" value="{$listID}" />
				<input type="hidden" name="month" value="{$month}" />
				<input type="hidden" name="year" value="{$year}" />
				<input type="hidden" name="day" value="{$day}" />
				<input type="hidden" name="period" value="{$period}" />
				<input type="hidden" name="periodName" value="{$periodname}" />
				<input type="hidden" name="imageURL" value="{$imageURL}" />

				{* The table is generated in this div using Ext-js (see js/attendanceList.js and getAttendanceList.php) *}
				<div id="attendanceList"></div>

				<table border="0">
					<tr>
						<td width="500" align="left">
							<div class="notewarning">
								<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
									Discipline-related attendance codes can only be adjusted through the Discipline Log screens. Click the code to view.
								</font>
							</div>
						</td>
						<td width="145" align="center" nowrap>
							<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2" color="red">
								<b>Attendance Code Entry</b>
							</font>
							{html_options name="selectCode" options=$codeMenu}
						</td>
						<td width="145">
							<div align="center">
								<input name="cmd2" onclick="javascript: return checkChecks();" value="Make it So!" type="submit" />
							</div>
						</td>
					</tr>
				</table>
			</form>
		</td>
	</tr>
</table>
{/block}
