import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.1
import QtQuick.Extras 1.4

/**
  *
  * @file terminalmobile/IHMPrincipale.qml
  *
  * @brief Définition de la fenêtre principale de l'application terminal mobile
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class IHMPrincipale
  *
  * @brief La fenêtre principale de l'application
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

ApplicationWindow {
    id: ihmPrincipale
    title: ("E-stock")
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    visible: true
    property bool debug: true
    property string bddArmoireBaseName: "e-stock"
    property string bddArmoireUsername: "estock"
    property string bddArmoirePassword: "password"
    property string adresseIPArmoire: ""

    /**
      * @brief Menu de la fenêtre principale
      */
    header: ToolBar {
        Label {
            text: ("Projet e-stock 2019")
            anchors.centerIn: parent
        }
    }

    /**
      * @brief Conteneur des éléments de l'IHMPrincipale
      */
    Column {
        id: colonneChoixArmoire
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 30

        Row {
            id: logoProjet
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Image {
                id: logo
                width: 216
                height: 108
                source: "logo.png"
            }

            /*Text {
                id: nomProjet
                text: qsTr("E-Stock")
                font.family: "Courier"
                font.pixelSize: Qt.application.font.pixelSize * 2
            }*/
        }
        /**
          * @brief Conteneur des éléments listeChoixArmoire et labelChoixArmoire
          */
        Row {
            id: ligneChoixArmoire
            anchors.right: parent.right
            spacing: 20

            Text {
                id: labelChoixArmoire
                text: qsTr("Armoire :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Liste déroulante des armoires enregistrées
              */
            ComboBox {
                id: listeChoixArmoire
                width: Screen.desktopAvailableWidth / 4
                height: Screen.desktopAvailableHeight / 20
                currentIndex: 0 // par défaut le premier élément
                textRole: "m_nom" // affichage du champ de l'élement sélectionné
                model: g_pArmoires.listeArmoires
                delegate: ItemDelegate { // personnalisation de l'affichage du modèle dans la liste déroulante
                    width: listeChoixArmoire.width
                    contentItem: Text {
                        text: model.modelData.m_nom + " (" + model.modelData.m_adresseIP + ")"
                        font: parent.font
                    }
                    highlighted: listeChoixArmoire.highlightedIndex === index
                }
            }
            /**
              * @brief Bouton pour ajouter une armoire
              */
            Button {
                id: boutonAjouterArmoire
                text: qsTr("Ajouter")
                spacing: 4
                width: implicitWidth * 1.2
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                onClicked: {
                    // ouvre la boîte de dialogue AjoutArmoire
                    dialogueAjoutArmoire.open()
                }
            }

            /**
              * @brief Bouton pour supprimer l'armoire selectionnée
              */
            Button {
                id: boutonSupprimer
                text: qsTr("Supprimer")
                width: implicitWidth * 1.2
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                onClicked: {
                    // supprimer l'armoire sélectionnée
                    g_pArmoires.supprimer(listeChoixArmoire.currentText, g_pArmoires.listeArmoires[listeChoixArmoire.currentIndex].m_adresseIP);
                }
            }
        }

        /**
          * @brief Conteneur des éléments labelUtilisateur et saisieUtilisateur
          */
        Row {
            id: ligneUtilisateur
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Text {
                id: labelUtilisateur
                text: qsTr("Utilisateur :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du nom d'utilisateur
              */
            TextField {
                id: saisieUtilisateur
                width: ihmPrincipale.width / 6
                text: "gauthier.r"
                inputMethodHints: Qt.ImhNoAutoUppercase // Qt::ImhLowercaseOnly
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        /**
          * @brief Conteneur des éléments labelMotDePasse et saisieMotDePasse
          */
        Row {
            id: ligneMotDePasse
            anchors.right: ligneUtilisateur.right
            //anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            /**
              * @brief
              */
            Text {
                id: labelMotDePasse
                text: qsTr("Mot de passe :")
                elide: Text.ElideMiddle
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }

            /**
              * @brief Zone de saisie du mot de passe
              */
            TextField {
                id: saisieMotDePasse
                width: ihmPrincipale.width / 6
                echoMode: TextInput.Password
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                anchors.verticalCenter: parent.verticalCenter
            }
        }        

        /**
          * @brief Conteneur des boutons boutonAjouterArmoire et boutonSelectionArmoire
          */
        Row {
            id: ligneConnexion
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            /**
              * @brief Bouton pour selectionner une armoire
              */
            Button {
                id: boutonConnecterArmoire
                text: qsTr("Se connecter")
                width: implicitWidth * 1.2
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                onClicked: {
                    var adresseIP = g_pArmoires.listeArmoires[listeChoixArmoire.currentIndex].m_adresseIP
                    if(debug)
                    {
                        console.log("Armoire : " + listeChoixArmoire.currentText)
                        console.log("Adresse IP : " + adresseIP)
                        console.log("Utilisateur : " + saisieUtilisateur.text)
                        console.log("Mot de passe : " + saisieMotDePasse.text)
                    }

                    if ((adresseIP !== "") && (saisieUtilisateur.text != ""))
                    {
                        indicateur.running = true;
                        // Par précaution, si on est déjà connecté alors on se déconnecte
                        if (g_pBddArmoire.estConnecte())
                        {
                            g_pBddArmoire.deconnecter();
                        }

                        if (g_pBddArmoire.connecter(bddArmoireBaseName, bddArmoireUsername, bddArmoirePassword, adresseIP))
                        {
                            // DEBUG: Le contrôle du mot de passe est désactivé.
                            //        Penser à remettre à 'false' pour la mise en production réelle.
                            g_pUtilisateurTerminal.lireUtilisateur(saisieUtilisateur.text, saisieMotDePasse.text, true)

                            // Vérification de la validité de l'utilisateur pour cette armoire
                            if (g_pUtilisateurTerminal.estExistant())
                            {
                                if (g_pUtilisateurTerminal.estAutorise())
                                {
                                    pageMenuArmoire.utilisateur = g_pUtilisateurTerminal.Nom + " " + g_pUtilisateurTerminal.Prenom
                                    pageMenuArmoire.armoire = "Armoire : " + listeChoixArmoire.currentText + " (" + adresseIP + ")"
                                    pageMenuArmoire.visible = true
                                    adresseIPArmoire = adresseIP
                                }
                                else
                                {
                                    console.log("Mot de passe incorrect pour l'utilisateur indiqué !")
                                }
                            }
                            else
                            {
                                console.log("Utilisateur inconnu !")
                            }
                        }
                        else
                        {
                            console.log("Impossible de se connecter à la base de données de l'armoire !")
                        }
                        indicateur.running = false;
                    }
                    else
                    {
                        console.log("Impossible d'obtenir la liste des armoires configurée !")
                    }
                }
            }
        }

        Row {
            id: ligneIndicateur
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            BusyIndicator {
                id: indicateur;
                visible: true;
                running: false;
            }
        }
    }

    /**
      * @brief page de menu de l'armoire sélectionnée
      */
    MenuArmoire {
        id: pageMenuArmoire
        visible: false
    }

    /**
      * @brief boîte de dialogue permettant d'ajouter une armoire à la liste
      */
    AjoutArmoire {
        id: dialogueAjoutArmoire
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight - header.height
        property string nomNouvelleArmoire: "";
        property string adresseIPNouvelleArmoire: "";
        onAccepted: { // signal émis par accept()
            if(debug)
            {
                console.log("Nouvelle armoire : " + nomNouvelleArmoire)
                console.log("Adresse IP : " + adresseIPNouvelleArmoire)
            }
            // une nouvelle armoire ?
            if(nomNouvelleArmoire != "" && adresseIPNouvelleArmoire != "")
            {
                // ajoute la nouvelle armoire à la liste
                g_pArmoires.inserer(nomNouvelleArmoire, adresseIPNouvelleArmoire);
                // réinitialise les champs de saisie
                nomNouvelleArmoire = ""
                adresseIPNouvelleArmoire = ""
            }
        }
    }

    /**
      * @brief pied de page
      */
    footer: Label {
        width: parent.width
        horizontalAlignment: Qt.AlignRight
        padding: 10
        text: qsTr("© e-stock 2019 <rgauthier2510@gmail.com>")
        font.pixelSize: Qt.application.font.pixelSize * 0.8
        font.italic: true
    }
}
