#include <stdio.h>

int main() {

    double solde = 0.0;
    int operation;
    double montant;

    while (1) {

        printf("Entrez le type d'opération (0 pour retrait, 1 pour dépôt) : ");
		if (scanf("%d", &operation) != 1) {
			printf("Erreur lors de la saisie du type d'opération.\n");
			return -1;
		}

        printf("Entrez le montant de l'opération : ");
        if (scanf("%lf", &montant) != 1) {
            printf("Erreur lors de la saisie du montant de l'opération.\n");
            return -1;
        }

		if (montant < 0) { // Montant négatif
            printf("Le montant doit être positif.\n");
        }
        else 
        { 

			if (operation == 0) { // Retrait

                if (solde >= montant) {
                    solde -= montant;
                    printf("Retrait effectué. Nouveau solde : %.2f\n", solde);
                }
                else {
                    printf("Solde insuffisant. Opération impossible.\n");
                    printf("Solde actuel : %.2f\n", solde);
                }
            }

            else if (operation == 1) { // Dépôt
                
                solde += montant;
                printf("Dépôt effectué. Nouveau solde : %.2f\n", solde);
            }

            else { // Opération inconnue
                
                printf("Opération inconnue.\n");
                printf("Solde actuel : %.2f\n", solde);
            }

        }

    }

    return 0;
}
