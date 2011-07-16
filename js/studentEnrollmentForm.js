/* 
 *  Copyright (C) 2011 Bolek Kurowski (bkurowsk@andrew.cmu.edu)
 * 
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

Ext.require([
    'Ext.form.*',
    'Ext.layout.container.Column',
    'Ext.tab.Panel',
    'Ext.tip.QuickTipManager',
    'Ext.data.*'
    ]);


/*!
 * Ext JS Library 3.3.1
 * Copyright(c) 2006-2010 Sencha Inc.
 * GNU GPL license v3.
 * http://www.sencha.com/license
 */
Ext.onReady(function(){

    Ext.QuickTips.init();

    Ext.define('Sites',{
        extend: 'Ext.data.Model',
        fields:[
        {
            name: 'siteid', 
            type: 'string'
        },

        {
            name: 'name', 
            type:'string'
        }
        ]
    })

    Ext.define('TransferTypes',{
        extend: 'Ext.data.Model',
        fields:[
        {
            name: 'id', 
            type: 'int'
        },

        {
            name: 'name', 
            type:'string'
        }
        ]
    })
    
    var form = Ext.get('enrollForm');

    Ext.create('Ext.form.Panel', {
        url:'sendEnrollmentForm.php',
        renderTo: form,
        frame:true,
        title: 'Enroll New Student',
        bodyStyle:'padding:5px 5px 0',
        width: 450,
        fieldDefaults: {
            msgTarget: 'side',
            labelAlign: 'top'
        },
        defaultType: 'textfield',
        defaults: {
            anchor: '100%'
        },
        items: [{
            xtype: 'container',
            anchor: '100%',
            layout: 'column',
            items:[{
                xtype: 'container',
                columnWidth: .5,
                layout: 'anchor',
                items: [{
                    xtype:'textfield',
                    fieldLabel: 'First Name',
                    name: 'First_Name',
                    allowBlank:false,
                    emptyText: 'First Name',
                    anchor:'98%'
                }]
            },{
                xtype: 'container',
                columnWidth: .5,
                layout: 'anchor',
                items: [{             
                    xtype: 'textfield',    
                    fieldLabel: 'Last Name',
                    name: 'Last_Name',
                    allowBlank:false,
                    emptyText: 'Last Name',
                    anchor: '100%'
                }]
            }]
        },{
            fieldLabel: 'Address 1',
            emptyText: 'Address 1',
            name: 'Address1',
            allowBlank:false
        },{
            fieldLabel: 'Address 2',
            emptyText: 'Address 2',
            name: 'Address2'
        },{
            xtype: 'container',
            anchor: '100%',
            layout: 'column',
            items:[{
                xtype: 'container',            
                columnWidth: .4,
                layout: 'anchor',
                items: [{
                    fieldLabel: 'City',    
                    xtype:'textfield',
                    emptyText: 'City',
                    name: 'City',
                    allowBlank:false,
                    anchor: '98%'
                }]
            },{
                xtype: 'container',            
                columnWidth: .4,
                layout: 'anchor',
                items: [{
                    fieldLabel: 'State/Province',
                    xtype: 'textfield',
                    emptyText: 'State/Province',
                    name: 'State/Province',
                    allowBlank:false,
                    anchor: '98%'
                }]
            },{
                xtype: 'container',            
                columnWidth: .2,
                layout: 'anchor',
                items: [{
                    fieldLabel: 'ZIP code',
                    xtype: 'textfield',
                    emptyText: 'Zip Code',
                    name: 'ZIP_Code',
                    allowBlank:false,
                    anchor:'100%'
                }]
            }]
        },{ 
            fieldLabel: 'Home Phone number',
            emptyText: 'Home Phone',
            name: 'Home_Phone',
            allowBlank:false
        },{
            xtype: 'container',
            anchor: '100%',
            layout: 'column',
            items:[{
                xtype: 'container',
                columnWidth: .25,
                layout: 'anchor',
                items: [{
                    xtype:'datefield',
                    fieldLabel: 'Entry date',
                    emptyText: 'Entry Date',
                    name: 'Entry_Date',
                    allowBlank:false,
                    anchor:'98%'
                }]
            },{
                xtype: 'container',
                columnWidth: .75,
                layout: 'anchor',
                items: [{             
                    xtype: 'combobox',
                    fieldLabel: 'Entry type',
                    name: 'Entry_Type',
                    anchor: '100%',
                    editable: false,
                    store: Ext.create('Ext.data.Store', {
                        model: 'TransferTypes',
                        proxy: {
                            type: 'ajax',
                            url : 'config/dict/entryTypes.json',
                            reader: 'json'
                        },
                        autoLoad: true
                    }),
                    valuefield: 'id',
                    displayField: 'name',
                    emptyText: 'Select entry type...'
                }]
            }]
        },{
            xtype: 'combobox',
            fieldLabel: 'From school',
            name: 'Entry_Type',
            anchor: '100%',
            queryMode: 'local', 
            store: Ext.create('Ext.data.Store', {
                model: 'Sites',
                proxy: {
                    type: 'ajax',
                    url : 'index.php?cmd=ajax&url=lib/ajaxData/getSiteList.php',
                    reader: 'json'
                },
                autoLoad: true
            }),
            valuefield: 'name',
            displayField: 'name',
            emptyText: 'Select entry type...'
        
        },{
            fieldLabel: 'Additional transfer details and comments',
            xtype: 'htmleditor',            
            name: 'Additional_Comments',
            height: 200,
            anchor: '100%'
        }],
        buttons: [{
            text: 'Send',
            handler: function() {
                this.up('form').getForm().submit({
                    url: 'sendEnrollmentForm.php',
                    submitEmptyText: false,
                    waitMsg: 'Sending form...',
                    success: function(form,action){
                        Ext.MessageBox.alert(action.result.title, action.result.msg);
                    },
                    failure: function(form,action){
                        Ext.MessageBox.alert('Error', 
                            'Unable to send form. Please contact administration.');
                    }
                });
            }
        },{
            text: 'Reset',
            handler: function(){
                this.up('form').getForm().reset();
            }
        }]
    });

});