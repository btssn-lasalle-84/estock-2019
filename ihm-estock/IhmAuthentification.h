#ifndef IHMAUTHENTIFICATION_H
#define IHMAUTHENTIFICATION_H

/**
  *
  * @file IhmAuthentification.h
  *
  * @brief Déclaration de la classe IhmAuthentification
  *
  * @author Thomas MACHON
  *
  * @version 1.1
  *
  */

#include <QtWidgets>

namespace Ui
{
    class IhmAuthentification;
}

class AuthentificationBadge;
class IhmAuthentificationSansBadge;
class IhmGestionArmoire;
class BaseDeDonnees;
class Utilisateur;

/**
  *
  * @class IhmAuthentification
  *
  * @brief La fenêtre principale de l'application
  *
  * @author Thomas MACHON
  *
  * @version 1.1
  *
  */
class IhmAuthentification : public QWidget
{
    Q_OBJECT

public:
    explicit IhmAuthentification(QWidget *parent = nullptr);
    ~IhmAuthentification();

private:
    Ui::IhmAuthentification *ui; //!< agrégation de la définition de la fenêtre UI
    AuthentificationBadge *authentificationBadge;
    IhmAuthentificationSansBadge *ihmAuthentificationSansBadge;
    IhmGestionArmoire *ihmGestionArmoire;
    Utilisateur *utilisateur;
    Utilisateur *administateur;
    BaseDeDonnees *bdd; //!< agrégation de l'objet BaseDeDonnees    

    void initialiserFenetre();    
    void afficherAuthentificationNonValide();
    void reinitialiserSaisieBadge();

public slots:
    void validerAcces();
    void authentifierSansBadge();
    void autoriserSansBadge(QString identifiant, QString motDePasse);
    void effacerMessage();
    void passerSansBadge(); // mode développeur seulement
};

#endif // IHMAUTHENTIFICATION_H
