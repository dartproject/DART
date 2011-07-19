// Hidden variables (ToDo: find a better way to access these variables)
var imageURL = document.getElementsByName("imageURL").length == 0? '' : document.getElementsByName("imageURL")[0].value;  


// Render functions
function renderDate(value, p, record) {
	if(value == null) // Date in wrong format
		return "";
	else
		return Ext.Date.dateFormat(value, 'm-d-Y');
}

function renderDateTime(value, p, record) {
	if(value == null)
		return "";
	else
	return Ext.Date.dateFormat(value, 'm-d-Y H:i:s');
}

// You can select columns for grid from this list
var disciplineColumns =  [
{	
	id: "Kind",
	value:
	{
		text     : 'Type',
		sortable : true,
		dataIndex: 'kind'
	}
},
{	
	id: "Creation",
	value:
	{
		text     : 'Creation Date',
		sortable : true,
		width    : 150,
		renderer : renderDateTime, 
		dataIndex: 'creation'
	}
},
{	
	id: "IncidentDate",
	value:
	{
		text     : 'Incident Date',
		sortable : true,
		renderer : renderDate, 
		dataIndex: 'incidentdate'
	}
},
{	
	id: "Status",
	value:
	{
		text     : 'Status',
		sortable : true,
		dataIndex: 'status'
	}
}
];

// You can select actions for the action column of your grid from this list
var disciplineActions = [
{
	id: "DisciplineEdit",
	value: {
		icon   : imageURL + 'icons/user_edit_16.png',
		tooltip: 'Edit',
		handler: function(grid, rowIndex, colIndex) {
			var rec = grid.store.getAt(rowIndex);
			window.location.href = Ext.String.format("?cmd=disciplineEdit&disciplineid={0}",
				rec.getId());
		}
	}
}
];

// You can select fields for your model from this list
var disciplineFields =  [
{
	id: "DisciplineId",
	value: {
		name: 'disciplineid',
		type: 'int'
	}
},
{
	id: "Kind",
	value: {
		name: 'kind',
		type: 'string'
	}
},
{
	id: "Creation",
	value: {
		name: 'creation',
		type: 'date'
	}
},
{
	id: "IncidentDate",
	value: {
		name: 'incidentdate',
		type: 'date'
	}
},
{
	id: "Status",
	value: {
		name: 'status',
		type: 'string'
	}
},
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
	'Incidents per Page: ',
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
