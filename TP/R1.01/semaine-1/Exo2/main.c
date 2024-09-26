#include <stdio.h>

#pragma warning(disable : 4996)
int main() {

	printf("Bonjour, saisir les deux nombres :\n");

	float nombre_A;
	float nombre_B;

	const int nb_element = 2;

	if (scanf("%f %f", &nombre_A, &nombre_B) != nb_element) {
		printf("Erreur de saisie.\n");
		return 1;
	}

	float resultat = (nombre_A + nombre_B) / nb_element;

	printf("Le resultat est : %f", resultat); // Celon le type de nombre_B le resultat diffère

	return 0;
}
