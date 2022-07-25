import QtQuick 2.12
import "../../JS/2dMath.js" as Math2d

Item {
    id: ptc
    property var phiViewer
    property int imgIndex
    property var posX
    property var hor
    property var ver
    property var rotate
    property real arc: Math2d.angleToArc(ptc.rotate)

    property int rW:       1300 * phiViewer.noteZoom
    property int rH:       rW
    property int rX:       hor  * phiViewer.width
    property int rY:       ver  * phiViewer.height
    property int xOffset:  posX * phiViewer.width

    Component.onCompleted: {
        anm.start();
    }

    NumberAnimation {
        id: anm
        target: ptc
        property: "imgIndex"
        duration: 500
        from: 0
        to  : 29

        onFinished: {
            ptc.destroy();
        }
    }

    onImgIndexChanged: {
        var thePtc = {};
        thePtc.imgIndex = imgIndex;
        thePtc.xOffset  = xOffset;
        thePtc.rX       = rX;
        thePtc.rY       = rY;
        thePtc.rW       = rW;
        thePtc.rH       = rH;
        thePtc.arc      = arc;
        ptc.phiViewer.hitPTCList.push(thePtc);
    }
}
