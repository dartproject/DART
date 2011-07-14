// Hidden variables
var imageURL = document.getElementsByName("imageURL")[0].value; 

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
		2010
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

var studentColumns =  [
	{
		width     : 5,
		sortable : false,
		renderer : renderCheckbox,
		hidden   : true,
		dataIndex: 'studentid'
	},
	{
		text     : 'Name',
		width    : 150,
		sortable : true,
		renderer : renderName,
		dataIndex: 'name'
	},
	{
		text     : 'Student Number',
		sortable : true,
		dataIndex: 'studentid'
	},
	{
		text     : 'AK Student ID',
		sortable : true,
		dataIndex: 'alaskaid'
	},
	{
		text     : 'School Site',
		sortable : true,
		width    : 90,
		dataIndex: 'site'
	},
	{
		text     : 'Testing Grade',
		renderer : renderGrade,
		sortable : true,
		width    : 90,
		dataIndex: 'grade_order'
	},
	{
		text     : 'Age',
		renderer : renderAge,
		sortable : true,
		width    : 90,
		dataIndex: 'age_order'
	},
	{
		text     : 'Code',
		width    : 60,
		sortable : true,
		dataIndex: 'Code'
	},
	{
		text     : 'Action',
		flex     : 1,
		renderer: renderAction,
		sortable : false,
		dataIndex: 'studentid'
	}
];
Ext.define('StudentModel', {
	extend: 'Ext.data.Model',
	fields: [
	{
		name: 'studentid',
		type: 'int'
	},
	{
		name: 'name',
		type: 'string'
	},
	{
		name: 'alaskaid',
		type: 'int'
	},
	{
		name: 'site',
		type: 'string'
	},
	{
		name: 'grade',
		type: 'string'
	},
	{
		name: 'age',
		type: 'string'
	},
	{
		name: 'Code',
		type: 'string'
	}
	],
	idProperty: 'studentid'
});

// Field to change the number of records displayed by page
var pageSize = new Ext.form.field.Number({
	anchor: '100%',
	width: 60,
	name: 'pageSize',
	value: 30,
	minValue: 0,
	listeners: {
		change: function(field, value) {
			bbar.store.pageSize = parseInt(value, 10);
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
	],
});
