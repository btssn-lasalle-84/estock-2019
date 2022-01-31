#include "mouvements.h"
#include "mouvement.h"
#include "baseDeDonnees.h"

Mouvements::Mouvements(QObject *p_parent) : QObject(p_parent)
{
    m_pBaseDeDonnees = BaseDeDonnees::getInstance("QMYSQL");
}

Mouvements::~Mouvements()
{
    BaseDeDonnees::detruireInstance("QMYSQL");
}

bool Mouvements::lire()
{
    QString requete = "SELECT Stock.numeroCasier, Mouvement.Horodatage, Utilisateur.Nom, Action.Nom, Article.Nom, Mouvement.Quantite FROM Mouvement INNER JOIN Stock ON Mouvement.idStock = Stock.idStock INNER JOIN Utilisateur ON Mouvement.idUtilisateur = Utilisateur.idUtilisateur INNER JOIN Action ON Mouvement.idAction = Action.idAction INNER JOIN Article ON Mouvement.idStock = Stock.idStock AND Stock.idArticle = Article.idArticle";
    QVector<QStringList> donneesMouvements;

    if (m_pBaseDeDonnees->recuperer(requete, donneesMouvements))
    {
        QStringList donneesMouvement;
        m_mouvements.clear();

        for(int i = 0; i < donneesMouvements.size(); i++)
        {
            donneesMouvement = donneesMouvements.at(i);
            qDebug() << Q_FUNC_INFO << "donneesMouvement" << donneesMouvement;
            Mouvement *pMouvement = new Mouvement(donneesMouvement.at(0), QDateTime::fromString(donneesMouvement.at(1), "yyyy-MM-ddTHH:mm:ss").toString("dd/MM/yyyy HH:mm"), donneesMouvement.at(2), donneesMouvement.at(3), donneesMouvement.at(4), donneesMouvement.at(5));
            m_mouvements.append(pMouvement);
        }
        emit listeMouvementsChanged();

        return true;
    }

    return false;
}

QVariant Mouvements::getMouvements()
{
    return QVariant::fromValue(m_mouvements);
}
