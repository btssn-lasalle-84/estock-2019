#include "GestionBalances.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>

/**
 * @brief Constructeur
 *
 * @fn GestionBalances::GestionBalances
 *
 * @param parent QObject Adresse de l'objet Qt parent
 */
GestionBalances::GestionBalances(QObject *parent) : QObject(parent)
{
    port = new QSerialPort(PORT, this);

    this->seConnecter();
}

/**
 * @brief Destructeur de la calsse GestionBalances
 *
 * @fn GestionBalances::~GestionBalances
 *
 */
GestionBalances::~GestionBalances()
{
    this->seDeconnecter();
}

/**
 * @brief Paramètrage du port
 *
 * @fn GestionBalances::parametrerPort()
 *
 */
void GestionBalances::parametrerPort()
{
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
}
/**
 * @brief Ouverture du port
 *
 * @fn GestionBalances::ouvrirPort()
 *
 */
void GestionBalances::ouvrirPort()
{
    port->open(QIODevice::ReadOnly);
    qDebug() << Q_FUNC_INFO << "etat ouverture port" << port->isOpen();
    if(port->isOpen())
    {
        connect(port, SIGNAL(readyRead()), this, SLOT(lirePort()));
    }
}

/**
 * @brief Réception des trames balance
 *
 * @fn GestionBalances::lirePort()
 *
 */
void GestionBalances::lirePort()
{
    if(port->canReadLine())
    {
        QByteArray donnees = port->readLine();
        qDebug() << Q_FUNC_INFO << donnees;
        if(donnees.startsWith("$"))
        {
            qDebug() << Q_FUNC_INFO << donnees;
            donnees.clear();
        }
    }
}

/**
 * @brief Fermeture du port
 *
 * @fn GestionBalances::fermerPort()
 *
 */
void GestionBalances::fermerPort()
{
    if(port->isOpen())
        port->close();
    qDebug() << Q_FUNC_INFO << "etat ouverture port" << port->isOpen();
}

/**
 * @brief Ouvre et paramètre le port
 *
 * @fn GestionBalances::seConnecter()
 *
 */
void GestionBalances::seConnecter()
{
    this->ouvrirPort();
    this->parametrerPort();
}

/**
 * @brief Fermeture du port
 *
 * @fn GestionBalances::seDeconnecter()
 *
 */
void GestionBalances::seDeconnecter()
{
    this->fermerPort();
}
