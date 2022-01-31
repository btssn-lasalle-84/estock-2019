import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.1

/**
  *
  * @file terminalmobile/MenuArmoire.qml
  *
  * @brief Définition de la page de gestion d'une armoire
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class MenuArmoire
  *
  * @brief La page de gestion d'une armoire
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  * @brief page de la gestion de l'Armoire
  */
Page {
    //id: pageMenuArmoire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("Armoire")
    property string utilisateur: ""
    property string armoire: ""

    ColumnLayout {
        id: columnLayout
        anchors.horizontalCenterOffset: 0
        anchors.top: parent.top
        anchors.topMargin: 150
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 25

        Text {
            id: labelArmoire
            text: armoire
            elide: Text.ElideMiddle
            font.pixelSize: Qt.application.font.pixelSize * 1.2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: button
            Layout.fillWidth: true
            text: qsTr("Consulter le stock")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                pageStockArmoire.visible = true
            }
        }

        Button {
            id: button1
            Layout.fillWidth: true
            text: qsTr("Consulter les mouvements")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                pageMouvementsArmoire.visible = true
            }
        }

        /*Button {
            id: button3
            Layout.fillWidth: true
            text: qsTr("Gérer les casiers")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }*/

        Button {
            id: button4
            Layout.fillWidth: true
            text: qsTr("Gérer les utilisateurs")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                pageUtilisateursArmoire.visible = true
            }
        }

        Button {
            id: button5
            text: qsTr("Retour")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                pageMenuArmoire.visible = false
            }
        }
    }

    StockArmoire {
        id: pageStockArmoire
        visible: false
    }

    MouvementsArmoire {
        id: pageMouvementsArmoire
        visible: false
    }

    UtilisateursArmoire {
        id: pageUtilisateursArmoire
        visible: false
    }
}
