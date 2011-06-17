<?php

include_once("lib/function_export.inc");
//echo "HERE". $_GET['s'];

$uval = array_unique($_GET['s']);
$studentlist = implode(",", $uval);
$type = $_GET['type'];

//echo "TYPE: $type";
  switch($type) {
    case "group":
        $lid = handleGroup($uval, $currentUserID, $action);
        echo("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"1; URL=index.php?cmd=editlist&p1=$lid\"> ");
        break;
    case "ExportAll":
		$sql = "select 	
					student.studentid as studentid,
					status as Dart_Status,
					Sped_Status,
					Site,
					lname as Last_Name,
					fname as First_Name,
					mname as Middle_Name,
					gender,
					bday,
					(CURDATE() - bday) as age,
					grade,
					alaskaid,
					GoalViewID,
					dc as D_Code,
					pcode as P_Code,
					pcode_old as P_Code_Old,
					percent,
					entrysped,
					iepstart,
					iepend,
					psyreeval as Last_Psy_Eval,
					splangreeval as Last_SpL_Eval,
					Last_OT_Eval,
					Last_PT_Eval,
					Other_Eval,
					Other_Eval_Date,
					Current_ESER,
					ESER_plus3,
					Latest_Consent,
					45_Days,
					Reason_Code,
					SpEd_Exit_Date,
					SpEd_Exit_Code,
					IEPLessAge3,
					Trans_Plan,
					ISS,
					OSS,
					MD_Held,
					Test_AC,
					Mod_HSGQE,
					Alt_Assmt,
					Int_Needs,
					RS_Sp,
					RS_FM,
					RS_GM,
					RS_Coun,
					RS_Tran,
					RS_Other,
					H_Aid,
					spedcomments 
				from student 
				Left join speddata on speddata.studentid = student.studentid 
				where student.studentid in ($studentlist) ";
		exportSQL($sql);
		break;
    case "ExportFallOasis":
        exportFallOasis($uval);
        break;
    case "ExportAttendance":
    	exportAttendanceCount($uval, $start, $end);
        break;
    case "ExportDiscipline":
		exportDiscipline($uval, $start, $end);
        break;
    case "EnterExit":
		exportEnterExit($uval, $start, $end);
        break;
    case "ExportSummerOasis":
		exportSummerOasis($uval, $start, $end);
        break;
    case "ExportAttendance":
		exportAllAttendance($uval, $start, $end);
        break;

    case "ExportSpringOasis":
    	echo "TBD";
        break;
    case "ExportAccommodations":
    	echo "TBD";
        break;

    default:
        echo "Bad call for type in handleSpedGroup.inc: $type";
        break;
   }

?>