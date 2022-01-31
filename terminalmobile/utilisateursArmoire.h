#ifndef UTILISATEURS_ARMOIRE_H
#define UTILISATEURS_ARMOIRE_H

#include <QObject>
#include <QVariant>

class BaseDeDonnees;

class UtilisateursArmoire : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant listeUtilisateursArmoire READ getUtilisateursArmoire NOTIFY listeUtilisateursArmoireChanged)
    Q_PROPERTY(QVariant listeProfil READ getListeProfil NOTIFY listeProfilChanged)
    Q_PROPERTY(QVariant listeGroupe READ getListeGroupe NOTIFY listeGroupeChanged)

public:
    explicit UtilisateursArmoire(QObject *p_parent = nullptr);
    ~UtilisateursArmoire();
    Q_INVOKABLE bool lire();
    Q_INVOKABLE bool lireProfil();
    Q_INVOKABLE bool lireGroupe();
    //Q_INVOKABLE bool lireUtilisateurs();
    Q_INVOKABLE bool inserer(QString p_idProfil, QString p_idGroupe, QString p_nom, QString p_prenom, QString p_dateDeValidite, QString p_identifiant, QString p_badge);
    Q_INVOKABLE bool modifier(QString p_idProfil, QString p_idGroupe, QString p_nom, QString p_prenom, QString p_dateDeValidite, QString p_identifiant, QString p_badge, QString p_idUtilisateur);
    Q_INVOKABLE bool supprimer(QString m_nomProfil, QString m_nomGroupe, QString m_nom, QString m_prenom, QString m_dateDeValidite, QString m_identifiant, QString m_badge, QString p_idUtilisateur);
    QVariant getUtilisateursArmoire();
    QVariant getListeProfil();
    QVariant getListeGroupe();

private:
    QList<QObject*> m_utilisateursArmoire;
    QList<QObject*> m_listeProfil;
    QList<QObject*> m_listeGroupe;
    BaseDeDonnees *m_pBaseDeDonnees;

signals:
    void listeUtilisateursArmoireChanged();
    void listeProfilChanged();
    void listeGroupeChanged();

public slots:
};

#endif // UTILISATEURS_ARMOIRE_H
