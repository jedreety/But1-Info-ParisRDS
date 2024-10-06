Chaque jeu de test xxx comprend 2 fichiers. Le premier, nommé in-xxx.txt, contient une suite de commandes devant être acceptées par votre programme. Le second, nommé out-xxx.txt, contient la suite des messages que votre programme doit afficher lorsque les commandes contenues dans in-xxx.txt sont entrées au clavier.

Vous pouvez en faire différents usages.

Si vous voulez stopper votre programme après qu'une partie des commandes d'un fichier in-xxx.txt, il vous suffit d'insérer une ligne avec la commande "exit" là où vous voulez arrêter l'excécution de votre programme. Il vous suffira de supprimer cette ligne lorsque les commandes suivantes seront supportées.

Vous pouvez copier une à une les commandes de in-xxx.txt pour les coller une à une lors de l'exécution de votre programme. Vous pouvez tout aussi bien copier plusieurs ligne en une foi et les soumettre (en les collant en une fois) dans la fenètre d'exécution du programme. Ce mode est particulièrement utile lorsqu'on veut employer le debuger et mettre des points d'arrêt.

Vous pouvez aussi éviter tout copier/coller en redirigeant l'entrée de votre programme. Cela peut se faire facilement à partir d'une invite de commande (ou d'un terminal).

Sous windows, le fichier exécutable résultant de la compilation porte le nom du projet suivi de .exe. Sous Visual Studio, il se trouve dans le répertoire Debug de la "solution" contenant le projet.

Vous devez copier les fichiers in-xxx.txt et out-xxx.txt dans le répertoire contenant ce fichier exécutable. Lancez ensuite une invite de commande dans ce même répertoire et taper les commandes suivantes. On fait l'hyptothèse que votre projet est nommé s1-01 et donc que l'exécutable est s1-01.exe.

s1-01.exe < in-xxx.txt

Votre programme s'exécute et vous n'avez rien à saisir, les commandes sont prises dans in-xxx.txt. Par contre, vous voyez tous les affichages à l'écran. Ce mode est très bien lorsque vous voulez mettre au point les affichages de votre programme.

s1-01.exe < in-xxx.txt > res-xxx.txt

Là encore, vous n'avez rien à saisir mais vous ne voyez plus les affichages de votre programme. Tout ce que votre programme aurait du afficher est maintenant sauvegardé dans le fichier res-xxx.txt. Ce mode va nous permettre de comparer automatiquement que votre programme affiche bien ce qui est attendu. Tapez la commande suivante.

fc /w res-xxx.txt out-xxx.txt

Cette commande affiche "FC : aucune différence trouvée" si les 2 fichiers ne diffèrent que par des espaces (les alignements ne sont pas nécessairement respectés) et affiche les différences trouvées dans le cas contraire.

Si vous voulez aussi vérifier que les alignements sont bien respectés, il suffit de supprimer l'option /w. 

fc res-xxx.txt out-xxx.txt

La liste commandes couvertes par chaque jeu de test est la suivante. 

* in-sp1.txt    : commandes "inscription", "absence" et "etudiants".
* in-sp2.txt    : commandes sp1 + "justificatif", "validation" et "validations"
* in-sp3.txt    : commandes sp2 + "etudiant"
* in-sp4.txt    : commande sp3 + "defaillants"

Pour toutes questions, vous pouvez m'écrire (denis.poitrenaud@u-paris.fr).
