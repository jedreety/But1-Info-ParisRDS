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

	- loop_to_space : Permet de passer au mot suivant en donnant l'index ( renvoie l'index de la premiere lettre dans la commande du mot suivant )
	- lecture_nombre : Permet de lire un nombre
	- lecture_string : Permet de lire une chaine de caractères
	- read_data_int : Permet de lire un nombre en sautant un nombre de mots spécifiés
	- read_data_str : Permet de lire une chaine de caractères en sautant un nombre de mots spécifiés

	- verifier_etudiant_existe : Permet de vérifier si un étudiant existe ( renvoie un booléen )
	- trouver_etudiant_par_id : Permet de trouver un étudiant par son ID ( renvoie un pointeur sur l'étudiant )

	- verifier_absence_existe : Permet de vérifier si une absence existe ( renvoie un booléen )
	- trouver_absence_par_id : Permet de trouver une absence par son ID ( renvoie un pointeur sur l'absence )

	!!! 
        Les fonctions trouver_etudiant_par_id et trouver_absence_par_id sont implementées de sorte a ce que les IDs dans la list ID sont attribués séquentiellement et sans suppression
        Si une fonction supprime un étudiant ou une absence, il faudra adapter ces fonctions (remplacer l'ID par NULL ou changer la fonction par une recherche linéaire).
    !!!

	... quelques autres fonctions utiles sont disponibles mais ne sont pas mentionnées ici.

*/

typedef enum /* bool */ {

    false = 0,
    true = 1,
} bool;

enum /* Constantes */ {
    MAX_ABSENCES = 100,
    MAX_ETUDIANTS = 100,

    LONGUEUR_COMMANDE = 100 + 1,
    LONGUEUR_DEMI_JOURNEE = 2 + 1,
    LONGUEUR_NOM = 30 + 1,
    LONGUEUR_JUSTIFICATIF = 50 + 1,
    LONGUEUR_AFFICHAGE = 50 + 1
};

typedef char STR_Commande[LONGUEUR_COMMANDE];
typedef void (*ParametresFunction)();

const STR_Commande liste_commande[] = {

    "exit",
    "inscription",
    "absence",
    "etudiants",
    "justificatif",
    "validations",
    "validation",
    "etudiant",
    "defaillants",
    "help"
};
const unsigned int nb_commande = sizeof(liste_commande) / sizeof(liste_commande[0]);

typedef enum /* INT_Commande */ {

    EXIT = 0,
    INSCRIPTION,
    ABSENCE,
    ETUDIANTS,
	JUSTIFICATIF,
    VALIDATIONS,
    VALIDATION,
    ETUDIANT,
    DEFAILLANTS,
    HELP,
    INCONNU
} INT_Commande;

typedef enum /* ETAT_Absence */ {

    EN_ATTENTE,     
    EN_COURS,       
    NON_JUSTIFIEE,  
    JUSTIFIEE       
} ETAT_Absence;

typedef struct /* Justificatif */ {

    ETAT_Absence etat;                        
    char justificatif[LONGUEUR_JUSTIFICATIF];
    unsigned int jour_justificatif;
} Justificatif;

typedef struct /* Absence */ {

    unsigned int id;

    unsigned int Njour;
    char demijournee[LONGUEUR_DEMI_JOURNEE];
    Justificatif justificatif;

    unsigned int etudiant_id;
} Absence;

typedef struct /* Etudiant */ {

    unsigned int id;

    char nom[LONGUEUR_NOM];
    int groupe;

	// liste et nombre d'absences de l'étudiant
    unsigned int absences_id[MAX_ABSENCES];
    unsigned int nombreAbsences;
} Etudiant;

typedef struct /* EtudiantDefaillant */ {

    Etudiant* etudiant;
    int total_absences;
} EtudiantDefaillant;

typedef struct /* GestionAbsences */ {

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

typedef struct /* Affichage */ { // Pas très utile mais je voulais faire quelque chose de different ¯\_(ツ)_/¯

    char welcome_message[LONGUEUR_AFFICHAGE]; // Message afficher au debut du programme
    char exit_message[LONGUEUR_AFFICHAGE]; // Message afficher a la fin du programme

    char left_deco[LONGUEUR_AFFICHAGE]; // A la toute gauche premiere chose print dehors du n commande
    char sep_prompt_deco[LONGUEUR_AFFICHAGE]; // une fois la commande fini il fait la separation entre deux commande

    char start_prompt[LONGUEUR_AFFICHAGE]; // avant que l'utilisateur entre la commande
    char start_return_prompt[LONGUEUR_AFFICHAGE]; // entre la reponse et l'entré

} Affichage;

typedef struct /* Context */ {

    unsigned int id;

    GestionAbsences gestionAbsences;
    unsigned int nombreCommandes;

    Affichage affichage;
} Context;

typedef struct /* AideCommande */ {

    char* nom;
    char* syntaxe;
    char* description;
    ParametresFunction afficher_parametres;
} AideCommande;


/* C0 | Fonctions de lecture et d'exécution des commandes */
INT_Commande lire_commande(char commande[LONGUEUR_COMMANDE]);
bool executer_commande(Context* context, char commande[LONGUEUR_COMMANDE]);

/* C1 | Fonctions pour l'inscription des étudiants */
void inscrire_etudiant(Context* context, char commande[LONGUEUR_COMMANDE]);

/* C2 | Fonctions pour l'a gestion'enregistrement des absences */
void enregistrer_absence(Context* context, char commande[LONGUEUR_COMMANDE]);

/* C3 | Fonctions pour la liste des étudiants */
int compte_nombre_absence(GestionAbsences* gestionAbsences, Etudiant* etudiant, int jour);
void afficher_etudiants_absents(GestionAbsences* gestionAbsences, Etudiant etudiant_absents[MAX_ETUDIANTS], int nombreEtudiantsAbsents, int jour);

/* C4 | Fonctions de dêpot de justificatif */
void enregistrer_justificatif(Context* context, char commande[LONGUEUR_COMMANDE]);
void mettre_a_jour_etat_absence(Justificatif* justificatif, unsigned int absence_Njour, unsigned int jour_submission);

/* C5 | Fonctions pour la liste des absences en attente de validation */
void afficher_validations(Context* context);

/* C6 | Validation/invalidation d’un justificatif */
void valider_justificatif(Context* context, char commande[LONGUEUR_COMMANDE]);

/* C7 | Fonctions pour la situation d’un étudiant */
void afficher_situation_etudiant(Context* context, char commande[LONGUEUR_COMMANDE]);
void afficher_absences(const char* titre, Absence* absences[], int nb_absences, bool afficher_justificatif, unsigned int jour_courant);
void traiter_absence_sans_justificatif(
    Absence* absence,
    unsigned int jour_courant,
    Absence* absences_en_attente_justificatif[], int* nb_attente_justificatif,
    Absence* absences_non_justifiees[], int* nb_non_justifiees
);

/* C8 | Fonctions pour la liste des étudiants d´efaillants */
void afficher_defaillants(Context* context, char commande[LONGUEUR_COMMANDE]);

/* Fonction de tri */
int sort_etudiants_absents(const void* a, const void* b);
int comparer_absences_C5(const void* a, const void* b);
int comparer_absences_C7(const void* a, const void* b);
int comparer_etudiants_defaillants(const void* a, const void* b);

/* Fonction de recherche */
Etudiant* trouver_etudiant_par_id(GestionAbsences* gestionAbsences, unsigned int id);
Absence* trouver_absence_par_id(GestionAbsences* gestionAbsences, unsigned int id);
void calculer_etudiants_absents(Context* context, char commande[LONGUEUR_COMMANDE]);
void categoriser_absences_etudiant(
    Etudiant* etudiant,
    GestionAbsences* gestionAbsences,
    unsigned int jour_courant,
    Absence* absences_en_attente_justificatif[], int* nb_attente_justificatif,
    Absence* absences_en_attente_validation[], int* nb_attente_validation,
    Absence* absences_justifiees[], int* nb_justifiees,
    Absence* absences_non_justifiees[], int* nb_non_justifiees
);

/* Lecture de commande */
void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE]);
void loop_to_space(char commande[LONGUEUR_COMMANDE], int* i);
void lecture_nombre(char commande[LONGUEUR_COMMANDE], int* nombre, int i);
void lecture_string(char commande[LONGUEUR_COMMANDE], char string[LONGUEUR_COMMANDE], unsigned int string_len, int i);
void read_data_int(char commande[LONGUEUR_COMMANDE], int* value, int skip_words);
void read_data_str(char commande[LONGUEUR_COMMANDE], char str[], unsigned int max_length, int skip_words);

/* Fonction de Verification */
bool verifier_etudiant_id(GestionAbsences* gestionAbsences, unsigned int etudiant_id);
bool verifier_absence_id(GestionAbsences* gestionAbsences, unsigned int absence_id);
bool verifier_date(int Njour);
bool verifier_demijournee(char demijournee[]);
bool verifier_code_validation(char code[]);
bool verifier_etudiant_existe_pas(GestionAbsences* gestionAbsences, char nom[], int groupe);
bool verifier_justificatif_existe(Justificatif* justificatif);
bool verifier_date_justificatif(Absence* absence, unsigned int jour_submission);
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe);
bool verifier_absence_existe(GestionAbsences* gestionAbsences, unsigned int etudiant_id, unsigned int Njour, char demijournee[LONGUEUR_DEMI_JOURNEE]);
bool afficher_justificatif(Absence* absence, unsigned int jour_courant);

/* Fonction Externe */
void afficher_aide();
void afficher_parametres_inscription();
void afficher_parametres_absence();
void afficher_parametres_justificatif();
void afficher_parametres_etudiants();
void afficher_parametres_validation();
void afficher_parametres_etudiant();
void afficher_parametres_defaillants();
const AideCommande aides[] = {
    {"exit", "exit", "Quitter l'application.", NULL},
    {"inscription", "inscription <nom> <groupe>", "Inscrire un etudiant.", afficher_parametres_inscription},
    {"absence", "absence <id> <Njour> <demijournee>", "Enregistrer une absence pour un etudiant.", afficher_parametres_absence},
    {"etudiants", "etudiants <jour>", "Afficher la liste des etudiants inscrits avec leur nombre total d'absences jusqu'au jour donne.", afficher_parametres_etudiants},
    {"justificatif", "justificatif <id> <Njour> <justificatif>", "Deposer un justificatif pour une absence.", afficher_parametres_justificatif},
    {"validations", "validations", "Afficher la liste des absences en attente de validation.", NULL},
    {"validation", "validation <id> <code>", "Valider ou invalider un justificatif.", afficher_parametres_validation},
    {"etudiant", "etudiant <id> <jour>", "Afficher la situation d'un etudiant.", afficher_parametres_etudiant},
    {"defaillants", "defaillants <jour>", "Afficher la liste des etudiants defaillants.", afficher_parametres_defaillants},
    {"help", "help", "Afficher l'aide.", NULL}
};

/* Fonction du Context */
void init_context(Context* context, unsigned int context_id) {
    context->id = context_id;

	context->nombreCommandes = 0;

	context->gestionAbsences.next_etudiant_id = 1;
	context->gestionAbsences.next_absence_id = 1;
	context->gestionAbsences.nombreEtudiants = 0;
	context->gestionAbsences.nombreAbsences = 0;

    strncpy(context->affichage.welcome_message, "Interface sur la gestion d'absences.", LONGUEUR_AFFICHAGE - 1);
    context->affichage.welcome_message[LONGUEUR_AFFICHAGE - 1] = '\0';

    strncpy(context->affichage.left_deco, "", LONGUEUR_AFFICHAGE - 1);
    context->affichage.left_deco[LONGUEUR_AFFICHAGE - 1] = '\0';

    strncpy(context->affichage.sep_prompt_deco, "", LONGUEUR_AFFICHAGE - 1);
    context->affichage.sep_prompt_deco[LONGUEUR_AFFICHAGE - 1] = '\0';

    strncpy(context->affichage.start_prompt, "", LONGUEUR_AFFICHAGE - 1);
    context->affichage.start_prompt[LONGUEUR_AFFICHAGE - 1] = '\0';

    strncpy(context->affichage.start_return_prompt, "", LONGUEUR_AFFICHAGE - 1);
    context->affichage.start_return_prompt[LONGUEUR_AFFICHAGE - 1] = '\0';

    strncpy(context->affichage.exit_message, "", LONGUEUR_AFFICHAGE - 1);
    context->affichage.exit_message[LONGUEUR_AFFICHAGE - 1] = '\0';
}
void context_loop(Context* context) {

	char commande[LONGUEUR_COMMANDE];
    Affichage* affichage = &(context->affichage);

	printf("%s\n\n", affichage->welcome_message);

    while (true) {

		context->nombreCommandes++;

        printf("%u%s %s ", context->nombreCommandes, affichage->left_deco, affichage->start_prompt);

        if (scanf(" %[^\n]%*c", commande) != 1) {
			printf("Input error : Erreur lors de la lecture de la commande.\n");
			return;
		}
        else {
			commande[LONGUEUR_COMMANDE - 1] = '\0';
		}

        printf("  %s %s \n", affichage->left_deco, affichage->start_return_prompt);
        if (!executer_commande(context, commande)) {
			break;
		}

        printf("%s\n", affichage->sep_prompt_deco);
	}
	printf("%s", affichage->exit_message);
}


int main() {

    // Initialisation du contexte
    Context context;
	init_context(&context, 1);
    
	// Lancement de l'application
	context_loop(&context);

    return 0;
}


/* ----- C0 ----- */
/* renvoie un numéro correspondant à la commande */
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
        return false;

    case INSCRIPTION:
        inscrire_etudiant(context, commande);
        break;

    case ABSENCE:
        enregistrer_absence(context, commande);
        break;

    case ETUDIANTS:
        calculer_etudiants_absents(context, commande);
        break;

    case JUSTIFICATIF:
        enregistrer_justificatif(context, commande);
        break;

    case VALIDATIONS:
        afficher_validations(context);
        break;

    case VALIDATION:
        valider_justificatif(context, commande);
        break;

    case ETUDIANT:
        afficher_situation_etudiant(context, commande);
        break;

    case DEFAILLANTS:
        afficher_defaillants(context, commande);
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


/* ----- C1 ----- */
/* inscrit un étudiant */
void inscrire_etudiant(Context* context, char commande[LONGUEUR_COMMANDE]) {

    // Récupère la gestion des absences
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);

    if (gestionAbsences->nombreEtudiants >= MAX_ETUDIANTS) {
        printf("Impossible d'inscrire un nouvel etudiant, le nombre maximum d'etudiants est atteint.\n");
        return;
    }

    char nom[LONGUEUR_NOM];
    int groupe = 0;

    read_data_str(commande, nom, LONGUEUR_NOM - 1, 1);
    read_data_int(commande, &groupe, 2);

    // Vérifie que l'étudiant n'existe pas déjà
    if (!verifier_etudiant_existe_pas(gestionAbsences, nom, groupe)) {
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


/* ----- C2 ----- */
/* enregistre une absence */
void enregistrer_absence(Context* context, char commande[LONGUEUR_COMMANDE]) {
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);
    if (gestionAbsences->nombreAbsences >= MAX_ABSENCES * MAX_ETUDIANTS) {
        printf("Nombre maximum d'absences atteint.\n");
        return;
    }

    unsigned int etudiant_id = 0;
    unsigned int Njour = 0;
    char demijournee[LONGUEUR_DEMI_JOURNEE];

    read_data_int(commande, (int*)&etudiant_id, 1);
    read_data_int(commande, (int*)&Njour, 2);
    read_data_str(commande, demijournee, LONGUEUR_DEMI_JOURNEE - 1, 3);

    if (!verifier_etudiant_id(gestionAbsences, etudiant_id)) {
        return;
    }

    if (!verifier_date(Njour)) {
        return;
    }

    if (!verifier_demijournee(demijournee)) {
        return;
    }

    if (verifier_absence_existe(gestionAbsences, etudiant_id, Njour, demijournee))
    {
        printf("Absence deja connue\n");
        return;
    }

    Etudiant* etudiant = trouver_etudiant_par_id(gestionAbsences, etudiant_id);

    // Crée le justificatif
    Justificatif justificatif;
    justificatif.etat = EN_ATTENTE;
    justificatif.justificatif[0] = '\0'; // Chaîne vide
    justificatif.jour_justificatif = 0;  // Pas de jour de justificatif

    // Crée l'absence
    Absence absence;
    absence.id = gestionAbsences->next_absence_id++;
    absence.etudiant_id = etudiant->id;
    absence.Njour = Njour;
    strcpy(absence.demijournee, demijournee);
    absence.justificatif = justificatif;

    // Ajoute l'absence à la liste globale
    gestionAbsences->absences[gestionAbsences->nombreAbsences] = absence;
    gestionAbsences->nombreAbsences++;

    // Ajoute l'id de l'absence à l'étudiant
    etudiant->absences_id[etudiant->nombreAbsences] = absence.id;
    etudiant->nombreAbsences++;

    printf("Absence enregistree [%u]\n", absence.id);
}


/* ----- C3 ----- */
/* affiche la liste des étudiants absents jusqu'à un jour donné */
void calculer_etudiants_absents(Context* context, char commande[LONGUEUR_COMMANDE]) {

    GestionAbsences* gestionAbsences = &(context->gestionAbsences);
    if (gestionAbsences->nombreEtudiants == 0) {
        printf("Aucun inscrit\n");
        return;
    }

    int jour = 0;
    read_data_int(commande, &jour, 1);

    if (!verifier_date(jour)) {
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
/* affiche la liste des étudiants absents */
void afficher_etudiants_absents(GestionAbsences* gestionAbsences, Etudiant etudiant_absents[MAX_ETUDIANTS], int nombreEtudiantsAbsents, int jour) {

    // parcour la liste
    for (int i = 0; i < nombreEtudiantsAbsents; i++) {

        Etudiant* etudiant = &etudiant_absents[i];
        int nb_absences = compte_nombre_absence(gestionAbsences, etudiant, jour); // compte le nombre d'absences de l'étudiant jusqu'au jour donné

        printf("(%u) %s %u %u\n", etudiant->id, etudiant->nom, etudiant->groupe, nb_absences);
    }
}


/* ----- C4 ----- */
/* enregistre un justificatif */
void enregistrer_justificatif(Context* context, char commande[LONGUEUR_COMMANDE]) {
    
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);

    // Initialise les données
    unsigned int absence_id = 0;
    unsigned int jour_justificatif = 0;
    char texte_justificatif[LONGUEUR_JUSTIFICATIF];

    // On récupere les données
    read_data_int(commande, (int*)&absence_id, 1);
    read_data_int(commande, (int*)&jour_justificatif, 2);
    read_data_str(commande, texte_justificatif, LONGUEUR_JUSTIFICATIF - 1, 3);

    // On recupere l'absence qui nous interesse
    if (!verifier_absence_id(gestionAbsences, absence_id)) {
        return;
    }

    Absence* absence = trouver_absence_par_id(gestionAbsences, absence_id);

    if (!verifier_date_justificatif(absence, jour_justificatif)) {
        printf("Date incorrecte\n");
        return;
    }

    if (verifier_justificatif_existe(&(absence->justificatif))) {
        printf("Justificatif deja connu\n");
        return;
    }

    // Enregistrement du justificatif
    strcpy(absence->justificatif.justificatif, texte_justificatif);
    absence->justificatif.jour_justificatif = jour_justificatif;

    mettre_a_jour_etat_absence(&(absence->justificatif), absence->Njour, jour_justificatif);

    printf("Justificatif enregistre\n");
}
/* met a jour l'etat d'un justificatif */
void mettre_a_jour_etat_absence(Justificatif* justificatif, unsigned int absence_Njour, unsigned int jour_submission) {
    if (jour_submission <= absence_Njour + 3) {
        justificatif->etat = EN_COURS;
    }
    else {
        justificatif->etat = NON_JUSTIFIEE;
    }
}


/* ----- C5 ----- */
/* affiche la liste des absences en attente de validation */
void afficher_validations(Context* context) {
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);

    // Tableau pour stocker les pointeurs vers les absences en attente de validation
    Absence* absences_en_attente[MAX_ABSENCES * MAX_ETUDIANTS];
    int nombreAbsencesEnAttente = 0;

    // Parcours de toutes les absences
    for (unsigned int i = 0; i < gestionAbsences->nombreAbsences; i++) {
        Absence* absence = &(gestionAbsences->absences[i]);

        // Vérification si le justificatif est en cours de validation
        if (absence->justificatif.etat == EN_COURS) {
            absences_en_attente[nombreAbsencesEnAttente] = absence;
            nombreAbsencesEnAttente++;
        }
    }

    if (nombreAbsencesEnAttente == 0) {
        printf("Aucune validation en attente\n");
        return;
    }

    // Tri des absences en attente
    qsort(absences_en_attente, nombreAbsencesEnAttente, sizeof(Absence*), comparer_absences_C5);

    // Affichage des absences en attente
    for (int i = 0; i < nombreAbsencesEnAttente; i++) {
        Absence* absence = absences_en_attente[i];

        // Récupération de l'étudiant
        Etudiant* etudiant = trouver_etudiant_par_id(gestionAbsences, absence->etudiant_id);
        if (etudiant == NULL) {
            printf("Etudiant introuvable pour l'absence %d\n", absence->id);
            continue; // Ne devrait pas se produire
        }

        // Affichage des informations
        printf("[%u] (%u) %s %d %u/%s (%s)\n",
            absence->id,
            etudiant->id,
            etudiant->nom,
            etudiant->groupe,
            absence->Njour,
            absence->demijournee,
            absence->justificatif.justificatif);
    }
}


/* ----- C6 ----- */
/* valide ou invalide un justificatif */
void valider_justificatif(Context* context, char commande[LONGUEUR_COMMANDE]) {
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);

    unsigned int absence_id = 0;
    char code[3]; // Pour stocker "ok" ou "ko"

    // Lecture des paramètres
    read_data_int(commande, (int*)&absence_id, 1);
    read_data_str(commande, code, 2, 2);

    // Vérification du code de validation
    if (!verifier_code_validation(code)) {
        return;
    }

    if (!verifier_absence_id(gestionAbsences, absence_id)) {
        return;
    }

    Absence* absence = trouver_absence_par_id(gestionAbsences, absence_id);

    // Vérification de l'état du justificatif
    if (absence->justificatif.etat == EN_COURS) {
        // On peut procéder à la validation
    }
    else if (absence->justificatif.etat == JUSTIFIEE || absence->justificatif.etat == NON_JUSTIFIEE) {
        printf("Validation deja connue\n");
        return;
    }
    else {
        printf("Identifiant incorrect\n");
        return;
    }

    // Mise à jour de l'état du justificatif
    if (strcmp(code, "ok") == 0) {
        absence->justificatif.etat = JUSTIFIEE;
    }
    else {
        absence->justificatif.etat = NON_JUSTIFIEE;
    }

    printf("Validation enregistree\n");
}


/* ----- C7 ----- */
/* affiche la situation d'un étudiant */
void afficher_situation_etudiant(Context* context, char commande[LONGUEUR_COMMANDE]) {
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);

    unsigned int etudiant_id = 0;
    int jour_courant = 0;

    // Lecture des paramètres
    read_data_int(commande, (int*)&etudiant_id, 1);
    read_data_int(commande, &jour_courant, 2);

    // Vérification des paramètres
    if (!verifier_date(jour_courant)) {
        return;
    }

    if (!verifier_etudiant_id(gestionAbsences, etudiant_id)) {
        return;
    }

    Etudiant* etudiant = trouver_etudiant_par_id(gestionAbsences, etudiant_id);

    // Affichage des informations de l'étudiant
    int total_absences = compte_nombre_absence(gestionAbsences, etudiant, jour_courant);
    printf("(%u) %s %d %d\n", etudiant->id, etudiant->nom, etudiant->groupe, total_absences);

    // Catégorisation des absences
    Absence* absences_en_attente_justificatif[MAX_ABSENCES];
    int nb_attente_justificatif = 0;

    Absence* absences_en_attente_validation[MAX_ABSENCES];
    int nb_attente_validation = 0;

    Absence* absences_justifiees[MAX_ABSENCES];
    int nb_justifiees = 0;

    Absence* absences_non_justifiees[MAX_ABSENCES];
    int nb_non_justifiees = 0;

    // Appel à la fonction de catégorisation
    categoriser_absences_etudiant(
        etudiant,
        gestionAbsences,
        (unsigned int)jour_courant,
        absences_en_attente_justificatif, &nb_attente_justificatif,
        absences_en_attente_validation, &nb_attente_validation,
        absences_justifiees, &nb_justifiees,
        absences_non_justifiees, &nb_non_justifiees
    );

    // Tri des absences dans chaque catégorie
    qsort(absences_en_attente_justificatif, nb_attente_justificatif, sizeof(Absence*), comparer_absences_C7);
    qsort(absences_en_attente_validation, nb_attente_validation, sizeof(Absence*), comparer_absences_C7);
    qsort(absences_justifiees, nb_justifiees, sizeof(Absence*), comparer_absences_C7);
    qsort(absences_non_justifiees, nb_non_justifiees, sizeof(Absence*), comparer_absences_C7);

    // Utilisation de la fonction afficher_absences
    afficher_absences("En attente justificatif", absences_en_attente_justificatif, nb_attente_justificatif, false, (unsigned int)jour_courant);
    afficher_absences("En attente validation", absences_en_attente_validation, nb_attente_validation, true, (unsigned int)jour_courant);
    afficher_absences("Justifiees", absences_justifiees, nb_justifiees, true, (unsigned int)jour_courant);
    afficher_absences("Non-justifiees", absences_non_justifiees, nb_non_justifiees, true, (unsigned int)jour_courant);
}
/* affiche le justificatif d'une absence */
void afficher_absences(const char* titre, Absence* absences[], int nb_absences, bool afficher_justificatif, unsigned int jour_courant) {
    if (nb_absences > 0) {
        printf("- %s\n", titre);
        for (int i = 0; i < nb_absences; i++) {
            Absence* absence = absences[i];
            if (afficher_justificatif && absence->justificatif.justificatif[0] != '\0' && absence->justificatif.jour_justificatif <= jour_courant) {
                printf("  [%u] %u/%s (%s)\n", absence->id, absence->Njour, absence->demijournee, absence->justificatif.justificatif);
            }
            else {
                printf("  [%u] %u/%s\n", absence->id, absence->Njour, absence->demijournee);
            }
        }
    }
}


/* ----- C8 ----- */
/* affiche la liste des étudiants défaillants */
void afficher_defaillants(Context* context, char commande[LONGUEUR_COMMANDE]) {
    GestionAbsences* gestionAbsences = &(context->gestionAbsences);
    int jour_courant = 0;

    // Lecture du jour courant
    read_data_int(commande, &jour_courant, 1);

    // Vérification du jour courant
    if (!verifier_date(jour_courant)) {
        return;
    }

    // Liste des étudiants défaillants
    typedef struct {
        Etudiant* etudiant;
        int total_absences;
    } EtudiantDefaillant;

    EtudiantDefaillant defaillants[MAX_ETUDIANTS];
    int nb_defaillants = 0;

    // Parcours des étudiants
    for (unsigned int i = 0; i < gestionAbsences->nombreEtudiants; i++) {
        Etudiant* etudiant = &(gestionAbsences->etudiants[i]);

        // Calcul du nombre d'absences non justifiées et total d'absences pour l'étudiant jusqu'au jour courant
        int nb_absences_non_justifiees = 0;
        int total_absences = 0;

        for (unsigned int j = 0; j < etudiant->nombreAbsences; j++) {
            unsigned int absence_id = etudiant->absences_id[j];
            Absence* absence = trouver_absence_par_id(gestionAbsences, absence_id);

            if (absence != NULL && absence->Njour <= (unsigned int)jour_courant) {
                total_absences++;

                // Vérifier l'état de l'absence
                ETAT_Absence etat = absence->justificatif.etat;

                if (etat == EN_ATTENTE) {
                    // Si le délai de dépôt du justificatif est dépassé
                    if ((unsigned int)jour_courant > absence->Njour + 3) {
                        nb_absences_non_justifiees++;
                    }
                }
                else if (etat == EN_COURS) {
                    // En attente de validation, on ne compte pas comme non justifiée
                }
                else if (etat == NON_JUSTIFIEE) {
                    nb_absences_non_justifiees++;
                }
                // Les absences justifiées ne sont pas comptées comme non justifiées
            }
        }

        // Si l'étudiant a 5 absences non justifiées ou plus, l'ajouter à la liste des défaillants
        if (nb_absences_non_justifiees >= 5) {
            defaillants[nb_defaillants].etudiant = etudiant;
            defaillants[nb_defaillants].total_absences = total_absences;
            nb_defaillants++;
        }
    }

    // Si aucun défaillant n'a été trouvé
    if (nb_defaillants == 0) {
        printf("Aucun defaillant\n");
        return;
    }

    // Trier la liste des défaillants
    qsort(defaillants, nb_defaillants, sizeof(EtudiantDefaillant), comparer_etudiants_defaillants);

    // Afficher la liste des défaillants
    for (int i = 0; i < nb_defaillants; i++) {
        Etudiant* etudiant = defaillants[i].etudiant;
        int total_absences = defaillants[i].total_absences;
        printf("(%u) %s %d %d\n", etudiant->id, etudiant->nom, etudiant->groupe, total_absences);
    }
}


/* ----- Tri ----- */
/* trie la liste des étudiants absents par groupe puis par nom */
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
/* tri des absences */
int comparer_absences_C5(const void* a, const void* b) {
    Absence* absence1 = *(Absence**)a;
    Absence* absence2 = *(Absence**)b;

    // Comparaison par ID d'étudiant
    if (absence1->etudiant_id != absence2->etudiant_id) {
        return (int)(absence1->etudiant_id - absence2->etudiant_id);
    }
    else {
        // Pour le même étudiant, comparaison par date
        if (absence1->Njour != absence2->Njour) {
            return (int)(absence1->Njour - absence2->Njour);
        }
        else {
            // Comparaison par demi-journée
            return strcmp(absence1->demijournee, absence2->demijournee);
        }
    }
}
/* tri des absences */
int comparer_absences_C7(const void* a, const void* b) {
    Absence* absence1 = *(Absence**)a;
    Absence* absence2 = *(Absence**)b;

    // Comparaison par date
    if (absence1->Njour != absence2->Njour) {
        return (int)(absence1->Njour - absence2->Njour);
    }
    else {
        // Comparaison par demi-journée
        return strcmp(absence1->demijournee, absence2->demijournee);
    }
}
/* tri des étudiants défaillants */
int comparer_etudiants_defaillants(const void* a, const void* b) {
    Etudiant* etudiant1 = ((EtudiantDefaillant*)a)->etudiant;
    Etudiant* etudiant2 = ((EtudiantDefaillant*)b)->etudiant;

    if (etudiant1->groupe != etudiant2->groupe) {
        return etudiant1->groupe - etudiant2->groupe;
    }
    else {
        return strcmp(etudiant1->nom, etudiant2->nom);
    }
}


/* ----- Recherche ----- */
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
/* Fonction qui categorise les absence d'un etudiant */
void categoriser_absences_etudiant(
    Etudiant* etudiant,
    GestionAbsences* gestionAbsences,
    unsigned int jour_courant,
    Absence* absences_en_attente_justificatif[], int* nb_attente_justificatif,
    Absence* absences_en_attente_validation[], int* nb_attente_validation,
    Absence* absences_justifiees[], int* nb_justifiees,
    Absence* absences_non_justifiees[], int* nb_non_justifiees
) {
    // Parcours des absences de l'étudiant
    for (unsigned int i = 0; i < etudiant->nombreAbsences; i++) {
        unsigned int absence_id = etudiant->absences_id[i];
        Absence* absence = trouver_absence_par_id(gestionAbsences, absence_id);

        // Ne considérer que les absences avant ou égales au jour courant
        if (absence != NULL && absence->Njour <= jour_courant) {
            // Déterminer le statut de l'absence
            ETAT_Absence etat = absence->justificatif.etat;

            // Vérifier si un justificatif a été déposé avant ou au jour courant
            bool justificatif_depose = absence->justificatif.justificatif[0] != '\0' && absence->justificatif.jour_justificatif <= jour_courant;

            switch (etat)
            {
            case EN_ATTENTE:
                // Vérifier si le délai de dépôt de justificatif n'est pas expiré
                if (jour_courant <= absence->Njour + 3) {
                    absences_en_attente_justificatif[(*nb_attente_justificatif)++] = absence;
                }
                else {
                    // Délai expiré, absence non justifiée
                    absences_non_justifiees[(*nb_non_justifiees)++] = absence;
                }
                break;

            case EN_COURS:
                if (justificatif_depose) {
                    absences_en_attente_validation[(*nb_attente_validation)++] = absence;
                }
                else {
                    // Appel à la fonction pour traiter l'absence sans justificatif
                    traiter_absence_sans_justificatif(
                        absence,
                        jour_courant,
                        absences_en_attente_justificatif, nb_attente_justificatif,
                        absences_non_justifiees, nb_non_justifiees
                    );
                }
                break;

            case JUSTIFIEE:
                if (justificatif_depose) {
                    absences_justifiees[(*nb_justifiees)++] = absence;
                }
                else {
                    // Appel à la fonction pour traiter l'absence sans justificatif
                    traiter_absence_sans_justificatif(
                        absence,
                        jour_courant,
                        absences_en_attente_justificatif, nb_attente_justificatif,
                        absences_non_justifiees, nb_non_justifiees
                    );
                }
                break;

            case NON_JUSTIFIEE:
                if (justificatif_depose) {
                    absences_non_justifiees[(*nb_non_justifiees)++] = absence;
                }
                else {
                    // Appel à la fonction pour traiter l'absence sans justificatif
                    traiter_absence_sans_justificatif(
                        absence,
                        jour_courant,
                        absences_en_attente_justificatif, nb_attente_justificatif,
                        absences_non_justifiees, nb_non_justifiees
                    );
                }
                break;

            default:
                break;
            }
        }
    }
}


/* ----- Lecture de Commande ----- */
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
    unsigned int j = 0;

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
/* Fonction qui permet de lire une donnée Int de la commande */
void read_data_int(char commande[LONGUEUR_COMMANDE], int* value, int skip_words) {
    int i = 0;
    // Sauter les mots spécifiés
    for (int w = 0; w < skip_words; w++) {
        loop_to_space(commande, &i);
    }
    // Sauter les espaces supplémentaires
    while (commande[i] == ' ' && commande[i] != '\0') {
        i++;
    }
    *value = 0; // Initialisation de la valeur
    lecture_nombre(commande, value, i);
}
/* Fonction qui permet de lire une donnée String de la commande */
void read_data_str(char commande[LONGUEUR_COMMANDE], char str[], unsigned int max_length, int skip_words) {
    int i = 0;
    // Sauter les mots spécifiés
    for (int w = 0; w < skip_words; w++) {
        loop_to_space(commande, &i);
    }
    // Sauter les espaces supplémentaires
    while (commande[i] == ' ' && commande[i] != '\0') {
        i++;
    }
    // Lire la chaîne de caractères
    lecture_string(commande, str, max_length, i);
}


/* ----- vérification des paramètres ----- */
bool verifier_etudiant_id(GestionAbsences* gestionAbsences, unsigned int etudiant_id) {
    if (trouver_etudiant_par_id(gestionAbsences, etudiant_id) == NULL) {
        printf("Identifiant incorrect\n");
        return false;
    }
    return true;
}
bool verifier_absence_id(GestionAbsences* gestionAbsences, unsigned int absence_id) {
    if (trouver_absence_par_id(gestionAbsences, absence_id) == NULL) {
        printf("Identifiant incorrect\n");
        return false;
    }
    return true;
}
bool verifier_date(int Njour) {
    if (Njour < 1 || Njour > 40) {
        printf("Date incorrecte\n");
        return false;
    }
    return true;
}
bool verifier_demijournee(char demijournee[]) {
    if (strcmp(demijournee, "am") != 0 && strcmp(demijournee, "pm") != 0) {
        printf("Demi-journee incorrecte\n");
        return false;
    }
    return true;
}
bool verifier_code_validation(char code[]) {
    if (strcmp(code, "ok") != 0 && strcmp(code, "ko") != 0) {
        printf("Code incorrect\n");
        return false;
    }
    return true;
}
bool verifier_etudiant_existe_pas(GestionAbsences* gestionAbsences, char nom[], int groupe) {
    if (verifier_etudiant_existe(gestionAbsences, nom, groupe)) {
        printf("Nom incorrect\n");
        return false;
    }
    return true;
}
bool verifier_justificatif_existe(Justificatif* justificatif) {
    return justificatif->justificatif[0] != '\0';
}
bool verifier_date_justificatif(Absence* absence, unsigned int jour_submission) {
    return jour_submission >= absence->Njour;
}
bool afficher_justificatif(Absence* absence, unsigned int jour_courant) {
    return absence->justificatif.justificatif[0] != '\0' && absence->justificatif.jour_justificatif <= jour_courant;
}


/* ----- Externe ----- */
/* Fonction qui affiche l'aide */
void afficher_aide() {
    printf("  |\n  | Liste des commandes :\n  | \n");
    for (unsigned int i = 0; i < sizeof(aides) / sizeof(AideCommande); i++) {
        printf("  | %s\n", aides[i].nom);
        printf("  |   Syntaxe : %s\n", aides[i].syntaxe);
        printf("  |   Description : %s\n", aides[i].description);
        if (aides[i].afficher_parametres != NULL) {
            aides[i].afficher_parametres();
        }
        else {
            printf("  | \n");
        }
    }
}
void afficher_parametres_inscription() {
    printf("  |   Parametres :\n");
    printf("  |     <nom>    : Nom de l'etudiant (chaine de caracteres, max %d caracteres, sans espaces)\n", LONGUEUR_NOM - 1);
    printf("  |     <groupe> : Numero de groupe (entier)\n  | \n");
}
void afficher_parametres_absence() {
    printf("  |   Parametres :\n");
    printf("  |     <id>           : Identifiant de l'etudiant (entier)\n");
    printf("  |     <Njour>        : Numero de jour (entier entre 1 et 40)\n");
    printf("  |     <demijournee>  : 'am' pour le matin, 'pm' pour l'apres-midi (chaine de caracteres, max %d caracteres)\n  | \n", LONGUEUR_DEMI_JOURNEE - 1);
}
void afficher_parametres_justificatif() {
    printf("  |   Parametres :\n");
    printf("  |     <id>           : Identifiant de l'absence (entier)\n");
    printf("  |     <Njour>        : Numero de jour (entier entre 1 et 40)\n");
    printf("  |     <justificatif> : Justificatif (chaine de caracteres, max %d caracteres)\n  | \n", LONGUEUR_JUSTIFICATIF - 1);
}
void afficher_parametres_etudiants() {
    printf("  |   Parametres :\n");
    printf("  |     <jour> : Numero de jour courant (entier >= 1)\n  | \n");
}
void afficher_parametres_validation() {
    printf("  |   Parametres :\n");
    printf("  |     <id>   : Identifiant de l'absence (entier)\n");
    printf("  |     <code> : 'ok' pour valider, 'ko' pour invalider\n  | \n");
}
void afficher_parametres_etudiant() {
    printf("  |   Parametres :\n");
    printf("  |     <id>   : Identifiant de l'etudiant (entier)\n");
    printf("  |     <jour> : Numero de jour courant (entier >= 1)\n  | \n");
}
void afficher_parametres_defaillants() {
    printf("  |   Parametres :\n");
    printf("  |     <jour> : Numero de jour courant (entier >= 1)\n  | \n");
}
