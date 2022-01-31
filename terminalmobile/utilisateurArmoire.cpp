#include "utilisateurArmoire.h"

UtilisateurArmoire::UtilisateurArmoire(QString p_nomProfil, QString p_nomGroupe, QString p_nom, QString p_prenom,
                                       QString p_dateDeValidite, QString p_identifiant, QString p_badge, QString p_idUtilisateur,
                                       QObject *p_parent)
    : QObject(p_parent), m_nomProfil(p_nomProfil), m_nomGroupe(p_nomGroupe), m_nom(p_nom), m_prenom(p_prenom),
      m_dateDeValidite(p_dateDeValidite), m_identifiant(p_identifiant), m_badge(p_badge), m_idUtilisateur(p_idUtilisateur)
{
}

void UtilisateurArmoire::setUtilisateurArmoire(QStringList p_utilisateurArmoire)
{
    if (p_utilisateurArmoire.size() == 8)
    {
        m_nomProfil = p_utilisateurArmoire.at(0);
        m_nomGroupe = p_utilisateurArmoire.at(1);
        m_nom = p_utilisateurArmoire.at(2);
        m_prenom = p_utilisateurArmoire.at(3);
        m_dateDeValidite = p_utilisateurArmoire.at(4);
        m_identifiant = p_utilisateurArmoire.at(5);
        m_badge = p_utilisateurArmoire.at(6);
        m_idUtilisateur = p_utilisateurArmoire.at(7);
    }
}

QString UtilisateurArmoire::getNomProfil() const
{
    return m_nomProfil;
}

void UtilisateurArmoire::setNomProfil(QString p_nomProfil)
{
    m_nomProfil = p_nomProfil;
}

QString UtilisateurArmoire::getNomGroupe() const
{
    return m_nomGroupe;
}

void UtilisateurArmoire::setNomGroupe(QString p_nomGroupe)
{
    m_nomGroupe = p_nomGroupe;
}

QString UtilisateurArmoire::getNom() const
{
    return m_nom;
}

void UtilisateurArmoire::setNom(QString p_nom)
{
    m_nom = p_nom;
}

QString UtilisateurArmoire::getPrenom() const
{
    return m_prenom;
}

void UtilisateurArmoire::setPrenom(QString p_prenom)
{
    m_prenom = p_prenom;
}

QString UtilisateurArmoire::getDateDeValidite() const
{
    return m_dateDeValidite;
}

void UtilisateurArmoire::setDateDeValidite(QString p_dateDeValidite)
{
    m_dateDeValidite = p_dateDeValidite;
}

QString UtilisateurArmoire::getIdentifiant() const
{
    return m_identifiant;
}

void UtilisateurArmoire::setIdentifiant(QString p_identifiant)
{
    m_identifiant = p_identifiant;
}

QString UtilisateurArmoire::getBadge() const
{
    return m_badge;
}

void UtilisateurArmoire::setBadge(QString p_badge)
{
    m_badge = p_badge;
}

QString UtilisateurArmoire::getIdUtilisateur() const
{
    return m_idUtilisateur;
}

void UtilisateurArmoire::setIdUtilisateur(QString p_idUtilisateur)
{
    m_idUtilisateur = p_idUtilisateur;
}
