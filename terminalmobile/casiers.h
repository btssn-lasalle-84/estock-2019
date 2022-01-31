#ifndef CASIERS_H
#define CASIERS_H

#include <QObject>
#include <QTimer>
#include <QVariant>

class BaseDeDonnees;

class Casiers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_nbCasiers READ getNbCasiers NOTIFY nbCasiersChanged)
    Q_PROPERTY(QVariant listeCasiers READ getCasiers NOTIFY listeCasiersChanged)

public:
    explicit Casiers(QObject *parent = nullptr);
    ~Casiers();
    Q_INVOKABLE QString lire(QString adresseIPArmoire, bool debug=true);
    Q_INVOKABLE void arreterRafraichissement();
    QString getNbCasiers();
    QVariant getCasiers();

private:    
    QList<QObject*> casiers;
    BaseDeDonnees *m_pBaseDeDonnees;
    QString m_nbCasiers;
    QString m_adresseIPArmoire;
    QTimer *m_timer;
    
signals:
    void listeCasiersChanged();
    void nbCasiersChanged();

public slots:
    void actualiser();
};

#endif // CASIERS_H
