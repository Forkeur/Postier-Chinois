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
    TypGraphe* g = parse(fopen("complex2", "r"));
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


    /*FILE* f = fopen("titi", "r");
    
    TypGraphe* g = parse(f);
    
    printf("%p", g);
    affichageTypGraphe(g);
    fclose(f);
    quitter();*/
    return (EXIT_SUCCESS);
}

