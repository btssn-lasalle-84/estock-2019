import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.1

/**
  *
  * @file terminalmobile/UtilisateursArmoire.qml
  *
  * @brief Définition de la page des utilisateurs
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  *
  * @class UtilisateursArmoire
  *
  * @brief La page des utilisateurs
  *
  * @author Robin Gauthier
  *
  * @version 1.1
  *
  */

/**
  * @brief page des utilisateurs
  */
Page {
    id: pageUtilisateursArmoire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("Utilisateurs Armoire")
    //visible: true

    onVisibleChanged: {
            if (visible)
                g_pUtilisateursArmoire.lire()
   }

    /**
      * @brief Conteneur du texte labelTitre
      */
    Row {
        id: ligneTitre
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        /**
          * @brief titre de la boîte de dialogue
          */
        Text {
            id: labelTitre;
            text: qsTr("Liste des utilisateurs")
            elide: Text.ElideMiddle
            font.bold: true
            font.pixelSize: Qt.application.font.pixelSize * 1.5
        }
    }
    Row {
        id: rowButton
        anchors.top: ligneTitre.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Bouton {
            id: boutonAjouter
            text: "Ajouter"
            onClicked: {
                // ouvre la boîte de dialogue AjoutUtilisateur
                dialogueAjoutUtilisateur.open()
            }
        }
        Bouton {
            id: boutonModifier
            text: "Modifier"
            onClicked: {                
                dialogueModificationUtilisateur.open()
            }
        }
        Bouton {
            id: boutonSupprimer
            text: "Supprimer"
            onClicked: {
                dialogueSuppressionUtilisateur.open()
            }
        }
        Bouton {
            id: boutonRecharger
            text: "Actualiser"
            onClicked: {
                g_pUtilisateursArmoire.lire()
            }
        }
        Bouton {
            id: boutonRetour
            text: qsTr("Retour")
            onClicked: {
                pageUtilisateursArmoire.visible = false
            }
        }
    }

    Row {
        id: row
        anchors.top: rowButton.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: ligneTitre.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 0

        TableView {
            id: vueUtilisateurArmoire
            width: Screen.desktopAvailableWidth * 0.85
            height: Screen.desktopAvailableHeight * 0.75
            model: g_pUtilisateursArmoire.listeUtilisateursArmoire

            TableViewColumn {
                role: "m_nomProfil"
                title: "Profil"
                width: pageUtilisateursArmoire.width / 8
            }
            TableViewColumn {
                role: "m_nomGroupe"
                title: "Groupe"
                width: pageUtilisateursArmoire.width / 7
            }
            TableViewColumn {
                role: "m_nom"
                title: "Nom"
                width: pageUtilisateursArmoire.width / 8
            }
            TableViewColumn {
                role: "m_prenom"
                title: "Prénom"
                width: pageUtilisateursArmoire.width / 9
            }
            TableViewColumn {
                role: "m_dateDeValidite"
                title: "Date de validité"
                width: pageUtilisateursArmoire.width / 8
            }
            TableViewColumn {
                role: "m_identifiant"
                title: "Identifiant"
                width: pageUtilisateursArmoire.width / 8
            }
            TableViewColumn {
                role: "m_badge"
                title: "Badge"
                width: pageUtilisateursArmoire.width / 10
            }
            /*TableViewColumn {
                role: "m_email"
                title: "e-mail"
                width: pageUtilisateursArmoire.width / 8
            }*/
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
                        color: textColor
                        /*color: {

                        }*/
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Ligne : " + styleData.row);
                            console.log("Colonne : " + styleData.column);
                            console.log("Role : " + styleData.role);
                            console.log("Valeur : " + styleData.value);
                            console.log("Casier : " + g_pUtilisateursArmoire.listeUtilisateursArmoire[styleData.row].m_nomProfil)
                            console.log("Casier : " + g_pUtilisateursArmoire.listeUtilisateursArmoire[styleData.row].m_nomGroupe)
                            console.log("Casier : " + g_pUtilisateursArmoire.listeUtilisateursArmoire[styleData.row].m_badgeSelectionne)
                        }
                    }
                }
            }
        }
    }

    AjoutUtilisateur {
        id: dialogueAjoutUtilisateur
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight - header.height        
        property string idProfil: "";
        property string idGroupe: "";
        property string nomUtilisateur: "";
        property string prenomUtilisateur: "";
        property string dateValidite: "";
        property string identifiant: "";
        property string badge: "";
        onAccepted: { // signal émis par accept()
            console.log("idProfil : " + idProfil)
            console.log("idGroupe : " + idGroupe)
            console.log("nomUtilisateur : " + nomUtilisateur)
            console.log("prenomUtilisateur : " + prenomUtilisateur)
            console.log("dateValidite : " + dateValidite)
            console.log("identifiant : " + identifiant)
            console.log("badge : " + badge)
            // une nouvel utilisateur ?
            if(nomUtilisateur != "")
            {
                // ajoute le nouvel utilisateur
                g_pUtilisateursArmoire.inserer(idProfil, idGroupe, nomUtilisateur, prenomUtilisateur, dateValidite, identifiant, badge);
                // réinitialise les champs de saisie
                idProfil = ""
                idGroupe = ""
                nomUtilisateur = ""
                prenomUtilisateur = ""
                dateValidite =  ""
                identifiant = ""
                badge = ""
            }
        }
    }

    ModificationUtilisateur {
        id: dialogueModificationUtilisateur
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight - header.height
        property string idUtilisateur: "";
        property string idProfil: "";
        property string idGroupe: "";
        property string nomUtilisateur: "";
        property string prenomUtilisateur: "";
        property string dateValidite: "";
        property string identifiant: "";
        property string badge: "";
        onAccepted: { // signal émis par accept()
            console.log("idUtilisateur : " + idUtilisateur)
            console.log("idProfil : " + idProfil)
            console.log("idGroupe : " + idGroupe)
            console.log("nomUtilisateur : " + nomUtilisateur)
            console.log("prenomUtilisateur : " + prenomUtilisateur)
            console.log("dateValidite : " + dateValidite)
            console.log("identifiant : " + identifiant)
            console.log("badge : " + badge)
            // une nouvel utilisateur ?
            if(nomUtilisateur != "")
            {
                // modifie l'utilisateur
                g_pUtilisateursArmoire.modifier(idProfil, idGroupe, nomUtilisateur, prenomUtilisateur, dateValidite, identifiant, badge, idUtilisateur);
                // réinitialise les champs de saisie
                nomUtilisateur = ""
                prenomUtilisateur = ""
                dateValidite =  ""
                identifiant = ""
                badge = ""
            }
        }
    }

    SuppressionUtilisateur {
        id: dialogueSuppressionUtilisateur
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight - header.height
        property string idUtilisateur: "";
        property string idProfil: "";
        property string idGroupe: "";
        property string nomUtilisateur: "";
        property string prenomUtilisateur: "";
        property string dateValidite: "";
        property string identifiant: "";
        property string badge: "";
        onAccepted: { // signal émis par accept()
            console.log("idUtilisateur : " + idUtilisateur)
            console.log("idProfil : " + idProfil)
            console.log("idGroupe : " + idGroupe)
            console.log("nomUtilisateur : " + nomUtilisateur)
            console.log("prenomUtilisateur : " + prenomUtilisateur)
            console.log("dateValidite : " + dateValidite)
            console.log("identifiant : " + identifiant)
            console.log("badge : " + badge)
            // une nouvel utilisateur ?
            if(nomUtilisateur != "")
            {
                // supprime l'utilisateur
                g_pUtilisateursArmoire.supprimer(idProfil, idGroupe, nomUtilisateur, prenomUtilisateur, dateValidite, identifiant, badge, idUtilisateur);
                // réinitialise les champs de saisie
                nomUtilisateur = ""
                prenomUtilisateur = ""
                dateValidite =  ""
                identifiant = ""
                badge = ""
            }
        }
    }
}
