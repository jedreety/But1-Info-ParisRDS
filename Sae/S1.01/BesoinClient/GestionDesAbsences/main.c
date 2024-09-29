#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

enum {LONGUEUR_COMMANDE = 100};

int main() {

	char commande[LONGUEUR_COMMANDE];

	printf("Bienvenue sur l'application de gestion des absences. \n\n");
	
	while (1)
	{
		printf("Entrer une commade : ");

		// Lecture de la commande
		if (scanf("%s", commande) != 1)
		{
			printf("Erreur lors de la lecture de la commande.\n");
			return 1;
		}
		else
		{
			commande[LONGUEUR_COMMANDE - 1] = '\0';
		}

		// Traitement de la commande
		if (strcmp(commande, "exit") == 0)
		{
			printf("Au revoir !\n");
			break;
		}
		else
		{
			printf("Commande inconnue.\n");
		}
		
	}

}
