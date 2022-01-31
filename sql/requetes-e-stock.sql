-- Les `Utilisateur`

SELECT Utilisateur.Nom, Utilisateur.Prenom, Utilisateur.DateValidite, Utilisateur.Identifiant, Utilisateur.Badge, Utilisateur.Email, Profil.Nom AS Profil, Groupe.Nom AS Groupe FROM Utilisateur INNER JOIN Groupe ON Groupe.idGroupe=Utilisateur.idGroupe INNER JOIN Profil ON Profil.idProfil=Utilisateur.idProfil ORDER BY Utilisateur.Nom

-- Les profils `Utilisateur`

SELECT Utilisateur.Nom, Utilisateur.Prenom, Utilisateur.DateValidite, Utilisateur.Identifiant, Utilisateur.Badge, Utilisateur.Email, Profil.Nom AS Profil, Groupe.Nom AS Groupe FROM Utilisateur INNER JOIN Groupe ON Groupe.idGroupe=Utilisateur.idGroupe INNER JOIN Profil ON Profil.idProfil=Utilisateur.idProfil WHERE Profil.Nom='Utilisateur' ORDER BY Utilisateur.Nom

-- Un `Groupe`

SELECT Groupe.*,Utilisateur.* FROM Groupe, Utilisateur WHERE Utilisateur.idGroupe = Groupe.idGroupe AND Groupe.Nom = 'PROFESSEUR'

-- Les `Mouvement`

SELECT Utilisateur.Nom, Article.Nom AS Article, Type.nom AS Type, Action.Nom AS Action, Mouvement.Quantite, Mouvement.Horodatage  FROM Mouvement INNER JOIN `Utilisateur` ON `Utilisateur`.idUtilisateur=Mouvement.idUtilisateur INNER JOIN `Article` ON `Article`.idArticle=Mouvement.idArticle INNER JOIN `Type` ON `Type`.idType=Article.idType INNER JOIN `Action` ON `Action`.idAction=Mouvement.idAction

-- Un `Article`

SELECT Article.Nom AS Article, Type.nom AS Type, Article.Code, Article.Designation FROM Article INNER JOIN `Type` ON `Type`.idType=Article.idType 

-- Le `Stock` des armoires

SELECT Armoire.Nom, Armoire.AdresseIP, Article.Nom AS Article, Type.nom AS Type, Article.Code, Article.Designation, Stock.Quantite FROM Stock INNER JOIN `Armoire` ON `Armoire`.idArmoire=Stock.idArmoire INNER JOIN `Article` ON `Article`.idArticle=Stock.idArticle INNER JOIN `Type` ON `Type`.idType=Article.idType INNER JOIN `Comptage` ON `Comptage`.idComptage=Stock.idComptage INNER JOIN `Unite` ON `Unite`.idUnite=Stock.idUnite

-- Le `Stock` d'une armoire

SELECT Armoire.Nom, Article.Nom AS Article, Type.nom AS Type, Article.Code, Article.Designation, Stock.Quantite FROM Stock INNER JOIN `Armoire` ON `Armoire`.idArmoire=Stock.idArmoire INNER JOIN `Article` ON `Article`.idArticle=Stock.idArticle INNER JOIN `Type` ON `Type`.idType=Article.idType INNER JOIN `Comptage` ON `Comptage`.idComptage=Stock.idComptage INNER JOIN `Unite` ON `Unite`.idUnite=Stock.idUnite WHERE Armoire.AdresseIP = '192.168.52.240'

-- Le nombre d'articles dans le `Stock` d'une armoire

SELECT COUNT(Article.Code) AS NbArticles FROM Stock INNER JOIN `Armoire` ON `Armoire`.idArmoire=Stock.idArmoire INNER JOIN `Article` ON `Article`.idArticle=Stock.idArticle INNER JOIN `Type` ON `Type`.idType=Article.idType INNER JOIN `Comptage` ON `Comptage`.idComptage=Stock.idComptage INNER JOIN `Unite` ON `Unite`.idUnite=Stock.idUnite WHERE Armoire.AdresseIP = '192.168.52.240'

-- Le nombre d' `Armoire`

SELECT COUNT(Armoire.AdresseMAC) FROM Armoire 

-- etc ...
