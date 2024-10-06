#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

/*
	Projet de gestion des absences
	Auteur : Mehdi Mazouz
	Date : 2024

	Pour compiler le programme, il suffit de taper la commande suivante dans le terminal :
	> gcc main.c -o main

    Pour ajouter une commande :
	1 - Ajouter le nom de commande dans la liste liste_commande    <const STR_Commande liste_commande[]>
	2 - Ajouter la commande dans l'énumération INT_Commande        <enum INT_Commande>
	
    !!! A savoir l'ordre des commandes dans l'énumération doit être le même que dans la liste liste_commande !!!

    	3 - Ajouter la commande dans la fonction help				     <void afficher_aide()>
	4 - Ajouter la commande dans la fonction executer_commande      <bool executer_commande(Context* context, char commande[LONGUEUR_COMMANDE])>
	5 - Ajouter les fonctions necessaire.

	Fonction d'aide :
	- lecture_commande : Permet de lire le nom de la commande

	- loop_to_space : Permet de passer au mot suivant en donnant l'index ( renvoie l'index de la premiere l'ettre dans la commande du mot suivant )
	- lecture_nombre : Permet de lire un nombre
	- lecture_string : Permet de lire une chaine de caractères

	- verifier_etudiant_existe : Permet de vérifier si un étudiant existe ( renvoie un booléen )
	- trouver_etudiant_par_id : Permet de trouver un étudiant par son ID ( renvoie un pointeur sur l'étudiant )

	- verifier_absence_existe : Permet de vérifier si une absence existe ( renvoie un booléen )
	- trouver_absence_par_id : Permet de trouver une absence par son ID ( renvoie un pointeur sur l'absence )

	!!! 
        Les fonctions trouver_etudiant_par_id et trouver_absence_par_id sont implementé de sorte a ce que les IDs sont attribués séquentiellement et sans suppression
		Si une fonction supprime un étudiant ou une absence, il faudra adapter ces fonctions ( remplace l'id par un NULL ou changer la fonction par une recherche linéaire )
    	!!!

	... quelques autres fonctions utiles sont disponibles mais ne sont pas mentionnées ici.

*/

typedef enum {
    false = 0,
    true = 1,
} bool;

enum {
    MAX_ABSENCES = 100,
    MAX_ETUDIANTS = 100,

    LONGUEUR_COMMANDE = 100 + 1,
    LONGUEUR_DEMI_JOURNEE = 2 + 1,
    LONGUEUR_NOM = 30 + 1,
    LONGUEUR_JUSTIFICATIF = 50 + 1,
};

typedef char STR_Commande[LONGUEUR_COMMANDE];

const STR_Commande liste_commande[] = {
    "exit",
    "inscription",
    "absence",
    "etudiants",
    "justificatif",
    "help"
};
const unsigned int nb_commande = sizeof(liste_commande) / sizeof(liste_commande[0]);

typedef enum {
    EXIT = 0,
    INSCRIPTION,
    ABSENCE,
    ETUDIANTS,
	JUSTIFICATIF,
    HELP,
    INCONNU
} INT_Commande;

typedef struct {
    unsigned int id;

    unsigned int Njour;
    char demijournee[LONGUEUR_DEMI_JOURNEE];
} Absence;

typedef struct {
    unsigned int id;

    char nom[LONGUEUR_NOM];
    int groupe;

	// liste et nombre d'absences de l'étudiant
    unsigned int absences_id[MAX_ABSENCES];
    unsigned int nombreAbsences;
} Etudiant;

typedef struct {
	// prochain id pour les étudiants et les absences
    unsigned int next_etudiant_id;
    unsigned int next_absence_id;

	// liste des étudiants et des absences
    Etudiant etudiants[MAX_ETUDIANTS];
    Absence absences[MAX_ABSENCES * MAX_ETUDIANTS];

	// nombre d'étudiants et d'absences
    unsigned int nombreEtudiants;
    unsigned int nombreAbsences;
} GestionAbsences;

typedef struct {
    unsigned int id;

    GestionAbsences gestionAbsences;
    unsigned int nombreCommandes;
} Context;
void init_context(Context* context, unsigned int context_id) /* Initialisé le context */ {
    context->id = context_id;
	context->nombreCommandes = 0;
	context->gestionAbsences.next_etudiant_id = 1;
	context->gestionAbsences.next_absence_id = 1;
	context->gestionAbsences.nombreEtudiants = 0;
	context->gestionAbsences.nombreAbsences = 0;
}

/* C0 | Fonctions de lecture et d'exécution des commandes */
void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE]);
INT_Commande lire_commande(char commande[LONGUEUR_COMMANDE]);
void afficher_aide();
void loop_to_space(char commande[LONGUEUR_COMMANDE], int* i);
bool executer_commande(Context* context, char commande[LONGUEUR_COMMANDE]);
void lecture_nombre(char commande[LONGUEUR_COMMANDE], int* nombre, int i);
void lecture_string(char commande[LONGUEUR_COMMANDE], char string[LONGUEUR_COMMANDE], unsigned int string_len, int i);

/* C1 | Fonctions pour la gestion des étudiants */
void inscrire_etudiant(Context* context, char commande[LONGUEUR_COMMANDE]);
void lecture_nom_etudiant(char commande[LONGUEUR_COMMANDE], char nom[LONGUEUR_NOM]);
void lecture_groupe_etudiant(char commande[LONGUEUR_COMMANDE], int* groupe);
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe);
Etudiant* trouver_etudiant_par_id(GestionAbsences* gestionAbsences, unsigned int id);

/* C2 | Fonctions pour la gestion des absences */
void enregistrer_absence(Context* context, char commande[LONGUEUR_COMMANDE]);
void lecture_id_etudiant(char commande[LONGUEUR_COMMANDE], unsigned int* id);
void lecture_Njour_absence(char commande[LONGUEUR_COMMANDE], unsigned int* Njour);
void lecture_demijournee_absence(char commande[LONGUEUR_COMMANDE], char demijournee[LONGUEUR_DEMI_JOURNEE]);
bool verifier_absence_existe(GestionAbsences* gestionAbsences, unsigned int etudiant_id, unsigned int Njour, char demijournee[LONGUEUR_DEMI_JOURNEE]);
Absence* trouver_absence_par_id(GestionAbsences* gestionAbsences, unsigned int id);

/* C3 | Fonctions pour l'affichage des étudiants absents */
void calculer_etudiants_absents(char commande[LONGUEUR_COMMANDE], Context* context);
void lecture_jour_absence(char commande[LONGUEUR_COMMANDE], int* jour);
int compte_nombre_absence(GestionAbsences* gestionAbsences, Etudiant* etudiant, int jour);
int sort_etudiants_absents(const void* a, const void* b);
void afficher_etudiants_absents(GestionAbsences* gestionAbsences, Etudiant etudiant_absents[MAX_ETUDIANTS], int nombreEtudiantsAbsents, int jour);

/* C4 | Fonctions de dêpot de justificatif */


int main() {
    char commande[LONGUEUR_COMMANDE];

    // Initialisation du contexte
    Context context;
	init_context(&context, 1);

    printf("Bienvenue sur l'application de gestion des absences.\n");

    while (true) {
		printf("\n");

        context.nombreCommandes++;
        printf("(%u) Entrer une commande : ", context.nombreCommandes);

        // Lecture de la commande
        if (scanf(" %[^\n]%*c", commande) != 1) /* %[^\n] pour avoir toute la chaine et %*c pour la structure de la chaine (meme que %s ?) */ {
            printf("Erreur lors de la lecture de la commande.\n");
            return 1;
        }
        else {
			commande[LONGUEUR_COMMANDE - 1] = '\0'; // Ajout d'un caractère de fin de chaîne
        }

        // Traitement de la commande
        if (!executer_commande(&context, commande)) {
            break;
        }
    }

    return 0;
}

/* Fonction qui permet de lire le nom de la commande (premier mot de la commande) */
void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE]) {
	int i = 0; // index qui parcourt la chaine ( commande )

	// Parcourt la chaine jusqu'à l'espace ou la fin de la chaine
    while (commande[i] != ' ' && commande[i] != '\0') {
		nom_commande[i] = commande[i]; // Copie le caractère dans la reference
        i++;
    }
	nom_commande[i] = '\0';
}

/* Fonction qui renvoie un numéro correspondant à la commande */
INT_Commande lire_commande(char commande[LONGUEUR_COMMANDE]) {

	// nom_commande est le premier mot de la commande
    char nom_commande[LONGUEUR_COMMANDE];
    lecture_commande(commande, nom_commande);

    // Parcourt la liste des commandes
    for (unsigned int index = 0; index < nb_commande; ++index) {

		// Compare le nom de la commande avec la liste des commandes
        if (strcmp(nom_commande, liste_commande[index]) == 0) {
            /*
				Renvoie le numéro de la commande
				Pour savoir même si la fonction renvoie un int, il est interprete comme un INT_Commande
				Chaque commande a un numéro correspondant :
				- EXIT = 0
				- INSCRIPTION = 1
				etc...
				Ainsi on peut savoir quelle commande a été entrée
            */
			return index;
        }
    }
	return INCONNU; // Si la commande n'est pas dans la liste
}

/* Fonction qui affiche l'aide */
void afficher_aide() {
    printf("\nListe des commandes :\n\n");

    // EXIT
    printf("exit\n");
    printf("  Syntaxe : exit\n");
    printf("  Description : Quitter l'application.\n\n");

	// INSCRIPTION
    printf("inscription\n");
    printf("  Syntaxe : inscription <nom> <groupe>\n");
    printf("  Description : Inscrire un etudiant.\n");
    printf("  Parametres :\n");
    printf("    <nom>    : Nom de l'etudiant (chaine de caracteres, max %d caracteres, sans espaces)\n", LONGUEUR_NOM - 1);
    printf("    <groupe> : Numero de groupe (entier)\n\n");

	// ABSENCE
    printf("absence\n");
    printf("  Syntaxe : absence <id> <Njour> <demijournee>\n");
    printf("  Description : Enregistrer une absence pour un etudiant.\n");
    printf("  Parametres :\n");
    printf("    <id>           : Identifiant de l'etudiant (entier)\n");
    printf("    <Njour>        : Numero de jour (entier entre 1 et 40)\n");
    printf("    <demijournee>  : 'am' pour le matin, 'pm' pour l'apres-midi (chaine de caracteres, max %d caracteres)\n\n", LONGUEUR_DEMI_JOURNEE - 1);

	// ETUDIANTS
    printf("etudiants\n");
    printf("  Syntaxe : etudiants <jour>\n");
    printf("  Description : Afficher la liste des etudiants inscrits avec leur nombre total d'absences jusqu'au jour donne.\n");
    printf("  Parametres :\n");
    printf("    <jour> : Numero de jour courant (entier >= 1)\n\n");

	// JUSTIFICATIF
	printf("justificatif\n");
	printf("  Syntaxe : justificatif <id> <Njour> <justificatif>\n");
	printf("  Description : Deposer un justificatif pour une absence.\n");
	printf("  Parametres :\n");
	printf("    <id>           : Identifiant de l'absence (entier)\n");
	printf("    <Njour>        : Numero de jour (entier entre 1 et 40)\n");
	printf("    <justificatif> : Justificatif (chaine de caracteres, max %d caracteres)\n\n", LONGUEUR_JUSTIFICATIF - 1);

	// HELP
    printf("help\n");
    printf("  Syntaxe : help\n");
    printf("  Description : Afficher l'aide.\n");
}


/* Fonction qui permet de passer à l'espace suivant */
void loop_to_space(char commande[LONGUEUR_COMMANDE], int* i) {

	// Parcourt la chaine jusqu'à l'espace ou la fin de la chaine
    while (commande[*i] != ' ' && commande[*i] != '\0') {
        (*i)++;
    }

	// Si il y a des espaces consécutifs
    while (commande[*i] == ' ' && commande[*i] != '\0') {
        (*i)++;
    }
}

/* Exécute la commande */
bool executer_commande(Context* context, char commande[LONGUEUR_COMMANDE]) {
    /*
		Permet d'executer la commande entrée par l'utilisateur
		Chaque commande a un numéro correspondant

		Renvoie un booléen une fois la commande terminée :
		    > true : pour passer a la commande suivante
		    > false : pour quitter l'application
    */

    switch (lire_commande(commande)) /* lecture de la commande */ {
    case EXIT:
        printf("Au revoir !\n");
        return false;

    case INSCRIPTION:
        inscrire_etudiant(context, commande);
        break;

    case ABSENCE:
        enregistrer_absence(context, commande);
        break;

    case ETUDIANTS:
        calculer_etudiants_absents(commande, context);
        break;

	case JUSTIFICATIF:
		printf("Commande non implementee\n");
		break;

    case HELP:
        afficher_aide();
        break;

    case INCONNU:
        printf("Commande inconnue\n");
        break;

    default:
        printf("Commande non traitee\n");
        break;
    }
    return true;
}

/* Fonction qui inscrit un étudiant */
void inscrire_etudiant(Context* context, char commande[LONGUEUR_COMMANDE]) {

	// Récupère la gestion des absences
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);

	if (gestionAbsences->nombreEtudiants >= MAX_ETUDIANTS) {
		printf("Impossible d'inscrire un nouvel etudiant, le nombre maximum d'etudiants est atteint.\n");
		return;
	}

    char nom[LONGUEUR_NOM];
    int groupe = 0;

    lecture_nom_etudiant(commande, nom);
    lecture_groupe_etudiant(commande, &groupe);

    // Vérifie que l'étudiant n'existe pas déjà
    if (verifier_etudiant_existe(gestionAbsences, nom, groupe)) {
        printf("Nom incorrect\n");
        return;
    }

    // Crée l'étudiant
    Etudiant etudiant;
    etudiant.id = gestionAbsences->next_etudiant_id++;
    strcpy(etudiant.nom, nom);
    etudiant.groupe = groupe;
    etudiant.nombreAbsences = 0;

    // Ajoute l'étudiant à la liste
    gestionAbsences->etudiants[gestionAbsences->nombreEtudiants] = etudiant;
    gestionAbsences->nombreEtudiants++;

    printf("Inscription enregistree (%u)\n", etudiant.id);

}

/* Fonction qui permet de lire le nom de l'étudiant */
void lecture_nom_etudiant(char commande[LONGUEUR_COMMANDE], char nom[LONGUEUR_NOM]) {

    int i = 0;
    loop_to_space(commande, &i); /* Commande */

    lecture_string(commande, nom, LONGUEUR_NOM - 1, i); /* Nom */
    
}

/* Fonction qui permet de lire un nombre */
void lecture_nombre(char commande[LONGUEUR_COMMANDE], int* nombre, int i) {
    
    while (commande[i] != ' ' && commande[i] != '\0') {

        // Si le caractère est un chiffre
        if (commande[i] >= '0' && commande[i] <= '9') {

            // Conversion du caractère en entier '1' -> 1
            *nombre = *nombre * 10 + (commande[i] - '0');
            i++;
        }
        else {
            break;
        }
    }
}

/* Fonction qui permet de lire une chaine de caractères */
void lecture_string(char commande[LONGUEUR_COMMANDE], char string[LONGUEUR_COMMANDE], unsigned int string_len, int i) {
	int j = 0;

    /*  lecture de la chaine deux variable pour le decalage
            i : index de la commande, 
            j : index du string                              */
	while (commande[i] != ' ' && commande[i] != '\0' && j < string_len) {
		string[j] = commande[i];
		i++;
		j++;
	}
	string[j] = '\0';
}

/* Fonction qui permet de lire le groupe de l'étudiant */
void lecture_groupe_etudiant(char commande[LONGUEUR_COMMANDE], int* groupe) {

    int i = 0;
    loop_to_space(commande, &i); /* Commande */
    loop_to_space(commande, &i); /* Nom */

	lecture_nombre(commande, (unsigned int*)groupe, i);
}

/* Fonction qui vérifie si un étudiant existe */
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe) {
	// Parcourt la liste des étudiants
    for (unsigned int i = 0; i < gestionAbsences->nombreEtudiants; i++) {
        
		// Compare le nom et le groupe de l'étudiant
        if (strcmp(gestionAbsences->etudiants[i].nom, nom) == 0 && gestionAbsences->etudiants[i].groupe == groupe) {
            return true;
        }
    }
    return false;
}

/* Fonction pour trouver un étudiant par son ID */
Etudiant* trouver_etudiant_par_id(GestionAbsences* gestionAbsences, unsigned int id) {
	
    // Si l'id est dans la plage des étudiants
    if (id > 0 && id <= gestionAbsences->nombreEtudiants) {
        return &(gestionAbsences->etudiants[id - 1]);
    }
    return NULL;
}

/* Fonction qui enregistre une absence */
void enregistrer_absence(Context* context, char commande[LONGUEUR_COMMANDE]) {
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);
    if (gestionAbsences->nombreAbsences >= MAX_ABSENCES * MAX_ETUDIANTS) {
        printf("Nombre maximum d'absences atteint.\n");
        return;
    }

    unsigned int etudiant_id = 0;
    unsigned int Njour = 0;
    char demijournee[LONGUEUR_DEMI_JOURNEE];

    lecture_id_etudiant(commande, &etudiant_id);
    lecture_Njour_absence(commande, &Njour);
    lecture_demijournee_absence(commande, demijournee);

    Etudiant* etudiant = trouver_etudiant_par_id(gestionAbsences, etudiant_id);
    if (etudiant == NULL) {
        printf("Identifiant incorrect\n");
        return;
    }

    if (Njour < 1 || Njour > 40) {
        printf("Date incorrecte\n");
        return;
    }

    if (strcmp(demijournee, "am") != 0 && strcmp(demijournee, "pm") != 0) {
        printf("Demi-journee incorrecte\n");
        return;
    }

    if (verifier_absence_existe(gestionAbsences, etudiant_id, Njour, demijournee)) {
        printf("Absence deja connue\n");
        return;
    }

    // Crée l'absence
    Absence absence;
    absence.id = gestionAbsences->next_absence_id++;
    absence.Njour = Njour;
    strcpy(absence.demijournee, demijournee);

    // Ajoute l'absence à la liste globale
    gestionAbsences->absences[gestionAbsences->nombreAbsences] = absence;
    gestionAbsences->nombreAbsences++;

    // Ajoute l'id de l'absence à l'étudiant
    etudiant->absences_id[etudiant->nombreAbsences] = absence.id;
    etudiant->nombreAbsences++;

    printf("Absence enregistree [%u]\n", absence.id);
}

/* Fonction qui permet de lire l'id de l'étudiant */
void lecture_id_etudiant(char commande[LONGUEUR_COMMANDE], unsigned int* id) {
    int i = 0;
    loop_to_space(commande, &i); /* Commande */
    while (commande[i] == ' ' && commande[i] != '\0') {
        i++;
    }
	*id = 0; // Initialisation de l'id
    
	lecture_nombre(commande, id, i);
}

/* Fonction qui permet de lire le numéro de jour de l'absence */
void lecture_Njour_absence(char commande[LONGUEUR_COMMANDE], unsigned int* Njour) {
    int i = 0;
    loop_to_space(commande, &i); /* Commande */
    loop_to_space(commande, &i); /* Id */

    while (commande[i] == ' ' && commande[i] != '\0') {
        i++;
    }
	*Njour = 0; // Initialisation du Njour

	lecture_nombre(commande, Njour, i);
}

/* Fonction qui permet de lire la demi-journée de l'absence */
void lecture_demijournee_absence(char commande[LONGUEUR_COMMANDE], char demijournee[LONGUEUR_DEMI_JOURNEE]) {
    int i = 0;
    loop_to_space(commande, &i); /* Commande */
    loop_to_space(commande, &i); /* Id */
    loop_to_space(commande, &i); /* Njour */
    
	lecture_string(commande, demijournee, LONGUEUR_DEMI_JOURNEE - 1, i); /* Demi-journée */
}

/* Fonction qui vérifie si une absence existe */
bool verifier_absence_existe(GestionAbsences* gestionAbsences, unsigned int etudiant_id, unsigned int Njour, char demijournee[LONGUEUR_DEMI_JOURNEE]) {
    
    Etudiant* etudiant = trouver_etudiant_par_id(gestionAbsences, etudiant_id);
    if (etudiant == NULL) {
        return false;
    }

	// Parcourt la liste des absences de l'étudiant
    for (unsigned int i = 0; i < etudiant->nombreAbsences; i++) {

		// initialise l'absence et trouve l'absence par son id
        unsigned int absence_id = etudiant->absences_id[i];
        Absence* absence = trouver_absence_par_id(gestionAbsences, absence_id);

		// Si l'absence existe et que le jour et la demi-journée correspondent
        if (absence != NULL && absence->Njour == Njour && strcmp(absence->demijournee, demijournee) == 0) {
            return true;
        }
    }
    return false;
}

/* Fonction pour trouver une absence par son ID */
Absence* trouver_absence_par_id(GestionAbsences* gestionAbsences, unsigned int id) {

	// Si l'id est dans la list d'absences
	if (id > 0 && id <= gestionAbsences->nombreAbsences) {
		return &(gestionAbsences->absences[id - 1]);
	}
	return NULL;
}

/* Fonction qui affiche la liste des étudiants absents jusqu'à un jour donné */
void calculer_etudiants_absents(char commande[LONGUEUR_COMMANDE], Context* context) {

    GestionAbsences* gestionAbsences = &(context->gestionAbsences);
    if (gestionAbsences->nombreEtudiants == 0) {
        printf("Aucun inscrit\n");
        return;
    }

    int jour = 0;
    lecture_jour_absence(commande, &jour);
    if (jour < 1) {
        printf("Date incorrecte\n");
        return;
    }

    Etudiant etudiant_absents[MAX_ETUDIANTS];

    // Copie de la liste des étudiants
    for (unsigned int i = 0; i < gestionAbsences->nombreEtudiants; i++) {
        etudiant_absents[i] = gestionAbsences->etudiants[i];
    }

    // Tri des étudiants absents
    qsort(etudiant_absents, gestionAbsences->nombreEtudiants, sizeof(Etudiant), sort_etudiants_absents);

    // Affiche les étudiants absents
    afficher_etudiants_absents(gestionAbsences, etudiant_absents, gestionAbsences->nombreEtudiants, jour);
}

/* Fonction qui permet de lire le jour de l'absence */
void lecture_jour_absence(char commande[LONGUEUR_COMMANDE], int* jour) {
    
    int i = 0;
    loop_to_space(commande, &i); /* Commande */
    while (commande[i] == ' ' && commande[i] != '\0') {
        i++;
    }

    *jour = 0;
	lecture_nombre(commande, jour, i);
}

/* Fonction qui compte le nombre d'absence d'un étudiant avant un jour donné */
int compte_nombre_absence(GestionAbsences* gestionAbsences, Etudiant* etudiant, int jour) {

    int nombreAbsences = 0;
    
	// Parcourt la liste des absences de l'étudiant
    for (unsigned int i = 0; i < etudiant->nombreAbsences; i++) {

		// initialise l'absence et trouve l'absence par son id
        unsigned int absence_id = etudiant->absences_id[i];
        Absence* absence = trouver_absence_par_id(gestionAbsences, absence_id);

		// Si l'absence existe et que le jour est inférieur ou égal au jour donné
        if (absence != NULL && absence->Njour <= (unsigned int)jour) {
            nombreAbsences++;
        }
    }
    return nombreAbsences;
}

/* Fonction qui trie la liste des étudiants absents par groupe puis par nom */
int sort_etudiants_absents(const void* a, const void* b) {
    Etudiant* etudiant1 = (Etudiant*)a;
    Etudiant* etudiant2 = (Etudiant*)b;

    if (etudiant1->groupe != etudiant2->groupe) {
        return etudiant1->groupe - etudiant2->groupe;
    }
    else {
        return strcmp(etudiant1->nom, etudiant2->nom);
    }
}

/* Fonction qui affiche la liste des étudiants absents */
void afficher_etudiants_absents(GestionAbsences* gestionAbsences, Etudiant etudiant_absents[MAX_ETUDIANTS], int nombreEtudiantsAbsents, int jour) {

    // parcour la liste
    for (int i = 0; i < nombreEtudiantsAbsents; i++) {
        
        Etudiant* etudiant = &etudiant_absents[i];
		int nb_absences = compte_nombre_absence(gestionAbsences, etudiant, jour); // compte le nombre d'absences de l'étudiant jusqu'au jour donné
        
        printf("(%u) %s %u %u\n", etudiant->id, etudiant->nom, etudiant->groupe, nb_absences);
    }
}
