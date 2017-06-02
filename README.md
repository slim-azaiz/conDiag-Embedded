Programme Embarqué

Le code source de ce programme est réparti selon des sous-répertoires:

"data" contient le code source qui permet de collecter les divers paramétres à partir du gather via sc-bus

"mongoose" notre serveur web embarqué

"utils" encapsule le code source de parsing de données

"cjson"

On a utilisé la librairie cJSON (open source crée par  Dave Gamble) qui permet de créer, parser des objets json et de les afficher sous ce format. 

cJSON est facile à intégrer dans notre projet car il suffit de copier le fichier cJSON.c et cJSON.h puis les cross compiler.


Pour le télécharger taper la commande :

git clone https://github.com/DaveGamble/cJSON <votre dossier de destination >

my_server.c qui contient le programme principal (main) et fait appel à ces bibliothèques dont on a parlé.


Le fichier Makefile présent dans le programme embarqué /condiag permet de lancer la compilation. 

A partir duquel on peut:

- positionner les variables d'environnement nécessaires à la compilation de application serveur.

- compiler le programme à travers la commande 

"make" ou "make all" 

- installer le binaire génére dans la STB à traver la commande 

"make install"

Cette étape permet de copier le binaire "conDiag" dans

le path suivant:

<Emplacement de votre BO>/src/sdt_sagemcom/sc_rootfs/scbin
