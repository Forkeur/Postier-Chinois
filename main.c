/* 
 * File:   main.c
 * Author: maxime
 *
 * Created on 10 octobre 2014, 10:04
 */

#include <stdio.h>
#include <stdlib.h>
#include "TypVoisin.h"

typedef struct
{
    bool estOriente : 1;
    int nbMaxSommets;
    TypVoisins** listesAdjacences;
} TypGraphe;

typedef int errorcode;


const char* TYPGRAPH_ERRORS[] = {
    "wtf (What a Terrible Failure)",
    "impossible d'acceder au sommet",
    "le sommet existe deja",
    "le sommet n'existe pas",
    "erreur lors de la creation de l'arrete",
    "il existe deja une arrete allant vers ce sommet",
    "l'arrete n'existe pas",
    "erreur lors de la suppression de l'arrete"
};

/**
 * La fonctionalité etc demander dans le "cahier des charges"
 */
void etc(void)
{
}

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

errorcode insertionAreteTypGraphe(TypGraphe* self, voisinT from,
                                  voisinT to, dataT data)
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

errorcode insertionSymetriqueAreteTypGraphe(TypGraphe* self, voisinT from,
                                            voisinT to, dataT data)
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

    return _suppressionAreteTypGraphe(self, from, to);
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

int main(int argc, char** argv)
{

    TypVoisins* lst = newTypVoisins();
    emplaceBackTypVoisins(lst, 1, 1);
    emplaceBackTypVoisins(lst, 2, 1);



    TypGraphe* graph = newTypGraphe(3, false);
    printf("%p", graph->listesAdjacences);
    return (EXIT_SUCCESS);
}

