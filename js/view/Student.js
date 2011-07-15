// Hidden variables (ToDo: find a better way to access these variables)
var CurrentYear = document.getElementsByName("CurrentYear").length == 0 ? '' : document.getElementsByName("CurrentYear")[0].value; 
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

var studentColumns =  [
	{
		id: "StudentID-checkbox",
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
		id: "TestingGrade",
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
		id: "Age",
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

var StudentActions = [
	{
		icon   : imageURL + 'icons/report_16.png',
		tooltip: 'Attendance',
		handler: function(grid, rowIndex, colIndex) {
			var rec = grid.store.getAt(rowIndex);
			window.location.href = Ext.String.format("?cmd=AttendanceCalendar&student={0}&year={1}",
				rec.getId(), CurrentYear);
		}
	}, {
		icon   : imageURL + 'icons/user_edit_16.png',
		tooltip: 'Advanced Edit',
		handler: function(grid, rowIndex, colIndex) {
			var rec = grid.store.getAt(rowIndex);
			window.location.href = Ext.String.format("?cmd=advEdit&id={0}",
				rec.getId());
		}
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

function getMyColumns(ids) {
	columns = new Array();
	for(var i = 0; i < ids.length; ++i) {
		for(var j = 0; j < studentColumns.length; ++j) {
			if(ids[i] == studentColumns[j].id) {
				columns.push(studentColumns[j].value);
			}
		}
	}
	return columns;
}
