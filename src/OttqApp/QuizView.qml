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

        onAvailabilityChanged: {
            if (isAvailable) {
                answerInput.state = "available";
                return;
            }
            answerInput.state = "";
            answerInput.text = "";
        }
        onQuestionChanged: question => {
            answerInput.text = "";
            tts.enqueue(question);
        }
        onQuizCompleted: {
            answerInput.state = "completed";
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
        enabled: false
        focus: false
        font.bold: true
        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: qsTr("Unavailable")

        states: [
            State {
                name: "available"

                PropertyChanges {
                    answerInput {
                        enabled: true
                        focus: true
                        placeholderText: qsTr("Result")
                    }
                }
            },
            State {
                name: "completed"

                PropertyChanges {
                    answerInput {
                        enabled: false
                        focus: false
                        placeholderText: qsTr("Completed")
                        text: ""
                    }
                }
            }
        ]

        onFocusChanged: {
            if (!focus)
                return;
            if (inputMethodHints != Qt.ImhDigitsOnly) {
                inputMethodHints = Qt.ImhDigitsOnly;
                // calls forceActiveFocus()
            } else {
                forceActiveFocus();
            }
        }
        onInputMethodHintsChanged: {
            if (focus && inputMethodHints == Qt.ImhDigitsOnly)
                forceActiveFocus();
        }
        onTextChanged: quizBackend.check(text)
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

    ProgressBar {
        id: progressBarTtsLoading

        anchors.centerIn: parent
        indeterminate: true
        visible: true
        width: parent.width - 2 * 10
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
        // The quiz should get started after the tts becomes available the
        // first time. Otherwise enqueueing the first question, in case of an
        // initial error state, would not be possible.

        function onStateChanged() {
            if (tts.state == TextToSpeech.Ready) {
                quizBackend.startQuiz(QuizConfiguration.timesTables, QuizConfiguration.minFactor, QuizConfiguration.maxFactor);
                target = null; // Call once.
            }
        }

        target: tts
    }

    Connections {
        function onAboutToSynthesize() {
            tts.setUp();
            target = null; // Will be called only once.
        }

        target: tts
    }

    Connections {
        function onStateChanged() {
            if (tts.state == TextToSpeech.Speaking) {
                progressBarTtsLoading.visible = false;
                target = null; // Call once.
            }
        }

        target: tts
    }
}
