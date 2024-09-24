#include <stdio.h>

// Function prototype
void printHello();

int main() {

	printHello();
	return 0;
}

void printHello() {

	const char *phrase = "Hello, World!\n";
	printf("%s", phrase);
}
