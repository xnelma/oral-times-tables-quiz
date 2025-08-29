import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtTextToSpeech

Item {
    QuizBackend {
        id: quizBackend

    }

    Dialog {
        id: dlgLocaleError

        anchors.centerIn: parent
        modal: true
        standardButtons: Dialog.Ok
        title: qsTr("Language Error")
        width: parent.width - 2 * 10

        Label {
            elide: Text.ElideRight
            text: qsTr("Language for Text-to-Speech engine not found.")
            width: parent.width
            wrapMode: Text.WordWrap
        }
    }

    Button {
        // for trying out tts
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        enabled: tts.state == TextToSpeech.Ready && quizBackend.isAvailable
        text: "Say '2 x 21'"

        onClicked: tts.say(quizBackend.getQuestion())
    }

    Label {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        opacity: 0.5
        text: quizBackend.localeName
    }

    TextToSpeech {
        id: tts

        function setUp() {
            tts.locale = Qt.locale(quizBackend.localeName);

            // If the locale is not available, the property won't change.
            if (tts.locale.name != quizBackend.localeName) {
                quizBackend.isAvailable = false;
                dlgLocaleError.open();
            }

        // TODO Have a setting for the tts rate
        }
    }

    Connections {
        function onAboutToSynthesize() {
            tts.setUp();
            target = null; // Will be called only once.
        }

        target: tts
    }
}
