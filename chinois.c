#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "TypGraphe.h"
#include "myvector.h"
// Nous considérons que le graphe de départ est correct.
// Ainsi,vous n’avez pas à tester si le graphe est connexe, ni s’il est orienté ou non.

int countEdge(TypGraphe* self)
{
    if (!self)
    {
        return 0;
    }
    int ret = 0;
    for (int i = 0; i < self->nbMaxSommets; i++)
    {
        if (checkSommetExist(self, i))
        {
            ret += 0;
        }
    }
    return ret;
}

typedef struct FloyrdMarshallMatrixElement
{
    dataT dist;
    int next;
} FloyrdMarshallMatrixElementT;


//based on http://en.wikipedia.org/wiki/Floyd-Warshall_algorithm#Path_reconstruction

FloyrdMarshallMatrixElementT** FloydWarshallWithPathReconstruction(TypGraphe* self)
{
    FloyrdMarshallMatrixElementT** ret = malloc(self->nbMaxSommets * sizeof (FloyrdMarshallMatrixElementT*));

    //init
    for (int i = 0; i < self->nbMaxSommets; ++i)
    {
        ret[i] = malloc(self->nbMaxSommets * sizeof (FloyrdMarshallMatrixElementT));
        for (int j = 0; j < self->nbMaxSommets; ++j)
        {
            ret[i][j].dist = INT_MAX;
            ret[i][j].next = -1;
        }
        if (!checkSommetExist(self, i))
        {
            continue;
        }
        TypVoisins* it = self->listesAdjacences[i];
        do
        {
            if (!isSentinelTypVoisins(it))
            {
                ret[i][it->voisin].dist = it->data;
                ret[i][it->voisin].next = it->voisin;
            }
            it = it->voisinSuivant;
        }
        while (it != self->listesAdjacences[i]);
    }


    // Floyd-Warshall implementation
    for (int k = 0; k < self->nbMaxSommets; ++k)
    {
        for (int i = 0; i < self->nbMaxSommets; ++i)
        {
            for (int j = 0; j < self->nbMaxSommets; ++j)
            {
                if (ret[i][k].dist != INT_MAX && ret[k][j].dist != INT_MAX &&
                        ret[i][k].dist + ret[k][j].dist < ret[i][j].dist)
                {
                    ret[i][j].dist = ret[i][k].dist + ret[k][j].dist;
                    ret[i][j].next = ret[i][k].next;
                }
            }
        }
    }

    return ret;
}

void deleteFloyrdMarshallComputedMatrix(FloyrdMarshallMatrixElementT** self, size_t size)
{
    for (int j = 0; j < size; ++j)
    {
        free(self[j]);
    }
    free(self);
}

void resetColor(TypGraphe* self)
{
    for (int i = 0; i < self->nbMaxSommets; ++i)
    {
        if (!checkSommetExist(self, i))
        {
            continue;
        }
        TypVoisins* it = self->listesAdjacences[i];
        do
        {
            it->color = 0;
            it = it->voisinSuivant;
        }
        while (it != self->listesAdjacences[i]);
    }
}

vector SommetImpair(TypGraphe* g)
{
    vector ret;
    vector_init(&ret, 10);
    for (int i = 0; i < g->nbMaxSommets; ++i)
    {
        if (!checkSommetExist(g, i))
        {
            continue;
        }
        TypVoisins* it = g->listesAdjacences[i];
        int count = 0;
        do
        {
            if (!isSentinelTypVoisins(it))
            {
                count += 1;
            }
            it = it->voisinSuivant;
        }
        while (it != g->listesAdjacences[i]);

        if (count & 0x1)
        {
            vector_push_back(&ret, i);
        }
    }
    return ret;
}

vector ParcoursEulerien(TypGraphe* g)
{
    vector ret;
    vector remaining;


    vector sommetImpair = SommetImpair(g);
    size_t sommetImpairSize = vector_size(&sommetImpair);
    if (sommetImpairSize > 2 || sommetImpairSize == 1)
    {
        //can't resolve that
        vector_delete(&sommetImpair);
        return ret;
    }

    int startSommet = -1;
    if (sommetImpairSize == 2)
    {
        startSommet = vector_get(&sommetImpair, 0);
    }
    else
    {
        for (int i = 0; i < g->nbMaxSommets; ++i)
        {
            if (checkSommetExist(g, i))
            {
                startSommet = i;
                break;
            }
        }
    }

    vector_delete(&sommetImpair);

    if (startSommet == -1)
    {
        return ret;
    }

    resetColor(g);
    vector_init(&remaining, 6);
    vector_init(&ret, 10);
    int sommet = startSommet;

    TypVoisins* it = g->listesAdjacences[sommet];
    do
    {
        it = it->voisinSuivant;
    }
    while (it != g->listesAdjacences[sommet]);

    return ret;
}




