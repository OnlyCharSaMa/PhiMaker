import QtQuick 2.12
import QtQuick.Window 2.12
import "./PhiCom/"
import "./JS/beatsTrans.js" as T

PhiMaker {
    Component.onCompleted: {
        phiViewer.musicUrl =  "qrc:/res/test.mp3";
        bpm = 172;// 四分音符

        var rotE;
        var verE;
        var horE;
        var disE;

        var jl = createJudgeLine();

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = 0;
        disE.endTime    = T.beatToReal(1, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = T.beatToReal(1, bpm);
        disE.endTime    = T.beatToReal(1, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;


        rotE = createRotateMoveEvent(jl.jlIndex);
        rotE.startTime  = 0;
        rotE.endTime    = 1000;
        rotE.start      = 90;
        rotE.end        = 90;

        horE = createHorMoveEvent(jl.jlIndex);
        horE.startTime  = 0;
        horE.endTime    = 7000;
        horE.start      = 0.2;
        horE.end        = 0.8;
        horE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(4, bpm) + 300;
        disE.endTime    = T.beatToReal(6, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(6, bpm);
        disE.endTime    = T.beatToReal(6, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(9, bpm) + 300;
        disE.endTime    = T.beatToReal(10, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(10, bpm);
        disE.endTime    = T.beatToReal(10, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;


        //2
        jl = createJudgeLine();

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = 0;
        disE.endTime    = T.beatToReal(1, bpm);
        disE.start      = 0.3;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = T.beatToReal(1, bpm);
        disE.endTime    = T.beatToReal(2, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        horE = createHorMoveEvent(jl.jlIndex);
        horE.startTime  = 0;
        horE.endTime    = 7000;
        horE.start      = 0.8;
        horE.end        = 0.2;
        horE.easingType = Easing.OutQuad;

        rotE = createRotateMoveEvent(jl.jlIndex);
        rotE.startTime  = 0;
        rotE.endTime    = 1000;
        rotE.start      = 90;
        rotE.end        = 90;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = T.beatToReal(2, bpm);
        disE.endTime    = T.beatToReal(2, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(2, bpm) + 300;
        disE.endTime    = T.beatToReal(4, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(4, bpm);
        disE.endTime    = T.beatToReal(4, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(7, bpm);
        disE.endTime    = T.beatToReal(8, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(8, bpm);
        disE.endTime    = T.beatToReal(8, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(10, bpm);
        disE.endTime    = T.beatToReal(11, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(11, bpm);
        disE.endTime    = T.beatToReal(11, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(13, bpm);
        disE.endTime    = T.beatToReal(15, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(15, bpm);
        disE.endTime    = T.beatToReal(15, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;




        // 3
        jl = createJudgeLine();

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = 0;
        disE.endTime    = T.beatToReal(2, bpm);
        disE.start      = 0.3;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = T.beatToReal(2, bpm);
        disE.endTime    = T.beatToReal(3, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;


        rotE = createRotateMoveEvent(jl.jlIndex);
        rotE.startTime  = 0;
        rotE.endTime    = 1000;
        rotE.start      = 90;
        rotE.end        = 90;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime  = T.beatToReal(3, bpm);
        disE.endTime    = T.beatToReal(3, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(8, bpm);
        disE.endTime    = T.beatToReal(9, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(9, bpm);
        disE.endTime    = T.beatToReal(9, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(11, bpm);
        disE.endTime    = T.beatToReal(13, bpm);
        disE.start      = 0.3;
        disE.end        = 1;
        disE.easingType = Easing.OutQuad;

        disE = createDisappearEvent(jl.jlIndex);
        disE.startTime    = T.beatToReal(13, bpm);
        disE.endTime    = T.beatToReal(13, bpm) + 300;
        disE.start      = 1;
        disE.end        = 0.3;
        disE.easingType = Easing.OutQuad;




        initChart();
        startChart();

    }


}


