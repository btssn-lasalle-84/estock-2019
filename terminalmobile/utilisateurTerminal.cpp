#include "utilisateurTerminal.h"
#include "baseDeDonnees.h"
#include <QDebug>

UtilisateurTerminal::UtilisateurTerminal(QObject *p_parent) : QObject(p_parent)
{
    m_estExistant = false;
    m_estAutorise = false;
    m_pBaseDeDonnees = BaseDeDonnees::getInstance("QMYSQL");
}

UtilisateurTerminal::~UtilisateurTerminal()
{
    BaseDeDonnees::detruireInstance("QMYSQL");
}

bool UtilisateurTerminal::lireUtilisateur(QString p_identifiant, QString p_password, bool p_doForceLogin)
{
    QString requeteExistant =
            "SELECT COUNT(*) AS decompte " \
            "FROM Utilisateur " \
            "WHERE Utilisateur.Identifiant='" + p_identifiant + "'";
    QString valeurDecompte;

    m_estExistant = false;
    m_estAutorise = false;

    if (!m_pBaseDeDonnees->recuperer(requeteExistant, valeurDecompte))
    {
        return false;
    }
    else
    {
        if (valeurDecompte == "0") // Inutile de convertir en valeur numérique ici car COUNT(*)
        {
            return false;
        }
        else
        {
            m_estExistant = true;
            m_estAutorise = false;
        }
    }

    QString requeteAutorisation =
            "SELECT Utilisateur.idUtilisateur, Utilisateur.Nom, Utilisateur.Prenom, Utilisateur.DateValidite, Utilisateur.Identifiant, Utilisateur.Badge, Utilisateur.Email, Profil.idProfil, Profil.Nom AS Profil, Groupe.idGroupe, Groupe.Nom AS Groupe " \
            "FROM Utilisateur " \
            "INNER JOIN Groupe ON Groupe.idGroupe=Utilisateur.idGroupe " \
            "INNER JOIN Profil ON Profil.idProfil=Utilisateur.idProfil " \
            "WHERE Utilisateur.Identifiant='" + p_identifiant + "'";

    QStringList donneesUtilisateur;

    if (!p_doForceLogin)
    {
        /**
         * @todo Vérifier la validité de l'utilisateur avec son mot de passe
         */
        requeteAutorisation += " AND Utilisateur.MotDePasse='" + p_password + "'";
    }


    /*
     * Exemple de résultat :
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
| idUtilisateur | Nom      | Prenom | DateValidite | Identifiant | Badge | Email                   | idProfil | Profil      | idGroupe | Groupe   |
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
|             7 | GAUTHIER | Robin  | 2019-07-01   | gauthier.r  | 4444  | rgauthier2510@gmail.com |        3 | Utilisateur |        5 | T-BTS-SN |
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
     */

    if (m_pBaseDeDonnees->recuperer(requeteAutorisation, donneesUtilisateur))
    {
        qDebug() << Q_FUNC_INFO << "donneesUtilisateur" << donneesUtilisateur;
        m_idUtilisateur = donneesUtilisateur.at(0);
        m_idProfil = donneesUtilisateur.at(7);
        m_idGroupe = donneesUtilisateur.at(9);
        m_identifiant = donneesUtilisateur.at(4);
        m_nom = donneesUtilisateur.at(1);
        m_prenom = donneesUtilisateur.at(2);
        m_dateValidite = donneesUtilisateur.at(3);
        m_badge = donneesUtilisateur.at(5);
        m_idUtilisateur = donneesUtilisateur.at(6);
        m_profil = donneesUtilisateur.at(8);
        m_groupe = donneesUtilisateur.at(10);

        m_estAutorise = true;

        emit utilisateurUpdated();

        return true;
    }
    else
    {
        m_estAutorise = false;

        return false;
    }

    return false;
}

bool UtilisateurTerminal::reinitialiser()
{
    qDebug() << Q_FUNC_INFO;
    m_idProfil.clear();
    m_idGroupe.clear();
    m_identifiant.clear();
    m_nom.clear();
    m_prenom.clear();
    m_dateValidite.clear();
    m_badge.clear();
    m_idUtilisateur.clear();
    m_profil.clear();
    m_groupe.clear();
    m_estExistant = false;
    m_estAutorise = false;
    emit utilisateurUpdated();
    return true;
}

bool UtilisateurTerminal::estExistant()
{
    return m_estExistant;
}

bool UtilisateurTerminal::estAutorise()
{
    return m_estAutorise;
}

QString UtilisateurTerminal::getNom() const
{
    return m_nom;
}

QString UtilisateurTerminal::getPrenom() const
{
    return m_prenom;
}
