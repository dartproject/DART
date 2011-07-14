function setCheckboxes(the_form, do_check) {
	var elts      = (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')? 
	document.forms[the_form].elements['studentID[]']
	:
	(typeof(document.forms[the_form].elements['studentID[]']) != 'undefined') ?
	document.forms[the_form].elements['studentID[]']
	:
	document.forms[the_form].elements['studentID[]'];
	var elts_cnt  = (typeof(elts.length) != 'undefined')? 
	elts.length : 0;

	if (elts_cnt) {
		for (var i = 0; i < elts_cnt; i++) {
			elts[i].checked = do_check;
		} // end for
	} else {
		elts.checked = do_check;
	} // end if... else

	return true;
} // end of the 'setCheckboxes()' function

function checkChecks () {
	var elts = document.forms['fieldsForm'].elements['studentID[]'];
	var elts_cnt = elts.length;
	for (var i = 0; i < elts_cnt; i++) {
		if(elts[i].checked == true) {
			return true;
		}
	} 
	alert ('There are no students checked.');
	return false;
}

function showCalendar() {
	selectedDate = $('#date').datepick('getDate')[0];
	
	form = document.getElementById("selectDateForm");
	form.month.selectedIndex = $.datepick.formatDate("m", selectedDate);
	form.day.selectedIndex = $.datepick.formatDate("d", selectedDate);
	form.year.value = $.datepick.formatDate("yyyy", selectedDate);
}

$('#date').datepick({
	showOnFocus: false,
	showTrigger: '#calImg',
	onSelect:showCalendar
});

/* Load Table */
Ext.require([
	'Ext.grid.*',
	'Ext.data.*',
	'Ext.util.*',
	'Ext.toolbar.Paging',
	'Ext.ModelManager',
	'Ext.tip.QuickTipManager',
	'Ext.state.*',
	'Ext.selection.CheckboxModel'
	]);

Ext.onReady(function() {

	// GET Variables
	var params = Ext.Object.fromQueryString(location.search.substring(1));

	// Hidden variables
	var month = document.getElementsByName("month")[0].value; 
	var day = document.getElementsByName("day")[0].value; 
	var year = document.getElementsByName("year")[0].value; 
	var periodName = document.getElementsByName("periodName")[0].value; 
	var imageURL = document.getElementsByName("imageURL")[0].value; 

	Ext.QuickTips.init();
    
	// setup the state provider, all state information will be saved to a cookie
	Ext.state.Manager.setProvider(Ext.create('Ext.state.CookieProvider'));

	var proxy = new Ext.data.proxy.Ajax({
		url : 'index.php',
		reader: {
			type: 'json',
			root: 'students',
			totalProperty: 'totalCount'
		},
		simpleSortMode: true,
		extraParams: {
			cmd     : "ajax",
			url     : "getAttendanceList.php",
			listID  : params.listid,
			month   : month,
			day     : day,
			year    : year,
			period  : params.period
		}
	});

	// create the data store
	Ext.define('StudentAttendance', {
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
		proxy: proxy,
		idProperty: 'studentid'
	});

	var store = Ext.create('Ext.data.Store', {
		model: 'StudentAttendance',
		pageSize : 30,
		remoteSort: true,
		sorters: [{
			property: 'name',
			direction: 'DESC'
		}]
	});

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

	// Create the Grid
	var pluginExpanded = true;
	var sm = Ext.create('Ext.selection.CheckboxModel', {
		// Mirror checkbox behavior
		listeners: {
			select: function(sm, record, index) {
				var checkbox = document.forms['fieldsForm'].elements['studentID[]'];
				checkbox[index].checked = true;
			},
			deselect: function(sm, record, index) {
				var checkbox = document.forms['fieldsForm'].elements['studentID[]'];
				checkbox[index].checked = false;
			}
		}
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
				store.loadPage(1);
			}
		}
	});
	// Paging toolbar, including the field to change page size
	var bbar = new Ext.PagingToolbar({
		store: store,
		displayInfo: true,
		items: [
		'-',
		'Per Page: ',
		pageSize
		],
	});
	var grid = Ext.create('Ext.grid.Panel', {
		title: 'Attendance Date: ' + month + '/' + day + '/' + year + ' -  Period: ' + periodName,
		store: store,
		selModel: sm, // For checkbox model
		stateful: true,
		stateId: 'stateGrid',
		columns: [
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
		],
		height: 500,
		width: 800,
		resizable: true,
		renderTo: 'attendanceList',
		iconCls: 'icon-grid',
		// paging bar on the bottom
		bbar: bbar,
		viewConfig: {
			stripeRows: true
		}
	});
	store.loadPage(1);
});