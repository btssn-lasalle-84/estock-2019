#include "groupe.h"

Groupe::Groupe(QString p_id, QString p_nom, QObject *parent) : QObject(parent), m_nom(p_nom), m_id(p_id)
{
}

QString Groupe::getNom() const
{
    return m_nom;
}

void Groupe::setNom(QString p_nom)
{
    m_nom = p_nom;
}

QString Groupe::getId() const
{
    return m_id;
}

void Groupe::setId(QString p_id)
{
    m_id = p_id;
}
