
function popUp2(URL, x, y) {
    self.name = "listings"; // names current window as "listings"
    newwindow = window.open(URL, 'name', 'toolbar=1,scrollbars=1,location=1,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
    if(window.focus) {
        newwindow.focus()
        }
}

function confirmMsg(msg)
{
    inbox = confirm(msg);
    return(inbox);
}

function logout(skip){
    window.location = 'index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.';
}

function go2(skip){
    if(skip == false) {
        alert ("You will be automatically logged out in 2 minutes if you don't save data or refresh screen");
        window.refresh();
    }
    window.setTimeout("go2(false)", 2400 * 1000); // 1000 is for every min or 1 sec
    window.setTimeout("logout(false)", 3600 * 1000); // 1000 is for every min or 1 sec
}

go2(true);

var countDownInterval=360000;
var countDownTime=countDownInterval+1;

function countDown(){
    countDownTime--;
    if (countDownTime <=0){
        countDownTime=countDownInterval;
        clearTimeout(counter)
        //window.location="index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.";
        return
    }
     if (document.getElementById){} //else if NS6+
//        document.getElementById("countDownText").innerHTML='Timing out in <b>'+countDownTime+' </b> seconds';
    
    counter=setTimeout("countDown()", 1000);
}

if (document.all||document.getElementById){
    countDown();
}
else{
    window.onload=countDown();
    
}
    

