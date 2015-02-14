# Convention Projet Réseau
####Team A: Kevin BASCOL, Nicolas REYNAUD
####Team B: Bachir BOUACHERIA Kévin LAOUSSING, Amar SEBAA
##### 30 janvier 2015

##Envoi
###Messages
- Demande de connexion à un collecteur: ListOfVolums
- Demande de connexion à un boss: ListOfCollectors
- Vérification qu'un collecteur ait toujours le fichier: envoi du nom du fichier
	- "exist" : Le collecteur a le fichier
	- "notExist" : Le collecteur n'a pas le fichier
- Demande d'un volume à un collecteur: VolX ( X = numéro de volume ) 
- Demande d'une nouvelle liste à un boss: ListOfCollectors

###Volumes
- Unité: octet.
- Taille minimale: 8ko (inclus).
- Taille maximale: 64ko (inclus).
- Checksum: SHA1 partagé via la version humainement lisible.

##Connexions
###Ports
- Établissement d'une connexion sur un collecteur: 47777.
- Établissement d'une connexion sur un boss: Définit dans l'Index.

###Limites ( Valeur fixée par chaque groupe )
- Nombre de connexions sur un collecteur: 25
- Nombre de connexions sur un boss: 50
- Nombre maximum de collecteur renvoyé par le boss : 10

##Erreurs
- Connexion échouée:
	- Limite de connexions atteinte sur un collecteur: deconnexion direct sans message d'erreur
	- Limite de connexions atteinte sur un boss: deconnexion direct sans message d'erreur

Exemple de conversation : 

##### ( Connexion au boss ) 
- ListOfCollector
- 2127.0.0.1            ( Collecteur 1 ) 
- 1154.454.15.1         ( Collecteur 2 ) 
- 0157.125.125.125      ( Collecteur 3 ) 

##### ( Connexion aux collecteurs ) 
- ( Connexion au collecteur 1 )
	- envoi de "ListOfVolums" par le collecteur local
	- 00010001011 ( Ici le collecteur a les volumes 3, 7, 9 et 10 )
- ( Connexion au collecteur 2 )
	- envoi de "ListOfVolums" par le collecteur local
	- fullVolum ( ici se collecteur a tout les volumes )
- ( Connexion au collecteur 3 )
	- envoi de "ListOfVolums" par le collecteur local
	- nullVolum ( Ici se collecteur n'a aucun volume )

##### ( Echange de volume ) 
- ( Collecteur local au collecteur 1 )  
	- Vol1  
	( Envoi / reception du volume 1 )  
- ( Collecteur 1 au collecteur local )  
	- Vol2  
	( Envoi / reception du volume 2 )  
