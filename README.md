# projet pandaReader:

Afin de revoir 2, 3 choses de ma dernière formation. Mais aussi exploiter ma carte Arduino Uno.
J'ai créé un petit projet que je décris dans la suite de ce document. 

### Les composants physiques:
Un afficheur digital 4 digit 7 segments
Un servo moteur sg90
Une petite figurine de panda.
Une carte Arduino Uno
Une machine qui fait office de serveur back-end
Un serveur qui héberge la partie front-end

### Les composants logiciels:
IDE (intellij, eclipse)

Langage:
      Java
      C/C++
      HTML/Css/javascript

Les framework:
      Jersey 2
      Boostrap
      Jquery
      
Les librairies externe:
      SegSev
     Ardulink site: www.ardulink.org
Le serveur:
      tomcat
      
## Le fonctionnement:

### Pour la carte Arduino:
Elle affiche grâce à la librairie SegSev des messages sur l'afficheur digital.En même temps elle gère le déplacement du servo moteur.
Les 2 pales du servo moteur sont reliés à la tête de la figurine par des fils. Ainsi quand le servo moteur tourne, la tête tourne aussi.

Pour que le projet soit un peu plus intéressant à programmer, je me suis imposé la condition de déplace le servo moteur en fonction du rythme de l'afficheur digital.

Ce qui donne l'impression que le panda lit les messages sur l'afficheur digital.
J'ai aussi ajouté une classe pour suivre l'état de la carte (comme l'angle de rotation du moteur, la vitesse d'affichage, etc..) afin d'afficher ses informations dans la page web de l'utilisateur final.

### Entre l'Arduino et la machine hébergeant tomcat:
On utilise la librairie arduilink pour faire communiquer l'arduino et l'application SSE (server sent event) à travers le port série avec le protocole Alp. Ce qui implique une implementation d'écoutes d'évenements sur la carte et dans l'application Java.

### L'application Java:
L'application Java se comporte comme un service rest. Sauf que la particularité du SEE est de transformer le client en serveur.
En fait lors d'une requête http du client vers le service SSE du serveur, le client s'abonne aux événements émis par le serveur.
La communication entre le serveur et le client reste ouverte. Tant que le client ne coupe pas la connexion, le serveur peut lui envoyer des messages.

J'ai donc remplacé la partie DAO d'un serveur de service, par les informations envoyés par la carte.
Et complété mes services rest avec des fonctionnalités SSE. Quand un événement est émi par la carte, un listener placer dans la partie SSE le capture, le transforme en json et l'envoie au client. 

### La partie front:
La partie front se décompose en deux:
Une partie d'envoi de messages, sous la forme d'un formulaire, une partie réception permettant l'affichage  des états de la carte. Les informations de la carte sont transmises en temps réel grâce aux fonctionnalités SSE de Jersey.

### Le résultat:
Une application web qui permet d'envoyer des messages sur un afficheur digital, depuis n'importe quel endroit dans le monde.
L'application étant responsive. Elle est utilisable par tous supports capables d'utiliser une connexion web.

### Le problème:
Le SSE n'a pas l'air de fonctionner sur les mobiles.


#todo relier et revoir la mise en forme.




