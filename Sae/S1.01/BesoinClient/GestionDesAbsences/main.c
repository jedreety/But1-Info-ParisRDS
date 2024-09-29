#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

typedef enum {
	false = 0,
	true = 1,
} bool;

const enum {
	LONGUEUR_COMMANDE = 100,
	MAX_ETUDIANTS = 100,
	LONGUEUR_NOM = 31,
};

typedef const enum {
	EXIT = 0,
	INSCRIPTION,
	HELP,
	INCONNU,
} Commande;

typedef struct {
	char nom[LONGUEUR_NOM];
	int groupe;
	int nombreAbsences;
} Etudiant;

typedef struct {
	Etudiant etudiants[MAX_ETUDIANTS];
	int nombreEtudiants;
} GestionAbsences;

void lecture_commande(char commande[LONGUEUR_COMMANDE], char nom_commande[LONGUEUR_COMMANDE]); // Fonction qui permet de lire le nom de la commande (premier mot de la commande)
Commande lire_commande(char commande[LONGUEUR_COMMANDE]); // Fonction qui renvoie un numéro correspondant à la commande
void afficher_aide(); // Fonction qui affiche l'aide

void inscrire_etudiant(GestionAbsences* gestionAbsences, char commande[LONGUEUR_COMMANDE]); // Fonction qui inscrit un étudiant
void lecture_nom_etudiant(char commande[LONGUEUR_COMMANDE], char nom[LONGUEUR_NOM]); // Fonction qui permet de lire le nom de l'étudiant
void lecture_groupe_etudiant(char commande[LONGUEUR_COMMANDE], int* groupe); // Fonction qui permet de lire le groupe de l'étudiant
bool verifier_etudiant_existe(GestionAbsences* gestionAbsences, char nom[LONGUEUR_NOM], int groupe); // Fonction qui vérifie si un étudiant existe

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

		case HELP:

			afficher_aide();
			break;

		case INCONNU:

			printf("Commande inconnue\n");
			break;

		default:
			printf("Commande non traitée\n");
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
			printf("Nom incorrect\n", nom, groupe);
			return;
		}

		// Crée l'étudiant
		Etudiant etudiant;
		strcpy(etudiant.nom, nom);
		etudiant.groupe = groupe;

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
	while (commande[i] != ' ' && commande[i] != '\0')
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0')
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
	while (commande[i] != ' ' && commande[i] != '\0')
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0')
	{
		i++;
	}
	i++;
	while (commande[i] != ' ' && commande[i] != '\0')
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