import QtQuick 2.12
import QtGraphicalEffects 1.12



Item {
    id: root
    x: 0
    y: 0
    width: 500
    height: 200
    property int rectRadius: 3
    property color maskColor: Qt.rgba(0.75, 0.75, 0.75, 0.6)

    property int pos_x: x
    property int pos_y: y

    property var blur
    property int blurSamples : (blurRadius + 1) * 2
    property var blurTarget: "null"
    property int blurRadius: 16
    property string blurQuality: "none"



    //使用layer来遮罩，以防rect的圆角被blur挡住
    layer.enabled: true
    layer.effect: OpacityMask {
        source: root
        maskSource: Rectangle {
            radius: rectRadius
            width: root.width
            height: root.height
        }
    }

    //用来遮罩的rect
    Rectangle {
        anchors.fill: parent
        width: root.width
        height: root.height
        radius: root.rectRadius
        color: root.maskColor
        z: 2
    }



    //高质量模糊 - 高斯模糊组件
    Component {
        id: gaussianBlur
        GaussianBlur {
            source: blurTarget
            width: source.width
            height: source.height
            radius: blurRadius
            samples: blurSamples
        }
    }

    //快速模糊 - fastBlur组件
    Component {
        id: fastBlur
        FastBlur {
            source: blurTarget
            width: source.width
            height: source.height
            radius: blurRadius
        }
    }


    Component.onCompleted: {
        if(blurTarget === "null"){console.log("你忘记设置blurTarget了");}

        if(blurQuality === "high")
        {blur = gaussianBlur.createObject(this,{z: 1});}
        else if(blurQuality === "low")
        {blur = fastBlur.createObject(this,{z: 1});}
        else if(blurQuality === "none")
        {}
        else{blur = gaussianBlur.createObject(this,{z: 1});}
        setBlurPosition()
    }

    onPos_xChanged: setBlurPosition();
    onPos_yChanged: setBlurPosition();

    function setBlurPosition()
    {
        blur.x = blurTarget.x - pos_x;
        blur.y = blurTarget.y - pos_y;
    }
}
