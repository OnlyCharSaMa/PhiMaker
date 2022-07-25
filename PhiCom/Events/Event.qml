import QtQuick 2.12

// Simple data store Component
QtObject {
    id: event
    property var startTime
    property var endTime
    property var start
    property var end
    property real easingType: Easing.Linear
    property real easingAmplitude
    property real easingOvershoot
    property real easingPeriod
    property var easingBezierCurve: []
}
