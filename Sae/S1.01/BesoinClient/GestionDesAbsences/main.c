#include <stdio.h>
#include <string.h>
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

typedef enum {
	EXIT = 0,
	INSCRIPTION,
	ABSENCE,
	HELP,
	INCONNU,
} Commande;

typedef struct {
	int Njour;
	char demijournee[LEN_CHAR_DEMI_JOURNEE];
} Absence;

typedef struct {
	char nom[LONGUEUR_NOM];
	int groupe;
	Absence absences[MAX_ABSENCES];
	int nombreAbsences;
} Etudiant;

typedef struct {
	Etudiant etudiants[MAX_ETUDIANTS];
	int nombreEtudiants;
} GestionAbsences;


// C0
void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE]); // Fonction qui permet de lire le nom de la commande (premier mot de la commande)
Commande lire_commande(char commande[LONGUEUR_COMMANDE]); // Fonction qui renvoie un numéro correspondant à la commande
void afficher_aide(); // Fonction qui affiche l'aide

// C1
void inscrire_etudiant(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]); // Fonction qui inscrit un étudiant
void lecture_nom_etudiant(char commande[LONGUEUR_COMMANDE], char nom[LONGUEUR_NOM]); // Fonction qui permet de lire le nom de l'étudiant
void lecture_groupe_etudiant(char commande[LONGUEUR_COMMANDE], int* groupe); // Fonction qui permet de lire le groupe de l'étudiant
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe); // Fonction qui vérifie si un étudiant existe

// C2
void enregistrer_absence(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]); // Fonction qui enregistre une absence
void lecture_id_etudiant(char commande[LONGUEUR_COMMANDE], int* id); // Fonction qui permet de lire l'id de l'étudiant
void lecture_Njour_absence(char commande[LONGUEUR_COMMANDE], int* Njour); // Fonction qui permet de lire le numéro de jour de l'absence
void lecture_demijournee_absence(char commande[LONGUEUR_COMMANDE], char demijournee[LEN_CHAR_DEMI_JOURNEE]); // Fonction qui permet de lire la demi-journée de l'absence
bool verifier_absence_existe(GestionAbsences* gestionAbsences, int id, int Njour, char demijournee[LEN_CHAR_DEMI_JOURNEE]); // Fonction qui vérifie si une absence existe

int main() {

	char commande[LONGUEUR_COMMANDE];
	GestionAbsences gestionAbsences;
	gestionAbsences.nombreEtudiants = 0;

	printf("Bienvenue sur l'application de gestion des absences. \n\n");
	
	while ( true )
	{

		printf("Entrer une commade : ");

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
		switch (lire_commande(commande))
		{
		case EXIT:
			
			printf("Au revoir !\n");
			return 0;
			break;

		case INSCRIPTION:

			inscrire_etudiant(&gestionAbsences, commande);

			break;

		case ABSENCE:

			enregistrer_absence(&gestionAbsences, commande);
			
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
Commande lire_commande(char commande[LONGUEUR_COMMANDE])
{

	char nom_commande[LONGUEUR_COMMANDE];
	lecture_commande(commande, nom_commande);

	if (strcmp(nom_commande, "exit") == 0)
	{
		return EXIT;
	}
	else if (strcmp(nom_commande, "inscription") == 0)
	{
		return INSCRIPTION;
	}
	else if (strcmp(nom_commande, "absence") == 0)
	{
		return ABSENCE;
	}
	else if (strcmp(nom_commande, "help") == 0)
	{
		return HELP;
	}
	else
	{
		return INCONNU;
	}
}

// Fonction qui affiche l'aide
void afficher_aide()
{
	printf("\nListe des commandes :\n\n");
	printf("exit : Quitter l'application\n");
	printf("inscription : Inscrire un etudiant\n");
	printf("absence : Enregistrer une absence\n");
	printf("help : Afficher l'aide\n\n");
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

		// Ajoute l'étudiant à la liste
		gestionAbsences->etudiants[gestionAbsences->nombreEtudiants] = etudiant;
		gestionAbsences->nombreEtudiants++;

		printf("Inscription enregistree (%d)\n", gestionAbsences->nombreEtudiants);
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
	while (commande[i] != ' ' && commande[i] != '\0') // Commande
	{
		i++;
	}
	i++;
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
	int j = 0;
	while (commande[i] != ' ' && commande[i] != '\0') // Commande
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0') // Nom
	{
		i++;
	}
	i++;
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
	int Njour = 0;
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
		printf("”Absence deja connue\n");
		return;
	}

	// Crée l'absence
	Absence absence;
	absence.Njour = Njour;
	strcpy(absence.demijournee, demijournee);

	// Ajoute l'absence à la liste
	gestionAbsences->etudiants[id].absences[gestionAbsences->etudiants[id].nombreAbsences] = absence;
	gestionAbsences->etudiants[id].nombreAbsences++;

	printf("Absence enregistree [%d]\n", gestionAbsences->etudiants[id].nombreAbsences);
}

// Fonction qui permet de lire l'id de l'étudiant
void lecture_id_etudiant(char commande[LONGUEUR_COMMANDE], int* id)
{
	int i = 0;
	int j = 0;
	while (commande[i] != ' ' && commande[i] != '\0') // Commande
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0') // Id
	{
		*id = *id * 10 + (commande[i] - '0'); // Conversion du caractère en entier
		i++;
	}
	(*id)--; // On décrémente l'id pour obtenir l'index dans le tableau
}

// Fonction qui permet de lire le numéro de jour de l'absence
void lecture_Njour_absence(char commande[LONGUEUR_COMMANDE], int* Njour)
{
	int i = 0;
	int j = 0;
	while (commande[i] != ' ' && commande[i] != '\0') // Commande
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0') // Id
	{
		i++;
	}
	i++;
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
	while (commande[i] != ' ' && commande[i] != '\0') // Commande
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0') // Id
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0') // Njour
	{
		i++;
	}
	i++;
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
