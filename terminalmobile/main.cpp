#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "baseDeDonnees.h"
#include "utilisateurTerminal.h"
#include "mouvements.h"
#include "utilisateursArmoire.h"
#include "utilisateurArmoire.h"
#include "armoires.h"
#include "casiers.h"

/**
 * @file terminalmobile/main.cpp
 *
 * @brief Programme principal terminalMobile
 *
 * @details Crée et affiche la fenêtre principale de l'application
 *
 * @author Robin Gauthier
 *
 * @version 1.1
 *
 * @fn main(int argc, char *argv[])
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("e-stock mobile");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    BaseDeDonnees *g_pBddTerminal = BaseDeDonnees::getInstance("QSQLITE");
    g_pBddTerminal->ouvrir("estock.sqlite");
    engine.rootContext()->setContextProperty("g_pBddTerminal", g_pBddTerminal);

    Armoires *g_pArmoires = new Armoires;
    engine.rootContext()->setContextProperty("g_pArmoires", g_pArmoires);

    BaseDeDonnees *g_pBddArmoire = BaseDeDonnees::getInstance("QMYSQL");
    engine.rootContext()->setContextProperty("g_pBddArmoire", g_pBddArmoire);

    UtilisateurTerminal *g_pUtilisateurTerminal = new UtilisateurTerminal;
    engine.rootContext()->setContextProperty("g_pUtilisateurTerminal", g_pUtilisateurTerminal);

    Mouvements *g_pMouvements = new Mouvements;
    engine.rootContext()->setContextProperty("g_pMouvements", g_pMouvements);

    UtilisateursArmoire *g_pUtilisateursArmoire = new UtilisateursArmoire;
    engine.rootContext()->setContextProperty("g_pUtilisateursArmoire", g_pUtilisateursArmoire);

    Casiers *g_pCasiers = new Casiers;
    engine.rootContext()->setContextProperty("g_pCasiers", g_pCasiers);

    engine.load(QUrl(QStringLiteral("qrc:/IHMPrincipale.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    int resultat = app.exec();

    BaseDeDonnees::detruireInstance("QMYSQL");
    BaseDeDonnees::detruireInstance("QSQLITE");

    return resultat;
}
