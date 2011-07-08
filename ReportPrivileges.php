<?php

 class ReportPrivileges {

	private $links;
	private $names;
	private $idEqual;
	private $siteEqual;
	private $studentID;
	private $edit;
	private $CurrentYear;

	public function  __construct($idEqual, $siteEqual, $studentID, $edit, $CurrentYear) {
		$this->idEqual = $idEqual;
		$this->siteEqual = $siteEqual;
		$this->studentID = $studentID;
		$this->edit = $edit;
		$this->CurrentYear = $CurrentYear;

		$this->links = array();
		$this->names = array();

		if(viewReport($this->idEqual, $this->siteEqual, Privilege(A4)) and $this->edit) {
			$this->links[] = "index.php?cmd=repcurrentcreate&id=$this->studentID";
			$this->names[] = "Create Current Report";

			$this->links[] = "index.php?cmd=studentInfo&id=$this->studentID";
			$this->names[] = "Student Information";

			$this->links[] = "index.php?cmd=StudentEdit&id=$this->studentID";
			$this->names[] = "Edit Student Information";
		}
		if(viewReport($this->idEqual, $this->siteEqual, Privilege(A18))) {
			$this->links[] = "index.php?cmd=sreport&id=$this->studentID";
			$this->names[] = "Report Cover - no QPI";

			$this->links[] = "index.php?cmd=sreport&id=$this->studentID&qpi=on";
			$this->names[] = "Report Cover - with QPI";
		}
		if(viewReport($this->idEqual, $this->siteEqual, Privilege(A20))) {
			$this->links[] = "index.php?cmd=graduation_report&student_id=$this->studentID";
			$this->names[] = "Graduation Progress Report";

			$this->links[] = "index.php?cmd=progressReport&id=$this->studentID";
			$this->names[] = "Standards Progress Details";
		}
		if(viewReport($this->idEqual, $this->siteEqual, Privilege(A22))) {
			$this->links[] = "index.php?cmd=pacingReport&id=$this->studentID";
			$this->names[] = "Pacing Report";
		}
		if($this->edit) {
			$this->links[] = "index.php?cmd=AttendanceCalendar&student=$studentID&year=$CurrentYear";
			$this->names[] = "Attendance";
		}
		if(viewReport($this->idEqual, $this->siteEqual, Privilege(A21)) and $this->edit) {
			$this->links[] = "index.php?cmd=disciplineList&studentid=$this->studentID&year=$this->CurrentYear";
			$this->names[] = "Discipline List";
		}
		if(viewReport($this->idEqual, $this->siteEqual, Privilege(A23)) and $this->edit) {
			$this->links[] = "index.php?cmd=MovementView&studentid=$this->studentID";
			$this->names[] = "View Student Movement";
		}
		if(viewReport($this->idEqual, $this->siteEqual, PrivilegeB(B9)) and $this->edit) {
			$this->links[] = "index.php?cmd=StudentTranscriptEdit&id=$this->studentID";
			$this->names[] = "Additional Transcript Info";
		}
	}

	public function getLinks() {
		return $this->links;
	}

	public function getNames() {
		return $this->names;
	}

        
        
}

?>
