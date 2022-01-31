#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <QObject>

class Mouvement : public QObject
{
    Q_OBJECT

    // Les propriétés
    Q_PROPERTY(QString m_casier READ getCasier WRITE setCasier NOTIFY casierChanged)
    Q_PROPERTY(QString m_horodatage READ getHorodatage WRITE setHorodatage NOTIFY horodatageChanged)
    Q_PROPERTY(QString m_utilisateur READ getUtilisateur WRITE setUtilisateur NOTIFY utilisateurChanged)
    Q_PROPERTY(QString m_action READ getAction WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(QString m_contenu READ getContenu WRITE setContenu NOTIFY contenuChanged)
    Q_PROPERTY(QString m_quantite READ getQuantite WRITE setQuantite NOTIFY quantiteChanged)

public:
    explicit Mouvement(QString p_casier="", QString p_horodatage="", QString p_utilisateur="", QString p_action="",
                       QString p_contenu="", QString p_quantite="", QObject *p_parent = nullptr);

    void setMouvement(QStringList p_mouvement);
    // Les accesseurs

    QString getCasier() const;
    void setCasier(QString p_casier);

    QString getHorodatage() const;
    void setHorodatage(QString p_horodatage);

    QString getUtilisateur() const;
    void setUtilisateur(QString p_utilisateur);

    QString getAction() const;
    void setAction(QString p_action);

    QString getContenu() const;
    void setContenu(QString p_contenu);

    QString getQuantite() const;
    void setQuantite(QString quantite);

private:
    QString m_casier;
    QString m_horodatage;
    QString m_utilisateur;
    QString m_action;
    QString m_contenu;
    QString m_quantite;

signals:
    void casierChanged();
    void horodatageChanged();
    void utilisateurChanged();
    void actionChanged();
    void contenuChanged();
    void quantiteChanged();

public slots:
};

#endif // MOUVEMENT_H
