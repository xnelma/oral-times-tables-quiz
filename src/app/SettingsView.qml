import OttqApp
import QtQuick
import QtQuick.Controls.Basic

Item {
    id: sRoot

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
                opacity: switchTtsLocale.checked ? 1 : 0.5
                text: {
                    var l = settingsBackend.autoLanguage;
                    return "%1\n(%2)".arg(l.language).arg(l.territory);
                }
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

            onActivated: settingsBackend.languageIndex = currentIndex
        }

        Label {
            text: qsTr("Voice rate:")
        }

        SpinBox {
            from: -10
            textFromValue: function (value) {
                // FIXME causes a binding loop

                var rate = value / 10;
                return Number(rate).toLocaleString(Qt.locale("C"), 'f', 1);
            }
            to: 10
            value: settingsBackend.voiceRate * 10

            onValueChanged: settingsBackend.voiceRate = value / 10
        }
    }
}
