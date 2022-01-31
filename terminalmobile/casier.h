#ifndef STOCKARMOIRE_H
#define STOCKARMOIRE_H

#include <QObject>

class Casier : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numeroCasier READ getNumeroCasier WRITE setNumeroCasier NOTIFY numeroCasierChanged)
    Q_PROPERTY(QString nomArticle READ getNomArticle WRITE setNomArticle NOTIFY nomArticleChanged)
    Q_PROPERTY(int quantite READ getQuantite WRITE setQuantite NOTIFY quantiteChanged)
    Q_PROPERTY(int disponible READ getDisponible WRITE setDisponible NOTIFY disponibleChanged)   

private:
    int numeroCasier;
    QString nomArticle;
    int quantite;
    int disponible;

public:
    explicit Casier(int numeroCasier=0, QString nomAricle="", int quantite=0, int disponible=0, QObject *parent = nullptr);

    void setCasier(int numeroCasier, QString nomArticle, int quantite, int disponible);

    int getNumeroCasier() const;
    void setNumeroCasier (int numeroCasier);

    QString getNomArticle() const;
    void setNomArticle (QString nomArticle);

    int getQuantite() const;
    void setQuantite (int quantite);

    int getDisponible() const;
    void setDisponible (int disponible);

signals:
    void numeroCasierChanged();
    void nomArticleChanged();
    void quantiteChanged();
    void disponibleChanged();

public slots:
};

#endif // STOCKARMOIRE_H
