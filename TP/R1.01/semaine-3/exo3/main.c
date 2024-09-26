#include <stdio.h>
#include <assert.h>

enum { TAB_LEN = 5 };

int main() {

	const unsigned int tab[TAB_LEN] = { 1, 50, 20, 19, 5 };

	unsigned int copy_tab_1[TAB_LEN] = { 1, 50, 20, 19, 5 };
	unsigned int temp;

	unsigned int copy_tab_2[TAB_LEN];

	// Copy les valeurs de tab dans copy tab dans l'ordre inverse
	for (int i = 0; i < TAB_LEN; ++i) {
		copy_tab_2[TAB_LEN - i - 1] = tab[i];
	}

	// inverse les valeurs de copy tab
	for (int i = 0; i < TAB_LEN/2; ++i) {

		temp = tab[TAB_LEN - i - 1];
		copy_tab_1[TAB_LEN - i - 1] = copy_tab_1[i];
		copy_tab_1[i] = temp;
	}

	// Affiche les valeurs de copy tab
	for (int i = 0; i < TAB_LEN; ++i) {

		assert(copy_tab_1[i] == copy_tab_2[i]);
	}

	return 0;

}
