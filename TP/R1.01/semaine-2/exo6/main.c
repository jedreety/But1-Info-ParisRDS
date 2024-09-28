#include <stdio.h>

int main() {
    int coefficient;
    double note;
    double somme_coefL = 0.0;
    int somme_coef = 0;

    while (1) {

        printf("Entrez le coefficient (0 pour terminer): ");
		if (scanf("%d", &coefficient) != 1) {
			printf("Erreur lors de la saisie du coefficient.\n");
			return -1;
		}

        if (coefficient == 0) {
            break;
        }

        printf("Entrez la note correspondante: ");
		if (scanf("%lf", &note) != 1) {
			printf("Erreur lors de la saisie de la note.\n");
			return -1;
		}

        somme_coefL += coefficient * note;
        somme_coef += coefficient;
    }

    if (somme_coef == 0) {
        printf("Aucune note saisie.\n");
    }
    else {
        double moyenne = somme_coefL / somme_coef;
        printf("La moyenne pondérée est : %.2f\n", moyenne);
    }

    return 0;
}
