#ifndef GROUPE_H
#define GROUPE_H

#include <QObject>

class Groupe : public QObject
{
    Q_OBJECT
    // Les propriétés
    Q_PROPERTY(QString m_nom READ getNom WRITE setNom NOTIFY nomChanged)
    Q_PROPERTY(QString m_id READ getId WRITE setId NOTIFY idChanged)

public:
    explicit Groupe(QString p_id="", QString p_nom="", QObject *parent = nullptr);

    // Les accesseurs
    QString getNom() const;
    void setNom(QString p_nom);
    QString getId() const;
    void setId(QString p_id);

private:
    QString m_nom;
    QString m_id;

signals:
    void nomChanged();
    void idChanged();

public slots:
};

#endif // GROUPE_H
