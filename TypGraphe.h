/* 
 * File:   TypGraphe.h
 * Author: maxime & awaleh
 *
 * Created on 24 octobre 2014, 20:50
 */

#pragma once

#include "TypVoisin.h"

#ifdef	__cplusplus
extern "C"
{
#endif

typedef struct
{
    bool estOriente : 1;
    int nbMaxSommets;
    TypVoisins** listesAdjacences;
} TypGraphe;

typedef int errorcode;

static const char* TYPGRAPH_ERRORS[] = {
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

TypGraphe* newTypGraphe(int nbMaxSommets, bool estOriente);
bool checkAccessListesAdjacences(TypGraphe* self, voisinT i);
bool checkSommetExist(TypGraphe* self, voisinT i);

errorcode insertionSommetTypGraphe(TypGraphe* self, voisinT numero);
static TypVoisins* _insertionAreteTypGraphe(TypGraphe* self, voisinT from,
                                            voisinT to, dataT data);

TypVoisins* sommetAdjacentTypGraphe(TypGraphe* self, voisinT from, voisinT to);
errorcode insertionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data);
errorcode insertionSymetriqueAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data);
errorcode _suppressionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to);
errorcode suppressionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to);
errorcode suppressionSommetTypGraphe(TypGraphe* self, voisinT sommet);

void sauvegardeTypGraphe(TypGraphe* g, FILE* fichier);
void affichageTypGraphe(TypGraphe* g);


#ifdef	__cplusplus
}
#endif

