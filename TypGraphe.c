#include <stdio.h>
#include <stdlib.h>
#include "TypGraphe.h"

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

bool checkAccessListesAdjacences(TypGraphe* self, voisinT i)
{
    return self && i >= 0 && i < self->nbMaxSommets;
}

bool checkSommetExist(TypGraphe* self, voisinT i)
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

errorcode insertionAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data)
{
    if (!checkAccessListesAdjacences(self, from) || !checkAccessListesAdjacences(self, to))
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

errorcode insertionSymetriqueAreteTypGraphe(TypGraphe* self, voisinT from, voisinT to, dataT data)
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
    int ret = _suppressionAreteTypGraphe(self, from, to);
    if (!self->estOriente)
    {
        ret |= _suppressionAreteTypGraphe(self, to, from);
    }
    return ret;
}

errorcode suppressionSommetTypGraphe(TypGraphe* self, voisinT sommet)
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

void sauvegardeTypGraphe(TypGraphe* g, FILE* fichier)
{
    if (fichier)
    {
        fprintf(fichier, "# nombre maximum de sommets\n");
        fprintf(fichier, "%d\n", g->nbMaxSommets);
        fprintf(fichier, "# Orienter\n");
        fprintf(fichier, "%s\n", g->estOriente ? "o" : "n");
        fprintf(fichier, "# sommets : voisins\n");
        int i = 0;
        bool ajoutvirgule;
        for (i = 0; i < g->nbMaxSommets; i++)
        {
            ajoutvirgule = false;
            TypVoisins* it = g->listesAdjacences[i];
            if (it == NULL)
            {
                continue;
            }
            fprintf(fichier, "%d : ", i);
            do
            {
                if (!isSentinelTypVoisins(it))
                {
                    if (ajoutvirgule)
                    {
                        fprintf(fichier, ", ");
                    }
                    fprintf(fichier, "(%d/%d)", it->voisin, it->data);

                }
                ajoutvirgule = it != g->listesAdjacences[i];
                it = it->voisinSuivant;
                ajoutvirgule &= it != g->listesAdjacences[i];
            }
            while (it != g->listesAdjacences[i]);
            fprintf(fichier, "\n");
        }
    }

}

void affichageTypGraphe(TypGraphe* g)
{
    sauvegardeTypGraphe(g, stdout);
}
