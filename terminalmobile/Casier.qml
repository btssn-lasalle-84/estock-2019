import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

/**
  *
  * @file terminalmobile/Casier.qml
  *
  * @brief Définition d'un casier de l'armoire
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

Rectangle {
    property string nomCasier: "";
    property int numeroCasier: 0;
    color: "lightgreen";
    radius: 10.0;
    width: Screen.desktopAvailableWidth / 3
    height: Screen.desktopAvailableHeight / 6    
    visible: false

    Text {
        text: nomCasier
        wrapMode: Text.WordWrap
        font.pixelSize: Qt.application.font.pixelSize * 1.4
        /*anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter*/
        anchors.top: parent.top
        anchors.left: parent.left
        height: parent.height
        width: parent.width
        padding: 5
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(numeroCasier > 0)
            {
                console.log("Casier : " + nomCasier + " (" + numeroCasier + ")")
                dialogueGestionCasier.numeroCasier = numeroCasier
                dialogueGestionCasier.open()
            }
        }
    }
}

