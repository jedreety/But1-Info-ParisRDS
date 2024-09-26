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

	unsigned int index_eleve_petit = 0;
	unsigned int index_eleve_grand = 0;

	for (int i = 0; i < NB_ETUDIANTS_MAX; ++i) {

		// si erreur sur scanf
		if (scanf("%29s %u", &temp_nom, &temp_taille) != 2) {
			return -1;
		}

		if (temp_taille == 0) {
			break;
		}

		// assigne les valeurs dans la liste d'etudiant
		strcpy(tab_etudiant[i].nom, temp_nom);
		tab_etudiant[i].taille = temp_taille;

		// change l'index si l'eleve actuelle est plus PETIT
		if (tab_etudiant[i].taille < tab_etudiant[index_eleve_petit].taille) {
			index_eleve_petit = i;
		}

		// change l'index si l'eleve actuelle est plus GRAND
		if (tab_etudiant[i].taille > tab_etudiant[index_eleve_grand].taille) {
			index_eleve_grand = i;
		}

	}

	// affiche l'eleve le plus grand et le plus petit
	printf("Le plus petit : \nnom : %s, taille : %u \n", tab_etudiant[index_eleve_petit].nom, tab_etudiant[index_eleve_petit].taille);
	printf("Le plus grand : \nnom : %s, taille : %u \n", tab_etudiant[index_eleve_grand].nom, tab_etudiant[index_eleve_grand].taille);

	return 0;

}
