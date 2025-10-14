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
                    name: "back"

                    PropertyChanges {
                        btnMenu {
                            visible: false
                        }

                        btnNav {
                            text: qsTr("Go Back")

                            onClicked: {
                                state = "";
                                stack.pop();
                            }
                        }
                    }
                }
            ]

            onClicked: {
                state = "back";
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

        MenuItem {
            text: qsTr("Settings")

            onClicked: {
                btnNav.state = "back";
                stack.push(settingsView);
            }
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
            parentHeight: height
            parentWidth: width
        }
    }

    Component {
        id: settingsView

        SettingsView {
            parentWidth: width
            width: Math.min(parent.width, 250)
        }
    }
}
