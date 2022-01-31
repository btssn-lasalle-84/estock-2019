#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QObject>
#include <QString>

class BaseDeDonnees;
class ihmAuthentificationSansBadge;

class Utilisateur : public QObject
{
    Q_OBJECT

private:
    QString idProfil;
    QString idUtilisateur;
    QString idGroupe;
    QString nom;
    QString prenom;
    QString badge;
    QString dateValidite;
    QString identifiant;
    QString motDePasse;
    QString email;
    QString profil;
    QString groupe;
    bool valide;
    BaseDeDonnees *bdd; //!< agrégation de l'objet BaseDeDonnees

    void lire();

public:
    Utilisateur();
    Utilisateur(QString idUtilisateur);
    ~Utilisateur();

    bool estAdministrateur() const;
    bool estGestionnaire() const;
    bool estUtilisateur() const;
    QString getIdUtilisateur() const;
    QString getIdGroupe() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getProfil() const;
    QString getGroupe() const;
    void setNom(QString nom);
    void setPrenom(QString prenom);
    bool lireUtilisateur(QString identifiant, QString password);

public slots:
    void receptionDonneeUtilisateur(QString nom,QString motDePasse);
};

#endif // UTILISATEUR_H
