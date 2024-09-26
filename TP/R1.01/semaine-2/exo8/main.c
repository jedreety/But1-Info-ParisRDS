#include <math.h>
#include <stdio.h>

int main()
{
    int nombre = 703;
    // Calculer le carr� du nombre
    long long carre = (long long)nombre * nombre;

    // Trouver le nombre de chiffres dans le nombre initial
    int n = 0;
    int temp = nombre;
    while (temp > 0) {
        temp /= 10;
        n++;
    }

    // Diviser le carr� en deux parties
    long long diviseur = pow(10, n);
    long long partie_gauche = carre / diviseur;

    printf("%u \n", partie_gauche);
    long long partie_droite = carre % diviseur;

    printf("%u", partie_droite);

    // V�rifier si la somme des deux parties est �gale au nombre initial
    if (partie_gauche + partie_droite == nombre && partie_droite != 0) {
        printf("Vrai : c'est un nombre de Kaprekar");
    }
    else
    {
        printf("ce n'est pas un nombre de Kaprekar");
    }

}


cc = cc + c
cc += c