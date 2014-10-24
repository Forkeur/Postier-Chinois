#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "menu.h"
#include "parser.h"

char reponse, c, choix, QuitterSousMenu = 0, choix2, q, orienter;
char nomfichier[PATH_MAX];
int nbMaxSommets, ch, numero, vp, vs, poids;
TypGraphe* graph = NULL;

static void cleanup_stdin()
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
    }
    else
    {
        printf("success\n");
    }
}

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
            affichageTypGraphe(graph);
            break;

        case 1:
            printf("-----------------Sauvegarde du graphe.----------------------------- \n");
            printf("Entrez le nom du fichier à sauvegarder : ");
            scanf(scanf_format_path_max(), &nomfichier);
            cleanup_stdin();
            FILE* f = fopen(nomfichier, "w");
            if (f)
            {
                sauvegardeTypGraphe(graph, f);
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
            handle_error_code(suppressionSommetTypGraphe(graph, numero));

            break;
        case 6:
            quitter();
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

void quitter()
{
    if (graph)
    {
        free(graph);
    }
    exit(EXIT_SUCCESS);
}

void MenuPrincipal()
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
        FILE* f = fopen(nomfichier, "r");
        if (f){
            graph = parse(f);
            fclose(f);
            if (graph){
                 printf("\t Message: Chargement du graphe effectuer avec succes\n");
            }
        }else{
            printf("Impossible d'ouvrir le fichier");
        }
        
        
        MenuGraph();

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
