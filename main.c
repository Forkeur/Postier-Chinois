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
#include "TypGraphe.h"
#include "menu.h"

int main(int argc, char** argv)
{

    TypGraphe* graph = newTypGraphe(10, false);
    handle_error_code(insertionSommetTypGraphe(graph, 2));
    handle_error_code(insertionSommetTypGraphe(graph, 3));
    handle_error_code(insertionSommetTypGraphe(graph, 5));
    handle_error_code(insertionAreteTypGraphe(graph, 2, 3, 99));
    handle_error_code(insertionAreteTypGraphe(graph, 2, 3, 99));
    handle_error_code(insertionAreteTypGraphe(graph, 2, 5, 90));
    affichageTypGraphe(graph);
    handle_error_code(suppressionAreteTypGraphe(graph, 2, 3));
    //affichageTypGraphe(graph);
    handle_error_code(suppressionSommetTypGraphe(graph, 2));
    //MenuPrincipale();
    //affichageTypGraphe(graph);
    
    quitter();
    return (EXIT_SUCCESS);
}

