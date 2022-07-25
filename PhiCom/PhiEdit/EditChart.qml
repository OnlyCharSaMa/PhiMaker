import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Window 2.12
import "../Obj"
import "../../Component/"
import "../../JS/beatsTrans.js" as Trans

Window {
    id: root
    width: 1200
    height: 800
    property JudgeLine jl
    property int jlIndex: 0
    property var phiMaker
    property var phiViewer
    property var noteRes:  phiViewer.noteImgList
    property var noteWs:   phiViewer.noteWs
    property var noteHs:   phiViewer.noteHs
    property var noteZoom: phiViewer.noteZoom
    property int noteW: noteWs[0]
    property int noteH: noteHs[0]
    property var notes: []

    property bool isOnEditMode: false
    property bool isOnPlaceMode: true
    property bool isOnRemoveMode: false
    property string noteType: "tap"
    property int timePerPixel: 5
    property real beatPerLine: 1 // the beat between two beatLine

    property int lineY: line.y + line.height / 2 // the judgeLine's y pos(middle)

    color: Qt.rgba(0.8, 0.8, 0.8, 1)

    Component.onCompleted: {
        reloadJL();

        var totalRelativeBeat = Math.ceil(Trans.realToBeat(yToTime(0), phiViewer.bpm));
        for(var i = 0; i < totalRelativeBeat / beatPerLine; i++)
        {
            var arg = {
                "lineIndex": i
            };
            var theBeatLine = beatLine.createObject(this, arg);
        }
    }

    Rectangle {
        id: line
        x: 0
        y: root.height * 0.9
        width: root.width
        height: root.height * 0.01
        color: "#FFFFFF"

        Rectangle {
            width:  phiViewer.height / phiViewer.width * line.width
            height: line.height
            anchors.centerIn: line
            color: Qt.rgba(0.9, 0.9, 0, 1)
        }
    }

    Rectangle {
        id: infoRect
        radius: 4
        color: Qt.rgba(0.95, 0.95, 0.95, 0.8)
        x: width * 0.01 + 30
        y: x
        width: 240
        height: 192

        Column {
            width: parent.width * 0.8
            height: parent.height * 0.8
            anchors.centerIn: parent

            Label {
                id: currentTime
                text: "Time: " + phiViewer.currentTime
            }

            Label {
                id: currentBeat
                text: "Beat: " + Trans.realToBeat(phiViewer.currentTime, phiViewer.bpm)
            }

            Label {
                id: isOnPlaceMode_l
                property alias isOn: root.isOnPlaceMode
                property string status: "Null"
                Component.onCompleted: checkStatus();
                onIsOnChanged: checkStatus();

                text: "Place Mode: " + status

                function checkStatus(){
                    if(isOn)
                    {
                        color = Qt.rgba(0, 0.7, 0, 1);
                        status = "on";
                    }
                    else
                    {
                        color = Qt.rgba(0.7, 0, 0, 1);
                        status = "off";
                    }
                }
            }

            Label {
                id: isOnEditMode_l
                property alias isOn: root.isOnEditMode
                property string status: "Null"
                Component.onCompleted: checkStatus();
                onIsOnChanged: checkStatus();

                text: "Edit Mode: " + status
                function checkStatus(){
                    if(isOn)
                    {
                        color = Qt.rgba(0, 0.7, 0, 1);
                        status = "on";
                    }
                    else
                    {
                        color = Qt.rgba(0.7, 0, 0, 1);
                        status = "off";
                    }
                }
            }

            Label {
                id: noteType_l
                property alias noteType: root.noteType
                Component.onCompleted: checkNoteType(); // be completed with color
                onNoteTypeChanged: checkNoteType();
                text: "Note Type: " + noteType

                function checkNoteType(){
                    if(noteType === "tap") {color = Qt.rgba(0, 0, 0.7, 1);}
                    else if(noteType === "drag") {color = Qt.rgba(0.7, 0.7, 0, 1);}
                    else if(noteType === "flick") {color = Qt.rgba(0.7, 0, 0, 1);}
                    else {color = Qt.rgba(0.2, 0.2, 0.7, 1);}
                }
            }

            Label {
                id: jlIndex_l
                property alias jlIndex: root.jlIndex
                text: "jlIndex: " + jlIndex
            }
        }
    }

    MouseArea {
        id: mouseArea
        width: root.width
        height: root.height
        onClicked: {
            if(isOnPlaceMode)
            {
                if(noteType !== "hold")
                {
                    var pNote = phiMaker.createNote(jl.jlIndex, noteType);
                    var nt = editNote.createObject(this, {phiNote: pNote});
                    pNote.posX = mouseX / root.width - 0.5;
                    pNote.time = yToTime(mouseY);
                    notes.push(nt);
                }
            }
        }
    }

    Component {
        id:editNote
        EditNote {
            id: theNote
            removable: root.isOnEditMode
            draggable: root.isOnEditMode


            // to avoid bindings
            Component.onCompleted:{
                width  = root.noteW * root.noteZoom;
                height = root.noteH * root.noteZoom;
            }

            x: (phiNote.posX + 0.5) * root.width - theNote.width / 2
            y: timeToY(phiNote.time - phiViewer.currentTime) - theNote.height / 2

            
            onXChanged: {
                if(root.isOnEditMode)
                {
                    phiNote.posX = (x + theNote.width / 2) / root.width - 0.5;
                }
            }
            
            onYChanged: {
                if(y !== timeToY(phiNote.time - phiViewer.currentTime) - theNote.height / 2)
                {
                    if(root.isOnEditMode)
                    {
                        phiNote.time = yToTime(y);

                    }
                }
            }


            Image {
                anchors.fill: theNote
                source: noteRes[theNote.phiNote.typeIndex]
            }
        }
    }

    Component {
        id: beatLine
        Rectangle {
            id: theBeatLine
            property int lineIndex
            property real relativeBeat: lineIndex * root.beatPerLine - phiViewer.currentBeat % beatPerLine
            property real time: Trans.beatToReal(relativeBeat, phiViewer.bpm) + phiViewer.currentTime
            property real beat: relativeBeat + phiViewer.currentBeat
            onLineIndexChanged: {
                if(relativeBeat === lineIndex * root.beatPerLine - phiViewer.currentBeat % beatPerLine) {return;}
                lineIndex++;
            }

            x: 0
            y: timeToY(Trans.beatToReal(relativeBeat, phiViewer.bpm))
            height: 5
            width: root.width
            color: Qt.rgba(0.2, 1, 0.2, 0.5)

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(noteType !== "hold")
                    {
                        var pNote = phiMaker.createNote(root.jl.jlIndex, root.noteType);
                        var nt = editNote.createObject(root, {phiNote: pNote});
                        pNote.posX = mouseX / root.width - 0.5;
                        pNote.time = theBeatLine.time;
                        root.notes.push(nt);
                    }
                }
            }

            Label {
                id: timeLabel
                anchors.left: theBeatLine.left
                color: Qt.rgba(0.4, 0.4, 0.4, 0.75)
                text: theBeatLine.time.toFixed(2)
            }

            Label {
                id: beatLabel
                anchors.right: theBeatLine.right
                color: Qt.rgba(0.4, 0.4, 0.4, 0.75)
                text: theBeatLine.beat.toFixed(2)
            }
        }
    }

    // Shortcuts
    Shortcut {
        id: alt_zShortcut
        context: Qt.ApplicationShortcut
        sequence: "alt+Z"
        onActivated: {
            noteType = "tap";
            noteW    = noteWs[0];
            noteH    = noteHs[0];
        }
    }

    Shortcut {
        id: alt_xShortcut
        context: Qt.ApplicationShortcut
        sequence: "alt+X"
        onActivated: {
            noteType = "drag";
            noteW    = noteWs[1];
            noteH    = noteHs[1];
        }
    }

    Shortcut {
        id: alt_cShortcut
        context: Qt.ApplicationShortcut
        sequence: "alt+C"
        onActivated: {
            noteType = "flick";
            noteW    = noteWs[2];
            noteH    = noteHs[2];
        }
    }

    Shortcut {
        id: alt_vShortcut
        context: Qt.ApplicationShortcut
        sequence: "alt+V"
        onActivated: {
            noteType = "hold";
            noteW    = noteWs[3];
            noteH    = noteHs[3];
        }
    }

    Shortcut {
        id: ctrl_eShortcut
        context: Qt.ApplicationShortcut
        sequence: "ctrl+E"
        onActivated: {
            isOnEditMode = !isOnEditMode;
        }
    }

    Shortcut {
        id: ctrl_pShortcut
        context: Qt.ApplicationShortcut
        sequence: "ctrl+P"
        onActivated: {
            isOnPlaceMode = !isOnPlaceMode;
        }
    }

    Shortcut {
        id: upShortcut
        context: Qt.ApplicationShortcut
        sequence: "up"
        onActivated: {
            if((jlIndex + 1) < phiViewer.judgeLineList.length)
            {
               jlIndex++;
            }
        }
    }

    Shortcut {
        id: downShortcut
        context: Qt.ApplicationShortcut
        sequence: "down"
        onActivated: {
            if(jlIndex >= 1)
            {
                jlIndex--;
            }
        }
    }

    onJlIndexChanged: reloadJL()

    function reloadJL()
    {
        jl = phiViewer.judgeLineList[jlIndex];
        for(var _note of root.notes){_note.destroy();}
        root.notes = []; // remove the undefined object
        for(var pNote of jl.noteList)
        {
            var nt = editNote.createObject(this, {phiNote: pNote});
            notes.push(nt);
        }
    }

    function timeToY(time){return lineY - time / timePerPixel;}
    function yToTime(posY){return (lineY -  posY) * timePerPixel + phiViewer.currentTime;}
}
