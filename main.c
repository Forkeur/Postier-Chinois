/*
 * File:   main.c
 * Author: maxime
 *
 * Created on 10 octobre 2014, 10:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "TypVoisin.h"

typedef struct
{
    bool estOriente : 1;
    int nbMaxSommets;
    TypVoisins** listesAdjacences;
} TypGraphe;

typedef int errorcode;


char reponse, c, choix, QuitterSousMenu = 0, choix2, q, orienter;
char nomfichier[PATH_MAX];
int nbMaxSommets, ch, numero, vp, vs, poids;
static TypGraphe* graph = NULL;



const char* TYPGRAPH_ERRORS[] = {
    "wtf (What a Terrible Failure)",
    "impossible d'acceder au sommet",
    "le sommet existe deja",
    "le sommet n'existe pas",
    "erreur lors de la creation de l'arrete",
    "il existe deja une arrete allant vers ce sommet",
    "l'arrete n'existe pas",
    "erreur lors de la suppression de l'arrete",
    "impossible d'ouvrir le fichier"
};

TypGraphe* newTypGraphe(int nbMaxSommets, bool estOriente)
{
    if (nbMaxSommets <= 0)
    {
        return NULL;
    }
    TypGraphe* ret = malloc(1 * sizeof (TypGraphe));
    ret->estOriente = estOriente;
    ret->nbMaxSommets = nbMaxSommets;
    ret->listesAdjacences = calloc(nbMaxSommets, sizeof (TypVoisins*));
    return ret;
}

static bool checkAccessListesAdjacences(TypGraphe* self, voisinT i)
{
    return self && i >= 0 && i < self->nbMaxSommets;
}

static bool checkSommetExist(TypGraphe* self, voisinT i)
{
    return checkAccessListesAdjacences(self, i) && self->listesAdjacences[i];
}

errorcode insertionSommetTypGraphe(TypGraphe* self, voisinT numero)
{
    if (!checkAccessListesAdjacences(self, numero))
    {
        return -1;
    }
    if (self->listesAdjacences[numero])
    {
        return -2;
    }
    self->listesAdjacences[numero] = newTypVoisins();
    return 0;
}

static TypVoisins* _insertionAreteTypGraphe(TypGraphe* self, voisinT from,
                                            voisinT to, dataT data)
{
    return emplaceBackTypVoisins(self->listesAdjacences[from], to, data);
}

TypVoisins* sommetAdjacentTypGraphe(TypGraphe* self, voisinT from, voisinT to)
{
    return checkSommetExist(self, from)
            ? searchForVoisin(self->listesAdjacences[from], to)
            : NULL;
}

errorcode insertionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data)
{
    if (!checkAccessListesAdjacences(self, from) || !checkAccessListesAdjacences(self, to))
    {
        return -1;
    }
    if (!checkSommetExist(self, from) || !checkSommetExist(self, to))
    {
        return -3;
    }

    if (sommetAdjacentTypGraphe(self, from, to))
    {
        return -5;
    }

    if (!_insertionAreteTypGraphe(self, from, to, data))
    {
        return -4;
    }
    if (!self->estOriente)
    {
        if (sommetAdjacentTypGraphe(self, to, from))
        {
            return -5;
        }
        if (!_insertionAreteTypGraphe(self, to, from, data))
        {
            return -4;
        }
    }
    return 0;
}

errorcode insertionSymetriqueAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data)
{
    if (self->estOriente)
    {
        return insertionAreteTypGraphe(self, from, to, data) ||
                insertionAreteTypGraphe(self, to, from, data);
    }
    return insertionAreteTypGraphe(self, from, to, data);
}

errorcode _suppressionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to)
{
    TypVoisins* voisin = sommetAdjacentTypGraphe(self, from, to);
    if (!voisin)
    {
        return -6;
    }
    return removeTypVoisins(voisin) ? 0 : -7;
}

errorcode suppressionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to)
{
    if (!checkAccessListesAdjacences(self, from) ||
            !checkAccessListesAdjacences(self, to))
    {
        return -1;
    }
    if (!checkSommetExist(self, from) || !checkSommetExist(self, to))
    {
        return -3;
    }
    int ret = _suppressionAreteTypGraphe(self, from, to);
    if (!self->estOriente){
        ret |= _suppressionAreteTypGraphe(self, to, from);
    }
    return ret;
}

errorcode suppressionSommet(TypGraphe* self, voisinT sommet)
{
    if (!checkAccessListesAdjacences(self, sommet))
    {
        return -1;
    }
    if (!checkSommetExist(self, sommet))
    {
        return -3;
    }

    deepDeleteTypVoisins(self->listesAdjacences[sommet]);
    self->listesAdjacences[sommet] = NULL;
    for (int i = 0; i < self->nbMaxSommets; ++i)
    {
        if (_suppressionAreteTypGraphe(self, i, sommet) == -7)
        {
            return -7;
        }
    }
}

void cleanup_stdin()
{
    scanf("%*[^\n]s");
    getchar();
}

/**
 * Permet d'eviter les "buffer overflow" lors des scanf pour les paths.
 * @return un string qui definit le format de scanf. (ie 1er argument de scanf)
 */
static char* scanf_format_path_max()
{
    static char* _scanf_format_path_max = NULL; // initialisation de la variable ne se fait que la 1er fois que la fonction est lancÃ©e.
    if (_scanf_format_path_max == NULL)
    {
        _scanf_format_path_max = malloc((strlen("%s") + 1 + (int) log10(PATH_MAX) + 1) * sizeof (char));
        sprintf(_scanf_format_path_max, "%%%is", PATH_MAX); // crÃ©e un string du type "%4096s"
    }
    return _scanf_format_path_max;
}

void handle_error_code(errorcode err)
{
    size_t index = -err;
    if (index > 0 && index < sizeof (TYPGRAPH_ERRORS))
    {
        printf("%s\n", TYPGRAPH_ERRORS[index]);
    }else{
        printf("success\n");
    }
}

/*
 * Description : cette fonction permet d'ecrire le graphe dans un fichier.
 */
void sauvegarde(TypGraphe* g, FILE* fichier)
{
    if (fichier)
    {
        fprintf(fichier, "# nombre maximum de sommets\n");
        fprintf(fichier, "%d\n", g->nbMaxSommets);
        fprintf(fichier, "# Orienter\n");
        fprintf(fichier, "%s\n", g->estOriente ? "o" : "n");
        fprintf(fichier, "# sommets : voisins\n");
        int i = 0;
        bool ajoutvirgule;
        for (i = 0; i < g->nbMaxSommets; i++)
        {
            ajoutvirgule = false;
            TypVoisins* it = g->listesAdjacences[i];
            if (it == NULL)
            {
                continue;
            }
            fprintf(fichier, "%d : ", i);
            do
            {
                if (!isSentinelTypVoisins(it))
                {
                    if (ajoutvirgule)
                    {
                        fprintf(fichier, ", ");
                    }
                    printf("(%d/%d)", it->voisin, it->data);
                    
                }
                ajoutvirgule = it != g->listesAdjacences[i];
                it = it->voisinSuivant;
                ajoutvirgule &= it != g->listesAdjacences[i];
            }
            while (it != g->listesAdjacences[i]);
            fprintf(fichier, "\n");
        }
    }

}

/*
 * Description : cette fonction permet d'afficher le graphe.
 */
void affichage(TypGraphe* g)
{
    sauvegarde(g, stdout);
}

/*
 * Description : cette fonction permet d'afficher le menu secondaire.
 */
void MenuGraph()
{
    int scanfresult = -1;
    while (QuitterSousMenu != 'n')
    {

        printf("  ---------------  MENU GRAPHE  ---------------------\n");
        printf(" |       [0]-> Afficher le graphe.                   |\n");
        printf(" |       [1]-> Sauvegarder le graphe.                |\n");
        printf(" |       [2]-> Inserer un sommet.                    |\n");
        printf(" |       [3]-> Inserer une arête.                    |\n");
        printf(" |       [4]-> Supprimer une arête.                  |\n");
        printf(" |       [5]-> Supprimer un sommet.                  |\n");
        printf(" |       [6]-> Quitter.                              |\n");
        printf("  ---------------------------------------------------\n");
        scanfresult = -1;
        while (scanfresult <= 0)
        {
            printf("Votre choix? ");
            scanfresult = scanf("%d", &choix2);
            cleanup_stdin();
        }
        switch (choix2)
        {
        case 0:
            printf("-----------------Affichage du graphe.----------------------------- \n");
            affichage(graph);
            break;

        case 1:
            printf("-----------------Sauvegarde du graphe.----------------------------- \n");
            printf("Entrez le nom du fichier à sauvegarder : ");
            scanf(scanf_format_path_max(), &nomfichier);
            cleanup_stdin();
            FILE* f = fopen(nomfichier, "w");
            if (f)
            {
                sauvegarde(graph, f);
                fclose(f);
            }
            else
            {
                handle_error_code(7);
            }
            break;

        case 2:
            printf("-----------------Insertion d'un sommet.----------------------------- \n");
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le numero du sommet: ");
                scanfresult = scanf("%u", &numero);
                cleanup_stdin();
            }
            handle_error_code(insertionSommetTypGraphe(graph, numero));
            break;
        case 3:
            printf("-----------------Insertion d'une arête.----------------------------- \n");
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le numero du sommet voisin precedant : \n");
                scanfresult = scanf("%u", &vp);
                cleanup_stdin();
            }
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le numero du sommet voisin suivant : \n");
                scanfresult = scanf("%u", &vs);
                cleanup_stdin();
            }
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le poids : \n");
                scanfresult = scanf("%u", &poids);
                cleanup_stdin();
            }

            handle_error_code(insertionAreteTypGraphe(graph, vp, vs, poids));

            break;
        case 4:
            printf("-----------------Suppression d'une arête----------------------------- \n");
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le numero du sommet voisin precedant : \n");
                scanfresult = scanf("%u", &vp);
                cleanup_stdin();
            }
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le numero du sommet voisin suivant : \n");
                scanfresult = scanf("%u", &vs);
                cleanup_stdin();
            }
            handle_error_code(suppressionAreteTypGraphe(graph, vp, vs));

            break;
        case 5:
            printf("-----------------Suppression d'un sommet----------------------------- \n");
            scanfresult = -1;
            while (scanfresult <= 0)
            {
                printf("Entrez le numero du sommet: ");
                scanfresult = scanf("%u", &numero);
                cleanup_stdin();
            }
            handle_error_code(suppressionSommet(graph, numero));

            break;
        case 6:

            break;

        default: printf("Veuillez saisir un chiffre correct");

        }
        do
        {
            printf("\n Voulez vous continuer ? ('o' pour continuer / 'n' pour quitter)\n");
            QuitterSousMenu = getchar();
            cleanup_stdin();
        }
        while (QuitterSousMenu != 'o' && QuitterSousMenu != 'n');

    }

}


void quitter(){
    if (graph){
        free(graph);
    }
    exit(EXIT_SUCCESS);
}


/*
 * Description : cette fonction permet d'afficher le menu principale.
 */

void MenuPrincipale()
{
    int scanfresult = -1;


    printf("\n");
    printf("\t********* MENU PRINCIPAL *********** \n");
    printf("\t|    1 : Charger un graphe         | \n");
    printf("\t|    2 : Creer un graphe           | \n");
    printf("\t|    3 : Quitter                   | \n");
    printf("\t************************************ \n");
    fflush(stdout);
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        printf("Donnez le nom du fichier à charger :\n");
        scanf(scanf_format_path_max(), &nomfichier);
        cleanup_stdin();
        printf("\t Message: Chargement du graphe effectuer avec succes\n");

        MenuGraph();

        // on test si le fichier existe à l'aide du fonction 

        // si le fichier existe on procede à sa lecture.

        break;


    case 2:


        printf("---creation du graphe---\n");
        scanfresult = -1;
        while (scanfresult <= 0 || nbMaxSommets < 1)
        {
            printf("Entrez le nombre maximum des sommets : \n");
            scanfresult = scanf("%u", &nbMaxSommets);
            cleanup_stdin();
        }
        do
        {
            printf("le graphe est orienter? ('o' pour oui / 'n' pour non) \n");
            orienter = getchar();
            cleanup_stdin();
        }
        while (orienter != 'o' && orienter != 'n');

        //creation du graphe
        graph = newTypGraphe(nbMaxSommets, orienter == 'o');
        MenuGraph();
        break;

    case 3:

        quitter();
        break;

    default: printf("/n Veuillez saisir un chiffre correct\n");
    }
}

int main(int argc, char** argv)
{

    graph = newTypGraphe(10, false);
    handle_error_code(insertionSommetTypGraphe(graph, 2));
    handle_error_code(insertionSommetTypGraphe(graph, 3));
    handle_error_code(insertionSommetTypGraphe(graph, 5));
    handle_error_code(insertionAreteTypGraphe(graph, 2, 3, 99));
    handle_error_code(insertionAreteTypGraphe(graph, 2, 5, 90));
    affichage(graph);
    handle_error_code(suppressionAreteTypGraphe(graph, 2, 3));
    affichage(graph);
    handle_error_code(suppressionSommet(graph, 2));
    //MenuPrincipale();
    affichage(graph);
    
    quitter();
    return (EXIT_SUCCESS);
}

