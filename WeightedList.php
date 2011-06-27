<?php

class WeightedList {
	private $list;
	private $students;
	private $classes;
	private $subjects;
	private $grades;

	public function  __construct($students, $classes, $subjects, $grades) {
		$this->list = array();
		$this->students = $students;
		$this->classes = $classes;
		$this->subjects = $subjects;
		$this->grades = $grades;
	}

	public function getList() {
		$wlist2 = array();
		for ($i = 0; $i < count($this->students); $i++) {
			$studentID = $this->students[$i]['studentid'];
			foreach ($this->subjects as $s) {
				$sub = $s['id'];
				$lvl = $this->classes[$studentID][$sub];
				$sublvls = getSubjectStandards ($sub, $lvl);
				foreach ($sublvls as $sublvl) {
					$std = $sublvl['std'];
					$stdw = strlen($std) == 1 ? "0" . $std : $std;
					$key = $sub . "_" . $lvl . "_" . $std;
					$value = $this->grades[$studentID][$sub][$lvl][$std];
					$wlist2[$key]['std'] = $std;
					$wlist2[$key]['subject'] = $sub;
					$wlist2[$key]['level'] = $lvl;
					$wlist2[$key]['link'] = $sublvl['link'];
					$wlist2[$key]['shortname'] = $sublvl['shortname'];
					$wlist2[$key]['count']++; /* Not used */
					$wlist2[$key]['sum'] += getToggleValue($value);
					$wlist2[$key]['comp'] = $wlist2[$key]['sum']/$stdcount;
					$wlist2[$key]['sort'] = $sub . "_" . $lvl . "_" . $stdw;
				}
			}
		}
		$wlist = array_unique2($wlist2);
		$wlist = array_sort($wlist, 'comp');
		$wnum = min(30, count($wlist));
		$buckets = 4;
		$start = 0;
		$end = $wnum-1+$start;
		$t = $wlist[$start]['comp'];
		$b = $wlist[$end]['comp'];
		$spread = ($t - $b)/$buckets;
		$wlist = array_slice($wlist, 0, $wnum);
		$wlist = array_sort($wlist, 'sort');

		for ($i = $start; $i <= $end; $i++) {
			$val = $wlist[$i]['comp'];
			$sid = $wlist[$i]['subject'] . $wlist[$i]['level'] . "." . $wlist[$i]['std'];
			if($spread == 0) {
				$tmpnum = 0;
			}
			else {
				$tmpnum = floor(($val - $b)/$spread);
			}
			$loc = $buckets - min($buckets-1, $tmpnum);
			$this->list[$i] = array();
			$this->list[$i]['link'] = $wlist[$i]['link'];
			$this->list[$i]['class'] = "t$loc";
			//$this->list[$i]['class'] = "t".rand(1,4);
			$this->list[$i]['span'] = $sid."-".$wlist[$i]['shortname'];
		}
		return $this->list;
	}
}
?>
