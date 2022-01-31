#include "IhmAuthentification.h"
#include "IhmAuthentificationSansBadge.h"
#include "ui_IhmAuthentificationSansBadge.h"
#include "baseDeDonnees.h"
#include "IhmGestionArmoire.h"
#include "utilisateur.h"

/**
  *
  * @file IhmAuthentificationSansBadge.cpp
  *
  * @brief Définition de la classe IhmAuthentificationSansBadge
  *
  * @author Thomas MACHON
  *
  * @version 0.1
  *
  */

/**
 * @brief Constructeur de la fenêtre d'authentification sans badge
 *
 * @fn IhmAuthentificationSansBadge::IhmAuthentificationSansBadge
 *
 * @param parent QObject Adresse de l'objet Qt parent
 */
IhmAuthentificationSansBadge::IhmAuthentificationSansBadge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmAuthentificationSansBadge)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();

    // Connexion des signaux/slots
    connect(ui->boutonConnexion, SIGNAL(clicked()), this, SLOT(validerAcces()));
    connect(ui->boutonFermeture, SIGNAL(clicked()), this, SLOT(fermer()));

    initialiserFenetre();
}

/**
 * @brief Destructeur de la fenêtre d'authentification sans badge
 *
 * @fn IhmAuthentificationSansBadge::~IhmAuthentificationSansBadge
 */
IhmAuthentificationSansBadge::~IhmAuthentificationSansBadge()
{
    delete ui;
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Initialise le mode plein écran
 *
 * @fn IhmAuthentificationSansBadge::initialiserFenetre
 *
 */
void IhmAuthentificationSansBadge::initialiserFenetre()
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
}

void IhmAuthentificationSansBadge::showEvent(QShowEvent *ev)
{
    Q_UNUSED(ev)

    initialiserClavierVirtuel();
    ui->lineEditAuthentification->setFocus();
}

/**
 * @brief Initialisation d'un clavier virtuel
 *
 * @fn IhmAuthentificationSansBadge::initialiserClavierVirtuel
 */
void IhmAuthentificationSansBadge::initialiserClavierVirtuel()
{
    QProcess processus;
    QString programme = "/usr/bin/florence";
    QStringList arguments;
    arguments << "--use-config=/usr/share/doc/florence/examples/florence.conf";
    processus.startDetached(programme, arguments);
}

/**
 * @brief Suppression du clavier virtuel
 *
 * @fn IhmAuthentificationSansBadge::supprimerClavierVirtuel
 */
void IhmAuthentificationSansBadge::supprimerClavierVirtuel()
{
    QProcess processus;
    QString programme = "killall"; // le nom du programme
    QStringList arguments; // arguments du programme
    arguments << "florence";
    processus.startDetached(programme, arguments);
}

/**
 * @brief Permet de fermer le clavier virtuel
 *
 * @fn IhmAuthentificationSansBadge::fermer
 */
void IhmAuthentificationSansBadge::fermer()
{
    supprimerClavierVirtuel();
    close();
}

/**
 * @brief Permet de valide l'acces à l'utilisateur avec son identifiant, mot de passe
 *
 * @fn IhmAuthentificationSansBadge::validerAcces
 */
void IhmAuthentificationSansBadge::validerAcces()
{
    if(estAutorise())
    {
        close();
        emit utilisateurAutorise(identifiant, motDePasse);
    }
    else
    {
        ui->labelMessagAuthentificatioSansBadge->setText("Identifiant non valide !");
        QTimer::singleShot(1000, this, SLOT(effacerMessage()));
    }
    // Réinitialiser la saisie d'un nouvel utilisateur
    ui->lineEditAuthentification->setText("");
    ui->lineEditMotDePasse->setText("");
    ui->lineEditAuthentification->setFocus();
}

/**
 * @brief Requete SQL pour valider l'identifiant de l'utilisateur et son mot de passe
 *
 * @fn IhmAuthentificationSansBadge::estValide
 *
 * @return valide
 */
bool IhmAuthentificationSansBadge::estValide()
{
    QString dateMaintenant = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString requete = "SELECT DateValidite FROM Utilisateur WHERE Identifiant='" + ui->lineEditAuthentification->text() + "' AND DateValidite>='" + dateMaintenant + "'";
    qDebug() << Q_FUNC_INFO << "requete" << requete;
    QString retour;
    valide = bdd->recuperer(requete, retour);
    qDebug() << Q_FUNC_INFO << "valide" << valide << "dateValidite" << dateValidite;
    return valide;
}

/**
 * @brief Retourne l'identifiant de l'utilisateur
 *
 * @fn IhmAuthentificationSansBadge::getIdUtilisateur
 *
 * @return idUtilisateur*
 */
QString IhmAuthentificationSansBadge::getIdUtilisateur() const
{
    return idUtilisateur;
}

/**
 * @brief Requete SQL pour autoriser l'acces de l'utilisateur.
 *
 * @fn IhmAuthentificationSansBadge::estValide
 *
 * @return valide && estValide
 */
bool IhmAuthentificationSansBadge::estAutorise()
{
    QString dateMaintenant = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    identifiant = ui->lineEditAuthentification->text();
    motDePasse = ui->lineEditMotDePasse->text();

    QString requete = "SELECT idUtilisateur, DateValidite FROM Utilisateur WHERE Identifiant='" + ui->lineEditAuthentification->text() + "' AND MotDePasse='" + ui->lineEditMotDePasse->text() + "'";
    QStringList donneesUtilisateur;
    idUtilisateur.clear();
    dateValidite.clear();
    motDePasse.clear();
    valide = bdd->recuperer(requete, donneesUtilisateur);
    if(valide)
    {
        idUtilisateur = donneesUtilisateur.at(0);
        dateValidite = donneesUtilisateur.at(1);
        qDebug() << Q_FUNC_INFO << "valide" << valide << "idUtilisateur" << idUtilisateur << "dateValidite" << dateValidite << "motDePasse" << motDePasse;
    }
    qDebug() << Q_FUNC_INFO << "valide" << valide;
    return (valide && estValide());
}

void IhmAuthentificationSansBadge::effacerMessage()
{
    ui->labelMessagAuthentificatioSansBadge->setText("");
}
