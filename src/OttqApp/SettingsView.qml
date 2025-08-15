import OttqApp
import QtQuick
import QtQuick.Controls.Basic

Item {
    Column {
        padding: 10
        spacing: 10

        Text {
            opacity: 0.5
            text: "Example Settings:"
        }

        Row {
            spacing: 10

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "Setting: "
            }

            Switch {
                anchors.verticalCenter: parent.verticalCenter
                checked: Backend.setting

                onToggled: Backend.setting = checked
            }
        }
    }
}
