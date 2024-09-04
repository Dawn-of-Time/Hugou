import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia

Item {
    width: 240
    height: 240

    MediaPlayer {
        id: mediaPlayer
        source: "../mp4/applyTheme.mp4"
        autoPlay: true
        loops: -1
        videoOutput: videoOutput
    }  

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }
}
