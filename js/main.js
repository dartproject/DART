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


(function($) {
            
    $("#quickSearch").autocomplete({
        source: "quickSearch.php",
        minLength: 3,
        select: function(event, ui) {
            $('#qs_StudentID').val(ui.item.studentID);
            $('#qs_navDIV').css('display','none');
            var studentID = $("#qs_StudentID").val();
            $('#qs_navDIV').load('studentNavLinks.php', 'studentID='+studentID, function(response){
                if(response){
                    $('#qs_navDIV').css('display','');
                }else{
                    $('#qs_navDIV').css('display','none');
                }
            });
        }
    });
    
    
    $('#quickSearch').change(function(){
        if($('#quickSearch').val()==''){
            $('#qs_StudentID').val='';
            $('#qs_navDIV').css('display','none');  
        } 
    });
    
    $.fn.extend({
        sticky: function() {
            var header = $(this),
            origTop = header.offset().top,
            content = header.add("#container");
            content = header.add("#header");

            $(window).scroll(function(e) {
                if ($(this).scrollTop() > 5) {
                    content.addClass("sticky");
                    
                } else if ($(this).scrollTop() < origTop) {
                    content.removeClass("sticky");
                }
            });
        }
    });

    $(function() {
        $('#menu').sticky();
    });
    
//Courtesy of Eric Hynds
//http://www.erichynds.com/jquery/a-new-and-improved-jquery-idle-timeout-plugin/

   

}(jQuery));

// setup the dialog
$("#dialog").dialog({
    autoOpen: false,
    modal: true,
    width: 400,
    height: 200,
    closeOnEscape: false,
    draggable: false,
    resizable: false,
    buttons: {
        'Yes, Keep Working': function(){
            $(this).dialog('close');
        },
        'No, Logoff': function(){
            // fire whatever the configured onTimeout callback is.
            // using .call(this) keeps the default behavior of "this" being the warning
            // element (the dialog in this case) inside the callback.
            $.idleTimeout.options.onTimeout.call(this);
        }
    }
});

// cache a reference to the countdown element so we don't have to query the DOM for it on each ping.
var $countdown = $("#dialog-countdown");

//
var $idleTime = $("#timeout");


function formatTime(time){
    var min = Math.floor(time/60000);
    var sec = Math.floor((time-min*60000)/1000);
          
    return min +'min '+sec+'s';
}

// start the idle timer plugin
$.idleTimeout('#dialog', 'div.ui-dialog-buttonpane button:first', {
    idleAfter: 1200,
    pollingInterval: 60,
    warningLength: 120,
    keepAliveURL: 'keepalive.php',
    serverResponseEquals: 'OK',
    onTimeout: function(){
        window.location = "index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.";
    },
    onIdle: function(){
        $(this).dialog("open");
    },
    onCountdown: function(counter){
        $countdown.html(counter); // update the counter
    },
    getIdleTime: function(idleCounter){
        $idleTime.html(formatTime(idleCounter));
    }
});


