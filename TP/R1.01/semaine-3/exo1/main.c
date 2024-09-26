#include <stdio.h>

// definir des const
#define LEN_TAB 100
enum { TAB_LEN = 5 }; // preferable definie que dans main et plus facile a deboguer

int main() {

	int tab1[LEN_TAB];
	const unsigned int tab2[TAB_LEN] = { 1, 50, 20, 19, 5 };

	for (int i = 0; i < TAB_LEN; ++i) {

		printf("%u \n", tab2[i]);
	}

	return 0;

}
