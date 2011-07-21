{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="js"}
{/block}
{block name="css"}
{/block}
{block name="body"}
<div style="width:1024px; margin: auto; padding-bottom:30px;">
	<table border="0" cellpadding="0" cellspacing="2" width="100%">
		<tr>
			<td>
				<div style="text-align:left">
					<br />
					<font color="#cc0000" size="4" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
						Attendance Adjusment 
					</font>
					<font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
					- {$StudentName} 
					</font>
					<br />
				</div>
				<blockquote>
					<div style="text-align:left">
						<div class="noteimportant">
							<font size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
							This screen is used for adjusting a student's Attendance Record page. After entering your new code, the page will return to a refreshed and recalculated view of the Attendance Record you were working on.The chart below is written in plain English to to help you set the correct code.
							</font>
							<br />
							<br />
						</div>
					</div>
				</blockquote>
			</td>
		</tr>
		<tr>
			<td>
				<div style="text-align:center">
					<table border="0" cellpadding="2" cellspacing="2" width="100%">
						<tbody>
							<tr>
								<td colspan="3" bgcolor="#ccffff" align="right">
									<font class="big" size="2" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
										<b>Change Attendance Code {$editmonth}/{$editday}/{$year}</b>
									</font>
								</td>
							</tr>
							<tr>
								<td colspan="3">
									<table width="468" border="0" cellspacing="2" cellpadding="0">
										<tr>
											<td>
												&nbsp;
											</td>
											<td align="right">
												<table border="0" cellspacing="2" cellpadding="2">
													<tr>
														<td colspan="2" nowrap align="center">
															<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																<font size="2" color="red" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																	<b>Attendance Code Change</b>
																</font>
															</font>
														</td>
													</tr>
												</table>
											</td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td>
									<table border="1" cellspacing="2" cellpadding="2">
										<tbody>
											<tr>
												<td nowrap width="25" align="center">
													<b>
														<font size="1" color="white" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">.</font>
													</b>
												</td>
												<td nowrap align="center">
													<b>
														<font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
															Code List
														</font>
													</b>
												</td>
												<td nowrap align="center">

													<b>
														<font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
															Present
														</font>
													</b>
												</td>
												<td nowrap>
													<div align="center">
														<b>
															<font size="1" color="#ff0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
																Absent
															</font>
														</b>
													</div>
												</td>
											</tr>
											{foreach $chart as $row}	
											<tr>
												<td nowrap width="25" align="center" {if $row->Code neq "P"}bgcolor="red"{/if}>
													<b>
														<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" {if $row->Code neq "P"}color="white"{/if}>
															{$row->Code}
														</font>
													</b>
												</td>
												<td nowrap>
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">{$row->Description}</font>
												</td>
												<td nowrap>
													<div align="center">
														<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
															<b>{$row->Present|default:'&nbsp;'}</b>
														</font>
													</div>

												</td>
												<td nowrap align="center">
													<font size="1" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
														<b>{$row->Absent|default:'&nbsp;'}</b>
													</font>
													</div>
												</td>
											</tr>
											{/foreach}
										</tbody>
									</table>
								</td>
								<td>&nbsp;</td>
								<td>
									<form action="index.php" method="GET">
										<input type="hidden" name="cmd" value="AttendanceCalendar">
										<input type="hidden" name="year" value="{$year}">
										<input type="hidden" name="student" value="{$student}">
										<input type="hidden" name="editmonth" value="{$editmonth}">
										<input type="hidden" name="editday" value="{$editday}">
										<table border="1" cellspacing="2" cellpadding="2">
											<tr>
												<th>
												</th>
												<th>Attendance Code</th>
												<th>Site Attended</th>
											</tr>
											<tr>
												<td align="left">
													<b>AM Period</b>
												</td>
												<td>
														{html_options name="editcode0" options=$codeMenuAM selected=$codeAM}
												</td>
												<td>
														{html_options name="editsite0" options=$siteMenuAM selected=$siteAM}
												</td>
											</tr>
											<tr>
												<td align="left">
													<b>PM Period</b>
												</td>
												<td>
														{html_options name="editcode1" options=$codeMenuPM selected=$codePM}
												</td>
												<td>
														{html_options name="editsite1" options=$siteMenuPM selected=$sitePM}
												</td>
											</tr>
											<tr>
												<td colspan="3" align="center">
													<input type="submit" value="Save Change"> <input type=button onClick="javascript:window.location='?cmd=AttendanceCalendar&student={$student}&year={$CurrentYear}';" value='Cancel'>
												</td>
											</tr>
										</table>
									</form>
								</td>
							</tr>
						</tbody>
					</table>
				</div>
			</td>
		</tr>
	</table>
</div>
{/block}