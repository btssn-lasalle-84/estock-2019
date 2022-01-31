#include "utilisateursArmoire.h"
#include "utilisateurArmoire.h"
#include "profil.h"
#include "groupe.h"
#include "baseDeDonnees.h"

UtilisateursArmoire::UtilisateursArmoire(QObject *p_parent) : QObject(p_parent)
{
    m_pBaseDeDonnees = BaseDeDonnees::getInstance("QMYSQL");
}

UtilisateursArmoire::~UtilisateursArmoire()
{
    BaseDeDonnees::detruireInstance("QMYSQL");
}

bool UtilisateursArmoire::lire()
{
    QString requete = "SELECT Profil.Nom, Groupe.Nom, Utilisateur.Nom, Utilisateur.Prenom, Utilisateur.DateValidite, Utilisateur.Identifiant, Utilisateur.Badge, Utilisateur.idUtilisateur FROM Utilisateur INNER JOIN Groupe ON Utilisateur.idGroupe = Groupe.idGroupe INNER JOIN Profil ON Utilisateur.idProfil = Profil.idProfil";
    QVector<QStringList> enregistrementsUtilisateursArmoire;

    m_utilisateursArmoire.clear();
    if (m_pBaseDeDonnees->recuperer(requete, enregistrementsUtilisateursArmoire))
    {
        QStringList champsUtilisateurArmoire;

        for(int i = 0; i < enregistrementsUtilisateursArmoire.size(); i++)
        {
            champsUtilisateurArmoire = enregistrementsUtilisateursArmoire.at(i);
            qDebug() << Q_FUNC_INFO << "champsUtilisateurArmoire" << champsUtilisateurArmoire;

            UtilisateurArmoire *pUtilisateurArmoire = new UtilisateurArmoire(
                        champsUtilisateurArmoire.at(0), champsUtilisateurArmoire.at(1),
                        champsUtilisateurArmoire.at(2), champsUtilisateurArmoire.at(3),
                        champsUtilisateurArmoire.at(4), champsUtilisateurArmoire.at(5),
                        champsUtilisateurArmoire.at(6), champsUtilisateurArmoire.at(7));
            m_utilisateursArmoire.append(pUtilisateurArmoire);
        }

        emit listeUtilisateursArmoireChanged();

        return true;
    }

    return false;
}

bool UtilisateursArmoire::lireProfil()
{
    QString requete = "SELECT Profil.idProfil, Profil.Nom FROM Profil ORDER BY Profil.idProfil ASC;";
    QVector<QStringList> enregistrementsListeProfil;

    qDebug() << Q_FUNC_INFO << "requete" << requete;
    m_listeProfil.clear();
    if (m_pBaseDeDonnees->recuperer(requete, enregistrementsListeProfil))
    {
        QStringList champsListeProfil;
        for(int i = 0; i < enregistrementsListeProfil.size(); i++)
        {
            champsListeProfil = enregistrementsListeProfil.at(i);
            qDebug() << Q_FUNC_INFO << "champsListeProfil" << champsListeProfil;
            Profil *pProfil = new Profil(champsListeProfil.at(0), champsListeProfil.at(1));
            m_listeProfil.append(pProfil);
        }
        emit listeProfilChanged();

        return true;
    }

    return false;
}

bool UtilisateursArmoire::lireGroupe()
{
    QString requete = "SELECT Groupe.idGroupe, Groupe.Nom FROM Groupe ORDER BY Groupe.idGroupe ASC;";
    QVector<QStringList> enregistrementsListeGroupe;

    qDebug() << Q_FUNC_INFO << "requete" << requete;
    m_listeGroupe.clear();
    if (m_pBaseDeDonnees->recuperer(requete, enregistrementsListeGroupe))
    {
        QStringList champsListeGroupe;
        for(int i = 0; i < enregistrementsListeGroupe.size(); i++)
        {
            champsListeGroupe = enregistrementsListeGroupe.at(i);
            qDebug() << Q_FUNC_INFO << "champsListeGroupe" << champsListeGroupe;
            Groupe *pGroupe = new Groupe(champsListeGroupe.at(0), champsListeGroupe.at(1));
            m_listeGroupe.append(pGroupe);
        }
        emit listeGroupeChanged();

        return true;
    }

    return false;
}

/*bool UtilisateursArmoire::lireUtilisateurs()
{
    QString requete = "SELECT Utilisateur.Badge FROM Utilisateur;";
    QVector<QStringList> enregistrementsListeBadge;

    qDebug() << Q_FUNC_INFO << "requete" << requete;
    m_listeBadge.clear();
    if (m_pBaseDeDonnees->recuperer(requete, enregistrementsListeBadge))
    {
        QStringList champsListeBadge;
        for(int i = 0; i < enregistrementsListeBadge.size(); i++)
        {
            champsListeBadge = enregistrementsListeBadge.at(i);
            qDebug() << Q_FUNC_INFO << "champsListeBadge" << champsListeBadge;
            Badge *pBadge = new Badge(champsListeBadge.at(0));
            m_listeBadge.append(pBadge);
        }
        emit listeBadgeChanged();

        return true;
    }

    return false;
}*/

bool UtilisateursArmoire::inserer(QString p_idProfil, QString p_idGroupe, QString p_nom, QString p_prenom, QString p_dateDeValidite, QString p_identifiant, QString p_badge)
{
    qDebug() << Q_FUNC_INFO << "p_idProfil" << p_idProfil << "p_idGroupe" << p_idGroupe << "p_nom" << p_nom << "p_prenom" << p_prenom << "p_dateDeValidite" << p_dateDeValidite << "p_identifiant" << p_identifiant << "p_badge" << p_badge;
    //requête INSERT
    QString requeteAjoutUtilisateur = "INSERT INTO Utilisateur (idProfil, idGroupe, Nom, Prenom, DateValidite, Identifiant, Badge, Email) VALUES ('" + p_idProfil + "', '" + p_idGroupe + "', '" + p_nom + "', '" + p_prenom + "', '" + p_dateDeValidite + "', '" + p_identifiant + "', '" + p_badge + "', '')";
    qDebug() << Q_FUNC_INFO << "requeteAjoutUtilisateur" << requeteAjoutUtilisateur;
    if (m_pBaseDeDonnees->executer(requeteAjoutUtilisateur))
    {
        // relire la liste
        lire();
        return true;
    }
    return false;
}

bool UtilisateursArmoire::modifier(QString p_idProfil, QString p_idGroupe, QString p_nom, QString p_prenom, QString p_dateDeValidite, QString p_identifiant, QString p_badge, QString p_idUtilisateur)
{
    qDebug() << Q_FUNC_INFO << "p_idProfil" << p_idProfil << "p_idGroupe" << p_idGroupe << "p_nom" << p_nom << "p_prenom" << p_prenom << "p_dateDeValidite" << p_dateDeValidite << "p_identifiant" << p_identifiant << "p_badge" << p_badge << "p_idUtilisateur" << p_idUtilisateur;
    //requête UPDATE
    QString requeteModificationUtilisateur = "UPDATE Utilisateur SET idProfil='" + p_idProfil + "',idGroupe='" + p_idGroupe + "',Nom='" + p_nom + "',Prenom='" + p_prenom + "',DateValidite='" + p_dateDeValidite + "',Identifiant='" + p_identifiant + "',Badge='" + p_badge + "' WHERE idUtilisateur='" + p_idUtilisateur + "'";
    qDebug() << Q_FUNC_INFO << "requeteModificationUtilisateur" << requeteModificationUtilisateur;
    if (m_pBaseDeDonnees->executer(requeteModificationUtilisateur))
    {
        // relire la liste
        lire();
        return true;
    }
    return false;
}

bool UtilisateursArmoire::supprimer(QString p_idProfil, QString p_idGroupe, QString p_nom, QString p_prenom, QString p_dateDeValidite, QString p_identifiant, QString p_badge, QString p_idUtilisateur)
{
    qDebug() << Q_FUNC_INFO << "p_idProfil" << p_idProfil << "p_idGroupe" << p_idGroupe << "p_nom" << p_nom << "p_prenom" << p_prenom << "p_dateDeValidite" << p_dateDeValidite << "p_identifiant" << p_identifiant << "p_badge" << p_badge << "p_idUtilisateur" << p_idUtilisateur;
    //requête UPDATE
    QString requeteSuppressionUtilisateur = "DELETE FROM Utilisateur WHERE Utilisateur.idUtilisateur = '" + p_idUtilisateur + "'";
    qDebug() << Q_FUNC_INFO << "requeteSuppressionUtilisateur" << requeteSuppressionUtilisateur;
    if (m_pBaseDeDonnees->executer(requeteSuppressionUtilisateur))
    {
        // relire la liste
        lire();
        return true;
    }
    return false;
}

QVariant UtilisateursArmoire::getUtilisateursArmoire()
{
    return QVariant::fromValue(m_utilisateursArmoire);
}

QVariant UtilisateursArmoire::getListeProfil()
{
    return QVariant::fromValue(m_listeProfil);
}

QVariant UtilisateursArmoire::getListeGroupe()
{
    return QVariant::fromValue(m_listeGroupe);
}
