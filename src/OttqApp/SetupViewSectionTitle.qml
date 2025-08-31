import QtQuick

Column {
    id: stRoot

    required property string subtitle
    required property string title

    spacing: 2

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#888"
        text: stRoot.title
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        text: stRoot.subtitle
    }
}
