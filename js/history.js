$(function() {
	$('#startdate').datepick();
	$('#enddate').datepick();
});
$('#startdate').datepick({onSelect: reformatDate});

function reformatDate() {
	$('#startOutput').val($.datepick.formatDate(
		"@", $('#startdate').datepick('getDate')[0]));
}

$('#enddate').datepick({onSelect: reformatDateEnd});

function reformatDateEnd() {
	$('#endOutput').val($.datepick.formatDate(
		"@", $('#enddate').datepick('getDate')[0]));
}
