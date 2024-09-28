#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning ( disable : 4996 )

enum { SHIFT = 2, MAX_LEN = 100 };

int main() {

    char input[MAX_LEN];       // Cha�ne saisie par l'utilisateur
    char original[MAX_LEN];    // Sauvegarde de la cha�ne originale
    char encrypted[MAX_LEN];   // Cha�ne crypt�e
    char decrypted[MAX_LEN];   // Cha�ne d�crypt�e
    int len;                // Longueur de la cha�ne

    printf("Entrez une chaine de caracteres ( tout en majuscule stp sinon ca marche pas ) : ");
	if (scanf(" %99s", input) != 1) {
		return -1;
	}

    strcpy(original, input);
    len = strlen(input);

    // Cryptage de la cha�ne
    for (int i = 0; i < len; i++) {

        char c = input[i];
        if (c >= 'A' && c <= 'Z') {
            // D�calage des lettres majuscules
            encrypted[i] = ((c - 'A' + SHIFT) % 26) + 'A';
        }
        else {
            // Conservation des autres caract�res
            encrypted[i] = c;
        }
    }
    encrypted[len] = '\0';

    printf("Chaine cryptee : %s\n", encrypted);

    // D�cryptage de la cha�ne
    for (int i = 0; i < len; i++) {
        char c = encrypted[i];
        if (c >= 'A' && c <= 'Z') {
            // D�calage inverse pour les lettres majuscules
            decrypted[i] = ((c - 'A' - SHIFT + 26) % 26) + 'A';
        }
        else {
            // Conservation des autres caract�res
            decrypted[i] = c;
        }
    }
    decrypted[len] = '\0';  

    printf("Chaine decryptee : %s\n", decrypted);

    assert(strcmp(original, decrypted) == 0);

    printf("La chaine decryptee correspond bien � la chaine originale.\n");

    return 0;
}
