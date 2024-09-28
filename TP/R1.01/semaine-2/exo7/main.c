#include <stdio.h>

int main() {

    double solde = 0.0;
    int operation;
    double montant;

    while (1) {

        printf("Entrez le type d'op�ration (0 pour retrait, 1 pour d�p�t) : ");
		if (scanf("%d", &operation) != 1) {
			printf("Erreur lors de la saisie du type d'op�ration.\n");
			return -1;
		}

        printf("Entrez le montant de l'op�ration : ");
        if (scanf("%lf", &montant) != 1) {
            printf("Erreur lors de la saisie du montant de l'op�ration.\n");
            return -1;
        }

		if (montant < 0) { // Montant n�gatif
            printf("Le montant doit �tre positif.\n");
        }
        else 
        { 

			if (operation == 0) { // Retrait

                if (solde >= montant) {
                    solde -= montant;
                    printf("Retrait effectu�. Nouveau solde : %.2f\n", solde);
                }
                else {
                    printf("Solde insuffisant. Op�ration impossible.\n");
                    printf("Solde actuel : %.2f\n", solde);
                }
            }

            else if (operation == 1) { // D�p�t
                
                solde += montant;
                printf("D�p�t effectu�. Nouveau solde : %.2f\n", solde);
            }

            else { // Op�ration inconnue
                
                printf("Op�ration inconnue.\n");
                printf("Solde actuel : %.2f\n", solde);
            }

        }

    }

    return 0;
}
