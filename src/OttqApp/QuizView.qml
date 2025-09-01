import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtTextToSpeech

FocusScope {
    id: qRoot

    required property int parentHeight
    required property int parentWidth

    height: parentHeight
    width: parentWidth

    QuizBackend {
        id: quizBackend

        Component.onCompleted: {
            startQuiz(QuizConfiguration.timesTables, QuizConfiguration.minFactor, QuizConfiguration.maxFactor);
        }
    }

    // Times Tables:

    Label {
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        opacity: 0.5
        text: {
            var num = quizBackend.numQuestionsRemaining;
            return num <= 0 ? "" : num + " " + qsTr("left");
        }
    }

    TextArea {
        id: answerInput

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: qRoot.parentHeight / 3
        focus: true
        font.bold: true
        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: qsTr("Result")

        onInputMethodHintsChanged: {
            forceActiveFocus();
        }
    }

    // Text-to-Speech:

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
            tts.rate = quizBackend.voiceRate;

            // If the locale is not available, the property won't change.
            if (tts.locale.name != quizBackend.localeName) {
                quizBackend.isAvailable = false;
                dlgLocaleError.open();
            }
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
