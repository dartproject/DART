function setCheckboxes(the_form, do_check) {
	var elts      = (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')? 
		document.forms[the_form].elements['studentID[]'] 
		: 
		(typeof(document.forms[the_form].elements['studentID[]']) != 'undefined') ? 
			document.forms[the_form].elements['studentID[]']
			: 
			document.forms[the_form].elements['studentID[]'];
	var elts_cnt  = (typeof(elts.length) != 'undefined')? 
				elts.length : 0;

	if (elts_cnt) {
		for (var i = 0; i < elts_cnt; i++) {
			elts[i].checked = do_check;
		} // end for
	} else {
		elts.checked = do_check;
	} // end if... else

	return true;
} // end of the 'setCheckboxes()' function

function checkChecks () {
	var elts = document.forms['fieldsForm'].elements['studentID[]'];
	var elts_cnt = elts.length;
	for (var i = 0; i < elts_cnt; i++) {
		if(elts[i].checked == true) { return true; }
	} 
	alert ('There are no students checked.' + elts_cnt);
	return false;
}

function nextSubmit() { document.nextForm.submit(); }

function prevSubmit() { document.prevForm.submit(); }

function showCalendar() {
	selectedDate = $('#date').datepick('getDate')[0];
	
	form = document.getElementById("selectDateForm");
	form.month.selectedIndex = $.datepick.formatDate("m", selectedDate);
	form.day.selectedIndex = $.datepick.formatDate("d", selectedDate);
	form.year.value = $.datepick.formatDate("yyyy", selectedDate);
}

$('#date').datepick({showOnFocus: false, showTrigger: '#calImg', onSelect:showCalendar});
