import QtQuick 2.12
import "../../JS/2dMath.js" as Math2d

Item {
    id: hold
    // basic paint infomation
    property string type: "hold"
    property real typeIndex: 3
    property real posX: 0
    property real rFloorPos: (time - currentTime) * speed / 1000
    property real speed: basicSpeed + judgeLine.speed
    property real basicSpeed: 0.3
    property real time: 1000
    property real holdTime: 1000
    property string position: "above"

    // performance
    property bool highLight: false
    property bool requestPTC: false
    property bool requestSound: false
    property real rFloorPosLength: holdTime * speed / 1000
    property real rEndFloorPos: rFloorPos + rFloorPosLength
    property real rCenterFloorPos: (rFloorPos + rEndFloorPos) / 2

    // other
    // property bool destoried: false
    property int anmFinishedTime: 0
    property JudgeLine judgeLine
    property var pv: judgeLine.pv
    property int currentTime: judgeLine.currentTime
    property alias ptcTimer: ptcTimer

    // signals
    signal crashed()

    property int centerX: Math.round(posX * pv.width)

    property int headY          : Math.round(-rFloorPos * pv.height)// i don't know why plus -
    property int headRW         : Math.round(pv.noteWs[typeIndex - 1] * pv.noteZoom)// short for real width // This isnt a mistake
    property int headRH         : Math.round(pv.noteHs[typeIndex] * pv.noteZoom)// short for real height
    property var headLeftTop    : Math2d.centerToLeftTop(centerX, headY, headRW, headRH)

    property int endY           : Math.round(-rEndFloorPos * pv.height)
    property int endRW          : Math.round(pv.holdEndW * pv.noteZoom)
    property int endRH          : Math.round(pv.holdEndH * pv.noteZoom)
    property var endLeftTop     : Math2d.centerToLeftTop(centerX, endY, endRW, endRH)

    property int bodyRW         : Math.round(pv.holdBodyW * pv.noteZoom)
    property int bodyRH         : - endLeftTop.y - endRH  + headLeftTop.y
    property int bodyTotalH     : bodyRH
    property var bodyLeftTop    : {
        "x": endLeftTop.x,
        "y": endLeftTop.y + endRH
    }

    property int headClipHeight : (headLeftTop.y + headRH);
    property int bodyClipHeight : headClipHeight - headRH;
    property int endClipHeight  : bodyClipHeight - bodyRH;

    property bool isCrashed:    false
    property bool isDestoried:  false
    property bool isCompleted:  false



    // we need property highLight to set typeIndex
    function checkHighLight()
    {
        if(highLight){typeIndex = 7;}
    }
    onHighLightChanged: checkHighLight();// not to judge falsely


    onRequestSoundChanged: {
        if(requestSound)
        {
            phiViewer.playNoteSound(0);
            requestSound = false;
        }
    }

    onCurrentTimeChanged: {
        if( (time + holdTime - currentTime) <= 0 && !isCrashed && isCompleted)
        {
            crash();
        }
        else if( ((time - currentTime) < 0) && ((time + holdTime - currentTime) > 0))
        {
            if(anmFinishedTime === 0)
            {
                requestSound = true;
                ptcTimer.start();
                anmFinishedTime++;
            }
        }
        else if( (time - currentTime) >= 0 && isCrashed)
        {
            isCrashed = false;
        }
    }

    // Component
    Component.onCompleted: {
        isCompleted = true;
        checkTypeIndex();
    }



    // other function
    function crash()
    {
        crashed();
        ptcTimer.stop();
        hold.isCrashed = true;
    }

    Timer {
        id: ptcTimer
        interval: 150
        triggeredOnStart: true
        repeat: true
        onTriggered: {
            hold.requestPTC = true;
        }
    }

}
