/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function SubmitType(value) {
    doreports.action = "index.php?cmd=transcriptsDefine&type=" + value;
    //     alert(value + "---" + doreports.action);
    doreports.submit();
}

function AddList () {
    var val = doreports.selectGroup.value;
    doreports.action = "index.php?cmd=transcriptsDefine&type=add&listid=" + val;
    //     alert("Here" + val);
    doreports.submit();
}
