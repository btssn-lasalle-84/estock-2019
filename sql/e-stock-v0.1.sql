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
  `Numero` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idGroupe`),
  CONSTRAINT Unique_Groupe UNIQUE (`Nom`,`Numero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Groupe` (`Nom`,`Numero`) VALUES
('ADMINISTRATEUR', '1'),
('GESTIONNAIRE', '2'),
('PROFESSEUR', '3'),
('1-BTS-SN', '4'),
('T-BTS-SN', '5');

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
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('2','3','Vaira','Thierry','2019-07-01','tvaira','5f4dcc3b5aa765d61d8327deb882cf99','1234','tvaira@free.fr');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('2','3','Beaumont','Jerome','2019-07-01','jbeaumont','','5678','beaumont@lasalle84.org');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','ANDREO','Michaël','2019-07-01','andreo.m','','1111','andreo.michael@outlook.fr');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','BOFFREDO','Nicolas','2019-07-01','boffredo.n','','2222','nboffredo@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','BOTELLA','Yohann','2019-07-01','botella.y','','3333','botellabroc.yohann@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','GAUTHIER','Robin','2019-07-01','gauthier.r','','4444','rgauthier2510@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','GIMENEZ','Hadrien','2019-07-01','gimenez.h','','5555','gimenezhadrien@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','HAMMOUMA','Youssef','2019-07-01','hammouma.y','','6666','yhammouma@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','LAURAIN','Clément','2019-07-01','laurain.c','','7777','laurain.clement.contact@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','MACHON','Thomas','2019-07-01','machon.t','','8888','thomaslasalle84@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','MELLAH','Florentin','2019-07-01','mellah.f','','9999','florentinmellah@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','REYNIER','Jacques','2019-07-01','reynier.j','','1112','reynier.jacques@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','ROSSI','Enzo','2019-07-01','rossi.e','','1113','enzo.rossi13160contact@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','SY','Somphon','2019-07-01','sy.s','','1114','somphon.sypro@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','TURLIN','Suzie','2019-07-01','turlin.s','','1115','suzie.turlin@gmail.com');
INSERT INTO `Utilisateur` (`idProfil`,`idGroupe`,`Nom`,`Prenom`,`DateValidite`,`Identifiant`,`MotDePasse`,`Badge`,`Email`) VALUES('3','5','WAGINAIRE','Nathan','2019-07-01','waginaire.n','','1116','nathanwaginaire3@gmail.com');

-- --------------------------------------------------------

--
-- Structure de la table `Armoire`
--

CREATE TABLE IF NOT EXISTS `Armoire` (
  `idArmoire` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(255) NOT NULL,
  `Description` varchar(255) DEFAULT NULL,
  `AdresseMac` varchar(17) DEFAULT NULL,
  `AdresseIP` varchar(15) DEFAULT NULL,
  PRIMARY KEY (`idArmoire`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseMac`,`AdresseIP`) VALUES('Armoire 1','','','192.168.52.240');
INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseMac`,`AdresseIP`) VALUES('Armoire 2','','','192.168.52.241');
INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseMac`,`AdresseIP`) VALUES('Armoire 3','','','192.168.52.242');
INSERT INTO `Armoire` (`Nom`,`Description`,`AdresseMac`,`AdresseIP`) VALUES('Armoire 4','','','192.168.52.243');

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

INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('1','','','');
INSERT INTO `Article` (`idType`, `Nom`, `Code`, `Designation`) VALUES('1','','','');

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
  PRIMARY KEY (`idStock`),
  CONSTRAINT Stock_fk_1 FOREIGN KEY (`idArmoire`) REFERENCES Armoire(`idArmoire`) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_2 FOREIGN KEY (`idArticle`) REFERENCES Article(`idArticle`) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_3 FOREIGN KEY (`idComptage`) REFERENCES Comptage(`idComptage`) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_4 FOREIGN KEY (`idUnite`) REFERENCES Unite(`idUnite`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Stock` (`idArmoire`,`idArticle`,`idComptage`,`idUnite`) VALUES('1','1','2','1');
INSERT INTO `Stock` (`idArmoire`,`idArticle`,`idComptage`,`idUnite`) VALUES('1','2','2','2');

-- --------------------------------------------------------

--
-- Structure de la table `Mouvement`
--

CREATE TABLE IF NOT EXISTS `Mouvement` (
  `idMouvement` int(11) NOT NULL AUTO_INCREMENT, 
  `idUtilisateur` int(11) NOT NULL,
  `idArticle` int(11) NOT NULL,
  `idAction` int(11) NOT NULL,
  --   `Action` enum('Entree','Sortie'),
  `Quantite` int(11) NOT NULL,
  `Horodatage` datetime NOT NULL,
  PRIMARY KEY (`idMouvement`),
  CONSTRAINT Mouvement_fk_1 FOREIGN KEY (`idUtilisateur`) REFERENCES Utilisateur(`idUtilisateur`) ON DELETE CASCADE,
  CONSTRAINT Mouvement_fk_2 FOREIGN KEY (`idArticle`) REFERENCES Article(`idArticle`) ON DELETE CASCADE,
  CONSTRAINT Mouvement_fk_3 FOREIGN KEY (`idAction`) REFERENCES Action(`idAction`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Mouvement` (`idUtilisateur`,`idArticle`,`idAction`,`Quantite`,`Horodatage`) VALUES('2','1','2','10','2018-11-14 06:15:56');
