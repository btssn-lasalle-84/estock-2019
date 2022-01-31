import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.1

/**
  *
  * @file terminalmobile/StockArmoire.qml
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
  * @class StockArmoire
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
    id: pageStockArmoire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("Armoire")
    property string utilisateur: ""
    property string armoire: ""

    function afficherCasiers(nbCasiers) {
        var numeroCasier = 0
        var decrementImpair = 1
        var decrementPair = 2
        if (pageStockArmoire.visible)
        {
            if(nbCasiers > 0)
            {
                for(var i=1; i <= nbCasiers; i++)
                {
                    if(i%2 == 1)
                    {
                        // casier impairs -> gauche
                        numeroCasier = (i-decrementImpair)
                        colonneCasiersGauche.itemAt(numeroCasier).visible = true
                        decrementImpair++;
                    }
                    else
                    {
                        // casier pairs -> droite
                        numeroCasier = (i-decrementPair)
                        colonneCasiersDroite.itemAt(numeroCasier).visible = true
                        decrementPair++;
                    }
                }
            }
            decrementImpair = 1
            decrementPair = 2
            for(var i=0; i < g_pCasiers.listeCasiers.length; i++)
            {
                //console.log("numeroCasier : " + g_pCasiers.listeCasiers[i].numeroCasier)
                if(g_pCasiers.listeCasiers[i].numeroCasier%2 == 1)
                {
                    // casier impairs -> gauche
                    numeroCasier = (g_pCasiers.listeCasiers[i].numeroCasier-decrementImpair)
                    colonneCasiersGauche.itemAt(numeroCasier).nomCasier = "Casier " + g_pCasiers.listeCasiers[i].numeroCasier + "\n" + g_pCasiers.listeCasiers[i].nomArticle + "\nQuantité : " + g_pCasiers.listeCasiers[i].quantite + "\nDisponible : " + g_pCasiers.listeCasiers[i].disponible;
                    colonneCasiersGauche.itemAt(numeroCasier).numeroCasier = g_pCasiers.listeCasiers[i].numeroCasier
                    //colonneCasiersGauche.itemAt(numeroCasier).visible = true
                    decrementImpair++;
                }
                else
                {
                    // casier pairs -> droite
                    numeroCasier = (g_pCasiers.listeCasiers[i].numeroCasier-decrementPair)
                    colonneCasiersDroite.itemAt(numeroCasier).nomCasier =  "Casier " + g_pCasiers.listeCasiers[i].numeroCasier + "\n" + g_pCasiers.listeCasiers[i].nomArticle + "\nQuantité : " + g_pCasiers.listeCasiers[i].quantite + "\nDisponible : " + g_pCasiers.listeCasiers[i].disponible;
                    colonneCasiersDroite.itemAt(numeroCasier).numeroCasier = g_pCasiers.listeCasiers[i].numeroCasier
                    //colonneCasiersDroite.itemAt(numeroCasier).visible = true
                    decrementPair++;
                }
            }
        }
        else
        {
            g_pCasiers.arreterRafraichissement()
            if(nbCasiers > 0)
            {
                //console.log("Nb casiers (armoire) : " + nbCasiers)
                for(var i=1; i <= nbCasiers; i++)
                {
                    if(i%2 == 1)
                    {
                        // casier impairs -> gauche
                        numeroCasier = (i-decrementImpair)
                        colonneCasiersGauche.itemAt(numeroCasier).visible = false
                        decrementImpair++;
                    }
                    else
                    {
                        // casier pairs -> droite
                        numeroCasier = (i-decrementPair)
                        colonneCasiersDroite.itemAt(numeroCasier).visible = false
                        decrementPair++;
                    }
                }
            }
        }
    }

    Connections {
        target: g_pCasiers
        onListeCasiersChanged: {
            var nbCasiers = g_pCasiers.m_nbCasiers
            afficherCasiers(nbCasiers)
        }
    }

    onVisibleChanged: {
        var nbCasiers = g_pCasiers.lire(ihmPrincipale.adresseIPArmoire)
        console.log("Armoire : " + ihmPrincipale.adresseIPArmoire)
        console.log("Nb casiers (armoire) : " + nbCasiers)
        console.log("Nb casiers (stock) : " + g_pCasiers.listeCasiers.length)

        afficherCasiers(nbCasiers)
    }

    /**
      * @brief Conteneur des casiers
      */
    // Affichage des casiers
    Rectangle {
        id: conteneurCasiers
        implicitWidth: colonneCasier1.implicitWidth + colonneCasier2.implicitWidth + 20
        implicitHeight: colonneCasier1.implicitHeight
        color: "lightgray";
        radius: 10.0;
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 50

        /**
          * @brief Colonne contenant les 4 casiers impairs
          */
        Column {
            id: colonneCasier1
            padding: 10
            spacing: 20
            /*Casier {
                id: casier1
                nomCasier: "casier1";
                idCasier: 1;
            }
            Casier {
                id: casier2
                nomCasier: "casier2";
                idCasier: 2;
            }
            Casier {
                id: casier3
                nomCasier: "casier3";
                idCasier: 3;
            }
            Casier {
                id: casier4
                nomCasier: "casier4";
                idCasier: 4;
            }*/
            Repeater {
                id: colonneCasiersGauche
                model: ["Casier 1", "Casier 3", "Casier 5", "Casier 7"]

                Casier {
                    nomCasier: modelData;                    
                    //numeroCasier: model.index + 1;
                }
            }
        }

        /**
          * @brief Colonne contenant les 4 derniers casiers pairs
          */
        Column {
            id: colonneCasier2
            anchors.left: colonneCasier1.right
            anchors.leftMargin: 20
            padding: 10
            spacing: 20
            Repeater {
                id: colonneCasiersDroite
                model: ["Casier 2", "Casier 4", "Casier 6", "Casier 8"]
                Casier {
                    nomCasier: modelData;
                    //numeroCasier: model.index + 5;
                }
            }
        }
    }

    /**
      * @brief Colonne contenant le bouton boutonQuitterStockArmoire
      */
    Column {
        id: colonneBoutons
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 50
        spacing: 20

        Text {
            id: labelUtilisateur
            text: utilisateur
            elide: Text.ElideMiddle
            font.pixelSize: Qt.application.font.pixelSize * 1.2
        }
        /**
          * @brief bouton pour quitter la page StockArmoire ( bouton retour et non annuler pour l'instant )
          */
        Button {
            id: boutonQuitterStockArmoire
            text: qsTr("Retour")
            width: implicitWidth * 1.2
            font.pixelSize: Qt.application.font.pixelSize * 1.2
            onClicked: {
                pageStockArmoire.visible = false
            }
        }
    }

    /**
      * @brief boîte de dialogue permettant de gérer un casier
      */
    GestionCasier {
        id: dialogueGestionCasier
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight - header.height
        property string numeroCasier: "";
        onAccepted: { // signal émis par accept()
            if(debug)
            {
                console.log("accept")
            }
        }
    }
}

