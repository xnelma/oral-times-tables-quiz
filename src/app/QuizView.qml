import OttqApp
import QtQuick
import QtQuick.Controls.Basic

FocusScope {
    id: qRoot

    required property int parentHeight
    required property int parentWidth

    height: parentHeight
    state: quizBackend.state
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
    }
    StackView.onDeactivated: {
        quizBackend.stopStateMachine();
    }

    QuizBackend {
        id: quizBackend

        onQuestionChanged: {
            answerInput.text = "";
        }
        onShowLocaleError: {
            dlgLocaleError.open();
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
        onTextChanged: quizBackend.check(text)
    }

    Button {
        id: btnReplay

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: qRoot.parentHeight / 3
        text: qsTr("Replay")

        onClicked: {
            quizBackend.sayQuestion();
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
        id: labelLocale

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        opacity: 0.5
        text: quizBackend.localeName
    }
}
