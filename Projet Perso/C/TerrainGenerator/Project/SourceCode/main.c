/*
    Projet de Generation d'une Carte
    Auteur : Mehdi Mazouz
    Date : 2024

	Ce projet a pour but de générer une carte à l'aide de parametre et d'algorithme.

    L'objectif de ce projet est de développer un programme en langage C capable de generer une height map a l'aide de fonction noise pour creer et affiche un Terrain "realiste".
	Mais pour ce faire l'utilisation d'aide externe chatgpt ou humaine est interdite. Seul les articles et les documentations sont autorisés.

    En conclusion ce projet permet d'apprendre a apprendre. Il sera utile pour de futur projet que j'ai en tête.
	Il ma permis de comprendre comment fonctionne la generation de terrain en 2D et comment utiliser le bruit de Perlin pour generer des terrains realistes.
	Enregistre des données dans un fichier PPM
	Utilisation de la librairie curl pour envoyer des données sur Discord.

	Fun : 9/10 plutot fun d'experimenter avec les parametres
	Difficulté : 5/10 il faut etre bon en math et bien rechercher l'information
    Utilité : 10/10
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <curl/curl.h>

enum { LARGEUR = 256, LONGUEUR = 256, LEN_PERMUTATION_TAB = 256 };

// Prototypes des fonctions
// initalise le tableau p
void init_perlin(int p[]);
// Lisse la valeur x pour l'interpolation
double lisse(double x);
// Fait une interpolation linéaire
double lerp(double x, double a, double b);
// Calcule le produit scalaire de la distance et vecteur gradient
double gradient(int hash, double x, double y, double z);
// Calcule le bruit de perlin a un point x y z
double perlin(double x, double y, double z);
// Enregistre le terrain dans un fichier PPM
void save_ppm(double terrain[LARGEUR][LONGUEUR], double hauteurMax, double hauteurMin);

/* Je ne citerais pas mes documentations mais expliquerais ce que j'ai fais pour la suite de ce programme */

/* 1 ere etape la creation des fonctions noise
Dans cette étape, nous allons mettre en oeuvre la fonction de Perlin noise, qui est essentielle pour générer des terrains d'apparence naturelle.
Le Perlin noise est un type de gradient noise qui produit des motifs lisses et continus, idéaux pour simuler des phénomènes naturels tels que le terrain, les rivieres ou les nuages.
*/ 

/* Le tableau de permutation est un tableau de 256 nombres uniques.
Elle sera utilisé pour génére des vecteurs gradient ( vecteur dont les coordonnées sont les dérivées partielles ) de manière pseudo aléatoire */
// Noté qu'inclures les 256 valeurs sont importantes pour l'algorithme
const int permutation[LEN_PERMUTATION_TAB] = {
    151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,
    197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,
    56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,
    27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,
    92,41,55,46,245,40,244,102,143,54, 65,25,63,161,1,216,
    80,73,209,76,132,187,208,89,18,169,200,196,135,130,116,188,
    159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,
    58,17,182,189,28,42,223,183,170,213,119,248,152, 2,44,154,
    163,70,221,153,101,155,167, 43,172,9,129,22,39,253,19,98,
    108,110,79,113,224,232,178,185,112,104,218,246,97,228,251,34,
    242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,
    239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,
    50,45,127, 4,150,254,138,236,205,93,222,114, 67,29,24,72,
    243,141,128,195,78,66,215,61,156,180
};



/* Cette fonction sert à initialisé le tableau p en dubliquant le tableau de permutation
Les valeurs en double sont utilisé pour accéde aux valeurs sans avoir à se soucier de repartir a 0 quand la valeur dépasse 255 */
void init_perlin(int p[]) {
    for (int i = 0; i < LEN_PERMUTATION_TAB; i++)
        p[i] = permutation[i];
    for (int i = 0; i < LEN_PERMUTATION_TAB; i++)
        p[LEN_PERMUTATION_TAB + i] = p[i];
}

/* Cette fonction permet de lisser la valeur x pour avoir une meilleur transition entre les points de la grille
Pour cela on utilise la fonction f(x) = 6x^5 - 15x^4 + 10x^3 elle permet de sassure que la derive au valeur x = 0 et x = 1 est nulle */
double lisse(double x) {
    return x * x * x * (x * (x * 6 - 15) + 10);
}

/* Cette fonction effectue une interpolation linéaire entre deux valeurs a et b en fonction du paramètre x.
Quand x = 0, la fonction retourne a, quand x = 1, la fonction retourne b
Pour les valeurs de x entre 0 et 1, la fonction retourne une moyenne ponderee */
double lerp(double x, double a, double b) {
    return a + x * (b - a);
}

/* Cette fonction calcule le produit scalaire entre un vecteur gradient et un vecteur distance a partir du coin */
double gradient(int hash, double x, double y, double z) {
	// On s'assure que la valeur de hash est entre 0 et 15
    int h = hash & 15;
    
	/* Les valeurs de x et y sont selectionné en fonction de la valeur de h
    Cela nous permet d'etre sur d'avoir une selection de gradient variés */
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);

	// produit scalaire : retourne la somme de u et v avec un signe determiné par des bits de h
    return ((h & 1) == 0 ? u : -u) +
        ((h & 2) == 0 ? v : -v);
}

/* Cette fonction permet de générer une valeur de bruit pseudo aléatoire en 3D*/
double perlin(double x, double y, double z, const int p[]) {

	/* 
    X Y et Z sont les parties entières des coordonnées x y et z elles representent la cellule contenant le point
	 modulo 255 pour s'assurer que les valeurs n'excedent pas lorsqu'on accede au tableau de permutation */
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;

    /* On calcule les positions relative dans le cube 
    x y et z sont modifiés pour etre les parties fractionnaires des coordonnées d'entrée, représentant la position à l'intérieur du cube*/
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

	/* Calcule la courbe gradient pour chaqu'une des cordonées */
    double u = lisse(x);
    double v = lisse(y);
    double w = lisse(z);

    /* On calcule les veleurs des gradient a chaque coins */
    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

	/* l'interpolation linéaire des resultats
    elle permet de mélanger la contribution du gradient de manière homogène dans le cube. */
    double res = lerp(w,
        lerp(v,
            lerp(u, gradient(p[AA], x, y, z),
                gradient(p[BA], x - 1, y, z)),
            lerp(u, gradient(p[AB], x, y - 1, z),
                gradient(p[BB], x - 1, y - 1, z))),
        lerp(v,
            lerp(u, gradient(p[AA + 1], x, y, z - 1),
                gradient(p[BA + 1], x - 1, y, z - 1)),
            lerp(u, gradient(p[AB + 1], x, y - 1, z - 1),
                gradient(p[BB + 1], x - 1, y - 1, z - 1)))
    );

	// On normalise le resutat pour passé d'une valeur entre -1 et 1 à une valeur entre 0 et 1
    return (res + 1.0) / 2.0;
}

/* 2 eme etape generer une height map 
Dans cette étape, nous utiliserons la fonction Perlin noise mise en œuvre à l'étape 1 pour créer une height map en 2D.
Cette height map représente l'élévation de chaque point du terrain. Nous verrons également comment visualiser cette carte d'altitude en utilisant l'art ASCII pour plus de simplicité.
*/

int main() {

    // Initialisation du tableau de permutation
    int p[LEN_PERMUTATION_TAB * 2];
    init_perlin(p);

    double terrain[LARGEUR][LONGUEUR];

    /* Les parametre ajustable */
    double scale = 50.0; // Contrôle le niveau de détail. Une valeur d'échelle plus élevée permet d'obtenir un terrain plus lisse avec des éléments plus grands.
    int octaves = 7; // Nombre de couches de bruit à combiner. Plus il y a d'octaves, plus les détails sont fins.
    double persistence = 0.8; // Détermine la manière dont l'amplitude diminue pour chaque octave suivante. Valeurs comprises entre 0 et 1.
    
    double hauteurMin = INFINITY;
    double hauteurMax = -INFINITY;

    // Ajoute des détails au terrain en combinant plusieurs couches de bruit (octaves).
    for (int x = 0; x < LARGEUR; x++) {
        for (int y = 0; y < LONGUEUR; y++) {
            double amplitude = 1.0; // Amplitude initiale pour la première octave. Elle diminuera à chaque octave en fonction de la persistance.
            double frequence = 1.0; // Fréquence initiale pour la première octave. Elle augmentera avec chaque octave.
            double hauteurBruit = 0.0; // Accumule les valeurs de bruit de toutes les octaves pour déterminer la hauteur finale à chaque point.

            // Ajoute des détails au terrain en combinant plusieurs couches de bruit (octaves).
            for (int o = 0; o < octaves; o++) {

                /* sampleX et sampleY sont des coordonnées mises à l'échelle introduites dans la fonction de bruit de Perlin.
                L'ajustement de l'échelle et de la fréquence affecte la granularité du bruit. */
                double sampleX = x / scale * frequence;
                double sampleY = y / scale * frequence;

                // On genere des valeurs de bruit la valeur de z est fixé à 0 car nous voulons une carte en 2D
                double valeurBruit = perlin(sampleX, 0.0, sampleY, p) * 2 - 1;
                // Ajoute l'octave actuele au terrain pondéré par l'amplitude
                hauteurBruit += valeurBruit * amplitude;

                // On ajuste l'amplitude et la fréquence pour l'octave suivante
                amplitude *= persistence;
                frequence *= 2.0;
            }

            // On stocke la hauteur finale dans le tableau de terrain
            terrain[x][y] = hauteurBruit;

			// Met à jour les valeurs minimales et maximales
            if (hauteurBruit < hauteurMin) hauteurMin = hauteurBruit;
            if (hauteurBruit > hauteurMax) hauteurMax = hauteurBruit;
        }
    }

	// define le tableau de charactere pour le gradient
    /*             Eau  Sable plaine colline montagne  */
    char gradient[] = { '~', '.', '-', '^', 'A' };
    int tailleGradient = sizeof(gradient) / sizeof(gradient[0]);

    /*
	// On affiche le terrain en utilisant le gradient ASCII
	for (int x = 0; x < LARGEUR; x += 4) { // Ajuste le saut de ligne pour afficher moins de points
        for (int y = 0; y < LONGUEUR; y += 2) {

			// Récupère la valeur de hauteur à la position actuelle
            double value = terrain[x][y];

            // Normalise la valeur a [0, 1]
            double valueNormalise = (value - hauteurMin) / (hauteurMax - hauteurMin);

			// Trouve l'index correspondant dans le gradient
            int index = (int)(valueNormalise * (tailleGradient - 1));

			// S'assure que l'index est dans les limites du gradient
            if (index < 0) index = 0;
            if (index >= tailleGradient) index = tailleGradient - 1;

            printf("%c", gradient[index]);
        }
        printf("\n");
    }
    */

    
	// Enregistre le terrain dans un fichier PPM
    save_ppm(terrain, hauteurMax, hauteurMin);
    

    return 0;
}

/* 3 eme etape Visualisé le terrain 
Dans cette étape, nous allons améliorer la visualisation de votre terrain en enregistrant la carte d'altitude sous forme de fichier image.
Au lieu d'un fichier ASCII, nous allons enregistrer les données du terrain dans un fichier Portable Pixmap (PPM), qui est un format d'image simple, facile à générer et à visualiser.
*/


void save_ppm(double terrain[LARGEUR][LONGUEUR], double hauteurMax, double hauteurMin) {
    FILE* fp = fopen("../../imageOUT/terrain.ppm", "w");
    if (fp == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    // Write the PPM header
    fprintf(fp, "P3\n%d %d\n255\n", LARGEUR, LONGUEUR);

    // Loop through the terrain data and write pixel values
    for (int y = 0; y < LONGUEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            // Normalize the terrain value to [0, 1]
            double normalizedValue = (terrain[x][y] - hauteurMin) / (hauteurMax - hauteurMin);

            // Initialize RGB components
            int r, g, b;

            // Map normalizedValue to colors
            if (normalizedValue < 0.3) {
                // Water: Deep blue
                r = 0;
                g = 0;
                b = (int)(normalizedValue / 0.3 * 128 + 127); // From dark to lighter blue
            }
            else if (normalizedValue < 0.4) {
                double t = (normalizedValue - 0.4) / 0.3;
                // Sand: Light yellow
                r = (int)((1 - t) * 238 - 20);  
                g = (int)((1 - t) * 214 - 20);
                b = (int)((1 - t) * 175 - 20);
            }
            else if (normalizedValue < 0.7) {
                double t = (normalizedValue - 0.4) / 0.3;
                r = (int)((1 - t) * 40 + t * 25);   // From dark green to lighter green
                g = (int)((1 - t) * 130 + t * 80);
                b = (int)((1 - t) * 40 + t * 15);
            }
            else {
                // Mountain: Gray to white
                int gray = (int)((normalizedValue - 0.7) / 0.8 * 255);
                r = g = b = 200 + gray;
            }

            // Clamp color values to [0, 255]
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);

            // Write the color values
            fprintf(fp, "%d %d %d ", r, g, b);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("Terrain image saved as terrain.ppm\n");
}
