import OttqApp
import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: suRoot

    property quizConfiguration config

    Column {
        anchors.centerIn: parent
        spacing: 10

        SetupViewSectionTitle {
            anchors.horizontalCenter: parent.horizontalCenter
            subtitle: {
                var numbers = suRoot.config.timesTablesStr;
                return numbers === "" ? qsTr("Add a number") : numbers;
            }
            title: qsTr("Times Tables:")
        }

        Item {
            height: timesTableNumber.height + 10 + btnAddTimesTable.height
            width: parent.width

            SpinBox {
                id: timesTableNumber

                anchors.horizontalCenter: parent.horizontalCenter
                from: 1
                to: 100
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

                onClicked: {
                    suRoot.config.addTimesTable(timesTableNumber.value);
                }
            }
        }

        MenuSeparator {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
        }

        GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3
            rowSpacing: 2
            rows: 2
            width: parent.width

            RoundButton {
                Layout.column: 0
                Layout.preferredHeight: factorRangeTitle.height / 2
                Layout.row: 0
                flat: true
                text: "+"

                onClicked: {
                    factorRange.first.increase();
                    factorRange.first.moved();
                }
            }

            RoundButton {
                Layout.column: 0
                Layout.preferredHeight: factorRangeTitle.height / 2
                Layout.row: 1
                flat: true
                text: "-"

                onClicked: {
                    factorRange.first.decrease();
                    factorRange.first.moved();
                }
            }

            SetupViewSectionTitle {
                id: factorRangeTitle

                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.column: 1
                Layout.row: 0
                Layout.rowSpan: 2
                subtitle: "[%1, %2]".arg(factorRange.low).arg(factorRange.high)
                title: qsTr("Factors:")
            }

            RoundButton {
                Layout.alignment: Qt.AlignRight
                Layout.column: 2
                Layout.preferredHeight: factorRangeTitle.height / 2
                Layout.row: 0
                flat: true
                text: "+"

                onClicked: {
                    factorRange.second.increase();
                    factorRange.second.moved();
                }
            }

            RoundButton {
                Layout.alignment: Qt.AlignRight
                Layout.column: 2
                Layout.preferredHeight: factorRangeTitle.height / 2
                Layout.row: 1
                flat: true
                text: "-"

                onClicked: {
                    factorRange.second.decrease();
                    factorRange.second.moved();
                }
            }
        }

        RangeSlider {
            id: factorRange

            property int high: Math.round(second.value)
            property int low: Math.round(first.value)

            anchors.horizontalCenter: parent.horizontalCenter
            first.value: suRoot.config.factorRange.min
            from: 1
            second.value: suRoot.config.factorRange.max
            snapMode: RangeSlider.SnapAlways
            stepSize: 1
            to: 100

            first.onMoved: suRoot.config.factorRange.min = low
            second.onMoved: suRoot.config.factorRange.max = high
        }
    }
}
