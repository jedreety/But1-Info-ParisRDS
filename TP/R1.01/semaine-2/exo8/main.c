#include <math.h>
#include <stdio.h>
#pragma warning ( disable : 4996)

int main()
{
	printf("Bonjour veuillez saisir un nombre : \n");

    int nombre;
	if (scanf("%d", &nombre) != 1) {
		printf("Une erreur est survenue lors de la saisie du nombre \n");
		return -1;
	}

    long long carre = (long long)nombre * nombre;

    // Trouver le nombre de chiffres dans le nombre initial
    int n = 0;
    int temp = nombre;
    while (temp > 0) {
        temp /= 10;
        n++;
    }

    // Diviser le carré en deux parties
    long long diviseur = pow(10, n);

    long long partie_gauche = carre / diviseur;
    long long partie_droite = carre % diviseur;

    // Vérifier si la somme des deux parties est égale au nombre initial
    if (partie_gauche + partie_droite == nombre && partie_droite != 0) {
        printf("Vrai : c'est un nombre de Kaprekar");
    }
    else
    {
        printf("ce n'est pas un nombre de Kaprekar");
    }

}

