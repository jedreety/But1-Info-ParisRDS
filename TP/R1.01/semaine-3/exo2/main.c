#include <stdio.h>

enum { TAB_LEN = 5 };

int main() {

	const unsigned int tab[TAB_LEN] = { 1, 50, 20, 19, 5 };
	unsigned int copy_tab[TAB_LEN];

	// Copy les valeurs de tab dans copy tab dans l'ordre invers
	for (int i = 0; i < TAB_LEN; ++i) {
		copy_tab[TAB_LEN - i - 1] = tab[i];
	}

	// Affiche les valeurs de copy tab
	for (int i = 0; i < TAB_LEN; ++i) {

		printf("%u \n", copy_tab[i]);
	}

	return 0;

}
