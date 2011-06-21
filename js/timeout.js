
//Timeout
var countDownInterval=3600;
var countDownTime=countDownInterval+1;

function popUp2(URL, x, y) {
  	self.name = "listings"; // names current window as "listings"
	newwindow = window.open(URL, 'name', 'toolbar=1,scrollbars=1,location=1,statusbar=0,menubar=0,resizable=1,width=' + x + ',height=' + y + ',left=376,top=135');
	if(window.focus) {newwindow.focus()}
  }

function confirmMsg(msg)
{
  inbox = confirm(msg);
  return(inbox);
}

function logout(skip){
	window.location = 'index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out."';
}

function go2(skip){
	if(skip == false) {
		alert ("You will be automatically logged out in 2 minutes if you don't save data or refresh screen");
		window.refresh();
	}
	window.setTimeout("go2(false)", 2400 * 1000); // 1000 is for every min or 1 sec
	window.setTimeout("logout(false)", countDownInterval * 1000); // 1000 is for every min or 1 sec
}

go2(true);

function countDown(){
    countDownTime--;
    if (countDownTime <=0){
        countDownTime=countDownInterval;
        clearTimeout(counter)
        //window.location="index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.";
        return
    }
    if (document.all) //if IE 4+
        document.all.countDownText.innerText = countDownTime+" ";
    else if (document.getElementById) //else if NS6+
        document.getElementById("countDownText").innerHTML='Timing out in <b id="countDownText">'+countDownTime+' </b> seconds';
    else if (document.layers){ //CHANGE TEXT BELOW TO YOUR OWN
        document.c_reload.document.c_reload2.document.write('Timing out in <b id="countDownText">'+countDownTime+' </b> seconds')
        document.c_reload.document.c_reload2.document.close()
    }
    counter=setTimeout("countDown()", 1000);
}

function startit(){
    if (document.all||document.getElementById) //CHANGE TEXT BELOW TO YOUR OWN
        document.write('Timing out in <b id="countDownText">'+countDownTime+' </b> seconds')
    countDown()
}

if (document.all||document.getElementById)
    startit()
else
    window.onload=startit
//setTimeout("location.href='index.php?cmd=expired&msg=Idle time exceed. You have been automatically logged out.'" , t)

