
////////////////////////////////////////////////////
var EnableFullAuto	= true; // set this to true and all of your flash objects will be fixed automatically
var SWFFormFixDebug = false; // set this to true to be alerted whenever a flash object is found and fixed
var NotLoadedWarning = true; // set this to true to alert the users when they try to access a function from
							 // the ExternalInterface() that isn't loaded yet
var NotLoadedMsg = "Please wait for the page to load..."; // this is the warning they will see
////////////////////////////////////////////////////

finished = false; // this is set to true when the body's onload is called, to stop the script
timeout = 10; // seconds to wait before giving up
starttime = new Date().getTime();
flashObjectList = Array();
fixedList = Array();
makeFuncArr = Array();
SWFFormFixAuto2 = function(){
//alert("running...");
	if(navigator.appName.toLowerCase() != "microsoft internet explorer")return true;
	var flashObjectList = document.getElementsByTagName("object");
	for(var i=0;i<flashObjectList.length;i++){
		var obj = flashObjectList[i];
		if(obj.getAttribute('classid') == "clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"){
			var id = obj.getAttribute('id');
			var alreadyfixed = false;
			for(var c=0;c<fixedList.length;c++){if(fixedList[i] == id)alreadyfixed=true;}
			if(!alreadyfixed){
				var debugtxt = '';
				for(var b in window[id]){
					if(typeof(window[id][b])=="function"){
						makeFuncArr.push(Array(obj,b));
						obj[b] = function(){
							if(NotLoadedWarning)alert(NotLoadedMsg);
							return("");
						}

					}
				}
				window[id]=obj;
				if(SWFFormFixDebug)alert("Fixed: "+id);
			}
		}
	}
	if(!finished){
		setTimeout("SWFFormFixAuto2()", 100);
	}else{
		for(var i=0;i<makeFuncArr.length;i++){
			// this is executed after the page is loaded - it rebuilds the custom
			// ExternalInterface() functions
			SWFFormFix_rebuildExtFunc(makeFuncArr[i][0],makeFuncArr[i][1]);
		}
	}
	return true;
}
SWFFormFix_rebuildExtFunc = function(obj,functionName){
	eval('obj[functionName] = function(){return eval(this.CallFunction("<invoke name=\\"'+functionName+'\\" returntype=\\"javascript\\">" + __flash__argumentsToXML(arguments,0) + "</invoke>"));}');
	if(SWFFormFixDebug)alert("Rebuilt ExternalInterface() function: "+functionName);
}
SWFFormFixOnloadAppend = function() {
	var oldonload = window.onload;
	if (typeof window.onload != 'function') {
		window.onload = function(){
			finished=true;
		}
	} else {
		window.onload = function() {
			oldonload();
			finished=true;
		}
	}
}
SWFFormFixAuto = function(){
	if(navigator.appName.toLowerCase() != "microsoft internet explorer")return true;
	var objects = document.getElementsByTagName("object");
	if(objects.length == 0) return true;
	for(i=0;i<objects.length;i++){
		// here's all the objects on the page, now lets find the flash objects
		if(objects[i].classid == "clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"){
			// this is a flash movie, apply the fix
			window[objects[i].id] = objects[i];
		}
	}
	var out = "";
	return true;
}
SWFFormFix = function(swfname){
	if(navigator.appName.toLowerCase() != "microsoft internet explorer")return false;
	var testnodename = "SWFFormFixTESTER";
	document.write('<div id="'+testnodename+'" onclick="SWFFormFixCallback(this,\''+swfname+'\');return false;" style="display:none">&nbsp;</div>');
	document.getElementById(testnodename).onclick();
}
SWFFormFixCallback = function (obj,swfname){
	var path = document;
	var error = false;
	var testnode = obj;
	while(obj = obj.parentNode){
		if(obj.nodeName.toLowerCase() == "form"){
			if(obj.name != undefined && obj.name != null && obj.name.length > 0){
				path = path.forms[obj.name];
			}else{
				alert("Error: one of your forms does not have a name!");
				error = true;
			}
		}
	}
	testnode.parentNode.removeChild(testnode);
	if(error) return false;
	window[swfname]=path[swfname];
	return true;
}
function noCacheIE(url){
	var isIE = navigator.appName.indexOf("Microsoft") != -1;
	if(!isIE)return(url);
	var newUrl = '?';
	if(url.indexOf('?') != -1)newUrl = '&';
	var now = new Date();
	var rand = Math.random().toString().substring(2,4);
	newUrl = url+newUrl+"noCacheIE="+rand+'-'+now.getTime().toString();
	return(newUrl);
}
if(EnableFullAuto){
	SWFFormFixAuto2();
	SWFFormFixOnloadAppend();
}