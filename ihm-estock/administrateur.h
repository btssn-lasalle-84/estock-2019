#ifndef ADMINISTATEUR_H
#define ADMINISTATEUR_H

#include <QObject>
#include <QString>

class Administrateur : public QObject
{
    Q_OBJECT

private:
    char nom;
    char prenom;
    QString identifiantConnextion;
    QString motDePasse;
    QString mail;

public:
    Administrateur();
    ~Administrateur();
    char getNom();
    char getPrenom();
    void setNom();
    void setPrenom();
};
#endif // ADMINISTATEUR_H
