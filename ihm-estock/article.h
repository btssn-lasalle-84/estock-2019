#ifndef ARTICLE_H
#define ARTICLE_H

#include <QObject>
#include <QString>

class Article : public QObject
{
    Q_OBJECT

private:
    QString nomArticle;
    int quantite;
    QString horodatage;

public:
    Article();
    ~Article();

    QString rechercherArticle();
    bool recupererArticle();
    bool restituerArticle();
    QString visualiserLesMouvements();
};

#endif // ARTICLE_H
