/*

Ce projet a pour but de r�aliser une recherche optimis�e de sous-cha�nes sans doublons de lettres dans une cha�ne de caract�res donn�e.

L'objectif de ce projet est de d�velopper un programme en langage C capable de parcourir une cha�ne de caract�res tr�s longue et de trouver,
de la mani�re la plus optimis�e possible, toutes les sous-cha�nes de longueur 14 qui ne contiennent aucun doublon de lettres.
Autrement dit, chaque lettre dans la sous-cha�ne doit �tre unique.

*/

#include <stdio.h>
#include <string.h>
#include <time.h>

enum { SOUS_CHAINE_LEN = 14, NB_METHOD = 3, ITERATIONS = 100000000 };

typedef enum { false, true } bool;

// M�thode 1
void method1(const char* chaine, unsigned int longueur);

// M�thode 2
void method2(const char* chaine, unsigned int longueur);

// M�thode 3
void method3(const char* chaine, size_t longueur);

int main() {

    printf("\n");

    const char chaine[] = "abcaefghijklmnoapqrstuvwxyzabcde";
    clock_t times[NB_METHOD];

    // M�thode 1

    times[0] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method1(chaine, strlen(chaine));
    }
    times[0] = clock() - times[0];

    // Affichage des temps d'ex�cution
    printf("Temps d'execution pour la methode 1 : %f secondes\n", (double)times[0] / CLOCKS_PER_SEC);
    // Temps d'ex�cution pour la m�thode 1 : 19.552000 secondes

    // M�thode 2
    times[1] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method2(chaine, strlen(chaine));
    }
    times[1] = clock() - times[1];

    // Affichage des temps d'ex�cution
    printf("Temps d'execution pour la methode 2 : %f secondes\n", (double)times[1] / CLOCKS_PER_SEC);
    // Temps d'ex�cution pour la m�thode 2 : 4.602000 secondes

    // M�thode 3
    times[2] = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        method3(chaine, strlen(chaine));
    }
    times[2] = clock() - times[2];

    // Affichage des temps d'ex�cution
    printf("Temps d'execution pour la methode 3 : %f secondes\n", (double)times[2] / CLOCKS_PER_SEC);
    // Temps d'ex�cution pour la m�thode 3 : 5.265000 secondes

    /*
    4.602000 / 19.552000 = 0.2357 soit 23.57% du temps de la m�thode 1
    5.265000 / 19.552000 = 0.2692 soit 26.92% du temps de la m�thode 1

    On peut voir que la m�thode 2 est plus rapide que la m�thode 3
    Mais la m�thode 3 peut �tre plus rapide sur des sous-cha�nes plus longues

    Ex avec une cha�ne de 1000 caract�res
    Temps d'ex�cution pour la m�thode 1 : 3.009000 secondes
    Temps d'ex�cution pour la m�thode 2 : 1.004000 secondes
    Temps d'ex�cution pour la m�thode 3 : 0.433000 secondes

    1.004000 / 3.009000 = 0.3338 soit 33.38% du temps de la m�thode 1
    0.433000 / 3.009000 = 0.1438 soit 14.38% du temps de la m�thode 1

    Soit 7 (6,666..) fois plus rapide pour la m�thode 3
    Contre 3 (2,994..) fois plus pour la m�thode 2

    Donc la m�thode 3 est plus rapide que la m�thode 2 sur des cha�nes plus longues
    */

    /*
    En conclusion, un projet assez fun mais qui a demand� beaucoup de r�flexion mais pas extr�mement beaucoup de temps ou de code.
    Il se peut qu'il existe des m�thodes plus optimis�es (pour �tre honn�te je n'ai pas cherch�)
    Une piste pourrait �tre de prendre la r�p�tition de lettre la plus � droite, en gros la derni�re.
    Il m'a permis d'approfondir mes connaissances sur les bits et les op�rations bit � bit et les structures de donn�es.
    Fun : 7/10
    Difficult� : 5/10 (d�pend de la m�thode choisie)
    Utilit� : 9/10 � refaire
    */

    return 0;
}


void method1(const char* chaine, size_t longueur) {

    // M�thode d'approche na�ve = de loin la meilleure hehe
    bool chaine_correct = false;
    bool doublons = false;

    char sous_chaine[SOUS_CHAINE_LEN + 1];
    unsigned int index = 0;

    // Parcours de la cha�ne 
    for (unsigned int i = 0; i < longueur; ++i) {
        index = 0;
        doublons = false;

        // Parcours de d�calage � d�calage + longueur 
        for (unsigned int j = i; j < SOUS_CHAINE_LEN + i; ++j) {

            sous_chaine[index] = chaine[j];

            // V�rifie si la lettre n'est pas d�j� dans la cha�ne
            for (unsigned int h = 0; h < j - i; ++h) {

                if (sous_chaine[h] == sous_chaine[index] && index != h) doublons = true;
            }

            if (doublons) break;

            // Si la cha�ne est pleine et qu'il n'y a pas de doublons
            if ((j == SOUS_CHAINE_LEN + i - 1) && !doublons) chaine_correct = true;

            ++index;

        }

        sous_chaine[SOUS_CHAINE_LEN] = '\0';

        if (chaine_correct) {

            // printf("Cha�ne trouv�e : %s , indice %u de caract�re %c\n", sous_chaine, i + SOUS_CHAINE_LEN, chaine[i + SOUS_CHAINE_LEN]);
            break;
        }

        if (i + SOUS_CHAINE_LEN >= longueur) {

            printf("Aucune cha�ne trouv�e\n");
            break;

        }

    }
}

void method2(const char* chaine, size_t longueur) {

    /*
    Ma pens�e :
    Les lettres sont du code ASCII,
    donc 'a' = 97, 'b' = 98 ... 'z' = 122
    On peut prendre un unsigned int et prendre chaque bit pour une lettre
    car 122 - 97 = 25, donc 26 bits suffisent pour stocker chaque lettre
    En bref, puisque une lettre est un indice de 0 � 25, on peut voir si elle est r�p�t�e ou non en utilisant un masque de bits (ici j'ai pr�f�r� faire une soustraction, c'est plus simple) (unsigned int = 32 bits)
    En C, c'est plus simple car un char est un octet hehe
    */

    unsigned int sous_chaine;

    // Parcours de la cha�ne
    for (unsigned int i = 0; i < longueur; ++i) {
        sous_chaine = 0;

        // Parcours de d�calage � d�calage + longueur
        for (unsigned int j = i; j < SOUS_CHAINE_LEN + i; ++j) {
            /*
            � savoir, quand j'�cris 1 << (chaine[j] - 'a') �a me sert � avoir en binaire la place de la lettre
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
            Le "if" sert � voir si la lettre est d�j� pr�sente
            La comparaison avec un AND (et) nous renvoie si la lettre est d�j� dans la cha�ne
            Car si elle est d�j� pr�sente, alors le AND nous renvoie un nombre diff�rent de 0

            Ex :
            Mon int = 0000 0001, le 'a' est pr�sent
            Je calcule la place du 'a' = 1 << 0 = 0000 0001

            Je fais un AND entre mon int et la place du 'a'
            0000 0001
            0000 0001
            ----------
            0000 0001

            Le r�sultat est diff�rent de 0 donc le 'a' est d�j� pr�sent
            */
            if (sous_chaine & (1 << (chaine[j] - 'a'))) break;

            /*
            Le 'if' sert � ajouter la lettre au int
            Je fais un OR (ou) entre mon int et la place de la lettre
            Ainsi je rajoute la lettre � mon int
            En gros, elle remplace le 0 par un 1 � l'index de la lettre
            */
            sous_chaine |= (1 << (chaine[j] - 'a'));

            // Une fois la boucle finie
            if (j == SOUS_CHAINE_LEN + i - 1) {
                // printf("Cha�ne trouv�e : %.*s , indice %u de caract�re %c\n", SOUS_CHAINE_LEN, chaine + i, i + SOUS_CHAINE_LEN, chaine[i + SOUS_CHAINE_LEN]); 
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
            // Ajoute la lettre � la sous-cha�ne
            sous_chaine |= (1 << (chaine[i] - 'a'));
            ++i;

            if (i - index == SOUS_CHAINE_LEN) {
                // printf("Cha�ne trouv�e : %.*s , indice %u\n", SOUS_CHAINE_LEN, chaine + index, i - 1);
                return;
            }
        }
        else {
            // Jusqu'� la premi�re occurrence
            while (chaine[index] != chaine[i]) {
                // Enl�ve la lettre de la sous-cha�ne la plus � gauche
                sous_chaine &= ~(1 << (chaine[index] - 'a'));
                ++index;
            }

            sous_chaine &= ~(1 << (chaine[index] - 'a'));
            ++index;
        }
    }
}
