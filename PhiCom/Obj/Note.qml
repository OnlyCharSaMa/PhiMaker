import QtQuick 2.12
import QtMultimedia 5.12


Item {
    id: note

    // basic paint infomation
    property string type: "tap"
    property var typeIndex
    property real posX: 0
    property real rFloorPos: (time - currentTime) * speed / 1000
    property real speed: basicSpeed + judgeLine.speed
    property real basicSpeed: 0.3
    property real time: 0
    property string position: "above"

    property int rX: posX * pv.width
    property int rY: rFloorPos * pv.height

    // performance
    property bool highLight: false
    property string soundSource
    property bool requestPTC: false
    property bool requestSound: false



    // other
    // property bool destoried: false
    property JudgeLine judgeLine
    property var pv: judgeLine.pv
    property int currentTime: judgeLine.currentTime

    property bool isCrashed:    false
    property bool isDestoried:  false
    property bool isCompleted:  false

    // signals
    signal crashed()



    // on property change
    function checkTypeIndex()
    {
        if(type === "tap"){typeIndex = 0;}
        else if(type === "drag"){typeIndex = 1;}
        else if(type === "flick"){typeIndex = 2;}
        else if(type === "hold"){typeIndex = 3;}
        else
        {
            typeIndex = 0;
            type = "tap";
        }
        checkHighLight();

    }
    onTypeChanged: checkTypeIndex();



    onRequestSoundChanged: {
        if(requestSound)
        {
            pv.playNoteSound(typeIndex);
            requestSound = false;
        }
    }

    onCurrentTimeChanged: {
        if( (time - currentTime) <= 0 && !isCrashed && isCompleted)
        {
            crash();
        }
        else if( (time - currentTime) >= 0 && isCrashed)
        {
            isCrashed = false;
        }
    }

    // Component
    Component.onCompleted: {
        isCompleted = true;
        checkTypeIndex();
    }


    // we need property highLight to set typeIndex
    function checkHighLight()
    {
        if(highLight){typeIndex += 4;}
    }
    onHighLightChanged: checkTypeIndex();// not to judge falsely


    // other function
    function crash()
    {
        crashed();
        note.isCrashed      = true;
        note.requestPTC     = true;
        note.requestSound   = true;
    }

    function selfDestory()
    {
        destroy(500);
        isDestoried = true;
    }

}
