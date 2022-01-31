#ifndef GESTIONBALANCES_H
#define GESTIONBALANCES_H

/**
  *
  * @file GestionBalances.h
  *
  * @brief Déclaration de la classe GestionBalances
  *
  * @author Hadrien Gimenez
  *
  * @version 1.1
  *
  */

#include <QObject>
#include <QSerialPort>

#define PORT "/dev/ttyACM0"

/**
  *
  * @class GestionBalances
  *
  * @brief Déclaration de la classe GestionBalances
  *
  * @author Hadrien Gimenez
  *
  * @version 1.1
  *
  */

class GestionBalances : public QObject
{
    Q_OBJECT
public:
    explicit GestionBalances(QObject *parent = nullptr);
     ~GestionBalances();

   void seConnecter();
   void seDeconnecter();

private:
   QSerialPort *port;
   QByteArray donnees;

   void parametrerPort();
   void ouvrirPort();
   void fermerPort();

signals:

public slots:
   void lirePort();

};

#endif // GESTIONBALANCE_H
