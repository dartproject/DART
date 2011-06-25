function onChangeValue (id, val) {
	$.get("index.php", { cmd: 'saveDB', spec: id, val: val },
	function(data){
//				alert(data);
	});	
}

function onChangeOrder (id, val, listid) {
	var page = 'index.php?cmd=showscoresEditInfo&listid='+listid+'&subcmd=reordertab&tabid='+id+'&ord='+val;
	window.location= page;
}

function onChangeInfoOrder (id, val, listid) {
	var page = 'index.php?cmd=showscoresEditInfo&listid='+listid+'&subcmd=reorderinfo&infoid='+id+'&ord='+val;
	window.location= page;
}
