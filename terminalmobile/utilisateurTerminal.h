#ifndef UTILISATEUR_TERMINAL_H
#define UTILISATEUR_TERMINAL_H

#include <QObject>

class BaseDeDonnees;

class UtilisateurTerminal : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Nom MEMBER m_nom NOTIFY utilisateurUpdated)
    Q_PROPERTY(QString Prenom MEMBER m_prenom NOTIFY utilisateurUpdated)

public:
    UtilisateurTerminal(QObject *p_parent = nullptr);
    ~UtilisateurTerminal();

    Q_INVOKABLE bool lireUtilisateur(QString p_identifiant, QString p_password, bool p_doForceLogin);
    Q_INVOKABLE bool reinitialiser();
    Q_INVOKABLE bool estExistant();
    Q_INVOKABLE bool estAutorise();

    QString getNom() const;
    QString getPrenom() const;

private:
    QString m_idProfil;
    QString m_idGroupe;
    QString m_identifiant;
    QString m_nom;
    QString m_prenom;
    QString m_dateValidite;
    QString m_badge;
    QString m_idUtilisateur;

    QString m_profil; // TODO
    QString m_groupe; // TODO

    BaseDeDonnees *m_pBaseDeDonnees;
    bool m_estExistant;
    bool m_estAutorise;

signals:
    void utilisateurUpdated();

public slots:
};

#endif // UTILISATEUR_TERMINAL_H
