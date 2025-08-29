import OttqApp
import QtQuick
import QtQuick.Controls.Basic

Item {
    id: sRoot

    required property int parentWidth

    SettingsBackend {
        id: settingsBackend

    }

    Column {
        padding: 10
        spacing: 10
        width: parent.width

        Label {
            opacity: 0.5
            text: qsTr("Text-to-Speech Settings")
        }

        Row {
            spacing: 10

            Label {
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideRight
                maximumLineCount: 2
                opacity: switchTtsLocale.checked ? 1 : 0.5
                text: settingsBackend.autoLocaleName
                width: sRoot.parentWidth - switchTtsLocale.width - 3 * 10
                wrapMode: Text.WordWrap
            }

            Switch {
                id: switchTtsLocale

                anchors.verticalCenter: parent.verticalCenter
                checked: settingsBackend.useAutoTtsLanguage

                onToggled: settingsBackend.useAutoTtsLanguage = checked
            }
        }

        ComboBox {
            currentIndex: settingsBackend.languageIndex
            enabled: !switchTtsLocale.checked
            model: settingsBackend.languages
            width: parent.width - 2 * parent.padding

            onActivated: settingsBackend.languageIndex = currentIndex
        }
    }
}
