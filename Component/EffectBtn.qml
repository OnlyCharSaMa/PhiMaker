import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 1.4

Item {
    id: root
    x: 0
    y: 0
    width: 200
    height: 70
    property int radius: 3
    property real enterAnmProgress: 0
    property real horLineZoom: 0.04
    property real verLineZoom: 0.02
    property alias text: label.text

    property alias textObj: text
    property alias enterAnm: enterAnm
    property alias rect: rect
    property alias bottomRect: bottomRect
    property alias topRect: topRect
    property alias leftRect: leftRect
    property alias rightRect: rightRect

    property int clickAnmDuration: 500

    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: Rectangle {
            height: root.height
            width:  root.width
            radius: root.radius
        }
    }

    //signal
    signal clicked();

    Label {
        id: text
    }

    EffectRect {
        id: rect
        anchors.fill: root
        rectRadius: 0
        pos_x: root.x
        pos_y: root.y
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: root
        onEntered: {
            exitAnm.stop();
            enterAnm.start();
        }
        onExited: {
            enterAnm.stop();
            exitAnm.start();
        }
        onClicked: {
            var c = circle.createObject(this);
            c.centerX = mouseX;
            c.centerY = mouseY;
            root.clicked();//send signal
        }
    }

    // enter anm solve
    Rectangle {
        id: bottomRect
        height: root.height * horLineZoom
        width: root.width * enterAnmProgress
        color: Qt.rgba(1, 1, 1, 0.7)
        anchors.bottom: root.bottom
        anchors.horizontalCenter: root.horizontalCenter
    }

    Rectangle {
        id: topRect
        visible: false
        height: root.height * horLineZoom
        width: root.width * enterAnmProgress
        color: Qt.rgba(1, 1, 1, 0.7)
        anchors.top: root.top
        anchors.horizontalCenter: root.horizontalCenter
    }

    Rectangle {
        id: leftRect
        visible: false
        height: root.height * enterAnmProgress
        width: root.width * verLineZoom
        color: Qt.rgba(1, 1, 1, 0.7)
        anchors.left: root.left
        anchors.verticalCenter: root.verticalCenter
    }

    Rectangle {
        id: rightRect
        visible: false
        height: root.height * enterAnmProgress
        width: root.width * verLineZoom
        color: Qt.rgba(1, 1, 1, 0.7)
        anchors.right: root.right
        anchors.verticalCenter: root.verticalCenter
    }

    NumberAnimation {
        id: enterAnm
        target: root
        property: "enterAnmProgress"
        from: enterAnmProgress
        to: 1
        duration: 300
        easing.type: Easing.InQuad
    }

    NumberAnimation {
        id: exitAnm
        target: root
        property: "enterAnmProgress"
        from: enterAnmProgress
        to: 0
        duration: 300
        easing.type: Easing.InQuad
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
