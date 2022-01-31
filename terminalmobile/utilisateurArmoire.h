#ifndef UTILISATEUR_ARMOIRE_H
#define UTILISATEUR_ARMOIRE_H

#include <QObject>

class UtilisateurArmoire : public QObject
{
    Q_OBJECT
    // Les propriétés
    Q_PROPERTY(QString m_nomProfil READ getNomProfil WRITE setNomProfil NOTIFY nomProfilChanged)
    Q_PROPERTY(QString m_nomGroupe READ getNomGroupe WRITE setNomGroupe NOTIFY nomGroupeChanged)
    Q_PROPERTY(QString m_nom READ getNom WRITE setNom NOTIFY nomChanged)
    Q_PROPERTY(QString m_prenom READ getPrenom WRITE setPrenom NOTIFY prenomChanged)
    Q_PROPERTY(QString m_dateDeValidite READ getDateDeValidite WRITE setDateDeValidite NOTIFY dateDeValiditeChanged)
    Q_PROPERTY(QString m_identifiant READ getIdentifiant WRITE setIdentifiant NOTIFY identifiantChanged)
    Q_PROPERTY(QString m_badge READ getBadge WRITE setBadge NOTIFY badgeChanged)
    Q_PROPERTY(QString m_idUtilisateur READ getIdUtilisateur WRITE setIdUtilisateur NOTIFY idUtilisateurChanged)

public:
    explicit UtilisateurArmoire(QString p_nomProfil="", QString p_idGroupe="", QString p_nom="", QString p_prenom="",
                                QString p_dateDeValidite="", QString p_identifiant="", QString p_badge="",
                                QString p_idUtilisateur="", QObject *p_parent = nullptr);

    void setUtilisateurArmoire(QStringList p_utilisateurArmoire);

    // Les accesseurs
    QString getNomProfil() const;
    void setNomProfil(QString p_nomProfil);

    QString getNomGroupe() const;
    void setNomGroupe(QString p_nomGroupe);

    QString getNom() const;
    void setNom(QString p_nom);

    QString getPrenom() const;
    void setPrenom(QString p_prenom);

    QString getDateDeValidite() const;
    void setDateDeValidite(QString p_dateDeValidite);

    QString getIdentifiant() const;
    void setIdentifiant(QString p_identifiant);

    QString getBadge() const;
    void setBadge(QString p_badge);

    QString getIdUtilisateur() const;
    void setIdUtilisateur(QString p_idUtilisateur);

private:
    QString m_nomProfil;
    QString m_nomGroupe;
    QString m_nom;
    QString m_prenom;
    QString m_dateDeValidite;
    QString m_identifiant;
    QString m_badge;
    QString m_idUtilisateur;

signals:
    void nomProfilChanged();
    void nomGroupeChanged();
    void nomChanged();
    void prenomChanged();
    void dateDeValiditeChanged();
    void identifiantChanged();
    void badgeChanged();
    void idUtilisateurChanged();

public slots:
};

#endif
