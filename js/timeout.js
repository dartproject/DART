
//Timeout
var countDownInterval=3600;
var countDownTime=countDownInterval+1;



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
        document.getElementById("countDownText").innerHTML=countDownTime+" "
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


