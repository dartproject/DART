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
        minLength: 2
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
}(jQuery));

