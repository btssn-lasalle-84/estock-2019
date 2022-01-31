#ifndef BADGE_H
#define BADGE_H

#include <QObject>
#include <QString>

class BaseDeDonnees;

class AuthentificationBadge : public QObject
{
    Q_OBJECT

private:
    QString identifiantBadge; //!< l'UID du badge
    QString idUtilisateur;
    QString dateValidite;
    bool valide;
    bool autorise;
    BaseDeDonnees *bdd;

public:
    AuthentificationBadge(QObject *parent = nullptr);
    ~AuthentificationBadge();

    bool estValide();
    bool estAutorise();
    QString getIdUtilisateur() const;
    QString getDateValidite() const;
    QString getIdentifiantBadge() const;
    bool lireBadge(QString badge);

public slots:    

signals:

};

#endif // BADGE_H
