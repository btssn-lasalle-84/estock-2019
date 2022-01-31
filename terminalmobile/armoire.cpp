#include "armoire.h"

Armoire::Armoire(QString p_nom, QString p_adresseIP, QObject *parent) : QObject(parent), m_nom(p_nom), m_adresseIP(p_adresseIP)
{
}

void Armoire::setArmoire(QStringList p_armoire)
{
    if (p_armoire.size() > 0)
    {
        m_nom = p_armoire.at(0);
        m_adresseIP = p_armoire.at(1);
    }
}

QString Armoire::getNom() const
{
    return m_nom;
}

void Armoire::setNom(QString p_nom)
{
    m_nom = p_nom;
}

QString Armoire::getAdresseIP() const
{
    return m_adresseIP;
}

void Armoire::setAdresseIP(QString p_adresseIP)
{
    m_adresseIP = p_adresseIP;
}
