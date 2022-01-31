import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

/**
  *
  * @file terminalmobile/AjoutArmoire.qml
  *
  * @brief Définition de la boîte de dialogue AjoutArmoire
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class AjoutArmoire
  *
  * @brief La boîte de dialogue AjoutArmoire
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

Dialog {
    //title: "Ajouter une armoire" // voir labelTitre
    modal: true // garde le controle
    //standardButtons: Dialog.Ok | Dialog.Cancel // boutons standards d'un Dialog

    /**
      * @brief Conteneur des éléments de la page qml AjoutArmoire
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
                text: qsTr("Ajouter une armoire")
                elide: Text.ElideMiddle
                font.bold: true
                font.pixelSize: Qt.application.font.pixelSize * 1.5
            }
        }

        /**
          * @brief Conteneur des éléments labelNomArmoire et saisieNomArmoire
          */
        Row {
            id: ligneNomArmoire
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelNomArmoire
                text: qsTr("Nom :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'armoire
              */
            TextField {
                id: saisieNomArmoire
                focus: true
                text: nomNouvelleArmoire
                //placeholderText: "Nom armoire"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        /**
          * @brief Conteneur des éléments labelAdresseIP et saisieAdresseIP
          */
        Row {
            id: ligneAdresseIP
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelAdresseIP
                text: qsTr("Adresse IP :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie de l'adresse IP de l'armoire
              */
            TextField {
                id: saisieAdresseIP
                text: adresseIPNouvelleArmoire
                //placeholderText: "Adresse IP"
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
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
                    nomNouvelleArmoire = saisieNomArmoire.text
                    adresseIPNouvelleArmoire = saisieAdresseIP.text
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
                    nomNouvelleArmoire = ""
                    adresseIPNouvelleArmoire = ""
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
