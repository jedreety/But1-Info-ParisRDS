#include <stdio.h>
#include <limits.h>
#pragma warning ( disable : 4996 6031)

int main() {
	
	unsigned int somme_taille=0, nombre_deleve=0, taille_min= UINT_MAX, taille_max=0, taille_input=0;

	printf("Bonjour veuillez saisir la taille (cm) des eleves : \n");

	do // tant que l'input 
	{

		if (scanf("%u", &taille_input) != 1) {
			return -1;
		}
		
		if (taille_input != 0) 
		{
			somme_taille = somme_taille + taille_input;
			++nombre_deleve;

			// Si l'eleve est plus grand que la valeur stocke
			if (taille_input > taille_max) {
				taille_max = taille_input;
			}

			// Si l'eleve est plus petit que la valeur stocke
			if (taille_input < taille_min) {
				taille_min = taille_input;
			}
		}

	} while (taille_input != 0);

	if (nombre_deleve != 0) {
		float moyenne = (float)somme_taille / (float)nombre_deleve;
		printf("Pour %u d'eleve(s) la taille moyenne est de %.3f, la plus grande est %u, la plus petite est %u.", nombre_deleve, moyenne, taille_max, taille_min);
	}

	return 0;

}