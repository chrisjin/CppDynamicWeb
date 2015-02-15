function sAlert(str) {


    if (document.getElementById("msgDiv") != null)
        return;

    var msgw, msgh, bordercolor;
    msgw = 400; //提示窗口的宽度
    msgh = 100; //提示窗口的高度
    titleheight = 25 //提示窗口标题高度
    bordercolor = ""; //"#336699"; //提示窗口的边框颜色
    titlecolor = "#00b6ff"; //提示窗口的标题颜色

    var sWidth, sHeight;
    sWidth = document.body.offsetWidth;
    sHeight = screen.height;

    //<div style="width:302px; height:97px;background:url(reg_bg.gif);filter:progid:DXImageTransform.Microsoft.Alpha(startX=20,startY=20,finishX=100,finishY=100,style=1,opacity=75,finishOpacity=100); opacity:0.75;cursor:pointer;"></div>
    var bgObj = document.createElement("div");
    bgObj.setAttribute('id', 'bgDiv');
    bgObj.style.position = "absolute";
    bgObj.style.top = "0";
    bgObj.style.background = "#000";
    bgObj.style.filter = "progid:DXImageTransform.Microsoft.Alpha(style=3,opacity=25,finishOpacity=75";
    bgObj.style.opacity = "0.6";
    bgObj.style.left = "0";
    bgObj.style.width = sWidth + "px";
    bgObj.style.height = sHeight + "px";
    bgObj.style.zIndex = "10000";
    document.body.appendChild(bgObj);

    //	 <div style="width: 400px; overflow: hiddendisplay:block; background: url(reg_bg_03.jpg) repeat-y 50% top;       filter: progid:DXImageTransform.Microsoft.Alpha(startX=20,startY=20,finishX=100,finishY=100,style=1,opacity=75,finishOpacity=100);      opacity: 0.75; cursor: pointer;">
    var msgObj = document.createElement("div");
    msgObj.setAttribute("id", "msgDiv");
    msgObj.setAttribute("align", "center");
    msgObj.style.background = "url(../images/tishi_bg.jpg) repeat-y 50% top";
    msgObj.style.border = "0px solid " + bordercolor;
    msgObj.style.position = "absolute";
    msgObj.style.left = "50%";
    msgObj.style.top = "50%";
    msgObj.style.font = "14px/1.6em Verdana, Geneva, Arial, Helvetica, sans-serif";
    msgObj.style.color = "#00b6ff";
    msgObj.style.marginLeft = "-210px";
    msgObj.style.marginTop = -75 + document.documentElement.scrollTop + "px";
    msgObj.style.width = msgw + "px";
    msgObj.style.height = "auto"; // msgh + "px";
    msgObj.style.textAlign = "left";
    msgObj.style.lineHeight = "19px";
    msgObj.style.zIndex = "10001";
    msgObj.style.border = "1px #666666 solid";
//    
//msgObj1.style.padding="15px 10px";
//	msgObj1.style.minHeight="20px";
//	msgObj1.style.wordBreak="break-all";


    //<div style="background: url(reg_bg_01.jpg) no-repeat 50% top;">
    var msgObj1 = document.createElement("div");
    msgObj1.setAttribute("id", "msgDiv1");
    msgObj1.setAttribute("align", "right");
    msgObj1.style.background = "url(../images/tishi_bg.jpg) no-repeat 50% top";
    msgObj1.style.margin = "0";
    msgObj1.style.padding = "0px";
    msgObj1.style.height = "5px";
    msgObj1.style.cursor = "pointer";



    var msgObj2 = document.createElement("div");
    msgObj2.setAttribute("id", "msgDiv2");
    msgObj2.style.background = "url(../images/tishi_bg.jpg) no-repeat 50% bottom";
    msgObj2.style.margin = "0";
    msgObj2.style.padding = "15px";
    msgObj2.style.height = "5px";




    //{width:426px;height:39px;color:#00b6ff;font-size:14px;font-weight:bold}
    var title = document.createElement("h1");
    title.setAttribute("id", "msgTitle");
    title.setAttribute("align", "right");
    title.style.margin = "0";
    title.style.padding = "0px";
    //    title.style.background = bordercolor;
    title.style.height = "18px"
    //      title.style.color = "white";
    title.style.cursor = "pointer";
    title.innerHTML = "<a href='#' style='display: block; position: absolute; top: 7px; right: 7px;'><img src=\"../images/dacha.gif\" width=\"16\" height=\"16\" /></a>";
    title.onclick = function() {
        document.body.removeChild(bgObj);
        document.getElementById("msgDiv").removeChild(title);
        document.getElementById("msgDiv").removeChild(msgObj1);
        document.getElementById("msgDiv").removeChild(msgObj2);
        document.body.removeChild(msgObj);

    }
    document.body.appendChild(msgObj);

    document.getElementById("msgDiv").appendChild(msgObj1);

    document.getElementById("msgDiv").appendChild(title);


    var txt = document.createElement("p");
    txt.style.margin = "1em 10"
    txt.setAttribute("id", "msgTxt");
    txt.innerHTML = str;

    document.getElementById("msgDiv").appendChild(txt);
    document.getElementById("msgDiv").appendChild(msgObj2);



    function keyListener(e) {
        e = e ? e : event;

        if (e.keyCode == 13 || e.keyCode == 32 || e.keyCode == 0) {
            document.body.removeChild(bgObj);
            document.getElementById("msgDiv").removeChild(title);
            document.getElementById("msgDiv").removeChild(msgObj1);
            document.getElementById("msgDiv").removeChild(msgObj2);

            document.body.removeChild(msgObj);

        }
    }

    document.onkeydown = keyListener;
}