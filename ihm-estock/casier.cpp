#include "casier.h"
#include <QDebug>

Casier::Casier(int numero, bool autorise, bool ouvert, QWidget *parent) : QLabel(parent), numero(numero), autorise(autorise), ouvert(ouvert)
{
    qDebug() << Q_FUNC_INFO << numero;
    // choix par défaut
    setText("Casier " + QString::number(numero));
    if(autorise)
    {
        setStyleSheet("background-color: rgb(239, 41, 41);");
    }
    else
    {
        setStyleSheet("background-color: rgb(85, 85, 85);");
    }

    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter); // centré
    setContentsMargins(10, 0, 10, 0); // Marges : Gauche Haut Droite Bas
}

Casier::~Casier()
{
    qDebug() << Q_FUNC_INFO << numero;
}

bool Casier::estAutorise() const
{
    return autorise;
}

bool Casier::estOuvert() const
{
    return ouvert;
}

void Casier::actionner()
{
    if(!autorise)
        return;
    if(ouvert)
        fermer();
    else
        ouvrir();
}

void Casier::ouvrir()
{
    if(!autorise)
        return;
    /**
     * @todo envoyer trame ouverture
     */
    setStyleSheet("background-color: rgb(115, 210, 22);");
    ouvert = true;
}

void Casier::fermer()
{
    if(!autorise)
        return;
    /**
     * @todo envoyer trame fermeture
     */
    setStyleSheet("background-color: rgb(239, 41, 41);");
    ouvert = false;
}

void Casier::mousePressEvent(QMouseEvent *event)
{
    if(!autorise)
        return;

    if(event->button() == Qt::LeftButton)
    {
        if(autorise)
        {
            emit clicked(numero);
            emit clicked();
        }
    }
}
