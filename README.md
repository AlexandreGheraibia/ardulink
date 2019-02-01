# projet pandaReader:

Afin de réviser 2, 3 choses de ma dernière formation. Et d'exploiter ma carte Arduino Uno laissée à l'abandon.
J'ai créé un petit projet que je décris dans la suite de ce document. 


## Les composants :

### La partie hardware:

Un afficheur digital 4 digits 7 segments,
Un servo-moteur sg90,
Une petite figurine de panda,
Une carte Arduino Uno,
Une machine (faisant office de serveur back-end),
Un serveur hébergeant (la partie front-end)

### La partie software:

IDE (Intellij, Eclipse)

Langage:
      Java
      C/C++
      HTML/Css/Javascript

Les framework:
      Jersey 2
      Boostrap
      Jquery
      
Les librairies externe:
      SegSev
      Ardulink site: www.ardulink.org
Le serveur:
      Tomcat
      
## Le fonctionnement:

### La carte Arduino:
Elle affiche grâce à la librairie SegSev des messages sur l'afficheur digital.En même temps elle gère le déplacement du servo moteur.
Les 2 pales du servo moteur sont reliés à la tête de la figurine par des fils. Ainsi quand le servo moteur tourne, la tête tourne.

Pour que le projet soit un peu plus intéressant à programmer, je me suis imposé la condition de déplace le servo moteur en fonction du rythme de l'afficheur digital.

Ce qui donne l'impression que le panda lit les messages sur l'afficheur digital.
J'ai aussi ajouté une classe pour suivre l'état de la carte (comme l'angle de rotation du moteur, la vitesse d'affichage, etc..) afin d'afficher ses informations dans la page web de l'utilisateur.

### Entre l'Arduino et la machine hébergeant Tomcat:
La librairie Arduilink est utilisé pour la communication entre l'arduino et l'application SSE (server-sent Events).
Ces deux deux derniers communiquent à travers le port série (câble usb) grâce au protocole Alp. Ce qui implique un traitement des événements (ou écoutes d'événements) pour l'application Java. Et pour la carte Arduino.

### L'application Java:
L'application Java se comporte comme un service rest. La principale différence entre l'implémentation et un service rest est l'utilisation de SSE. Lors d'une requête http du client vers le service SSE du serveur, le client s'abonne aux événements émis par le serveur. La communication entre le serveur et le client reste ouverte. Ce qui permets au serveur d'envoyer des messages au client.Le modèle serveur-client habituel est inversé. La communication est interrompu à l'initiative du client.

### La partie front:
La partie front se décompose en deux:
Une partie d'envois de messages, sous la forme d'un formulaire, une partie réception permettant l'affichage des états de la carte. Les informations de la carte sont transmises en temps réel grâce aux fonctionnalités SSE de Jersey.

## Le résultat:
le projet est une application web qui permet d'envoyer des messages sur un afficheur digital, depuis n'importe quel endroit dans le monde. l'application est responsive (ce qui est dù à l'utilisation de Bootsrap). Elle est utilisable par tous appareils possédant un navigateur internet.

Si on compare la configuration du projet au modèle MVVM. L'application Java est le fournirseur de service (la vue serveur). Elle fait le lien entre la Carte Arduino qui fournit les données (le Modèle serveur) et la partie front (le patron Modèle-vue-présentation).

### Le problème:
Le SSE n'a pas l'air de fonctionner sur les mobiles.




