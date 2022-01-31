#include "administrateur.h"

Administrateur::Administrateur()
{

}

Administrateur::~Administrateur()
{

}

char Administrateur::getNom()
{
    return nom;
}
char Administrateur::getPrenom()
{
    return prenom;
}

void Administrateur::setNom()
{
    this -> nom = nom;
}

void Administrateur::setPrenom()
{
    this -> prenom = prenom;
}
