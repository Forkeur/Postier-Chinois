/* 
 * File:   TypVoisin.h
 * Author: maxime & awaleh
 *
 * Created on 10 octobre 2014, 14:06
 */

#pragma once

#include "stdbool.h"

#ifdef	__cplusplus
extern "C"
{
#endif
typedef int voisinT;
typedef int dataT;

/**
 * La valeur de la sentinel
 */
static const voisinT SENTINEL_VALUE = -1;

typedef struct _TypVoisins
{
    voisinT voisin;
    dataT data;
    struct _TypVoisins* voisinSuivant;
    struct _TypVoisins* voisinPrecedent;
} TypVoisins;

/**
 * permet de connaitre la valeur de la sentinel
 * @return 
 */
int getSentinelValue();

/**
 * Crée une nouvelle liste malloced (contient une sentinel)
 * @return une liste
 */
TypVoisins* newTypVoisins();

/**
 * Supprime en chaine la liste chainé.
 * @param self la liste
 */
void deepDeleteTypVoisins(TypVoisins* self);

/**
 * Crée un element d'une liste chainé malloced.
 * @param voisin le voisin
 * @param data la donnée
 * @return le nouvel element de la liste
 */
TypVoisins* createTypVoisins(voisinT voisin, dataT data);

/**
 * peremet de connaitre si l'element est la sentinel.
 * @param self un element de la liste
 * @return 
 */
bool isSentinelTypVoisins(TypVoisins* self);

/**
 * part a la recherche de la sentinel dans la liste.
 * @param self un element de la liste
 * @return la sentinel
 */
TypVoisins* getSentinelTypVoisins(TypVoisins* self);

/**
 * part a la recherche du dernier element de la liste.
 * @param self un element de la liste
 * @return le dernier element de la liste
 */
TypVoisins* getLastTypVoisins(TypVoisins* self);

/**
 * part a la recherche du premier element de la liste.
 * @param self un element de la liste
 * @return le premier element de la liste
 */
TypVoisins* getFirstTypVoisins(TypVoisins* self);

/**
 * insertion d'un element entre deux elements
 * @param left l'element precedent
 * @param incoming le nouvel element
 * @param rigth l'element suivant
 */
void insertTypVoisins(TypVoisins* left, TypVoisins* incoming, TypVoisins* rigth);

/**
 * ajout en fin d'un nouvel element dans la liste
 * @param self la liste
 * @param incoming le nouvel element
 * @return le nouvel element ou null si erreur
 */
TypVoisins* appendTypVoisins(TypVoisins* self, TypVoisins* incoming);

/**
 * ajout au debut d'un nouvel element dans la liste
 * @param self la liste
 * @param incoming le nouvel element
 * @return le nouvel element ou null si erreur
 */
TypVoisins* prependTypVoisins(TypVoisins* self, TypVoisins* incoming);
/**
 * Construit sur place un nouvel element d'une liste
 * @param self la liste
 * @param voisin le voisin
 * @param data la donnée
 * @return 
 */
TypVoisins* emplaceBackTypVoisins(TypVoisins* self, voisinT voisin, dataT data);

/**
 * Supprime un element de la liste
 * @param self
 * @return 
 */
bool removeTypVoisins(TypVoisins* self);

/**
 * Recherche d'un element suivant son voisin
 * @param self la liste
 * @param seek la valeur voisin a rechercher
 * @return l'element qui a la valeur voisin; NULL sinon
 */
TypVoisins* searchForVoisin(TypVoisins* self, voisinT seek);

/**
 * Recherche d'un element suivant son data
 * @param self la liste
 * @param seek la valeur data a rechercher
 * @return l'element qui a la valeur data; NULL sinon
 */
TypVoisins* searchForData(TypVoisins* self, dataT seek);




#ifdef	__cplusplus
}
#endif

