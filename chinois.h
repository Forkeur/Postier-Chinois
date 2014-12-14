/* 
 * File:   chinois.h
 * Author: maxime
 *
 * Created on 14 décembre 2014, 15:21
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "TypGraphe.h"
#include "myvector.h"

#ifdef	__cplusplus
extern "C"
{
#endif

struct exception
{
    char* msg;
    size_t line;
};

typedef vector vertxvect;

// Nous considérons que le graphe de départ est correct.
// Ainsi,vous n’avez pas à tester si le graphe est connexe, ni s’il est orienté ou non.

vertxvect ParcoursEulerien(TypGraphe* g, struct exception* error);

vector listeCouplage(vector* sommetsImpairs);

void CPP(TypGraphe* g);


#ifdef	__cplusplus
}
#endif

