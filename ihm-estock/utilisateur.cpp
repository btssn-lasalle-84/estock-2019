#include "utilisateur.h"
#include "baseDeDonnees.h"

Utilisateur::Utilisateur() : idUtilisateur(""), nom(""), prenom(""), identifiant(""), motDePasse(""), email(""), valide(false)
{
    qDebug() << Q_FUNC_INFO;
    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();
}

Utilisateur::Utilisateur(QString idUtilisateur) : idUtilisateur(idUtilisateur), nom(""), prenom(""), identifiant(""), motDePasse(""), email(""), valide(false)
{
    qDebug() << Q_FUNC_INFO;
    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();
    lire();
}

Utilisateur::~Utilisateur()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

bool Utilisateur::estAdministrateur() const
{
    if(profil == "Administrateur")
        return true;
    return false;
}

bool Utilisateur::estGestionnaire() const
{
    if(profil == "Gestionnaire")
        return true;
    return false;
}

bool Utilisateur::estUtilisateur() const
{
    if(profil == "Utilisateur")
        return true;
    return false;
}

QString Utilisateur::getIdUtilisateur() const
{
    return idUtilisateur;
}

QString Utilisateur::getIdGroupe() const
{
    return idGroupe;
}

QString Utilisateur::getNom() const
{
    return nom;
}

QString Utilisateur::getPrenom() const
{
    return prenom;
}

QString Utilisateur::getProfil() const
{
    return profil;
}

QString Utilisateur::getGroupe() const
{
    return groupe;
}

void Utilisateur::setNom(QString nom)
{
    this->nom = nom;
}

void Utilisateur::setPrenom(QString prenom)
{
    this->prenom = prenom;
}

void Utilisateur::lire()
{
    QString requete = "SELECT Utilisateur.idUtilisateur, Utilisateur.Nom, Utilisateur.Prenom, Utilisateur.DateValidite, Utilisateur.Identifiant, Utilisateur.Badge, Utilisateur.Email, Profil.idProfil, Profil.Nom AS Profil, Groupe.idGroupe, Groupe.Nom AS Groupe FROM Utilisateur INNER JOIN Groupe ON Groupe.idGroupe=Utilisateur.idGroupe INNER JOIN Profil ON Profil.idProfil=Utilisateur.idProfil WHERE Utilisateur.idUtilisateur='" + idUtilisateur + "'";
    QStringList donneesUtilisateur;
    /*
     * Exemple de résultat :
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
| idUtilisateur | Nom      | Prenom | DateValidite | Identifiant | Badge | Email                   | idProfil | Profil      | idGroupe | Groupe   |
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
|             7 | GAUTHIER | Robin  | 2019-07-01   | gauthier.r  | 4444  | rgauthier2510@gmail.com |        3 | Utilisateur |        5 | T-BTS-SN |
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
     */

    bool retour = bdd->recuperer(requete, donneesUtilisateur);
    if(retour)
    {
        qDebug() << Q_FUNC_INFO << "donneesUtilisateur" << donneesUtilisateur;

        this->idProfil = donneesUtilisateur.at(7);
        this->identifiant = donneesUtilisateur.at(4);
        this->nom = donneesUtilisateur.at(1);
        this->prenom = donneesUtilisateur.at(2);
        this->dateValidite = donneesUtilisateur.at(3);
        this->badge = donneesUtilisateur.at(5);
        this->email = donneesUtilisateur.at(6);
        this->profil = donneesUtilisateur.at(8);
        this->idGroupe = donneesUtilisateur.at(9);
        this->groupe = donneesUtilisateur.at(10);
        /**
         * @todo Vérifier la validité de l'utilisateur
         */
    }
}

bool Utilisateur::lireUtilisateur(QString identifiant, QString password)
{
    QString requete = "SELECT Utilisateur.idUtilisateur, Utilisateur.Nom, Utilisateur.Prenom, Utilisateur.DateValidite, Utilisateur.Identifiant, Utilisateur.Badge, Utilisateur.Email, Profil.idProfil, Profil.Nom AS Profil, Groupe.idGroupe, Groupe.Nom AS Groupe FROM Utilisateur INNER JOIN Groupe ON Groupe.idGroupe=Utilisateur.idGroupe INNER JOIN Profil ON Profil.idProfil=Utilisateur.idProfil WHERE Utilisateur.Identifiant='" + identifiant + "' AND Utilisateur.MotDePasse='" + password + "'";
    QStringList donneesUtilisateur;
    /*
     * Exemple de résultat :
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
| idUtilisateur | Nom      | Prenom | DateValidite | Identifiant | Badge | Email                   | idProfil | Profil      | idGroupe | Groupe   |
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
|             7 | GAUTHIER | Robin  | 2019-07-01   | gauthier.r  | 4444  | rgauthier2510@gmail.com |        3 | Utilisateur |        5 | T-BTS-SN |
+---------------+----------+--------+--------------+-------------+-------+-------------------------+----------+-------------+----------+----------+
     */

    bool retour = bdd->recuperer(requete, donneesUtilisateur);
    if(retour)
    {
        qDebug() << Q_FUNC_INFO << "donneesUtilisateur" << donneesUtilisateur;

        this->idUtilisateur = donneesUtilisateur.at(0);
        this->idProfil = donneesUtilisateur.at(7);
        this->identifiant = donneesUtilisateur.at(4);
        this->nom = donneesUtilisateur.at(1);
        this->prenom = donneesUtilisateur.at(2);
        this->dateValidite = donneesUtilisateur.at(3);
        this->badge = donneesUtilisateur.at(5);
        this->email = donneesUtilisateur.at(6);
        this->profil = donneesUtilisateur.at(8);
        this->idGroupe = donneesUtilisateur.at(9);
        this->groupe = donneesUtilisateur.at(10);
        /**
         * @todo Vérifier la validité de l'utilisateur
         */
    }
    return retour;
}

void Utilisateur::receptionDonneeUtilisateur(QString nom, QString motDePasse)
{
    this->nom = nom;
    this->motDePasse = motDePasse;
}
