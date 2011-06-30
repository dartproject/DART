$(function() {
	$('#start').datepick();
	$('#end').datepick();
});
$('#start').datepick({onSelect: reformatDate});

function reformatDate() {
	$('#startOutput').val($.datepick.formatDate(
		"@", $('#start').datepick('getDate')[0]));
}

$('#end').datepick({onSelect: reformatDateEnd});

function reformatDateEnd() {
	$('#endOutput').val($.datepick.formatDate(
		"@", $('#end').datepick('getDate')[0]));
}
