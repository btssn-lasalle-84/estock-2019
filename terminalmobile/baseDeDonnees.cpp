/**
  *
  * @file terminalmobile/baseDeDonnees.cpp
  *
  * @brief Définition de la classe BaseDeDonnees pour Android
  *
  * @author Thierry Vaira
  *
  * @version 1.1
  *
  */

#include "baseDeDonnees.h"

#include <QDebug>

BaseDeDonnees* BaseDeDonnees::baseDeDonnees[NB_BASEDEDONNEES] = { NULL, NULL };
int BaseDeDonnees::nbAcces[NB_BASEDEDONNEES] = { 0, 0 };

BaseDeDonnees::BaseDeDonnees(QString type)
{
    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO << "type" << type;
    #endif

    nomBDD = type.toLower();
    if(type == "QSQLITE")
    {
        db = QSqlDatabase::addDatabase(type, nomBDD);
    }
    else if(type == "QMYSQL")
    {
        db = QSqlDatabase::addDatabase(type, nomBDD);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "type" << type << "non pris en charge";
    }
}

BaseDeDonnees::~BaseDeDonnees()
{
    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO;
    #endif
}

BaseDeDonnees* BaseDeDonnees::getInstance(QString type)
{
    if(type == "QSQLITE")
    {
        if (baseDeDonnees[BDD_SQLITE] == NULL)
        {
            baseDeDonnees[BDD_SQLITE] = new BaseDeDonnees(type);
        }
        nbAcces[BDD_SQLITE]++;
        #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces[BDD_SQLITE] << type;
        #endif
        return baseDeDonnees[BDD_SQLITE];
    }
    else if(type == "QMYSQL")
    {
        if (baseDeDonnees[BDD_MYSQL] == NULL)
        {
            baseDeDonnees[BDD_MYSQL] = new BaseDeDonnees(type);
        }
        nbAcces[BDD_MYSQL]++;
        #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces[BDD_MYSQL] << type;
        #endif
        return baseDeDonnees[BDD_MYSQL];
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "type" << type << "non pris en charge";
    }
    return NULL;
}

void BaseDeDonnees::detruireInstance(QString type)
{
    if(type == "QSQLITE")
    {
        if (baseDeDonnees[BDD_SQLITE] != NULL)
        {
            if (nbAcces[BDD_SQLITE] > 0)
            {
                nbAcces[BDD_SQLITE]--;
            }
        }
        #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces[BDD_SQLITE] << type;
        #endif
        if (nbAcces[BDD_SQLITE] == 0)
        {
            baseDeDonnees[BDD_SQLITE]->deconnecter();
            delete baseDeDonnees[BDD_SQLITE];
            baseDeDonnees[BDD_SQLITE] = NULL;
        }
    }
    else if(type == "QMYSQL")
    {
        if (baseDeDonnees[BDD_MYSQL] != NULL)
        {
            if (nbAcces[BDD_MYSQL] > 0)
            {
                nbAcces[BDD_MYSQL]--;
            }
        }
        #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces[BDD_MYSQL] << type;
        #endif
        if (nbAcces[BDD_MYSQL] == 0)
        {
            baseDeDonnees[BDD_MYSQL]->deconnecter();
            delete baseDeDonnees[BDD_MYSQL];
            baseDeDonnees[BDD_MYSQL] = NULL;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "type" << type << "non pris en charge";
    }
}

QSqlDatabase BaseDeDonnees::getNomBDD()
{
    return QSqlDatabase::database(nomBDD, false);
}

bool BaseDeDonnees::estConnecte()
{
    QMutexLocker verrou(&mutex);
    return getNomBDD().isOpen();
}

void BaseDeDonnees::deconnecter()
{
    QMutexLocker verrou(&mutex);
    if(getNomBDD().isOpen())
    {
        qDebug() << Q_FUNC_INFO << getNomBDD().driverName();
        getNomBDD().close();
    }
}

bool BaseDeDonnees::connecter(QString nomBase, QString username/*=BDD_USERNAME*/, QString password/*=BDD_PASSWORD*/, QString serveur/*=BDD_HOSTNAME*/)
{
    QMutexLocker verrou(&mutex);
    qDebug() << Q_FUNC_INFO << "type" << getNomBDD().driverName();
    if (getNomBDD().driverName() != "QMYSQL")
    {
        return false;
    }    

    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO << "open" << getNomBDD().isOpen() << "serveur" << serveur << "username" << username << "password" << password << "nomBase" << nomBase;
    #endif

    if(!getNomBDD().isOpen())
    {
       getNomBDD().setHostName(serveur);
       getNomBDD().setUserName(username);
       getNomBDD().setPassword(password);
       getNomBDD().setDatabaseName(nomBase);

       #ifdef DEBUG_BASEDEDONNEES
       qDebug() << Q_FUNC_INFO << "open" << getNomBDD().isOpen() << "hostName" << getNomBDD().hostName() << "userName" << getNomBDD().userName() << "password" << getNomBDD().password() << "databaseName" << getNomBDD().databaseName();
       #endif

       if(getNomBDD().open())
       {
           #ifdef DEBUG_BASEDEDONNEES
           qDebug() << Q_FUNC_INFO << "open" << getNomBDD().isOpen() << "hostName" << getNomBDD().hostName() << "userName" << getNomBDD().userName() << "password" << getNomBDD().password() << "databaseName" << getNomBDD().databaseName();
           #endif

           return true;
       }
       else
       {
           qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : impossible de se connecter à la base de données !");
           qDebug() << Q_FUNC_INFO << "Driver MYSQL disponible" << getNomBDD().isDriverAvailable("QMYSQL"); // driverName
           qDebug() << Q_FUNC_INFO << "Driver valide" << getNomBDD().isValid();
           qDebug() << Q_FUNC_INFO << "Erreur" << getNomBDD().lastError().text();
           return false;
       }
    }
    else
        return true;
}

bool BaseDeDonnees::estOuvert()
{
    QMutexLocker verrou(&mutex);
    return getNomBDD().isOpen();
}

bool BaseDeDonnees::ouvrir(QString fichierBase)
{
    if (getNomBDD().driverName() != "QSQLITE")
    {
        return false;
    }

    QMutexLocker verrou(&mutex);
    if(!getNomBDD().isOpen())
    {
       QFile sfile(QString("assets:/db") + QString("/" + fichierBase));
       QFile dfile(QString("./" + fichierBase));

       // supprime le fichier destination
       /*if (sfile.exists())
       {
           if (dfile.exists())
           {
               dfile.remove();
           }
       }*/

       // copie
       if (sfile.exists())
       {
           sfile.copy(dfile.fileName());
           bool retour = dfile.setPermissions(QFileDevice::ReadUser|QFileDevice::WriteUser);
           qDebug() << Q_FUNC_INFO << retour << dfile.permissions();
       }

       getNomBDD().setDatabaseName(QString("./") + fichierBase);

       #ifdef DEBUG_BASEDEDONNEES
       qDebug() << Q_FUNC_INFO << getNomBDD().databaseName();
       #endif

       if(getNomBDD().open())
       {
           #ifdef DEBUG_BASEDEDONNEES
           qDebug() << Q_FUNC_INFO << QString::fromUtf8("Ouverture réussie de '%1'").arg(getNomBDD().databaseName());
           #endif

           return true;
       }
       else
       {
           qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : impossible d'ouvrir la base de données !");
           return false;
       }
    }
    else
    {
        return true;
    }
}

/* pour : UPDATE, INSERT et DELETE */
bool BaseDeDonnees::executer(QString requete)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery enregistrements(db);
    bool estCorrect;

    if (getNomBDD().isOpen())
    {
        if(requete.contains("UPDATE") || requete.contains("INSERT") || requete.contains("DELETE"))
        {
            estCorrect = enregistrements.exec(requete);

            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(estCorrect)).arg(requete);
            #endif

            if (estCorrect)
            {
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(enregistrements.lastError().text()).arg(requete);

                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);

            return false;
        }
    }
    else
    {
        return false;
    }

}

/* uniquement pour récupérer (SELECT) UN champ d'UN seul enregistrement
   Remarque : le champ est stocké dans un QString
 */
bool BaseDeDonnees::recuperer(QString requete, QString &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery enregistrements(db);
    bool estCorrect;

    if (getNomBDD().isOpen())
    {
        if (requete.contains("SELECT"))
        {
            estCorrect = enregistrements.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(estCorrect)).arg(requete);
            #endif

            if (estCorrect)
            {
                // on se positionne sur l'enregistrement
                enregistrements.first();

                // on vérifie l'état de l'enregistrement retourné
                if(!enregistrements.isValid())
                {
                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Résultat non valide !");
                    #endif

                    return false;
                }

                // on récupère sous forme de QString la valeur du champ
                if (enregistrements.isNull(0))
                {
                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Aucun résultat !");
                    #endif

                    return false;
                }
                donnees = enregistrements.value(0).toString();

                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif

                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(enregistrements.lastError().text()).arg(requete);

                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
    {
        return false;
    }
}

/* uniquement pour récupérer (SELECT) plusieurs champs d'UN seul enregistrement
   Remarque : les différents champs sont stockés dans un QStringList
 */
bool BaseDeDonnees::recuperer(QString requete, QStringList &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery enregistrements(db);
    bool estCorrect;

    if (getNomBDD().isOpen())
    {
        if (requete.contains("SELECT"))
        {
            estCorrect = enregistrements.exec(requete);

            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << QString::fromUtf8("<BaseDeDonnees::recuperer(QString, QStringList)> retour %1 pour la requete : %2").arg(QString::number(estCorrect)).arg(requete);
            #endif

            if (estCorrect)
            {
                // on se positionne sur l'enregistrement
                enregistrements.first();

                // on vérifie l'état de l'enregistrement retourné
                if (!enregistrements.isValid())
                {
                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Résultat non valide !");
                    #endif

                    return false;
                }

                // on récupère sous forme de QString la valeur de tous les champs sélectionnés
                // et on les stocke dans une liste de QString
                for(int i = 0; i < enregistrements.record().count(); i++)
                {
                    if (!enregistrements.isNull(i))
                    {
                        donnees << enregistrements.value(i).toString();
                    }
                }

                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif

                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(enregistrements.lastError().text()).arg(requete);

                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);

            return false;
        }
    }
    else
    {
        return false;
    }
}

/* uniquement pour récupérer (SELECT) un seul champ de plusieurs enregistrements
   Remarque : le champ des différents enregistrements est stocké dans un QVector de QString
 */
bool BaseDeDonnees::recuperer(QString requete, QVector<QString> &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery enregistrements(db);
    bool estCorrect;
    QString valeur;

    if (getNomBDD().isOpen())
    {
        if (requete.contains("SELECT"))
        {
            estCorrect = enregistrements.exec(requete);

            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(estCorrect)).arg(requete);
            #endif

            if(estCorrect)
            {
                // pour chaque enregistrement
                while (enregistrements.next() )
                {
                    // on récupère sous forme de QString la valeur du champs sélectionné
                    valeur = enregistrements.value(0).toString();

                    #ifdef DEBUG_BASEDEDONNEES
                    //qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
                    #endif

                    // on stocke l'enregistrement dans le QVector
                    donnees.push_back(valeur);
                }

                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif

                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(enregistrements.lastError().text()).arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);

            return false;
        }
    }
    else
    {
        return false;
    }
}

/* uniquement pour récupérer (SELECT) plusieurs champs de plusieurs enregistrements
   Remarque : les différents champs des différents enregistrements sont stockés dans un QVector de QStringList
 */
bool BaseDeDonnees::recuperer(QString requete, QVector<QStringList> &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery enregistrements(db);
    bool estCorrect;
    QStringList valeurs;

    if(getNomBDD().isOpen())
    {
        if (requete.contains("SELECT"))
        {
            estCorrect = enregistrements.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(estCorrect)).arg(requete);
            #endif

            if (estCorrect)
            {
                // pour chaque enregistrement
                while (enregistrements.next() )
                {
                    // on récupère sous forme de QString la valeur de tous les champs sélectionnés
                    // et on les stocke dans une liste de QString
                    for(int i=0; i < enregistrements.record().count(); i++)
                    {
                        valeurs << enregistrements.value(i).toString();
                    }

                    #ifdef DEBUG_BASEDEDONNEES
                    //qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
                    /*for(int i=0;i<r.record().count();i++)
                        qDebug() << r.value(i).toString();*/
                    #endif

                    // on stocke l'enregistrement dans le QVector
                    donnees.push_back(valeurs);

                    // on efface la liste de QString pour le prochain enregistrement
                    valeurs.clear();
                }

                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif

                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(enregistrements.lastError().text()).arg(requete);

                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);

            return false;
        }
    }
    else
    {
        return false;
    }
}
