#include <stdio.h>
#include <ctype.h> // pour la fonction tolower
#include <assert.h>

#pragma warning(disable: 4996 6031)




// Constante et type utilitaires
// ESP : espace, MUR : mur
typedef enum { ESP, MUR } Cellule;

// Hauteur et largeur du terrain de jeu (il est carré).
enum { TAILLE = 4 };

// Le terrain doit être initialisé conformément à la valeur de TAILLE.
const Cellule TERRAIN[TAILLE][TAILLE] = {
	{ESP, ESP, ESP, ESP},
	{ESP, MUR, ESP, MUR},
	{ESP, ESP, MUR, ESP},
	{MUR, ESP, ESP, ESP}
};

typedef struct /* distance */ {

	unsigned int min_deplacement;
	unsigned int ligne;
	unsigned int colonne;
	int visited[TAILLE][TAILLE];
	Cellule to_visit[TAILLE][TAILLE];
	Cellule actuelle;
} Distance;

// Directions possibles : haut, bas, droite et gauche
// (lettre de chaque direction suivie du déplacement relatif ligne puis colonne).
const int DIR[][3] = { {'h', -1, 0}, {'b', 1, 0}, {'d', 0, 1}, {'g', 0, -1} };
// Nb de directions
const int  NB_DIR = sizeof(DIR) / sizeof(DIR[0]);

// Retourne l'indice dans le tableau dir de la direction correspondante et NB_DIR si elle n'existe pas.
int conversion(char c) {
	for (int i = 0; i < NB_DIR; ++i)
		if (c == DIR[i][0])
			return i;
	return NB_DIR;
}

// Coordonnée valide (i.e. dans le terrain et cellule non occupée par un mur) ?
int estValide(int ligne, int colonne);

// Calcule le nombre minimal de déplacements nécessaires pour aller d'un point à un autre.
int distance(int ligDep, int colDep, int ligArr, int colArr);

int main() {
	// Position courante du joueur initialisée au point de départ.
	int ligne = 0, colonne = 0;
	// Cible à atteindre.
	const int LIGNE = TAILLE - 1, COLONNE = TAILLE - 1;
	// Nb minimal de déplacements nécessaires pour aller du point de départ à la cible.
	const int MIN_NB_DEP = distance(ligne, colonne, LIGNE, COLONNE);
	// Nb de déplacements du joueur.
	int nbDep = 0;

	printf("vous pouvez gagner en %d deplacements\n", MIN_NB_DEP);
	while (ligne != LIGNE || colonne != COLONNE) {
		printf("Vous etes en (%d, %d) et vous devez aller en (%d, %d)\n", ligne, colonne, LIGNE, COLONNE);
		printf("(h)aut, (b)as, (d)roite, (g)auche ? : ");
		char c;
		scanf("\n%c", &c);
		int d = conversion(tolower(c));
		if (d == NB_DIR)
			printf("direction inconnue\n");
		else {
			int li = ligne + DIR[d][1], co = colonne + DIR[d][2];
			if (estValide(li, co)) {
				ligne = li;
				colonne = co;
				++nbDep;
			}
			else
				printf("il y a un mur\n");
		}
	}
	if (nbDep == MIN_NB_DEP)
		printf("Bravo !!!\n");
	else if (nbDep > MIN_NB_DEP)
		printf("Vous pouvez faire mieux\n");
	else
		printf("Vous etes plus fort que moi !!!\n");
}

// à compléter durant les exercices

int estValide(int ligne, int colonne) {

	if (ligne < 0 || ligne >= TAILLE) {
		return 0;
	}
	if (colonne < 0 || colonne >= TAILLE) {
		return 0;
	}
		

	switch (TERRAIN[ligne][colonne])
	{
	case ESP :
		return 1;

	case MUR :
		return 0;

	default:
		break;
	}

	printf("Une erreur est survenue dans la valeur de la cellule terrain : f | estValide");
}

int distance(int ligDep, int colDep, int ligArr, int colArr) {
	Distance distance;
	distance.actuelle = TERRAIN[ligArr][colArr];
	distance.visited[ligArr][colArr] = 0;
	while (distance.visited[0][0] == NULL)
	{

		for (distance.ligne; distance.ligne < TAILLE; distance.ligne++) {

			for (distance.colonne; distance.colonne < TAILLE; distance.colonne++) {

				for (int i; i < NB_DIR; i++) {

					if ( distance.actuelle )
					
				}
			}
		}
	}
}
