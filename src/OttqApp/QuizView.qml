import QtQuick
import QtTextToSpeech

Item {
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: "Quiz View"
    }

    TextToSpeech {
        id: tts

    }
}
