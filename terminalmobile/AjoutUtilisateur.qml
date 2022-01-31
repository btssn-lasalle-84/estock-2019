import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

/**
  *
  * @file terminalmobile/AjoutUtilisateur.qml
  *
  * @brief Définition de la boîte de dialogue AjoutUtilisateur
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class AjoutUtilisateur
  *
  * @brief La boîte de dialogue AjoutUtilisateur
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

Dialog {
    id: pageAjoutUtilisateur
    //title: "Ajouter un Utilisateur" // voir labelTitre
    modal: true // garde le controle
    //standardButtons: Dialog.Ok | Dialog.Cancel // boutons standards d'un Dialog

    onOpened: {
        var retourprofil = g_pUtilisateursArmoire.lireProfil()
        console.log("retour : " + retourprofil)
        var retourgroupe = g_pUtilisateursArmoire.lireGroupe()
        console.log("retour : " + retourgroupe)
    }


    /**
      * @brief Conteneur des éléments de la page qml AjoutArmoire
      */
    Column {
        id: edition
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 15

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
                text: qsTr("Ajouter un Utilisateur")
                elide: Text.ElideMiddle
                font.bold: true
                font.pixelSize: Qt.application.font.pixelSize * 1.5
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_nomProfil
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_nomProfil
                text: qsTr("Profil :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Liste déroulante du Profil
              */
            ComboBox {
                id: listeProfil
                focus: true
                width: saisiem_nom.implicitWidth
                currentIndex: 0 // par défaut le premier élément
                //text: idProfil
                //placeholderText: "Nom armoire"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
                textRole: "m_nom" // affichage du champ de l'élement sélectionné
                model: g_pUtilisateursArmoire.listeProfil
                /*delegate: ItemDelegate { // personnalisation de l'affichage du modèle dans la liste déroulante
                    width: listeProfil.width
                    contentItem: Text {
                        text: model.modelData.m_nomProfil
                        font: parent.font
                    }
                    highlighted: listeChoixArmoire.highlightedIndex === index
                }*/
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_nomGroupe
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_nomGroupe
                text: qsTr("Groupe :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'idGroupe
              */
            ComboBox {
                id: listeGroupe
                focus: true
                width: saisiem_nom.implicitWidth
                currentIndex: 0 // par défaut le premier élément
                //text: idGroupe
                //placeholderText: "Nom armoire"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
                textRole: "m_nom" // affichage du champ de l'élement sélectionné
                model: g_pUtilisateursArmoire.listeGroupe
                /*delegate: ItemDelegate { // personnalisation de l'affichage du modèle dans la liste déroulante
                    width: listeGroupe.width
                    contentItem: Text {
                        text: model.modelData.m_nomGroupe
                        font: parent.font
                    }
                    highlighted: listeChoixArmoire.highlightedIndex === index
                }*/
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_nom
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_nom
                text: qsTr("Nom :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'armoire
              */
            TextField {
                id: saisiem_nom
                focus: true
                //text: m_nom
                placeholderText: "Nom"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_prenom
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_prenom
                text: qsTr("Prénom :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'armoire
              */
            TextField {
                id: saisiem_prenom
                focus: true
                //text: m_prenom
                placeholderText: "Prénom"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_dateDeValidite
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_dateDeValidite
                text: qsTr("DateValidité :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'armoire
              */
            TextField {
                id: saisiem_dateDeValidite
                focus: true
                //text: m_dateDeValidite
                placeholderText: "Date validité"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_identifiant
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_identifiant
                text: qsTr("Identifiant :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'armoire
              */
            TextField {
                id: saisiem_identifiant
                focus: true
                //text: m_identifiant
                placeholderText: "Identifiant"
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        /**
          * @brief Conteneur des éléments ligneidUtilisateur et saisieidUtilisateur
          */
        Row {
            id: lignem_badge
            anchors.right: parent.right
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelm_badge
                text: qsTr("Badge :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom de l'armoire
              */
            TextField {
                id: saisiem_badge
                focus: true
                //text: m_badge
                placeholderText: "Badge"
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
                    idProfil = g_pUtilisateursArmoire.listeProfil[listeProfil.currentIndex].m_id
                    idGroupe = g_pUtilisateursArmoire.listeGroupe[listeGroupe.currentIndex].m_id
                    nomUtilisateur = saisiem_nom.text
                    prenomUtilisateur = saisiem_prenom.text
                    dateValidite = saisiem_dateDeValidite.text
                    identifiant = saisiem_identifiant.text
                    badge = saisiem_badge.text
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
                    pageAjoutUtilisateur.visible = false
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
