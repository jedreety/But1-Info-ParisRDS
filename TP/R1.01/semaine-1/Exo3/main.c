#include <stdio.h>

int main() {

	const float x = 5.2f;
	const double y = 5.2;

	printf("%f", 10000000 * (x - y)); // Le resultat est different de 0, ceci est absurde.

	return 0;
}