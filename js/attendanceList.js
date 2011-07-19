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

$(document).ready(function(){
    $( "input:submit", "#content" ).button();
    
    $('#page_help').click(function (e) {
        $('#page_modal_help').modal();

        return false;
    });
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

	Ext.QuickTips.init();
    
	// setup the state provider, all state information will be saved to a cookie
	Ext.state.Manager.setProvider(Ext.create('Ext.state.CookieProvider'));

	// Select fields from studentFields in view/Student.js
	var fields = getMyValues(studentFields, [
		"StudentID",
		"Name",
		"AlaskaID",
		"Site",
		"TestingGrade",
		"TestingGrade-Order",
		"Age",
		"Age-Order",
		"AttendanceCode"
	]);
	// Create Model
	Ext.define('StudentModel', {
		extend: 'Ext.data.Model',
		fields: fields,
		idProperty: 'studentid'
	});

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
	var store = Ext.create('Ext.data.Store', {
		model: 'StudentModel',
		pageSize : 30,
		proxy: proxy,
		autoLoad: false,
		remoteSort: true,
		sorters: [{
			property: 'name',
			direction: 'DESC'
		}]
	});

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

	bbar.bindStore(store);

	// Select columns from studentColumns in view/Student.js
	var columns = getMyValues(studentColumns, [
		"StudentID-Checkbox-Site",
		"Name",
		"StudentID",
		"AlaskaID",
		"Site",
		"TestingGrade-Order",
		"Age-Order",
		"AttendanceCode"
	]);
	// Action icons
	var actions = getMyValues(studentActions, [
		"AttendanceCalendar",
		"AdvancedEdit"
	]);
	columns.push({
		xtype: 'actioncolumn',
		width: 80,
		items: actions
	});
	var grid = Ext.create('Ext.grid.Panel', {
		title: 'Attendance Date: ' + month + '/' + day + '/' + year + ' -  Period: ' + periodName,
		store: store,
		selModel: sm, // For checkbox model
		stateful: true,
		stateId: 'attendanceListGrid',
		columns: columns,
		height: 500,
		width: 800,
		resizable: true,
		resizeHandles: 'se',
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
