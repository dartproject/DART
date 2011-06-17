//Script for left Navigation
<!--
function swapNav(){
 var i,x,tB,j=0,tA=new Array(),arg=swapNav.arguments;
 if(document.getElementsByTagName)
	 {for(i=4;i<arg.length;i++)
		{tB=document.getElementsByTagName(arg[i]);
	  for(x=0;x<tB.length;x++)
	  {tA[j]=tB[x];j++;}
	  }
  for(i=0;i<tA.length;i++){
 	 if(tA[i].className)
 		 {if(tA[i].id==arg[1])
  			{if(arg[0]==1){
 				 tA[i].className=(tA[i].className==arg[3])?arg[2]:arg[3];}
  			else{tA[i].className=arg[2];}
 		 }else if(arg[0]==1 && arg[1]=='none') 		
				{if(tA[i].className==arg[2] || tA[i].className==arg[3])
  					{ tA[i].className=(tA[i].className==arg[3])?arg[2]:arg[3];}
   				}
  				else if(tA[i].className==arg[2])
  				{tA[i].className=arg[2];}
				}
			}
	}
}
//-->
<!--
function writeStyles(op,a){
if(op==0||document.getElementById)
	{var tS="<sty"+"le type=\"text/css\">";
		tS+=a+"<"+"/sty"+"le>";document.write(tS);document.close();}
}
writeStyles(1,'.closed ul{ display:none;}.open ul{ display:block;}');
//-->
//End Script for left navigation

//Start form assistant
function showAndFocus(div_id, field_to_focus)
{
  var the_div = getStyleObject(div_id);
  if (the_div != false)
  {
    changeObjectVisibility(div_id, "visible");
    field_to_focus.focus();
  }
}


function fillInName(first_name,middle_name,last_name)
{

  document.myform.cname.value = 
		first_name + " " +middle_name + " " + last_name;

  changeObjectVisibility("nameDiv","hidden");  
}

function fillInDate()
{
  var month_select = document.date_fields.month;
  var month = month_select.options[month_select.selectedIndex].value;

  var day_select = document.date_fields.day;
  var day = day_select.options[day_select.selectedIndex].value;

  var year_select = document.date_fields.year;
  var year = year_select.options[year_select.selectedIndex].value;

  document.myform.date.value = 
		month + " " + day + ", " + year;

  changeObjectVisibility("dateDiv","hidden");
}

function hideAll()
{
  changeObjectVisibility("dateDiv","hidden");
  changeObjectVisibility("nameDiv","hidden");
}
//End form assistant

//Start DOM Clone of table rows with elements
fcount = 1;
function addRowClone(tblId)
{
  var tblBody = document.getElementById(tblId).tBodies[0];
  var newNode = tblBody.rows[0].cloneNode(true);

//append number to each id
	newNode.id = tblId + fcount;
	newNode.name = tblId + fcount;
	
	
	addNumberToAttribute('input',newNode);
	addNumberToAttribute('select',newNode);
	//insert new cloned, incremented elements into page	
	tblBody.appendChild(newNode);
	
	//increment field count
	fcount++; 
	return false;
}

function addNumberToAttribute(element, newNode){ 
		elementList = newNode.getElementsByTagName(element);
		for (i = 0; i < elementList.length; i++){
			numberAttribute(elementList[i], fcount);
		}
}
//add number to each cloned form field's id
function numberAttribute(currentNode, numToUse) {
		var name = currentNode.getAttribute('name');
		if((currentNode.nodeType == 1) && name){
//				var currentId = name + "_a";
//				currentNode.setAttribute('name', (currentId + numToUse )) ;
				currentNode.value = '';
		}
		  

}

function removeRowClone(divNum)
{
//alert('here');
var d = document.getElementById('phoneClone');
var lastRow = d.rows.length;
//alert('here1' + d);
//var olddiv = document.getElementById(divNum);
//alert('here2' + olddiv);
//if (lastRow > 2) tbl.deleteRow(lastRow - 1);
d.deleteRow(divNum);
//alert('here3');
}
