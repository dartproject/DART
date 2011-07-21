function setCheckboxes(the_form, do_check)
{
    var elts      = (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
                  ? document.forms[the_form].elements['studentID[]']
                  : (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
          ? document.forms[the_form].elements['studentID[]']
          : document.forms[the_form].elements['studentID[]'];
    var elts_cnt  = (typeof(elts.length) != 'undefined')
                  ? elts.length
                  : 0;

    if (elts_cnt) {
        for (var i = 0; i < elts_cnt; i++) {
            elts[i].checked = do_check;
        } // end for
    } else {
        elts.checked        = do_check;
    } // end if... else

    return true;
} // end of the 'setCheckboxes()' function

function checkChecks () {
    var elts = document.forms[0].elements['studentID[]'];
	if(typeof(elts != 'undefined')) {
		if(elts instanceof NodeList) { // Array
    		var elts_cnt = elts.length;
    		for (var i = 0; i < elts_cnt; i++) {
        		if(elts[i].checked) {
            		return true;
				}
			}
        } else { // One element
			if(elts.checked) {
				return true;
			}
		}
    }
    alert ('There are no students checked.');
    return false;
}

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
	/*
	var month = document.getElementsByName("month")[0].value; 
	var day = document.getElementsByName("day")[0].value; 
	var year = document.getElementsByName("year")[0].value; 
	*/

	Ext.QuickTips.init();
    
	// setup the state provider, all state information will be saved to a cookie
	Ext.state.Manager.setProvider(Ext.create('Ext.state.CookieProvider'));

	// Select fields from studentFields in view/Student.js
	var fields = getMyValues(studentFields, [
		"StudentID",
		"Name",
		"Site",
	]);
	// Select columns from studentColumns in view/Student.js
	var columns = getMyValues(studentColumns, [
		"StudentID-Checkbox",
		"Name",
		"StudentID",
		"Site"
	]);

	// This information could also be retrieved from the DB
	var categories = ["Absent", "Late", "ISS", "Suspended", "Present"];
	for(i = 0; i < categories.length; ++i) {
		columns.push({
			text: categories[i],
			width: 83,
			sortable : true,
			dataIndex: categories[i]
		});
		fields.push({
			name: categories[i],
			type: 'float'
		});
	}

	// Create Model
	Ext.define('AttendanceDrillDownModel', {
		extend: 'Ext.data.Model',
		fields: fields,
		idProperty: 'studentid'
	});

	var proxy = new Ext.data.proxy.Ajax({
		url : 'index.php',
		reader: {
			type: 'json',
			root: 'rows',
			totalProperty: 'totalCount'
		},
		simpleSortMode: true,
		extraParams: {
			cmd     : "ajax",
			url     : "getAttendanceDrillDown_2.php",
			type    : params.type,
			site    : params.site,
			quarter : params.quarter,
			cdate   : params.cdate,
			year    : params.year,
		}
	});

	// create the data store
	var store = Ext.create('Ext.data.Store', {
		model: 'AttendanceDrillDownModel',
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
				var checkbox = document.forms['selectionForm'].elements['studentID[]'];
				if(checkbox instanceof NodeList)
					checkbox[index].checked = true;
				else
					checkbox.checked = true;
			},
			deselect: function(sm, record, index) {
				var checkbox = document.forms['selectionForm'].elements['studentID[]'];
				if(checkbox instanceof NodeList)
					checkbox[index].checked = false;
				else
					checkbox.checked = false;
			},
			selectionchange: function(sm, records, options) { // When all records are selected or deselected at once, the previous events are not triggered
				var checkbox = document.forms['fieldsForm'].elements['studentID[]'];
				var new_value = false;
				if(sm.store.data.length == records.length) { // All records selected
					new_value = true;
				} else if(records.length == 0) { // No records selected
					new_value = false;
				} else return;
				if(checkbox instanceof NodeList) {
					for(var i = 0; i < sm.store.data.length; i++) {
						checkbox[i].checked = new_value;
					}
				} else {
					checkbox.checked = new_value;
				}
			}
		}
	});

	bbar.bindStore(store);

	var grid = Ext.create('Ext.grid.Panel', {
		store: store,
		selModel: sm, // For checkbox model
		stateful: true,
		stateId: 'attendanceDrillDownGrid',
		columns: columns,
		height: 500,
		width: 800,
		resizable: true,
		resizeHandles: 'se',
		renderTo: 'attendanceDrillDown',
		iconCls: 'icon-grid',
		// paging bar on the bottom
		bbar: bbar,
		viewConfig: {
			stripeRows: true
		}
	});
	store.loadPage(1);
});
