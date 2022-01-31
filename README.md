# Le projet e-stock 2019

Système de gestion de stock automatisé et communicant.

- [Le projet e-stock 2019](#le-projet-e-stock-2019)
  - [Auteurs](#auteurs)
  - [Présentation](#présentation)
  - [Productions](#productions)
  - [Vidéo](#vidéo)
  - [Base de données MySQL](#base-de-données-mysql)
  - [Licence GPL](#licence-gpl)

## Auteurs

- GAUTHIER Robin <rgauthier2510@gmail.com>
- GIMENEZ Hadrien <gimenezhadrien@gmail.com>
- MACHON Thomas <thomaslasalle84@gmail.com>

## Présentation

Il s’agit de réaliser un système de gestion de stock automatisé et communicant qui permettra :

- de contrôler et gérer l’utilisation de produits stockés dans des armoires sensibles
- d’assurer la traçabilité de l’attribution du matériel et des consommables stockés
- de sécuriser l’accès par un contrôle d’accès par badge RFID

Les armoires seront composées de 8 casiers maximum. Chaque casier pourra être équipé d’une gâche électrique afin d’assurer son ouverture/fermeture et d’une balance pour assurer le comptage automatique des articles.

Un lecteur de badge RFID est intégré à chaque armoire pour contrôler l’accès. L’exploitation de l’armoire e-stock est possible à partir soit de l’écran tactile intégré soit par un terminal mobile (tablette Android par exemple).

## Productions

- [dossier-estock-ir-2019.pdf](dossier-estock-ir-2019.pdf)
- [refman-estock.pdf](refman-estock.pdf)
- [presentation-gauthier-2019.pdf](presentation-gauthier-2019.pdf)
- [presentation-machon-2019.pdf](presentation-machon-2019.pdf)
- [presentation-gimenez-2019.pdf](presentation-gimenez-2019.pdf)

## Vidéo

Lien : https://www.youtube.com/watch?v=6vcnuNmmL2M

## Base de données MySQL

```sql
--
-- Base de données: `e-stock`
--

DROP DATABASE IF EXISTS `e-stock`;

CREATE DATABASE IF NOT EXISTS `e-stock`;

USE `e-stock`;

-- --------------------------------------------------------

-- Création du compte d'accès à la base de données e-stock

-- CREATE USER 'estock'@'%' IDENTIFIED BY 'password';
-- GRANT ALL PRIVILEGES ON `e-stock`.* TO 'estock'@'%';
-- FLUSH PRIVILEGES;

-- --------------------------------------------------------

--
-- Structure de la table `Profil`
--

CREATE TABLE IF NOT EXISTS `Profil` (
  `idProfil` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  PRIMARY KEY (`idProfil`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Profil` (`Nom`) VALUES
('Administrateur'),
('Gestionnaire'),
('Utilisateur');

-- --------------------------------------------------------

--
-- Structure de la table `Groupe`
--

CREATE TABLE IF NOT EXISTS `Groupe` (
  `idGroupe` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  PRIMARY KEY (`idGroupe`),
  CONSTRAINT Unique_Groupe UNIQUE (`Nom`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Groupe` (`Nom`) VALUES
('PROFESSEUR'),
('1-BTS-SN'),
('T-BTS-SN');

-- --------------------------------------------------------

--
-- Structure de la table `Utilisateur`
--

CREATE TABLE IF NOT EXISTS `Utilisateur` (
  `idUtilisateur` int(11) NOT NULL AUTO_INCREMENT,
  `idProfil` int(11) NOT NULL,
  `idGroupe` int(11) NOT NULL,
  `Nom` varchar(64) NOT NULL,
  `Prenom` varchar(64) NOT NULL,
  `DateValidite` date NOT NULL,
  `Identifiant` varchar(255) DEFAULT NULL,
  `MotDePasse` varchar(255) DEFAULT NULL,
  `Badge` varchar(11) NOT NULL,
  `Email` varchar(64) NOT NULL,  
  PRIMARY KEY (`idUtilisateur`),
  CONSTRAINT Unique_Utilisateur UNIQUE (`Badge`),
  CONSTRAINT Utilisateur_fk_1 FOREIGN KEY (`idProfil`) REFERENCES Profil(`idProfil`) ON DELETE CASCADE,
  CONSTRAINT Utilisateur_fk_2 FOREIGN KEY (`idGroupe`) REFERENCES Groupe(`idGroupe`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('1','1','Vaira','Thierry','2019-07-01','admin','5f4dcc3b5aa765d61d8327deb882cf99','','tvaira@free.fr');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('2','1','Vaira','Thierry','2019-07-01','tvaira','5f4dcc3b5aa765d61d8327deb882cf99','1234','tvaira@free.fr');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('2','1','Beaumont','Jerome','2019-07-01','jbeaumont','','5678','beaumont@lasalle84.org');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','ANDREO','Michaël','2019-07-01','andreo.m','','1111','andreo.michael@outlook.fr');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','BOFFREDO','Nicolas','2019-07-01','boffredo.n','','2222','nboffredo@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','BOTELLA','Yohann','2019-07-01','botella.y','','3333','botellabroc.yohann@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','GAUTHIER','Robin','2019-07-01','gauthier.r','','5022A783','rgauthier2510@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','GIMENEZ','Hadrien','2019-07-01','gimenez.h','','02BE0261','gimenezhadrien@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','HAMMOUMA','Youssef','2019-07-01','hammouma.y','','6666','yhammouma@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','LAURAIN','Clément','2019-07-01','laurain.c','','7777','laurain.clement.contact@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','MACHON','Thomas','2019-07-01','machon.t','170796','30DDA983','thomaslasalle84@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','MELLAH','Florentin','2019-07-01','mellah.f','','9999','florentinmellah@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','REYNIER','Jacques','2019-07-01','reynier.j','','1112','reynier.jacques@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','ROSSI','Enzo','2019-07-01','rossi.e','','1113','enzo.rossi13160contact@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','SY','Somphon','2019-07-01','sy.s','','1114','somphon.sypro@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','TURLIN','Suzie','2019-07-01','turlin.s','','1115','suzie.turlin@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','3','WAGINAIRE','Nathan','2019-07-01','waginaire.n','','62A3F560','nathanwaginaire3@gmail.com');

-- --------------------------------------------------------

--
-- Structure de la table `Armoire`
--

CREATE TABLE IF NOT EXISTS `Armoire` (
  `idArmoire` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(255) NOT NULL,
  `Description` varchar(255) DEFAULT NULL,
  `AdresseIP` varchar(15) DEFAULT NULL,
  `nbCasiers` int(11) NOT NULL DEFAULT 8,
  PRIMARY KEY (`idArmoire`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseIP`,`nbCasiers`) VALUES('Armoire C01','','192.168.52.1','2');
INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseIP`,`nbCasiers`) VALUES('Armoire C02','','192.168.52.2','2');
INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseIP`,`nbCasiers`) VALUES('Armoire A01','','192.168.52.3','2');
INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseIP`,`nbCasiers`) VALUES('Armoire A02','','192.168.52.122','8');

-- --------------------------------------------------------

--
-- Structure de la table `Type`
--

CREATE TABLE IF NOT EXISTS `Type` (
  `idType` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  PRIMARY KEY (`idType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Type` (`Nom`) VALUES
('Equipement'),
('Consommable');

-- --------------------------------------------------------

--
-- Structure de la table `Unite`
--

CREATE TABLE IF NOT EXISTS `Unite` (
  `idUnite` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  PRIMARY KEY (`idUnite`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Unite` (`Nom`) VALUES
('Metre'),
('Piece'),
('Pourcentage'),
('Poids g'),
('Poids kg');

-- --------------------------------------------------------

--
-- Structure de la table `Comptage`
--

CREATE TABLE IF NOT EXISTS `Comptage` (
  `idComptage` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  PRIMARY KEY (`idComptage`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Comptage` (`Nom`) VALUES
('Aucun'),
('Automatique'),
('CodeBarre');

-- --------------------------------------------------------

--
-- Structure de la table `Action`
--

CREATE TABLE IF NOT EXISTS `Action` (
  `idAction` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  PRIMARY KEY (`idAction`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Action` (`Nom`) VALUES
('Entree'),
('Sortie');

-- --------------------------------------------------------

--
-- Structure de la table `Article`
--

CREATE TABLE IF NOT EXISTS `Article` (
  `idArticle` int(11) NOT NULL AUTO_INCREMENT,
  `idType` int(11) NOT NULL,  
  --   `Type` enum('Equipement','Consommable'),
  `Nom` varchar(255) NOT NULL,
  `Code` varchar(255) NOT NULL,
  `Designation` varchar(255) NOT NULL,
  PRIMARY KEY (`idArticle`),
  CONSTRAINT Article_fk_1 FOREIGN KEY (`idType`) REFERENCES Type(`idType`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('2','Vis six pans creux M2 8mm','','M2*8');
INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('2','Vis tête cylindrique M2 8mm','','M2*8');
INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('2','Vis six pans creux M2 12mm','','M2*12');
INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('2','Vis tête cylindrique M2 12mm','','M2*12');
INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('1','Fluke i30s','2584935','Amperemetre AC/DC');
INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('1','Fluke 179','','Multimetre');

-- --------------------------------------------------------

--
-- Structure de la table `Stock`
--

CREATE TABLE IF NOT EXISTS `Stock` (
  `idStock` int(11) NOT NULL AUTO_INCREMENT,
  `idArmoire` int(11) NOT NULL,
  `idArticle` int(11) NOT NULL,
  `idComptage` int(11) NOT NULL,
  `idUnite` int(11) NOT NULL,
  `Quantite` int(11) DEFAULT 0,
  `Disponible` int(11) DEFAULT 0,
  `numeroCasier` int(11) NOT NULL,
  PRIMARY KEY (`idStock`),
  CONSTRAINT Unique_NumeroCasier UNIQUE (`numeroCasier`),
  CONSTRAINT Stock_fk_1 FOREIGN KEY (`idArmoire`) REFERENCES Armoire(`idArmoire`) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_2 FOREIGN KEY (`idArticle`) REFERENCES Article(`idArticle`) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_3 FOREIGN KEY (`idComptage`) REFERENCES Comptage(`idComptage`) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_4 FOREIGN KEY (`idUnite`) REFERENCES Unite(`idUnite`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `Mouvement`
--

CREATE TABLE IF NOT EXISTS `Mouvement` (
  `idMouvement` int(11) NOT NULL AUTO_INCREMENT, 
  `idUtilisateur` int(11) NOT NULL,
  `idStock` int(11) NOT NULL,
  `idAction` int(11) NOT NULL,
  --   `Action` enum('Entree','Sortie'),
  `Quantite` int(11) NOT NULL,
  `Horodatage` datetime NOT NULL,
  PRIMARY KEY (`idMouvement`),
  CONSTRAINT Mouvement_fk_1 FOREIGN KEY (`idUtilisateur`) REFERENCES Utilisateur(`idUtilisateur`) ON DELETE CASCADE,
  CONSTRAINT Mouvement_fk_2 FOREIGN KEY (`idStock`) REFERENCES Stock(`idStock`) ON DELETE CASCADE,
  CONSTRAINT Mouvement_fk_3 FOREIGN KEY (`idAction`) REFERENCES Action(`idAction`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------
```

## Licence GPL

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
