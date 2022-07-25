 import QtQuick 2.12
import "../../JS/2dMath.js" as Math2d

Item {
    id: jl
    // basic paint infomation
    property real ver: 0.5
    property real hor: 0.5
    property real rotate: 0
    property real arc: Math2d.angleToArc(rotate)
    property real alpha: 1

    property var noteList: []

    // performance
    property real color_red: 1
    property real color_green: 0.843
    property real color_blue: 0
    property real speed: 0

    // event List
    property var verMoveEvents: []
    property var horMoveEvents: []
    property var rotateEvents: []
    property var disappearEvents: []
    property var speedEvents: []

    property int verEventIndex: 0
    property int horEventIndex: 0
    property int rotateEventIndex: 0
    property int disappearEventIndex: 0
    property int speedEventIndex: 0

    // other
    property var jlIndex
    property var pv
    property int currentTime: pv.currentTime

    // Position
    property int centerX: hor * pv.width
    property int centerY: ver * pv.height


    // Component
    Component.onCompleted: {
        initAllEvents();
    }




    // events solve functions
//    function start()
//    {
//        startAllEvents();
//        startNoteEvents();
//    }

//    function restart()
//    {
//        startAllEvents();
//        startNoteEvents();
//    }


    // jl events solve
    function startAllEvents()
    {
        verAnm.start();
        horAnm.start();
        rotateAnm.start();
        disappearAnm.start();
        speedAnm.start();
    }

    function resumeAllEvents()
    {
        verAnm.resume();
        horAnm.resume();
        rotateAnm.resume();
        disappearAnm.resume();
        speedAnm.resume();
    }

    function restartAllEvents()
    {
        // event
        verEventIndex         = 0;
        horEventIndex         = 0;
        rotateEventIndex      = 0;
        disappearEventIndex   = 0;

        initAllEvents(); // needs to init To load original events

        verAnm.restart();
        horAnm.restart();
        rotateAnm.restart();
        disappearAnm.restart();
        speedAnm.restart();
    }

    function pauseAllEvents()
    {
        verAnm.pause();
        horAnm.pause();
        rotateAnm.pause();
        disappearAnm.pause();
        speedAnm.pause();
    }

    function initAllEvents()
    {
        initVerMoveAnm();
        initHorMoveAnm();
        initRotateAnm();
        initDisappearAnm();
        initSpeedAnm();
    }

    function initVerMoveAnm()
    {
        if(verMoveEvents.length > 0)
        {
            var verEvent    = verMoveEvents[verEventIndex];
            verAnm.duration = verEvent.endTime - verEvent.startTime;
            verAnm.from     = verEvent.start;
            verAnm.to       = verEvent.end;

            // easing
            verAnm.easing.type        = verEvent.easingType;
            verAnm.easing.amplitude   = verEvent.easingAmplitude;
            verAnm.easing.overshoot   = verEvent.easingOvershoot;
            verAnm.easing.period      = verEvent.easingPeriod;
            verAnm.easing.bezierCurve = verEvent.easingBezierCurve;
        }
    }

    function initHorMoveAnm()
    {
        if(horMoveEvents.length > 0)
        {
            var horEvent    = horMoveEvents[horEventIndex];
            horAnm.duration = horEvent.endTime - horEvent.startTime;
            horAnm.from     = horEvent.start;
            horAnm.to       = horEvent.end;

            // easing
            horAnm.easing.type        = horEvent.easingType;
            horAnm.easing.amplitude   = horEvent.easingAmplitude;
            horAnm.easing.overshoot   = horEvent.easingOvershoot;
            horAnm.easing.period      = horEvent.easingPeriod;
            horAnm.easing.bezierCurve = horEvent.easingBezierCurve;
        }
    }

    function initRotateAnm()
    {
        if(rotateEvents.length > 0)
        {
            var rotateEvent    = rotateEvents[rotateEventIndex];
            rotateAnm.duration = rotateEvent.endTime - rotateEvent.startTime;
            rotateAnm.from     = rotateEvent.start;
            rotateAnm.to       = rotateEvent.end;

            // easing
            rotateAnm.easing.type        = rotateEvent.easingType;
            rotateAnm.easing.amplitude   = rotateEvent.easingAmplitude;
            rotateAnm.easing.overshoot   = rotateEvent.easingOvershoot;
            rotateAnm.easing.period      = rotateEvent.easingPeriod;
            rotateAnm.easing.bezierCurve = rotateEvent.easingBezierCurve;
        }

    }

    function initDisappearAnm()
    {
        if(disappearEvents.length > 0)
        {
            var disappearEvent          = disappearEvents[disappearEventIndex];
            disappearAnm.duration       = disappearEvent.endTime - disappearEvent.startTime;
            disappearAnm.from           = disappearEvent.start;
            disappearAnm.to             = disappearEvent.end;

            // easing
            disappearAnm.easing.type        = disappearEvent.easingType;
            disappearAnm.easing.amplitude   = disappearEvent.easingAmplitude;
            disappearAnm.easing.overshoot   = disappearEvent.easingOvershoot;
            disappearAnm.easing.period      = disappearEvent.easingPeriod;
            disappearAnm.easing.bezierCurve = disappearEvent.easingBezierCurve;
        }
    }

    function initSpeedAnm()
    {
        if(speedEvents.length > 0)
        {
            var speedEvent          = speedEvents[speedEventIndex];
            speedAnm.duration       = speedEvent.endTime - speedEvent.startTime;
            speedAnm.from           = speedEvent.start;
            speedAnm.to             = speedEvent.end;

            // easing
            speedAnm.easing.type        = speedEvent.easingType;
            speedAnm.easing.amplitude   = speedEvent.easingAmplitude;
            speedAnm.easing.overshoot   = speedEvent.easingOvershoot;
            speedAnm.easing.period      = speedEvent.easingPeriod;
            speedAnm.easing.bezierCurve = speedEvent.easingBezierCurve;
        }
    }

    // anmSolve
    NumberAnimation {
        id: verAnm
        target: jl
        property: "ver"

        property bool isAfterBlank: false

        onFinished: {
            if(isAfterBlank){jumped();}
            else{normal();}
        }

        function normal()
        {
            verEventIndex++;
            // because after++ , index === next obj's length
            if(verEventIndex >= verMoveEvents.length) return;
            else{
                if(verMoveEventIndex === 0){}
                else if(verMoveEvents[verEventIndex-1].endTime !== verMoveEvents[verEventIndex].startTime)
                {
                    verAnm.duration = verMoveEvents[verEventIndex].startTime - verMoveEvents[verEventIndex-1].endTime;
                    verAnm.from     = ver;
                    verAnm.to       = ver;
                    verAnm.isAfterBlank   = true;
                    verAnm.start();
                }
                else
                {
                    initVerMoveAnm();
                    verAnm.start();
                }
            }
        }

        function jumped()
        {
            initVerMoveAnm();
            verAnm.start();
            isAfterBlank = false;
        }
    }

    NumberAnimation {
        id: horAnm
        target: jl
        property: "hor"

        property bool isAfterBlank: false

        onFinished: {
            if(isAfterBlank){jumped();}
            else{normal();}
        }

        function normal()
        {
            horEventIndex++;
            // because after++ , index === next obj's length
            if(horEventIndex >= horMoveEvents.length) return;
            else{
                if(horMoveEventIndex === 0){}
                else if(horMoveEvents[horEventIndex-1].endTime !== horMoveEvents[horEventIndex].startTime)
                {
                    horAnm.duration = horMoveEvents[horEventIndex].startTime - horMoveEvents[horEventIndex-1].endTime;
                    horAnm.from     = hor;
                    horAnm.to       = hor;
                    horAnm.isAfterBlank   = true;
                    horAnm.start();
                }
                else {
                    initHorMoveAnm();
                    horAnm.start();
                }
            }
        }

        function jumped()
        {
            initHorMoveAnm();
            horAnm.start();
            isAfterBlank = false;
        }

    }

    NumberAnimation {
        id: rotateAnm
        target: jl
        property: "rotate"

        property bool isAfterBlank: false

        onFinished: {
            if(isAfterBlank){jumped();}
            else{normal();}
        }

        function normal()
        {
            rotateEventIndex++;
            // because after++ , index === next obj's length
            if(rotateEventIndex >= rotateEvents.length) return;
            else{
                if(rotateEventIndex === 0){}
                else if(rotateEvents[rotateEventIndex-1].endTime !== rotateEvents[rotateEventIndex].startTime)
                {
                    rotateAnm.duration          = rotateEvents[rotateEventIndex].startTime - rotateEvents[rotateEventIndex-1].endTime;
                    rotateAnm.from              = rotate;
                    rotateAnm.to                = rotate;
                    rotateAnm.isAfterBlank      = true;
                    rotateAnm.start();
                }
                else {
                    initRotateAnm();
                    rotateAnm.start();
                }
            }
        }

        function jumped()
        {
            initRotateAnm();
            rotateAnm.start();
            isAfterBlank = false;
        }

    }

    NumberAnimation {
        id: disappearAnm
        target: jl
        property: "alpha"


        property bool isAfterBlank: false

        onFinished: {
            if(isAfterBlank){jumped();}
            else{normal();}

        }

        function normal()
        {
            disappearEventIndex++;
            // because after++ , index === next obj's length
            if(disappearEventIndex >= disappearEvents.length) return;
            else{
                if(disappearEventIndex === 0){}
                else if(disappearEvents[disappearEventIndex-1].endTime !== disappearEvents[disappearEventIndex].startTime)
                {
                    disappearAnm.duration       = disappearEvents[disappearEventIndex].startTime - disappearEvents[disappearEventIndex-1].endTime;
                    disappearAnm.from           = alpha;
                    disappearAnm.to             = alpha;
                    disappearAnm.isAfterBlank   = true;
                    disappearAnm.start();
                }
                else {
                    initDisappearAnm();
                    disappearAnm.start();
                }
            }

        }

        function jumped()
        {
            initDisappearAnm();
            disappearAnm.start();
            isAfterBlank = false;
        }
    }

    NumberAnimation {
        id: speedAnm
        target: jl
        property: "speed"


        property bool isAfterBlank: false

        onFinished: {
            if(isAfterBlank){jumped();}
            else{normal();}

        }

        function normal()
        {
            speedEventIndex++;
            // because after++ , index === next obj's length
            if(speedEventIndex >= speedEvents.length) return;
            else{
                if(speedEventIndex === 0){}
                else if(speedEvents[speedEventIndex-1].endTime !== speedEvents[speedEventIndex].startTime)
                {
                    speedAnm.duration       = speedEvents[speedEventIndex].startTime - speedEvents[speedEventIndex-1].endTime;
                    speedAnm.from           = speed;
                    speedAnm.to             = speed;
                    speedAnm.isAfterBlank   = true;
                    speedAnm.start();
                }
                else {
                    initSpeedAnm();
                    speedAnm.start();
                }
            }

        }

        function jumped()
        {
            initSpeedAnm();
            speedAnm.start();
            isAfterBlank = false;
        }
    }
}
