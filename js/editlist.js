function confirm_delete(id) {
	input_box=confirm("Click OK to delete or Cancel");
	if (input_box==true) { 
		window.location="index.php?cmd=deletelist&p1=" + id;
		return false;
	} else {
		return false;
	}
}
function studentSelected(selectId) {
	add = document.getElementById("add");
	remove = document.getElementById("remove");
	if(selectId == "removeselect") {
		add_disabled = true;
		remove_disabled = false;
		otherSelectId = "addselect"; 
	} else if(selectId == "addselect") {
		add_disabled = false;
		remove_disabled = true;
		otherSelectID = "removeselect"; 
	} else return;
	add.disabled = add_disabled;
	remove.disabled = remove_disabled;
	document.getDocumentById(otherSelectID).selectedIndex=-1;
}
