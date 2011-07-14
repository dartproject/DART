<?php

 class ListMembers {

	private $id;
	private $db;

	public function  __construct($db, $sql, $studentClause, $userid) {
		$this->id = uniqid(substr($userid, 0, 12)); // In case length($userid) > 12
		$this->db = $db;
		$from_pos = stripos($sql, " from ");
		$tail = substr($sql, $from_pos);
		$this->db->get_results("INSERT INTO list_members_tmp(process_id, studentid) (SELECT '$this->id', $studentClause $tail)");
	}

	public function getId() {
		return $this->id;
	}

	public function  __destruct() {
		$this->db->get_results("DELETE FROM list_members_tmp WHERE process_id = '$this->id'");
	}
}

?>