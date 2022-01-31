#include "IhmGestionArmoire.h"
#include "ui_IhmGestionArmoire.h"
#include "utilisateur.h"
#include "IhmGestionGroupe.h"
#include "IhmAuthentification.h"
#include "IhmAuthentificationSansBadge.h"
#include "baseDeDonnees.h"
#include "casier.h"
#include "GestionBalances.h"
#include <QNetworkInterface>

/**
  *
  * @file IhmGestionArmoire.cpp
  *
  * @brief Définition de la classe IhmGestionArmoire
  *
  * @author Thomas MACHON
  *
  * @version 0.1
  *
  */

/**
 * @brief Constructeur de la fenêtre gestion armoire
 *
 * @fn IhmAuthentificationSansBadge::IhmAuthentificationSansBadge
 *
 * @param parent QObject Adresse de l'objet Qt parent
 */
IhmGestionArmoire::IhmGestionArmoire(QWidget *parent) : QWidget(parent), ui(new Ui::IhmGestionArmoire), utilisateur(nullptr)//, casiers(NB_CASIERS_MAX, nullptr)
{
    ui->setupUi(this);    
    qDebug() << Q_FUNC_INFO;

    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();

    // crée les casiers
    afficherCasiers();

    ihmGestionGroupe = new IhmGestionGroupe(this);
    ihmGestionGroupe->hide();

    // Temporaire
    //gestionBalances = new GestionBalances;

    connect(ui->boutonFermeture, SIGNAL(clicked()), this, SLOT(fermer()));
    //connect(ui->lineEditRechercheArticle, SIGNAL(editingFinished()), this, SLOT(rechercherArticle()));
    connect(ui->boutonRechercheArticle, SIGNAL(clicked()), this, SLOT(rechercherArticle()));
    connect(ui->comboBoxListeArticles, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionnerArticle(int)));
    // pour administrateur
    connect(ui->boutonGestionGroupe, SIGNAL(clicked()), this, SLOT(gererGroupe()));    

    initialiserFenetre();
}

/**
 * @brief Destructeur de la fenêtre gestion armoire
 *
 * @fn IhmGestionArmoire::~IhmGestionArmoire
 *
 */
IhmGestionArmoire::~IhmGestionArmoire()
{
    BaseDeDonnees::detruireInstance();
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Retourne l'association utilisateur
 *
 * @fn IhmGestionArmoire::getUtilisateur
 *
 * @return Utilisateur*
 */
Utilisateur *IhmGestionArmoire::getUtilisateur()
{
    return utilisateur;
}

/**
 * @brief Crée l'association utilisateur
 *
 * @fn IhmGestionArmoire::setUtilisateur
 *
 * @param utilisateur Utilisateur*
 */
void IhmGestionArmoire::setUtilisateur(Utilisateur *utilisateur)
{
    this->utilisateur = utilisateur;
    if(utilisateur->estAdministrateur() || utilisateur->estGestionnaire())
        ui->boutonGestionGroupe->setEnabled(true);
    else
        ui->boutonGestionGroupe->setEnabled(false);
}

/**
 * @brief S'exécute à chaque fois que la fenêtre IhmGestionArmoire est affichée
 *
 * @fn IhmGestionArmoire::showEvent
 *
 */
void IhmGestionArmoire::showEvent(QShowEvent *ev)
{
    QString informationsUtilisateur;
    QString informationsGroupe;
    // Affiche des informations sur l'utilisateur qui a accès à l'armoire
    if(utilisateur != nullptr)
    {
        informationsUtilisateur = utilisateur->getNom() + " " + utilisateur->getPrenom();
        informationsGroupe = utilisateur->getGroupe();
    }
    ui->labelUtilisateur->setText(informationsUtilisateur);
    ui->labelGroupe->setText(informationsGroupe);

    initialiserClavierVirtuel();
}

/**
 * @brief Initialise le mode plein écran
 *
 * @fn IhmGestionArmoire::initialiserFenetre
 *
 */
void IhmGestionArmoire::initialiserFenetre()
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
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog); // Ajouter Qt::WindowStaysOnTopHint
    //showMaximized();
    setWindowModality(Qt::WindowModal);
    ui->lineEditRechercheArticle->setFocus();
}

/**
 * @brief Initialise le clavier virtuel
 *
 * @fn IhmGestionArmoire::initialiserClavierVirtuel
 *
 */
void IhmGestionArmoire::initialiserClavierVirtuel()
{
    QProcess processus;
    QString programme = "/usr/bin/florence";
    QStringList arguments;
    arguments << "--use-config=/usr/share/doc/florence/examples/florence.conf";
    processus.startDetached(programme, arguments);
}

/**
 * @brief Supprime le clavier virtuel
 *
 * @fn IhmGestionArmoire::supprimerClavierVirtuel
 *
 */
void IhmGestionArmoire::supprimerClavierVirtuel()
{
    QProcess processus;
    QString programme = "killall"; // le nom du programme
    QStringList arguments; // arguments du programme
    arguments << "florence";
    processus.startDetached(programme, arguments);
}

/**
 * @brief ferme le clavier virtuel
 *
 * @fn IhmGestionArmoire::fermerClavierVirtuel
 *
 */
void IhmGestionArmoire::fermerClavierVirtuel()
{
    supprimerClavierVirtuel();
    close();
}

/**
 * @brief ferme l'IhmGestionArmoire et supprime l'utilisateur crée
 *
 * @fn IhmGestionArmoire::fermer
 *
 */
void IhmGestionArmoire::fermer()
{
    if(utilisateur != nullptr)
    {
        delete utilisateur;
        utilisateur = nullptr;
    }
    close();
    effacerLaListeArticle();
    effacerLaSelectionArticle();
    effacerMessageNumeroCasier();
}

/**
 * @brief Identifiaction du status de l'utilisateur gestionnaire ou administrateur
 *
 * @fn IhmGestionArmoire::gererGroupe
 *
 */
// pour administateur ou gestionnaire
void IhmGestionArmoire::gererGroupe()
{
    qDebug() << Q_FUNC_INFO << "Nom" << utilisateur->getNom() << "Administrateur" << utilisateur->estAdministrateur() << "estGestionnaire" << utilisateur->estGestionnaire();
    if(utilisateur->estAdministrateur() || utilisateur->estGestionnaire())
    {
        ihmGestionGroupe->setUtilisateur(utilisateur);
        ihmGestionGroupe->show();
    }
}

/**
 * @brief Permet de savoir quel casier a était sélectionner
 *
 * @fn IhmGestionArmoire::selectionnerCasier
 *
 * @param numeroCasier int
 *
 */
void IhmGestionArmoire::selectionnerCasier(int numeroCasier)
{
    qDebug() << Q_FUNC_INFO << "numeroCasier" << numeroCasier;
    QString requete = "SELECT Stock.NumeroCasier, Article.idType, Article.Nom, Stock.Quantite, Stock.Disponible, Article.Designation FROM Stock INNER JOIN Article ON Stock.idArticle = Article.idArticle WHERE Stock.NumeroCasier='" + QString::number(numeroCasier) + "'";
    qDebug() << Q_FUNC_INFO << requete;
    QStringList articleCasier;
    bdd->recuperer(requete, articleCasier);
    qDebug() << Q_FUNC_INFO << "articleCasier" << articleCasier;
    casiers[numeroCasier-1]->actionner();
}

/**
 * @brief Requete permettant la recherche d'article dans les casiers
 *
 * @fn IhmGestionArmoire::rechercherArticle
 *
 */
void IhmGestionArmoire::rechercherArticle()
{
    QString mot = ui->lineEditRechercheArticle->text();
    qDebug() << Q_FUNC_INFO << mot;
    /*if(mot.isEmpty())
        return;*/
    QString requete = "SELECT Stock.NumeroCasier, Article.idType, Article.Nom, Stock.Quantite, Stock.Disponible, Article.Designation FROM Stock INNER JOIN Article ON Stock.idArticle = Article.idArticle WHERE Article.Nom LIKE '%" + mot + "%' OR Article.Code LIKE '%" + mot + "%' OR Article.Designation LIKE '%" + mot + "%' ORDER BY Stock.NumeroCasier ASC";
    //QString requete = "SELECT * FROM Article WHERE Nom LIKE '%" + mot + "%' OR Code LIKE '%" + mot + "%' OR Designation LIKE '%" + mot + "%'";
    qDebug() << Q_FUNC_INFO << requete;
    disconnect(ui->comboBoxListeArticles, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionnerArticle(int)));
    ui->comboBoxListeArticles->clear();
    articlesTrouves.clear();
    bdd->recuperer(requete, articlesTrouves);
    qDebug() << Q_FUNC_INFO << "articlesTrouves" << articlesTrouves.size() << articlesTrouves;

    ui->comboBoxListeArticles->addItem("Sélectionner un article");
    for(int i = 0 ; i < articlesTrouves.size() ; i++)
    {
        ui->comboBoxListeArticles->addItem(articlesTrouves[i].at(2));
    }
    connect(ui->comboBoxListeArticles, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionnerArticle(int)));

    /*if(articlesTrouves.size() > 0)
    {
        selectionnerArticle(1);
        ui->labelMessageNumeroCasier->setText("L'article se trouve\ndans le casier numéro : " + articlesTrouves[0].at(0));
    }*/
    effacerRechercheArticle();
}

void IhmGestionArmoire::effacerRechercheArticle()
{
    ui->lineEditRechercheArticle->setText("");
}

/**
 * @brief Affiche l'article selectionner
 *
 * @fn IhmGestionArmoire::rechercherArticle
 *
 */
void IhmGestionArmoire::selectionnerArticle(int index)
{
    if(articlesTrouves.size() == 0 || index < 0)
        return;
    if(index > 0)
    {
        //Stock.NumeroCasier, Article.idType, Article.Nom, Stock.Quantite, Stock.Disponible, Article.Designation
        QString article = articlesTrouves[index-1].at(5);
        QString qte = QString::fromUtf8("Quantité : ") + articlesTrouves[index-1].at(3);
        QString dispo = QString::fromUtf8("Disponible : ") + articlesTrouves[index-1].at(4);
        ui->labelMessageArticle->setText(article + "\n" + qte + "\n" + dispo);
        ui->labelMessageNumeroCasier->setText("Casier " + articlesTrouves[index-1].at(0));
    }
    else
    {
        ui->labelMessageArticle->setText("");
        ui->labelMessageNumeroCasier->setText("");
    }
}

void IhmGestionArmoire::effacerLaListeArticle()
{
    ui->comboBoxListeArticles->clear();
}

void IhmGestionArmoire::effacerLaSelectionArticle()
{
    ui->labelMessageArticle->setText("");
}

void IhmGestionArmoire::effacerMessageNumeroCasier()
{
    ui->labelMessageNumeroCasier->setText("");
}

void IhmGestionArmoire::afficherCasiers()
{
    QString nbCasiers;
    QString adresseIP = lireAdresseIP();
    qDebug() << Q_FUNC_INFO << "adresseIP" << adresseIP;
    if(!adresseIP.isEmpty())
    {
        QString requeteNbCasiers = "SELECT Armoire.nbCasiers FROM Armoire WHERE Armoire.AdresseIP = '" + adresseIP + "'";
        bdd->recuperer(requeteNbCasiers, nbCasiers);
        qDebug() << Q_FUNC_INFO << "nbCasiers" << nbCasiers;
        for(int i=0; i < nbCasiers.toInt(); i++)
        {
            Casier* casier = new Casier(i+1, true, false, this); // autorisé et présent
            casiers.push_back(casier);
            connect(casier, SIGNAL(clicked(int)), this, SLOT(selectionnerCasier(int)));
            // pair/impair -> droite/gauche ?
            if((i+1)%2)
            {
                ui->gridLayoutArmoire->addWidget(casier, i/2, 0, 1, 1);
            }
            else
            {
                ui->gridLayoutArmoire->addWidget(casier, i/2, 1, 1, 1);
            }
        }
    }
}

QString IhmGestionArmoire::lireAdresseIP()
{
    //QNetworkInterface interface = QNetworkInterface::interfaceFromName("wlan0");
    //qDebug() << Q_FUNC_INFO << interface.hardwareAddress();
    QList<QHostAddress> adresses = QNetworkInterface::allAddresses();
    for(int i = 0; adresses.size(); i++)
    {
        if(adresses.at(i).isInSubnet(QHostAddress::parseSubnet("192.168.52.0/24")))
            return adresses.at(i).toString();
    }

    return QString("");
}
