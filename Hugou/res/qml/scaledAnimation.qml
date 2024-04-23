import QtQuick 2.15
import QtQuick.Controls 2.15
import HugouModules 1.0

Item {
    PropertyAnimation {
        id: restoreAnimation
        target: mainWindow
        property: "geometry"
        duration: 300
        to: generalGeometry
        easing.type: Easing.OutCirc
    }

    PropertyAnimation {
        id: maximumAnimation
        target: mainWindow
        property: "geometry"
        duration: 300
        to: maximumGeometry
        easing.type: Easing.OutCirc
    }

    function startRestoreAnimation() {
        restoreAnimation.running = true;
    }

    function startMaximumAnimation() {
        maximumAnimation.running = true;
    }
}
