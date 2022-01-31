#ifndef ARMOIRES_H
#define ARMOIRES_H

#include <QObject>
#include <QVariant>

class BaseDeDonnees;

class Armoires : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant listeArmoires READ getArmoires NOTIFY listeArmoiresChanged)
public:
    explicit Armoires(QObject *parent = nullptr);
    ~Armoires();
    Q_INVOKABLE bool lire();
    Q_INVOKABLE bool inserer(QString p_nom, QString p_adresseIP);
    Q_INVOKABLE bool supprimer(QString p_nom, QString p_adresseIP);
    QVariant getArmoires();

private:
    QList<QObject*> m_armoires;
    BaseDeDonnees *m_pBaseDeDonnees;

signals:
    void listeArmoiresChanged();

public slots:
};

#endif // ARMOIRES_H
