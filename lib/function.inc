<?php

// ==================================================================
//  Author: Robert Joseph (dart@vizmotion.com)
//	 Web: http://wiki.bssd.org/index.php/DART_System
// ==================================================================
/* CHANGE LOG
  12/9/09 rlj - fixed getSubjectInfo to also return level name

 */
define("GRADETHRESHHOLD", 80);

// <editor-fold defaultstate="collapsed" desc="Privileges">
// Can go up to A31 then has to start with Privledges B
// Defines for privileges
define("A2", 2);
define("A3", 4);
define("A4", 8);
define("A5", 16);
define("A6", 32);
define("A7", 64); // SFA Module Access
define("A8", 128); // Report Card Notes Function
define("A9", 256); // SFA Edit capabiities
define("A10", 512); // See History
define("A11", 1024);
define("A12", 2048);
define("A13", 4096); // update level
define("A14", 8192);
define("A15", 16384); // SIP module
define("A16", 32768); // SIP module edit
define("A17", 65536);
define("A18", 131072);
define("A19", 262144);
define("A20", 524288);
define("A21", 1048576); // discipline reports
define("A22", 2097152);
define("A23", 4194304); // ability to move students
define("A24", 8388608);
define("A25", 16777216); // edit level capabilities
define("A26", 33554432);
define("A27", 67108864);
define("A28", 134217728);
define("A29", 268435456);
define("A30", 536870912);

define("B2", 2);
define("B3", 4);
define("B4", 8);
define("B5", 16);
define("B6", 32);
define("B7", 64);
define("B8", 128);
define("B9", 256);
define("B10", 512);
define("B11", 1024);
define("B12", 2048);
define("B13", 4096);
define("B14", 8192);
define("B15", 16384);
define("B16", 32768);
define("B17", 65536);
define("B18", 131072);
define("B19", 262144);
define("B20", 524288);
define("B21", 1048576);
define("B22", 2097152);
define("B23", 4194304);
define("B24", 8388608);
define("B25", 16777216);
define("B26", 33554432);
define("B27", 67108864);
define("B28", 134217728);
define("B29", 268435456);
define("B30", 536870912);

function PDisplay($priv) {
    global $currentPrivA;

    return($priv & $currentPrivA);
}

function PDisplayB($priv) {
    global $currentPrivB;

    return($priv & $currentPrivB);
}

function PType($priv) {
    global $currentScopeA;

    $retValue = $priv & $currentScopeA ? "district" : "site";
    return($retValue);
}

function Privilege($priv) {
    global $currentScopeA, $currentPrivA;

    $active = $priv & $currentPrivA ? ($priv & $currentScopeA ? "district" : "site" ) : "none";
    debugPrint("Return Value: $active Priv: $priv currentPrivA: $currentPrivA currentScopeA: $currentScopeA");
    return ($active);
}

function PrivilegeB($priv) {
    global $currentScopeB, $currentPrivB;

    $active = $priv & $currentPrivB ? ($priv & $currentScopeB ? "district" : "site" ) : "none";
    debugPrint("Return Value: $active Priv: $priv currentPrivB: $currentPrivB currentScopeB: $currentScopeB");
    return ($active);
}

/* idEqual, siteEqual, View Scope, Edit Scope   */
$A2A3['0']['0']['none']['none'] = "no";
$A2A3['0']['0']['none']['site'] = "no";
$A2A3['0']['0']['none']['district'] = "edit";
$A2A3['0']['0']['site']['none'] = "no";
$A2A3['0']['0']['site']['site'] = "no";
$A2A3['0']['0']['site']['district'] = "edit";
$A2A3['0']['0']['district']['none'] = "view";
$A2A3['0']['0']['district']['site'] = "view";
$A2A3['0']['0']['district']['district'] = "edit";
$A2A3['0']['1']['none']['none'] = "no";
$A2A3['0']['1']['none']['site'] = "edit";
$A2A3['0']['1']['none']['district'] = "edit";
$A2A3['0']['1']['site']['none'] = "view";
$A2A3['0']['1']['site']['site'] = "edit";
$A2A3['0']['1']['site']['district'] = "edit";
$A2A3['0']['1']['district']['none'] = "view";
$A2A3['0']['1']['district']['site'] = "edit";
$A2A3['0']['1']['district']['district'] = "edit";
$A2A3['1']['0']['none']['none'] = "view";
$A2A3['1']['0']['none']['site'] = "view";
$A2A3['1']['0']['none']['district'] = "edit";
$A2A3['1']['0']['site']['none'] = "view";
$A2A3['1']['0']['site']['site'] = "view";
$A2A3['1']['0']['site']['district'] = "edit";
$A2A3['1']['0']['district']['none'] = "view";
$A2A3['1']['0']['district']['site'] = "view";
$A2A3['1']['0']['district']['district'] = "edit";
$A2A3['1']['1']['none']['none'] = "view";
$A2A3['1']['1']['none']['site'] = "view";
$A2A3['1']['1']['none']['district'] = "edit";
$A2A3['1']['1']['site']['none'] = "view";
$A2A3['1']['1']['site']['site'] = "view";
$A2A3['1']['1']['site']['district'] = "edit";
$A2A3['1']['1']['district']['none'] = "view";
$A2A3['1']['1']['district']['site'] = "view";
$A2A3['1']['1']['district']['district'] = "edit";

// </editor-fold>

function makePrivOption($priv, $value, $name) {
    if (PrivilegeB($priv) == 'district') {
        return ("<option value='$value'>$name</optoin>");
    } else {
        return("");
    }
}

function permission($kind) {
    $priv = userPrivilege();
    return (checked($kind, $priv));
}

function checked($val1, $val2) {
    return ($val1 & $val2);
}

function addChecked($val, $priv, $scope, $kind) {
    debugPrint("VAL: $val PRIV: $priv<br>");
    if (!($priv & $val) and $kind == "No") {
        return ("checked");
    } else if (($priv & $val) and !($scope & $val) and $kind == "Site") {
        return ("checked");
    } else if (($priv & $val) and ($scope & $val) and $kind == "Dist") {
        return ("checked");
    } else {
        return ("");
    }
}

function debugPrint($str, $group="") {
    global $debug;

    if (isset($_SESSION['debug']) && $_SESSION['debug'] == "on") {
        echo ($group == "" ? "<br>" : "");
        echo ("$str");
    }
}

function setDebug($value) {
    global $debug;

    $_SESSION['debug'] = $value;
    debugPrint("SET DEBUG: " . $value . "<br>");
}

/*
  checks to see if user is logged on
 */

function checkLogon() {
    if (!isset($_SESSION['logon']) or !$_SESSION['logon']) {
        return (FALSE);
    } else {
        return (TRUE);
    }
}

/*
  returns the users name based on logon
 */

function getUserName() {
    global $currentUserName;

    return ($currentUserName);
}

/*
  returns the users name based on logon
 */

function userPriviledge() {
    return ($_SESSION['priviledge']);
}

/*
  returns the users id based on logon
 */

function logonID() {
    debugPrint("Get logonID: " . $_SESSION['sessionUserID']);
    return ($_SESSION['sessionUserID']);
}

function getSite() {
    debugPrint("Get Site: " . $_SESSION['site']);
    return ($_SESSION['site']);
}

/*
  sets the logon to be true
 */

function setLogon() {
    $_SESSION['logon'] = TRUE;
}

/*
  sets the logon to be false
 */

function unsetLogon() {
    $_SESSION['logon'] = FALSE;
    session_unset();
    session_destroy();
}

function emailPassword($user) {
    return TRUE;
}

function displayCurrentYearQuarter() {
    global $CurrentYear, $CurrentQuarter;
    return($CurrentYear . "-" . ($CurrentYear + 1) . ":Q" . $CurrentQuarter);
}

function getMyGlobals() {
    global $db, $currentUserID, $currentUserName, $currentUser, $currentPrivA, $currentPrivB, $currentScopeA, $currentScopeB, $currentMySite, $cmd, $msg;

//    if (isset($_SESSION['LAST_ACTIVITY']) && (time() - $_SESSION['LAST_ACTIVITY'] > 1800)) {
//        // last request was more than 30 minates ago
//        session_destroy();   // destroy session data in storage
//        session_unset();     // unset $_SESSION variable for the runtime
//    }
//    $_SESSION['LAST_ACTIVITY'] = time();


    if (isset($_SESSION['sessionUserID'])) {
        $currentUserID = $_SESSION['sessionUserID'];
        $query = "select * from user where userID='$currentUserID'";
        debugPrint("getGlobals SQL: " . $query . "<br>");
        $res = $db->get_results($query);
        debugPrint("Globals Sql: " . print_r($res[0], true));
        if (ucfirst($res[0]->status) == "Active") {
            $currentUserName = $res[0]->name;
            $currentUser = $res[0]->user;
            $currentPrivA = $res[0]->privilegeA;
            $currentPrivB = $res[0]->privilegeB;
            $currentScopeA = $res[0]->scopeA;
            $currentScopeB = $res[0]->scopeB;
            $currentMySite = $res[0]->site;
            if (isset($res[0]->affiliated))
                $currentAffiliatedID = $res[0]->affiliated;
            else
                $currentAffiliatedID = -1;
        }
    }
}

/* * * Student Web ** */

// <editor-fold defaultstate="collapsed" desc="Student Web">

function getStudentGlobals() {
    global $db, $currentStudentID, $currentStudentName, $currentPrivA, $currentPrivB, $currentScopeA, $currentScopeB, $currentMySite, $cmd, $msg;

    $currentStudentID = $_SESSION['sessionStudentID'];
    $query = "select status, fname, lname, site from student where studentID='$currentStudentID'";
    debugPrint("getStudentGlobals SQL: " . $query . "<br>");
    $res = $db->get_results($query);
    debugPrint("Globals Sql: " . print_r($res[0], true));
    if (ucfirst($res[0]->status) == "Active") {
        $currentStudentName = $res[0]->fname . " " . $res[0]->lname;
        $currentPrivA = 0;
        $currentPrivB = 0;
        $currentScopeA = 0;
        $currentScopeB = 0;
        $currentMySite = $res[0]->site;
        $currentAffiliatedID = $currentStudentID;
    }
}

function studentlogon($user, $pwd) {
    global $db;

    $query = "select studentid from student where user='$user' and pwd  = '$pwd' and status = 'Active'";
    debugPrint("Logon Query: " . $query);
    $res = $db->get_results($query);
    if ($db->num_rows == 1) {
        $_SESSION['sessionStudentID'] = $res[0]->studentid;
        debugPrint("LOGIN UserID: " . $_SESSION['sessionStudentID']);
        return( $res[0]->studentid);
    } else {
        return (0);
    }
}

function checkStudentLogon() {
    if (!isset($_SESSION['studentlogon']) or !$_SESSION['studentlogon']) {
        return (FALSE);
    } else {
        return (TRUE);
    }
}

function setStudentLogon() {
    $_SESSION['studentlogon'] = TRUE;
}

function unsetStudentLogon() {
    $_SESSION['studentlogon'] = FALSE;
    session_unset();
    session_destroy();
}

// </editor-fold>
/*
  processes logon
 */
function logon($user, $pwd) {
    global $db;

    $query = "select userid from user where user='$user' and pwd  = '$pwd' and status = 'Active'";
    debugPrint("Logon Query: " . $query);
    $res = $db->get_results($query);
    if ($db->num_rows == 1) {
        $_SESSION['sessionUserID'] = $res[0]->userid;
        debugPrint("LOGIN UserID: " . $_SESSION['sessionUserID']);
        return( $res[0]->userid);
    } else {
        return (0);
    }
}

/* * * Access to user table ** */

// <editor-fold defaultstate="collapsed" desc="User">

function getUserInfo($id) {
    global $db;

    $query = "select * from user where userid='$id'";
    debugPrint("getUserInfo: " . $query);
    $res = $db->get_results($query, ARRAY_A);
    return($res[0]);
}

function saveUserInfo($id, $field, $value) {
    global $db;

    $sql = "Update user SET $field = '$value' where userid = '$id'";
    debugPrint($sql);
    $db->get_results($sql);
}

function getUsers($site, $status) {
    global $db;

    $sql = "SELECT * FROM user where site = '$site' and status = '$status' order by name";
    debugPrint("getUSERS: " . $sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function getAllUsers($site="") {
    global $db;

    $clause = whereClause("Where user.site", "", $site, "'");
    $sql = "SELECT user.userid as id, name FROM user $clause order by name";
    debugPrint("getAllUSERS: " . $sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function admin_getUsers() {
    global $db;

    $query = "select userid, user, name, status, privilegeA, privilegeB, scopeA, scopeB, pwd from user";
    debugPrint($query);
    $res = $db->get_results($query, ARRAY_A);
    return($res);
}

function admin_adduser($name, $user, $password) {
    global $db;

    if ($name != "" and $user != "" and pwd != "") {
        $sql = "INSERT into user
				SET name ='$name',
				user = '$user',
				pwd = '$password'";
        debugPrint($sql);
        $db->get_results($sql);
        return (TRUE);
    } else {
        return (FALSE);
    }
}

function admin_statususer($id, $status) {
    global $db;

    $sql = "Update user SET status = '$status' where userid = '$id'";
    debugPrint($sql);
    $db->get_results($sql);
}

function admin_changepassword($id, $pwd) {
    global $db;

    $sql = "Update user SET pwd = '$pwd' where userid = '$id'";
    debugPrint($sql);
    $db->get_results($sql);
}

// </editor-fold>

/* * * Interface elements ** */
// <editor-fold defaultstate="collapsed" desc="Interface">

function admin_statusForm($id, $status) {
    $tmp .= "<form style=\"margin-bottom:0;\" name=" . $status . "User method=post action=index.php?cmd=adminStatusUser><input type=hidden name=id value=$id><input type=hidden name=p1 value=$status><input type=submit value=$status></form>";
    return ($tmp);
}

function admin_formPwd($id) {
    $tmp .='<form style=\"margin-bottom:0;\" name=changePwd method=post action=index.php?cmd=adminChangePwd><input type=hidden name=id value=' . $id . '><input type=password name=p1><input type=submit value="Change Password"></form>';
    return $tmp;
}

function showListOptional($items, $sel="") {
    foreach ($items as $item) {
        $select = selected($item['studentid'], $sel);

        $val .= '<option value = "' . $item['studentid'] . '" ' . $select . '>' . $item['lname'] . ", " . $item['fname'] . '</option>';
    }
    return $val;
}

function selectEditStdMenu() {

    $str = <<<END
<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
	<td align="right" width="15%">
		<input type="button" value="Create Subjects" onclick="javascript: window.location = 'index.php?cmd=createsubject';" style="width: 100%;" />
	</td>
	<td align="right" width="15%">
		<input type="button" value="Create Levels" onclick="javascript: window.location = 'index.php?cmd=createlevels';" style="width: 100%;" />
	</td>
	<td align="left" width="15%">
		<input type="button" value="Edit Standard" onclick="javascript: window.location = 'index.php?cmd=editStandards';" style="width: 100%;" />
	</td>
	<td align="right" width="15%">
		<input type="button" value="Create, Delete, and Rename" onclick="javascript: window.location = 'index.php?cmd=standardManipulation';" style="width: 100%;" />
	</td>
	<td align="right" width="15%">
		<input type="button" value="Edit Quarters" onclick="javascript: window.location = 'index.php?cmd=editQuarter';" style="width: 100%;" />
	</td>
</tr>
</table><br><br>
END;
    return($str);
}

function getMonth($name, $selection="") {

    ${"m" . $selection} = "selected";

    $str = <<<END
		<select  name="$name">
			<option value=""></option>
			<option value="1" $m1>Jan</option>
			<option value="2" $m2>Feb</option>
			<option value="3" $m3>Mar</option>
			<option value="4" $m4 >Apr</option>
			<option value="5" $m5>May</option>
			<option value="6" $m6>Jun</option>
			
			<option value="7" $m7>Jul</option>
			<option value="8" $m8>Aug</option>
			<option value="9" $m9>Sep</option>
			<option value="10" $m10>Oct</option>
			<option value="11" $m11>Nov</option>
			<option value="12" $m12>Dec</option>
		</select>
END;
    return ($str);
}

function getDay($name, $selection="") {

    ${"d" . $selection} = "selected";

    $str = <<<END
		<select name="$name">				
			<option value=""></option>		
			<option value="1" $d1>01</option>
			<option value="2" $d2>02</option>
			<option value="3" $d3>03</option>
			<option value="4" $d4>04</option>
			<option value="5" $d5>05</option>
			<option value="6" $d6>06</option>
			<option value="7" $d7>07</option>
			<option value="8" $d8>08</option>
			<option value="9" $d9>09</option>		
			<option value="10" $d10>10</option>
			<option value="11" $d11>11</option>
			<option value="12" $d12>12</option>
			<option value="13" $d13>13</option>
			<option value="14" $d14>14</option>
			<option value="15" $d15>15</option>
			<option value="16" $d16>16</option>
			<option value="17" $d17>17</option>
			<option value="18" $d18>18</option>		
			<option value="19" $d19>19</option>
			<option value="20" $d20>20</option>
			<option value="21" $d21>21</option>
			<option value="22" $d22>22</option>
			<option value="23" $d23>23</option>
			<option value="24" $d24>24</option>
			<option value="25" $d25>25</option>
			<option value="26" $d26>26</option>
			<option value="27" $d27>27</option>		
			<option value="28" $d28>28</option>
			<option value="29" $d29>29</option>
			<option value="30" $d30>30</option>
			<option value="31" $d31>31</option>
			</select>
END;
    return ($str);
}

function getYear($name, $selection="") {

    ${"y" . $selection} = "selected";

    $str = <<<END
		<select name="$name">							
			<option value=""></option>
			<option value="2005" $y2005>2005</option>
			<option value="2006" $y2006>2006</option>		
			<option value="2007" $y2007>2007</option>
			<option value="2008" $y2008>2008</option>
			<option value="2009" $y2009>2009</option>
			<option value="2010" $y2010>2010</option>
			<option value="2011" $y2011>2011</option>
			<option value="2012" $y2012>2012</option>
			<option value="2013" $y2013>2013</option>
			<option value="2014" $y2014>2014</option>
			<option value="2015" $y2015>2015</option>
			<option value="2016" $y2016>2016</option>
			<option value="2017" $y2017>2017</option>
			<option value="2018" $y2018>2018</option>
			<option value="2019" $y2019>2019</option>
			<option value="2020" $y2020>2020</option>
		</select>
	
END;
    return ($str);
}

/* function to display all the list information for a user */

function showMyList($userID, $before="", $after="", $type="self") {
    $str = "";
    $list = getMyList($userID, $type);
    for ($i = 0; $i < count($list); $i++) {
        $listname = $list[$i]['listname'];
        $str .= "$before<a href=index.php?cmd=showscores&p1=" . $list[$i]['listid'] . ">$listname</a>$after";
    }
    return $str;
}

function getSubjectOption($subject='') {
    global $db;

    $subjects = $db->get_results("select id from subjects", ARRAY_A);
    foreach ($subjects as $sub) {
        $id = $sub['id'];
        $selected = $id == $subject ? "selected" : "";
        $str .= "<option value='$id' $selected>$id</option>\n";
    }
    return ($str);
}

// </editor-fold>

/* * * Access to subjects table ** */

function getSubjects() {
    global $db;
    $query = "select * from subjects order by subjects.order";
    debugPrint("GetSubjects: $query");
    $subject = $db->get_results($query, ARRAY_A);
    return ($subject);
}

function getCoreSubjects() {
    global $db;
    $query = "SELECT id, name FROM subjects WHERE core = 'x' ORDER BY subjects.order";
    $subject = $db->get_results($query, ARRAY_A);
    return $subject;
}

function getElectiveSubjects() {
    global $db;
    $query = "SELECT id, name FROM subjects WHERE core = '' ORDER BY subjects.order";
    $subject = $db->get_results($query, ARRAY_A);
    return $subject;
}

/* * * Access to lists table ** */

// <editor-fold defaultstate="collapsed" desc="List">

function getListStudents($lid) {
    global $db;

    $list = $db->get_results("select kind, lists.sql from lists where listid = '$lid' ", ARRAY_A);
    if ($list[0]['kind'] == 'search') {
        $sql = $list[0]['sql'];
    } else {
        $sql = "select studentid from listvalues where listid = '$lid'";
    }
    $results = $db->get_results($sql, ARRAY_A);

    $str = "";

    if ($results != null)
        foreach ($results as $row) {
            $id = $row['studentid'];
            $str .= $str == '' ? "" : ",";
            $str .= "$id";
        } else
        $str = "(NULL)";
    return($str);
}

function getListItems($listID) {
    global $debugLevel, $db;

    $query = "select listvalues.studentid, fname, lname from listvalues, student where listvalues.listid='$listID' and student.studentid = listvalues.studentid order by lname,fname ASC";
    debugPrint($query);
    $list = $db->get_results($query, ARRAY_A);

    return $list;
}

/* function to display all the list information for a user */

function showSharedList($userID, $before="", $after="") {
    global $db;
    $str = "";
    $sql = "select listid, listname, kind from lists
					where lists.userid = $userID and type = 'Private'
			union
				select lists.listid, listname, kind from lists, listshare
					where lists.listid = listshare.listid and listshare.userid = $userID and type='Private'";
    $list = $db->get_results($sql, ARRAY_A);
    for ($i = 0; $i < count($list); $i++) {
        $addtion = ($list[$i]['kind'] == 'search') ? "*" : "";
        $listname = $list[$i]['listname'] . $addtion;
        $str .= "$before<a href=index.php?cmd=showscores&p1=" . $list[$i]['listid'] . ">$listname</a>$after";
    }
    return $str;
}

/* returns a all the list and list information associated with a userid */

function getMyList($userID, $type="self") {
    global $db;
    if ($type == 'self') {
        $query = "select *, listid as id, listname as name from lists where type = \"$type\" and userid='$userID' order by listname ASC";
    } else if ($type == 'all') {
        $query = "select *, listid as id, listname as name from lists where userid='$userID' order by listname ASC";
    } else {
        $query = "select *, listid as id, listname as name from lists where type = \"$type\" order by listname ASC";
    }
    debugPrint("<Br>My List" . $query);
    $list = $db->get_results($query, ARRAY_A);
    for ($i = 0; $i < count($list); $i++) {
        $addtion = ($list[$i]['kind'] == 'search') ? "*" : "";
        $list[$i]['listname'] = $list[$i]['listname'] . $addtion;
        $list[$i]['name'] = $list[$i]['name'] . $addtion;
    }

    return $list;
}

// </editor-fold>

/* * * Access to student table ** */
// <editor-fold defaultstate="collapsed" desc="Student">

function getStudentInfo($studentID) {
    global $db;

    $sql = "select *, student.village as village, (CURDATE() - bday) as age from student LEFT JOIN site ON site.siteid = student.site where studentid ='$studentID'";
    debugPrint($sql);
    $res = $db->get_results($sql, ARRAY_A);
    return ($res[0]);
}

function createNewStudent($site) {
    global $db;
    $sql = "INSERT into student
		SET site='$site',
			status = 'Active'";
    debugPrint("INSERT SQL=>" . $sql . "<br>");
    $db->get_results($sql);
    return ($db->insert_id);
}

function newStudent($id, $site) {
    global $db;
    $sql = "INSERT into student
		SET studentid='$id',
			site='$site',
			status = 'Active'";
    debugPrint("INSERT SQL=>" . $sql . "<br>");
    $db->get_results($sql);
    return ($db->insert_id);
}

function getStudentPwd($username) {
    global $dartEmail, $db, $rootURL;

    $sql = "select email, name, pwd from student where user='$username'";
    debugPrint("forgetPassword: " . $sql);
    $result = $db->get_results($sql);
    $res = $result[0];
    debugPrint("Here in getPWD");
    $email = $res->email;
    debugPrint("Email: $email");

    if ($email == "") {
        $ans['result'] = FALSE;
        $ans['msg'] = "The user name you gave does not exist in our system";
    } else {
        $name = $res->name;
        $pwd = $res->pwd;
        $headers = "From: Dart Admin <$dartEmail>\n";
        $to_email = "$name <$email>\n";
        $subject = "Password for Dart";

        $message = "Hello $name,\nYour password is $pwd.\nPlease go to $rootURL. To logon with your password.";
        debugPrint("<br>MSG: " . $message);
        if (mail($to_email, $subject, $message, $headers)) {
            $ans['result'] = TRUE;
            $ans['msg'] = "Your password will be emailed to your email address on file shortly.";
        } else {
            $ans['result'] = FALSE;
            $ans['msg'] = "Sorry we are having temporary trouble with sending mail. Please try again later or call dart administrator.";
        }
    }
    return ($ans);
}

function getStudentList($listID) {
    global $debugLevel, $db;

    $studentlist = getListStudents($listID);


    $query = "select student.studentid, fname, lname from student
				WHERE student.studentid in ($studentlist) order by lname ASC, fname ASC";
    $list = $db->get_results($query, ARRAY_A);
    return $list;
}

function getStudentToggleList($listID, $sub, $lvl) {
    global $debugLevel, $db;
    $studentlist = getListStudents($listID);

    $query = "select student.studentid, fname, lname, change_username, change_timestamp, studentlevel.progress, student.site, student.grade, gsid as gradetype, gs.name as  gradetypename
			FROM (student, studentlevel) 
			LEFT JOIN (gs_select, gs) ON gs.id = gs_select.gsid and student.site = gs_select.siteid and grade >= lowgrade and grade <= highgrade
			where student.studentid in ($studentlist) and studentlevel.studentid=student.studentid and studentlevel.level='$lvl' and studentlevel.subject='$sub' and studentlevel.final = '00000000' order by lname ASC";
    debugPrint($query);
    $list = $db->get_results($query, ARRAY_A);
    return $list;
}

function getPotentialListItems($userID, $priv="district") {
    global $debugLevel, $db, $currentMySite;

    $students = "";
    if ($priv != 'none') {
        $filter = $priv == 'site' ? " site = '$currentMySite' and " : "";
        $query = "select studentid, fname, lname from student where $filter student.status = 'Active' order by lname ASC, fname ASC";
        debugPrint($query);
        $students = $db->get_results($query, ARRAY_A);
    }
    return $students;
}

/*
 * Get classes the list of students is taking (subject and level)
 */

function getStudentScores($listID) {
    global $debugLevel, $db;
    $studentList = getListStudents($listID);
    $query = "SELECT studentid, subject, level FROM studentlevel WHERE studentid in ($studentList) and studentlevel.final = '00000000'";
    $result = $db->get_results($query);
    foreach ($result as $res) {
        $student[$res->studentid][$res->subject] = $res->level;
    }
    return $student;
}

// </editor-fold>

function getStudentOverall($studentID) {
    global $db;

    $sql = "select grades.subject, grades.level, grades.value, count(value) as num from grades where grades.studentid = $studentID and (grades.value='DEV' or grades.value='EMG' or grades.value='PRO' or grades.value='ADV' ) group by grades.subject, grades.level, grades.value";
    debugPrint("OVERALL SQL: " . $sql . "<br>");
    $result = $db->get_results($sql);
    foreach ($result as $res) {
        $ret[$res->subject][$res->level][$res->value] = $res->num;
        debugPrint("<br>Subject:level:value:num " . $res->subject . ":" . $res->level . ":" . $res->value . ":" . $res->num);
    }
    return $ret;
}

function overallScore($sub, $lvl, $over) {
    $emgNum = $over[$sub][$lvl]['EMG'];
    $devNum = $over[$sub][$lvl]['DEV'];
    $proNum = $over[$sub][$lvl]['PRO'];
    $advNum = $over[$sub][$lvl]['ADV'];
    $totalValues = $proNum + $emgNum + $advNum + $devNum;
    $total = $over[$sub][$lvl]['total'];

    if ($emgNum == 0 and $devNum == 0 and $advNum > 0 and ($advNum / ($proNum + $advNum) >= .9) and $totalValues == $total) {
        $ans = "ADV";
    } else if ($emgNum == 0 and $devNum == 0 and $totalValues == $total) {
        $ans = "PRO";
    } else if (($proNum > 0 or $advNum > 0) and $total >= $totalValues) {
        $ans = "DEV";
    } else if ($total >= $totalValues) {
        $ans = "EMG";
    } else {
        $ans = "INTERNAL ERR - Too many values see developer";
    }
    debugPrint("<br>******$sub.$lvl-EMG $emgNum: DEV $devNum: PRO $proNum :ADV $advNum: Total $total: TotalValues $totalValues: - $ans<br>");
    $ans = "TBD";
    return ($ans);
}

function updateOverall2($studentID, $subject, $level) {
    global $db;
    exit();
    $sql = "SELECT gradetype, gsid FROM gs, student as st, gs_select
			WHERE st.site = gs_select.siteid and grade >= lowgrade and grade <= highgrade and
			st.studentid='$studentID' and gs.id = gs_select.gsid";
    $gs = $db->get_results($sql, ARRAY_A);
    if ($gs[0]['gsid'] == '1') {
        $sql = "SELECT count(*) as ct, symbol, gradetype from (standards as s, student as st)
				LEFT JOIN (grades as g, gs_grades as gsg, gs_select, gs) ON 
				gsg.low <= convert(value,unsigned) and gsg.high >= convert(g.value,unsigned) and 
				gsg.gsid=gs_select.gsid and st.site = gs_select.siteid and grade >= lowgrade and
				grade <= highgrade and g.studentid='$studentID'and s.subject = g.subject and
				s.level = g.level and s.std = g.std and gs.id = gsg.gsid
				WHERE s.subject = '$subject' and s.level = '$level' and (s.type='std' or s.type='over') and
				st.studentid = '$studentID'
				GROUP BY symbol";
        $result = $db->get_results($sql, ARRAY_A);
        foreach ($result as $r) {
            if (is_null($r['symbol']) or ($r['symbol'] == '')) {
                $r['symbol'] = 'NULL';
            }
            $over[$r['symbol']] = $r['ct'];
            $total += $r['ct'];
        }

        $emgNum = $over['EMG'];
        $devNum = $over['DEV'];
        $proNum = $over['PRO'];
        $advNum = $over['ADV'];
        $totalValues = $proNum + $emgNum + $advNum + $devNum;

        if ($emgNum == 0 and $devNum == 0 and $advNum > 0 and ($advNum / ($proNum + $advNum) >= .9) and $totalValues == $total) {
            $ans = "ADV";
        } else if ($emgNum == 0 and $devNum == 0 and $totalValues == $total) {
            $ans = "PRO";
        } else if (($proNum > 0 or $advNum > 0) and $total >= $totalValues) {
            $ans = "DEV";
        } else if ($total >= $totalValues) {
            $ans = "EMG";
        } else {
            $ans = "INTERNAL ERR - Too many values see developer";
        }
        debugPrint("<br>******$sub.$lvl-EMG $emgNum: DEV $devNum: PRO $proNum :ADV $advNum: Total $total: TotalValues $totalValues: - $ans<br>");
        return ($ans);
    } else {
        $sql = "SELECT AVG(value) FROM grades as g, standards as s
				WHERE s.subject = '$subject' and s.level = '$level' and 
				g.subject = s.subject and g.level = s.level and 
				s.std = g.std and (s.type='std' or s.type='over') and 
				studentid = '$studentID' and value > 0";
        $avg = (int) $db->get_var($sql);
        $sql = "SELECT concat('$avg',' ',symbol) FROM gs_grades
				WHERE gs_grades.low <= '$avg' and gs_grades.high >= '$avg' and 
				gs_grades.gsid='{$gs[0]['gsid']}'";
        $ans = $db->get_var($sql);
        return($ans);
    }
}

function updateOverall($studentID, $subject, $level) {
    global $db;

    $sql = "select grades.subject, grades.level, grades.value, count(value) as num from grades, standards where grades.subject = '$subject' and grades.level = '$level' and grades.studentid = $studentID and (grades.value='DEV' or grades.value='EMG' or grades.value='PRO' or grades.value='ADV' ) and standards.subject=grades.subject and standards.level=grades.level and standards.std=grades.std and (standards.type='std' or standards.type='over') group by grades.value";
    debugPrint("UPDATE OVERALL SQL: " . $sql . "<br>");
    $result = $db->get_results($sql);
    $ret[$subject][$level]['EMG'] = 0;
    $ret[$subject][$level]['DEV'] = 0;
    $ret[$subject][$level]['PRO'] = 0;
    $ret[$subject][$level]['ADV'] = 0;
    foreach ($result as $res) {
        $value = is_null($res->num) ? 0 : $res->num;
        $ret[$subject][$level][$res->value] = $value;
    }

    $sql2 = "select standards.subject, standards.level, standards.std, count(standards.std) as num from standards where standards.subject= '$subject' and standards.level = '$level' and (standards.type = 'std' or standards.type='over') group by standards.subject, standards.level";
    debugPrint("Total Std SQL: " . $sql2 . "<br>");
    $result2 = $db->get_results($sql2);
    foreach ($result2 as $res2) {
        $ret[$subject][$level]['total'] = $res2->num;
        debugPrint("<br>Subject:level:value:num " . $res2->subject . ":" . $res2->level . ":" . $res2->value . ":" . $res2->num);
    }
    return(overallScore($subject, $level, $ret));
}

function getStudentComments($id) {
    global $db;

    $sql = "select g.subject, g.std, g.value FROM studentlevel as s, grades as g where g.studentid = s.studentid and g.subject = s.subject and g.level=s.level and (g.std= 'comment' or g.std='qpi' or g.std='til' or g.std='entered') and s.studentid = $id";
    debugPrint("COMMENT SQL: " . $sql . "<br>");
    $result = $db->get_results($sql);
    foreach ($result as $res) {
        $ret[$res->subject][$res->std] = $res->value;
        debugPrint("<br>Subject:type:value " . $res->subject . ":" . $res->std . ":" . $res->value);
    }
    return $ret;
}

function getStudentComments2($id) {
    global $db;

    $sql = "select g.subject, g.level, g.std, g.value FROM studentlevel as s, grades as g where g.studentid = s.studentid and g.subject = s.subject and g.level=s.level and (g.std= 'comment' or g.std='qpi' or g.std='til' or g.std='entered' or g.std='prog') and s.studentid = $id";
    debugPrint("COMMENT SQL: " . $sql . "<br>");
    $result = $db->get_results($sql);
    foreach ($result as $res) {
        $ret[$res->subject][$res->level][$res->std] = $res->value;
        debugPrint("<br>Subject:type:value " . $res->subject . ":" . $res->std . ":" . $res->value);
    }
    return $ret;
}

function getStudentOverallScore($studentID, $filter=" and studentlevel.final = '00000000' ", $start='', $finish='') {
    $subjects = getStudentLevels($studentID, $filter);
    $subs = $subjects;
    $values = getStudentComments2($studentID);
    $len = count($subjects);
    for ($i = 0; $i < $len; $i++) {
        $sub = $subjects[$i]['subject'];
        $lvl = $subjects[$i]['level'];
        $subjects[$i]['score'] = $subjects[$i]['progress']; // overallScore ($sub, $lvl, $scoreTotals);
        $subjects[$i]['qpi'] = commentSpace($values[$sub][$lvl]['qpi']);
        $subjects[$i]['til'] = commentSpace($values[$sub][$lvl]['til']);
        $subjects[$i]['entered'] = commentSpace($values[$sub][$lvl]['entered']);
        $subjects[$i]['comment'] = commentSpace($values[$sub][$lvl]['comment']);
        $subjects[$i]['prog'] = commentSpace($values[$sub][$lvl]['prog']);
        $d = $subjects[$i]['final'];
        if ($d == "0000-00-00 00:00:00") {
            $subjects[$i]['complete'] = "In Progress";
        } else if (($d > $finish) and ($finish != '')) {
            $subjects[$i]['complete'] = "In Progress<br>" . DateMYSQLConvert($d);
        } else {
            $subjects[$i]['complete'] = DateMYSQLConvert($d);
        }
    }
    return $subjects;
}

function DateMYSQLConvert($d) {
    return(substr($d, 5, 2) . "/" . substr($d, 8, 2) . "/" . substr($d, 2, 2));
}

function updateStudentField($id, $field, $value) {
    global $db;

    $sql = "Update student SET $field = '$value' where studentid = '$id'";
    debugPrint($sql);
    $db->get_results($sql);
}

function updateUserField($id, $field, $value) {
    global $db;

    $sql = "Update user SET $field = '$value' where userID = '$id'";
    debugPrint($sql);
    $db->get_results($sql);
}

function getSubjectInfo($sub, $lvl='') {
    global $db;

    $sql = "select subjects.*, level.name as lname from subjects LEFT JOIN level ON id = subject and level = '$lvl' where id ='$sub'";
    debugPrint($sql);
    $res = $db->get_results($sql, ARRAY_A);
    return ($res);
}

function getSubjectStandards($sub, $level) {
    global $db;
    $query = "SELECT std, description, link, shortname FROM standards WHERE subject='$sub' AND level='$level' AND type='std' ORDER BY standards.order ASC";
    $subject = $db->get_results($query, ARRAY_A);
    return $subject;
}

function getSubjectOverall($sub, $level) {
    global $db;
    $query = "SELECT std, description FROM standards WHERE subject='$sub' AND level='$level' AND type='over' ORDER BY standards.order ASC";
    $subject = $db->get_results($query, ARRAY_A);

    return $subject;
}

function getStudentStdScores($listid, $subject, $level) {
    global $debugLevel, $db;
    $studentlist = getListStudents($listid);
    $query = "SELECT student.studentid, std, value FROM grades, student WHERE grades.subject='$subject' and grades.level='$level' and student.studentid = grades.studentid and student.studentid in ($studentlist)";
    debugPrint($query);
    $result = $db->get_results($query);
    foreach ($result as $res) {
        $student[$res->studentid][$res->std] = $res->value;
    }
    return $student;
}

function getStudentChanges($studentID) {
    global $db;
    $query = "SELECT * FROM studentlevel WHERE studentid = '$studentID'";
    debugPrint("Student Changes: " . $query . "<br>");
    $result = $db->get_results($query);
    foreach ($result as $res) {
        $studentlevel[$res->subject]['ch_name'] = $res->change_username;
        $studentlevel[$res->subject]['ch_time'] = $res->change_timestamp;
    }
    return $studentlevel;
}

function getStudentChanges2($studentID) {
    global $db;
    $query = "SELECT * FROM studentlevel WHERE studentid = '$studentID'";
    debugPrint("Student Changes: " . $query . "<br>");
    $result = $db->get_results($query);
    foreach ($result as $res) {
        $studentlevel[$res->subject][$res->level]['ch_name'] = $res->change_username;
        $studentlevel[$res->subject][$res->level]['ch_time'] = $res->change_timestamp;
    }
    return $studentlevel;
}

function selected($val1, $val2) {
    if ($val1 == $val2)
        return "selected";
    else
        return "";
}

function getToggleValue($val) {
    switch ($val) {
        case "EMG":
            return 1;
        case "DEV":
            return 2;
        case "PRO":
            return 3;
        case "ADV":
            return 4;
        default:
            return 0;
    }
}

function saveAdvEditStudentInfo($values) {
    global $db;

    $id = $values['id'];
    while (list($var, $val) = each($values)) {
        if (substr($var, 0, 4) == "new_" and $val != "empty") {
            $field = substr($var, 4, 500);
            $oldval = $values['old_' . $field];
            $sep = $list != "" ? ", " : "";
            $list .= "$sep$field = '$val'";
            $oldlist .= "$sep$field = $oldval";
            debugPrint("var $var => $val field => $field<br>");
        }
    }
    if ($list != "") {
        $sql = "Update student
			SET $list
			WHERE
			studentid = '$id'";
        debugPrint("List: $list OldList: $oldlist<br>");
        debugPrint("SQL=>" . $sql . "<br>");
        $db->get_results($sql);
        $insertValue = addslashes("Old: $oldlist New: $list");
        logEntry("Bulk Change Demographics", $insertValue, $id, "", "", "");
    }
}

function saveGrades($values) {
    global $db;

    debugPrint("saveGrades<br>");
    while (list($var, $val) = each($values)) {
        // debugPrint("var $var => $val <br>");
        if (substr($var, 0, 3) == "ch_" and $val != "empty") {
            debugPrint("CHANGE: var $var => $val <br>");
            $str = substr($var, 3, 3);
            $tok = strtok(substr($var, 5, 100), "_");
            $studentid = strtok("_");
            $subject = strtok("_");
            $level = strtok("_");
            $partialstd = strtok("_");
            $aux = strtok("_");
            $std = $aux == "" ? $partialstd : "$partialstd.$aux";
            $num = getToggleValue($val);
            if ($str == "gri") {
                $sql = "INSERT into grades
							SET value='$val',
								num = '$num',
								studentid = '$studentid',
								subject = '$subject',
								level = '$level',
								std = '$std'";
            } else if ($str == "gru") {
                $sql = "Update grades
							 SET value='$val',
								num = '$num'
							 WHERE
								studentid = '$studentid' and
								subject = '$subject' and
								level = '$level' and
								std = '$std'";
            }
            debugPrint($var . "<br>");
            debugPrint("<br><br>SQL=>" . $sql . "<br>");
            $db->get_results($sql);
            logEntry("toggle", $val, $studentid, $subject, $level, $std);
            $changed[] = "id=$studentid&subject=$subject&lvl=$level";
        }
    }
    $changed = array_values(array_unique($changed));
    debugPrint("count" . count($changed) . "<br>" . print_r($changed, true));
    for ($i = 0; $i < count($changed); $i++) {
        parse_str($changed[$i]);
        debugPrint("<br>" . print_r($changed[$i], true) . "<br>**Change ID: $id SUB: $subject LEVEL: $lvl<br>");
        updateChange($id, $subject, $lvl);
    }
    debugPrint("ISTR=>" . $istr);
    debugPrint("USTR=>" . $ustr);
}

function getStudentLevelTable($studentID) {
    global $db;

    $sql = "SELECT * FROM studentlevel, subjects WHERE
			studentlevel.studentid = '$studentID' and 
			studentlevel.subject = subjects.id order by 'subjects.order' ASC";
    debugPrint("<br>Get Student Levels: $sql<br>");
    $results = $db->get_results($sql, ARRAY_A);
    $results = array_sort($results, 'order');
    return ($results);
}

function getLevels($sub) {
    global $db;

    $sql = "select * from level where subject = '$sub' order by numlevel ASC";
    debugPrint("SELECT LEVEL SQL=>" . $sql . "<br>");
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function getSubLvlOptions($sub, $sel) {
    $levelValues = getLevels($sub);
    foreach ($levelValues as $value) {
        $val = $value['level'];
        $ans .= "<option value=\"$val\"" . selected($val, $sel) . ">$val</option>";
    }
    return ($ans);
}

function addLevel($id, $sub) {
    global $db;
    $sql = "INSERT into studentlevel
						SET subject='$sub',
							studentid = '$id'";
    debugPrint("AddLevel => $sql<br>");
    /*     * ******** Need To Log ************** */
    $db->get_results($sql);
}

function deleteLevel($id, $sub, $lvl) {
    global $db;
    $level = $lvl == '' ? "level is NULL" : "level = '$lvl'";
    $sql = "Delete from studentlevel
						WHERE subject='$sub' and
							studentid = '$id' and
			$level";
    debugPrint("DeleteLevels => $sql<br>");
    $db->get_results($sql);
    logEntry("Delete Level", "", $id, $sub, $lvl, "");
}

function saveLevels($values) {
    global $db;

    $id = $values['id'];
    while (list($var, $val) = each($values)) {
        debugPrint(substr($var, 0, 3) . "-var $var => $val <br>");
        if (substr($var, 0, 3) == "new" and $val != 'empty') {
            $sub = substr($var, 4, 2);
            $oldval = substr($var, 7, 500);
            $oldst = $oldval == "" ? 'is NULL or level=""' : " = '$oldval'";
            $update = "Update studentlevel
				SET level = '$val'
				WHERE studentid = '$id' and
				subject = '$sub' and
				(level $oldst)";
            debugPrint("UPDATE LEVEL: $update");
            $db->get_results($update);
            logEntry("Update Level", $val, $id, $sub, $oldval, "");
        }
    }
}

function overAllGPA($studentid) {
    global $db;

    $sql = "SELECT sum( sweight * spoints ) / sum( sweight ) as gpa, sum(sweight) as credit
			FROM studentlevel
			WHERE studentid = '$studentid' and sweight > 0 ";
    $val = $db->get_row($sql, ARRAY_A);
    $ans['gpa'] = number_format(round($val['gpa'], 3), 3);
    $ans['credit'] = $val['credit'];
    return($ans);
}

function filterGPA($studentid, $filter) {
    global $db;

    $sql = "SELECT sum( sweight * spoints ) / sum( sweight ) as gpa
		FROM studentlevel
		WHERE studentid = '$studentid' and sweight > 0 $filter";
    $gpa = number_format(round($db->get_var($sql), 3), 3);
    return($gpa);
}

function updateChange($studentID, $subject, $level) {
    global $db, $currentUserName, $currentUserID;

    $tm = time();
    $userID = logonID();
    $name = getUserName();

    cleanupInternalErrors($studentID, $subject, $level);

    $sql = "SELECT gradetype, gsid FROM gs, student as st, gs_select
		WHERE st.site = gs_select.siteid and grade >= lowgrade and grade <= highgrade and
		st.studentid='$studentID' and gs.id = gs_select.gsid ";
    $gs = $db->get_row($sql, ARRAY_A);
    $stu = $db->get_row("SELECT * from student where studentid = '$studentID' ", ARRAY_A);
    $grade = $stu['grade'];
    $site = $stu['site'];
    if ($gs['gradetype'] == '1') {
        $total = $db->get_var("SELECT count(*) as ct from standards
				WHERE subject = '$subject' and level = '$level' and (type='std' or type='over')
				");
        $sql = "SELECT count(*) as ct, symbol, gradetype, points from(grades as g, gs_grades as gsg, gs_select, gs) WHERE
					gsg.low <= convert(value,unsigned) and gsg.high >= convert(g.value,unsigned) and 
					gsg.gsid=gs_select.gsid and gs_select.siteid='$site' and $grade >= lowgrade and
				$grade <= highgrade and g.studentid='$studentID'and g.subject = '$subject' and
					g.level = '$level' and gs.id = gsg.gsid
				GROUP BY symbol";
        $sql = "SELECT count( * ) AS ct, symbol, points, val FROM (grades AS g, gs_grades AS gsg, standards as s)
				WHERE gsg.low <= convert( value, unsigned ) AND gsg.high >= convert( g.value, unsigned ) and g.std not like '%comment%'
					AND gsg.gsid = '{$gs['gsid']}' AND g.studentid = '$studentID' AND g.subject = '$subject' AND g.level = '$level'
					and s.subject = g.subject and s.level = g.level and s.std = g.std
				GROUP BY symbol";
        $result = $db->get_results($sql, ARRAY_A);

        foreach ($result as $r) {
            if (is_null($r['symbol']) or ($r['symbol'] == '')) {
                $r['symbol'] = 'NULL';
            }
            $over[$r['symbol']] = $r['ct'];
            $pts[$r['symbol']] = $r['points'];
            $value[$r['symbol']] = $r['val'];
        }
        $tweight = $db->get_var("SELECT weight FROM level WHERE subject='$subject' and level='$level' ");

        $emgNum = $over['EMG'];
        $devNum = $over['DEV'];
        $proNum = $over['PRO'];
        $advNum = $over['ADV'];
        $totalValues = $proNum + $emgNum + $advNum + $devNum;
        $avg = ($proNum * $value['PRO'] + $emgNum * $value['EMG'] + $advNum * $value['ADV'] + $devNum * $value['DEV']) / $totalValues;
        if ($emgNum == 0 and $devNum == 0 and $advNum > 0 and ($advNum / ($proNum + $advNum) >= .9)
                and $totalValues == $total) {
            $ans = "ADV";
        } else if ($emgNum == 0 and $devNum == 0 and $totalValues == $total) {
            $ans = "PRO";
        } else if (($proNum > 0 or $advNum > 0) and $total >= $totalValues) {
            $ans = "DEV";
        } else if ($total >= $totalValues) {
            $ans = "EMG";
        } else {
            $ans = "INTERNAL ERR - Too many values see developer";
        }
        $score = $ans;
        $advpro = $advNum + $proNum;
        $sans = ($advNum / ($advpro)) > .9 ? "ADV" : "PRO";
        $spoints = $pts[$sans];
        $percentcomp = $advpro / $total;
        $sweight = (floor($percentcomp * 4) / 4) * $tweight;
    } else {
        $sql = "SELECT AVG(value) as avg, COUNT(value) as ct FROM grades as g, standards as s
			WHERE s.subject = '$subject' and s.level = '$level' and 
				g.subject = s.subject and g.level = s.level and 
				s.std = g.std and (s.type='std' or s.type='over') and 
				studentid = '$studentID' and value > 0
				";
        $r = $db->get_row($sql, ARRAY_A); // get avg and number of scores
        $avg = round($r['avg'], 0);
        $sql = "SELECT symbol, points FROM gs_grades
			WHERE gs_grades.low <= '{$avg}' and gs_grades.high >= '{$avg}' and 
					gs_grades.gsid='{$gs['gsid']}'";
        $s = $db->get_row($sql, ARRAY_A);
        $sql = "SELECT count(*) as ct, weight FROM standards as s, level as l
			WHERE s.subject = '$subject' and s.level = '$level' and (s.type='std' or s.type='over') and
				l.subject = s.subject and l.level = s.level ";
        $t = $db->get_row($sql, ARRAY_A);

        $sql = "SELECT COUNT(value) as ct FROM grades as g, standards as s
			WHERE s.subject = '$subject' and s.level = '$level' and 
				g.subject = s.subject and g.level = s.level and 
				s.std = g.std and (s.type='std' or s.type='over') and 
				studentid = '$studentID' and value > '0'";
        $tt = $db->get_row($sql, ARRAY_A); // get avg and number of scores

        $percentcomp = $tt['ct'] / $t['ct'];
        $sweight = (floor($percentcomp * 4) / 4) * $t['weight'];
        $score = "<br>{$s['symbol']}/{$s['points']} - Avg: {$avg} - Complete/Total: {$r['ct']}/{$t['ct']} - Weight: {$t['weight']} Partial Weight: {$sweight} ";
        $score = $s['symbol'] . " {$avg}%";
        $score = ($s['symbol'] != '') ? $s['symbol'] . " {$avg}%" : "";
        $spoints = $s['points'];
    }

    $sql = "Update studentlevel
		 SET	progress='$score',
		 		  sweight = '$sweight',
		 		  percentcomp = '$percentcomp',
		 		  avg = '$avg',
		 		  spoints = '$spoints',
				change_username='$currentUserName', 
				change_user='$currentUserID', 
				change_timestamp='$tm'					
		 WHERE  studentID = '$studentID' and
				subject = '$subject' and
				level = '$level'";
    debugPrint("SQL Update =>" . $sql);

    $db->get_results($sql);
}

function updateChange2($studentID, $subject, $level) {
    global $db, $currentUserName, $currentUserID;

    $tm = time();
    $userID = logonID();
    $name = getUserName();
    $score = updateOverall2($studentID, $subject, $level);

    $sql = "Update studentlevel
				 SET	progress='$score',
						change_username='$currentUserName', 
						change_user='$currentUserID', 
						change_timestamp='$tm'					
				 WHERE  studentID = '$studentID' and
						subject = '$subject' and
						level = '$level'";
    debugPrint("SQL Update =>" . $sql);

    $db->get_results($sql);
}

function updateSingleLevelScore($studentID, $subject, $level) {
    global $db, $currentUserName, $currentUserID;
    return (updateChange($studentID, $subject, $level));
}

function allStudentLevels($id) {
    global $db;

    $sql1 = "SELECT DISTINCT subject, level
					FROM grades
					WHERE studentid = '$id'";
    debugPrint("<br>All Grades =>" . $sql1);
    $res1 = $db->get_results($sql1, ARRAY_A);

    $sql2 = "SELECT subject, level
					FROM studentlevel
					WHERE studentid = '$id'";
    debugPrint("<br>All Student Level =>" . $sql2);
    $res2 = $db->get_results($sql2, ARRAY_A);

    $results = array_merge($res1, $res2);
    debugPrint("<br>AFTER MERGE: " . print_r($results, true));
    $results = array_unique2($results);

    $sql3 = "SELECT subject, level, final
					FROM studentlevel
					WHERE studentid = '$id'";
    debugPrint("<br>All Student Level =>" . $sql2);
    $res3 = $db->get_results($sql3, ARRAY_A);
    debugPrint("<br>ADDING FINAL: " . print_r($results, true));

    foreach ($res3 as $rec) {
        $sub = $rec['subject'];
        $lvl = $rec['level'];
        $value = $rec['final'];
        $final[$sub][$lvl] = $value;
        debugPrint("****** Create Final $sub$lvl $value ********<br>");
    }

    $results = array_sort($results, 'subject');
    $ct = count($results);
    for ($i = 0; $i < $ct; $i++) {
        $sub = $results[$i]['subject'];
        $lvl = $results[$i]['level'];
        $value = $final[$sub][$lvl];
        $results[$i]['final'] = $value;
        debugPrint("****** Add Final $sub$lvl $value ********<br>");
    }

    return($results);
}

function array_unique2($input) { // multiarray dedup which renumbers elements
    $tmp = array();
    foreach ($input as $a => $b)
        $tmp[$a] = serialize($b);
    $newinput = array();
    $i = 0;
    foreach (array_unique($tmp) as $a => $b)
        $newinput[$i++] = $input[$a];
    debugPrint("<br><br>====>" . print_r($newinput, true));
    return $newinput;
}

function allStudentGrades($id) {
    global $db;

    $sql = "SELECT *
					FROM grades
					WHERE studentid = '$id'";
    debugPrint("All Grades =>" . $sql);
    $results = $db->get_results($sql);
    foreach ($results as $res) {
        $ret[$res->subject][$res->level][$res->std] = $res->value;
    }
    return $ret;
}

function getStandards($sub, $lvl) {
    global $db;

    $sql = "SELECT *
					FROM standards
					WHERE subject = '$sub' and 
							level = '$lvl' and
							(type = 'std' or type = 'over')
					order by standards.order ASC";
//			debugPrint ("<br>All Standards =>" . $sql);
    $results = $db->get_results($sql, ARRAY_A);
    return($results);
}

function removeList($studentid, $listid) {
    global $db;

    $sql = "delete from listvalues where listid = '$listid' and studentid = '$studentid'";
//		 debugPrint($sql);
    $db->get_results($sql);
//		 return ($sql);
}

function addList($studentid, $listid) {
    global $db;

    $sql = "insert into listvalues set listid = '$listid', studentid = '$studentid'";
    $db->get_results($sql);
}

function newList($user, $name="{Name Group!}", $type="self", $kind='', $sql='') {
    global $db;
    $user = logonID();
    $sql = "insert into lists set userid = '$user', type = '$type', listname = '$name', lists.kind='$kind', lists.sql='$sql'";
    debugPrint($sql);
    $db->get_results($sql);
    return($db->insert_id );
}

function deleteList($listid) {
    global $db;

    $sql = "delete from lists where listid = '$listid'";
    debugPrint($sql);
    $db->get_results($sql);
    $sql = "delete from listvalues where listid = '$listid'";
    debugPrint($sql);
    $db->get_results($sql);
}

function updateListName($listid, $name) {
    global $db;

    $sql = "update lists set listname = '$name' where listID = $listid";
    debugPrint($sql);
    $db->get_results($sql);
}

function updateListType($listid, $type, $userID) {
    global $db;

    $sql = "update lists set type = '$type', userID = '$userID' where listID = '$listid'";
    debugPrint($sql);
    $db->get_results($sql);
}

function getListName($listID) {
    global $db;
    $query = "select listname from lists where listid='$listID'";
    debugPrint("<br>GetListName => " . $query);
    $results = $db->get_results($query);

    return ($results[0]->listname);
}

function getListInfo($listID) {
    global $db;
    $query = "select * from lists where listid='$listID'";
    $results = $db->get_results($query, ARRAY_A);

    return ($results[0]);
}

function dupList($listID) {
    global $db;

    $l1 = getListInfo($listID);
    $lists1 = getListItems($listID);
    $l2 = newList($l1['userid'], "c_" . $l1['listname'], $l1['type'], $l1['kind'], addslashes($l1['sql']));
    foreach ($lists1 as $item) {
        $studentid = $item['studentid'];
        $sql = "insert into listvalues set listid = '$l2', studentid = '$studentid'";
        debugPrint($sql);
        $db->get_results($sql);
    }
    return ($l2);
}

/* It seams this function is only used in showScores.inc, that functionality should be reimplemented */

function getGradesList($listid) {
    global $db;

    $studentlist = getListStudents($listid);
    $sql = "select grades.* from grades where grades.studentid in ($studentlist)";
    debugPrint("<br>getGradesList => " . $sql);
    $result = $db->get_results($sql);
    foreach ($result as $res) {
        $ret[$res->studentid][$res->subject][$res->level][$res->std] = $res->value;
        debugPrint("<br>Student: " . $res->studentid . " Subject: " . $res->subject . " Level: " . $res->level . " Std: " . $res->std . " Value: " . $res->value);
    }
    return $ret;
}

/* It seams this function is never used */

function getGradesListTotal($listid) {
    global $db;

    $studentlist = getListStudents($listid);

    $sql = "select standards.subject, standards.level, standards.std from  studentlevel, standards where studentlevel.studentid in ($studentlist) and studentlevel.subject = standards.subject and studentlevel.level = standards.level";
    debugPrint("<br>getGradesListTotal => " . $sql);
    $result = $db->get_results($sql);
    return (count($result));
}

function getSutdentSubjectStandards($studentID, $sub, $level) {
    global $db;

    $sql = "SELECT * FROM grades WHERE
			grades.studentid = '$studentID'
			AND grades.subject = '$sub'
			AND grades.level  = '$level'
			ORDER BY grades.std ASC";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function getStudentLevels($studentID, $a="and studentlevel.final = '00000000'") {
    global $db;

    $sql = "SELECT *, level.name as sname FROM studentlevel, subjects, level WHERE
			studentid = '$studentID'
			and studentlevel.subject = subjects.id and
			studentlevel.subject = level.subject and 
			studentlevel.level = level.level 
			$a
			ORDER BY `subjects`.`order` ASC, `level`.`level` ASC";
    debugPrint("<br>Get Sustent Levels: $sql<br>");
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function getStdValue($std, $scores) {

    debugPrint($std);
    if ($scores) {
        foreach ($scores as $rec) {
            if ($rec['std'] == $std)
                return ($rec['value']);
        }
    }
    return (NULL);
}

function getAllStudentInfo($id) {
    global $db;

    $sql = "SELECT * FROM student WHERE studentid = '$id'";
    debugPrint($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results[0]);
}

function saveStudentValue($id, $field, $value) {
    global $db;

    $sql = "Update student SET $field = '$value' where studentid = '$id'";
    debugPrint($sql);
    $db->get_results($sql);
}

function printValues($values) {
    $listid = $values['id'];

    while (list($var, $val) = each($values)) {
        if ($var == "removeselect") {
            foreach ($val as $val2) {
                removeList($val2, $listid);
            }
        } else if ($var == "addselect") {
            foreach ($val as $val2) {
                addList($val2, $listid);
            }
        }
    }
}

function logEntry($tp, $val, $student="", $subject="", $lvl="", $std="") {
    global $db;

    $user = logonID();
    $ip = $_SERVER['REMOTE_ADDR'];
    $tm = time();
    $sql = "insert into history2 set type = '$tp', ip = '$ip', userid = '$user', value = '$val', studentID = '$student', subject = '$subject', lvl = '$lvl', std = '$std', timestamp = '$tm'";
    debugPrint("<br>History=>" . $sql);
    $db->get_results($sql);
}

function comparisonClause($class, $list, $value1, $symbol, $quote="") {
    if ($value1 <> "") {
        $ret = "$class $symbol $quote$value1$quote";
        if ($list <> "") {
            $ret = $list . " and " . $ret;
        }
    } else {
        $ret = $list;
    }
    return $ret;
}

// https://dart.bssd.org/index.php?cmd=count&start=04%2F01%2F2010&startOutput=1270094400&end=05%2F02%2F2010&endOutput=1272772800&site=DIO&toggle=student&button=go
function whereClause($class, $list, $value1, $quote="") {
    if ($value1 <> "") {
        $ret = "$class = $quote$value1$quote";
        if ($list <> "") {
            $ret = $list . " and " . $ret;
        }
    } else {
        $ret = $list;
    }
    return $ret;
}

function getEntries($start=0, $limit=30, $student="", $user="", $subject="", $lvl="", $site="", $starttime="", $endtime="", $toggletype='') {
    global $db;

    $clause = whereClause("history2.userid", $clause, $user, "'");
    $clause = whereClause("history2.subject", $clause, $subject, "'");
    $clause = whereClause("history2.studentID", $clause, $student, "'");
    $clause = whereClause("history2.lvl", $clause, $lvl, "'");
    $clause = whereClause("history2.userid", $clause, "user.userid");
    $clause = whereClause("user.site", $clause, $site, "'");
    $comp = ($toggletype == 'comment') ? '=' : '!=';
    $toggletype = ($toggletype == 'std') ? 'comment' : $toggletype;
    $clause = comparisonClause("history2.std", $clause, $toggletype, $comp, "'");
    $clause = comparisonClause("timestamp", $clause, $starttime, ">", "'");
    $clause = comparisonClause("timestamp", $clause, $endtime, "<", "'");
    $sqlcount = "select count(*) as num from history2, user where $clause";
    $res1 = $db->get_results($sqlcount);
    $total = $res1[0]->num;
    $sql = "select *, history2.studentID from (history2, user)
				LEFT JOIN student ON history2.studentID = student.studentid
				WHERE $clause";
    $sql .= " order by timestamp desc LIMIT $start, $limit";
    $res2 = $db->get_results($sql, ARRAY_A);
    $results['list'] = $res2;
    $results['total'] = $total;
    return ($results);
}

function getLoginEntries($start=0, $limit=30, $user="", $site="") {
    global $db;

    $clause = whereClause("history.userid", $clause, $user, "'");
    $clause = whereClause("history.userid", $clause, "user.userid");
    $clause = whereClause("user.site", $clause, $site, "'");
    $sqlcount = "select count(*) as num from history, user where $clause";
    $res1 = $db->get_results($sqlcount);
    $total = $res1[0]->num;
    $sql = "select *, history.type from history, user where $clause";
    $sql .= " order by timestamp desc LIMIT $start, $limit";
    $res2 = $db->get_results($sql, ARRAY_A);
    $results['list'] = $res2;
    $results['total'] = $total;
    return ($results);
}

function logHistory($type, $p1, $p2, $p3, $userid = "") {
    global $db, $currentUserID;

    if ($userid == "") {
        $userid = $currentUserID;
    }
    $ip = $_SERVER['REMOTE_ADDR'];
    $sql = "insert into history set type = '$type', ip = '$ip', userid = '$userid', p1 = '$p1', p2 = '$p2', p3 = '$p3'";
    debugPrint("<br>History=>" . $sql);
    $db->get_results($sql);
}

function getHistory($start) {
    $sql = "SELECT timestamp, TYPE , name, p1, p2, p3 FROM history, user WHERE history.userid = user.userid
LIMIT 0 , $limit ";
    $res = $db->get_results($sql);
    return ($res);
}

function getToggleAlerts() {
    global $db;
    $tm = time();

    $sql = "SELECT * FROM alert_toggles, studentlevel, student WHERE student.studentid = studentlevel.studentid and alert_toggles.subject = studentlevel.subject and alert_toggles.lvl = studentlevel.level and studentlevel.change_timestamp <  $tm - (alert_toggles.days * 86400)";
    debugPrint($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function getNotes($site) {
    global $db, $currentMySite;

    $sql = "SELECT * FROM site WHERE siteID = '$site'";
    debugPrint($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results[0]);
}

function saveNotes($site, $important, $warning, $tip) {
    global $db;

    $sql = "Update site
				 SET	important='$important', 
						warning='$warning', 
						tip='$tip'					
				 WHERE  siteid = '$site'";
    debugPrint("SQL Update =>" . $sql);
    $db->get_results($sql);
}

function getRepNotes($site) {
    global $db, $currentMySite;

    $sql = "SELECT * FROM repnotes WHERE site = '$site'";
    debugPrint($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results[0]);
}

function saveRepNotes($site, $notes) {
    global $db;

    $notes = addslashes($notes);

    if (getRepNotes($site) == NULL) {
        $sql = "insert repnotes
					SET	comment=\"$notes\",				   
						site = '$site'";
    } else {
        $sql = "Update repnotes
					SET	comment=\"$notes\"				   
					WHERE  site = '$site'";
    }
    debugPrint("<br>SQL Rep Notes =>" . $sql);
    $db->get_results($sql);
}

function getSites($priv="none", $admin=true) {
    global $db, $currentMySite;

    $results = "";
    if ($priv != 'none') {
        $where = $priv == 'site' ? " and siteid = '$currentMySite' " : "";
        $where .= $admin ? "" : " and name != 'Admin' ";
        $sql = "SELECT * FROM site where 1 $where order by site.order ASC";
        debugPrint($sql);
        $results = $db->get_results($sql, ARRAY_A);
//			  return ($results);
    }
    return ($results);
}

function getSitesOptions($selected, $type="district") {

    $str = "";
    $sites = getSites($type);
    foreach ($sites as $site) {
        $id = $site['siteid'];
        $str .= "<option value =\"$id\" " . selected($id, $selected) . ">$id</option>\n";
//			 debugPrint("\n<br>ID: $id $SELECTED: $selected STR: $str");
    }
    $str .= "<option value =\"Private\" " . selected("Private", $selected) . ">Private</option>\n";
    return ($str);
}

function getGradesSelection($selected) {
    $results = "<option value=\"\" " . selected("", $selected) . ">none</option>
		<option value=\"PK\" " . selected("PK", $selected) . ">PK</option>
		<option value=\"K\" " . selected('K', $selected) . ">K</option>
		<option value=\"1\" " . selected('1', $selected) . ">1</option>
		<option value=\"2\" " . selected('2', $selected) . ">2</option>
		<option value=\"3\" " . selected('3', $selected) . ">3</option>
		<option value=\"4\" " . selected('4', $selected) . ">4</option>
		<option value=\"5\" " . selected('5', $selected) . ">5</option>
		<option value=\"6\" " . selected('6', $selected) . ">6</option>
		<option value=\"7\" " . selected('7', $selected) . ">7</option>
		<option value=\"8\" " . selected('8', $selected) . ">8</option>
		<option value=\"9\" " . selected('9', $selected) . ">9</option>
		<option value=\"10\" " . selected('10', $selected) . ">10</option>
		<option value=\"11\" " . selected('11', $selected) . ">11</option>
		<option value=\"12\" " . selected('12', $selected) . ">12</option>
		<option value=\"13\" " . selected('13', $selected) . ">13</option>";
    return ($results);
}

function getSiteInfo($site) {
    global $db;

    $sql = "SELECT * FROM site where siteID = '$site'";
    debugPrint($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results[0]);
}

function setIfNeeded($value, $default) {
    if ($value <> "") {
        return $value;
    } else {
        return $default;
    }
}

function getListWeight($listid, $subject="", $level="", $student="") {
    global $db;

    $sql = "select * from listvalues where listid=$listid";
    debugPrint($sql);
    $results = $db->get_results($sql);
    $total = $db->num_rows;

    $sql = "select grades.subject, grades.level, grades.std, sum(num) as sum, count(num) as count, sum(num)*count(num)/$total as comp, shortname, link from grades, listvalues, standards where listvalues.listid=$listid and listvalues.studentid = grades.studentid and grades.subject = standards.subject and grades.level = standards.level and grades.std = standards.std group by grades.subject, grades.level, grades.std order by comp desc";
    debugPrint($sql);
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

// Weighted list for individual		
function getIndWeight($id) {
    global $db;

    $sql = "select grades.subject, grades.level, grades.std, grades.num, shortname, link from grades, studentlevel, standards where standards.type='std' and studentlevel.studentid='$id' and standards.type = 'std' and studentlevel.studentid = grades.studentid and studentlevel.subject = grades.subject and studentlevel.level = grades.level and grades.subject = standards.subject and grades.level = standards.level and grades.std = standards.std order by num desc";
    debugPrint("<br>getIndWeight=> " . $sql . "<br>");
    $results = $db->get_results($sql, ARRAY_A);
    debugPrint("getIndWeight array: " . print_r($results, true) . "<br>");
    return ($results);
}

function getListSubjectLevelWeight($listid, $subject, $level) {
    global $db;

    $sql = "select * from listvalues where listid=$listid";
    debugPrint("TOTAL SQL: " . $sql . "<br>");
    $results = $db->get_results($sql);
    $total = $db->num_rows;

    $sql = "select grades.subject, grades.level, grades.std, sum(num) as sum, count(num) as count, sum(num)*count(num)/$total as comp, shortname, link from grades, listvalues, standards where standards.type='std' and listvalues.listid=$listid and listvalues.studentid = grades.studentid and grades.subject = standards.subject and grades.level = standards.level and grades.std = standards.std and grades.subject='$subject' and grades.level='$level' group by grades.subject, grades.level, grades.std order by comp desc";
    debugPrint("GROUP SQL: " . $sql . "<br>");
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function commentSpace($value) {
    if ($value == "") {
        return "&nbsp;";
    } else {
        return $value;
    }
}

function array_sort($array, $key) {
    for ($i = 0; $i < sizeof($array); $i++) {
        $sort_values[$i] = $array[$i][$key];
    }
    asort($sort_values);
    reset($sort_values);
    while (list ($arr_key, $arr_val) = each($sort_values)) {
        $sorted_arr[] = $array[$arr_key];
    }
    return $sorted_arr;
}

function getSearchSQL($values) {
    $wherestudent = "";
    $wherelevel = "";
    $wheregrades = "";
    $tables = "";

//		 $wherestudent .= createLike($values['sped'], "student.sped");
    $wherestudent .= createLike($values['fname'], "student.fname");
    $wherestudent .= createLike($values['lname'], "student.lname");
    $wherestudent .= createDate($values['age'], "student.bday");
    $wherestudent .= createEqual($values['status'], "student.status");
    $wherestudent .= createEqual($values['LEPstatus'], "student.LEPstatus");
    $wherestudent .= createEqual($values['studentnumber'], "student.studentid");
    $wherestudent .= createEqual($values['aid'], "student.alaskaid");
    $wherestudent .= createEqual($values['psid'], "student.psid");
    $wherestudent .= createEqual($values['Eligibility'], "student.Eligibility");
    $wherestudent .= createOr($values['grade'], "student.grade");
    $wherestudent .= createEqual($values['gender'], "student.gender");
    $wherestudent .= createEqual($values['HSGQEReading'], "student.HSGQEReading");
    $wherestudent .= createEqual($values['HSGQEWriting'], "student.HSGQEWriting");
    $wherestudent .= createEqual($values['HSGQEMath'], "student.HSGQEMath");
//		 $wherestudent .= createFunction($values['age'], "student.age");
    $wherestudent .= createBetween($values['attendance'], "student.attper");
    $wherestudent .= createBetween($values['suspension'], "student.absent");

    $wherelevel .= createOr($values['areas'], "studentlevel.subject");
    $wherelevel .= createOr($values['level'], "studentlevel.level");
    $wherelevel .= createOr($values['overall'], "studentlevel.progress");

    if ($values['area'] != '' or $values['level'] != '')
        $wherelevel .= " studentlevel.final = '0000-00-00 00:00:00' and ";

    $wheregrades .= createOr($values['QPIs'], "grades.value");

    $wheresite .= createOr($values['locationids'], "student.site");

    if ($wheregrades != "") {
        $other .= " student.studentid = grades.studentid and ";
        $tables .= "grades, ";
        $wherelevel .= "studentlevel.subject = grades.subject and studentlevel.level = grades.level and ";
    }

    if ($values['sped'] != "") {
        if ($values['sped'] == 'Y') {
            $other .= "student.studentid IN (SELECT studentid from speddata where entrysped > exitdate) and";
        } else {
            $other .= "student.studentid IN (SELECT student.studentid
					FROM student
					LEFT JOIN speddata ON speddata.studentid = student.studentid
					WHERE (ISNULL( entrysped ) OR (entrysped < exitdate))) and";
        }
    }
    if ($wherelevel != "") {
        $other .= " student.studentid = studentlevel.studentid and ";
        $tables .= "studentlevel, ";
    }

    if ($wheresite != "") {
        $other .= " student.site = site.siteid and ";
        $tables .= "site, ";
    }

    $sql = "select *, (CURDATE() - bday) as age from $tables student where $wherestudent $wherelevel $wheregrades $wheresite $other 1 group by student.studentid";
    return $sql;
}

function age($DOB) {
    if ($DOB != 0) {
        $dayinseconds = 24 * 60 * 60;
        $dayinYear = 0.00273972602739726;

        $dif = time() - strtotime($DOB);

        $age_in_days = $dif / $dayinseconds;

        $flt_year = $age_in_days * $dayinYear;
        $year = floor($flt_year);

        $flt_month = ($flt_year - $year) * 12;
        $month = floor($flt_month);

        $flt_day = ($flt_month - $month) * 30.58;
        $day = floor($flt_day);

        return $year . "y " . $month . "m " . $day . "d";
    } else {
        return("unk");
    }
}

function age_old($bday) {
    if ($bday != 0) {
        $cur_year = date("Y");
        $cur_month = date("m");
        $cur_day = date("d");

        $dob_year = substr($bday, 0, 4);
        $dob_month = substr($bday, 5, 2);
        $dob_day = substr($bday, 8, 2);

        if ($cur_month > $dob_month || ($dob_month == $cur_month && $cur_day >= $dob_day))
            return $cur_year - $dob_year;
        else
            return $cur_year - $dob_year - 1;
        $span = "7<br>";
    } else {
        $span = 0;
    }
    return ($span);
}

function createBetween($val, $str) {
    $returnStr = "";
    if (isset($val) and $val != "") {
        $val1 = "x";
        $val2 = "y";
        $returnStr = " $str >= '$val1' and $str <= '$val2' and ";
    }
    return ($returnStr);
}

function createDate($val, $str) {
    $returnStr = "";
    if (isset($val) and $val != "") {
        $y = date("Y");
        $m = date("m");
        $d = date("d");
        $val1 = $y - $val - 1 . "-$m-$d";
        $val2 = $y - $val . "-$m-$d";
        $returnStr = $val == '18' ?
                " bday != '0000-00-00' and $str <= '$val2' and " :
                " $str <= '$val2' and $str > '$val1' and ";
    }
    return ($returnStr);
}

function createLike($val, $str) {
    $returnStr = "";
    if (isset($val) and $val != "") {
        $returnStr = " $str like \"%$val%\" and ";
    }
    return ($returnStr);
}

function createEqual($val, $str) {
    $returnStr = "";
    if (isset($val) and $val != "") {
        $returnStr = " $str = '$val' and ";
    }
    return ($returnStr);
}

function createFunction($val, $str) {
    $returnStr = "";
    if (isset($val) and $val != "") {
        $returnStr = " $str $val and ";
    }
    return ($returnStr);
}

function createOr($arr, $val, $andFlag=TRUE) {
    $orval = "";
    if ($arr[0] != "" and count($arr) != 0) {
        foreach ($arr as $el) {
            debugPrint("  $val = $el<BR>");
            if ($orval != "") {
                $orval .= " or ";
            }
            $orval .= "$val = '$el'";
        }
        if ($orval != "" and $andFlag == TRUE) {
            $orval = "($orval) and ";
        }
    }
    return ($orval);
}

function getStudentSearchResults($values, $start, $limit) {
    global $db;

    $sql = getSearchSQL($values);
    $results['sql'] = $sql;
    debugPrint("SQL Results: " . $sql);
    $res1 = $db->get_results($sql);
    $total = $db->num_rows;
    debugPrint("SQL Total: " . $total . "<br>");
    $sql = $sql . " order by lname asc LIMIT $start, $limit";
    debugPrint("SQL LIMIT: " . $sql . "<br>");
    $res2 = $db->get_results($sql, ARRAY_A);
    $results['list'] = $res2;
    $results['total'] = $total;
    return ($results);
}

function createEqualAnd($val, $str, $clause) {
    $returnStr = "";
    if (isset($val) and $val != "") {
        if ($clause != "") {
            $pre = "and";
        }
        $returnStr = "$pre $str = '$val'";
    }
    return ($returnStr);
}

function getPivotValues($studentID, $gradelevel, $site) {
    global $db;
//		 $whereclause = "studentlevel.final = 0 ";

    $whereclause .= createEqual($studentID, "student.studentID");
    $whereclause .= createEqual($gradelevel, "student.grade");
    $whereclause .= createEqual($site, "student.site");

    $sql = "SELECT studentlevel.subject, level.numlevel as level, count(studentlevel.studentid) as num FROM studentlevel, student, level $table where $whereclause studentlevel.level = level.level and studentlevel.subject = level.subject and student.status = 'Active' and studentlevel.studentid = student.studentid and studentlevel.final = '00000000' group by subject, numlevel";
    debugPrint("Pivot sql: " . $sql);
    $results = $db->get_results($sql);
    $i = 0;
    foreach ($results as $res) {
        $subject = $res->subject;
        $level = $res->level;
        $num = $res->num;
        $values[$subject][$level] = $num;
    }
    $v['values'] = $values;

    return ($v);
}

function getPivotStudents($studentID, $gradelevel, $site, $sub, $lvl) {
    global $db;

    $whereclause .= createEqual($studentID, "student.studentID");
    $whereclause .= createEqual($gradelevel, "student.grade");
    $whereclause .= createEqual($site, "student.site");
    $whereclause .= createEqual($sub, "studentlevel.subject");
    $whereclause .= createEqual($lvl, "level.numlevel");

    $sql = "SELECT * FROM studentlevel, level, student $table where $gradeclause $whereclause studentlevel.level = level.level and studentlevel.subject = level.subject and studentlevel.studentid = student.studentid and studentlevel.final = 0 and student.status = 'Active' order by lname ASC";
    debugPrint("PivotDrilldown: " . $sql);
    $results = $db->get_results($sql);
    return ($results);
}

function pulldownPivotStudents($id, $gradelevel, $site) {
    global $db;

    $whereclause .= createEqual($id, "student.studentID");
    $whereclause .= createEqual($gradelevel, "student.grade");
    $whereclause .= createEqual($site, "student.site");

    $sql = "select * from student where $whereclause student.status = 'Active' order by lname ASC";
    debugPrint("<br>Pulldown SQL: $sql<br>");
    $results = $db->get_results($sql);
    $returnArr['count'] = $db->num_rows;

    $pulldown = "<select name=\"studentID\" onChange=\"submit()\">
												<option value=\"\">All Students</option>";

    foreach ($results as $res) {
        if ($res->studentid == $id) {
            $sel = "selected";
        } else {
            $sel = "";
        }
        $pulldown .= "<option value=" . $res->studentid . " $sel>" . $res->lname . ", " . $res->fname . "</option>";
    }
    $pulldown .= "</select>";

    $returnArr['options'] = $pulldown;

    return ($returnArr);
}

function savePostedPriv($values, $user) {
    global $db;

    $scopeA = 0;
    $privA = 0;
    $scopeB = 0;
    $privB = 0;

    while (list($var, $val) = each($values)) {
//		   debugPrint("VAR: $var VAL: $val<br>");
        $flag = substr($val, 0, 2);
        $num = intval(substr($val, 3, 300));
        debugPrint("VAR: $var VAL: $val FLAG: $flag NUM: $num<br>");
        if ($flag == "A1") {
            $privA = $privA + $num;
        } else if ($flag == "A2") {
            $scopeA = $scopeA + $num;
            $privA = $privA + $num;
        } else if ($flag == "B1") {
            $privB = $privB + $num;
        } else if ($flag == "B2") {
            $scopeB = $scopeB + $num;
            $privB = $privB + $num;
        }
    }
    debugPrint("Priv: $priv Scope: $scope<br>");
    $sql = "Update user set privilegeA = '$privA', scopeA = '$scopeA',
								privilegeB = '$privB', scopeB = '$scopeB'
							where userid = '$user'";
    debugPrint("SQL=>" . $sql . "<br>");
//		 exit();
    $db->get_results($sql);
    logHistory("Privilege Change", $user, $privA, $scopeA);
}

function handleGroup($values, $user, $action) {
    $listID = newList($user);
    for ($i = 0; $i < count($values); $i++) {
        addList($values[$i], $listID);
    }
    return ($listID);
}

function exportList($listid, $type='') {
    global $db;
    $stack = array();

    $studentlist = getListStudents($listid);
    $stack = explode(",", $studentlist);
    exportGroup($stack, $type);
    debugPrint("here3");
}

// "/home/dartdb/public_html/exp/" 
function exportGroup($values, $type="") {
    global $db, $exportDIR;

    set_time_limit(0);
    $fnname = "export_" . logonID() . ".xls";
    $fn = $exportDIR . $fnname;
//		 $exp = createOr($values, "student.studentid", FALSE); 
    foreach ($values as $val)
        $vala[] = "\"" . $val . "\"";
    $exp = " student.studentid in (" . implode(", ", $vala) . ")";

    if ($type == 'sfa') {
        $sql2 = "select * from student left join sfascores ON sfascores.studentid = student.studentid where ($exp)";
    } else {
        $sql2 = "select * from student left join grades on student.studentid = grades.studentid where ($exp)";
    }
    debugPrint("EXPORT SQL: $sql2<br>");
    $results2 = $db->get_results($sql2);
    $cols2 = $db->get_col_info("name");
//		 print_r($results2);
    debugPrint("EXPORT FN: $fn<br>");

    $fp = fopen($fn, 'w');
    newfputcsv($fp, $cols2, "\t");
    foreach ($results2 as $ln) {
        newfputcsv($fp, $ln, "\t");
    }

    debugPrint("FINISHED WITH FN: $fn<br>");
    fclose($fp);

    header("Pragma: public");
    header('Expires: ' . gmdate('D, d M Y H:i:s') . ' GMT');
    header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
    header("Cache-Control: private", false);
    header("Content-Type: application/text");
    header('Content-Disposition: attachment; filename="' . $fnname . '"');
    header("Content-Transfer-Encoding: binary");
    header('Content-Length: ' . filesize($fn));
    @readfile($fn) OR die("<html><body OnLoad=\"javascript: alert('File not found');history.back();\" bgcolor=\"#F0F0F0\"></body></html>");

    return ($fn);
}

function newfputcsv($filePointer, $dataArray, $delimiter=",", $enclosure="\"") {
    // Write a line to a file
    // $filePointer = the file resource to write to
    // $dataArray = the data to write out
    // $delimeter = the field separator
    // Build the string
    $string = "";
    $writeDelimiter = TRUE;
    foreach ($dataArray as $dataElement) {
        $dataElement = str_replace("\"", "\"\"", $dataElement);
        if ($writeDelimiter)
            $string .= $delimiter;
        $string .= $enclosure . $dataElement . $enclosure;
        $writeDelimiter = TRUE;
    } // end foreach($dataArray as $dataElement)
    // Append new line
    $string .= "\n";

    // Write the string to the file
    fwrite($filePointer, $string);
}

// end function fputcsv($filePointer, $dataArray, $delimiter)

function getUserNameInfo($username) {
    global $db;

    $query = "select * from user where user='$username'";
    debugPrint("getUserInfo: " . $query);
    $res = $db->get_results($query, ARRAY_A);
    return($res[0]);
}

function getPwd($username) {
    global $dartEmail, $db, $rootURL;

    $sql = "select * from user where user='$username'";
    debugPrint("forgetPassword: " . $sql);
    $result = $db->get_results($sql);
    $res = $result[0];
    debugPrint("Here in getPWD");
    $email = $res->email;
    debugPrint("Email: $email");

    if ($email == "") {
        $ans['result'] = FALSE;
        $ans['msg'] = "The user name you gave does not exist in our system";
    } else {
        $name = $res->name;
        $pwd = $res->pwd;
        $headers = "From: Dart Admin <$dartEmail>\n";
        $to_email = "$name <$email>\n";
        $subject = "Password for Dart";

        $message = "Hello $name,\nYour password is $pwd.\nPlease go to $rootURL. To logon with your password.";
        debugPrint("<br>MSG: " . $message);
        if (mail($to_email, $subject, $message, $headers)) {
            $ans['result'] = TRUE;
            $ans['msg'] = "Your password will be emailed to your email address on file shortly.";
        } else {
            $ans['result'] = FALSE;
            $ans['msg'] = "Sorry we are having temporary trouble with sending mail. Please try again later or call dart administrator.";
        }
    }
    return ($ans);
}

function initialize() {
    global $db;

    $res['studentlevel'] = updateStudentLevelProgress();
    $res['gradenum'] = updateGradeNum();
}

function updateStudentLevelProgress() {
    global $db;

    $sql = "select * from studentlevel";
    $studentlevels = $db->get_results($sql);
    $number = $db->num_rows;
    $i = 0;
    echo "<table border=0><tr><td width=300>&nbsp;</td></tr><tr><td>";
    foreach ($studentlevels as $sl) {
        if (floor($i++ / 100) == 0) {
            echo ("* ");
        }
//			echo ("* ");
//			echo ($i++ . ") Initialize: $sid-$sub-$lvl<br>");
        $sid = $sl->studentid;
        $sub = $sl->subject;
        $lvl = $sl->level;
        updateChange($sid, $sub, $lvl);
    }
    echo "</td></tr></table>";
    return ($number);
}

function updateGradeNum() {
    global $db;
    $sql = "select * from grades";
    $grades = $db->get_results($sql);
    $number = $db->num_rows;

    foreach ($grades as $grade) {
        $val = $grade->value;
        $num = getToggleValue($val);
        $studentid = $grade->studentid;
        $subject = $grade->subject;
        $level = $grade->level;
        $std = $grade->std;
        $sql = "Update grades
					SET num = '$num'
					WHERE
					studentid = '$studentid' and
					subject = '$subject' and
					level = '$level' and
					std = '$std'";

        debugPrint("SQL=>" . $sql . "<br>");
        $db->get_results($sql);
    }
    return ($number);
}

function checkStudent($id, $site, $a2, $a3) {
    global $A2A3;

    $retVal = $A2A3[$id][$site][$a2][$a3];
    return ($retVal);
}

function NoPriv($type, $notes) {
//		  echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=noPrivilege&type=$type&notes=$notes\"> ");
    header("Location: index.php?cmd=noPrivilege&type=$type&notes=$notes/");
}

function viewReport($id, $site, $a) {
    if ($id == 1) {
        return true;
    } else if ($a == 'district') {
        return true;
    } else if ($site == 1 and $a = 'site') {
        return true;
    } else {
        return false;
    }
}

function updatePremissions($privA, $scopeA, $id) {
    global $db;

    $sql = "Update user SET privilegeA = '$privA',
								 scopeA = '$scopeA' 
							 WHERE userid = '$id'";
    debugPrint("updatePremissions SQL=>" . $sql . "<br>");
    $db->get_results($sql);
}

function sendMailDart($subject, $message) {
    global $currentUserID, $currentUserName, $currentPrivA, $currentPrivB, $currentScopeA, $currentScopeB, $currentMySite;

    $message = "Hello Robert,
			$message

	CurrentUser = $currenUserName
	CurrentUserID = $currentUserID
	currentMySite = $currentMySite
	currentPrivA = $currentPrivA
	currentScopeA = $currentScopeA";
    $headers = "From: Dart Admin <$dartEmail>\n";
    $to_email = "Robert Jospeh <dart@vizmotion.com>\n";

    mail($to_email, $subject, $message, $headers);
}

function UpdateStudents() {
    global $db;

    $sql = "select * from loadtable";
    $results = $db->get_results($sql);
    $i = 0;
    foreach ($results as $res) {
        $p1 = $res->param1;
        $p2 = $res->param2;
        $p3 = $res->param3;
        $p4 = $res->param4;
        $sql2 = "update student set user='$p2', pwd='$p3', email='$p4'
					 where studentid = '$p1'";
        $db->get_results($sql2);
//			if($i++ == 10) { break; }
    }
}

function getQuarterDates() {
    global $db, $CurrentYear, $CurrentQuarter;

    $sql = "SELECT start, finish as stop from quarters where year = '$CurrentYear' and quarter = '$CurrentQuarter'";
    $dates = $db->get_results($sql, ARRAY_A);
    return($dates[0]);
}

function getAttendance($id, $startdate='2007-01-01', $enddate='2008-01-01') {
    global $db, $CurrentYear, $CurrentQuarter;

    $sql = "SELECT start, finish from quarters where year = '$CurrentYear' and quarter = '$CurrentQuarter'";
    $dates = $db->get_results($sql, ARRAY_A);
    $startdate = $dates[0]['start'];
    $enddate = $dates[0]['finish'];
    $sql = "SELECT count(AG.GroupID)/2 as count, GroupID
				FROM AttendanceEvents AE, AttendanceCodeGroups AG, student S
				WHERE AE.Date BETWEEN '$startdate' AND '$enddate' AND AE.CodeID = AG.CodeID 
					AND S.studentid = AE.studentid AND S.studentid = '$id'
				GROUP BY AG.GroupID";
    $attendance = $db->get_results($sql, ARRAY_A);
    $studentattendance[0] = 0;
    $studentattendance[4] = 0;
    foreach ($attendance as $at)
        $studentattendance[$at['GroupID']] = number_format($at['count'], 1);
    $studentattendance['rate'] = round(($studentattendance[4] / ($studentattendance[0] + $studentattendance[4]) * 100), 0);
    return($studentattendance);
}

function getReportListItems($userID) {
    global $db;


    $query = "select student.* from student, reportlist where reportlist.userid = '$userID' and student.studentid = reportlist.studentid order by lname ASC";
    debugPrint($query);
    $students = $db->get_results($query, ARRAY_A);
    return $students;
}

function removeStudentFromReport($students, $userID) {
    global $db;
    if ($students != "") {
        for ($i = 0; $i < count($students); $i++) {
            $studentID = $students[$i];
            $sql = "delete from reportlist where studentid='$studentID' and userid = '$userID'";
            debugPrint("Delete SQL: $sql<br>");
            $db->get_results($sql);
        }
    }
}

function addListtoReport($listid, $userid) {
    global $db;
    debugPrint("addListtoReport");

    $students = getListStudents($listid);
    $slist = explode(",", $students);
    if ($slist[0] != "") {
        removeAllfromReport($userid);
        foreach ($slist as $id) {
//			   $id = $stu->studentid;
            $asql = "insert reportlist set studentid = '$id', userid = '$userid'";
            debugPrint("Add sql: $asql<br>");
            $db->get_results($asql);
        }
    }
}

function removeAllfromReport($userid) {
    global $db;

    $dsql = "delete from reportlist where userid = '$userid'";
    debugPrint("Clear SQL: $dsql<br>");
    $db->get_results($dsql);
}

function showListNameOptional($items) {
    debugPrint("ShowListNameOptions List: " . print_r($items, true));
    foreach ($items as $item) {
        $val .= '<option value = "' . $item['listid'] . '">' . $item['listname'] . '</option>';
    }
    return $val;
}

function modifyLevelState($studentid, $subject, $level, $value, $direction) {
    global $db;

    $update = "Update studentlevel
					SET final = '$value'
					WHERE studentid = '$studentid' and
						subject = '$subject' and
						level = '$level'";
    debugPrint("MODIFY LEVEL: $update");
    $db->get_results($update);
    logEntry("Modify Level", '$directon $value', $studentid, $subject, $level, "");
}

function getOptionList($list, $sel) {

    foreach ($list as $value) {
        $val = $value['id'];
        $name = $value['name'];
        $ans .= "<option value=\"$val\"" . selected($val, $sel) . ">$name</option>";
    }
    return ($ans);
}

function getMultipleOptionList($list, $sel) {

    foreach ($list as $value) {
        $val = $value['id'];
        $name = $value['name'];
        $ans .= "<option value=\"$val\"" . $sel[$val] . ">$name</option>";
    }
    return ($ans);
}

function getOpenStudentLevels($site) {
    global $db;
    //GRADETHRESHHOLD
    $siteclase = $site == "" ? "" : "and student.site = '$site'";
    $sql = "SELECT * FROM studentlevel, student WHERE avg >= " . GRADETHRESHHOLD . " and percentcomp = '1'  and studentlevel.final = 0 and student.status = 'Active' and student.studentid = studentlevel.studentid $siteclase order by lname ASC, fname ASC";
    $results = $db->get_results($sql, ARRAY_A);
    return ($results);
}

function promoteStudents($values) {
    global $db, $currentUserName, $currentUserID;

    while (list($var, $val) = each($values)) {
        $type = strtok($var, "_");
        if ($val == 'close') {
            debugPrint("Value: var $var => $val <br>");
            $studentid = strtok("_");
            $subject = strtok("_");
            $level = strtok("_");
            $dt = date("Y-m-d");
            $tm = time();

            $sql = "Update studentlevel
							SET final='$dt'
							WHERE
									studentid = '$studentid' and
									subject = '$subject' and
									level = '$level'";
            debugPrint("Progress Level SQL: $sql");
            $db->get_results($sql);
            logEntry("Progress Level", "", $studentid, $subject, $level, "");
        } else if ($val != "" and $type == "lvl") {
            debugPrint("Value: var $var => $val <br>");
            $studentid = strtok("_");
            $subject = strtok("_");
            $level = strtok("_");
            $dt = date("Y-m-d");
            $tm = time();

            $sql = "Update studentlevel
							SET final='$dt'
							WHERE
									studentid = '$studentid' and
									subject = '$subject' and
									level = '$level'";
            debugPrint("Progress Level SQL: $sql");
            $db->get_results($sql);

            $sql = "Insert into studentlevel
							SET studentid = '$studentid',
								subject = '$subject',
								level = '$val',
								start = '$dt',
								progress='EMG',
								change_username='$currentUserName', 
								change_user='$currentUserID', 
								change_timestamp='$tm'";
            debugPrint("Start Level SQL: $sql");
            $db->get_results($sql);
            logEntry("Progress Level", "", $studentid, $subject, $level, "");
            logEntry("Start Level", "", $studentid, $subject, $val, "");
        }
    }
}

function getNextLevel($site) {
    global $db;

    $sql = "SELECT DISTINCT nextlevel.subject, nextlevel.level, nextlevel.nextlevel FROM studentlevel, nextlevel, student
				  WHERE avg >= " . GRADETHRESHHOLD . " and percentcomp = '1'  and studentlevel.final = 0
				  		and studentlevel.subject = nextlevel.subject and studentlevel.level = nextlevel.level 
				  		and student.site = '$site' and student.studentid = studentlevel.studentid order by lname ASC, fname ASC";
    debugPrint("getNextLevel SQL: $sql");
    $results = $db->get_results($sql);
    return ($results);
}

function alertAreaLevels() {
    global $db;


    $sql = "select distinct student.studentid, student.fname, student.lname, studentlevel.change_username, studentlevel.change_timestamp, studentlevel.subject, studentlevel.progress, studentlevel.level, user.userid, user.name as uname, user.email as uemail FROM studentlevel, student, listvalues, lists, user WHERE (studentlevel.progress = 'PRO' or studentlevel.progress = 'ADV')  and studentlevel.final = 0 and student.studentid = studentlevel.studentid and listvalues.studentid = student.studentid and lists.listid = listvalues.listid and user.userid = lists.userid order by lists.userid ASC, student.lname ASC, student.fname ASC";
    debugPrint("alertAreaLevels: $sql");
    $results = $db->get_results($sql);
    return ($results);
}

function alertToggles($time) {
    global $db;

    $days = 7;
    $sql = "select distinct student.studentid, student.fname, student.lname, studentlevel.change_username, studentlevel.change_timestamp, studentlevel.subject, studentlevel.progress, studentlevel.level, user.userid, user.name as uname, user.email as uemail from student, studentlevel, lists, listvalues, user, level where studentlevel.change_timestamp < ($time - ((level.delta+1)*86400)) and studentlevel.studentid = student.studentid and student.studentid = listvalues.studentid  and listvalues.listid = lists.listid and lists.userid = user.userid and studentlevel.subject = level.subject and studentlevel.level = level.level order by lists.userid ASC, student.lname ASC, student.fname ASC";
    debugPrint("alertToggle: $sql");
    $results = $db->get_results($sql);
    return ($results);
}

function emptyAlertTable() {
    global $db;

    $sql = "TRUNCATE TABLE alerts";
    $db->query($sql);
}

function defaultValue($first, $second) {
    return($first == '' || !isset($first) ? $second : $first);
}

function movestudent($studentid, $exitCode, $enterCode, $enterSite) {
    global $db, $CurrentYear, $CurrentQuarter;

    $studentInfo = getStudentInfo($studentid);
    $currentSite = $studentInfo['site'];
    $currentDate = date("Y-m-d");
    $currentGrade = $studentInfo['grade'];
    $sql = "insert into movement set
				studentid = '$studentid',
				exitcode = '$exitCode',
				exitlocation = '$currentSite',
				exitdate = '$currentDate',
				exityear = '$CurrentYear',
				exitquarter = '$CurrentQuarter',
				exitgrade = '$currentGrade',
				entercode = '$enterCode',
				enterlocation = '$enterSite',
				enterdate = '$currentDate',
				enteryear = '$CurrentYear',
				enterquarter = '$CurrentQuarter',
				entergrade = '$currentGrade',
				movementnotes = ''
			";
    $db->get_results($sql);
    $sql = "Update student
				SET
					site = '$enterSite'
				WHERE
					studentid = '$studentid'
			";
    $db->get_results($sql);
}

function saveEntry($studentid, $enterCode, $enterSite, $date, $aid, $comments="") {
    global $db, $CurrentYear, $CurrentQuarter;

    $sql = "insert into studentmovement set
				studentid = '$studentid',
				code = '$enterCode',
				site = '$enterSite',
				date = '$date',
				kind = 'enter',
				comment = '$comments'
			";
    $db->get_results($sql);
    $sql = "UPDATE student
			SET alaskaid = $aid
			WHERE studentid = '$studentid'";
    $db->get_results($sql);
}

function MySQLDate($month, $day, $year) {
    $ans = date('Y-m-d', mktime(0, 0, 0, $month, $day, $year));
    return($ans);
}

function PHPDate($format, $d) {
    $ans = date($format, mktime(0, 0, 0, substr($d, 5, 2), substr($d, 8, 2), substr($d, 0, 4)));
    return($ans);
}

function saveEnter($id, $enterCode, $enterSite, $date, $comments) {
    global $db;

    $sql = "update student set status = 'Active', site = '$enterSite' where studentid = '$id'";
    $db->get_results($sql);
    $scomments = addslashes($comments);
    $sql = "insert studentmovement set studentid = '$id', code = '$enterCode', date = '$date', comment = '$scomments', kind = 'enter', site='$enterSite'";
    $db->get_results($sql);
}

function saveExit($id, $exitCode, $site, $date, $comments) {
    global $db;

    $sql = "update student set status = 'Inactive' where studentid = '$id'";
    $db->get_results($sql);
    $scomments = addslashes($comments);
    $sql = "insert studentmovement set studentid = '$id', code = '$exitCode', date = '$date', comment = '$scomments', kind = 'exit', site='$site'";
    $db->get_results($sql);
}

function getEnterExitDates($id) {
    global $db;

    $results = $db->get_results("select * from studentmovement where studentid = '$id' order by date ASC", ARRAY_A);
    return ($results);
}

function attendanceCalCode() {
    global $db;

    $codes = $db->get_results("select * from AttendanceCodes", ARRAY_A);
    //	print_r($codes);
    $str = "<table border=1>";
    foreach ($codes as $code) {
        $color = $code['Color'] != "" ? "bgcolor=#" . $code['Color'] : "";
        $codenm = $code['Code'];
        $desc = $code['Description'];
        $str .= "<tr  $color><td>$codenm</td><td>$desc</td></tr>";
    }
    $str .="</table>";
    return ($str);
}

function exportText($text) {
    global $db, $exportDIR;

    set_time_limit(0);
    $fnname = "export_" . logonID() . ".xls";
    $fn = $exportDIR . $fnname;

    $fp = fopen($fn, 'w');

    fwrite($fp, $text);
    fclose($fp);

    header("Pragma: public");
    header('Expires: ' . gmdate('D, d M Y H:i:s') . ' GMT');
    header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
    header("Cache-Control: private", false);
    header("Content-Type: application/text");
    header('Content-Disposition: attachment; filename="' . $fnname . '"');
    header("Content-Transfer-Encoding: binary");
    header('Content-Length: ' . filesize($fn));
    @readfile($fn) OR die("<html><body OnLoad=\"javascript: alert('File not found');history.back();\" bgcolor=\"#F0F0F0\"></body></html>");

    return ($fn);
}

function exportSQL($sql) {
    global $db, $exportDIR;

    set_time_limit(0);
    $fnname = "export_" . logonID() . ".xls";
    $fn = $exportDIR . $fnname;

    $results2 = $db->get_results($sql, ARRAY_A);
    $cols2 = $db->get_col_info("name");

    $fp = fopen($fn, 'w');

    newfputcsv($fp, $cols2, "\t");
    foreach ($results2 as $ln) {
        newfputcsv($fp, $ln, "\t");
    }

    fclose($fp);

    header("Pragma: public");
    header('Expires: ' . gmdate('D, d M Y H:i:s') . ' GMT');
    header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
    header("Cache-Control: private", false);
    header("Content-Type: application/text");
    header('Content-Disposition: attachment; filename="' . $fnname . '"');
    header("Content-Transfer-Encoding: binary");
    header('Content-Length: ' . filesize($fn));
    @readfile($fn) OR die("<html><body OnLoad=\"javascript: alert('File not found');history.back();\" bgcolor=\"#F0F0F0\"></body></html>");

    return ($fn);
}

function getStudentIn($sql) {
    global $db;

    $results = $db->get_col($sql);
    $ret = NULL;
    if ($results != NULL)
        $ret = implode(",", $results);
    return $ret;
}

function quarterBetweenDates($date1, $date2) {

    global $db, $CurrentYear, $CurrentQuarter;

    $sql1 = "select year, quarter from quarters where '$date1' >= start and '$date1' <= finish";
    $sinfo = $db->get_results($sql1, ARRAY_A);
    //	print_r($sinfo);
    if (substr($date2, 0, 4) == '0000') {
        $finfo[0]['year'] = $CurrentYear;
        $finfo[0]['quarter'] = $CurrentQuarter;
    } else {
        $sql2 = "select year, quarter from quarters where '$date2' >= start and '$date2' <= finish";
        $finfo = $db->get_results($sql2, ARRAY_A);
    }
    //	echo "$sql1<br>$sql2<br>";
    //	echo (substr($finfo[0]['year'], 2, 2) * 4) . " - " . (substr($sinfo[0]['year'], 2, 2) * 4) . " + " .
    //				$finfo[0]['quarter'] . " - " .  $sinfo[0]['quarter'];

    $between = (substr($finfo[0]['year'], 2, 2) * 4) - (substr($sinfo[0]['year'], 2, 2) * 4) +
            $finfo[0]['quarter'] - + $sinfo[0]['quarter'];

    return($between + 1);
}

function SpEdStudent($id) {
    global $db;

    $value = $db->get_var("SELECT entrysped > exitdate from speddata where studentid = '$id' ");
    if ($value)
        return('Yes'); else
        return('No');
}

function cleanupInternalErrors($sid, $sub, $lvl) {
    global $db;

    $sql = "select g1.* from grades as g1, grades as g2
			WHERE g1.studentid = g2.studentid and g1.subject = g2.subject and 
					g1.std = g2.std and g1.level = g2.level and 
					g1.gradeid != g2.gradeid and 
					g1.studentid = '$sid' and g1.subject = '$sub' and g1.level = '$lvl'
					ORDER BY g1.studentid ASC, g1.subject, g1.level, g1.std, g1.value";
    $grades = $db->get_results($sql, ARRAY_A);
    $subject = '';
    $level = '';
    $std = '';
    print_r($grades);
    for ($i = 0; $i < count($grades); $i++) {
        if (($subject == $grades[$i]['subject']) and ($level == $grades[$i]['level']) and ($std == $grades[$i]['std'])) {
            $sql = "UPDATE grades SET subject = 'old{$grades[$i]['subject']}' where gradeid = '{$grades[$i]['gradeid']}' ";
            $db->get_results($sql);
        } else {
            $subject = $grades[$i]['subject'];
            $level = $grades[$i]['level'];
            $std = $grades[$i]['std'];
        }
    }
}

function writeFile($str) {
    $outfile = 'data.txt';
    $fp = fopen($outfile, 'a') or die("Error opening file $outfile");
    if (is_array($str)) {
        $str = print_r($str, true);
    } else
        $str = $str . "\n";
    fwrite($fp, $str);
}

function getSharedList($userID) {
    global $db;

    $str = "";
    $sql = "select listid, listname, kind from lists
         			where lists.userid = $userID and type = 'Private'
				union
				 select lists.listid, listname, kind from lists, listshare
				 	where lists.listid = listshare.listid and listshare.userid = $userID and type='Private'";
    $list = $db->get_results($sql, ARRAY_A);
    return $list;
}

function getListTabs($listID) {
    global $db;
    $rows = $db->get_results("SELECT grp_tab.tabid, tabname, infoid, kind, value,
				width, height FROM grp_tab,grp_info
				WHERE listid = '$listID' and grp_tab.tabid = grp_info.tabid
				ORDER BY grp_tab.ord, grp_info.ord", ARRAY_A);
    $tabs = array();
    $tabid = NULL;
    if ($rows != NULL) {
        foreach ($rows as $r) {
            if ($tabid != $r['tabid']) { // new tab
                $tabid = $r['tabid'];
                $tabs[$tabid]['name'] = $r['tabname'];
            }
            $tabs[$tabid]['subtabs'][$r['infoid']]['kind'] = $r['kind'];
            $tabs[$tabid]['subtabs'][$r['infoid']]['value'] = $r['value'];
            if ($r['kind'] == 'iframe') {
                if ($r['width'] == '0')
                    $r['width'] = '100%';
                if ($r['height'] == '0')
                    $r['height'] = '100%';
                $tabs[$tabid]['subtabs'][$r['infoid']]['width'] = $r['width'];
                $tabs[$tabid]['subtabs'][$r['infoid']]['height'] = $r['height'];
            }
        }
    }
    return $tabs;
}

function getSummaryInfo() {
    $summary = array(
        "qpi" => array(
            "description" => "Quarterly Performance Indicator",
            "label" => "QPI",
            "options" => array(
                "", "Disengaged", "Deficient", "Acceptable", "Exemplary", "Not_Instructed"
            )
        ),
        "ase" => array(
            "description" => "ASE",
            "label" => "ASE",
            "options" => array(
                "", "Eligible", "Not_Eligible"
            )
        ),
        "prog" => array(
            "description" => "PROGRESS",
            "label" => "Progress",
            "options" => array(
                "", "On Track!", "Not On Track"
            )
        )
    );
    return $summary;
}

function getSubjectLevelInfo($studentsID, $subject, $level) {
    global $db;
    $data = array();
    $students = implode(",", $studentsID);

    $query = "SELECT
		s.studentid, 
		s.fname, 
		s.lname, 
		sl.change_username, 
		sl.change_timestamp, 
		sl.progress, 
		s.site, 
		s.grade, 
		gsid AS gradetype, 
		gs.name AS gradetypename, 
		st.type, 
		st.std, 
		g.value, 
		su.name, 
		su.gradLevel, 
		su.core 
		FROM (
			student AS s, 
			studentlevel AS sl, 
			standards AS st, 
			grades AS g, 
			subjects AS su, 
			gs_select AS gss, 
			gs) 
		WHERE 
			s.studentid in ($students) AND 
			sl.studentid = s.studentid AND 
			sl.level = '$level' AND 
			sl.subject = '$subject' AND 
			sl.final = '00000000' AND 
			st.subject = sl.subject AND 
			st.level = sl.level AND 
			st.type in ('std','over') AND 
			st.std = g.std AND 
			g.subject = sl.subject AND 
			g.level = sl.level AND 
			s.studentid = g.studentid AND 
			su.id = sl.subject AND 
			gs.id = gss.gsid AND 
			s.site = gss.siteid AND 
			s.grade BETWEEN gss.lowgrade AND gss.highgrade 
		ORDER BY 
			s.lname, 
			s.studentid, 
			st.order";

    $res = $db->get_results($query, ARRAY_A);

    if ($res == NULL) { // Student with no toggles
        $query = "SELECT
			s.studentid,
			s.fname,
			s.lname,
			sl.change_username,
			sl.change_timestamp,
			sl.progress,
			s.site,
			s.grade,
			gsid AS gradetype,
			gs.name AS gradetypename,
			st.type,
			st.std,
			su.name,
			su.gradLevel,
			su.core
			FROM (
				student AS s,
				studentlevel AS sl,
				standards AS st,
				subjects AS su,
				gs_select AS gss,
				gs)
			WHERE
				s.studentid in ($students) AND
				sl.studentid = s.studentid AND
				sl.level = '$level' AND
				sl.subject = '$subject' AND
				sl.final = '00000000' AND
				st.subject = sl.subject AND
				st.level = sl.level AND
				st.type in ('std','over') AND
				su.id = sl.subject AND
				gs.id = gss.gsid AND
				s.site = gss.siteid AND
				s.grade BETWEEN gss.lowgrade AND gss.highgrade
			ORDER BY
				s.lname,
				s.studentid,
				st.order";

        $res = $db->get_results($query, ARRAY_A);
    }
    $n = count($res);

    // Get Summary Indicators: 'comment','QPI','prog','ase'
    $query = "SELECT
		g.studentid, 
		g.value, 
		lower(g.std) AS std   
		FROM (
			studentlevel AS sl, 
			student AS s, 
			grades AS g
		) 
		WHERE 
			s.studentid in ($students) AND 
			sl.studentid = g.studentid AND 
			sl.level = '$level' AND 
			sl.subject = '$subject' AND 
			sl.final = '00000000' AND 
			s.studentid = g.studentid AND 
			g.std in ('comment','QPI','prog','ase') AND 
			g.subject = sl.subject AND 
			g.level = sl.level 
		ORDER BY 
			s.lname, 
			g.studentid";

    $summary = $db->get_results($query, ARRAY_A);
    $n2 = count($summary);
    $student = NULL;
    $s = -1;
    $j = 0;
    $types = array("std" => "standards", "over" => "overall", "qpi" => "summary",
        "ase" => "summary", "prog" => "summary", "comment" => "comment");
    for ($i = 0; $i < $n; $i++) {
        $this_student = $res[$i]['studentid'];
        if ($this_student != $student) {
            $student = $this_student;
            $data[++$s] = array();
            $data[$s]['studentID'] = $student;
            $data[$s]['fname'] = $res[$i]['fname'];
            $data[$s]['lname'] = $res[$i]['lname'];
            $data[$s]['progress'] = $res[$i]['progress'];
            $data[$s]['change_username'] = $res[$i]['change_username'];
            $data[$s]['change_timestamp'] = $res[$i]['change_timestamp'];
            $data[$s]['site'] = $res[$i]['site'];
            $data[$s]['grade'] = $res[$i]['grade'];
            $data[$s]['gradetype'] = $res[$i]['gradetype'];
            $data[$s]['gradetypename'] = $res[$i]['gradetypename'];
            $data[$s]['standards'] = array();
            $data[$s]['overall'] = array();
            $data[$s]['summary'] = array();

            // Search for student in $summary
            for ($k = $j; $k < $n2; $k++) {
                if ($summary[$k]['studentid'] == $student)
                    break;
            }
            // Retrieve each summary record
            for ($j = $k; $j < $n2; $j++) {
                if ($summary[$j]['studentid'] != $student)
                    break;
                $type = $types[$summary[$j]['std']];

                $data[$s][$type][$summary[$j]['std']] = array(
                    'value' => $summary[$j]['value']
                );
            }
        }

        $type = $types[$res[$i]['type']];

        if (isset($res[$i]['value'])) {
            $data[$s][$type][$res[$i]['std']] = array(
                'value' => $res[$i]['value']
            );
        }
    }
    return $data;
}

function getSubjectStandardsArray($sub, $level) {
    global $db;
    $query = "SELECT std, description, link, shortname FROM standards WHERE subject='$sub' AND level='$level' AND type='std' ORDER BY standards.order ASC";
    $res = $db->get_results($query, ARRAY_A);
    for ($i = 0; $i < count($res); $i++) {
        $res[$i]['description'] = str_replace("'", "\'", htmlentities($res[$i]['description']));
    }
    return $res;
}

function getSubjectOverallArray($sub, $level) {
    global $db;
    $query = "SELECT std, description FROM standards WHERE subject='$sub' AND level='$level' AND type='over' ORDER BY standards.order ASC";
    $res = $db->get_results($query, ARRAY_A);
    for ($i = 0; $i < count($res); $i++) {
        $res[$i]['description'] = str_replace("'", "\'", htmlentities($res[$i]['description']));
    }
    return $res;
}

function getCoreLevels() {
    global $db;
    $query = "SELECT DISTINCT level FROM level, subjects WHERE subjects.id = level.subject AND subjects.core = 'x'  ORDER BY CAST(level AS SIGNED)";
    $res = $db->get_results($query, ARRAY_A);
    return $res;
}

function getValue($arr, $key, $default = NULL) {
    if (isset($arr[$key]) && $arr[$key] != "") {
        return $arr[$key];
    } else {
        return $default;
    }
}

function getStudentToggles($startdate, $enddate, $site='', $start = 0, $limit = 30) {
    global $db;

    $data = array();
    $res = array();
    if ($site != '') {
        $joinClause = "AND h.studentid = s.studentid";
        $siteClause = "AND s.site = '$site'";
        $tables = ", student AS s";
    } else {
        $joinClause = "";
        $siteClause = "";
        $tables = "";
    }

    $sql = "SELECT 
		COUNT(DISTINCT h.studentid) AS n 
		FROM history2 AS h $tables 
		WHERE 
			h.type = 'toggle' and
			h.timestamp > '$startdate' and
			h.timestamp < '$enddate' 
			$joinClause 
			$siteClause";

    $total = $db->get_var($sql);

    $sql = "SELECT
			CONCAT(fname, ' ', lname, ' (', s.studentid, ')') AS name, 
			CONCAT('student=', s.studentid) AS filter, 
			t.toggle, c.comments, site  
		FROM 
			history2 AS h JOIN student AS s ON h.studentid = s.studentid
			LEFT JOIN (
			SELECT 
				studentid, COUNT(history2.type) AS comments 
			FROM 
				history2 
			WHERE 
				type = 'toggle' and
				timestamp > '$startdate' and
				timestamp < '$enddate' and
				std = 'comment'
			GROUP BY 
				studentid
			) AS c 
		ON 
			c.studentid = h.studentid LEFT JOIN (
			SELECT 
				studentid, COUNT(history2.type) AS toggle 
			FROM 
				history2 
			WHERE 
				type = 'toggle' and
				timestamp > '$startdate' and
				timestamp < '$enddate' and
				std != 'comment'
			GROUP BY 
				studentid
			) AS t 
		ON 
			t.studentid = h.studentid 
		WHERE
			h.type = 'toggle' and
			h.timestamp > '$startdate' and
			h.timestamp < '$enddate' 
			$siteClause
		GROUP BY h.studentid
		ORDER BY s.site, s.lname, s.fname 
		LIMIT $start, $limit";

    $res = $db->get_results($sql, ARRAY_A);

    return array("total" => $total, "data" => $res);
}

function getTeacherToggles($startdate, $enddate, $site='', $start = 0, $limit = 30) {
    global $db;

    $data = array();
    $res = array();
    if ($site != '') {
        $joinClause = "AND h.userid = u.userid";
        $siteClause = "AND u.site = '$site'";
        $tables = ", user AS u";
    } else {
        $joinClause = "";
        $siteClause = "";
        $tables = "";
    }

    $sql = "SELECT 
		COUNT(DISTINCT h.userid) AS n 
		FROM history2 AS h $tables 
		WHERE 
			h.type = 'toggle' and
			h.timestamp > '$startdate' and
			h.timestamp < '$enddate' 
			$joinClause 
			$siteClause";

    $total = $db->get_var($sql);

    $sql = "SELECT
		u.name, t.toggle, c.comments, CONCAT('user=', u.userid) AS filter, site  
		FROM 
			history2 AS h JOIN user AS u ON h.userid = u.userid  
			LEFT JOIN (
			SELECT 
				userid, COUNT(history2.type) AS comments 
			FROM 
				history2 
			WHERE 
				type = 'toggle' and
				timestamp > '$startdate' and
				timestamp < '$enddate' and
				std = 'comment'
			GROUP BY 
				userid
			) AS c 
		ON 
			c.userid = h.userid LEFT JOIN (
			SELECT 
				userid, COUNT(history2.type) AS toggle 
			FROM 
				history2 
			WHERE 
				type = 'toggle' and
				timestamp > '$startdate' and
				timestamp < '$enddate' and
				std != 'comment'
			GROUP BY 
				userid
			) AS t 
		ON 
			t.userid = h.userid 
		WHERE
			h.type = 'toggle' and
			h.timestamp > '$startdate' and
			h.timestamp < '$enddate' 
			$siteClause
		GROUP BY h.userid
		ORDER BY u.site, u.name 
		LIMIT $start, $limit";

    $res = $db->get_results($sql, ARRAY_A);

    return array("total" => $total, "data" => $res);
}

function getDates($year, $quarter) {
    global $db;
    $sql = "select * from quarters where year = '$year' order by quarter ";
    $res = $db->get_results($sql, ARRAY_A);
    $startQ = $res[$quarter - 1]['start'];
    $endQ = $res[$quarter - 1]['finish'];
    $startY = $res[0]['start'];
    $endY = $res[3]['finish'];
    $curdate = date('Y-m-d');
    $dates = array(
        "quarter" => array($res[$quarter - 1]['start'], $res[$quarter - 1]['finish']),
        "year" => array($res[0]['start'], $res[3]['finish']),
        "day" => array($curdate, $curdate)
    );
    return $dates;
}

?>
