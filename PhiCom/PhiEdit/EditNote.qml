import QtQuick 2.0
import QtQuick 2.12

Item {
    id: note
    property bool draggable
    property bool removable
    property var phiNote


    MouseArea {
        id: mouseArea
        enabled: draggable
        anchors.fill: note
        drag.target: note

        onDoubleClicked: {
            phiNote.selfDestory();
            note.destroy();
        }

    }
}
