# Convention Projet Réseau
####Team A: Kevin BASCOL, Nicolas REYNAUD
####Team B: Bachir BOUACHERIA Kévin LAOUSSING, Amar SEBAA
##### 30 janvier 2015

##Envoi
###Messages
- Message de déconnexion : S ( Si se message est recu les collecteurs qui le recoivent doivent se donnecter proprement du collecteur / boss )
- Demande de connexion à un collecteur:
- Demande de connexion à un boss:
- Vérification qu'un collecteur ait toujours le fichier:
- Demande d'un volume à un collecteur: VolX ( X = numéro de volume ) 
- Demande d'une nouvelle liste à un boss: ListOfCollector

###Volumes
- Unité: octet.
- Taille minimale: 8ko (inclus).
- Taille maximale: 64ko (inclus).
- Checksum: SHA1 partagé via la version humainement lisible.

##Connexions
###Ports
- Établissement d'une connexion sur un collecteur: 47777.
- Établissement d'une connexion sur un boss: Définit dans l'Index.

###Limites
- Nombre de connexions sur un collecteur: 15
- Nombre de connexions sur un boss: 50
- Nombre maximum de collecteur renvoyé par le boss : 10


##Erreurs
- Connexion échouée:
	- Limite de connexions atteinte sur un collecteur:
	- Limite de connexions atteinte sur un boss:
	- Autre:
- Volume absent:
- Liste vide:


Exemple de conversation : 

### ( Connexion au boss ) 
- ListOfCollector
- 2127.0.0.1            ( Collecteur 1 ) 
- 1154.454.15.1         ( Collecteur 2 ) 
- 0157.125.125.125      ( Collecteur 3 ) 

### ( Connexion aux collecteurs ) 
#### ( Connexion au collecteur 1 )
    - 1,5,15 ( Ici le collecteur 1 à les volumes 1 - 5 et 15 )
    - 2,4,13 (Ici le collecteur local à les volumes 2 - 4 et 13 )
#### ( Connexion au collecteur 2 )
    - 8,13,15 ( Ici le collecteur 2 à les volumes 8 - 13 et 15)
    - 2,4,13 (Ici le collecteur local à les volumes 2 - 4 et 13 )
#### ( Connexion au collecteur 3 )
    - Message d'erreur
---
### ( Echange de volume ) 
    ( Collecteur local au collecteur 1 ) 
    - Vol1
    ( Envoi / reception du volume 1 )
    ( Collecteur 1 au collecteur local ) 
    - Vol2
    ( Envoi / reception du volume 2 )
---
### ( Arret ) 
    (Collecteur local au collecteur 1 )
    - Stop
    ( Deconnexion du collecteur 1 )
    (Collecteur local au collecteur 2 )
    - Stop
    ( Deconnexion du collecteur 2 )
    ( Message du boss au collecteur local )
    - Stop
    ( Deconnexion du collecteur local )
