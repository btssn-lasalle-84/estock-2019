#ifndef IHMGESTIONGROUPE_H
#define IHMGESTIONGROUPE_H

/**
  *
  * @file IhmGestionGroupe.h
  *
  * @brief Déclaration de la classe IhmGestionGroupe
  *
  * @author Hadrien GIMENEZ
  *
  * @version 1.1
  *
  */

#include <QtWidgets>

namespace Ui {
class IhmGestionGroupe;
}

class IhmGestionArmoire;
class Utilisateur;
class BaseDeDonnees;

/**
  *
  * @class IhmGestionGroupe
  *
  * @brief La fenêtre de gestion des groupes
  *
  * @author Hadrien GIMENEZ
  *
  * @version 1.1
  *
  */
class IhmGestionGroupe : public QWidget
{
    Q_OBJECT

public:
    explicit IhmGestionGroupe(QWidget *parent = nullptr);
    ~IhmGestionGroupe();

    void setUtilisateur(Utilisateur *utilisateur);

protected:
      void showEvent(QShowEvent *ev);

private:
    Ui::IhmGestionGroupe *ui; //!< agrégation de la définition de la fenêtre UI
    BaseDeDonnees *bdd; //!< agrégation de l'objet BaseDeDonnees
    Utilisateur *utilisateur;
    QVector<QStringList> groupes; //!< les groupes
    QStringList utilisateurs;

    void initialiserFenetre();    
    void listerGroupe();
    void afficherListerUtilisateursGroupe();
    void gererActions(bool etat);
    QString getIdGroupe();
    QString getNomUtilisateur();

public slots:
    void fermer();    
    void selectionnerGroupe(QString nomGroupe);
    void ajouterGroupe();
    void supprimerGroupe();
    void modifierGroupe();
};

#endif // IHMGESTIONGROUPE_H
