#ifndef IHMGESTIONARMOIRE_H
#define IHMGESTIONARMOIRE_H

#include <QtWidgets>

#define NB_CASIERS_MAX  8

namespace Ui {
class IhmGestionArmoire;
}

class BaseDeDonnees;
class Utilisateur;
class GestionBalances;
class IhmGestionGroupe;
class Casier;
class Article;
class AuthentificationBadge;
class IhmAuthentificationSansBadge;

class IhmGestionArmoire : public QWidget
{
    Q_OBJECT

public:
    explicit IhmGestionArmoire(QWidget *parent = nullptr);
    ~IhmGestionArmoire();

    Utilisateur *getUtilisateur();
    Casier *getCasier();
    void setUtilisateur(Utilisateur *utilisateur);

protected:
      void showEvent(QShowEvent *ev);

private:
    Ui::IhmGestionArmoire *ui; //!< agrégation de la définition de la fenêtre UI
    BaseDeDonnees *bdd; //!< agrégation de l'objet BaseDeDonnees
    Utilisateur *utilisateur;
    GestionBalances *gestionBalances;
    IhmGestionGroupe *ihmGestionGroupe; //!< la fenêtre de gestion des groupes
    QVector<Casier *> casiers; //!< les casier de l'armoire
    QVector<QStringList> articlesTrouves;
    Article *article;

    void initialiserFenetre();
    void initialiserClavierVirtuel();
    void supprimerClavierVirtuel();
    void fermerClavierVirtuel();
    void afficherCasiers();
    QString lireAdresseIP();

public slots:
    void fermer();
    void gererGroupe();
    void selectionnerCasier(int);
    void rechercherArticle();
    void effacerRechercheArticle();
    void effacerLaListeArticle();
    void effacerLaSelectionArticle();
    void effacerMessageNumeroCasier();
    void selectionnerArticle(int index);
};

#endif // IHMGESTIONARMOIRE_H
