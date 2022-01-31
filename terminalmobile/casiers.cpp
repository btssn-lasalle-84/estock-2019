#include "casiers.h"
#include "casier.h"
#include "baseDeDonnees.h"

Casiers::Casiers(QObject *parent) : QObject(parent)
{
    m_pBaseDeDonnees = BaseDeDonnees::getInstance("QMYSQL");
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(actualiser()));
}

Casiers::~Casiers()
{
    if(m_timer->isActive())
       m_timer->stop();
    BaseDeDonnees::detruireInstance("QMYSQL");    
}

void Casiers::arreterRafraichissement()
{
    if(m_timer->isActive())
       m_timer->stop();
}

QString Casiers::getNbCasiers()
{
    return m_nbCasiers;
}

QVariant Casiers::getCasiers()
{
    return QVariant::fromValue(casiers);
}

QString Casiers::lire(QString adresseIPArmoire, bool debug)
{
    this->m_adresseIPArmoire = adresseIPArmoire;
    QString requeteNbCasiers = "SELECT Armoire.nbCasiers FROM Armoire WHERE Armoire.AdresseIP = '" + adresseIPArmoire + "'";
    m_pBaseDeDonnees->recuperer(requeteNbCasiers,m_nbCasiers);

    QString requeteStockCasier = "SELECT Stock.NumeroCasier, Article.Nom, Stock.Quantite, Stock.Disponible FROM Stock INNER JOIN Article ON Stock.idArticle = Article.idArticle ORDER BY Stock.NumeroCasier ASC";
    QVector<QStringList> enregistrementsCasiers;

    casiers.clear();
    if (m_pBaseDeDonnees->recuperer(requeteStockCasier,enregistrementsCasiers))
    {
        QStringList champsCasier;

        for(int i = 0; i < enregistrementsCasiers.size(); i++)
        {
            champsCasier = enregistrementsCasiers.at(i);
            if(debug)
                qDebug() << Q_FUNC_INFO << "champsCasier" << champsCasier;

            Casier *pCasier = new Casier(champsCasier.at(0).toInt(), champsCasier.at(1), champsCasier.at(2).toInt(), champsCasier.at(3).toInt());
            casiers.append(pCasier);
        }
        emit listeCasiersChanged();

        return m_nbCasiers;
    }

    if(!m_timer->isActive())
        m_timer->start(500);

    return m_nbCasiers;
}

void Casiers::actualiser()
{
    if(!m_adresseIPArmoire.isEmpty())
        lire(m_adresseIPArmoire, false);
}
