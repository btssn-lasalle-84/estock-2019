#ifndef ARMOIRE_H
#define ARMOIRE_H

#include <QObject>

class Armoire : public QObject
{
    Q_OBJECT
    // Les propriétés
    Q_PROPERTY(QString m_nom READ getNom WRITE setNom NOTIFY nomChanged)
    Q_PROPERTY(QString m_adresseIP READ getAdresseIP WRITE setAdresseIP NOTIFY adresseIPChanged)

public:
    explicit Armoire(QString p_nom="", QString p_adresseIP="", QObject *parent = nullptr);
    void setArmoire(QStringList p_armoire);
    // Les accesseurs
    QString getNom() const;
    void setNom(QString p_nom);
    QString getAdresseIP() const;
    void setAdresseIP(QString p_adresseIP);

private:
    QString m_nom;
    QString m_adresseIP;

signals:
    void nomChanged();
    void adresseIPChanged();

public slots:
};

#endif // ARMOIRE_H
