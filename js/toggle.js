function changeValue(name,newval) {
	obj = document.getElementsByName("ch_" + name)[0];
	obj.value = newval;
}

function handleSelection(value) {
	toggle = document.getElementsByName("toggle")[0];
	if (value == "#save_changes") {
		toggle.loc.value = location.href;
		toggle.submit();
	} else {
		window.location=value;
	}
}
