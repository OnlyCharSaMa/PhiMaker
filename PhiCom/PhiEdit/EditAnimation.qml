import QtQuick 2.12
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import "../Obj/"
import "../../Component"

Window {
    id: window
    property JudgeLine jl
    property var phiMaker
    property var phiViewer

    width:  1200
    height: 800

    Item {
        id: root
        width: window.width
        height:window.height


        Image {
            id: background
            anchors.fill: root
            fillMode: Image.PreserveAspectCrop
            source: "qrc:/res/pic/miku.jpg"
        }
    }

    // 顶部的Rect用于显示信息
    EffectRect {
        id: infoRect
        anchors.top: root.top
        anchors.left: root.left
        anchors.right: root.right
        anchors.topMargin: 30
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        height: root.height * 0.07 + 30
        blurTarget: root
        blurRadius: 40
        blurQuality: "high"
        rectRadius: root.width * 0.005 + 5
        pos_x: x
        pos_y: y
    }

    Column {
        id: btnCol
        anchors.top: infoRect.bottom
        anchors.left: root.left
        anchors.bottom: root.bottom
        anchors.topMargin: 50
        anchors.leftMargin: 20
        anchors.bottomMargin: 30
        width: root.width * 0.15
        spacing: root.height * 0.1 - 20

        property int btnCount: 5
        property int totalHeight: (height - (btnCount - 1) * btnCol.spacing) //组件占用的高度

        property SimpleBtn horMoveBtn
        property SimpleBtn verMoveBtn
        property SimpleBtn rotateBtn
        property SimpleBtn disappearBtn
        property SimpleBtn speedBtn

        Component.onCompleted: {
            btnCount = 5;

            horMoveBtn   = btn.createObject(btnCol);
            verMoveBtn   = btn.createObject(btnCol);
            rotateBtn    = btn.createObject(btnCol);
            disappearBtn = btn.createObject(btnCol);
            speedBtn     = btn.createObject(btnCol);

            horMoveBtn   .label.text = qsTr("Hor Move  Events Manage");
            verMoveBtn   .label.text = qsTr("Ver Move  Events Manage");
            rotateBtn    .label.text = qsTr("Rotate    Events Manage");
            disappearBtn .label.text = qsTr("Disappear Events Manage");
            speedBtn     .label.text = qsTr("Speed     Events Manage");

        }

        Component {
            id: btn
            SimpleBtn {
                rect.blurQuality: "high"
                rect.blurTarget: root
                rect.blurRadius: 30
                rect.rectRadius: btnCol.height * 0.005 + 15
                rect.pos_x: x + btnCol.x
                rect.pos_y: y + btnCol.y
                x: 0
                y: 0
                height: btnCol.totalHeight / btnCol.btnCount
                width: btnCol.width
                label.font.pixelSize: btnCol.width * 0.075

                property int o_x
                property int o_y
                property int o_w
                property int o_h
                property int t_x
                property int t_y
                property int t_w
                property int t_h

                NumberAnimation on x {
                    easing.type: Easing.OutExpo
                    duration: 200
                }
                NumberAnimation on y {
                    easing.type: Easing.OutExpo
                    duration:200
                }
                NumberAnimation on width {
                    easing.type: Easing.OutExpo
                    duration: 200
                }
                NumberAnimation on height {
                    easing.type: Easing.OutExpo
                    duration:200
                }
            }
        }
    }

    EffectRect {
        id: detailRect
        anchors.left: btnCol.right
        anchors.bottom: root.bottom
        anchors.top: infoRect.bottom
        anchors.right: root.right
        anchors.leftMargin: 20
        anchors.bottomMargin: 30
        anchors.topMargin: 50
        anchors.rightMargin: 20
        blurTarget: root
        blurQuality: "high"
        blurRadius: 30
        rectRadius: height * 0.005 + 45
        maskColor: Qt.rgba(1, 1, 1, 0.65)
    }

}
