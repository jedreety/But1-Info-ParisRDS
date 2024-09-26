#include <stdio.h>
#pragma warning ( disable : 4996)

int main() {

	unsigned int jour;
	printf("Bonjour Saisir le jour :");

	if (scanf("%u", &jour) != 1) {
		printf("Une erreur est survenue lors de la saisie du jour");
		return -1;
	}

	// Verifie si le jour est une valeur correct
	if (jour < 1 || jour > 7) {
		printf("Le jour choisie n'est pas compris entre 1 et 7 inclus");
		return 1;
	}

	// Methode des instructions if/else
	if (jour == 6) {
		printf("Le medecin est d'astreinte");
	}
	else if (jour == 7) {
		printf("Le medecin est en conge");
	}
	else {
		printf("Le medecin est present");
	}

	// Methode l’instruction switch
	switch (jour)
	{
	case 1:
		printf("Le medecin est present");
		break;
	case 2: 
		printf("Le medecin est present");
		break;
	case 3: 
		printf("Le medecin est present");
		break;
	case 4:
		printf("Le medecin est present");
		break;
	case 5:
		printf("Le medecin est present");
		break;
	case 6: 
		printf("Le medecin est d'astreinte");
		break;
	case 7: 
		printf("Le medecin est en conge");
		break;

	default:
		break;
	}

	// Méthode avec l’opérateur conditionnel ternaire (?:)
	printf("%s\n", jour == 6 ? "Le medecin est d'astreinte" :
		(jour == 7 ? "Le medecin est en conge" :
			"Le medecin est present"));

	return 0;
}
