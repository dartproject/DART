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


function setCheckboxes(the_form, do_check)
{
    var elts = (typeof(document.forms[the_form].elements['studentID[]']) != 'undefined')
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
    var elts = document.forms['fieldsForm'].elements['studentID[]'];
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

function nextSubmit() {
    document.nextForm.submit();
}

function prevSubmit() {
    document.prevForm.submit();
}

$(document).ready(function(){
    $( "input:submit, button", "#content" ).button();
});
