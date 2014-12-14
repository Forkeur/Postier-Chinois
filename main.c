/*
 * File:   main.c
 * Author: maxime
 *
 * Created on 10 octobre 2014, 10:04
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "TypVoisin.h"
#include "TypGraphe.h"
#include "parser.h"
#include "menu.h"
#include "chinois.h"

int main(int argc, char** argv)
{
    //MenuPrincipal();
    TypGraphe* g = parse(fopen("complex", "r"));
    if (!g)
    {
        return EXIT_FAILURE;
    }
    affichageTypGraphe(g);
    struct exception ex = {};
    vector v = ParcoursEulerien(g, &ex);
    if (ex.msg)
    {
        printf("error : %s", ex.msg);
    }
    else
    {
        for (int i = 0; i < v.size; ++i)
        {
            printf("%d ", v.data[i]);
        }
    }
    
    printf("\n");
    vector v1;
    vector_init(&v1, 10);
    vector_push_back(&v1, 1);
    vector_push_back(&v1, 2);
    vector_push_back(&v1, 3);
    vector_push_back(&v1, 4);
    vector_push_back(&v1, 5);
    vector_push_back(&v1, 6);

    vector couplage = listeCouplage(&v1);
    for (int i = 0; i < couplage.size; ++i)
    {
        printf("%d ", couplage.data[i]);
    }


    /*FILE* f = fopen("titi", "r");
    
    TypGraphe* g = parse(f);
    
    printf("%p", g);
    affichageTypGraphe(g);
    fclose(f);
    quitter();*/
    return (EXIT_SUCCESS);
}

