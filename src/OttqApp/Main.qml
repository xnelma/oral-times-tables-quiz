import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ApplicationWindow {
    id: root

    title: qsTr("Oral Times Tables Quiz")
    visible: true

    footer: ToolBar {
        ToolButton {
            id: btnNav

            anchors.fill: parent
            text: qsTr("Start")

            states: [
                State {
                    name: "running"

                    PropertyChanges {
                        btnMenu {
                            visible: false
                        }

                        btnNav {
                            text: qsTr("Complete")

                            onClicked: {
                                state = "";
                                stack.pop();
                            }
                        }
                    }
                }
            ]

            onClicked: {
                state = "running";
                stack.push(quizView);
            }
        }
    }
    header: ToolBar {
        id: tbHeader

        RowLayout {
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignLeft
                opacity: 0.75
                text: qsTr("Oral Times Tables Quiz")
                verticalAlignment: Qt.AlignVCenter
            }

            ToolButton {
                id: btnMenu

                property real leftMargin: parent.width - menu.width

                text: qsTr("Menu")

                onClicked: menu.popup(leftMargin, 0)
            }
        }
    }

    Backend {
        id: backend

    }

    Dialog {
        id: dlgAbout

        anchors.centerIn: parent
        modal: true
        standardButtons: Dialog.Ok
        title: qsTr("About")
    }

    Menu {
        id: menu

        MenuItem {
            text: qsTr("About")

            onClicked: dlgAbout.open()
        }
    }

    StackView {
        id: stack

        anchors.fill: parent
        initialItem: setupView
    }

    Component {
        id: setupView

        SetupView {
        }
    }

    Component {
        id: quizView

        QuizView {
        }
    }
}
