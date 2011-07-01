$(function() {
	$('#startdate').datepick();
	$('#enddate').datepick();
});
$('#startdate').datepick({onSelect: reformatDate});

function reformatDate() {
	$('#startOutput').val($.datepick.formatDate(
		"yyyy-mm-dd", $('#startdate').datepick('getDate')[0]));
}

$('#enddate').datepick({onSelect: reformatDateEnd});

function reformatDateEnd() {
	$('#endOutput').val($.datepick.formatDate(
		"yyyy-mm-dd", $('#enddate').datepick('getDate')[0]));
}
