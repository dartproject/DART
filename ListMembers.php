<?php

class ListMembers {

	private $id;
	private $db;
	private $n;

	public function  __construct($db, $listID, $userid) {
		$this->id = uniqid(substr($userid, 0, 12)); // In case length($userid) > 12
		$this->db = $db;

		$list = $this->db->get_results("select lists.kind, lists.sql from lists where listid = '$listID' ", ARRAY_A);
		if ($list[0]['kind'] == 'search') {
			$sql = $list[0]['sql'];
			$studentClause = "student.studentid";
		} else {
			$sql = "select studentid from listvalues where listid = '$listID'";
			$studentClause = "listvalues.studentid";
		}
		$from_pos = stripos($sql, " from ");
		$tail = substr($sql, $from_pos);
		$this->n = $this->db->query("INSERT INTO list_members_tmp(process_id, studentid) (SELECT '$this->id', $studentClause $tail)");
	}

	public function getId() {
		return $this->id;
	}

	public function count() {
		return $this->n;
	}

	public function  __destruct() {
		$this->db->get_results("DELETE FROM list_members_tmp WHERE process_id = '$this->id'");
	}
}

?>
