function rnd() {
    rnd.seed = (rnd.seed * 9301 + 49297) % 233280;
    return rnd.seed / (233280.0);
}
function rand(number) {
    return Math.ceil(Math.random() * number);
}
function GetRandImg() {
    document.getElementById('ValidateCodeImg').src = 'ValidateCode.aspx?' + rand(99999999).toString();
    return false;
}
function GetRandImgFile() {
    document.getElementById('ValidateCodeImg').src = '../ValidateCode.aspx?' + rand(99999999).toString();
    return false;
}