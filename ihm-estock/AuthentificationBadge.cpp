#include "AuthentificationBadge.h"
#include "baseDeDonnees.h"

AuthentificationBadge::AuthentificationBadge(QObject *parent) : QObject(parent), valide(false), autorise(false)
{
    qDebug() << Q_FUNC_INFO;
    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();
}

AuthentificationBadge::~AuthentificationBadge()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

bool AuthentificationBadge::lireBadge(QString badge)
{
    //badge = "RFIDMàBDD'èCD"; // test
    if(badge.isEmpty())
        return false;

    qDebug() << Q_FUNC_INFO << "badge" << badge;

    QString messageNettoye;

    if(!badge.isEmpty())
    {
        // les informations lues proviennent d'un clavier US en QWERTY
        // remplacement caractères QWERTY
        messageNettoye = badge.replace(QString::fromUtf8("Q"), "A");
        messageNettoye = badge.replace(QString::fromUtf8("W"), "Z");
        messageNettoye = badge.replace(QString::fromUtf8("q"), "q");
        messageNettoye = badge.replace(QString::fromUtf8("w"), "z");
        messageNettoye = badge.replace(QString::fromUtf8("M"), ":");
        // remplacement caractères US
        messageNettoye = badge.replace(QString::fromUtf8("à"), "0");
        messageNettoye = badge.replace(QString::fromUtf8("&"), "1");
        messageNettoye = badge.replace(QString::fromUtf8("é"), "2");
        messageNettoye = badge.replace(QString::fromUtf8("\""), "3");
        messageNettoye = badge.replace(QString::fromUtf8("'"), "4");
        messageNettoye = badge.replace(QString::fromUtf8("("), "5");
        messageNettoye = badge.replace(QString::fromUtf8("-"), "6");
        messageNettoye = badge.replace(QString::fromUtf8("è"), "7");
        messageNettoye = badge.replace(QString::fromUtf8("_"), "8");
        messageNettoye = badge.replace(QString::fromUtf8("ç"), "9");
        //qDebug() << Q_FUNC_INFO << messageNettoye;

        // les informations du badge doivent commencer par "RFID:"
        if(messageNettoye.startsWith("RFID:"))
        {
            QStringList champs = messageNettoye.split(":");
            //qDebug() << Q_FUNC_INFO << champs;

            if(champs.count() == 2 && champs.at(0) == "RFID")
            {
                // récupération de l'UID du badge
                QString UID = champs.at(1);

                // vérification de l'UID du badge (Un UID est une valeur hexadécimale valide)
                bool ok;
                qulonglong uid = UID.toULongLong(&ok, 16);
                //qDebug() << Q_FUNC_INFO << UID << uid << ok;
                if(ok)
                {
                    //labelUID->setText("UID : 0x" + UID + "\nUID : " + QString::number(uid));
                    identifiantBadge = UID;
                    qDebug() << Q_FUNC_INFO << "identifiantBadge" << identifiantBadge;
                    valide = true;
                    return true;
                }
                else
                {
                    valide = false;
                }
            }
            else
            {
                valide = false;
            }
        }
        else
        {
            valide = false;
        }
    }
    else
    {
        valide = false;
    }
    return false;
}

bool AuthentificationBadge::estValide()
{    
    QString dateMaintenant = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString requete = "SELECT DateValidite FROM Utilisateur WHERE Badge='" + identifiantBadge + "' AND DateValidite>='" + dateMaintenant + "'";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    QString retour;
    valide = bdd->recuperer(requete, retour);
    qDebug() << Q_FUNC_INFO << "valide" << valide << "dateValidite" << dateValidite;
    return valide;
}

bool AuthentificationBadge::estAutorise()
{
    if(!valide)
        return false;
    QString dateMaintenant = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString requete = "SELECT idUtilisateur, DateValidite FROM Utilisateur WHERE Badge='" + identifiantBadge + "'";
    QStringList donneesUtilisateur;
    idUtilisateur.clear();
    dateValidite.clear();
    valide = bdd->recuperer(requete, donneesUtilisateur);
    if(valide)
    {
        idUtilisateur = donneesUtilisateur.at(0);
        dateValidite = donneesUtilisateur.at(1);
        qDebug() << Q_FUNC_INFO << "valide" << valide << "idUtilisateur" << idUtilisateur << "dateValidite" << dateValidite;
    }
    qDebug() << Q_FUNC_INFO << "valide" << valide;
    return (valide && estValide());
}

QString AuthentificationBadge::getIdUtilisateur() const
{
    return idUtilisateur;
}

QString AuthentificationBadge::getDateValidite() const
{
    return dateValidite;
}

QString AuthentificationBadge::getIdentifiantBadge() const
{
    return identifiantBadge;
}
