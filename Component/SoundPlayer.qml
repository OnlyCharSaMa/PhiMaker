import QtQuick 2.0
import QtMultimedia 5.12

Item {
    property int playerCount: 50
    property var players: [tapPlayers, dragPlayers, flickPlayers, tapPlayers, tapPlayers, dragPlayers, flickPlayers, tapPlayers]
    property var tapPlayers: []
    property var dragPlayers: []
    property var flickPlayers: []




    Component {
        id: player
        Audio {
            property bool isBusy: false
            autoLoad: true
            notifyInterval: 100
            onPlaying: isBusy = true;
            onStopped: isBusy = false;
            onPaused:  isBusy = false;
        }
    }

    Component.onCompleted: {
        for(var i = 0; i < playerCount; i++)
        {
            var temp_player = player.createObject(this);
            temp_player.source = "qrc:/res/phi/sound/Tap.wav";
            tapPlayers.push(temp_player);
        }

        for(var j = 0; j < playerCount; j++)
        {
            var temp_player1 = player.createObject(this);
            temp_player1.source = "qrc:/res/phi/sound/Drag.wav";
            dragPlayers.push(temp_player1);
        }

        for(var m = 0; m < playerCount; m++)
        {
            var temp_player2 = player.createObject(this);
            temp_player2.source = "qrc:/res/phi/sound/Flick.wav";
            flickPlayers.push(temp_player2);
        }
    }

    function play(typeIndex)
    {
        for(var player of players[typeIndex+1])
        {
            if(player.availability === MediaPlayer.Busy)
            {
                player.play();
                break;
            }
        }
    }
}
