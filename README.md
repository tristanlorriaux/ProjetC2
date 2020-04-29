# ProjetC2_Blockchain
![Bottle Design](bottle.png)
**BOTTLE : Une messagerie sécurisée écrite en C. Utilise uniquement : C, SDL, OPENSSL.**

Cette application est une simulation de messagerie qui fonctionne grâce aux blockchains. 
Assurant ainsi la sécurité des messages transmis, l’application permet aussi la création et la gestion de comptes dont les informations confidentielles sont chiffrées.

Installation
------------

### 1. Télécharger le code


### 2. Installer les librairies :

- sudo apt-get install libsdl1.2-dev
- sudo apt-get install libsdl2-ttf-dev
- sudo apt-get install libsdl2-image-dev

- sudo apt-get install libssl-dev  

### 3. Executer le code une fois compilé:

- make)
- ./bottle

### 4. Fonctionnalités :

- Créer un nouveau compte : Vous pouvez créer un compte en écrivant votre identifiant et votre mot de passe
![Bottle Design](images/compte.bmp)
Cependant, il est seulement possible de créer 5 comptes différents.
Il n'y a pas de bouton pour supprimer un compte : il faut directement supprimer la ligne correspondante dans le fichier SaveID.txt

- Se connecter :  Pour vous connecter il vous suffit de rentrer les identifiants préalablement rentrés. En cas d'erreur, appuyez sur le bouton retour

- Choisir un destinataire : Rentrez directement le nom du destinataire que vous souhaitez parmi les choix proposés

- Envoyer des messages : Communiquez directement avec les autres utilisateurs via la messagerie qui affichera les derniers messages de la conversation. Si vous voulez changer de destinataire, appuyez sur le bouton retour et reconnectez-vous

Sécurité
------------

  Bottle est un projet qui a été créé pour garantir la sécurité lors de la transmission des données d'un utilisateur à un autre. Pour cela nous avons utilisé des blockchains pour garantir une sécurité maximale mais nous permettons aussi la création de comptes dont les identifiants sont stockés et cryptés. L'algorithme est aussi capable de reconnaître toute modification des fichiers de sauvegarde de la blockchain et des IDs et supprimera toutes les conversations précdentes : ne jouez pas aux hackers! 
