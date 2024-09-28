#include <stdio.h>
#pragma warning ( disable : 4996)

int main() {

	unsigned int nombre;
	if (scanf("%u", &nombre) != 1) {
		printf("Une erreur est survenue lors de la saisie du jour \n");
		return -1;
	}

	// Verifie si la valeur est correct
	if (nombre < 1) {
		printf("Le valeur choisie n'est pas compris entre 1 et MAX-INT inclus \n");
		return 1;
	}

	// Methode en employant une boucle while
	unsigned int i = nombre;
	while (i >= 1)
	{
		printf("%u \n", i--);
	}

	// Methode en employant une boucle do
	i = nombre;
	do {
		printf("%u \n", i--);
	} while (i >= 1);

	// Methode en employant une boucle for
	for (i = nombre; i >= 1 ; i--) {
		printf("%u \n", i);
	}

	return 0;

}
