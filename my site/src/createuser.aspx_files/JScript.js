function Trim(str) {
    return str.replace(/\s+/g, '');
}
function Email_reg(email) {
    var reg = /^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/;
    if (!reg.test(email)) { return true; }
    return false;
}
function isChinaIDCard(num) {
    if (num == 111111111111111)
        return false;
    num = num.toUpperCase();
    //身份证号码为15位或者18位，15位时全为数字，18位前17位为数字，最后一位是校验位，可能为数字或字符X。   
    if (!(/(^\d{15}$)|(^\d{17}([0-9]|X)$)/.test(num))) {
        return false;
    }

    //校验位按照ISO 7064:1983.MOD 11-2的规定生成，X可以认为是数字10。
    //下面分别分析出生日期和校验位
    if (idcard_getAge(num) <= 0) {
        return false;
    }
    var len, re;
    len = num.length;
    if (len == 15) {
        re = new RegExp(/^(\d{6})(\d{2})(\d{2})(\d{2})(\d{3})$/);
        var arrSplit = num.match(re);

        //检查生日日期是否正确 
        var dtmBirth = new Date('19' + arrSplit[2] + '/' + arrSplit[3] + '/' + arrSplit[4]);
        var bGoodDay;
        bGoodDay = (dtmBirth.getYear() == Number(arrSplit[2])) && ((dtmBirth.getMonth() + 1) == Number(arrSplit[3])) && (dtmBirth.getDate() == Number(arrSplit[4]));
        if (!bGoodDay) {
            return false;
        }
        else {
            //将15位身份证转成18位 
            //校验位按照ISO 7064:1983.MOD 11-2的规定生成，X可以认为是数字10。 
            var arrInt = new Array(7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2);
            var arrCh = new Array('1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2');
            var nTemp = 0, i;
            num = num.substr(0, 6) + '19' + num.substr(6, num.length - 6);
            for (i = 0; i < 17; i++) {
                nTemp += num.substr(i, 1) * arrInt[i];
            }
            num += arrCh[nTemp % 11];
            return true;
        }
    }
    if (len == 18) {
        re = new RegExp(/^(\d{6})(\d{4})(\d{2})(\d{2})(\d{3})([0-9]|X)$/);
        var arrSplit = num.match(re);

        //检查生日日期是否正确 
        var dtmBirth = new Date(arrSplit[2] + "/" + arrSplit[3] + "/" + arrSplit[4]);
        var bGoodDay;
        bGoodDay = (dtmBirth.getFullYear() == Number(arrSplit[2])) && ((dtmBirth.getMonth() + 1) == Number(arrSplit[3])) && (dtmBirth.getDate() == Number(arrSplit[4]));
        if (!bGoodDay) {
            return false;
        }
        else {
            //检验18位身份证的校验码是否正确。 
            //校验位按照ISO 7064:1983.MOD 11-2的规定生成，X可以认为是数字10。 
            var valnum;
            var arrInt = new Array(7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2);
            var arrCh = new Array('1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2');
            var nTemp = 0, i;
            for (i = 0; i < 17; i++) {
                nTemp += num.substr(i, 1) * arrInt[i];
            }
            valnum = arrCh[nTemp % 11];
            if (valnum != num.substr(17, 1)) {
                return false;
            }
            return true;
        }
    }
    return false;
}
function isValidDate(iY, iM, iD) {
    var a = new Date(iY, iM, iD);
    var y = a.getFullYear();
    var m = a.getMonth();
    var d = a.getDate();
    if (y != iY || m != iM || d != iD) {
        return false;
    }
    return true;
}
function isInteger(str) {
    //if (/[^\d]+$/.test(str)){
    if (!/^\d+$/.test(str)) {
        return false;
    }
    return true;
}
function idcard_getbirthday(id) {
    var id = String(id);
    var birthday;
    if (id.length == 15) {
        birthday = new Date(id.substr(6, 2), id.substr(8, 2) - 1, id.substr(10, 2));
    } else if (id.length == 18) {
        birthday = new Date(id.slice(6, 10), id.slice(10, 12) - 1, id.slice(12, 14));
    } else {
        return false;
    }
    return birthday;
}

function idcard_getAge(id) {
    var id = String(id);
    var age;
    if (id.length == 15) {
        age = (new Date()).getFullYear() - (new Date(id.substr(6, 2), id.substr(8, 2) - 1, id.substr(10, 2))).getFullYear();
    } else if (id.length == 18) {
        age = (new Date()).getFullYear() - (new Date(id.slice(6, 10), id.slice(10, 12) - 1, id.slice(12, 14))).getFullYear();
    } else {
        return false;
    }
    return age;
}



function checkstr(str) {      //定义checkstr函数实现对用户名长度的限制

    var re1 = new RegExp("^([a-z]|[A-Z]|[^\x00-\xff]){1}([a-z]|[A-Z]|[^\x00-\xff]|[_]|[0-9]|[|]){0,9}$");
    if (!re1.test(str)) { return true; }
    else return false;
}
function checkAccount(str) {
    var n = 0;         //定义变量n，初始值为0
    for (i = 0; i < str.length; i++) {     //应用for循环语句，获取表单提交用户名字符串的长度
        var leg = str.charCodeAt(i);     //获取字符的ASCII码值
        if (leg > 255) {       //判断如果长度大于255 
            n += 2;       //则表示是汉字为两个字节
        } else {
            n += 1;       //否则表示是英文字符，为一个字节
        }
    } if (n > 10 || n < 4) {        //判断用户名的总长度如果超过指定长度，则返回true
        return true;
    } else {
        return false;       //如果用户名的总长度不超过指定长度，则返回false
    }
}
function on_txt(txt, type) {
    if (type == 1)
        txt.className = "txt1_bg";
    else
        txt.className = "txt6_bg";
}
function over_txt(txt,type){
    if (type == 1)
        txt.className = "txt2_bg";
    else
        txt.className = "txt3_bg";
}

function SpreadIdCopy(id) {


    var obj = "Hi，我最近发现了个对战平台非常不错，你也来试试吧！\nhttp://www.5211game.com/11/index.html?spread=" + id;
    window.clipboardData.setData('text', obj); window.scroll(0, 360);
    alert("邀请链接地址复制成功。\n请在QQ或MSN等处同时按Ctrl+V将链接粘贴过去！");
}

function PublicMenu(tag, content,src) {
    for (var i = 1; i < 3; i++) {
        if ('div' + i == content) {
            document.getElementById(content).style.display = 'block';
        }
        else {
            document.getElementById('div' + i).style.display = 'none';
        }
        if ('img' + i == tag) {
            document.getElementById(tag).src = '../images/' + src + i + '.jpg';
        }
        else {
            document.getElementById('img' + i).src = '../images/' + src + i+'_0.jpg';
        }
    }
}