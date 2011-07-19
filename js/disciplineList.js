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

	Ext.QuickTips.init();
    
	// setup the state provider, all state information will be saved to a cookie
	Ext.state.Manager.setProvider(Ext.create('Ext.state.CookieProvider'));

	// Select fields from disciplineFields in view/Student.js
	var fields = getMyValues(disciplineFields, [
		"DisciplineId",
		"Kind",
		"Creation",
		"IncidentDate",
		"Status"
	]);
	// Create Model
	Ext.define('DisciplineListModel', {
		extend: 'Ext.data.Model',
		fields: fields,
		idProperty: 'disciplineid'
	});

	var proxy = new Ext.data.proxy.Ajax({
		url : 'index.php',
		reader: {
			type: 'json',
			root: 'incidents',
			totalProperty: 'totalCount'
		},
		simpleSortMode: true,
		extraParams: {
			cmd      : "ajax",
			url      : "getDisciplineList.php",
			studentid: params.studentid,
			year     : params.year
		}
	});

	// create the data store
	var store = Ext.create('Ext.data.Store', {
		model: 'DisciplineListModel',
		pageSize : 30,
		proxy: proxy,
		autoLoad: false,
		remoteSort: true,
		sorters: [{
			property: 'creation',
			direction: 'ASC'
		}]
	});

	// Create the Grid
	var pluginExpanded = true;

	bbar.bindStore(store);

	// Select columns from disciplineColumns in view/Student.js
	var columns = getMyValues(disciplineColumns, [
		"Kind",
		"Creation",
		"IncidentDate",
		"Status",
		"DisciplineId"
	]);
	// Action icons
	var actions = getMyValues(disciplineActions, [
		"DisciplineEdit"
	]);
	columns.push({
		xtype: 'actioncolumn',
		width: 80,
		items: actions
	});
	var grid = Ext.create('Ext.grid.Panel', {
		store: store,
		stateful: true,
		stateId: 'disciplineListGrid',
		columns: columns,
		height: 500,
		width: 550,
		resizable: true,
		resizeHandles: 'se',
		renderTo: 'disciplineList',
		iconCls: 'icon-grid',
		// paging bar on the bottom
		bbar: bbar,
		viewConfig: {
			stripeRows: true
		}
	});
	store.loadPage(1);
});
