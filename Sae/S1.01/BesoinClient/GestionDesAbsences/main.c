#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef enum {
	false = 0,
	true = 1,
} bool;

enum {
	LONGUEUR_COMMANDE = 100,
	LEN_CHAR_DEMI_JOURNEE = 3,
	MAX_ABSENCES = 100,
	MAX_ETUDIANTS = 100,
	LONGUEUR_NOM = 31,
};

typedef char STR_Commande[LONGUEUR_COMMANDE];

const STR_Commande liste_commande[] = {
	
	"exit",
	"inscription",
	"absence",
	"etudiants",
	"help"
};
const unsigned int nb_commande = (sizeof(liste_commande) / sizeof(liste_commande[0])) + 1; // Calcule le nombre de commande inscrite

typedef enum {
	EXIT = 0,
	INSCRIPTION,
	ABSENCE,
	ETUDIANTS,

	HELP,
	INCONNU,
} INT_Commande;

typedef struct {
	unsigned int Njour;
	char demijournee[LEN_CHAR_DEMI_JOURNEE];
} Absence;

typedef struct {
	char nom[LONGUEUR_NOM];
	int groupe;
	Absence absences[MAX_ABSENCES];
	unsigned int nombreAbsences;
	unsigned int id;
} Etudiant;

typedef struct {
	Etudiant etudiants[MAX_ETUDIANTS];
	unsigned int nombreEtudiants;
} GestionAbsences;


// C0
void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE]); // Fonction qui permet de lire le nom de la commande (premier mot de la commande)
INT_Commande lire_commande(char commande[LONGUEUR_COMMANDE]); // Fonction qui renvoie un numéro correspondant à la commande
void afficher_aide(); // Fonction qui affiche l'aide
void loop_to_space(char commande[LONGUEUR_COMMANDE], int* i); // Fonction qui permet de passer à l'espace suivant
void executer_commande(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]); // execute la commande 

// C1
void inscrire_etudiant(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]); // Fonction qui inscrit un étudiant
void lecture_nom_etudiant(char commande[LONGUEUR_COMMANDE], char nom[LONGUEUR_NOM]); // Fonction qui permet de lire le nom de l'étudiant
void lecture_groupe_etudiant(char commande[LONGUEUR_COMMANDE], int* groupe); // Fonction qui permet de lire le groupe de l'étudiant
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe); // Fonction qui vérifie si un étudiant existe

// C2
void enregistrer_absence(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]); // Fonction qui enregistre une absence
void lecture_id_etudiant(char commande[LONGUEUR_COMMANDE], int* id); // Fonction qui permet de lire l'id de l'étudiant
void lecture_Njour_absence(char commande[LONGUEUR_COMMANDE], unsigned int* Njour); // Fonction qui permet de lire le numéro de jour de l'absence
void lecture_demijournee_absence(char commande[LONGUEUR_COMMANDE], char demijournee[LEN_CHAR_DEMI_JOURNEE]); // Fonction qui permet de lire la demi-journée de l'absence
bool verifier_absence_existe(GestionAbsences* gestionAbsences, int id, int Njour, char demijournee[LEN_CHAR_DEMI_JOURNEE]); // Fonction qui vérifie si une absence existe

// C3
void calculer_etudiants_absents(char commande[LONGUEUR_COMMANDE], GestionAbsences* gestionAbsences); // Fonction qui affiche la liste des étudiants absents à un jour donné
void lecture_jour_absence(char commande[LONGUEUR_COMMANDE], int* jour); // Fonction qui permet de lire le jour de l'absence
void insert_etudiants_absents(Etudiant etudiant_absents[MAX_ETUDIANTS], Etudiant etudiant, int* nombreEtudiantsAbsents, int jour); // Fonction qui insère un étudiant dans la liste des étudiants absents
void sort_etudiants_absents_NOM(const void* a, const void* b); // Fonction qui trie la liste des étudiants absents par nom (ordre alphabétique)
void sort_etudiants_absents_GROUPE(const void* a, const void* b); // Fonction qui trie la liste des étudiants absents par groupe (ordre croissant)
void afficher_etudiants_absents(Etudiant etudiant_absents[MAX_ETUDIANTS], int nombreEtudiantsAbsents); // Fonction qui affiche la liste des étudiants absents

int main() {

	char commande[LONGUEUR_COMMANDE];
	GestionAbsences gestionAbsences;
	gestionAbsences.nombreEtudiants = 0;

	printf("Bienvenue sur l'application de gestion des absences. \n\n");
	
	while ( true )
	{

		printf("Entrer une commande : ");

		// Lecture de la commande
		if (scanf(" %[^\n]%*c", commande) != 1) // %*c permet de consommer le caractère de retour à la ligne
		{
			printf("Erreur lors de la lecture de la commande.\n");
			return 1;
		}
		else
		{
			commande[LONGUEUR_COMMANDE - 1] = '\0';
		}


		// Traitement de la commande
		executer_commande(&gestionAbsences, commande);
		
	}

	return 0;

}

// Fonction qui permet de lire le nom de la commande (premier mot de la commande)
void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE])
{
	int i = 0;
	while (commande[i] != ' ' && commande[i] != '\0')
	{
		nom_commande[i] = commande[i];
		i++;
	}
	nom_commande[i] = '\0';
}

// Fonction qui renvoie un numéro correspondant à la commande
INT_Commande lire_commande(char commande[LONGUEUR_COMMANDE])
{

	char nom_commande[LONGUEUR_COMMANDE];
	lecture_commande(commande, nom_commande);

	// parcour la list des commandes
	for (unsigned int index = 0; index < nb_commande; ++index) {
		// Si le cas est trouvé
		if (strcmp(nom_commande, liste_commande[index]) == 0) {
			return index; // il est important que 
		}
	}
	return nb_commande + 1;

}

// Fonction qui affiche l'aide
void afficher_aide()
{
	printf("\nListe des commandes :\n\n");
	printf("exit : Quitter l'application\n");
	printf("inscription : Inscrire un etudiant\n");
	printf("absence : Enregistrer une absence\n");
	printf("etudiants : Afficher la liste des etudiants absents ce jour\n");
	printf("help : Afficher l'aide\n\n");
}

// Fonction qui permet de passer à l'espace suivant
void loop_to_space(char commande[LONGUEUR_COMMANDE], int* i)
{
	while (commande[*i] != ' ' && commande[*i] != '\0')
	{
		(*i)++;
	}
	(*i)++;
}

// execute la commande 
void executer_commande(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]) {
	
	switch (lire_commande(commande))
	{
	case EXIT:

		printf("Au revoir !\n");
		return 0;
		break;

	case INSCRIPTION:

		inscrire_etudiant(gestionAbsences, commande);

		break;

	case ABSENCE:

		enregistrer_absence(gestionAbsences, commande);

		break;

	case ETUDIANTS:

		calculer_etudiants_absents(commande, gestionAbsences);
		break;

	case HELP:

		afficher_aide();
		break;

	case INCONNU:

		printf("Commande inconnue\n");
		break;

	default:
		printf("Commande non traitee\n");
		return -1;
		break;
	}
}


// Fonction qui inscrit un étudiant
void inscrire_etudiant(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE])
{
	if (gestionAbsences->nombreEtudiants < MAX_ETUDIANTS)
	{
		char nom[LONGUEUR_NOM];
		int groupe = 0;

		lecture_nom_etudiant(commande, nom);
		lecture_groupe_etudiant(commande, &groupe);

		// Vérifie que l'etudiant n'existe pas déjà
		if (verifier_etudiant_existe(gestionAbsences, nom, groupe))
		{
			printf("Nom incorrect\n");
			return;
		}

		// Crée l'étudiant
		Etudiant etudiant;
		strcpy(etudiant.nom, nom);
		etudiant.groupe = groupe;
		etudiant.nombreAbsences = 0;
		etudiant.id = gestionAbsences->nombreEtudiants + 1;

		// Ajoute l'étudiant à la liste
		gestionAbsences->etudiants[gestionAbsences->nombreEtudiants] = etudiant;
		gestionAbsences->nombreEtudiants++;

		printf("Inscription enregistree (%u)\n", gestionAbsences->nombreEtudiants);
	}
	else
	{
		printf("Impossible d'inscrire un nouvel etudiant, le nombre maximum d'etudiants est atteint.\n");
	}
}

// Fonction qui permet de lire le nom de l'étudiant
void lecture_nom_etudiant(char commande[LONGUEUR_COMMANDE], char nom[LONGUEUR_NOM])
{
	int i = 0;
	int j = 0;
	loop_to_space(commande, &i); // Commande
	while (commande[i] != ' ' && commande[i] != '\0') // Nom
	{
		nom[j] = commande[i];
		i++;
		j++;
	}
	nom[j] = '\0';
}

// Fonction qui permet de lire le groupe de l'étudiant
void lecture_groupe_etudiant(char commande[LONGUEUR_COMMANDE], int* groupe)
{
	int i = 0;
	loop_to_space(commande, &i); // Commande
	loop_to_space(commande, &i); // Nom
	while (commande[i] != ' ' && commande[i] != '\0') // Groupe
	{
		*groupe = *groupe * 10 + (commande[i] - '0'); // Conversion du caractère en entier
		i++;
	}
}

// Fonction qui vérifie si un étudiant existe ( renvoie vrai si l'étudiant existe, faux sinon)
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe)
{
	for (int i = 0; i < gestionAbsences->nombreEtudiants; i++)
	{
		if (strcmp(gestionAbsences->etudiants[i].nom, nom) == 0 && gestionAbsences->etudiants[i].groupe == groupe)
		{
			return true;
		}
	}
	return false;
}


// Fonction qui enregistre une absence
void enregistrer_absence(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE])
{
	int id = 0;
	unsigned int Njour = 0;
	char demijournee[LEN_CHAR_DEMI_JOURNEE];

	lecture_id_etudiant(commande, &id);
	lecture_Njour_absence(commande, &Njour);
	lecture_demijournee_absence(commande, demijournee);

	if (id < 0 || id >= gestionAbsences->nombreEtudiants)
	{
		printf("Identifiant incorrect\n");
		return;
	}

	if (Njour < 1 || Njour > 40)
	{
		printf("Numero de jour incorrect\n");
		return;
	}

	if (strcmp(demijournee, "am") != 0 && strcmp(demijournee, "pm") != 0)
	{
		printf("Demi-journee incorrecte\n");
		return;
	}

	if (verifier_absence_existe(gestionAbsences, id, Njour, demijournee))
	{
		printf("Absence deja connue\n");
		return;
	}

	// Crée l'absence
	Absence absence;
	absence.Njour = Njour;
	strcpy(absence.demijournee, demijournee);

	// Ajoute l'absence à la liste
	gestionAbsences->etudiants[id].absences[gestionAbsences->etudiants[id].nombreAbsences] = absence;
	gestionAbsences->etudiants[id].nombreAbsences++;

	printf("Absence enregistree [%u]\n", gestionAbsences->etudiants[id].nombreAbsences);
}

// Fonction qui permet de lire l'id de l'étudiant
void lecture_id_etudiant(char commande[LONGUEUR_COMMANDE], int* id)
{
	int i = 0;
	loop_to_space(commande, &i); // Commande
	while (commande[i] != ' ' && commande[i] != '\0') // Id
	{
		*id = *id * 10 + (commande[i] - '0'); // Conversion du caractère en entier
		i++;
	}
	(*id)--; // On décrémente l'id pour obtenir l'index dans le tableau
}

// Fonction qui permet de lire le numéro de jour de l'absence
void lecture_Njour_absence(char commande[LONGUEUR_COMMANDE], unsigned int* Njour)
{
	int i = 0;
	loop_to_space(commande, &i); // Commande
	loop_to_space(commande, &i); // Id
	while (commande[i] != ' ' && commande[i] != '\0') // Njour
	{
		*Njour = *Njour * 10 + (commande[i] - '0'); // Conversion du caractère en entier
		i++;
	}
}

// Fonction qui permet de lire la demi-journée de l'absence
void lecture_demijournee_absence(char commande[LONGUEUR_COMMANDE], char demijournee[LEN_CHAR_DEMI_JOURNEE])
{
	int i = 0;
	int j = 0;
	loop_to_space(commande, &i); // Commande
	loop_to_space(commande, &i); // Id
	loop_to_space(commande, &i); // Njour
	while (commande[i] != ' ' && commande[i] != '\0') // Demi-journee
	{
		demijournee[j] = commande[i];
		i++;
		j++;
	}
	demijournee[j] = '\0';
}

// Fonction qui vérifie si une absence existe ( renvoie vrai si l'absence existe, faux sinon)
bool verifier_absence_existe(GestionAbsences* gestionAbsences, int id, int Njour, char demijournee[LEN_CHAR_DEMI_JOURNEE])
{
	for (int i = 0; i < gestionAbsences->etudiants[id].nombreAbsences; i++)
	{
		if (gestionAbsences->etudiants[id].absences[i].Njour == Njour && strcmp(gestionAbsences->etudiants[id].absences[i].demijournee, demijournee) == 0)
		{
			return true;
		}
	}
	return false;
}

// Fonction qui affiche la liste des étudiants absents à un jour donné
void calculer_etudiants_absents(char commande[LONGUEUR_COMMANDE], GestionAbsences* gestionAbsences) {

	int jour = 0;
	lecture_jour_absence(commande, &jour);
	printf("Jour : %d\n", jour);
	// Si la date est incorrecte
	if (jour < 1)
	{
		printf("Date incorrecte\n");
		return;
	}
	
	Etudiant etudiant_absents[MAX_ETUDIANTS]; // Plus optimisé d'utiliser gestionAbsences->etudiants mais j'arrive pas
	
	// Parcours de la liste des étudiants
	int nombreEtudiantsAbsents = 0;
	for (int i = 0; i < gestionAbsences->nombreEtudiants; i++)
	{
		insert_etudiants_absents(etudiant_absents, gestionAbsences->etudiants[i], &nombreEtudiantsAbsents, jour);
	}

	// Si aucun étudiant n'est absent
	if (nombreEtudiantsAbsents == 0)
	{
		printf("Aucun inscrit\n");
		return;
	}

	// Tri des étudiants absents
	qsort(etudiant_absents, nombreEtudiantsAbsents, sizeof(Etudiant), sort_etudiants_absents_GROUPE);
	qsort(etudiant_absents, nombreEtudiantsAbsents, sizeof(Etudiant), sort_etudiants_absents_NOM);

	// Affichage des étudiants absents
	afficher_etudiants_absents(etudiant_absents, nombreEtudiantsAbsents);

}

// Fonction qui permet de lire le jour de l'absence
void lecture_jour_absence(char commande[LONGUEUR_COMMANDE], int* jour)
{
	int i = 0;
	loop_to_space(commande, &i); // Commande
	while (commande[i] != ' ' && commande[i] != '\0') // Jour
	{
		*jour = *jour * 10 + (commande[i] - '0'); // Conversion du caractère en entier
		i++;
	}
}

// Fonction qui insère un étudiant dans la liste des étudiants absents à un jour donné
void insert_etudiants_absents(Etudiant etudiant_absents[MAX_ETUDIANTS], Etudiant etudiant, int* nombreEtudiantsAbsents, int jour)
{
	// Parcours de la liste des absences de l'étudiant
	for (int j = 0; j < etudiant.nombreAbsences; j++)
	{

		if (etudiant.absences[j].Njour == jour)
		{
			etudiant_absents[*nombreEtudiantsAbsents] = etudiant;
			(*nombreEtudiantsAbsents)++;
			break;
		}
	}

}

// Fonction qui trie la liste des étudiants absents par nom (ordre alphabétique)
void sort_etudiants_absents_NOM(const void* a, const void* b)
{
	Etudiant* etudiant1 = (Etudiant*)a;
	Etudiant* etudiant2 = (Etudiant*)b;

	return strcmp(etudiant1->nom, etudiant2->nom);
}

// Fonction qui trie la liste des étudiants absents par classe (ordre croissant)
void sort_etudiants_absents_GROUPE(const void* a, const void* b)
{
	Etudiant* etudiant1 = (Etudiant*)a;
	Etudiant* etudiant2 = (Etudiant*)b;

	if (etudiant1->groupe < etudiant2->groupe)
	{
		return -1;
	}
	else if (etudiant1->groupe > etudiant2->groupe)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Fonction qui affiche la liste des étudiants absents
void afficher_etudiants_absents(Etudiant etudiant_absents[MAX_ETUDIANTS], int nombreEtudiantsAbsents)
{
	for (int i = 0; i < nombreEtudiantsAbsents; i++)
	{
		Etudiant etudiant = etudiant_absents[i];
		printf("(%u) %s %u %u \n", etudiant.id, etudiant.nom, etudiant.groupe, etudiant.nombreAbsences);
	}
}
