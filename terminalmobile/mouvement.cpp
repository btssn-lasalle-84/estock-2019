#include "mouvement.h"

Mouvement::Mouvement(QString p_casier, QString p_horodatage, QString p_utilisateur, QString p_action,
                     QString p_contenu, QString p_quantite, QObject *p_parent)
    : QObject(p_parent), m_casier(p_casier), m_horodatage(p_horodatage), m_utilisateur(p_utilisateur),
      m_action(p_action), m_contenu(p_contenu), m_quantite(p_quantite)
{
}

void Mouvement::setMouvement(QStringList p_mouvement)
{
    if (p_mouvement.size() == 6)
    {
        m_casier = p_mouvement.at(0);
        m_horodatage = p_mouvement.at(1);
        m_utilisateur = p_mouvement.at(2);
        m_action = p_mouvement.at(3);
        m_contenu = p_mouvement.at(4);
        m_quantite = p_mouvement.at(5);
    }
}

QString Mouvement::getCasier() const
{
    return m_casier;
}

void Mouvement::setCasier(QString p_casier)
{
    m_casier = p_casier;
}

QString Mouvement::getHorodatage() const
{
    return m_horodatage;
}

void Mouvement::setHorodatage(QString p_horodatage)
{
    m_horodatage = p_horodatage;
}

QString Mouvement::getUtilisateur() const
{
    return m_utilisateur;
}

void Mouvement::setUtilisateur(QString p_utilisateur)
{
    m_utilisateur = p_utilisateur;
}

QString Mouvement::getAction() const
{
    return m_action;
}

void Mouvement::setAction(QString p_action)
{
    m_action = p_action;
}

QString Mouvement::getContenu() const
{
    return m_contenu;
}

void Mouvement::setContenu(QString p_contenu)
{
    m_contenu = p_contenu;
}

QString Mouvement::getQuantite() const
{
    return m_quantite;
}

void Mouvement::setQuantite(QString p_quantite)
{
    m_quantite = p_quantite;
}
