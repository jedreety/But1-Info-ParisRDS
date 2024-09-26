#include <stdio.h>
#pragma warning ( disable : 4996)

int main() {

	int nbr1, nbr2;
	printf("Bonjour Saisir deux entiers :");

	if (scanf("%d %d", &nbr1, &nbr2) != 2) {
		printf("Une erreur est survenue lors de la saisie des entiers");
		return -1;
	}

	if (nbr1 == nbr2) {
		printf("Les deux se valent");
	}

	else if (nbr1 > nbr2) {
		printf("Le premier est plus grand que le second");
	}

	else {
		printf("Le second est plus grand que le premier");
	}

	return 0;
}
