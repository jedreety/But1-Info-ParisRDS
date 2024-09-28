#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning ( disable : 4996 )

enum { SHIFT = 2, MAX_LEN = 100 };

int main() {

    char input[MAX_LEN];       // Chaîne saisie par l'utilisateur
    char original[MAX_LEN];    // Sauvegarde de la chaîne originale
    char encrypted[MAX_LEN];   // Chaîne cryptée
    char decrypted[MAX_LEN];   // Chaîne décryptée
    int len;                // Longueur de la chaîne

    printf("Entrez une chaine de caracteres ( tout en majuscule stp sinon ca marche pas ) : ");
	if (scanf(" %99s", input) != 1) {
		return -1;
	}

    strcpy(original, input);
    len = strlen(input);

    // Cryptage de la chaîne
    for (int i = 0; i < len; i++) {

        char c = input[i];
        if (c >= 'A' && c <= 'Z') {
            // Décalage des lettres majuscules
            encrypted[i] = ((c - 'A' + SHIFT) % 26) + 'A';
        }
        else {
            // Conservation des autres caractères
            encrypted[i] = c;
        }
    }
    encrypted[len] = '\0';

    printf("Chaine cryptee : %s\n", encrypted);

    // Décryptage de la chaîne
    for (int i = 0; i < len; i++) {
        char c = encrypted[i];
        if (c >= 'A' && c <= 'Z') {
            // Décalage inverse pour les lettres majuscules
            decrypted[i] = ((c - 'A' - SHIFT + 26) % 26) + 'A';
        }
        else {
            // Conservation des autres caractères
            decrypted[i] = c;
        }
    }
    decrypted[len] = '\0';  

    printf("Chaine decryptee : %s\n", decrypted);

    assert(strcmp(original, decrypted) == 0);

    printf("La chaine decryptee correspond bien à la chaine originale.\n");

    return 0;
}
