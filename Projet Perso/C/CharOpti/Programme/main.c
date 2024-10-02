/* 

Ce projet a pour but de r�aliser une eecherche optimis�e de sous-cha�nes sans doublons de lettres dans une cha�ne de caract�res donn�e.

L'objectif de ce projet est de d�velopper un programme en langage C capable de parcourir une cha�ne de caract�res tr�s longue et de trouver, 
de la mani�re la plus optimis�e possible, toutes les sous-cha�nes de longueur 14 qui ne contiennent aucun doublon de lettres. 
Autrement dit, chaque lettre dans la sous-cha�ne doit �tre unique.

*/

#include <stdio.h>
#include <string.h>
#include <time.h>

enum { SOUS_CHAINE_LEN = 14, NB_METHOD = 1 };

typedef enum { false, true } bool;

// M�thode 1
void method1(const char* chaine, unsigned int longeur);

int main() {

	printf("\n");

	const char chaine[] = "abcaefghijklmnoapqrstuvwxyzabcde";
	clock_t times[NB_METHOD];
	
	// M�thode 1
	times[0] = clock();
	method1(chaine, strlen(chaine));
	times[0] = clock() - times[0];

	// Affichage des temps d'ex�cution
	printf("Temps d'execution pour la methode 1: %f secondes\n", (double)times[0] / CLOCKS_PER_SEC);


	return 0;
}

void method1(const char* chaine, unsigned int longeur) {
	
	// Methode d'approche naive = demain la meilleur hehe
	bool chaine_correct = false;
	bool doublons = false;

	char sous_chaine[SOUS_CHAINE_LEN + 1];
	unsigned int index = 0;

	// Parcour la cha�ne 
	for (unsigned int i = 0; i < longeur; ++i) {
		index = 0;
		doublons = false;

		// Parcour de decal a decal + Longueur 
		for (unsigned int j = i; j < SOUS_CHAINE_LEN + i; ++j) {

			
			sous_chaine[index] = chaine[j];

			// Verifie si la lettre n'est pas d�j� dans la chaine
			for (unsigned int h = 0; h < j - i; ++h) {

				if (sous_chaine[h] == sous_chaine[index] && index != h) doublons = true;
			}

			if (doublons) break;

			// Si la chaine est pleine et qu'il n'y a pas de doublons
			if ((j == SOUS_CHAINE_LEN + i - 1) && !doublons) chaine_correct = true;

			++index;

		}

		sous_chaine[SOUS_CHAINE_LEN] = '\0';
		
		if (chaine_correct) {
			
			printf("chaine trouve : %s , indice %u de charactere %c\n", sous_chaine, i + SOUS_CHAINE_LEN, chaine[i + SOUS_CHAINE_LEN]);
			break;
		}

		if (i + SOUS_CHAINE_LEN >= longeur) {

			printf("Aucune chaine trouve\n");
			break;

		}

	}
}