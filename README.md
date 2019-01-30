# projet pandaReader:

Afin de revoir 2, 3 choses de ma dernière formation développeur FullStack.
Et aussi d'exploiter ma carte Arduino Uno.

## Les composants physiques:
un afficheur digital 4 digit 7 segments
un servo moteur sg90
une petite figurine de panda.
une carte Arduino Uno
une machine qui fait office de serveur back-end
un serveur qui heberge la partie front-end

## Les composants logiciels:
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
      
Le fonctionnement:

## Pour la carte Arduino:
Elle affiche grâce à la librairie SegSev des message sur l'afficheur digital. Et en même temps elle gère le déplacement du servo moteur.
Les 2 pales du servo moteur sont reliés à la tête de la figurine par des fils. Ainsi quand le servo moteur tourne, la tête de la figurine tourne aussi.
Pour que le projet soit un peu plus intéressant à programmer, j'ai me suis imposé la condition de déplace le servo moteur en fonction du rythme de l'afficheur digital.

Ce qui donne l'impression que le panda lit les messages sur l'afficheur digital.
J'ai aussi ajouté une classe pour suivre l'état de la carte (comme l'angle de rotation du moteur, la vitesse d'affichage, etc..). Afin d'afficher ses informations dans la page web de l'utilisateur final.

## Entre l'Arduino et la machine hébergeant tomcat:
On utilise la librairie arduilink pour faire communiquer l'arduino et l'application SSE (server sent event) à travers le port série avec le protocol Alp. Ce qui implique une implementation d'écoute d'évenement sur la carte et dans l'application java.

## L'application Java:
L'application java se comporte comme un service rest. Sauf que la particularité du SEE est de transformer le client en serveur.
En fait lors d'une requête du client au au service du serveur, le client s'abonne aux événements émis par le serveur.
La communication entre le serveur et le client reste ouverte. Tant que le client ne coupe pas la connexion, le serveur peut lui envoyer des messages.

J'ai donc naturellement remplacé la partie DAO d'un serveur de service, par les informations envoyés par ma carte.
Mais aussi complété mes services rest avec des fonctionnalités SSE. Quand un événement est émi par la carte, un listener placer dans la partie SSE le capture, le transforme en json et l'envoie au client. 

## la partie front:
La partie front se décompose en deux: Une partie d'envoi de messages sous la forme d'un formulaire, et une partie réception pour l'affichage des informations des états de la carte. Les informations de la carte sont transmis en temps réel grâce à l'implémentation SSE de Jersey.

## le résultat:
une application web qui permet d'envoyer des messages sur mon afficheur digital, depuis n'importe quel endroit dans le monde.
L'application étant responsive. Elle est utilisable par les téléphones, les tablettes et bien évidemment par les ordinateurs.

## Le problème:
Le SSE n'a pas l'air de fonctionner sur les mobiles.





