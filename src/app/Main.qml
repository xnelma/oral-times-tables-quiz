pragma ComponentBehavior: Bound
import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ApplicationWindow {
    id: root

    property QuizView quizViewInst
    property SetupView setupViewInst

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
                if (!root.quizViewInst.visible)
                    root.quizViewInst.visible = true;
                var p = {
                    "config": root.setupViewInst.config
                };
                stack.push(root.quizViewInst, p);
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

    Component.onCompleted: {
        // Keep state of quiz view for faster navigation.
        var properties = {
            parentHeight: stack.height,
            parentWidth: stack.width,
            visible: false
        };
        const incubator = quizView.incubateObject(root, properties);
        if (incubator.status === Component.Ready) {
            quizViewInst = incubator.object;
            return;
        }
        incubator.onStatusChanged = function (status) {
            if (status == Component.Ready) {
                quizViewInst = incubator.object;
            }
        };
    }
    onClosing: close => {
        if (Qt.platform.os === "android" || Qt.platform.os === "ios") {
            if (stack.depth > 1) {
                close.accepted = false;
                btnNav.state = "";
                stack.pop();
            } else {
                close.accepted = true;
            }
        } else {
            close.accepted = true;
        }
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
            Component.onCompleted: {
                root.setupViewInst = this;
            }
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
