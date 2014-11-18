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
/**
 * La structure TypGraphe
 */
typedef struct
{
    bool estOriente : 1;
    int nbMaxSommets;
    TypVoisins** listesAdjacences;
} TypGraphe;

typedef int errorcode;

/**
 * chaines des caracteres correspondant aux erreurs renvoyées par les fonctions
 *  ci dessous.
 */
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
/**
 * Crée un nouveau graph.
 * @param nbMaxSommets le nombre maximum de sommets
 * @param estOriente si le graph est oriente ou pas
 * @return un graph malloced.
 */
TypGraphe* newTypGraphe(int nbMaxSommets, bool estOriente);

/**
 * Verification d'un acces a une liste d'adjacences
 * @param self le graph
 * @param i le sommet cible
 * @return un boolean
 */
bool checkAccessListesAdjacences(TypGraphe* self, voisinT i);

/**
 * Verification de l'existance d'un sommet.
 * @param self le graph
 * @param i le sommet cible
 * @return un boolean
 */
bool checkSommetExist(TypGraphe* self, voisinT i);

/**
 * insertion d'un sommet dans un graph
 * @param self le graph
 * @param numero le sommet cible
 * @return une erreur si < 0
 */
errorcode insertionSommetTypGraphe(TypGraphe* self, voisinT numero);

/**
 * la fonction qui insert réelement une arrete dans un graph.
 * @param self le graph
 * @param from le sommet de depart
 * @param to le sommet d'arrivé
 * @param data la donnée
 * @return le nouvel element de la liste chainé ou null si erreur.
 */
static TypVoisins* _insertionAreteTypGraphe(TypGraphe* self, voisinT from,
                                            voisinT to, dataT data);

/**
 * permet de savoir si le sommet est adjacent a un autre.
 * @param self le graph
 * @param from le sommet de depart
 * @param to le sommet d'arrivé
 * @return l'element de la liste chainé qui definit le lien ou null pas de lien
 */
TypVoisins* getSommetAdjacentTypGraphe(TypGraphe* self, voisinT from, voisinT to);

/**
 * insertion d'une nouvelle arrete dans un graph.
 * @param self le graph
 * @param from le sommet de depart
 * @param to le sommet d'arrivé
 * @param data la donnée
 * @return une erreur si < 0
 */
errorcode insertionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data);

/**
 * insertion d'un chemin bidirectionnel entre deux sommet.
 * @param self le graph
 * @param from le sommet de depart
 * @param to le sommet d'arrivé
 * @param data la donnée
 * @return une erreur si < 0
 */
errorcode insertionSymetriqueAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data);

/**
 * la fonction qui supprime réelement une arrete d'un graph
 * @param self le graph
 * @param from le sommet de depart
 * @param to le sommet d'arrivé
 * @return une erreur si < 0
 */
errorcode _suppressionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to);

/**
 * supprime une arrete dans un graph
 * @param self le graph
 * @param from le sommet de depart
 * @param to le sommet d'arrivé
 * @return une erreur si < 0
 */
errorcode suppressionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to);

/**
 * supprime un sommet d'un graph
 * @param self le graph
 * @param sommet le sommet a supprimer
 * @return une erreur si < 0
 */
errorcode suppressionSommetTypGraphe(TypGraphe* self, voisinT sommet);

/**
 * Sauvegarde le graph dans un format specifié
 * @param g le graph
 * @param fichier le fichier où sauvegarder
 */
void sauvegardeTypGraphe(TypGraphe* g, FILE* fichier);

/**
 * Affichage d'un graph sur la sortie standard
 * @param g le graph
 */
void affichageTypGraphe(TypGraphe* g);

/**
 * Suppression du graph
 * @param self
 */
void deleteTypGraphe(TypGraphe* self);

#ifdef	__cplusplus
}
#endif

