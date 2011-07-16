// Hidden variables (ToDo: find a better way to access these variables)
var CurrentYear = document.getElementsByName("CurrentYear").length == 0 ? '' : document.getElementsByName("CurrentYear")[0].value; 
var imageURL = document.getElementsByName("imageURL").length == 0? '' : document.getElementsByName("imageURL")[0].value;  

// Render functions
function renderCheckbox(value, p, record) {
	return Ext.String.format(
		'<div style="display:none"><input type="checkbox" name="studentID[]" value="{0} {1}" class="radio"></div>',
		record.data.studentid,
		record.data.site
	);
}
function renderAction(value, p, record) {
	return Ext.String.format(
		'<a href="index.php?cmd=AttendanceCalendar&student={0}&year={1}"><img alt="Attendance" src="' + imageURL + 'icons/report_16.png" title="Attendance" style="padding:2px; vertical-align: middle" /></a>&nbsp;<a href="?cmd=advEdit&id={0}"><img alt="Advanced Edit" src="' + imageURL + 'icons/user_edit_16.png" title="Advanced Edit" style="padding:2px; vertical-align: middle" /></a>',
		value,
		CurrentYear
	);
}
function renderName(value, p, record) {
	return Ext.String.format(
		'<a href="?cmd=toggleStudent&p1={0}">{1}</a>',
		record.data.studentid,
		value
	);
}
function renderEdit(value, p, record) {
	return Ext.String.format(
		'&gt;&gt;<a href="?cmd=advEdit&id={0}">Edit</a>',
		value
	);
}
function renderAge(value, p, record) {
	return Ext.String.format(
		'{0}',
		record.data.age
	);
}
function renderGrade(value, p, record) {
	return Ext.String.format(
		'{0}',
		record.data.grade
	);
}

// You can select columns for grid from this list
var studentColumns =  [
{
	id: "StudentID-Checkbox",
	value:
	{
		width     : 5,
		sortable : false,
		renderer : renderCheckbox,
		hidden   : true,
		dataIndex: 'studentid'
	}
},
{	
	id: "Name",
	value:
	{
		text     : 'Name',
		width    : 150,
		sortable : true,
		renderer : renderName,
		dataIndex: 'name'
	}
},
{	
	id: "StudentID",
	value:
	{
		text     : 'Student Number',
		sortable : true,
		dataIndex: 'studentid'
	}
},
{	
	id: "AlaskaID",
	value:
	{
		text     : 'AK Student ID',
		sortable : true,
		dataIndex: 'alaskaid'
	}
},
{	
	id: "Site",
	value:
	{
		text     : 'School Site',
		sortable : true,
		width    : 90,
		dataIndex: 'site'
	}
},
{	
	id: "TestingGrade-Order",
	value:
	{
		text     : 'Testing Grade',
		renderer : renderGrade,
		sortable : true,
		width    : 90,
		dataIndex: 'grade_order'
	}
},
{	
	id: "Age-Order",
	value:
	{
		text     : 'Age',
		renderer : renderAge,
		sortable : true,
		width    : 90,
		dataIndex: 'age_order'
	}
},
{	
	id: "AttendanceCode",
	value:
	{
		text     : 'Code',
		width    : 60,
		sortable : true,
		dataIndex: 'Code'
	}
}
];

// You can select actions for the action column of your grid from this list
var studentActions = [
{
	id: "AttendanceCalendar",
	value: {
		icon   : imageURL + 'icons/report_16.png',
		tooltip: 'Attendance',
		handler: function(grid, rowIndex, colIndex) {
			var rec = grid.store.getAt(rowIndex);
			window.location.href = Ext.String.format("?cmd=AttendanceCalendar&student={0}&year={1}",
				rec.getId(), CurrentYear);
		}
	}
},
{
	id: "AdvancedEdit",
	value: {
		icon   : imageURL + 'icons/user_edit_16.png',
		tooltip: 'Advanced Edit',
		handler: function(grid, rowIndex, colIndex) {
			var rec = grid.store.getAt(rowIndex);
			window.location.href = Ext.String.format("?cmd=advEdit&id={0}",
				rec.getId());
		}
	}
},
{
	id: "StudentEdit",
	value: {
		icon   : imageURL + 'icons/user_edit_16.png',
		tooltip: 'Edit Student Information',
		handler: function(grid, rowIndex, colIndex) {
			var rec = grid.store.getAt(rowIndex);
			window.location.href = Ext.String.format("?cmd=StudentEdit&id={0}",
				rec.getId());
		}
	}
}
];

// You can select fields for your model from this list
var studentFields =  [
{
	id: "StudentID",
	value: {
		name: 'studentid',
		type: 'int'
	}
},
{
	id: "Name",
	value: {
		name: 'name',
		type: 'string'
	}
},
{
	id: "AlaskaID",
	value: {
		name: 'alaskaid',
		type: 'int'
	}
},
{
	id: "Site",
	value: {
		name: 'site',
		type: 'string'
	}
},
{
	id: "TestingGrade-Order",
	value: {
		name: 'grade_order',
		type: 'string'
	}
},
{
	id: "TestingGrade",
	value: {
		name: 'grade',
		type: 'string'
	}
},
{
	id: "Age-Order",
	value: {
		name: 'age_order',
		type: 'int'
	}
},
{
	id: "Age",
	value: {
		name: 'age',
		type: 'string'
	}
},
{
	id: "AttendanceCode",
	value: {
		name: 'Code',
		type: 'string'
	}
}
];

// Field to change the number of records displayed by page
var pageSize = new Ext.form.field.Number({
	anchor: '100%',
	width: 60,
	name: 'pageSize',
	value: 30,
	minValue: 1,
	listeners: {
		change: function(field, newValue, oldValue) {
			if(newValue == null) {
				return false;
			}
			bbar.store.pageSize = newValue;
			bbar.store.loadPage(1);
		}
	}
});
// Paging toolbar, including the field to change page size
var bbar = new Ext.PagingToolbar({
	displayInfo: true,
	items: [
	'-',
	'Students per Page: ',
	pageSize
	]
});

function getMyValues(list, ids) {
	result = new Array();
	for(var i = 0; i < ids.length; ++i) {
		for(var j = 0; j < list.length; ++j) {
			if(ids[i] == list[j].id) {
				result.push(list[j].value);
			}
		}
	}
	return result;
}
