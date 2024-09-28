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
	unsigned int i = 1;
	while (i <= nombre)
	{
		printf("%u \n", i++);
	}

	// Methode en employant une boucle do
	i = 1;
	do {
		printf("%u \n", i++);
	} while (i <= nombre);

	// Methode en employant une boucle for
	i = 1;
	for (i = 1; i <= nombre; i++) {
		printf("%u \n", i);
	}

	return 0;

}
