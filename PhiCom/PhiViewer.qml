import QtQuick 2.0
import QtMultimedia 5.12
import "./Obj/"
import "../Component/"
import "../JS/beatsTrans.js" as Trans


CharCanvas {
    id: phiViewer
    objectName: "phiViewer"

    fps: 60


    // chart
    property var judgeLineList: []

    // render and performance
    property color perfectColor: Qt.rgba(1, 0.843, 0, 1)
    property color goodColor: Qt.rgba(0.341, 0.98, 1, 1)
    property var hitPTCList: []

    // img
    property var hitPTCImgList: []
    property var noteImgList: [
        "qrc:/res/phi/notes/Tap.png",
        "qrc:/res/phi/notes/Drag.png",
        "qrc:/res/phi/notes/Flick.png",
        "qrc:/res/phi/notes/Hold_Head.png",
        "qrc:/res/phi/notes/TapHL.png",
        "qrc:/res/phi/notes/DragHL.png",
        "qrc:/res/phi/notes/FlickHL.png",
        "qrc:/res/phi/notes/Hold_HeadHL.png"
    ]


    // note info
    property var noteWs: [
        989,//tap
        989,//drag
        989,//flick
        989,//hold_head
        1089,//tap hl
        1089,//drag hl
        1089,//flick hl
        1058//hold_head hl
    ]

    property var noteHs: [
        100,//tap
        60,//drag
        200,//flick
        50,//hold_head
        200,//tap hl
        160,//drag hl
        300,//flick hl
        97//hold_head hl
    ]

    property string holdBodyImg: "qrc:/res/phi/notes/Hold.png"
    property int holdBodyW: 989
    property int holdBodyH: 1900
    // the body should be strength

    property string holdEndImg: "qrc:/res/phi/notes/Hold_End.png"
    property int holdEndW: 989
    property int holdEndH: 50

    property real noteZoom: 0.12


    // other
    property string musicUrl


    // basic Infomation
    property string formatVersion: "PhiMaker Chart Standard 1.0"
    property string musician: "null musician"
    property string charter: "null charter"
    property string illustrator: "null illustrator"
    property string chartLevel: "FM Lv.?"
    property string musicName: "null music name"

    // invisible info
    property real bpm


    signal requestSound(int typeIndex)
    signal chartStarted()
    signal chartPaused()

    // solve in advance
    Component.onCompleted: {
        loadImage("qrc:/res/phi/notes/Drag.png");
        loadImage("qrc:/res/phi/notes/DragHL.png");
        loadImage("qrc:/res/phi/notes/Flick.png");
        loadImage("qrc:/res/phi/notes/FlickHL.png");
        loadImage("qrc:/res/phi/notes/Hold.png");
        loadImage("qrc:/res/phi/notes/Hold_End.png");
        loadImage("qrc:/res/phi/notes/Hold_Head.png");
        loadImage("qrc:/res/phi/notes/Hold_HeadHL.png");
        loadImage("qrc:/res/phi/notes/HoldHL.png");
        loadImage("qrc:/res/phi/notes/Tap.png");
        loadImage("qrc:/res/phi/notes/TapHL.png");


        for(var i = 1; i < 31; i++)
        {
            var img = "qrc:/res/phi/perfect_particle/HitParticle (" + i + ")_perfect.png";
            loadImage(img);
            hitPTCImgList.push(img);
        }
    }

    property int currentTime
    property real currentBeat: Trans.realToBeat(currentTime, bpm)
    NumberAnimation {
        id: timeAnm
        target: phiViewer
        property: "currentTime"
        from: 0
        to: 9999999
        duration: 9999999
    }




    // OnPaint
    onPaint: {
        clearAll();
        drawJudgeLines();
        drawNotes();
        drawHitPTCs();
    }

    MediaPlayer {
        id: mediaPlayer
        autoLoad: true
        source: phiViewer.musicUrl
    }

    // Component
    Component {
        id: hitPTC
        HitPTC {
        }
    }

    // functional function
    function initChart()
    {
        for(var jl of judgeLineList)
        {
            jl.initAllEvents();
        }
    }

    function startChart()
    {
        chartStarted();
        timeAnm.start();
        for(var jl of judgeLineList)
        {
            jl.startAllEvents();
        }
        mediaPlayer.play();
    }

    function resumeChart()
    {
        chartStarted();
        mediaPlayer.play();
        timeAnm.resume();
        for(var jl of judgeLineList)
        {
            jl.resumeAllEvents();
        }
    }

    function restartChart()
    {
        timeAnm.restart();
        mediaPlayer.seek(0);
        mediaPlayer.play();
        chartStarted();
        for(var jl of judgeLineList)
        {
            jl.restartAllEvents();
        }
    }

    function pauseChart()
    {
        timeAnm.pause();
        mediaPlayer.pause();
        chartPaused();
        for(var jl of judgeLineList)
        {
            jl.pauseAllEvents();
        }
    }

    // sound function
    function playNoteSound(typeIndex)
    {
        requestSound(typeIndex);
    }


    // paint function
    function drawJudgeLines()
    {
        for(var i = 0; i < judgeLineList.length; i++){
            drawJudgeLine(judgeLineList[i]);
        }
    }

    function drawNotes()
    {
        var jl;
        var note;

        for(var i = 0; i < judgeLineList.length; i++)
        {
            jl = judgeLineList[i];
            for(var j = 0; j < jl.noteList.length; j++)
            {
                note = jl.noteList[j];

                if(note.requestPTC === true)
                {
                    createHitPTC(jl.hor, jl.ver, jl.rotate, note.posX);
                    note.requestPTC = false; // after meet its need(create hitParticle) then set it to false
                }

                // if note will be destroried the remove it from the list
                if(note.isDestoried === true)
                {
                    jl.noteList.splice(j,1);
                    continue;
                }

                else if(note.rFloorPos > 2){break;}
                else{drawNote(note);}
            }
        }
    }

    function drawNote(note)
    {
        var jl = note.judgeLine;
        var ctx = getContext("2d");
        // core code
        // move the original point to the specific point and rotate, draw note by using its relative position
        ctx.translate(jl.centerX, jl.centerY);
        ctx.rotate(jl.arc);
        if(note.type !== "hold")
        {
            if(note.rFloorPos <= 0) {}
            else if(note.position === "above") {drawFixedImgEx(noteImgList[note.typeIndex], note.rX, -note.rY, noteWs[note.typeIndex], noteHs[note.typeIndex], noteZoom);}
            else if(note.position === "below") {drawFixedImgEx(noteImgList[note.typeIndex], note.rx,  note.rY, noteWs[note.typeIndex], noteHs[note.typeIndex], noteZoom);}
        }
        else if(note.type === "hold")
        {
            if(note.position === "below")
            {
                ctx.scale(1 ,-1);
            }

            //note.
            if(note.headClipHeight > 0)
            {
                if(note.headClipHeight < note.headRH)
                {
                    ctx.drawImage(noteImgList[note.typeIndex],
                                  0,
                                  0,
                                  noteWs[note.typeIndex],
                                  (note.headRH - note.headClipHeight) / noteZoom,
                                  note.headLeftTop.x,
                                  note.headLeftTop.y,
                                  note.headRW,
                                  note.headRH - note.headClipHeight);
                }
            }
            else
            {
                ctx.drawImage(noteImgList[note.typeIndex],
                              note.headLeftTop.x,
                              note.headLeftTop.y,
                              note.headRW,
                              note.headRH)
            }


            // draw Body
            if(note.bodyClipHeight > 0)
            {
                if(note.bodyClipHeight < note.bodyRH)
                {
                    ctx.drawImage(holdBodyImg,
                                  0,
                                  0,
                                  holdBodyW,
                                  holdBodyH,
                                  note.bodyLeftTop.x,
                                  note.bodyLeftTop.y,
                                  note.bodyRW,
                                  note.bodyRH - note.bodyClipHeight);
                }

            }
            else
            {
                ctx.drawImage(holdBodyImg,
                              note.bodyLeftTop.x,
                              note.bodyLeftTop.y,
                              note.bodyRW,
                              note.bodyRH);
            }


            // draw End
            if(note.endClipHeight > 0)
            {
                if(note.endClipHeight < note.endRH)
                {
                    ctx.drawImage(holdEndImg,
                                  0,
                                  0,
                                  note.holdEndW,
                                  (note.endRH - note.endClipHeight) / noteZoom,
                                  note.endLeftTop.x,
                                  note.endLeftTop.y,
                                  note.endRW,
                                  note.endRH - note.endClipHeight);
                }
            }
            else
            {
                ctx.drawImage(holdEndImg,
                              note.endLeftTop.x,
                              note.endLeftTop.y,
                              note.endRW,
                              note.endRH);
            }



            if(note.position === "below")
            {
                ctx.scale(1 ,-1);
            }
        }
        ctx.rotate(-jl.arc);
        ctx.translate(-jl.centerX, -jl.centerY);
    }

    function drawHitPTCs()
    {
        var ctx = getContext("2d");
        var ptc;
        for(var i = 0; i < hitPTCList.length; i++)
        {
            ptc = hitPTCList[i];


            // very core code
            ctx.translate(ptc.rX, ptc.rY);
            ctx.rotate(ptc.arc);
            ctx.translate(ptc.xOffset, 0);
            ctx.rotate(-ptc.arc);
            drawFixedImgEx(hitPTCImgList[ptc.imgIndex], 0, 0, ptc.rW, ptc.rH);
            ctx.rotate(ptc.arc);
            ctx.translate(-ptc.xOffset, 0);
            ctx.rotate(-ptc.arc);
            ctx.translate(-ptc.rX, -ptc.rY);
        }

        hitPTCList = [];
    }

    // help paint function
    function drawJudgeLine(jl)
    {
        drawLongLine(
                    jl.centerX,
                    jl.centerY,
                    jl.arc,
                    Qt.rgba(jl.color_red, jl.color_green, jl.color_blue, jl.alpha),
                    );
    }

    // Dyn create hitPTC
    function createHitPTC(hor, ver, rotate, posX)
    {
        var ptc = hitPTC.createObject(this,{phiViewer: phiViewer});
        ptc.hor       = hor;
        ptc.ver       = ver;
        ptc.rotate    = rotate;
        ptc.posX      = posX;

    }


}
