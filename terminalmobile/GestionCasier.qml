import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

/**
  *
  * @file terminalmobile/GestionCasier.qml
  *
  * @brief Définition de la boîte de dialogue GestionCasier
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class GestionCasier
  *
  * @brief La boîte de dialogue GestionCasier
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

Dialog {
    //title: "" // voir labelTitre
    modal: true // garde le controle
    //standardButtons: Dialog.Ok | Dialog.Cancel // boutons standards d'un Dialog

    /**
      * @brief Conteneur des éléments de la page qml GestionCasier
      */
    Column {
        id: edition
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 50

        /**
          * @brief Conteneur du texte labelTitre
          */
        Row {
            id: ligneTitre
            anchors.horizontalCenter: parent.horizontalCenter

            /**
              * @brief titre de la boîte de dialogue
              */
            Text {
                id: labelTitre;
                text: qsTr("Casier")
                elide: Text.ElideMiddle
                font.bold: true
                font.pixelSize: Qt.application.font.pixelSize * 1.5
            }
        }

        /**
          * @brief Conteneur des boutons boutonAjouter et boutonAnnuler
          */
        Row {
            id: boutons
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            /**
              * @brief Bouton pour ajouter une armoire
              */
            Button {
                id: boutonAjouter
                //width: window.width / 8
                //height: window.height / 16
                text: qsTr("Ajouter")
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                onClicked: {

                    // Ok
                    accept()
                }
            }

            /**
              * @brief Bouton pour revenir a la page IHMPrincipale
              */
            Button {
                id: boutonAnnuler
                //width: window.width / 8
                //height: window.height / 16
                text: qsTr("Annuler")
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                onClicked: {

                    // Annuler
                    reject()
                }
            }
        }
    }

    /**
      * @brief pied de page
      */
    footer: Label {
        width: Screen.desktopAvailableWidth
        horizontalAlignment: Qt.AlignRight
        padding: 10
        text: qsTr("© e-stock 2019 <rgauthier2510@gmail.com>")
        font.pixelSize: Qt.application.font.pixelSize * 0.8
        font.italic: true
    }
}
