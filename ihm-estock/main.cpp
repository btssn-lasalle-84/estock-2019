#include <QApplication>
#include "IhmAuthentification.h"

/**
 * @file ihm-estock/main.cpp
 *
 * @brief Programme principal e-stock
 *
 * @details Crée et affiche la fenêtre principale de l'application
 *
 * @author Thomas MACHON, Hadrien GIMENEZ et Nathan WAGINAIRE
 *
 * @version 1.1
 *
 * @fn main(int argc, char *argv[])
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IhmAuthentification ihmAuthentification;
    ihmAuthentification.show();

    return a.exec();
}
