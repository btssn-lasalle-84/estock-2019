#ifndef MOUVEMENTS_H
#define MOUVEMENTS_H

#include <QObject>
#include <QVariant>

class BaseDeDonnees;

class Mouvements : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant listeMouvements READ getMouvements NOTIFY listeMouvementsChanged)

public:
    explicit Mouvements(QObject *p_parent = nullptr);
    ~Mouvements();
    Q_INVOKABLE bool lire();
    QVariant getMouvements();

private:
    QList<QObject*> m_mouvements;
    BaseDeDonnees *m_pBaseDeDonnees;

signals:
    void listeMouvementsChanged();

public slots:
};

#endif // MOUVEMENTS_H
