#ifndef BASEDEDONNEES_H
#define BASEDEDONNEES_H

/**
  *
  * @file terminalmobile/baseDeDonnees.h
  *
  * @brief Déclaration de la classe BaseDeDonnees pour Android
  *
  * @author Thierry VAIRA
  *
  * @version 1.1
  *
  */

#include <QObject>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMutex>
#include <QString>

//#define DEBUG_BASEDEDONNEES

#define NB_BASEDEDONNEES    2
#define BDD_SQLITE          0
#define BDD_MYSQL           1

class BaseDeDonnees : public QObject
{
    Q_OBJECT
    public:
        static BaseDeDonnees* getInstance(QString type);
        static void detruireInstance(QString type);

        Q_INVOKABLE bool estConnecte();
        Q_INVOKABLE void deconnecter();
        Q_INVOKABLE bool connecter(QString nomBase, QString username, QString password, QString serveur);
        
        Q_INVOKABLE bool estOuvert();
        Q_INVOKABLE bool ouvrir(QString fichierBase);

        /* uniquement pour : UPDATE, INSERT et DELETE */
        Q_INVOKABLE bool executer(QString requete);

        /* uniquement pour : SELECT */
        Q_INVOKABLE bool recuperer(QString requete, QString &donnees); // 1 -> 1
        Q_INVOKABLE bool recuperer(QString requete, QStringList &donnees); // 1 -> 1..*
        Q_INVOKABLE bool recuperer(QString requete, QVector<QString> &donnees); // 1..* -> 1
        Q_INVOKABLE bool recuperer(QString requete, QVector<QStringList> &donnees); // 1..* -> 1..*

    private:
        BaseDeDonnees(QString type);
        ~BaseDeDonnees();

        static BaseDeDonnees*  baseDeDonnees[NB_BASEDEDONNEES];
        static int             nbAcces[NB_BASEDEDONNEES];
        QSqlDatabase           db;
        QString                nomBDD;
        QMutex                 mutex;

        QSqlDatabase           getNomBDD();
};

#endif // BASEDEDONNEES_H
