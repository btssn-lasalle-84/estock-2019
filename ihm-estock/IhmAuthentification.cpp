#include "IhmAuthentification.h"
#include "IhmAuthentificationSansBadge.h"
#include "ui_IhmAuthentification.h"
#include "e-stock.h"
#include "utilisateur.h"
#include "IhmGestionArmoire.h"
#include "baseDeDonnees.h"
#include "AuthentificationBadge.h"

#include <QMessageBox>

/**
  *
  * @file IhmAuthentification.cpp
  *
  * @brief Définition de la classe IhmAuthentification
  *
  * @author Thomas MACHON
  *
  * @version 0.1
  *
  */

/**
 * @brief Constructeur de la fenêtre principale
 *
 * @fn IhmAuthentification::IhmAuthentification
 *
 * @param parent QObject Adresse de l'objet Qt parent
 */
IhmAuthentification::IhmAuthentification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmAuthentification), utilisateur(nullptr)
{
    ui->setupUi(this);    
    qDebug() << Q_FUNC_INFO;

    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();

    ihmAuthentificationSansBadge = nullptr;
    authentificationBadge = new AuthentificationBadge(this);

    ihmGestionArmoire = new IhmGestionArmoire(this);
    ihmGestionArmoire->hide();

    // Connexion des signaux/slots
    connect(ui->saisieBadge, SIGNAL(editingFinished()), this, SLOT(validerAcces()));
    connect(ui->boutonPasDeBadge, SIGNAL(clicked()), this, SLOT(authentifierSansBadge()));    
    // mode développeur seulement
    connect(ui->boutonPasser, SIGNAL(clicked()), this, SLOT(passerSansBadge()));    

    initialiserFenetre();
}

/**
 * @brief Destructeur de la fenêtre principale
 *
 * @fn IhmAuthentification::~IhmAuthentification
 *
 */
IhmAuthentification::~IhmAuthentification()
{
    BaseDeDonnees::detruireInstance();
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Initialise le mode plein écran
 *
 * @fn IhmAuthentification::initialiserFenetre
 *
 */
void IhmAuthentification::initialiserFenetre()
{
    setStyleSheet(IHM_CSS);

    #ifndef DESKTOP
    const int w = qApp->desktop()->availableGeometry(this).width();
    const int h = qApp->desktop()->availableGeometry(this).height();
    resize(w, h);
    #else
    // 800×480
    resize(800, 480);
    #endif
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //showMaximized();
    setWindowModality(Qt::WindowModal);

    // Configuration de la saisie badge
    ui->saisieBadge->setFixedSize(0, 0);
    ui->saisieBadge->setFocus();
}

/**
 * @brief Affiche le message d'erreur du badge non valide
 *
 * @fn IhmAuthentification::afficherAuthentificationNonValide
 *
 */
void IhmAuthentification::afficherAuthentificationNonValide()
{
    ui->labelBadgeNonValide->setText("Badge non valide !");
    QTimer::singleShot(1000, this, SLOT(effacerMessage()));
}

/**
 * @brief Permet de reinitialiser la saisie du badge
 *
 * @fn IhmAuthentification::reinitialiserSaisieBadge
 *
 */
void IhmAuthentification::reinitialiserSaisieBadge()
{
    // Réinitialiser la saisie d'un nouveau badge
    ui->saisieBadge->setText("");
    ui->saisieBadge->setFocus();
}

/**
 * @brief Permet de valide l'acces à l'utilisateur pour le connecter à l'armoire
 *
 * @fn IhmAuthentification::validerAcces
 *
 */
void IhmAuthentification::validerAcces()
{
    if(authentificationBadge->lireBadge(ui->saisieBadge->text()))
    {
        if(authentificationBadge->estAutorise())
        {
            utilisateur = new Utilisateur(authentificationBadge->getIdUtilisateur());
            ihmGestionArmoire->setUtilisateur(utilisateur);
            ihmGestionArmoire->show();
        }
        else
        {
            afficherAuthentificationNonValide();
        }
    }
    reinitialiserSaisieBadge();
}

/**
 * @brief Permet de valide l'acces à l'utilisateur pour le connecter à l'armoire
 *
 * @fn IhmAuthentification::validerAcces
 *
 */
void IhmAuthentification::authentifierSansBadge()
{
    if(ihmAuthentificationSansBadge == nullptr)
    {
        ihmAuthentificationSansBadge = new IhmAuthentificationSansBadge(this);
        connect(ihmAuthentificationSansBadge, SIGNAL(utilisateurAutorise(QString,QString)), this, SLOT(autoriserSansBadge(QString,QString)));
    }    
    ihmAuthentificationSansBadge->show();
}

/**
 * @brief Permet à un utilisateur de s'authentifier sans le badge
 *
 * @fn IhmAuthentification::autoriserSansBadge
 *
 */
void IhmAuthentification::autoriserSansBadge(QString identifiant, QString motDePasse)
{
    qDebug() << Q_FUNC_INFO << "identifiant" << identifiant << "motDePasse" << motDePasse;
    utilisateur = new Utilisateur(ihmAuthentificationSansBadge->getIdUtilisateur());
    ihmGestionArmoire->setUtilisateur(utilisateur);
    ihmGestionArmoire->show();
}

void IhmAuthentification::passerSansBadge()
{
    utilisateur = new Utilisateur("1");
    ihmGestionArmoire->setUtilisateur(utilisateur);
    ihmGestionArmoire->show();
}


void IhmAuthentification::effacerMessage()
{
    ui->labelBadgeNonValide->setText("");
}
