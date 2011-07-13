{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
<script type="text/javascript" src="js/jquery.datepick.package/jquery.datepick.js"></script>
<script language="JavaScript" type="text/javascript" src="js/attendanceList.js"></script>
{/block}
{block name="css"}
<link rel="stylesheet" type="text/css" href="js/jquery.datepick.package/jquery.datepick.css" />
{/block}

{block name="body"}
<table border="0" cellpadding="0" cellspacing="2" width="100%">
	<tr>
		<td>
			<div align="left">
				<br>
				<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Group Attendance Entry </font>
				<font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- {$listName}</font>
			</div>
			<blockquote>
				<div align="left">
					<div class="noteimportant">
						<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Attendance is taken in batches. 
							Select the checkbox next to all of the names that will be marked in this batch, and then select
							the correct code at the bottom of the screen. This screen will refresh, and the next batch of codes can be entered.
						</font>
					</div>
				</div>
			</blockquote>
		</td>
	</tr>
	<tr>
		<td>
			<div>
				<div align="right" style="background-color:#ccffff;">
					<b>
						<font size="2" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
							<form id="selectDateForm" action=index.php method="get">
								<input type="hidden" name="cmd" value="AttendanceList" />
								<input type="hidden" name="listid" value="{$listID}" />
								<input type="hidden" name="period" value="{$period}" />
								{html_options name="month" id="month" options=$monthMenu selected=$month}
								{html_options name="day" id="day" options=$dayMenu selected=$day}
								<input name="year" id="year" value="{$year}" size="5" type="text" />
								<input type="hidden" name="date" id="date" />
								<div style="display: none;"> 
    								<a id="calImg" class="trigger">Select Date</a> 
								</div>
								<input type="submit" />
							</form>
						</font>
					</b>
				</div>
				<div align="center">
					Attendance Date: {$month}/{$day}/{$year} Period: {$periodname}
				</div>
				<div align="center">
					<font size="4" color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">Keeping a List &amp; Checking it Twice...</font>
				</div>
				<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
					<b>Absent:</b> {$absent} ::
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
					<table>
						<tr class="listhead">
							<td></td>
							<td align="center" nowrap>
								<a href="(EmptyReference!)">Name</a>
							</td>
							<td align="center">
								<div align="center">
									<a href="(EmptyReference!)">Student Number</a>
								</div>
							</td>
							<td align="center">
								<div align="center">
									<a href="(EmptyReference!)">AK Student ID</a>
								</div>
							</td>
							<td align="center">
								<div align="center">
									<a href="(EmptyReference!)">School Site</a>
								</div>
							</td>
							<td align="center">
								<div align="center">
									<a href="(EmptyReference!)">Testing<br>Grade</a>
								</div>
							</td>
							<td align="center">
								<div align="center">
									<a href="(EmptyReference!)">Age</a>
								</div>
							</td>
							<td align="center">
								<div align="center">
									<a href="(EmptyReference!)">Code</a>
								</div>
							</td>
							<td align="center" nowrap>
								<div align="center">
									Action
								</div>
							</td>
							<td align="center" nowrap>
								<div align="center">
									Edit
								</div>
							</td>
						</tr>
						{foreach $students as $student}
							<tr bgcolor="{cycle values="#f4f7fd,#E5E5E5"}">
								<td align="center" nowrap>
									<input type="checkbox" name="studentID[]" value="{$student.studentid} {$student.site}" class="radio">
								</td>
								<td nowrap>
									<a href="index.php?cmd=toggleStudent&p1={$student.studentid}">{$student.name}</a>
								</td>
								<td align="center">
									{$student.studentid}
								</td>
								<td align="center">
									{$student.alaskaid}
								</td>
								<td align="center">
									{$student.site}
								</td>
								<td align="center">
									{$student.grade}
								</td>
								<td align="center">
									{$student.age}
								</td>
								<td align="center">
									{$student.Code}
								</td>
								<td align="center" nowrap="nowrap">
									<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<a href="index.php?cmd=toggleStudent&p1={$student.studentid}">Details</a> &gt;&gt;
											<a href="index.php?cmd=AttendanceCalendar&student={$student.studentid}&year={$CurrentYear}">Attendance</a>
										</font>
								</td>
								<td nowrap="nowrap">
									<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
										&gt;&gt;<a href="index.php?cmd=advEdit&id={$student.studentid}">Edit</a>
									</font>
								</td>
							</tr>
						{/foreach}
					</table>
					<table align="center" width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td colspan="2">
								<img src="http://dart.bssd.org/images/1pix.gif" width="1" height="5" border="0" alt="">
							</td>
						</tr>
						<tr>
							<td valign="middle" nowrap>
								{if $stdcount > 0}
								<div align="left">&nbsp;
									<a href="javascript: ;" onclick="setCheckboxes('fieldsForm', true); return false;" class="action">Check All</a>&nbsp;/&nbsp;
									<a href="javascript: ;" onclick="setCheckboxes('fieldsForm', false); return false;" class="action">UnCheck All</a>
								</div>
								{else}&nbsp;{/if}
							</td>
							<td align="right">&nbsp;</td>
						</tr>
					</table>
					<table border="0">
						<tr>
							<td width="500">
								<div align="left">
									<div class="notewarning">
										<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
											Discipline-related attendance codes can only be adjusted through the Discipline Log screens. Click the code to view.
										</font>
									</div>
								</div>
							</td>
							<td width="145">
								<div align="center">
									<table border="0" cellspacing="2" cellpadding="2">
										<tr>
											<td nowrap>
												<div align="center">
													<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2" color="red">
														<b>Attendance Code Entry</b>
													</font>
												</div>
											</td>
										</tr>
										<tr>
											<td>
												<div align="center">
													{html_options name="selectCode" options=$codeMenu}
												</div>
											</td>
										</tr>
									</table>
								</div>
							</td>
							<td width="145">
								<div align="center">
									<input name="cmd2" onclick="javascript: return checkChecks();" value="Make it So!" type="submit" />
									<br />
								</div>
							</td>
						</tr>
					</table>
				</form>
			</div>
		</td>
	</tr>
</table>
{/block}
