/*

Ce projet a pour but de réaliser une recherche optimisée de sous-chaînes sans doublons de lettres dans une chaîne de caractères donnée.

L'objectif de ce projet est de développer un programme en langage C capable de parcourir une chaîne de caractères très longue et de trouver,
de la manière la plus optimisée possible, toutes les sous-chaînes de longueur 14 qui ne contiennent aucun doublon de lettres.
Autrement dit, chaque lettre dans la sous-chaîne doit être unique.

*/

#include <stdio.h>
#include <string.h>
#include <time.h>

enum { SOUS_CHAINE_LEN = 14, NB_METHOD = 3, ITERATIONS = 100000000 };

typedef enum { false, true } bool;

// Méthode 1
void method1(const char* chaine, unsigned int longueur);

// Méthode 2
void method2(const char* chaine, unsigned int longueur);

// Méthode 3
void method3(const char* chaine, size_t longueur);

int main() {

    printf("\n");

    const char chaine[] = "abcaefghijklmnoapqrstuvwxyzabcde";
    clock_t times[NB_METHOD];

    // Méthode 1

    times[0] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method1(chaine, strlen(chaine));
    }
    times[0] = clock() - times[0];

    // Affichage des temps d'exécution
    printf("Temps d'execution pour la methode 1 : %f secondes\n", (double)times[0] / CLOCKS_PER_SEC);
    // Temps d'exécution pour la méthode 1 : 19.552000 secondes

    // Méthode 2
    times[1] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method2(chaine, strlen(chaine));
    }
    times[1] = clock() - times[1];

    // Affichage des temps d'exécution
    printf("Temps d'execution pour la methode 2 : %f secondes\n", (double)times[1] / CLOCKS_PER_SEC);
    // Temps d'exécution pour la méthode 2 : 4.602000 secondes

    // Méthode 3
    times[2] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method3(chaine, strlen(chaine));
    }
    times[2] = clock() - times[2];

    // Affichage des temps d'exécution
    printf("Temps d'execution pour la methode 3 : %f secondes\n", (double)times[2] / CLOCKS_PER_SEC);
    // Temps d'exécution pour la méthode 3 : 5.265000 secondes

    /*
    4.602000 / 19.552000 = 0.2357 soit 23.57% du temps de la méthode 1
    5.265000 / 19.552000 = 0.2692 soit 26.92% du temps de la méthode 1

    On peut voir que la méthode 2 est plus rapide que la méthode 3
    Mais la méthode 3 peut être plus rapide sur des sous-chaînes plus longues

    Ex avec une chaîne de 1000 caractères
    Temps d'exécution pour la méthode 1 : 3.009000 secondes
    Temps d'exécution pour la méthode 2 : 1.004000 secondes
    Temps d'exécution pour la méthode 3 : 0.433000 secondes

    1.004000 / 3.009000 = 0.3338 soit 33.38% du temps de la méthode 1
    0.433000 / 3.009000 = 0.1438 soit 14.38% du temps de la méthode 1

    Soit 7 (6,666..) fois plus rapide pour la méthode 3
    Contre 3 (2,994..) fois plus pour la méthode 2

    Donc la méthode 3 est plus rapide que la méthode 2 sur des chaînes plus longues
    */

    /*
    En conclusion, un projet assez fun mais qui a demandé beaucoup de réflexion mais pas extrêmement beaucoup de temps ou de code.
    Il se peut qu'il existe des méthodes plus optimisées (pour être honnête je n'ai pas cherché)
    Une piste pourrait être de prendre la répétition de lettre la plus à droite, en gros la dernière.
    Il m'a permis d'approfondir mes connaissances sur les bits et les opérations bit à bit et les structures de données.
    Fun : 7/10
    Difficulté : 5/10 (dépend de la méthode choisie)
    Utilité : 9/10 à refaire
    */

    return 0;
}


void method1(const char* chaine, size_t longueur) {

    // Méthode d'approche naïve = de loin la meilleure hehe
    bool chaine_correct = false;
    bool doublons = false;

    char sous_chaine[SOUS_CHAINE_LEN + 1];
    unsigned int index = 0;

    // Parcours de la chaîne 
    for (unsigned int i = 0; i < longueur; ++i) {
        index = 0;
        doublons = false;

        // Parcours de décalage à décalage + longueur 
        for (unsigned int j = i; j < SOUS_CHAINE_LEN + i; ++j) {

            sous_chaine[index] = chaine[j];

            // Vérifie si la lettre n'est pas déjà dans la chaîne
            for (unsigned int h = 0; h < j - i; ++h) {

                if (sous_chaine[h] == sous_chaine[index] && index != h) doublons = true;
            }

            if (doublons) break;

            // Si la chaîne est pleine et qu'il n'y a pas de doublons
            if ((j == SOUS_CHAINE_LEN + i - 1) && !doublons) chaine_correct = true;

            ++index;

        }

        sous_chaine[SOUS_CHAINE_LEN] = '\0';

        if (chaine_correct) {

            // printf("Chaîne trouvée : %s , indice %u de caractère %c\n", sous_chaine, i + SOUS_CHAINE_LEN, chaine[i + SOUS_CHAINE_LEN]);
            break;
        }

        if (i + SOUS_CHAINE_LEN >= longueur) {

            printf("Aucune chaîne trouvée\n");
            break;

        }

    }
}

void method2(const char* chaine, size_t longueur) {

    /*
    Ma pensée :
    Les lettres sont du code ASCII,
    donc 'a' = 97, 'b' = 98 ... 'z' = 122
    On peut prendre un unsigned int et prendre chaque bit pour une lettre
    car 122 - 97 = 25, donc 26 bits suffisent pour stocker chaque lettre
    En bref, puisque une lettre est un indice de 0 à 25, on peut voir si elle est répétée ou non en utilisant un masque de bits (ici j'ai préféré faire une soustraction, c'est plus simple) (unsigned int = 32 bits)
    En C, c'est plus simple car un char est un octet hehe
    */

    unsigned int sous_chaine;

    // Parcours de la chaîne
    for (unsigned int i = 0; i < longueur; ++i) {
        sous_chaine = 0;

        // Parcours de décalage à décalage + longueur
        for (unsigned int j = i; j < SOUS_CHAINE_LEN + i; ++j) {
            /*
            À savoir, quand j'écris 1 << (chaine[j] - 'a') ça me sert à avoir en binaire la place de la lettre
            Ex avec 'a' :
            'a' - 'a' = 0
            en binaire 0 = 0000 0000
            et donc 1 << 0 = 0000 0001

            Ex avec 'b' :
            'b' - 'a' = 1
            en binaire 1 = 0000 0001
            et donc 1 << 1 = 0000 0010

            Ex avec 'c' :
            'c' - 'a' = 2
            en binaire 2 = 0000 0010
            et donc 1 << 2 = 0000 0100

            Ainsi, chaine[j] - 'a' me renvoie l'indice de la lettre et 1 << (chaine[j] - 'a') me renvoie la place de la lettre dans le int
            */


            /*
            Le "if" sert à voir si la lettre est déjà présente
            La comparaison avec un AND (et) nous renvoie si la lettre est déjà dans la chaîne
            Car si elle est déjà présente, alors le AND nous renvoie un nombre différent de 0

            Ex :
            Mon int = 0000 0001, le 'a' est présent
            Je calcule la place du 'a' = 1 << 0 = 0000 0001

            Je fais un AND entre mon int et la place du 'a'
            0000 0001
            0000 0001
            ----------
            0000 0001

            Le résultat est différent de 0 donc le 'a' est déjà présent
            */
            if (sous_chaine & (1 << (chaine[j] - 'a'))) break;

            /*
            Le 'if' sert à ajouter la lettre au int
            Je fais un OR (ou) entre mon int et la place de la lettre
            Ainsi je rajoute la lettre à mon int
            En gros, elle remplace le 0 par un 1 à l'index de la lettre
            */
            sous_chaine |= (1 << (chaine[j] - 'a'));

            // Une fois la boucle finie
            if (j == SOUS_CHAINE_LEN + i - 1) {
                // printf("Chaîne trouvée : %.*s , indice %u de caractère %c\n", SOUS_CHAINE_LEN, chaine + i, i + SOUS_CHAINE_LEN, chaine[i + SOUS_CHAINE_LEN]); 
                return;
            }

        }
    }
}

void method3(const char* chaine, size_t longueur) {
    unsigned int index = 0;
    unsigned int i = 0;
    unsigned int sous_chaine = 0;

    while (i < longueur) {

        if (!(sous_chaine & (1 << (chaine[i] - 'a')))) {
            // Ajoute la lettre à la sous-chaîne
            sous_chaine |= (1 << (chaine[i] - 'a'));
            ++i;

            if (i - index == SOUS_CHAINE_LEN) {
                // printf("Chaîne trouvée : %.*s , indice %u\n", SOUS_CHAINE_LEN, chaine + index, i - 1);
                return;
            }
        }
        else {
            // Jusqu'à la première occurrence
            while (chaine[index] != chaine[i]) {
                // Enlève la lettre de la sous-chaîne la plus à gauche
                sous_chaine &= ~(1 << (chaine[index] - 'a'));
                ++index;
            }

            sous_chaine &= ~(1 << (chaine[index] - 'a'));
            ++index;
        }
    }
}
