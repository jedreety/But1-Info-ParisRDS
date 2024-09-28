#include <stdio.h>
#include <string.h>
#pragma warning ( disable : 4996 )

enum { MAX_STR_LENGTH = 50 };

int main() {
    char inputString[MAX_STR_LENGTH];

    printf("Veuillez saisir une chaîne de caracteres (max %d caracteres) : ", MAX_STR_LENGTH - 1);
	if (scanf("%49s", inputString) != 1) {
		return -1;
	}

    printf("Vous avez saisi : '%s'\n", inputString);
    printf("Longueur de la chaine (strlen) : %u\n", strlen(inputString));
    printf("Occupation memoire (sizeof) : %u\n", sizeof(inputString));

    return 0;
}
