#include <stdio.h>
#include <string.h>
#pragma warning ( disable : 4996 )

enum { LONGUEUR_MAX = 30, NB_ETUDIANTS_MAX = 20 };

typedef struct {
	char nom[LONGUEUR_MAX];
	unsigned int taille; // (en cm)
} Etudiant;

int main() {

	Etudiant tab_etudiant[NB_ETUDIANTS_MAX];
	char temp_nom[LONGUEUR_MAX];
	unsigned int temp_taille;

	unsigned int somme_taille = 0;
	unsigned int nbr_eleve = 0;

	for (int i = 0; i < NB_ETUDIANTS_MAX; ++i) {

		// %29s pour avoir une longueur max de 29
		if (scanf("%29s %u", &temp_nom, &temp_taille) != 2) {
			return -1;
		}

		if (temp_taille == 0) {
			break;
		}

		// assigne les valeurs dans la liste d'etudiant
		strcpy(tab_etudiant[i].nom, temp_nom);
		tab_etudiant[i].taille = temp_taille;

		somme_taille = somme_taille + temp_taille;
		++nbr_eleve;

	}

	float moyenne = somme_taille / nbr_eleve;
	unsigned int index_eleve_proche_moyenne = 0;
	float difference_eleve_proche = 10000.;
	float difference;

	for (int i = 0; i < nbr_eleve; ++i) {

		difference = moyenne - tab_etudiant[i].taille;
		// inverse si difference est negative
		if (difference < 0) {
			difference = difference * -1;
		}

		if (difference < difference_eleve_proche) {
			difference_eleve_proche = difference;
			index_eleve_proche_moyenne = i;
		}
	}

	printf("%s", tab_etudiant[index_eleve_proche_moyenne].nom);

	return 0;

}
