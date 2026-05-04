import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtTextToSpeech
import QtQml

FocusScope {
    id: qRoot

    property quizConfiguration config
    property string questionBase: "%1 times %2"

    signal showLocaleError

    function check(answer: string) {
        if (answer === "")
            return;

        if (quiz.answerIsCorrect(parseInt(answer)))
            nextQuestion();
    }

    function nextQuestion() {
        if (quiz.next()) {
            qRoot.sayQuestion();
        } else {
            // Let last question fade out instead of stopping it.
            quizBackend.quizCompleted();
        }
    }

    function sayQuestion() {
        var q = quiz.question();
        var qStr = qRoot.questionBase.arg(q.number).arg(q.factor);
        // Stop current question and start next right away instead of
        // enqueueing. This way the quiz is more snappy.
        if (tts.state === TextToSpeech.Speaking) {
            tts.stop();
            tts.say(qStr);
        } else {
            // Enqueue in case tts is not ready for reasons other than
            // currently speaking.
            tts.enqueue(qStr);
        }
    }

    state: quizBackend.state

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
            extend: "unavailable"
            name: "setting-up"

            PropertyChanges {
                answerInput {
                    placeholderText: qsTr("Setting Up")
                }

                progressBarTtsLoading {
                    visible: true
                }

                labelLocale {
                    text: ""
                }
            }
        },
        State {
            extend: "setting-up"
            name: "tts-loading"

            PropertyChanges {
                answerInput {
                    placeholderText: qsTr("Text-to-Speech Loading")
                }
            }
        },
        State {
            extend: "setting-up"
            name: "tts-synthesizing"

            PropertyChanges {
                answerInput {
                    placeholderText: qsTr("Text-to-Speech Synthesizing")
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
                    text: ""
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
            extend: "unavailable"
            name: "completed"

            PropertyChanges {
                answerInput {
                    placeholderText: qsTr("Completed")
                    text: ""
                }
            }
        }
    ]

    StackView.onActivated: {
        quizBackend.startStateMachine();
        quiz.setup(qRoot.config);
    }
    StackView.onDeactivated: {
        quizBackend.stopStateMachine();
    }
    onShowLocaleError: {
        dlgLocaleError.open();
    }

    Quiz {
        id: quiz

        onQuestionChanged: {
            answerInput.text = "";
        }
    }

    QuizBackend {
        id: quizBackend

        onFirstQuestion: {
            qRoot.sayQuestion();
        }
        onSetup: {
            tts.setLocale(Qt.locale(quizBackend.localeName));
            tts.setRate(quizBackend.voiceRate);
            if (tts.state === TextToSpeech.Error) {
                // could not set translation
                qRoot.showLocaleError();
            }
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
            var num = quiz.numQuestionsRemaining;
            return num <= 0 ? qsTr("Last question") : num + " " + qsTr("left");
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
        onTextChanged: qRoot.check(text)
    }

    Button {
        id: btnReplay

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: qRoot.height / 3
        text: qsTr("Replay")

        onClicked: {
            qRoot.sayQuestion();
            answerInput.focus = true;
        }
    }

    // Text-to-Speech:

    Dialog {
        id: dlgLocaleError

        anchors.centerIn: parent
        margins: 10
        modal: true
        standardButtons: Dialog.Ok
        title: qsTr("Language Error")

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
        id: labelLocale

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        opacity: 0.5
        text: quizBackend.localeName
    }

    TextToSpeech {
        id: tts

        onStateChanged: {
            if (state === TextToSpeech.Ready)
                quizBackend.ttsReady();
            else if (state === TextToSpeech.Speaking)
                quizBackend.ttsSpeaking();
            else if (state === TextToSpeech.Error)
                quizBackend.ttsError();
        }
    }
}
