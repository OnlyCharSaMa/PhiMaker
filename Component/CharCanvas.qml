import QtQuick 2.0
import "../JS/2dMath.js" as Math2d

Canvas {
    id: root
    property real fps: 60
    property color maskColor: Qt.rgba(0, 0, 0, 0.65)

    // functions
    property var angleToArc     : Math2d.angleToArc
    property var getLineCenter  : Math2d.getLineCenter
    property var centerToLeftTop: Math2d.centerToLeftTop
    property var leftTopToCenter: Math2d.leftTopToCenter

    //background
    Rectangle {
        width: root.width
        height: root.height
        color: maskColor
        z: -1
    }

    // refresh the canvas
    Timer {
        interval: 1000 / fps
        running: true
        repeat: true
        onTriggered: requestPaint();
    }

    // solve render
    function clearAll()
    {
        var ctx = getContext("2d");
        ctx.reset();
    }

    // paint functions
    function drawLongLine(x, y, arc, color = Qt.rgba(1,1,1,1), width = 5)
    {

        var ctx = getContext("2d");

        ctx.strokeStyle = color;
        ctx.lineWidth = width;

        ctx.translate(x, y);
        ctx.rotate(arc);

        ctx.beginPath();
        ctx.moveTo(-1000000,0);
        ctx.lineTo(+1000000,0);
        ctx.stroke();
        ctx.closePath();

        ctx.rotate(-arc);
        ctx.translate(-x, -y);
    }

    function drawLongLineEx(x, y, rotate, color = Qt.rgba(1,1,1,1), zoom = 0.0035)
    {

        var ctx = getContext("2d");

        ctx.strokeStyle = color;
        ctx.lineWidth = root.height * zoom;

        ctx.translate(x, y);
        ctx.rotate(angleToArc(rotate));

        ctx.beginPath();
        ctx.moveTo(-1000000,0);
        ctx.lineTo(+1000000,0);
        ctx.stroke();
        ctx.closePath();

        ctx.rotate(-angleToArc(rotate));
        ctx.translate(-x, -y);
    }

    function drawArc(x, y, r, startAngle, endAngle, color = Qt.rgba(1,1,1,1), flag = false, zoom = 0.005)
    {
        var ctx = getContext("2d");

        ctx.strokeStyle = color;
        ctx.lineWidth = root.height * zoom;

        ctx.beginPath();
        ctx.arc(x, y, r, angleToArc(startAngle), angleToArc(endAngle), flag);
        ctx.stroke();
        ctx.closePath();
    }


    function drawBall(x, y, r, color = Qt.rgba(1,1,1,1))
    {
        var ctx = getContext("2d");

        ctx.fillStyle = color;

        ctx.beginPath();
        ctx.arc(x, y, r, 0, Math.PI * 2, false);
        ctx.fill();
        ctx.closePath();

        console.log("x: ", x, " y: ", y);
    }

    function drawFixedImg(img, x, y, w, h)
    {
        var ctx = getContext("2d");
        var leftTop = centerToLeftTop(x, y, w, h);
        ctx.drawImage(img, leftTop.x, leftTop.y, w, h);
    }

    function drawFixedImgEx(img, x, y, w, h, zoom = 1)
    {
        var ctx = getContext("2d");

        var leftTop = centerToLeftTop(x, y, w * zoom, h * zoom);

        ctx.drawImage(img, leftTop.x, leftTop.y, w * zoom, h * zoom);
    }

    function drawRotateImg(img, x, y, w, h, zoom = 1, rotate = 0)
    {
        var ctx = getContext("2d");

        ctx.translate(x, y);
        ctx.rotate(angleToArc(rotate));
        drawFixedImgEx(img, 0, 0, w, h, zoom);
        ctx.rotate(-angleToArc(rotate));
        ctx.translate(-x, -y);
    }


    // math solve functions



    function randomNum(a, b)
    {
        return (Math.random() * (b - a) + a);
    }
}
