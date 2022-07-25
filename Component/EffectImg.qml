import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    property var maskColor: Qt.rgba(0,0,0,0.4)
    property var radius: 0
    property alias rect: rect
    property alias image: image

    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: Rectangle {
            width: root.width
            height: root.height
            radius: root.radius
        }
    }

    Image {
        id: image
        anchors.fill: root
        fillMode: Image.PreserveAspectCrop
        z: 1
    }

    EffectRect {
        id: rect
        maskColor: Qt.rgba(1, 1, 1, 0.25)
        blurTarget: image
        blurQuality: "high"
        width: image.width
        height: image.height
        x: image.x
        y: image.y
        z: 2
    }

}

