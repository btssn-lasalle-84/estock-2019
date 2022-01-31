#ifndef IHMAUTHENTIFICATIONSANSBADGE_H
#define IHMAUTHENTIFICATIONSANSBADGE_H

#include <QtWidgets>

namespace Ui {
class IhmAuthentificationSansBadge;
}

class BaseDeDonnees;

class IhmAuthentificationSansBadge : public QWidget
{
    Q_OBJECT

public:
    explicit IhmAuthentificationSansBadge(QWidget *parent = nullptr);
    ~IhmAuthentificationSansBadge();

    QString getIdUtilisateur() const;
    bool estValide();
    bool estAutorise();

protected:
      void showEvent(QShowEvent *ev);

private:
    Ui::IhmAuthentificationSansBadge *ui;
    QString identifiant; //!< le login de l'utilisateur
    QString motDePasse;
    QString idUtilisateur;
    QString dateValidite;
    bool valide;
    bool autorise;
    BaseDeDonnees *bdd; //!< agrégation de l'objet BaseDeDonnees    

    void initialiserFenetre();
    void initialiserClavierVirtuel();
    void supprimerClavierVirtuel();

signals:
    void utilisateurAutorise(QString identifiant, QString motDePasse);

private slots:    
    void fermer();
    void validerAcces();
    void effacerMessage();
};

#endif // IHMAUTHENTIFICATIONSANSBADGE_H

