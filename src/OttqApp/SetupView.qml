import QtQuick
import QtQuick.Controls.Basic

Item {
    Column {
        anchors.centerIn: parent
        spacing: 10

        SetupViewSectionTitle {
            anchors.horizontalCenter: parent.horizontalCenter
            subtitle: qsTr("Add a number") // Or the number list if not empty.
            title: qsTr("Times Tables:")
        }

        Item {
            height: timesTableNumber.height + 10 + btnAddTimesTable.height
            width: parent.width

            SpinBox {
                id: timesTableNumber

                anchors.horizontalCenter: parent.horizontalCenter
                value: timesTableNumberDecimalStep.value
            }

            Slider {
                id: timesTableNumberDecimalStep

                anchors.bottom: btnAddTimesTable.bottom
                anchors.left: timesTableNumber.right
                anchors.leftMargin: 5
                anchors.top: timesTableNumber.top
                from: 90
                height: parent.height
                orientation: Qt.Vertical
                stepSize: 10
                to: 10
            }

            Button {
                id: btnAddTimesTable

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.left: timesTableNumber.left
                anchors.top: timesTableNumber.bottom
                anchors.topMargin: 10
                text: qsTr("Add")
                width: timesTableNumber.width

                onClicked: console.log(timesTableNumber.value)
            }
        }

        MenuSeparator {
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SetupViewSectionTitle {
            anchors.horizontalCenter: parent.horizontalCenter
            subtitle: "[%1, %2]".arg(factorRange.low).arg(factorRange.high)
            title: qsTr("Factors:")
        }

        RangeSlider {
            id: factorRange

            property int high: Math.round(second.value)
            property int low: Math.round(first.value)

            anchors.horizontalCenter: parent.horizontalCenter
            first.value: 10
            from: 2
            second.value: 20
            snapMode: RangeSlider.SnapAlways
            stepSize: 1
            to: 100

            first.onMoved: console.log(low)
            second.onMoved: console.log(high)
        }
    }
}
