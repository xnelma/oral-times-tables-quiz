import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtTextToSpeech

Item {
    Button {
        // for trying out tts
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: tts.state == TextToSpeech.Ready
        text: "Say '2 x 21'"

        onClicked: tts.say(Backend.getQuestion())
    }

    TextToSpeech {
        id: tts

        function setUp() {
            // TODO if translation available
            tts.locale = Qt.locale("de");
        }
    }

    Connections {
        function onAboutToSynthesize() {
            tts.setUp();
            target = null;
        }

        target: tts
    }
}
