#include "armoires.h"
#include "armoire.h"
#include "baseDeDonnees.h"

Armoires::Armoires(QObject *p_parent) : QObject(p_parent)
{
    m_pBaseDeDonnees = BaseDeDonnees::getInstance("QSQLITE");    
    lire();
}

Armoires::~Armoires()
{
    BaseDeDonnees::detruireInstance("QSQLITE");
}

bool Armoires::lire()
{
    QString requete = "SELECT Nom, AdresseIP FROM Armoire";
    QVector<QStringList> donneesArmoires;

    if (m_pBaseDeDonnees->recuperer(requete, donneesArmoires))
    {
        QStringList donneesArmoire;
        m_armoires.clear();
        for(int i = 0; i < donneesArmoires.size(); i++)
        {
            donneesArmoire = donneesArmoires.at(i);
            qDebug() << Q_FUNC_INFO << "donneesArmoire" << donneesArmoire;
            Armoire *pArmoire = new Armoire(donneesArmoire.at(0), donneesArmoire.at(1));
            m_armoires.append(pArmoire);
        }
        emit listeArmoiresChanged();
        return true;
    }
    return false;
}

bool Armoires::inserer(QString p_nom, QString p_adresseIP)
{
    qDebug() << Q_FUNC_INFO << "p_nom" << p_nom << "p_adresseIP" << p_adresseIP;
    //requête INSERT
    QString requeteAjoutArmoire = "INSERT INTO Armoire (Nom, AdresseIP) VALUES ('" + p_nom + "','" + p_adresseIP + "')";
    qDebug() << Q_FUNC_INFO << "requeteAjoutArmoire" << requeteAjoutArmoire;
    if (m_pBaseDeDonnees->executer(requeteAjoutArmoire))
    {
        // relire la liste
        lire();
        return true;
    }
    return false;
}

bool Armoires::supprimer(QString p_nom, QString p_adresseIP)
{
    qDebug() << Q_FUNC_INFO << "p_nom" << p_nom << "p_adresseIP" << p_adresseIP;
    // Faire requête DELETE
    QString requeteSuppressionArmoire = "DELETE FROM Armoire WHERE Nom = '" + p_nom + "'";
    qDebug() << Q_FUNC_INFO << "requeteSuppressionArmoire" << requeteSuppressionArmoire;
    if (m_pBaseDeDonnees->executer(requeteSuppressionArmoire))
    {
        // relire la liste
        lire();
        return true;
    }
    return false;
}

QVariant Armoires::getArmoires()
{
    return QVariant::fromValue(m_armoires);
}
