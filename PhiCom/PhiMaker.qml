import QtQuick 2.12
import QtQuick.Window 2.12
import "../Component"
import "./Obj"
import "./Events"
import "./PhiEdit"
import "../JS/FuncLib.js" as Lib

    Window {
    id: phiMaker
    width: 1300
    height: 800
    visible: true
    title: "PhiMaker"

    property alias judgeLineList: phiViewer.judgeLineList
    property alias phiViewer: phiViewer
    property alias editChart: editChart

    property alias formatVersion:   phiViewer.formatVersion
    property alias musician:        phiViewer.musician
    property alias charter:         phiViewer.charter
    property alias illustrator:     phiViewer.illustrator
    property alias chartLevel:      phiViewer.chartLevel
    property alias musicName:       phiViewer.musicName

    property alias bpm: phiViewer.bpm

    // functions
    property var sleep: Lib.sleep

    // chart status
    property bool onPlaying: false
    property bool onPaused: false


    
    EffectImg {
        width: phiMaker.width
        height: phiMaker.height
        image.source: "qrc:/res/Phigros_Icon_New.png"
        rect.blurRadius: 32
    }

    PhiViewer {
        id: phiViewer
        width: phiMaker.width
        height: phiMaker.height
    }

    EditChart {
        id: editChart
        phiViewer: phiViewer
        phiMaker: phiMaker
    }

    EditAnimation {
        id: editAnimation

    }


    // Phi obj
    Component {
        id: judgeLineObj
        JudgeLine {
        }
    }

    Component {
        id: note
        Note {
        }
    }

    Component {
        id: hold
        Hold {
        }
    }

    Component {
        id: event
        Event {

        }
    }
    
    // other object

    // shortcuts
    Shortcut {
        id: spaceShortcut
        context: Qt.ApplicationShortcut
        sequence: "space"
        onActivated: {
            if(onPlaying) {pauseChart();}
            else if(onPaused) {resumeChart();}
        }
    }

    Shortcut {
        id: f1Shortcut
        context: Qt.ApplicationShortcut
        sequence: "f1"
        onActivated: {

            // show Edit Window
            if(!editChart.visible)
            {
                if(onPlaying) {pauseChart();}
                editChart.visible = true;
            }
            else
            {
                editChart.visible = false;
            }
        }
    }

    Shortcut {
        id: f2Shortcut
        context: Qt.ApplicationShortcut
        sequence: "f2"
        onActivated: {
            if(!editAnimation.visible)
            {
                if(onPlaying) {pauseChart();}
                editAnimation.visible = true;
            }
            else
            {
                editAnimation.visible = false;
            }
        }
    }

    Shortcut {
        id: leftShortcut
        context: Qt.ApplicationShortcut
        sequence: "left"
        onActivated: {
            phiViewer.currentTime -= 100;
        }
    }

    Shortcut {
        id: rightShortcut
        context: Qt.ApplicationShortcut
        sequence: "right"
        onActivated: {
            phiViewer.currentTime += 100;
        }
    }


    // chart operate
    function initChart()
    {
        phiViewer.initChart();
    }

    function startChart()
    {
        phiViewer.startChart();
        onPlaying = true;
        onPaused  = false;
    }

    function resumeChart()
    {
        phiViewer.resumeChart();
        onPlaying = true;
        onPaused  = false;
    }

    function restartChart()
    {
        phiViewer.restartChart();
        onPlaying = true;
        onPaused  = false;
    }

    function pauseChart()
    {
        phiViewer.pauseChart();
        onPlaying = false;
        onPaused  = true;
    }

    function clearChart()
    {
        for(var jl of judgeLineList)
        {
            jl.destroy();
        }

        judgeLineList = [];

    }

    // Chart to JSON
    function createJSNote(qmlNote)
    {
        var nt = {};

        nt.type     = qmlNote.type;
        nt.time     = qmlNote.time;
        nt.posX     = qmlNote.posX;
        nt.speed    = qmlNote.speed;
        nt.position = qmlNote.position;

        return nt;
    }

    function createJSEvent(qmlEvent)
    {
        var event = {};

        event.startTime         = qmlEvent.startTime;
        event.endTime           = qmlEvent.endTime;
        event.start             = qmlEvent.start;
        event.end               = qmlEvent.end;
        event.easingType        = qmlEvent.easingType;
        event.easingAmplitude   = qmlEvent.easingAmplitude;
        event.easingOvershoot   = qmlEvent.easingOvershoot;
        event.easingPeriod      = qmlEvent.easingPeriod;
        event.easingBezierCurve = qmlEvent.easingBezierCurve;

        return event;
    }

    function getChartJSObj()
    {
        var chart = {};
        chart.formatVersion = formatVersion;
        chart.musician      = musician;
        chart.charter       = charter;
        chart.illustrator   = illustrator;
        chart.chartLevel    = chartLevel;
        chart.musicName     = musicName;

        chart.judgeLineList = [];


        for(var qmlJL of judgeLineList)
        {
            var jl = {};
            jl.noteList         = [];
            jl.verMoveEvents    = [];
            jl.horMoveEvents    = [];
            jl.rotateEvents     = [];
            jl.disappearEvents  = [];
            jl.speedEvents      = [];

            for(var note of qmlJL.noteList)
            {jl.noteList.push(createJSNote(note));}

            for(var verMoveEvents of qmlJL.verMoveEvents)
            {jl.verMoveEvents.push(createJSEvent(verMoveEvents));}

            for(var horMoveEvent of qmlJL.horMoveEvents)
            {jl.horMoveEvents.push(createJSEvent(horMoveEvent));}

            for(var disappearEvent of qmlJL.disappearEvents)
            {jl.disappearEvents.push(createJSEvent(disappearEvent));}

            for(var rotateEvent of qmlJL.rotateEvents)
            {jl.rotateEvents.push(createJSEvent(rotateEvent));}

            for(var speedEvent of qmlJL.speedEvents)
            {jl.speedEvents.push(createJSEvent(speedEvent));}

            chart.judgeLineList.push(jl);
        }
        return chart;
    }

    function loadChart(JSChart)
    {
        clearChart();

        formatVersion = JSChart.formatVersion;
        musician      = JSChart.musician;
        charter       = JSChart.charter;
        illustrator   = JSChart.illustrator;
        chartLevel    = JSChart.chartLevel;
        musicName     = JSChart.musicName;

        for(var JSJL of JSChart.judgeLineList)
        {
            var jl = createJudgeLine(); // qml Component has already declare the list so here we don't do that

            for(var JSNote of JSJL.noteList)
            {
                var nt = createQMLNote(jl.jlIndex, JSNote);
                // This is my fault , Event didnt create as an instance but note did so neednt to push
            }

            for(var verMoveEvent of JSJL.verMoveEvents)
            {
                var event = createQMLEvent(verMoveEvent);
                jl.verMoveEvents.push(event);
            }

            for(var horMoveEvent of JSJL.horMoveEvents)
            {
                var event1 = createQMLEvent(horMoveEvent);
                jl.horMoveEvents.push(event1);
            }

            for(var disappearEvent of JSJL.disappearEvents)
            {
                var event2 = createQMLEvent(disappearEvent);
                jl.disappearEvents.push(event2);
            }

            for(var rotateEvent of JSJL.rotateEvents)
            {
                var event3 = createQMLEvent(rotateEvent);
                jl.rotateEvents.push(event3);
            }

            for(var speedEvent of JSJL.speedEvents)
            {
                var event4 = createQMLEvent(speedEvent);
                jl.speedEvents.push(event4);
            }

            jl.pv = phiViewer;

            judgeLineList.push(jl);

        }

    }

    function createQMLNote(jlIndex, JSNote)
    {
        var nt = createNote(jlIndex, JSNote.type);

        nt.type     = JSNote.type;
        nt.time     = JSNote.time;
        nt.posX     = JSNote.posX;
        nt.speed    = JSNote.speed;
        nt.position = JSNote.position;
        nt.judgeLine= judgeLineList[jlIndex];

        return nt;
    }

    function createQMLEvent(JSEvent)
    {
        var e = event.createObject(phiViewer);

        e.startTime         = JSEvent.startTime;
        e.endTime           = JSEvent.endTime;
        e.start             = JSEvent.start;
        e.end               = JSEvent.end;
        e.easingType        = JSEvent.easingType;
        e.easingAmplitude   = JSEvent.easingAmplitude;
        e.easingOvershoot   = JSEvent.easingOvershoot;
        e.easingPeriod      = JSEvent.easingPeriod;
        e.easingBezierCurve = JSEvent.easingBezierCurve;

        return e;
    }

    // create QML Phi obj function
    function createJudgeLine(parameter = {})
    {
        var jl      = judgeLineObj.createObject(phiViewer, parameter);
        var len     = phiViewer.judgeLineList.length;
        jl.pv = phiMaker.phiViewer;
        jl.jlIndex  = len;
        phiViewer.judgeLineList.push(jl);

        return jl;
    }

    function createNote(jlIndex, noteType = "tap")
    {
        var nt;
        var parameter = {
            type: noteType,
            judgeLine: judgeLineList[jlIndex]
        }

        if(noteType !== "hold"){nt = note.createObject(phiViewer, parameter);}
        else if(noteType === "hold"){nt = hold.createObject(phiViewer, parameter);}
        phiViewer.judgeLineList[jlIndex].noteList.push(nt);
        return nt;
    }

    // create jl Event
    function createHorMoveEvent(jlIndex, parameter = {})
    {
        var horEvent = event.createObject(phiViewer, parameter);
        phiViewer.judgeLineList[jlIndex].horMoveEvents.push(horEvent);
        return horEvent;
    }

    function createVerMoveEvent(jlIndex, parameter = {})
    {
        var verEvent = event.createObject(phiViewer, parameter);
        phiViewer.judgeLineList[jlIndex].verMoveEvents.push(verEvent);
        return verEvent;
    }

    function createRotateMoveEvent(jlIndex, parameter = {})
    {
        var rotateEvent = event.createObject(phiViewer, parameter);
        phiViewer.judgeLineList[jlIndex].rotateEvents.push(rotateEvent);
        return rotateEvent;
    }

    function createDisappearEvent(jlIndex, parameter = {})
    {
        var disappearEvent = event.createObject(phiViewer, parameter);
        phiViewer.judgeLineList[jlIndex].disappearEvents.push(disappearEvent);
        return disappearEvent;
    }


}
