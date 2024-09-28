#include <stdio.h>
#include <string.h>
#include <ctype.h>
#pragma warning ( disable : 4996 )

int main() {
    char name[100]; 
    int sum = 0;

    printf("Entrez votre prenom : ");
	if (scanf("%99s", name) != 1) {
		return -1;
	}

    // Calcul de la somme des positions des lettres
    for (int i = 0; name[i] != '\0'; i++) {
        char c = toupper(name[i]);  // Conversion en majuscule
        if (c >= 'A' && c <= 'Z') {
            int pos = c - 'A' + 1;  // Position dans l'alphabet (A=1, B=2, ..., Z=26)
            sum += pos;
        }
        else {
			// ignoré si pas une lettre ( pas sensé arriver )
        }
    }

    // Réduction de la somme à un seul chiffre en sommant les chiffres
    while (sum >= 10) {
        int temp_sum = 0;
        while (sum > 0) {
            temp_sum += sum % 10;  // Ajout du chiffre des unités
            sum /= 10;             // Passage au chiffre suivant
        }
        sum = temp_sum;         
    }

    
    printf("Le nombre magique de %s est %d.\n", name, sum);

    return 0;
}
