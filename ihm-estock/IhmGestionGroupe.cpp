#include "IhmGestionGroupe.h"
#include "ui_IhmGestionGroupe.h"
#include "baseDeDonnees.h"
#include "utilisateur.h"

/**
 * @brief Constructeur de la Gestion de groupe
 *
 * @fn IhmGestionGroupe::IhmGestionGroupe
 *
 * @param parent QWidget*
 */
IhmGestionGroupe::IhmGestionGroupe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmGestionGroupe), utilisateur(nullptr)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    bdd = BaseDeDonnees::getInstance();
    if(!bdd->estConnecte())
        bdd->connecter();

    connect(ui->boutonFermeture, SIGNAL(clicked()), this, SLOT(fermer()));
    connect(ui->boutonAjout, SIGNAL(clicked()), this, SLOT(ajouterGroupe()));
    connect(ui->boutonSuppression, SIGNAL(clicked()), this, SLOT(supprimerGroupe()));
    connect(ui->boutonModification, SIGNAL(clicked()), this, SLOT(modifierGroupe()));

    ui->boutonAjout->setEnabled(false);
    ui->boutonModification->setEnabled(false);
    ui->boutonSuppression->setEnabled(false);
    QStringListModel *modele = new QStringListModel(this);
    modele->setStringList(QStringList{});
    ui->listViewUtilisateurs->setModel(modele);

    initialiserFenetre();
}

/**
 * @brief Destructeur de la fenêtre Gestion de Groupe
 *
 * @fn IhmGestionGroupe::~IhmGestionGroupe
 *
 */
IhmGestionGroupe::~IhmGestionGroupe()
{
    BaseDeDonnees::detruireInstance();
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Crée l'association utilisateur
 *
 * @fn IhmGestionArmoire::setUtilisateur
 *
 * @param utilisateur Utilisateur*
 */
void IhmGestionGroupe::setUtilisateur(Utilisateur *utilisateur)
{
    this->utilisateur = utilisateur;
}

/**
 * @brief Initialise le mode plein écran
 *
 * @fn IhmGestionGroupe::initialiserFenetre
 *
 */
void IhmGestionGroupe::initialiserFenetre()
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

/**
 * @brief Recharge la liste des groupes à chaque fois que la fenêtre GestionGroupe est affichée
 *
 * @fn IhmGestionGroupe::showEvent
 *
 */
void IhmGestionGroupe::showEvent(QShowEvent *ev)
{
    listerGroupe();
    gererActions(false);
}

/**
 * @brief Ferme la fenêtre
 *
 * @fn IhmGestionGroupe::fermer
 *
 */
void IhmGestionGroupe::fermer()
{
    ui->saisieNomGroupe->setText("");
    ui->cbListeGroupe->setCurrentIndex(0);
    ui->boutonAjout->setEnabled(false);
    ui->boutonModification->setEnabled(false);
    ui->boutonSuppression->setEnabled(false);
    close();
}

/**
 * @brief Sélectionne un groupe dans la liste
 *
 * @fn IhmGestionGroupe::selectionnerGroupe
 * @param nomGroupe QString le nom du groupe sélectionné
 */
void IhmGestionGroupe::selectionnerGroupe(QString nomGroupe)
{
    if(!nomGroupe.isEmpty())
    {
        ui->saisieNomGroupe->setText(nomGroupe);        
        QVector<QStringList> donnees;
        QString requete = "SELECT Nom, Prenom FROM Utilisateur WHERE idGroupe='" + getIdGroupe() + "'";
        bool retour = bdd->recuperer(requete, donnees);
        if(retour)
        {
            qDebug() << Q_FUNC_INFO << donnees;
            utilisateurs.clear();
            for(int i = 0; i < donnees.size(); i++)
            {
                utilisateurs << (donnees.at(i).at(0) + " " + donnees.at(i).at(1));
            }
            afficherListerUtilisateursGroupe();
            gererActions(true);
        }
    }
    else
    {
        ui->saisieNomGroupe->setText("");
        if(ui->listViewUtilisateurs->model()->rowCount() > 0)
            ui->listViewUtilisateurs->model()->removeRows(0, ui->listViewUtilisateurs->model()->rowCount());
        gererActions(false);
    }
}

/**
 * @brief Affiche la liste des utilisateur pour le groupe sélectionné
 *
 * @fn IhmGestionGroupe::afficherListerUtilisateursGroupe
 *
 */
void IhmGestionGroupe::afficherListerUtilisateursGroupe()
{
    QStringListModel *modele;
    modele = new QStringListModel(this);
    modele->setStringList(utilisateurs);
    ui->listViewUtilisateurs->setModel(modele);
}

/**
 * @brief Gère les état des boutons Ajout, Modification et Suppression
 *
 * @fn IhmGestionGroupe::gererActions
 *
 * @param etat bool true (Modification et Suppression actifs et pas d'Ajout) sinon l'inverse
 */
void IhmGestionGroupe::gererActions(bool etat)
{
    ui->boutonModification->setEnabled(etat);
    ui->boutonSuppression->setEnabled(etat);
    ui->boutonAjout->setEnabled(!etat);
}

/**
 * @brief Affiche la liste des groupes
 *
 * @fn IhmGestionGroupe::listerGroupe
 *
 */
void IhmGestionGroupe::listerGroupe()
{
    QString requete;

    if(utilisateur != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Nom" << utilisateur->getNom() << "Administrateur" << utilisateur->estAdministrateur() << "estGestionnaire" << utilisateur->estGestionnaire();
        if(utilisateur->estAdministrateur() || utilisateur->estGestionnaire())
        {
            requete = "SELECT * FROM Groupe";
            groupes.clear();
            bool retour = bdd->recuperer(requete, groupes);
            if(retour)
            {
                qDebug() << Q_FUNC_INFO << groupes;
                disconnect(ui->cbListeGroupe, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectionnerGroupe(QString)));
                if(ui->listViewUtilisateurs->model()->rowCount() > 0)
                    ui->listViewUtilisateurs->model()->removeRows(0, ui->listViewUtilisateurs->model()->rowCount());
                ui->cbListeGroupe->clear();
                ui->cbListeGroupe->addItem("");
                for(int i=0;i<groupes.size();i++)
                {
                    ui->cbListeGroupe->addItem(groupes.at(i).at(1));
                }
                connect(ui->cbListeGroupe, SIGNAL(currentIndexChanged(QString)), this, SLOT(selectionnerGroupe(QString)));
            }
        }
    }
}

/**
 * @brief Ajouter un groupe
 *
 * @fn IhmGestionGroupe::ajouterGroupe
 *
 */
void IhmGestionGroupe::ajouterGroupe()
{
    if(utilisateur != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Nom" << utilisateur->getNom() << "Administrateur" << utilisateur->estAdministrateur() << "estGestionnaire" << utilisateur->estGestionnaire();
        if(utilisateur->estAdministrateur() || utilisateur->estGestionnaire())
        {
            QString nomGroupe = ui->saisieNomGroupe->text();
            if(nomGroupe.isEmpty())
                return;
            QString requete = QString("INSERT INTO `Groupe` (`Nom`) VALUES('%1')").arg(nomGroupe);
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            bool retour = bdd->executer(requete);

            if(retour)
            {
                ui->saisieNomGroupe->clear();
                listerGroupe();
            }
        }
    }
}


/**
 * @brief Supprimer un groupe
 *
 * @fn IhmGestionGroupe::supprimerGroupe
 *
 */
void IhmGestionGroupe::supprimerGroupe()
{
    if(utilisateur != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Nom" << utilisateur->getNom() << "Administrateur" << utilisateur->estAdministrateur() << "estGestionnaire" << utilisateur->estGestionnaire();
        if(utilisateur->estAdministrateur() || utilisateur->estGestionnaire())
        {
            QString nomGroupe = ui->saisieNomGroupe->text();
            if(nomGroupe.isEmpty())
                return;
            QString idGroupe = getIdGroupe();
            if(idGroupe.isEmpty())
                return;
            QString requete = QString("DELETE FROM `Groupe` WHERE idGroupe='%1'").arg(idGroupe);
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            bool retour = bdd->executer(requete);

            if(retour)
            {
                ui->saisieNomGroupe->clear();
                listerGroupe();
            }
        }
    }
}

/**
 * @brief Modifier un groupe
 *
 * @fn IhmGestionGroupe::modifierGroupe
 *
 */
void IhmGestionGroupe::modifierGroupe()
{
    if(utilisateur != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "Nom" << utilisateur->getNom() << "Administrateur" << utilisateur->estAdministrateur() << "estGestionnaire" << utilisateur->estGestionnaire();
        if(utilisateur->estAdministrateur() || utilisateur->estGestionnaire())
        {
            QString nomGroupe = ui->saisieNomGroupe->text();
            if(nomGroupe.isEmpty())
                return;
            QString idGroupe = getIdGroupe();
            if(idGroupe.isEmpty())
                return;

            QString requete = QString("UPDATE `Groupe` SET `Nom`='%1' WHERE idGroupe='%2'").arg(nomGroupe).arg(idGroupe);
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            bool retour = bdd->executer(requete);

            if(retour)
            {
                ui->saisieNomGroupe->clear();
                listerGroupe();
            }
        }
    }
}

/**
 * @brief Retourne l'idGroupe du groupe sélectionné
 *
 * @fn IhmGestionGroupe::getIdGroupe
 * @return QString l'idGroupe
 */
QString IhmGestionGroupe::getIdGroupe()
{
    QString idGroupe = "";
    QString nomGroupe = ui->cbListeGroupe->currentText();
    if(nomGroupe.isEmpty())
        return idGroupe;

    for(int i=0;i<groupes.size();i++)
    {
        if(groupes.at(i).at(1) == nomGroupe)
        {
            idGroupe = groupes.at(i).at(0);
            break;
        }
    }

    qDebug() << Q_FUNC_INFO << "idGroupe" << idGroupe;
    return idGroupe;
}

QString IhmGestionGroupe::getNomUtilisateur()
{
    return QString("");
}
