import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.1

/**
  *
  * @file terminalmobile/MouvementsArmoire.qml
  *
  * @brief Définition de la page des mouvements
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class MouvementsArmoire
  *
  * @brief La page des mouvements d'une armoire
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  * @brief page des mouvements d'une armoire
  */
Page {
    id: pageMouvementsArmoire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("Mouvements Armoire")
    //visible: true

    onVisibleChanged: {
        if (visible)
            g_pMouvements.lire()
    }

    /**
      * @brief Conteneur du texte labelTitre
      */
    Row {
        id: ligneTitre
        anchors.horizontalCenterOffset: 0
        anchors.top: parent.top
        anchors.topMargin: 10
        spacing: 0
        anchors.horizontalCenter: parent.horizontalCenter

        /**
          * @brief titre de la boîte de dialogue
          */
        Text {
            id: labelTitre;
            text: qsTr("Mouvements de l'armoire")
            elide: Text.ElideMiddle
            font.bold: true
            font.pixelSize: Qt.application.font.pixelSize * 1.5
        }
    }
    Row {
        id: row
        anchors.top: rowButton.bottom
        anchors.topMargin: 10
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: rowButton.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 0

        TableView {
            id: vueMouvement
            width: Screen.desktopAvailableWidth * 0.85
            height: Screen.desktopAvailableHeight * 0.75
            opacity: 1
            model: g_pMouvements.listeMouvements

            TableViewColumn {
                role: "m_casier"
                title: "Casier"
                width: vueMouvement.width * 0.1
            }
            TableViewColumn {
                role: "m_horodatage"
                title: "Date / Heure"
                width: vueMouvement.width * 0.18
            }
            TableViewColumn {
                role: "m_utilisateur"
                title: "Utilisateur"
                width: vueMouvement.width * 0.20
            }
            TableViewColumn {
                role: "m_action"
                title: "Action"
                width: vueMouvement.width * 0.1
            }
            TableViewColumn {
                role: "m_contenu"
                title: "Contenu"
                width: vueMouvement.width * 0.26
            }
            TableViewColumn {
                role: "m_quantite"
                title: "Quantité"
                width: vueMouvement.width / 6
            }
            style: TableViewStyle {
                headerDelegate: Rectangle {
                    height: textItem.implicitHeight * 1.2
                    width: textItem.implicitWidth
                    color: "lightsteelblue"
                    Text {
                        id: textItem
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: styleData.value
                        elide: Text.ElideRight
                        //color: textColor
                    }
                }
                itemDelegate: Rectangle {
                    color: styleData.row ? "transparent" : "#f5f5f5"
                    Text {
                        id: textItemRow
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: styleData.value
                        elide: Text.ElideRight
                        //color: textColor
                        color: {
                            switch(styleData.column)
                            {
                            case 0: // Casier
                                color = "green";
                                break;
                            case 1: // Horodatage
                                color = "blue";
                                break;
                            default:
                                color = "black";
                            }
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Ligne : " + styleData.row);
                            console.log("Colonne : " + styleData.column);
                            console.log("Role : " + styleData.role);
                            console.log("Valeur : " + styleData.value);
                            console.log("Casier : " + g_pMouvements.listeMouvements[styleData.row].m_casier)
                        }
                    }
                }
            }
        }
    }
    Row {
        id: rowButton
        anchors.top: ligneTitre.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Bouton {
            id: boutonRecharger
            text: "Actualiser"
            onClicked: {
                g_pMouvements.lire()
            }
        }
        Bouton {
            id: boutonRetour
            text: qsTr("Retour")
            //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                pageMouvementsArmoire.visible = false
            }
        }
    }
}
