{extends file="layout.tpl"}
{block name="title"}{$pageTitle}{/block}
{block name="body"}
<div style="width:1024px; margin: 0 auto">
	Edit Discipline: {$dispID}
	<br />
	<a href="?cmd=disciplineList&studentid={$studentid}">List Discipline</a>
	<table border="0" cellpadding="2" cellspacing="2" width="100%">
		<tbody>
			<tr>
				<td align="left">
					<br />
					<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="4">Discipline Log Entry </font>
					<font class="big" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">- {$studentname}</font>
					<br />
					<h3>{$msg|default:'&nbsp;'}</h3>
					<div align="right">
						<table border="0" cellpadding="0" cellspacing="2">
							<tbody>
								<tr>
									<td nowrap="nowrap" align="right">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="4">"Just the facts..."</font>
										<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<a title="Dragnet Series - Wikipedia" href="http://en.wikipedia.org/wiki/Dragnet_%28drama%29" target="_blank">.</a>
										</font>
										<br />
										<p>
											<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												Sergeant Joe Friday, 
												<a title="Dragnet Series - Wikipedia" href="http://en.wikipedia.org/wiki/Dragnet_%28drama%29" target="_blank">Dragnet</a>
												<br />
												<br />
												<b><font color="#ff0033">Note:</font></b>
												Some required information is only visible for Special Education students
											</font>
										</p>
									</td>
									<td align="center" nowrap="nowrap" valign="top">
										<div align="right">
											<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular">
												<a href="http://en.wikipedia.org/wiki/Dragnet_%28drama%29">
													<img src="https://dart.bssd.org/images/facts_sm.gif" alt="" align="right" border="0" height="114" width="91" />
												</a>
											</font>
										</div>
									</td>
								</tr>
							</tbody>
						</table>
					</div>
					<blockquote>
						<div align="left">
							<div class="noteimportant">
								<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
								All discipline events are entered here.  This includes both relatively minor 
								infractions, as well as more serious ones. Although some of this data is used 
								for state and federal reporting, the majority of it is <b>not used </b>
								outside the district, but is important for us so that students get the 
								assistance they need to succeed.  Please be as accurate and non-judgemental as 
								possible.  Focus  on the facts in your responses. 
								</font>
							</div>
						</div>
					</blockquote>
				</td>
			</tr>
			<tr>
				<td>
					<div align="center">
						<form action="?cmd=disciplineEdit&disciplineid={$dispID}" method="post">
							<table border="0" cellpadding="2" cellspacing="2" width="100%">
								<tbody>
								<tr>
									<td colspan="4" align="center">
										<input type=hidden name=disciplineid value="{$dispID}">
										<font color="#000000" face="Arial,Helvetica">
											<b>
												<br>
											</b>
										</font>
									</td>
								</tr>
								<tr>
									<td colspan="4" bgcolor="#ccffff">
										<div align="right">
											<b>
												<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">Enter Discipline Log Data</font>
											</b>
										</div>
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Incident Date:</b>
										</font>
									</td>
									<td width="197">
										<div align="left">
											<input name="i_incidentdate" value="{$incidentdate}" size="20" type="text">
										</div>
									</td>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>{$disabilityLabel|default:'&nbsp;'}</b>
										</font>
									</td>
									<td nowrap="nowrap" width="15%" align="left">
										<a href="%28EmptyReference%21%29">
											<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">{$disabilityCode|default:'&nbsp;'}</font>
										</a>
									</td>
								</tr>
								<tr>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Current Log Entries:</b>
										</font>
									</td>
									<td width="197">
										<font color="#cc0000" size="2">
											<b> </b>
										</font>
										<a href="{$logentriesLink}">{$logentries}</a>
									</td>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>{$daysAvailableLabel|default:'&nbsp;'}</b>
										</font>
									</td>
									<td width="15%">
										<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">{$daysAvailableNote|default:'&nbsp;'}</font>
									</td>
								</tr>
								<tr>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>ISS Days:</b>
										</font>
									</td>
									<td width="197">
										<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">{$issDays} days <u>before</u> today</font>
									</td>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Supension Days:</b>
										</font>
									</td>
									<td width="15%" align="left">
										<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">{$suspensionDays} days <u>before</u> today</font>
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Non-Weapon Incident:</b>
										</font>
									</td>
									<td width="197">
										{html_options name="i_nonweapon" id="nonweapon" options=$nonweaponMenu selected=$nonweapon}
									</td>
									<td nowrap="nowrap" width="15%">
										<div align="left">
											<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<b>Weapon Incident:</b>
											</font>
										</div>
									</td>
									<td width="15%">
										{html_options name="i_weapon" id="weapon" options=$weaponMenu selected=$weapon}
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Number of Victims:</b>
										</font>
									</td>
									<td width="197">
										{html_options name="i_victimno" id="victimno" options=$victimnoMenu selected=$victimno}
									</td>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Victim Type:</b>
										</font>
									</td>
									<td width="15%">
										{html_options name="i_victimtype" id="victimtype" options=$victimMenu selected=$victimtype}
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Police Involved?:</b>
										</font>
									</td>
									<td width="197">
										{html_options name="i_police" id="police" options=$policeMenu selected=$police}
									</td>
									<td bgcolor="#33cc33" nowrap="nowrap" width="15%">
										<div align="center">
											<font color="black" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<b>Start Date</b>
											</font>
										</div>
									</td>
									<td rowspan="4" nowrap="nowrap">
										<div align="left">
											<img src="{$picture}" alt="" align="left" border="0" height="105" width="95">
											<br>
											<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<b>Guardian Contact</b>
												<br />
												{$guardian}
											</font>
										</div>
									</td>
								</tr>
								<tr>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Consequence:</b>
										</font>
									</td>
									<td width="197">
										{html_options name="i_consequence" id="consequence" options=$consequenceMenu selected=$consequence}
									</td>
									<td bgcolor="#33cc33" width="15%">
										<input name="i_startdate" value="{$startdate}" size="20" type="text">
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Length in School Days:</b>
										</font>
									</td>
									<td width="197">
										{html_options name="i_lengthdays" id="lengthdays" options=$lengthMenu selected=$lengthdays}
									</td>
									<td bgcolor="red" width="15%">
										<div align="center">
											<font color="black" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<b>End Date</b>
											</font>
										</div>
									</td>
								</tr>
								<tr>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Status:</b>
										</font>
									</td>
									<td width="197">
										{html_options name="i_dstatus" id="dstatus" options=$statusMenu selected=$dstatus}
									<br />
									</td>
									<td bgcolor="red" width="15%">
										<input name="i_enddate" value="{$enddate}" size="20" type="text">
									</td>
								</tr>
								<tr>
									<td width="15%">
									</td>
									<td valign="top">
									</td>
									<td>&nbsp;</td>
									<td>&nbsp;</td>
								</tr>
								<tr>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Comments / Notes:</b>
										</font>
									</td>
									<td rowspan="4" colspan="2" valign="top">
										<textarea name="i_notes" rows="6" cols="50">{$notes}</textarea>
									</td>
									<td rowspan="4">
									</td>
								</tr>
								<tr>
									<td width="15%">
										<div align="center">
										</div>
									</td>
								</tr>
								<tr>
									<td width="15%">
									</td>
								</tr>
								<tr>
									<td width="15%">
									</td>
								</tr>
<!-- SpedEd -->
								{if $spedEd}
								<tr>
									<td colspan="4" bgcolor="#ccffff">
										<div align="right">
											<b>
												<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">Required Special Education Data </font>
											</b>
											<b> </b>
										</div>
									</td>
								</tr>
								<tr>
									<td valign="top" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Educational Services:</b>
										</font>
										<font color="#000000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<strong>
												<br>
											</strong>
										</font>
									</td>
									<td valign="top" width="197">
										{html_options name="i_eduservice" id="eduservice" options=$serviceMenu selected=$eduservice}
									</td>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>IEP Team Meet?:</b>
										</font>
									</td>
									<td width="15%">
										{html_options name="i_iepmeet" id="iepmeet" options=$iepMenu selected=$iepmeet}
									</td>
								</tr>
								<tr>
									<td valign="top" width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Related to Disability?:</b>
										</font>
										<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<br>
										</font>
									</td>
									<td valign="top" width="197">
										{html_options name="i_relateddisability" id="relateddisability" options=$disabilityMenu selected=$relateddisability}
									</td>
									<td width="15%">
										<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>Date of Meeting:</b>
										</font>
									</td>
									<td width="15%">
										<input name="i_meetdate" value="{$meetdate}" size="20" type="text">
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
										<div align="center">
											<font color="#330066" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<b>Special Ed Questions?</b>
											</font>
											<font color="#cc0000" face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<b>
													<br>
												</b>
											</font>
											<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
												<br>
												<a href="mailto:rconcilus@bssd.org">
													<b>Contact Rebecca!</b>
												</a>
												<br>
												<br>
											</font>
											<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="1">
												<i>

									She'd rather help you now<br>


									 than testify in court!!!</i>
											</font>
										</div>
									</td>
									<td rowspan="2" colspan="3">
										<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
											<b>
												<font color="red">Important Note:</font>
											</b> A "<i>
												<b>
													<a title="Alaska EED Special Education Handbook" href="http://www.eed.state.ak.us/tls/SPED/Handbook05/part4.html#sec12" target="_blank">Manifestation Determination</a>
												</b>
											</i>" must be held for any student that is being suspended for 7-10 consecutive days, or if the the proposed suspension goes over 10 days of cumulative suspension time for the current school year.<br>
											<br>

								In addition, if the the incident is found by the IEP team to be related to the student's disability, the student <i>
												<b>
													<a title="Alaska EED Special Education Handbook" href="http://www.eed.state.ak.us/tls/SPED/Handbook05/part4.html#sec12" target="_blank">can't be suspended</a>
												</b>
											</i> for that incident, must conduct a "Functional Behavior Analysis", and create or review a behavior plan.<br>
										</font>
										<div align="left">
											<ul>
												<li type="disc">
													<font face="Arial,Helvetica,Geneva,Swiss,SunSans-Regular" size="2">
														<a title="Alaska EED Special Education Handbook" href="http://www.eed.state.ak.us/tls/SPED/Handbook05/part4.html#sec12" target="_blank">Alaska EED Special Education Regulations - Student Discipline</a>
													</font>
												</li>
											</ul>
										</div>
									</td>
								</tr>
								<tr>
									<td nowrap="nowrap" width="15%">
									</td>
								</tr>
								{/if}
<!-- SpedEd -->
								<tr>
									<td width="15%">
									</td>
									<td colspan="3">
										<div align="center">
											<br>
											<input name="gobutton" value="Save Log Entry" type="submit">
										</div>
									</td>
								</tr>
								</tbody>
							</table>
						</form>
					</div>
				</td>
			</tr>
		</tbody>
	</table>
</div>
{/block}
