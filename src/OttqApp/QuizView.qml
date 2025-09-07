import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtTextToSpeech

FocusScope {
    id: qRoot

    required property int parentHeight
    required property int parentWidth

    height: parentHeight
    state: "unavailable"
    width: parentWidth

    states: [
        State {
            name: "unavailable"

            PropertyChanges {
                answerInput {
                    enabled: false
                    focus: false
                    placeholderText: qsTr("Unavailable")
                    text: ""
                }

                progressBarTtsLoading {
                    visible: false
                }

                labelNumQuestionsRemaining {
                    visible: false
                }

                btnReplay {
                    visible: false
                }
            }
        },
        State {
            name: "tts-loading"

            PropertyChanges {
                answerInput {
                    enabled: false
                    focus: false
                    placeholderText: qsTr("Text-to-Speech Loading")
                    text: ""
                }

                progressBarTtsLoading {
                    visible: true
                }

                labelNumQuestionsRemaining {
                    visible: false
                }

                btnReplay {
                    visible: false
                }
            }
        },
        State {
            name: "available"

            PropertyChanges {
                answerInput {
                    enabled: true
                    focus: true
                    placeholderText: qsTr("Result")
                }

                progressBarTtsLoading {
                    visible: false
                }

                labelNumQuestionsRemaining {
                    visible: true
                }

                btnReplay {
                    visible: true
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

                progressBarTtsLoading {
                    visible: false
                }

                labelNumQuestionsRemaining {
                    visible: false
                }

                btnReplay {
                    visible: false
                }
            }
        }
    ]

    QuizBackend {
        id: quizBackend

        Component.onCompleted: {
            var ok = quizBackend.setupQuiz(QuizConfiguration.timesTables, QuizConfiguration.minFactor, QuizConfiguration.maxFactor);
            if (!ok) {
                qRoot.state = "unavailable";
            } else if (tts.state == TextToSpeech.Error) {
                qRoot.state = "tts-loading";
                connectionTtsReady.enabled = true;
            } else {
                qRoot.state = "available";
                quizBackend.startQuiz();
            }
        }
        onAvailabilityChanged: {
            if (!isAvailable)
                qRoot.state = "unavailable";
            else if (isAvailable && qRoot.state != "tts-loading")
                qRoot.state = "available";
        }
        onQuestionChanged: {
            answerInput.text = "";
            tts.enqueue(question);
        }
        onQuizCompleted: {
            qRoot.state = "completed";
        }
    }

    // Times Tables:

    Label {
        id: labelNumQuestionsRemaining

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

        anchors.bottom: btnReplay.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: false
        focus: false
        font.bold: true

        onFocusChanged: {
            // Force active focus.
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

    Button {
        id: btnReplay

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: qRoot.parentHeight / 3
        enabled: tts.state == TextToSpeech.Ready
        text: qsTr("Replay")

        onClicked: {
            tts.enqueue(quizBackend.question);
            answerInput.focus = true;
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

    ProgressBar {
        id: progressBarTtsLoading

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: answerInput.bottom
        anchors.topMargin: 10
        indeterminate: true
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
        id: connectionTtsReady

        function onStateChanged() {
            if (tts.state == TextToSpeech.Ready) {
                quizBackend.startQuiz();
                target = null; // Start quiz only once.
            }
        }

        enabled: false
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
                qRoot.state = quizBackend.isAvailable ? "available" : "unavailable";
                target = null; // Call once.
            }
        }

        target: tts
    }
}
