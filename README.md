# TP6-informatique
TP 6
Traitement d’image

Exercice 1 : chargement d’un image (bitmap)

1. Écrivez un programme nommé exo1.c permettant de charger en mémoire une image stockée
dans un fichier au format BMP.
1. Le programme prend en paramètre le nom du fichier image à charger.
2. On pourra utiliser la bibliothèque fournie pour lire les entêtes fichier et image.
3. Écrivez une fonction permettant d’extraire les trois images monochromes composant
l’image couleur. On stockera ces données dans trois matrices 2D (char **), une par
composante.
1. Les pixels sont rangés ligne par ligne en allant de gauche à droite. Si la longueur de la
ligne n’est pas un multiple de 4 octets, elle est complétée par 1, 2 ou 3 octets nuls pour
atteindre un multiple de 4. Les lignes sont rangées de bas en haut. Le premier pixel
correspond donc au coin inférieur gauche de l’image et le dernier au coin supérieur
droit.
2. Chaque pixel est codé sur 3 octets (on ne traitera que le cas d’images 24 bits). Les
composantes sont rangées dans l’ordre suivant : bleu d’abord, vert ensuite, et rouge en
dernier. Ce sont des entiers non signés.
4. Votre programme doit afficher la quantité de mémoire allouée.
2. Créez un fichier makefile avec une recette exo1 permettant de produire l’exécutable exo1.
3. Testez votre programme avec l’image fournie.

 Exercice 2 : génération d’un négatif

6. Écrivez un programme nommé exo2.c permettant de charger une image encodées au format
BMP, d’en calculer le négatif et de l’enregistrer dans un nouveau fichier.
1. Le programme prend en paramètre le nom du fichier image à traiter.
2. On pourra utiliser la bibliothèque fournie pour lire et écrire les entêtes fichier et image.
3. Le fichier de sortie doit s’appeler « negatif.bmp ».
1. Attention au « padding » des lignes (alignement sur un multiple de 4 octets).
2. Puisqu’on ne change ni l’encodage ni les dimensions de l’image, les entêtes fichier et
images du fichier lu peuvent être réutilisés pour construire le fichier produit par votre
programme.
4. Pour obtenir le négatif, il suffit d’inverser tous les bits de chaque composante.
2. Complétez le fichier makefile avec une recette exo2 permettant de produire l’exécutable exo2.
3. Testez votre programme avec l’image fournie et vérifiez le résultat en ouvrant le fichier produit
avec un logiciel de traitement d’images (Gimp). En générant le négatif du négatif que vous avez
créé, vous devez retrouver l’image originale.

Exercice 3 : transformation couleur → noir et blanc

1. Écrivez un programme nommé exo3.c permettant de charger une image encodées au format
BMP, d’en calculer l’intensité lumineuse et de l’enregistrer dans un nouveau fichier.
1. Le programme prend en paramètre le nom du fichier image à traiter.
2. On pourra utiliser la bibliothèque fournie pour lire et écrire les entêtes fichier et image.
3. Le fichier de sortie doit s’appeler «noirblanc.bmp ».
1. Attention au « padding » des lignes (alignement sur un multiple de 4 octets).
2. Puisqu’on ne change ni l’encodage ni les dimensions de l’image, les entêtes fichier et
images du fichier lu peuvent être réutilisés pour construire le fichier produit par votre
programme.
4. Pour calculer l’intensité lumineuse d’une couleur telle qu’elle est perçue par l’œil, il faut
faire une somme pondérée des trois composantes primaires. En effet l’œil humain est
beaucoup plus sensible dans le centre du spectre visible (vert) qu’à ses extrémités (rouge et
bleu). On utilisera des pondérations de 10 % pour le bleu, 70 % pour le vert et 20 % pour le
rouge.
5. Pour produire un pixel gris, il suffit de fixer ses trois composantes à la même valeur,
l’intensité lumineuse en l’occurence.
2. Complétez le fichier makefile avec une recette exo3 permettant de produire l’exécutable exo3.
3. Testez votre programme avec l’image fournie et vérifiez son fonctionnement en visualisant le
résultat.

Bonus : autres transformations
1. Rotation de 90°
2. Redimensionnement (division des dimensions par 2 n )
3. Détection de contour
