<div align="left">
    <b><font color="#0066ff">Logged In As:</font></b><br>
    <img src="{$imageURL}dart1.gif" alt="" height="67" width="77" border="0"><br>
    <b><font color="#0066ff">{$currentUserName}</font></b>

    <!-- TRANSCRIPT MENU -->
{if $showTranscriptOptions}
    <br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=transcriptsDefine">Define Transcript</a>
    <br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0"><a href="index.php?cmd=editTranscripts">Edit Transcripts</a><br>
    {/if}

    <!-- DART HOME INFORMATION -->
    <br><b><font color="#0066ff">DART Info<br></font></b>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=logout">Log Out</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=home">Dart Home</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=editProfile">Edit Profile</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="mailto:dart@bssd.org" target=_blank>Feedback</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=districtrep" target=_blank>SIP Plan</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=siterep" target=_blank>Site SIP Plan</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=teacherrep" target=_blank>Teacher SIP Plan</a><br>

    <!-- Search Students -->
{if $showSearch}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=search">Search</a><br>
{/if}

    <!-- Dashboard -->
{if $showDashboard}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=Dashboard">Dashboard</a><br>
{/if}

    <!-- My Groups -->
{if $showMyGroups}
    <br>
    <font color="#0066ff"><b>My Groups</b></font><br>
    {foreach $myGroups as $group}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href=index.php?cmd=showscores&p1={$group.listid}">{$group.listname}</a>
    <!--        <font color="#0066ff">   <br>-->
    {/foreach}
{/if}

    <!-- Shared Groups -->
{if $showSharedGroups}
    <br><font color="#0066ff">
        <b>Shared Groups<br>
        {$currentMySite}</b>
    </font><br>
    {foreach $sharedGroups as $group}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href=index.php?cmd=showscores&p1={$group.listid}">{$group.listname}</a>
    <!--        <font color="#0066ff">   <br>-->
    {/foreach}
{/if}

    <!-- Private Shared Groups -->
{if $privateSharedGroups !=null}
    <br><font color="#0066ff"><b>Private Shared List</b></font><br>

    {foreach $privateSharedGroups as $group}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href=index.php?cmd=showscores&p1="{$group.listid}">{$group.listname}</a>
    <!--<font color="#0066ff">--><br>
    {/foreach}
 {/if}

    <!-- Manage Groups -->
{if $showManageGroups}
    <br><font color="#0066ff"><b>Manage Groups</b></font><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=newlist">New Group</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=editlist">Edit Groups</a><br>
{/if}

    <!-- Reports -->
 {if $showReports}
    <br><font color="#0066ff"><b>Reports</b></font><br>
 {/if}

    <!-- Official Report -->
 {if $showOfficialReport}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=reportsInd">Official</a><br>
 {/if}

    <!-- Drill Down -->
 {if $showDrillDown}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=pivot">Drill Down!</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=extraPacingReport">PASS</a><br>
 {/if}

    <!-- Admin Area -->
{if $showAdminArea}
    <br><font color="#0066ff"><b>Admin Area</b></font><br>
{/if}

    <!-- Users Admin -->
 {if $showUsers}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=userAdmin&site=$currentMySite&status=Active">Users {$currentMySite}</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=InternalError">Internal Error</a><br>
 {/if}

    <!-- Test Grd and Red Button -->
 {if $showRedButton_Grd_Test}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=bigRed">Big Red Button</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=edittestlevel">Edit Test Level</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=editgs">Edit Grd Setup</a><br>
 {/if}

    <!-- Edit Standards -->
 {if $showEditStandards}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=editStandards">Edit Standards</a><br>
 {/if}

    <!-- Edit School Calendar -->
  {if $showEditSchoolCal}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=SchoolCalendar&site=DIO&year={$currentYear}">Edit School Cal</a><br>
  {/if}

    <!-- Progress -->
{if $showProgress}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=progress&site=$currentMySite">Progress {$currentMySite}</a><br>
{/if}

    <!-- History -->
{if $showHistory}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=history">History Toggle</a><br>
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=historylogin">History Login</a><br>
{/if}

    <!-- Mass Import -->
{if $showMassImport}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=uploadInput">Mass Import</a><br>
{/if}

    <!-- Edit  Notes -->
{if $showEditNotes}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=editNotes">Edit Notes</a><br>
{/if}

    <!-- Edit Report Notes -->
{if $showEditReportNotes}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a href="index.php?cmd=editRepNotes">Edit Report Notes</a><br>
{/if}

    <!-- Student Management -->
{if $showStudentManagement}
    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a title="DART Enrollment Form" href="enrollment_form.shtml">Add Student</a><br>

    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a title="DART Drop &amp; Transfer Form" href="transfer_form.shtml">Drop/ Transfer</a><br>

    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a title="DART Level Adjustment Form" href="schedule_form.shtml">Level Change</a><br>

    <img src="images/10_h.gif" alt="" height="2" width="10" border="0">
    <a title="DART Enrollment Form" href="forms/elective_form.shtml">Add Elective</a><br>
{/if}

    <br />

{foreach $modulesLinks as $moduleLink}
{$moduleLink}
{/foreach}
</div>