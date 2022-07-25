import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 1.4

Item {
    id: root
    x: 0
    y: 0
    width: 200
    height: 70
    clip: true
    property bool hoverEnabled: false
    property int radius: 3
    property alias label: label
    property alias rect: rect
    property int clickAnmDuration: 500


    //signal
    signal entered();
    signal exited();
    signal clicked();



    EffectRect {
        id: rect
        pos_x: root.x
        pos_y: root.y
        anchors.fill: root
        maskColor: Qt.rgba(0.8, 0.8, 0.8, 0.65)
    }

    Label {
        id: label
        anchors.centerIn: root
    }

    MouseArea {
        hoverEnabled: root.hoverEnabled
        anchors.fill: root
        onEntered: {
            root.entered();
        }
        onExited: {
            root.exited();
        }
        onClicked: {
            var c = circle.createObject(this);
            c.centerX = mouseX;
            c.centerY = mouseY;
            root.clicked();//send signal
        }
    }



    // clicked anm
    Component {
        id: circle
        Circle {
            id: theCircle
            property real alpha: 0.3
            color: Qt.rgba(0.3, 0.3, 0.3, alpha)

            NumberAnimation {
                target: theCircle
                property: "r"
                from: 0
                to: Math.max(root.height, root.width)
                duration: clickAnmDuration
                running: true
                onFinished: {
                    theCircle.destroy();
                }
            }

            NumberAnimation {
                target: theCircle
                property: "alpha"
                from: alpha
                to: 0
                duration: clickAnmDuration
                running: true
            }
        }
    }
}
