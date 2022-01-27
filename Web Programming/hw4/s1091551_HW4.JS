var box1Image;
var picValue = 1;
var picCode = 1;
var picturee = "bird1.jpg";
var picname = "bird";

function start() {
    var button = document.getElementById("submit");
    button.addEventListener("click", changebg, false);
    box1Image = document.getElementById("boxpic");
    var clearbutton = document.getElementById("reset");
    clearbutton.addEventListener("click", clearvoc, false);
}

function changebg() {
    setImage(box1Image);
}

function setImage(boxImg) {

    if (picCode == 1) {
        boxImg.setAttribute("src", "pic/bird" + picValue + ".jpg");
        picturee = ("bird" + picValue + ".jpg");
        picname = "bird";
    }
    if (picCode == 2) {
        boxImg.setAttribute("src", "pic/cat" + picValue + ".jpg");
        picturee = ("cat" + picValue + ".jpg");
        picname = "cat";
    }
    if (picCode == 3) {
        boxImg.setAttribute("src", "pic/dog" + picValue + ".jpg");
        picturee = ("dog" + picValue + ".jpg");
        picname = "dog";
    }


    picValue++;

    if (picValue == 6) {
        picValue = 1;
        picCode++;
        if (picCode == 4)
            picCode = 1;
    }
}

window.addEventListener("load", start, false);

//回傳正確座標
var flag = 0;
var minx = miny = maxx = maxy = 0;
function clickEvent(e) {
    if (flag == 0) {
        alert('minx: ' + mousePos(e).x + '\nminy: ' + mousePos(e).y);
        minx = mousePos(e).x;
        miny = mousePos(e).y;
        flag++;
        return;
    }

    if (flag == 1) {
        alert('maxx: ' + mousePos(e).x + '\nmaxy: ' + mousePos(e).y);
        maxx = mousePos(e).x;
        maxy = mousePos(e).y;
        flag = 0;
    }

    $.ajax({
        url: "s1091551_HW4.php", //傳到哪
        data: {
            minx: minx,  //在php裏面的變數
            miny: miny,
            maxx: maxx,
            maxy: maxy,
            picturee: picturee,
            name: picname,
            valid:1
        },
        type: "POST",
        datatype: "html",
        success: function (output) {  //如果執行成功的話
            $("#box2").html(output);
            //alert(output);
        },
        error: function () {
            alert("Request Failed.")
        }
    });
};

function mousePos(e) {
    var e = e || window.event;
    return {
        x: e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft,
        y: e.clientY + document.body.scrollTop + document.documentElement.scrollTop
    };
};


function clearvoc(){
    $.ajax({
        url: "s1091551_HW4.php", //傳到哪
        data: {
            minx: null,  //在php裏面的變數
            miny: null,
            maxx: null,
            maxy: null,
            picturee: picturee,
            name: picname,
            valid:null
        },
        type: "POST",
        datatype: "html",
        success: function (output) { 
            $("#box2").html(output);
            //alert(output);
        },
        error: function () {
            alert("Request Failed.")
        }
    });
}