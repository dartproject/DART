function turnOn(id) {
	$('.unhidden').addClass('hidden');
	$('.hidden').removeClass('unhidden');
	$("#tab"+id).addClass('unhidden');
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
	var listName = document.getElementsByName("listName")[0].value; 

	Ext.QuickTips.init();
    
	// setup the state provider, all state information will be saved to a cookie
	Ext.state.Manager.setProvider(Ext.create('Ext.state.CookieProvider'));

	// Get initial data
	Ext.define('Header', {
		extend: 'Ext.data.Model',
		fields: [
		{
			name: 'id',
			type: 'string'
		},
		{
			name: 'name',
			type: 'string'
		}
		]
	});
	var aux_store = Ext.create('Ext.data.Store', {
		model: 'Header',
		proxy: {
			type: 'ajax',
			url : 'index.php',
			reader: {
				type:'json',
				root:'headers'
			}
		},
		autoLoad: false
	});

	aux_store.load({
		params: {
			cmd     : "ajax",
			url     : "getShowScoresHeaders.php"
		},
		callback: function(records, options, success){
			// Select columns from studentColumns in view/Student.js
			var columns = getMyValues(studentColumns, [
				"Name"
				]);

			// Select fields from studentFields in view/Student.js
			var fields = getMyValues(studentFields, [
				"StudentID",
				"Name"
				]);
			
			Ext.Array.each(records, function(row) {
				// Custom columns: Subjects
				columns.push({
					text: row.data.id,
					width: 50,
					sortable : true,
					renderer: function(value, p, record) {
						return Ext.String.format(
							'<a href="?cmd=toggle&p1={0}&p2={1}&p3={2}">{2}</a>',
							params.p1,
							row.data.id,
							record.data['level_' + row.data.id]
							);
					},
					dataIndex: 'level_' + row.data.id + '_order'
				});
				// Custom fields: Subjects
				fields.push({
					name: 'level_' + row.data.id + '_order',
					type: 'string'
				});
				fields.push({
					name: 'level_' + row.data.id,
					type: 'string'
				});
			});
			// Custom fields: Electives
			fields.push({
				name: 'electives',
				type: 'string'
			});
			fields.push({
				name: 'electives_level',
				type: 'string'
			});
			// Custom columns: Subjects
			columns.push({
				text: 'EL',
				width: 130,
				sortable : false,
				renderer: function(value, p, record) {
					var text = "";
					if(value != "") {
						var electives = value.split(",");
						var levels = record.data.electives_level.split(",");
						for(var i = 0; i < electives.length; i++) {
							text += Ext.String.format(
								'<a href="?cmd=toggle&p1={0}&p2={1}&p3={2}">{1}.{2}</a> ',
								params.p1,
								electives[i],
								levels[i]
							);
						}
					}
					return text;
				},
				dataIndex: 'electives'
			});

			// Action icons
			var actions = getMyValues(studentActions, ["StudentEdit"]);
			columns.push({
				xtype: 'actioncolumn',
				width: 50,
				items: actions
			});

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
					url     : "getShowScores.php",
					listID  : params.p1
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
			bbar.bindStore(store);
		
			var grid = Ext.create('Ext.grid.Panel', {
				title: listName + ' Profile',
				store: store,
				stateful: true,
				stateId: 'showScoresGrid',
				columns: columns,
				height: 500,
				width: 800,
				resizable: true,
				renderTo: 'tabhome',
				// paging bar on the bottom
				bbar: bbar,
				viewConfig: {
					stripeRows: true
				}
			});	
			store.loadPage(1);
		}
	});
});
