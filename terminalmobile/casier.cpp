#include "casier.h"
#include "baseDeDonnees.h"

Casier::Casier(int numeroCasier, QString nomArticle, int quantite, int disponible, QObject *parent) : QObject(parent), numeroCasier(numeroCasier), nomArticle(nomArticle), quantite(quantite), disponible(disponible)
{

}

void Casier::setCasier( int numeroCasier, QString nomArticle, int quantite, int disponible)
{
    numeroCasier = numeroCasier;
    nomArticle = nomArticle;
    quantite = quantite;
    disponible = disponible;
}

int Casier::getNumeroCasier() const
{
    return numeroCasier;
}

void Casier::setNumeroCasier(int numeroCasier)
{
    numeroCasier = numeroCasier;
}

QString Casier::getNomArticle() const
{
    return nomArticle;
}

void Casier::setNomArticle(QString nomArticle)
{
    nomArticle = nomArticle;
}

int Casier::getDisponible() const
{
    return disponible;
}

void Casier::setDisponible(int disponible)
{
    disponible = disponible;
}

int Casier::getQuantite() const
{
    return quantite;
}

void Casier::setQuantite(int quantite)
{
    quantite = quantite;
}
