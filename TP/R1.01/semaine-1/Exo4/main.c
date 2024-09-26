#include <stdio.h>
#include <assert.h>

int main() {

	 const float taux_conversion = 1.17f;
	 float dollars = 100.f;

	 float euro = dollars / taux_conversion;

	 const double valeur_attendue = 85.470085470085470085470085470085;
	 const float marge = 0.0001;

	printf("%f \n", euro);
	assert((double)euro - valeur_attendue <= (double)marge);

	return 0;
}
