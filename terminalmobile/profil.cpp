#include "profil.h"

Profil::Profil(QString p_id, QString p_nom, QObject *parent) : QObject(parent), m_nom(p_nom), m_id(p_id)
{
}

QString Profil::getNom() const
{
    return m_nom;
}

void Profil::setNom(QString p_nom)
{
    m_nom = p_nom;
}

QString Profil::getId() const
{
    return m_id;
}

void Profil::setId(QString p_id)
{
    m_id = p_id;
}
