import QtQuick 2.0

Rectangle {
    id: root
    property var centerX: 0
    property var centerY: 0
    property var r: 0

    radius: root.width / 2

    width: 2 * r
    height: 2 * r
    x: centerX - root.width / 2
    y: centerY - root.height / 2
}
