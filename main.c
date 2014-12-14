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

int main(int argc, char** argv)
{
    //MenuPrincipal();
    int i = INT_MAX;
    long long l = i;
    l += INT_MAX;
    printf("%i\n", i + 1);
    printf("%ld\n", l);
    /*FILE* f = fopen("titi", "r");
    
    TypGraphe* g = parse(f);
    
    printf("%p", g);
    affichageTypGraphe(g);
    fclose(f);
    quitter();*/
    return (EXIT_SUCCESS);
}

